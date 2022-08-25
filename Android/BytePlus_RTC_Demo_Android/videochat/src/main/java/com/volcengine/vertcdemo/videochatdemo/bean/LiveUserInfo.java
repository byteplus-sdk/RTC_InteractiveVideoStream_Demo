/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.annotation.CameraStatus;
import com.volcengine.vertcdemo.core.annotation.MicStatus;
import com.volcengine.vertcdemo.core.annotation.RoleType;
import com.volcengine.vertcdemo.core.annotation.UserStatus;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;

public class LiveUserInfo implements RTMBizResponse {

    @SerializedName("room_id")
    public String roomId;
    @SerializedName("user_id")
    public String userId;
    @SerializedName("user_name")
    public String userName;
    @SerializedName("user_role")
    @RoleType
    public int role;

    /**
     * status:
     * 1:其它
     * 2:主播连麦邀请中
     * 3:主播连麦互动中
     * 4:观众连麦邀请中
     * 5:观众连麦互动中
     */
    @SerializedName("status")
    @UserStatus
    public int status;
    @MicStatus
    @SerializedName("mic")
    public Integer micStatus;
    @CameraStatus
    @SerializedName("camera")
    public Integer cameraStatus;
    @SerializedName("width")
    public int width;
    @SerializedName("height")
    public int height;
//    public boolean mic = micStatus == 1;
//    public boolean camera = cameraStatus == 1;

    public boolean isMicOn() {
        return micStatus == MicStatus.ON;
    }

    public boolean isCameraOn() {
        return cameraStatus == CameraStatus.ON;
    }

    @Override
    public String toString() {
        return "LiveUserInfo{" +
                "roomId='" + roomId + '\'' +
                ", userId='" + userId + '\'' +
                ", userName='" + userName + '\'' +
                ", role=" + role +
                ", status=" + status +
                ", micStatus=" + micStatus +
                ", cameraStatus=" + cameraStatus +
                ", width='" + width + '\'' +
                ", height='" + height + '\'' +
                '}';
    }

    public LiveUserInfo getDeepCopy() {
        LiveUserInfo userInfo = new LiveUserInfo();
        userInfo.userId = userId;
        userInfo.userName = userName;
        userInfo.roomId = roomId;
        userInfo.cameraStatus = cameraStatus;
        userInfo.micStatus = micStatus;
        userInfo.role = role;
        userInfo.status = status;
        userInfo.width = width;
        userInfo.height = height;
        return userInfo;
    }
}
