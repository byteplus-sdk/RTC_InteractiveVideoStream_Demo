// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import static com.volcengine.vertcdemo.videochat.core.VideoChatDataManager.SEAT_STATUS_LOCKED;
import static com.volcengine.vertcdemo.videochat.core.VideoChatDataManager.SEAT_STATUS_UNLOCKED;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.core.content.ContextCompat;

import com.ss.bytertc.engine.type.NetworkQuality;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.utils.AppUtil;
import com.volcengine.vertcdemo.utils.Utils;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.VideoChatSeatInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.LayoutVideoChatSeatBinding;
import com.volcengine.vertcdemo.videochat.event.SDKNetStatusEvent;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

/**
 * 单个座位控件
 */
public class VideoChatSeatLayout extends ConstraintLayout {

    private final VideoChatSeatInfo mSeatInfo = new VideoChatSeatInfo();

    private LayoutVideoChatSeatBinding mViewBinding;

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
        View view = View.inflate(getContext(), R.layout.layout_video_chat_seat, this);
        mViewBinding = LayoutVideoChatSeatBinding.bind(view);
        bind(null);
    }

    public void setIndex(int index) {
        mSeatInfo.seatIndex = index;
    }

    public int getIndex() {
        return mSeatInfo.seatIndex;
    }

    public void bind(@Nullable VideoChatSeatInfo info) {
        mSeatInfo.status = info == null ? SEAT_STATUS_UNLOCKED : info.status;
        mSeatInfo.userInfo = info == null ? null : info.userInfo == null ? null : info.userInfo.deepCopy();
        updateLockedStatus(mSeatInfo.isLocked());
        if (mSeatInfo.userInfo == null || mSeatInfo.isLocked()) {
            mViewBinding.videoChatSeatNetworkTv.setVisibility(GONE);
            mViewBinding.videoChatSeatVideoContainer.removeAllViews();
            mViewBinding.videoChatSeatCameraOffTv.setVisibility(GONE);
            mViewBinding.videoChatSeatEmpty.setVisibility(VISIBLE);
            mViewBinding.videoChatMainRoomBottomCover.setVisibility(GONE);
            mViewBinding.videoChatMainRoomNameIv.setVisibility(GONE);
            mViewBinding.videoChatMainRoomHostIv.setVisibility(GONE);
            mViewBinding.videoChatMainRoomMicOffIv.setVisibility(GONE);
        } else {
            mViewBinding.videoChatSeatEmpty.setVisibility(GONE);
            mViewBinding.videoChatSeatNetworkTv.setVisibility(VISIBLE);
            mViewBinding.videoChatSeatCameraOffTv.setText(mSeatInfo.userInfo.userName.substring(0, 1));
            mViewBinding.videoChatMainRoomBottomCover.setVisibility(VISIBLE);
            mViewBinding.videoChatMainRoomNameIv.setVisibility(VISIBLE);
            mViewBinding.videoChatMainRoomNameIv.setText(mSeatInfo.userInfo.userName);
            if (mSeatInfo.userInfo.isHost()) {
                mViewBinding.videoChatMainRoomHostIv.setVisibility(VISIBLE);
            }
            if (mSeatInfo.userInfo.isMicOn()) {
                mViewBinding.videoChatMainRoomMicOffIv.setVisibility(GONE);
            } else {
                mViewBinding.videoChatMainRoomMicOffIv.setVisibility(VISIBLE);
            }
            onUserCameraStateUpdated(mSeatInfo.userInfo.userId, mSeatInfo.userInfo.userName, mSeatInfo.userInfo.isCameraOn());
        }
    }

    public void updateLockedStatus(boolean isLocked) {
        if (isLocked) {
            mViewBinding.videoChatSeatEmptyIv.setImageResource(R.drawable.video_chat_room_main_seat_locked);
        } else {
            mViewBinding.videoChatSeatEmptyIv.setImageResource(R.drawable.video_chat_room_main_seat_empty);
        }
        mSeatInfo.status = isLocked ? SEAT_STATUS_LOCKED : SEAT_STATUS_UNLOCKED;
    }

    private void onUserCameraStateUpdated(String userID, String userName, boolean cameraOn) {
        if (cameraOn) {
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            TextureView renderView = VideoChatRTCManager.ins().getUserRenderView(userID);
            Utils.removeFromParent(renderView);
            mViewBinding.videoChatSeatVideoContainer.addView(renderView, params);
            if (TextUtils.equals(userID, SolutionDataManager.ins().getUserId())) {
                VideoChatRTCManager.ins().setLocalVideoView(renderView);
            } else {
                VideoChatRTCManager.ins().setRemoteVideoView(userID, VideoChatDataManager.ins().hostUserInfo.roomId, renderView);
            }
            mViewBinding.videoChatSeatCameraOffTv.setVisibility(GONE);
        } else {
            mViewBinding.videoChatSeatVideoContainer.removeAllViews();
            mViewBinding.videoChatSeatCameraOffTv.setVisibility(VISIBLE);
            if (TextUtils.equals(userID, SolutionDataManager.ins().getUserId())) {
                VideoChatRTCManager.ins().setLocalVideoView(new TextureView(getContext()));
            } else {
                VideoChatRTCManager.ins().setRemoteVideoView(userID, VideoChatDataManager.ins().hostUserInfo.roomId, null);
            }
        }
    }

    public void updateMicStatus(String userId, boolean micOn, boolean cameraOn) {
        if (mSeatInfo.userInfo != null && TextUtils.equals(mSeatInfo.userInfo.userId, userId)) {
            mSeatInfo.userInfo.mic = micOn ? VideoChatUserInfo.MIC_STATUS_ON : VideoChatUserInfo.MIC_STATUS_OFF;
            if (mSeatInfo.userInfo.isMicOn()) {
                mViewBinding.videoChatMainRoomMicOffIv.setVisibility(GONE);
            } else {
                mViewBinding.videoChatMainRoomMicOffIv.setVisibility(VISIBLE);
            }
            if (mSeatInfo.userInfo.isCameraOn() != cameraOn) {
                mSeatInfo.userInfo.camera = cameraOn ? VideoChatUserInfo.CAMERA_STATUS_ON : VideoChatUserInfo.CAMERA_STATUS_OFF;
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

    public void setSeatClick(IAction<VideoChatSeatInfo> action) {
        setOnClickListener((v) -> {
            if (action != null && mSeatInfo != null) {
                action.act(mSeatInfo);
            }
        });
    }


    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
        SolutionDemoEventManager.register(this);
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        SolutionDemoEventManager.unregister(this);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void updateNetQuality(SDKNetStatusEvent event) {
        int visibility = mViewBinding.videoChatSeatNetworkTv.getVisibility();
        if (visibility == View.VISIBLE && TextUtils.equals(event.uid, mSeatInfo.userInfo.userId)) {
            updateNetStatus(mViewBinding.videoChatSeatNetworkTv, event.networkQuality);
        }
    }

    private int mLastNetworkQuality;

    private void updateNetStatus(TextView textView, int networkQuality) {
        if (textView == null || mLastNetworkQuality == networkQuality) {
            return;
        }
        mLastNetworkQuality = networkQuality;
        boolean good = networkQuality == NetworkQuality.NETWORK_QUALITY_GOOD ||
                networkQuality == NetworkQuality.NETWORK_QUALITY_EXCELLENT;
        textView.setText(good ? R.string.net_excellent : R.string.net_stuck_stopped);
        Drawable netStatusDrawable = ContextCompat.getDrawable(AppUtil.getApplicationContext(), good ? R.drawable.net_status_good : R.drawable.net_status_bad);
        if (netStatusDrawable != null) {
            netStatusDrawable.setBounds(0, 0, (int) Utils.dp2Px(12), (int) Utils.dp2Px(12));
        }
        textView.setCompoundDrawables(netStatusDrawable, null, null, null);
    }
}
