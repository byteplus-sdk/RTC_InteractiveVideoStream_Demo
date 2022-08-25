/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizInform;

public class InviteAnchorReplyBroadcast implements RTMBizInform {
    @SerializedName("to_room_id")
    public String toRoomId;
    @SerializedName("to_user_id")
    public String toUserId;
    @SerializedName("to_user_name")
    public String toUserName;
    @SerializedName("interact_info")
    public InteractInfo interactInfo;
    @SerializedName("reply")
    public int reply;

    @Override
    public String toString() {
        return "InviteAnchorReplyBroadcast{" +
                "toRoomId='" + toRoomId + '\'' +
                ", toUserId='" + toUserId + '\'' +
                ", toUserName='" + toUserName + '\'' +
                ", interactInfo=" + interactInfo +
                ", reply=" + reply +
                '}';
    }
}
