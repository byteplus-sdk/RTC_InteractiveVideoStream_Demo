// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class MediaChangedEvent implements RTSBizInform {

    @SerializedName("mic")
    @VideoChatUserInfo.MicStatus
    public int mic;
    @SerializedName("camera")
    @VideoChatUserInfo.CameraStatus
    public int camera;
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;

    @Override
    public String toString() {
        return "MediaChangedEvent{" +
                "mic=" + mic +
                ", camera=" + camera +
                ", userInfo=" + userInfo +
                '}';
    }
}
