// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

public class CreateRoomEvent extends VideoChatResponse {

    @SerializedName("room_info")
    public VideoChatRoomInfo roomInfo;
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;
    @SerializedName("rtc_token")
    public String rtcToken;

    @Override
    public String toString() {
        return "CreateRoomEvent{" +
                "roomInfo=" + roomInfo +
                ", userInfo=" + userInfo +
                ", rtcToken='" + rtcToken + '\'' +
                '}';
    }
}