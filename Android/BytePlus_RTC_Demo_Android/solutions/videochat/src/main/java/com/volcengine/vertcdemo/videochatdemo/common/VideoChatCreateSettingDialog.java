/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.common;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioGroup;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;

import com.volcengine.vertcdemo.common.BaseDialog;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

import java.util.Locale;

public class VideoChatCreateSettingDialog extends BaseDialog implements
        SeekBar.OnSeekBarChangeListener {

    private ViewGroup mVideoSettingLayout;
    private RadioGroup mFrameRateLayout;
    private RadioGroup mResolutionLayout;
    private SeekBar mBitRateSeekBar;
    private TextView mBitRateTv;
    private boolean isInLive;
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
        setContentView(R.layout.layout_video_chat_create_setting_dialog);
        super.onCreate(savedInstanceState);
        initUI();
    }

    private void initUI() {
        mVideoSettingLayout = findViewById(R.id.video_setting_layout);
        mVideoSettingLayout.setVisibility(View.GONE);
        mFrameRateLayout = findViewById(R.id.frame_rate_rg);
        if (VideoChatRTCManager.ins().getFrameRate() == 20){
            mFrameRateLayout.check(R.id.frame_rate_20);
        }
        mFrameRateLayout.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (checkedId == R.id.frame_rate_15) {
                    VideoChatRTCManager.ins().setFrameRate(15);
                } else if (checkedId == R.id.frame_rate_20) {
                    VideoChatRTCManager.ins().setFrameRate(20);
                }
            }
        });
        mResolutionLayout = findViewById(R.id.resolution_rg);
        switch (VideoChatRTCManager.ins().getFrameWidth()){
            case 480:
                mResolutionLayout.check(R.id.resolution_480);
                break;
            case 544:
                mResolutionLayout.check(R.id.resolution_540);
                break;
            case 1088:
                mResolutionLayout.check(R.id.resolution_1080);
                break;
            default:
                mResolutionLayout.check(R.id.resolution_720);
                break;
        }
        mResolutionLayout.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
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
            }
        });
        mBitRateSeekBar = findViewById(R.id.bit_rate_seekbar);
        mBitRateSeekBar.setOnSeekBarChangeListener(this);
        mBitRateTv = findViewById(R.id.bit_rate_tv);

        if (isInLive) {
            mVideoSettingLayout.setVisibility(View.VISIBLE);
        } else {
            mVideoSettingLayout.setVisibility(View.GONE);
        }

        currentBitRate = VideoChatRTCManager.ins().getBitrate();
        updateBitRate();
    }

    private void updateBitRate() {
        if (currentBitRate < minBitRate) {
            currentBitRate = minBitRate;
        } else if (currentBitRate > maxBitRate) {
            currentBitRate = maxBitRate;
        }

        float progress = 100 * (currentBitRate - minBitRate) * 1f / (maxBitRate - minBitRate);
        mBitRateSeekBar.setProgress((int) progress);
        VideoChatRTCManager.ins().setBitrate(currentBitRate);
        mBitRateTv.setText(String.format(Locale.ENGLISH, "%d kbps", currentBitRate));
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if (fromUser) {
            currentBitRate = (int) (minBitRate + (progress / 100f) * (maxBitRate - minBitRate));
            mBitRateTv.setText(String.format(Locale.ENGLISH, "%d kbps", currentBitRate));
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }

}
