// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.widget.SeekBar;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.DialogVideoChatBgmSettingBinding;

/**
 * 视频互动背景音乐管理对话框
 */
public class VideoChatBGMSettingDialog extends BaseDialog {
    
    private DialogVideoChatBgmSettingBinding mViewBinding;

    private boolean mBGMStatus;
    private int mBGMVolume = 0;
    private int mUserVolume = 0;

    public VideoChatBGMSettingDialog(@NonNull Context context) {
        super(context);
    }

    public VideoChatBGMSettingDialog(@NonNull Context context, int themeResId) {
        super(context, themeResId);
    }

    protected VideoChatBGMSettingDialog(@NonNull Context context, boolean cancelable, @Nullable OnCancelListener cancelListener) {
        super(context, cancelable, cancelListener);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mViewBinding = DialogVideoChatBgmSettingBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());
        
        super.onCreate(savedInstanceState);
        initView();
    }

    @SuppressLint("ClickableViewAccessibility")
    private void initView() {
        mViewBinding.bgmBgmVolumeSeekbar.setMax(100);
        mViewBinding.bgmUserVolumeSeekbar.setMax(100);
        mViewBinding.bgmBgmVolumeProgress.setText(String.valueOf(mBGMVolume));
        mViewBinding.bgmUserVolumeProgress.setText(String.valueOf(mUserVolume));

        onBGMSwitchChanged(mBGMStatus);
        onBGMVolumeProgressChanged(mBGMVolume);
        onUserVolumeProgressChanged(mUserVolume);

        mViewBinding.bgmSwitchSwitch.setOnCheckedChangeListener((v, checked) -> onBGMSwitchChanged(checked));
        mViewBinding.bgmBgmVolumeSeekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    onBGMVolumeProgressChanged(progress);
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        mViewBinding.bgmUserVolumeSeekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    onUserVolumeProgressChanged(progress);
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    public void setData(boolean bgmSwitch, int bgmVolume, int userVolume) {
        mBGMStatus = bgmSwitch;
        mBGMVolume = bgmVolume;
        mUserVolume = userVolume;
    }

    private void onBGMSwitchChanged(boolean isChecked) {
        mBGMStatus = isChecked;
        mViewBinding.bgmSwitchSwitch.setChecked(isChecked);
        mViewBinding.bgmBgmVolumeLayout.setAlpha(isChecked ? 1 : 0.5F);
        mViewBinding.bgmBgmVolumeSeekbar.setTouchAble(isChecked);
        VideoChatDataManager.ins().setBGMOpening(isChecked);

        if (isChecked) {
            if (VideoChatDataManager.ins().getIsFirstSetBGMSwitch()) {
                VideoChatRTCManager.ins().startAudioMixing(true);
            } else {
                VideoChatRTCManager.ins().resumeAudioMixing();
            }
            VideoChatDataManager.ins().setIsFirstSetBGMSwitch(false);
        } else {
            if (VideoChatDataManager.ins().getIsFirstSetBGMSwitch()) {
                VideoChatRTCManager.ins().startAudioMixing(false);
            } else {
                VideoChatRTCManager.ins().pauseAudioMixing();
            }
        }
    }

    private void onBGMVolumeProgressChanged(int progress) {
        mBGMVolume = progress;
        mViewBinding.bgmBgmVolumeProgress.setText(String.valueOf(progress));
        mViewBinding.bgmBgmVolumeSeekbar.setProgress(progress);
        VideoChatDataManager.ins().setBGMVolume(progress);
        VideoChatRTCManager.ins().adjustBGMVolume(progress);
    }

    private void onUserVolumeProgressChanged(int progress) {
        mUserVolume = progress;
        mViewBinding.bgmUserVolumeProgress.setText(String.valueOf(progress));
        mViewBinding.bgmUserVolumeSeekbar.setProgress(progress);
        VideoChatDataManager.ins().setUserVolume(progress);
        VideoChatRTCManager.ins().adjustUserVolume(progress);
    }
}
