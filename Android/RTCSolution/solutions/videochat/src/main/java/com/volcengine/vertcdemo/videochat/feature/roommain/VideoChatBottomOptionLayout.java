// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;


import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_ROLE_HOST;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.VideoChatRoomInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.databinding.LayoutVideoChatMainBottomOptionBinding;

/**
 * 视频互动主页底部功能按钮控件
 */
public class VideoChatBottomOptionLayout extends LinearLayout {

    private LayoutVideoChatMainBottomOptionBinding mViewBinding;

    private IBottomOptions mIBottomOptions;

    public VideoChatBottomOptionLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public VideoChatBottomOptionLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public VideoChatBottomOptionLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        View view = View.inflate(getContext(), R.layout.layout_video_chat_main_bottom_option, this);
        mViewBinding = LayoutVideoChatMainBottomOptionBinding.bind(view);

        mViewBinding.videoChatMainOptionInputBtn.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onInputClick();
            }
        });
        mViewBinding.videoChatMainOptionPkBtn.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onPkClick();
            }
        });
        mViewBinding.videoChatMainOptionInteractBtn.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onInteractClick();
            }
        });
        mViewBinding.videoChatMainOptionSetting.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onSettingsClick();
            }
        });
        mViewBinding.videoChatMainOptionEffect.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onEffectClick();
            }
        });
    }

    public void setOptionCallback(IBottomOptions callback) {
        mIBottomOptions = callback;
    }

    public void updateUIByRoleAndStatus(@VideoChatRoomInfo.RoomStatus int roomStatus,
                                        @VideoChatUserInfo.UserRole int userRole,
                                        @VideoChatUserInfo.UserStatus int userStatus) {
        if (roomStatus == VideoChatRoomInfo.ROOM_STATUS_LIVING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mViewBinding.videoChatMainOptionPkBtn.setImageResource(R.drawable.video_chat_main_option_pk);
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionSetting.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionEffect.setVisibility(VISIBLE);
            } else {//观众
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(GONE);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionSetting.setVisibility(GONE);
                mViewBinding.videoChatMainOptionEffect.setVisibility(GONE);
            }
            return;
        }
        if (roomStatus == VideoChatRoomInfo.ROOM_STATUS_PK_ING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionPkBtn.setImageResource(R.drawable.video_chat_main_option_cancel_pk);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionSetting.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionEffect.setVisibility(VISIBLE);
            } else {//观众
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(GONE);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(GONE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(GONE);
                mViewBinding.videoChatMainOptionSetting.setVisibility(GONE);
                mViewBinding.videoChatMainOptionEffect.setVisibility(GONE);
            }
            return;
        }
        if (roomStatus == VideoChatRoomInfo.ROOM_STATUS_CHATTING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionSetting.setVisibility(VISIBLE);
                mViewBinding.videoChatMainOptionEffect.setVisibility(VISIBLE);
            } else {//观众
                mViewBinding.videoChatMainOptionPkBtn.setVisibility(GONE);
                mViewBinding.videoChatMainOptionInteractFl.setVisibility(GONE);
                mViewBinding.videoChatMainOptionInteractBtn.setVisibility(GONE);
                boolean isInteracting = userStatus == VideoChatUserInfo.USER_STATUS_INTERACT;
                if (isInteracting) {
                    mViewBinding.videoChatMainOptionSetting.setVisibility(VISIBLE);
                    mViewBinding.videoChatMainOptionEffect.setVisibility(VISIBLE);
                } else {
                    mViewBinding.videoChatMainOptionSetting.setVisibility(GONE);
                    mViewBinding.videoChatMainOptionEffect.setVisibility(GONE);
                }
            }
        }
    }

    public void updateDotTip(boolean withDot) {
        mViewBinding.icInteractIndicator.setVisibility(withDot ? VISIBLE : GONE);
    }

    public interface IBottomOptions {

        void onInputClick();

        void onPkClick();

        void onInteractClick();

        void onSettingsClick();

        void onEffectClick();
    }
}
