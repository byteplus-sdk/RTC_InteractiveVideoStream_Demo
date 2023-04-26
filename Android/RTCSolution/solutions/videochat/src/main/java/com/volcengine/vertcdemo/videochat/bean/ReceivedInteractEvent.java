// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class ReceivedInteractEvent implements RTSBizInform {

    @SerializedName("host_info")
    public VideoChatUserInfo userInfo;
    @SerializedName("seat_id")
    public int seatId;

    @Override
    public String toString() {
        return "ReceivedInteractEvent{" +
                "userInfo=" + userInfo +
                ", seatId=" + seatId +
                '}';
    }
}
