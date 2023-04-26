// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.annotation.CameraStatus;
import com.volcengine.vertcdemo.core.annotation.MicStatus;

public class AnchorInfo {
    @SerializedName("room_id")
    public String roomId;
    @SerializedName("user_id")
    public String userId;
    @SerializedName("user_name")
    public String userName;
    @SerializedName("user_role")
    public int userRole;
    @SerializedName("status")
    public int status;//1:普通, 2:互动中, 3:申请中, 4:邀请中
    @SerializedName("mic")
    @MicStatus
    public int mic;//0:关闭, 1:开启
    @SerializedName("camera")
    @CameraStatus
    public int camera;//0:关闭, 1:开启
    @SerializedName("audio_status_this_room")
    public int audioStatusThisRoom = 1;//0: mute 1:unmute

    @Override
    public String toString() {
        return "AnchorInfo{" +
                "roomId='" + roomId + '\'' +
                ", userId='" + userId + '\'' +
                ", userName='" + userName + '\'' +
                ", userRole=" + userRole +
                ", status=" + status +
                ", mic=" + mic +
                ", camera=" + camera +
                ", audioStatusThisRoom='" + audioStatusThisRoom + '\'' +
                '}';
    }
}
