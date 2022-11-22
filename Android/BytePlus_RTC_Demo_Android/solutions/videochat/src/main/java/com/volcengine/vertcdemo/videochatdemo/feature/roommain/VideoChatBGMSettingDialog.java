/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

public class VideoChatBGMSettingDialog extends BaseDialog {
    private TextView mBGMVolumeProgress;
    private TextView mUserVolumeProgress;
    private Switch mBGMSwitch;
    private TouchSeekBar mBGMVolumeSeekBar;
    private SeekBar mUserVolumeSeekBar;
    private View mBGMLayout;
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
        setContentView(R.layout.dialog_video_chat_demo_bgm_setting);
        super.onCreate(savedInstanceState);
        initView();
    }

    @SuppressLint("ClickableViewAccessibility")
    private void initView() {
        mBGMSwitch = findViewById(R.id.bgm_switch_switch);
        mBGMLayout = findViewById(R.id.bgm_bgm_volume_layout);
        mBGMVolumeProgress = findViewById(R.id.bgm_bgm_volume_progress);
        mUserVolumeProgress = findViewById(R.id.bgm_user_volume_progress);
        mBGMVolumeSeekBar = findViewById(R.id.bgm_bgm_volume_seekbar);
        mUserVolumeSeekBar = findViewById(R.id.bgm_user_volume_seekbar);
        mBGMVolumeSeekBar.setMax(100);
        mUserVolumeSeekBar.setMax(100);
        mBGMVolumeProgress.setText(String.valueOf(mBGMVolume));
        mUserVolumeProgress.setText(String.valueOf(mUserVolume));

        onBGMSwitchChanged(mBGMStatus);
        onBGMVolumeProgressChanged(mBGMVolume);
        onUserVolumeProgressChanged(mUserVolume);

        mBGMSwitch.setOnCheckedChangeListener((v, checked) -> onBGMSwitchChanged(checked));
        mBGMVolumeSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
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
        mUserVolumeSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
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
        mBGMSwitch.setChecked(isChecked);
        mBGMLayout.setAlpha(isChecked ? 1 : 0.5F);
        mBGMVolumeSeekBar.setTouchAble(isChecked);
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
        mBGMVolumeProgress.setText(String.valueOf(progress));
        mBGMVolumeSeekBar.setProgress(progress);
        VideoChatDataManager.ins().setBGMVolume(progress);
        VideoChatRTCManager.ins().adjustBGMVolume(progress);
    }

    private void onUserVolumeProgressChanged(int progress) {
        mUserVolume = progress;
        mUserVolumeProgress.setText(String.valueOf(progress));
        mUserVolumeSeekBar.setProgress(progress);
        VideoChatDataManager.ins().setUserVolume(progress);
        VideoChatRTCManager.ins().adjustUserVolume(progress);
    }
}
