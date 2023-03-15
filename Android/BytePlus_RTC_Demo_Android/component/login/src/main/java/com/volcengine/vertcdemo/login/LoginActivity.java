/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.login;

import android.app.AlertDialog;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.Html;
import android.text.SpannableStringBuilder;
import android.text.Spanned;
import android.text.TextUtils;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.text.style.URLSpan;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.lifecycle.Lifecycle;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.adapter.TextWatcherAdapter;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SocketConnectEvent;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.eventbus.UpgradeAppEvent;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.ServerResponse;
import com.volcengine.vertcdemo.entity.AuditStateResult;
import com.volcengine.vertcdemo.entity.LoginInfo;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.regex.Pattern;

public class LoginActivity extends BaseActivity implements View.OnClickListener {

    public static final String PHONE_NUM_INPUT_REGEX = "^[0-9]*$";
    public static final String NAME_INPUT_REGEX = "^[\\u4e00-\\u9fa5a-zA-Z0-9]*$";

    private EditText mPhoneNumberEt;
    private TextView mConfirmTv;
    private TextView mPhoneNumberError;
    private View mRoomLayout;
    private View mToastLayout;
    private TextView mToastTv;
    private TextView mPolicyText;
    private ImageView mPolicyIcon;

    private boolean mIsPolicyChecked = false;
    private long mLastClick = 0L;
    private long mRemain = 0;
    private long mLastShowDisconnectMs = 0;

    private SocketConnectEvent.ConnectStatus mConnectStatus = SocketConnectEvent.ConnectStatus.DISCONNECTED;

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    private final TextWatcherAdapter mTextWatcher = new TextWatcherAdapter() {
        @Override
        public void afterTextChanged(Editable s) {
            super.afterTextChanged(s);
            setupConfirmStatus();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        mRoomLayout = findViewById(R.id.verify_root_layout);
        mToastLayout = findViewById(R.id.verify_toast_layout);
        mToastTv = findViewById(R.id.verify_toast_text);
        mPhoneNumberEt = findViewById(R.id.verify_input_phone_number_et);
        mPhoneNumberError = findViewById(R.id.verify_input_phone_number_waring_tv);
        mConfirmTv = findViewById(R.id.verify_confirm);
        mPolicyIcon = findViewById(R.id.verify_policy_state);
        mPolicyText = findViewById(R.id.verify_policy_text);
        mConfirmTv.setOnClickListener(this);
        mRoomLayout.setOnClickListener(this);
        mPolicyIcon.setOnClickListener(this);
        mPolicyText.setOnClickListener(this);

        String str = getString(R.string.confirm_server_privace);
        Spanned text = Html.fromHtml(str);
        SpannableStringBuilder ssb = new SpannableStringBuilder(text);
        URLSpan[] urls = ssb.getSpans(0, ssb.length(), URLSpan.class);
        for (URLSpan span : urls) {
            setLinkClickable(ssb, span);
        }
        mPolicyText.setText(ssb);
        mPolicyText.setMovementMethod(LinkMovementMethod.getInstance());

        mPhoneNumberEt.addTextChangedListener(mTextWatcher);
        setupConfirmStatus();

        SolutionDemoEventManager.register(this);
    }

    private void setLinkClickable(final SpannableStringBuilder clickableHtmlBuilder,final URLSpan urlSpan) {
        int start = clickableHtmlBuilder.getSpanStart(urlSpan);
        int end = clickableHtmlBuilder.getSpanEnd(urlSpan);
        int flags = clickableHtmlBuilder.getSpanFlags(urlSpan);

        ClickableSpan clickableSpan = new ClickableSpan() {
            public void onClick(View view) {
                openBrowser(urlSpan.getURL());
            }
        };
        clickableHtmlBuilder.setSpan(clickableSpan, start, end, flags);
    }

    @Override
    public void finish() {
        super.finish();
        SolutionDemoEventManager.unregister(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mConfirmTv) {
            onClickConfirm();
        } else if (v == mRoomLayout) {
            IMEUtils.closeIME(mRoomLayout);
        } else if (v == mPolicyText || v == mPolicyIcon) {
            updatePolicyChecked();
            setupConfirmStatus();
        }
    }

    @Override
    public void onBackPressed() {
    }

    private void setupConfirmStatus() {
        String phoneNum = mPhoneNumberEt.getText().toString().trim();

        boolean isPhoneMatch = Pattern.matches(NAME_INPUT_REGEX, phoneNum) && phoneNum.length() <= 18;
        if (isPhoneMatch) {
            mPhoneNumberError.setVisibility(View.INVISIBLE);
        } else {
            mPhoneNumberError.setText(R.string.audio_input_wrong_content_waring);
            mPhoneNumberError.setVisibility(View.VISIBLE);
        }
        if (TextUtils.isEmpty(phoneNum) || !isPhoneMatch || !mIsPolicyChecked) {
            mConfirmTv.setAlpha(0.3F);
            mConfirmTv.setEnabled(false);
        } else {
            mConfirmTv.setEnabled(true);
            mConfirmTv.setAlpha(1F);
        }
    }

    private void onClickConfirm() {
        String phoneNum = mPhoneNumberEt.getText().toString().trim();
        mConfirmTv.setEnabled(false);
        IMEUtils.closeIME(mConfirmTv);
        LoginApi.passwordFreeLogin(phoneNum,
                new IRequestCallback<ServerResponse<LoginInfo>>() {
                    @Override
                    public void onSuccess(ServerResponse<LoginInfo> response) {
                        AppExecutors.mainThread().execute(() -> {
                            if (response.getCode() == 200) {
                                LoginInfo login = response.getData();
                                if (login == null) {
                                    return;
                                }
                                mConfirmTv.setEnabled(true);

                                SolutionDataManager.ins().setUserName(login.user_name);
                                SolutionDataManager.ins().setUserId(login.user_id);
                                SolutionDataManager.ins().store(login.login_token, login.user_id, login.user_name);

                                LoginActivity.this.finish();
                            } else {
                                onError(response.getCode(), response.getMsg());
                            }
                        });
                    }

                    @Override
                    public void onError(int errorCode, String message) {
                        showToast(message);
                        mConfirmTv.setEnabled(true);
                    }
                });
    }

    private void openUpdateDialog(AuditStateResult result) {
        if (getLifecycle().getCurrentState() != Lifecycle.State.RESUMED) {
            return;
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(this, R.style.transparentDialog);
        View view = getLayoutInflater().inflate(R.layout.layout_verify_upgrade, null);
        builder.setView(view);
        TextView cancel = view.findViewById(R.id.verify_upgrade_dialog_cancel);
        TextView confirm = view.findViewById(R.id.verify_upgrade_dialog_confirm);
        builder.setCancelable(true);
        AlertDialog dialog = builder.create();
        cancel.setOnClickListener((d) -> dialog.dismiss());
        confirm.setOnClickListener(v -> {
            Intent i = new Intent(Intent.ACTION_VIEW);
            i.setData(Uri.parse(result.url));
            LoginActivity.this.startActivity(i);
        });
        dialog.show();
    }

    private void showToast(String toast) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.postDelayed(mAutoDismiss, 2000);
        mToastTv.setText(toast);
    }

    private void dismissToast() {
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.setVisibility(View.GONE);
    }

    private void openBrowser(String url) {
        Intent i = new Intent(Intent.ACTION_VIEW);
        i.setData(Uri.parse(url));
        startActivity(i);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUpgradeAppEvent(UpgradeAppEvent event) {
        openUpdateDialog(event.result);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (event.status == SocketConnectEvent.ConnectStatus.CONNECTED) {
            dismissToast();
        } else {
            if (System.currentTimeMillis() - mLastShowDisconnectMs > 4000) {
                showToast(getString(R.string.network_error));
                mLastShowDisconnectMs = System.currentTimeMillis();
            }
        }
        mConnectStatus = event.status;
    }

    private void updatePolicyChecked() {
        mIsPolicyChecked = !mIsPolicyChecked;
        mPolicyIcon.setImageResource(mIsPolicyChecked ? R.drawable.circle_checked : R.drawable.circle_unchecked);
    }
}
