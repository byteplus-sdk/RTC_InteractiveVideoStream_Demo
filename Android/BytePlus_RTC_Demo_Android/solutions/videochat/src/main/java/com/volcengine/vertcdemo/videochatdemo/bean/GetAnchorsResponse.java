/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizResponse;

import java.util.List;

public class GetAnchorsResponse implements RTSBizResponse {
    @SerializedName("anchor_list")
    public List<VCUserInfo> anchorList;

    @Override
    public String toString() {
        return "GetAnchorsResponse{" +
                "anchorList=" + anchorList +
                '}';
    }
}
