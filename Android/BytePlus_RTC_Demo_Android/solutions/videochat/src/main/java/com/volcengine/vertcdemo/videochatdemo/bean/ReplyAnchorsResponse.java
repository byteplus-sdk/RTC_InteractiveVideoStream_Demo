/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;

import java.util.List;

public class ReplyAnchorsResponse implements RTMBizResponse {
    @SerializedName("interact_info_list")
    public List<InteractInfo> interactInfoList;

    @Override
    public String toString() {
        return "ReplyAnchorsResponse{" +
                "interactInfoList=" + interactInfoList +
                '}';
    }
}
