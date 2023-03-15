/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizResponse;

public class ReplyResponse implements RTSBizResponse {

    @SerializedName("user_info")
    public VCUserInfo userInfo;

    @Override
    public String toString() {
        return "ReplyResponse{" +
                "userInfo=" + userInfo +
                '}';
    }
}
