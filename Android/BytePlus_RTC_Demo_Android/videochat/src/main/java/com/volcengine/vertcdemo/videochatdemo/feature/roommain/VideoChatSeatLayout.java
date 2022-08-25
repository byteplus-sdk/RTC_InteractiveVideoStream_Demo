/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.SEAT_STATUS_LOCKED;
import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.SEAT_STATUS_UNLOCKED;

import android.content.Context;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.VCSeatInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

public class VideoChatSeatLayout extends FrameLayout {


    private final VCSeatInfo mSeatInfo = new VCSeatInfo();

    // network status
    private LinearLayout mNetworkStatusContainer;
    private ImageView mNetworkStateIv;
    private TextView mNetworkStateTv;

    private FrameLayout mVideoContainer;

    private TextView mUserNamePrefixTv;

    private View mSeatEmptyView;
    private ImageView mSeatEmptyIv;

    private View mSeatBottomCoverView;

    private TextView mUserNameTv;

    // 主播身份标记
    private TextView mHostIv;

    private ImageView mMicOffIv;

    public VideoChatSeatLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public VideoChatSeatLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public VideoChatSeatLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_video_chat_demo_seat, this, true);
        mNetworkStatusContainer = findViewById(R.id.video_chat_seat_network_container);
        mNetworkStateIv = findViewById(R.id.video_chat_seat_network_iv);
        mNetworkStateTv = findViewById(R.id.video_chat_seat_network_tv);
        mVideoContainer = findViewById(R.id.video_chat_seat_video_container);
        mUserNamePrefixTv = findViewById(R.id.video_chat_seat_camera_off_tv);
        mSeatEmptyView = findViewById(R.id.video_chat_seat_empty);
        mSeatEmptyIv = findViewById(R.id.video_chat_seat_empty_iv);
        mSeatBottomCoverView = findViewById(R.id.video_chat_main_room_bottom_cover);
        mUserNameTv = findViewById(R.id.video_chat_main_room_name_iv);
        mHostIv = findViewById(R.id.video_chat_main_room_host_iv);
        mMicOffIv = findViewById(R.id.video_chat_main_room_mic_off_iv);
        bind(null);
    }

    public void setIndex(int index) {
        mSeatInfo.seatIndex = index;
    }

    public int getIndex() {
        return mSeatInfo.seatIndex;
    }

    public void bind(@Nullable VCSeatInfo info) {
        mSeatInfo.status = info == null ? SEAT_STATUS_UNLOCKED : info.status;
        mSeatInfo.userInfo = info == null ? null : info.userInfo == null ? null : info.userInfo.deepCopy();
        updateLockedStatus(mSeatInfo.isLocked());
        if (mSeatInfo.userInfo == null || mSeatInfo.isLocked()) {
            mNetworkStatusContainer.setVisibility(GONE);
            mVideoContainer.removeAllViews();
            mUserNamePrefixTv.setVisibility(GONE);
            mSeatEmptyView.setVisibility(VISIBLE);
            mSeatBottomCoverView.setVisibility(GONE);
            mUserNameTv.setVisibility(GONE);
            mHostIv.setVisibility(GONE);
            mMicOffIv.setVisibility(GONE);
        } else {
            mSeatEmptyView.setVisibility(GONE);
            mNetworkStatusContainer.setVisibility(VISIBLE);
            mUserNamePrefixTv.setText(mSeatInfo.userInfo.userName.substring(0, 1));
            mSeatBottomCoverView.setVisibility(VISIBLE);
            mUserNameTv.setVisibility(VISIBLE);
            mUserNameTv.setText(mSeatInfo.userInfo.userName);
            if (mSeatInfo.userInfo.isHost()) {
                mHostIv.setVisibility(VISIBLE);
            }
            if (mSeatInfo.userInfo.isMicOn()) {
                mMicOffIv.setVisibility(GONE);
            } else {
                mMicOffIv.setVisibility(VISIBLE);
            }
            onUserCameraStateUpdated(mSeatInfo.userInfo.userId, mSeatInfo.userInfo.userName, mSeatInfo.userInfo.isCameraOn());
        }
    }

    public void updateLockedStatus(boolean isLocked) {
        if (isLocked) {
            mSeatEmptyIv.setImageResource(R.drawable.video_chat_room_main_seat_locked);
        } else {
            mSeatEmptyIv.setImageResource(R.drawable.video_chat_room_main_seat_empty);
        }
        mSeatInfo.status = isLocked ? SEAT_STATUS_LOCKED : SEAT_STATUS_UNLOCKED;
    }

    private void onUserCameraStateUpdated(String userID, String userName, boolean cameraOn) {
        if (cameraOn) {
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            TextureView renderView = VideoChatRTCManager.ins().getUserRenderView(userID);
            Utilities.removeFromParent(renderView);
            mVideoContainer.addView(renderView, params);
            if (TextUtils.equals(userID, SolutionDataManager.ins().getUserId())) {
                VideoChatRTCManager.ins().setLocalVideoView(renderView);
            } else {
                VideoChatRTCManager.ins().setRemoteVideoView(userID, renderView);
            }
            mUserNamePrefixTv.setVisibility(GONE);
        } else {
            mVideoContainer.removeAllViews();
            mUserNamePrefixTv.setVisibility(VISIBLE);
            if (TextUtils.equals(userID, SolutionDataManager.ins().getUserId())) {
                VideoChatRTCManager.ins().setLocalVideoView(null);
            } else {
                VideoChatRTCManager.ins().setRemoteVideoView(userID, null);
            }
        }
    }

    public void updateMicStatus(String userId, boolean micOn, boolean cameraOn) {
        if (mSeatInfo.userInfo != null && TextUtils.equals(mSeatInfo.userInfo.userId, userId)) {
            mSeatInfo.userInfo.mic = micOn ? VCUserInfo.MIC_STATUS_ON : VCUserInfo.MIC_STATUS_OFF;
            if (mSeatInfo.userInfo.isMicOn()) {
                mMicOffIv.setVisibility(GONE);
            } else {
                mMicOffIv.setVisibility(VISIBLE);
            }
            if (mSeatInfo.userInfo.isCameraOn() != cameraOn) {
                mSeatInfo.userInfo.camera = cameraOn ? VCUserInfo.CAMERA_STATUS_ON : VCUserInfo.CAMERA_STATUS_OFF;
                onUserCameraStateUpdated(mSeatInfo.userInfo.userId, mSeatInfo.userInfo.userName, cameraOn);
            }
        }
    }

    private void updateVolumeStatus(int volume, boolean forceUpdate) {
    }

    public void updateVolumeStatus(String userId, int volume) {
        if (mSeatInfo.userInfo != null && TextUtils.equals(mSeatInfo.userInfo.userId, userId)) {
            updateVolumeStatus(volume, false);
        }
    }

    public void setSeatClick(IAction<VCSeatInfo> action) {
        setOnClickListener((v) -> {
            if (action != null && mSeatInfo != null) {
                action.act(mSeatInfo);
            }
        });
    }
}
