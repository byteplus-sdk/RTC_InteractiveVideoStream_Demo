/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizInform;

public class ManageOtherAnchorBroadcast implements RTSBizInform {
    @SerializedName("room_id")
    public String roomId;
    @SerializedName("other_anchor_user_id")
    public String otherAnchorUid;
    @SerializedName("type")
    public int type;

    @Override
    public String toString() {
        return "ManageOtherAnchorBroadcast{" +
                "roomId='" + roomId + '\'' +
                ", otherAnchorUid='" + otherAnchorUid + '\'' +
                ", type=" + type +
                '}';
    }
}
