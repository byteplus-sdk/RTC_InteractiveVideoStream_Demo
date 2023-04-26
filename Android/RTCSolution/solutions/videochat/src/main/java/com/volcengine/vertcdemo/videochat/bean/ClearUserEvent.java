// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class ClearUserEvent implements RTSBizInform {

    @SerializedName("room_id")
    public String roomId;
    @SerializedName("user_id")
    public String userId;

    @Override
    public String toString() {
        return "ClearUserEvent{" +
                "roomId='" + roomId + '\'' +
                ", userId='" + userId + '\'' +
                '}';
    }
}
