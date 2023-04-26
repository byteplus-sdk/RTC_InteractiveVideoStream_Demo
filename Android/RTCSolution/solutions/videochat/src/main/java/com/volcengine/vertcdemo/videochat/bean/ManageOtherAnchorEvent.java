// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class ManageOtherAnchorEvent implements RTSBizInform {
    @SerializedName("room_id")
    public String roomId;
    @SerializedName("other_anchor_user_id")
    public String otherAnchorUid;
    @SerializedName("type")
    public int type;

    @Override
    public String toString() {
        return "ManageOtherAnchorEvent{" +
                "roomId='" + roomId + '\'' +
                ", otherAnchorUid='" + otherAnchorUid + '\'' +
                ", type=" + type +
                '}';
    }
}
