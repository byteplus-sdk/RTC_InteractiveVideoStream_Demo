// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

import java.util.List;

public class GetAudienceEvent extends VideoChatResponse {
    @SerializedName("audience_list")
    public List<VideoChatUserInfo> audienceList;

    @Override
    public String toString() {
        return "GetAudienceEvent{" +
                "audienceList=" + audienceList +
                '}';
    }
}
