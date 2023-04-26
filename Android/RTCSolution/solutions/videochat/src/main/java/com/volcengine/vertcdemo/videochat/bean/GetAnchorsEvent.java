// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

import java.util.List;

public class GetAnchorsEvent extends VideoChatResponse {
    @SerializedName("anchor_list")
    public List<VideoChatUserInfo> anchorList;

    @Override
    public String toString() {
        return "GetAnchorsEvent{" +
                "anchorList=" + anchorList +
                '}';
    }
}
