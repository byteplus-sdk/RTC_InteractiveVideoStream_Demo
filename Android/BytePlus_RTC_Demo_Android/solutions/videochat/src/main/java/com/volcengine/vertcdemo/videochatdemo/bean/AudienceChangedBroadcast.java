/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizInform;

public class AudienceChangedBroadcast implements RTSBizInform {

    public boolean isJoin;
    @SerializedName("user_info")
    public VCUserInfo userInfo;
    @SerializedName("audience_count")
    public int audienceCount;

    @Override
    public String toString() {
        return "AudienceChangedBroadcast{" +
                "userInfo=" + userInfo +
                ", audienceCount=" + audienceCount +
                '}';
    }
}
