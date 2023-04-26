// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.createroom;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;

import androidx.annotation.NonNull;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.databinding.LayoutVideoChatCreateSettingDialogBinding;

import java.util.Locale;

public class VideoChatCreateSettingDialog extends BaseDialog implements
        SeekBar.OnSeekBarChangeListener {

    private LayoutVideoChatCreateSettingDialogBinding mViewBinding;

    private final boolean isInLive; // 是不是正在直播中，用来区分是创建直播页面还是直播页面
    private String mRoomId;

    private int minBitRate = 800;
    private int maxBitRate = 1900;
    private int currentBitRate = 0;

    public VideoChatCreateSettingDialog(@NonNull Context context, boolean isInLive, String roomId) {
        super(context);
        this.isInLive = isInLive;
        this.mRoomId = roomId;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mViewBinding = LayoutVideoChatCreateSettingDialogBinding.inflate(getLayoutInflater());
        setContentView(mViewBinding.getRoot());

        super.onCreate(savedInstanceState);
        initUI();
    }

    private void initUI() {
        mViewBinding.videoSettingLayout.setVisibility(View.GONE);
        int frCheckId;
        if (VideoChatRTCManager.ins().getFrameRate() == 15) {
            frCheckId = R.id.frame_rate_15;
        } else {
            frCheckId = R.id.frame_rate_20;
        }
        mViewBinding.frameRateRg.check(frCheckId);
        mViewBinding.frameRateRg.setOnCheckedChangeListener((group, checkedId) -> {
            if (checkedId == R.id.frame_rate_15) {
                VideoChatRTCManager.ins().setFrameRate(15);
            } else if (checkedId == R.id.frame_rate_20) {
                VideoChatRTCManager.ins().setFrameRate(20);
            }
        });

        // 根据当前视频分辨率的宽，修改UI选中
        int rCheckedId;
        if (VideoChatRTCManager.ins().getFrameWidth() == 480) {
            rCheckedId = R.id.resolution_480;
        } else if (VideoChatRTCManager.ins().getFrameWidth() == 544) {
            rCheckedId = R.id.resolution_540;
        } else if (VideoChatRTCManager.ins().getFrameWidth() == 1088) {
            rCheckedId = R.id.resolution_1080;
        } else {
            rCheckedId = R.id.resolution_720;
        }
        mViewBinding.resolutionRg.check(rCheckedId);
        mViewBinding.resolutionRg.setOnCheckedChangeListener((group, checkedId) -> {
            if (checkedId == R.id.resolution_480) {
                minBitRate = 320;
                maxBitRate = 1266;
                VideoChatRTCManager.ins().setResolution(480, 864);
            } else if (checkedId == R.id.resolution_540) {
                minBitRate = 500;
                maxBitRate = 1520;
                VideoChatRTCManager.ins().setResolution(544, 960);
            } else if (checkedId == R.id.resolution_720) {
                minBitRate = 800;
                maxBitRate = 1900;
                VideoChatRTCManager.ins().setResolution(720, 1280);
            } else if (checkedId == R.id.resolution_1080) {
                minBitRate = 1000;
                maxBitRate = 3800;
                VideoChatRTCManager.ins().setResolution(1088, 1920);
            }
            updateBitRate();
        });

        mViewBinding.bitRateSeekbar.setOnSeekBarChangeListener(this);

        if (isInLive) {
            mViewBinding.videoSettingLayout.setVisibility(View.VISIBLE);
        } else {
            mViewBinding.videoSettingLayout.setVisibility(View.GONE);
        }

        currentBitRate = VideoChatRTCManager.ins().getBitrate();
        updateBitRate();
    }

    /**
     * 根据当前码率区间，判断正确的码率值，并修改UI
     */
    private void updateBitRate() {
        if (currentBitRate < minBitRate) {
            currentBitRate = minBitRate;
        } else if (currentBitRate > maxBitRate) {
            currentBitRate = maxBitRate;
        }

        float progress = 100 * (currentBitRate - minBitRate) * 1f / (maxBitRate - minBitRate);
        mViewBinding.bitRateSeekbar.setProgress((int) progress);
        VideoChatRTCManager.ins().setBitrate(currentBitRate);
        mViewBinding.bitRateTv.setText(String.format(Locale.ENGLISH, "%d kbps", currentBitRate));
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if (fromUser) {
            currentBitRate = (int) (minBitRate + (progress / 100f) * (maxBitRate - minBitRate));
            mViewBinding.bitRateTv.setText(String.format(Locale.ENGLISH, "%d kbps", currentBitRate));
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }
}
