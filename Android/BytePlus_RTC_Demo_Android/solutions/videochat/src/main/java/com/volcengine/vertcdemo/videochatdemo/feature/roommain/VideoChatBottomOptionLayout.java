/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;


import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_ROLE_HOST;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;

public class VideoChatBottomOptionLayout extends LinearLayout {

    private TextView mInputTv;
    private FrameLayout mInteractFl;
    private ImageView mInteractBtn;
    private ImageView mInteractIndicator;
    private ImageView mPkBtn;
    private ImageView mSettingBtnIv;
    private ImageView mEffectBtnIv;
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
        LayoutInflater.from(getContext()).inflate(R.layout.layout_video_chat_main_bottom_option, this, true);
        mInputTv = findViewById(R.id.voice_chat_demo_main_option_input_btn);
        mPkBtn = findViewById(R.id.voice_chat_demo_main_option_pk_btn);
        mInteractFl = findViewById(R.id.voice_chat_demo_main_option_interact_fl);
        mInteractIndicator = findViewById(R.id.ic_interact_indicator);
        mInteractBtn = findViewById(R.id.voice_chat_demo_main_option_interact_btn);
        mSettingBtnIv = findViewById(R.id.voice_chat_demo_main_option_setting);
        mEffectBtnIv = findViewById(R.id.voice_chat_demo_main_option_effect);

        mInputTv.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onInputClick();
            }
        });
        mPkBtn.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onPkClick();
            }
        });
        mInteractBtn.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onInteractClick();
            }
        });
        mSettingBtnIv.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onSettingsClick();
            }
        });
        mEffectBtnIv.setOnClickListener((v) -> {
            if (mIBottomOptions != null) {
                mIBottomOptions.onEffectClick();
            }
        });
    }

    public void setOptionCallback(IBottomOptions callback) {
        mIBottomOptions = callback;
    }

    public void updateUIByRoleAndStatus(@VCRoomInfo.RoomStatus int roomStatus,
                                        @VCUserInfo.UserRole int userRole,
                                        @VCUserInfo.UserStatus int userStatus) {
        if (roomStatus == VCRoomInfo.ROOM_STATUS_LIVING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mPkBtn.setImageResource(R.drawable.voice_chat_demo_main_option_pk);
                mPkBtn.setVisibility(VISIBLE);
                mInteractFl.setVisibility(VISIBLE);
                mInteractBtn.setVisibility(VISIBLE);
                mSettingBtnIv.setVisibility(VISIBLE);
                mEffectBtnIv.setVisibility(VISIBLE);
            } else {//观众
                mPkBtn.setVisibility(GONE);
                mInteractFl.setVisibility(VISIBLE);
                mInteractBtn.setVisibility(VISIBLE);
                mSettingBtnIv.setVisibility(GONE);
                mEffectBtnIv.setVisibility(GONE);
            }
            return;
        }
        if (roomStatus == VCRoomInfo.ROOM_STATUS_PK_ING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mPkBtn.setVisibility(VISIBLE);
                mPkBtn.setImageResource(R.drawable.voice_chat_demo_main_option_cancel_pk);
                mInteractFl.setVisibility(VISIBLE);
                mInteractBtn.setVisibility(VISIBLE);
                mSettingBtnIv.setVisibility(VISIBLE);
                mEffectBtnIv.setVisibility(VISIBLE);
            } else {//观众
                mPkBtn.setVisibility(GONE);
                mInteractFl.setVisibility(GONE);
                mInteractBtn.setVisibility(GONE);
                mSettingBtnIv.setVisibility(GONE);
                mEffectBtnIv.setVisibility(GONE);
            }
            return;
        }
        if (roomStatus == VCRoomInfo.ROOM_STATUS_CHATTING) {
            if (userRole == USER_ROLE_HOST) {//主播
                mPkBtn.setVisibility(VISIBLE);
                mInteractFl.setVisibility(VISIBLE);
                mInteractBtn.setVisibility(VISIBLE);
                mSettingBtnIv.setVisibility(VISIBLE);
                mEffectBtnIv.setVisibility(VISIBLE);
            } else {//观众
                mPkBtn.setVisibility(GONE);
                mInteractFl.setVisibility(GONE);
                mInteractBtn.setVisibility(GONE);
                boolean isInteracting = userStatus == VCUserInfo.USER_STATUS_INTERACT;
                if (isInteracting) {
                    mSettingBtnIv.setVisibility(VISIBLE);
                    mEffectBtnIv.setVisibility(VISIBLE);
                } else {
                    mSettingBtnIv.setVisibility(GONE);
                    mEffectBtnIv.setVisibility(GONE);
                }
            }
        }
    }

    public void updateDotTip(boolean withDot) {
        mInteractIndicator.setVisibility(withDot ? VISIBLE : GONE);
    }

    public interface IBottomOptions {

        void onInputClick();

        void onPkClick();

        void onInteractClick();

        void onSettingsClick();

        void onEffectClick();
    }
}
