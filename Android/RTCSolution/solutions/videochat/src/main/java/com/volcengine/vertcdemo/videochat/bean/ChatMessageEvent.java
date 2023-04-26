// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class ChatMessageEvent implements RTSBizInform {
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;
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
