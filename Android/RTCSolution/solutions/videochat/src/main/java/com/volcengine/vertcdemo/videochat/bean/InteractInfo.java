// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

public class InteractInfo {

    @SerializedName("room_id")
    public String roomId;//连麦主播roomID
    @SerializedName("user_id")
    public String userId;  //连麦主播userID
    @SerializedName("user_name")
    public String userName;
    @SerializedName("user_role")
    public int userRole;
    @SerializedName("status")
    public int status;//1:普通, 2:互动中, 3:申请中, 4:邀请中
    @SerializedName("mic")
    @VideoChatUserInfo.MicStatus
    public int mic;//0:关闭, 1:开启
    @VideoChatUserInfo.CameraStatus
    @SerializedName("camera")
    public int camera;//0:关闭, 1:开启
    @SerializedName("token")
    public String token; //你要推流房间需要的token 注意：这里使用你自己的user_id和要连麦主播的room_id生成的token。

    @Override
    public String toString() {
        return "InteractInfo{" +
                "roomId='" + roomId + '\'' +
                ", userId='" + userId + '\'' +
                ", userName='" + userName + '\'' +
                ", userRole=" + userRole +
                ", status=" + status +
                ", mic=" + mic +
                ", camera=" + camera +
                ", token='" + token + '\'' +
                '}';
    }
}
