// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

import java.util.List;

public class ReplyAnchorsEvent extends VideoChatResponse {
    @SerializedName("interact_info_list")
    public List<InteractInfo> interactInfoList;

    @Override
    public String toString() {
        return "ReplyAnchorsEvent{" +
                "interactInfoList=" + interactInfoList +
                '}';
    }
}
