// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import android.content.Context;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;

import androidx.annotation.NonNull;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.annotation.CameraStatus;
import com.volcengine.vertcdemo.core.annotation.MicStatus;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.InteractChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.DialogVideoChatSettingBinding;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

/**
 * 视频互动设置对话框
 */
public class VideoChatSettingDialog extends BaseDialog {

    private DialogVideoChatSettingBinding mViewBinding;

    private final String mRoomId;
    private final IAction<Object> mBgmBtnAction;

    public VideoChatSettingDialog(@NonNull Context context, String roomId, IAction<Object> bgmBtnAction) {
        super(context);
        this.mRoomId = roomId;
        this.mBgmBtnAction = bgmBtnAction;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mViewBinding = DialogVideoChatSettingBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());
        
        super.onCreate(savedInstanceState);
        initView();
    }

    private void initView() {
        mViewBinding.bgmIv.setOnClickListener(v -> onClickBGM());
        
        VideoChatUserInfo selfUser = VideoChatDataManager.ins().selfUserInfo;
        String selfUid = selfUser == null ? null : selfUser.userId;
        VideoChatUserInfo hostUser = VideoChatDataManager.ins().hostUserInfo;
        String hostUid = hostUser == null ? null : hostUser.userId;
        if (!TextUtils.isEmpty(selfUid)) {
            boolean isHost = TextUtils.equals(selfUid, hostUid);
            mViewBinding.bgmIv.setVisibility(isHost ? View.VISIBLE : View.GONE);
            mViewBinding.bgmTv.setVisibility(isHost ? View.VISIBLE : View.GONE);
        }
        mViewBinding.micIv.setOnClickListener(v -> onClickMic());
        mViewBinding.cameraIv.setOnClickListener(v -> onClickCamera());
        mViewBinding.switchCameraIv.setOnClickListener(v -> onClickSwitchCamera());

        updateCameraAndMicView();
    }

    @Override
    public void show() {
        super.show();
        SolutionDemoEventManager.register(this);
    }

    @Override
    public void dismiss() {
        super.dismiss();
        SolutionDemoEventManager.unregister(this);
    }

    private void updateCameraAndMicView() {
        mViewBinding.cameraIv.setImageResource(VideoChatRTCManager.ins().isCameraOn() ? R.drawable.camera_on : R.drawable.camera_off_red);
        mViewBinding.micIv.setImageResource(VideoChatRTCManager.ins().isMicOn() ? R.drawable.mic_on : R.drawable.mic_off_red);
    }

    private void onClickBGM() {
        if (mBgmBtnAction != null) {
            mBgmBtnAction.act(null);
        }
        cancel();
    }

    private void onClickSwitchCamera() {
        VideoChatRTCManager.ins().switchCamera();
        cancel();
    }

    private void onClickMic() {
        VideoChatRTCManager.ins().turnOnMic();
        updateMediaStatus();
        cancel();
    }

    private void onClickCamera() {
        VideoChatRTCManager.ins().turnOnCamera();
        updateMediaStatus();
        cancel();
    }

    private void updateMediaStatus() {
        if (!TextUtils.isEmpty(mRoomId)) {
            int micStatus = VideoChatRTCManager.ins().isMicOn() ? MicStatus.ON : MicStatus.OFF;
            int cameraStatus = VideoChatRTCManager.ins().isCameraOn() ? CameraStatus.ON : CameraStatus.OFF;
            VideoChatRTCManager.ins().getRTSClient().updateMediaStatus(mRoomId, SolutionDataManager.ins().getUserId(), micStatus, cameraStatus, null);
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedEvent event) {
        if (!event.isStart && TextUtils.equals(SolutionDataManager.ins().getUserId(), event.userInfo.userId)) {
            dismiss();
        }
    }
}
