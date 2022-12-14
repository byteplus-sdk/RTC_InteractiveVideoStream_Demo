/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizInform;

public class CloseChatRoomBroadcast implements RTMBizInform {
    @SerializedName("room_id")
    public String roomId;

    @Override
    public String toString() {
        return "CloseChatRoomBroadcast{" +
                "roomId='" + roomId + '\'' +
                '}';
    }
}
