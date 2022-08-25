/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizInform;

public class MessageBroadcast implements RTMBizInform {
    @SerializedName("user_info")
    public VCUserInfo userInfo;
    @SerializedName("message")
    public String message;

    @Override
    public String toString() {
        return "ChatMessageEvent{" +
                "userInfo=" + userInfo +
                ", message='" + message + '\'' +
                '}';
    }
}
