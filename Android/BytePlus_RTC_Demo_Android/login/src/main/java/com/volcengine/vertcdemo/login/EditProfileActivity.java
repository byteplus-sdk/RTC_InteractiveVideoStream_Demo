/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.login;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.adapter.TextWatcherAdapter;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.RefreshUserNameEvent;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.ServerResponse;

import java.util.regex.Pattern;

public class EditProfileActivity extends BaseActivity {

    public static final String INPUT_REGEX = "^[\\u4e00-\\u9fa5a-zA-Z0-9@_-]+$";
    public static final int USER_NAME_MAX_LENGTH = 18;
    private View mRootView;
    private View mToastLayout;
    private TextView mToastTv;
    private TextView mConfirmBtn;
    private EditText mUserNameEt;
    private TextView mErrorTv;
    private String mUserName;

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    private final TextWatcherAdapter mUserNameTextWatcher = new TextWatcherAdapter() {

        @Override
        public void afterTextChanged(Editable s) {
            Log.d("afterTextChanged", s.toString());
            setupInputStatus(s.toString());
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.change_user_name_txt);
        mConfirmBtn = findViewById(R.id.title_bar_right_tv);
        mConfirmBtn.setText(R.string.btn_ok);
        mConfirmBtn.setOnClickListener(v -> {
            String userName = mUserNameEt.getText().toString().trim();
            if (TextUtils.isEmpty(userName)) {
                setupInputStatus(userName);
            } else {
                AppExecutors.networkIO().execute(
                        () -> LoginApi.changeUserName(userName, SolutionDataManager.ins().getToken(),
                                new IRequestCallback<ServerResponse<Void>>() {
                                    @Override
                                    public void onSuccess(ServerResponse<Void> response) {
                                        SolutionDataManager.ins().setUserName(userName);
                                        RefreshUserNameEvent event = new RefreshUserNameEvent(userName, true);
                                        SolutionDemoEventManager.post(event);
                                        finish();
                                    }

                                    @Override
                                    public void onError(int errorCode, String message) {
                                        SafeToast.show(message);
                                    }
                                }));
            }
        });

        mToastLayout = findViewById(R.id.profile_toast_layout);
        mToastTv = findViewById(R.id.profile_toast_text);
        mRootView = findViewById(R.id.profile_root_view);
        mRootView.setOnClickListener(v -> IMEUtils.closeIME(mRootView));
        mUserNameEt = findViewById(R.id.profile_user_name_input);
        mErrorTv = findViewById(R.id.profile_user_name_error);
        View mClearBtn = findViewById(R.id.profile_user_name_clear);
        mClearBtn.setOnClickListener(v -> mUserNameEt.setText(""));

        mUserName = SolutionDataManager.ins().getUserName();
        mUserNameEt.setText(mUserName);
        mUserNameEt.removeTextChangedListener(mUserNameTextWatcher);
        mUserNameEt.addTextChangedListener(mUserNameTextWatcher);
    }

    private void setupInputStatus(String newUserName) {
        if (newUserName.length() > USER_NAME_MAX_LENGTH) {
            mErrorTv.setText(R.string.login_input_meeting_id_waring);
            mErrorTv.setVisibility(View.VISIBLE);
            mConfirmBtn.setEnabled(true);
        } else {
            if (Pattern.matches(INPUT_REGEX, newUserName)) {
                mErrorTv.setVisibility(View.INVISIBLE);
                mConfirmBtn.setEnabled(true);
            } else {
                mErrorTv.setVisibility(View.VISIBLE);
                mErrorTv.setText(R.string.audio_input_wrong_content_waring);
                mConfirmBtn.setEnabled(false);
            }
        }
        mUserName = newUserName;
    }

    private void showToast(String toast) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.postDelayed(mAutoDismiss, 2000);
        mToastTv.setText(toast);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }
}
