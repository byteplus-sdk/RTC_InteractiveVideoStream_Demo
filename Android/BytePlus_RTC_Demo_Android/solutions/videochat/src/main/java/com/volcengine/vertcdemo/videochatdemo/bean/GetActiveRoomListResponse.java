/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;

import java.util.List;

public class GetActiveRoomListResponse implements RTMBizResponse {

    @SerializedName("room_list")
    public List<VCRoomInfo> roomList;

    @Override
    public String toString() {
        return "GetActiveRoomListResponse{" +
                "roomList=" + roomList +
                '}';
    }
}
