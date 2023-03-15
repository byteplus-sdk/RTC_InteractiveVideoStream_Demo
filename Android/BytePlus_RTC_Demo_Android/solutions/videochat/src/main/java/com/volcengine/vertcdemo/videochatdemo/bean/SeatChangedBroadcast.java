/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizInform;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;

public class SeatChangedBroadcast implements RTSBizInform {

    @SerializedName("seat_id")
    public int seatId;
    @SerializedName("type")
    @VideoChatDataManager.SeatStatus
    public int type;

    @Override
    public String toString() {
        return "SeatChangedEvent{" +
                "seatId=" + seatId +
                ", type=" + type +
                '}';
    }
}
