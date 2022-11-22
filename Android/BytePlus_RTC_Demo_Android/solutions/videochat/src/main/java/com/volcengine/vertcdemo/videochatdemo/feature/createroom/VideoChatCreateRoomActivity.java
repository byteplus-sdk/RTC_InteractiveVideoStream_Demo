/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.createroom;

import static com.volcengine.vertcdemo.core.SolutionConstants.CLICK_RESET_INTERVAL;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SocketConnectEvent;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.CreateRoomResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.LiveUserInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.common.VideoChatCreateSettingDialog;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.VideoChatRoomMainActivity;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class VideoChatCreateRoomActivity extends BaseActivity implements View.OnClickListener {

    private View mTopTip;
    private View mBackBtn;
    private View mSwitchCameraBtn;
    private View mVideoEffectBtn;
    private View mVideoSettingBtn;
    private View mStartLiveBtn;
    private TextureView mLocalVideoView;

    private boolean mEnableStartLive = false;
    private VCRoomInfo mRoomInfo;
    private VCUserInfo mSelfInfo;
    private String mRTCToken;

    private long mLastClickStartLiveTs = 0;

    private final IRequestCallback<CreateRoomResponse> mCreateRoomRequest = new IRequestCallback<CreateRoomResponse>() {
        @Override
        public void onSuccess(CreateRoomResponse data) {
            Log.d("bytertc","mCreateRoomRequest success");
            mEnableStartLive = true;
            mRoomInfo = data.roomInfo;
            mSelfInfo = data.userInfo;
            mRTCToken = data.rtcToken;
            VideoChatRTCManager.ins().setLocalVideoView(mLocalVideoView);
            VideoChatRTCManager.ins().startVideoCapture(true);
            VideoChatRTCManager.ins().startAudioCapture(true);
        }

        @Override
        public void onError(int errorCode, String message) {
            Log.d("bytertc","mCreateRoomRequest error");
            SafeToast.show(message);
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_video_chat_room);
        requestCreateVideoRoom();
        VideoChatRTCManager.ins().turnOnCamera(true);
        VideoChatRTCManager.ins().turnOnMic(true);
        VideoChatRTCManager.ins().switchCamera(true);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        mTopTip = findViewById(R.id.create_disconnect_tip);
        mStartLiveBtn = findViewById(R.id.start_live);
        mStartLiveBtn.setOnClickListener(this);
        mBackBtn = findViewById(R.id.exit_create_live);
        mBackBtn.setOnClickListener(this);
        mSwitchCameraBtn = findViewById(R.id.switch_camera_iv);
        mSwitchCameraBtn.setOnClickListener(this);
        mVideoEffectBtn = findViewById(R.id.effect_iv);
        mVideoEffectBtn.setOnClickListener(this);
        mVideoSettingBtn = findViewById(R.id.settings_iv);
        mVideoSettingBtn.setOnClickListener(this);
        FrameLayout mLocalVideoViewContainer = findViewById(R.id.preview_view_container);
        mLocalVideoView = VideoChatRTCManager.ins().getUserRenderView(SolutionDataManager.ins().getUserId());
        Utilities.removeFromParent(mLocalVideoView);
        mLocalVideoViewContainer.removeAllViews();
        mLocalVideoViewContainer.addView(mLocalVideoView, new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

        SolutionDemoEventManager.register(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mBackBtn) {
            onBackPressed();
        } else if (v == mSwitchCameraBtn) {
            switchCamera();
        } else if (v == mVideoEffectBtn) {
            openVideoEffectDialog();
        } else if (v == mVideoSettingBtn) {
            openVideoVideoSettingDialog();
        } else if (v == mStartLiveBtn) {
            startLive();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        VideoChatRTCManager.ins().startVideoCapture(true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        VideoChatRTCManager.ins().startVideoCapture(false);
    }

    @Override
    public void finish() {
        super.finish();
        SolutionDemoEventManager.unregister(this);
    }

    private void switchCamera() {
        VideoChatRTCManager.ins().switchCamera();
    }

    private void openVideoEffectDialog() {
        showToast(getString(R.string.effect_toast));
    }

    private void openVideoVideoSettingDialog() {
        VideoChatCreateSettingDialog settingDialog = new VideoChatCreateSettingDialog(this, false, null);
        settingDialog.show();
    }

    private void startLive() {
        if (!mEnableStartLive) {
            showToast(getString(R.string.start_live_error));
            return;
        }
        long now = System.currentTimeMillis();
        if (now - mLastClickStartLiveTs <= CLICK_RESET_INTERVAL) {
            return;
        }
        mLastClickStartLiveTs = now;
        VideoChatRTCManager.ins().getRTMClient().requestStartLive(mRoomInfo.roomId, new IRequestCallback<LiveUserInfo>() {
            @Override
            public void onSuccess(LiveUserInfo userInfo) {
                mLastClickStartLiveTs = 0;
                showToast(getString(R.string.start_live_success));
                mRoomInfo.status = VCRoomInfo.ROOM_STATUS_LIVING;
                VideoChatRoomMainActivity.openFromCreate(VideoChatCreateRoomActivity.this,
                        mRoomInfo, mSelfInfo, mRTCToken);
                finish();
            }

            @Override
            public void onError(int errorCode, String message) {
                mLastClickStartLiveTs = 0;
                showToast(getString(R.string.start_live_fail));
            }
        });
    }

    private void requestCreateVideoRoom() {
        Log.d("bytertc","requestCreateVideoRoom");
        String roomName = getString(R.string.video_chat_room_name, SolutionDataManager.ins().getUserName());
        VideoChatRTCManager.ins().getRTMClient().requestCreateRoom(SolutionDataManager.ins().getUserName(),
                roomName, "voicechat_background_1.jpg", mCreateRoomRequest);
    }

    private void showToast(String toast) {
        SafeToast.show(toast);
    }

    private void showTopTip(boolean isShow) {
        mTopTip.setVisibility(isShow ? View.VISIBLE : View.GONE);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        boolean show = event.status == SocketConnectEvent.ConnectStatus.DISCONNECTED
                || event.status == SocketConnectEvent.ConnectStatus.CONNECTING;
        showTopTip(show);
    }

    public static void open(Activity activity) {
        Intent intent = new Intent(activity, VideoChatCreateRoomActivity.class);
        activity.startActivity(intent);
    }
}
