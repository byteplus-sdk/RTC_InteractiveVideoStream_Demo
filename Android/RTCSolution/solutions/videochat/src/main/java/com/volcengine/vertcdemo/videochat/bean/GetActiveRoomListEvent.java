// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

import java.util.List;

public class GetActiveRoomListEvent extends VideoChatResponse {

    @SerializedName("room_list")
    public List<VideoChatRoomInfo> roomList;

    @Override
    public String toString() {
        return "GetActiveRoomListEvent{" +
                "roomList=" + roomList +
                '}';
    }
}
