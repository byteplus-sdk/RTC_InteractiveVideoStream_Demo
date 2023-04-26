// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.createroom;

import static com.volcengine.vertcdemo.core.SolutionConstants.CLICK_RESET_INTERVAL;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.TextureView;

import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.common.SolutionBaseActivity;
import com.volcengine.vertcdemo.common.SolutionToast;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.eventbus.AppTokenExpiredEvent;
import com.volcengine.vertcdemo.core.net.ErrorTool;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.utils.Utils;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.CreateRoomEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatResponse;
import com.volcengine.vertcdemo.videochat.bean.VideoChatRoomInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.ActivityCreateVideoChatRoomBinding;
import com.volcengine.vertcdemo.videochat.feature.roommain.VideoChatRoomMainActivity;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

/**
 * Create video chat room activity.
 */
public class VideoChatCreateRoomActivity extends SolutionBaseActivity {

    private static final String TAG = "VideoChatCreate";

    private ActivityCreateVideoChatRoomBinding mViewBinding;

    private TextureView mLocalVideoView;

    private boolean mEnableStartLive = false;
    private VideoChatRoomInfo mRoomInfo;
    private VideoChatUserInfo mSelfInfo;
    private String mRTCToken;

    private long mLastClickStartLiveTs = 0;

    /**
     * The callback for creating video room.
     */
    private final IRequestCallback<CreateRoomEvent> mCreateRoomRequest = new IRequestCallback<CreateRoomEvent>() {
        @Override
        public void onSuccess(CreateRoomEvent data) {
            mEnableStartLive = true;
            mRoomInfo = data.roomInfo;
            mSelfInfo = data.userInfo;
            mRTCToken = data.rtcToken;
            VideoChatRTCManager.ins().setLocalVideoView(mLocalVideoView);
            VideoChatRTCManager.ins().startVideoCapture(true);
            VideoChatRTCManager.ins().startAudioCapture(true);
            dismissLoadingDialog();
        }

        @Override
        public void onError(int errorCode, String message) {
            SolutionToast.show(ErrorTool.getErrorMessageByErrorCode(errorCode, message));
            dismissLoadingDialog();
            finish();
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mViewBinding = ActivityCreateVideoChatRoomBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());
        
        requestCreateVideoRoom();
        VideoChatRTCManager.ins().turnOnCamera(true);
        VideoChatRTCManager.ins().turnOnMic(true);
        VideoChatRTCManager.ins().switchCamera(true);

        String hint = getString(R.string.application_experiencing_xxx_title, "20");
        mViewBinding.experienceTimeHint.setText(hint);

        mViewBinding.startLive.setOnClickListener(v -> startLive());
        mViewBinding.exitCreateLive.setOnClickListener(v -> onBackPressed());
        mViewBinding.switchCameraIv.setOnClickListener(v -> switchCamera());
        mViewBinding.effectIv.setOnClickListener(v -> openVideoEffectDialog());
        mViewBinding.settingsIv.setOnClickListener(v -> openVideoVideoSettingDialog());

        setLocalVideoView();

        SolutionDemoEventManager.register(this);

        VideoChatRTCManager.ins().resumeVideoEffect();
    }

    private void setLocalVideoView() {
        mLocalVideoView = VideoChatRTCManager.ins().getUserRenderView(SolutionDataManager.ins().getUserId());
        Utils.attachViewToViewGroup(mViewBinding.previewViewContainer, mLocalVideoView);
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
    protected void onDestroy() {
        super.onDestroy();
        SolutionDemoEventManager.unregister(this);
    }

    @Override
    protected boolean onMicrophonePermissionClose() {
        Log.d(TAG, "onMicrophonePermissionClose");
        finish();
        return true;
    }

    @Override
    protected boolean onCameraPermissionClose() {
        Log.d(TAG, "onCameraPermissionClose");
        finish();
        return true;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(AppTokenExpiredEvent event) {
        finish();
    }

    /**
     * Switch camera.
     */
    private void switchCamera() {
        VideoChatRTCManager.ins().switchCamera();
    }

    /**
     * Open video effect dialog.
     */
    private void openVideoEffectDialog() {
        VideoChatRTCManager.ins().openEffectDialog(this);
    }

    /**
     * Open video setting dialog.
     */
    private void openVideoVideoSettingDialog() {
        VideoChatCreateSettingDialog settingDialog = new VideoChatCreateSettingDialog(this, false, null);
        settingDialog.show();
    }

    /**
     * Start live.
     */
    private void startLive() {
        if (!mEnableStartLive) {
            SolutionToast.show(R.string.failed_get_live_information);
            return;
        }
        long now = System.currentTimeMillis();
        if (now - mLastClickStartLiveTs <= CLICK_RESET_INTERVAL) {
            return;
        }
        mLastClickStartLiveTs = now;
        VideoChatRTCManager.ins().getRTSClient().requestStartLive(mRoomInfo.roomId,
                new IRequestCallback<VideoChatResponse>() {
                    @Override
                    public void onSuccess(VideoChatResponse response) {
                        mLastClickStartLiveTs = 0;
                        SolutionToast.show(R.string.live_started);
                        mRoomInfo.status = VideoChatRoomInfo.ROOM_STATUS_LIVING;
                        VideoChatRoomMainActivity.openFromCreate(VideoChatCreateRoomActivity.this,
                                mRoomInfo, mSelfInfo, mRTCToken);
                        finish();
                    }

                    @Override
                    public void onError(int errorCode, String message) {
                        mLastClickStartLiveTs = 0;
                        SolutionToast.show(R.string.failed_create_live);
                    }
                });
    }

    /**
     * Send a request to the business to create a video room.
     */
    private void requestCreateVideoRoom() {
        showLoadingDialog();
        VideoChatRTCManager.ins().getRTSClient().requestCreateRoom(
                getString(R.string.video_chat_xxx_live, SolutionDataManager.ins().getUserName()),
                SolutionDataManager.ins().getUserName(),
                "", mCreateRoomRequest);
    }

    public static void open(Activity activity) {
        Intent intent = new Intent(activity, VideoChatCreateRoomActivity.class);
        activity.startActivity(intent);
    }
}
