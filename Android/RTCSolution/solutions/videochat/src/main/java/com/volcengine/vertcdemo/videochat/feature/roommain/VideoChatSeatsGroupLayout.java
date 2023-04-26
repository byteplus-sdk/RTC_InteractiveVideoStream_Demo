// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain;

import static com.volcengine.vertcdemo.videochat.core.VideoChatDataManager.SEAT_STATUS_LOCKED;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;

import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.VideoChatSeatInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.databinding.LayoutVideoChatSeatGroupBinding;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * 多个座位集合控件
 */
public class VideoChatSeatsGroupLayout extends ConstraintLayout {

    private final List<VideoChatSeatLayout> mSeatInfoList = new ArrayList<>();

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
        View view = View.inflate(getContext(), R.layout.layout_video_chat_seat_group, this);
        LayoutVideoChatSeatGroupBinding viewBinding = LayoutVideoChatSeatGroupBinding.bind(view);

        mSeatInfoList.add(viewBinding.videoGroupSeat1);
        mSeatInfoList.add(viewBinding.videoGroupSeat2);
        mSeatInfoList.add(viewBinding.videoGroupSeat3);
        mSeatInfoList.add(viewBinding.videoGroupSeat4);
        mSeatInfoList.add(viewBinding.videoGroupSeat5);
        mSeatInfoList.add(viewBinding.videoGroupSeat6);

        for (int i = 0; i < mSeatInfoList.size(); i++) {
            VideoChatSeatLayout layout = mSeatInfoList.get(i);
            layout.setIndex(i);
            layout.bind(null);
        }
    }

    public void bindHostInfo(VideoChatUserInfo userInfo) {
        VideoChatSeatInfo info = new VideoChatSeatInfo();
        info.userInfo = userInfo;
        info.status = VideoChatDataManager.SEAT_STATUS_UNLOCKED;
        mSeatInfoList.get(0).bind(info);
    }

    public void bindSeatInfo(Map<Integer, VideoChatSeatInfo> map) {
        if (map == null || map.isEmpty()) {
            return;
        }
        for (Map.Entry<Integer, VideoChatSeatInfo> seatInfoEntry : map.entrySet()) {
            bindSeatInfo(seatInfoEntry.getKey(), seatInfoEntry.getValue());
        }
    }

    public void bindSeatInfo(int seatId, VideoChatSeatInfo seatInfo) {
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

    public void setSeatClick(IAction<VideoChatSeatInfo> action) {
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