/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizInform;

public class AudienceApplyBroadcast implements RTMBizInform {

    public boolean hasNewApply;
    @SerializedName("user_info")
    public VCUserInfo userInfo;
    @SerializedName("seat_id")
    public int seatId;

    @Override
    public String toString() {
        return "AudienceApplyBroadcast{" +
                "userInfo=" + userInfo +
                ", seatId=" + seatId +
                '}';
    }
}
