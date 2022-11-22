/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;

public class NewAnchorJoinBroadcast {
    @SerializedName("room_id")
    public String roomId;//当前房间，不是新主播房间
    @SerializedName("user_id")
    public String userId;//新主播user_id
    @SerializedName("user_name")
    public String userName;//新主播user_name
    @SerializedName("mic")
    @VCUserInfo.MicStatus
    public int mic;
    @SerializedName("camera")
    @VCUserInfo.CameraStatus
    public int camera;

    @Override
    public String toString() {
        return "NewAnchorJoinBroadcast{" +
                "roomId='" + roomId + '\'' +
                ", userId='" + userId + '\'' +
                ", userName='" + userName + '\'' +
                '}';
    }
}
