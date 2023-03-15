/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;
import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizInform;

public class InviteAnchorBroadcast implements RTSBizInform {
    @SerializedName("from_room_id")
    public String fromRoomId;
    @SerializedName("from_user_id")
    public String fromUserId;
    @SerializedName("from_user_name")
    public String fromUserName;

    @Override
    public String toString() {
        return "InviteAnchorBroadcast{" +
                "fromRoomId='" + fromRoomId + '\'' +
                ", fromUserId='" + fromUserId + '\'' +
                ", fromUserName='" + fromUserName + '\'' +
                '}';
    }
}
