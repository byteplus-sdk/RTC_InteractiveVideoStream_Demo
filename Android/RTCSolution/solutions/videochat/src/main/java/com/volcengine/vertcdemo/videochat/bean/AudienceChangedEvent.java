// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class AudienceChangedEvent implements RTSBizInform {

    public boolean isJoin;
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;
    @SerializedName("audience_count")
    public int audienceCount;

    @Override
    public String toString() {
        return "AudienceChangedEvent{" +
                "userInfo=" + userInfo +
                ", audienceCount=" + audienceCount +
                '}';
    }
}
