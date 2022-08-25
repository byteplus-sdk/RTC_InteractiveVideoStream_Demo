/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.SEAT_STATUS_LOCKED;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.VCSeatInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class VideoChatSeatsGroupLayout extends FrameLayout {

    private final List<VideoChatSeatLayout> mSeatInfoList = new LinkedList<>();

    public VideoChatSeatsGroupLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public VideoChatSeatsGroupLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public VideoChatSeatsGroupLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_video_chat_demo_seat_group, this, true);
        mSeatInfoList.add(findViewById(R.id.video_group_seat_1));
        mSeatInfoList.add(findViewById(R.id.video_group_seat_2));
        mSeatInfoList.add(findViewById(R.id.video_group_seat_3));
        mSeatInfoList.add(findViewById(R.id.video_group_seat_4));
        mSeatInfoList.add(findViewById(R.id.video_group_seat_5));
        mSeatInfoList.add(findViewById(R.id.video_group_seat_6));
        for (int i = 0; i < mSeatInfoList.size(); i++) {
            VideoChatSeatLayout layout = mSeatInfoList.get(i);
            layout.setIndex(i);
            layout.bind(null);
        }
    }

    public void bindHostInfo(VCUserInfo userInfo) {
        VCSeatInfo info = new VCSeatInfo();
        info.userInfo = userInfo;
        info.status = VideoChatDataManager.SEAT_STATUS_UNLOCKED;
        mSeatInfoList.get(0).bind(info);
    }

    public void bindSeatInfo(Map<Integer, VCSeatInfo> map) {
        if (map == null || map.isEmpty()) {
            return;
        }
        for (Map.Entry<Integer, VCSeatInfo> seatInfoEntry : map.entrySet()) {
            bindSeatInfo(seatInfoEntry.getKey(), seatInfoEntry.getValue());
        }
    }

    public void bindSeatInfo(int seatId, VCSeatInfo seatInfo) {
        for (VideoChatSeatLayout layout : mSeatInfoList) {
            if (layout.getIndex() == seatId) {
                layout.bind(seatInfo);
                break;
            }
        }
    }

    public void updateUserMediaStatus(String userId, boolean micOn, boolean cameraOn) {
        for (VideoChatSeatLayout layout : mSeatInfoList) {
            layout.updateMicStatus(userId, micOn, cameraOn);
        }
    }

    public void onUserSpeaker(String userId, int volume) {
        for (VideoChatSeatLayout layout : mSeatInfoList) {
            layout.updateVolumeStatus(userId, volume);
        }
    }

    public void setSeatClick(IAction<VCSeatInfo> action) {
        for (VideoChatSeatLayout layout : mSeatInfoList) {
            layout.setSeatClick(action);
        }
    }

    public void updateSeatStatus(int seatId, @VideoChatDataManager.SeatStatus int seatStatus) {
        for (VideoChatSeatLayout layout : mSeatInfoList) {
            if (layout.getIndex() == seatId) {
                layout.updateLockedStatus(seatStatus == SEAT_STATUS_LOCKED);
                break;
            }
        }
    }
}