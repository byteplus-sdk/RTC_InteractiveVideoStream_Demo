// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;

public class InteractResultEvent implements RTSBizInform {

    @SerializedName("reply")
    @VideoChatDataManager.ReplyType
    public int reply;
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;

    @Override
    public String toString() {
        return "InteractResultEvent{" +
                "reply=" + reply +
                ", userInfo=" + userInfo +
                '}';
    }
}
