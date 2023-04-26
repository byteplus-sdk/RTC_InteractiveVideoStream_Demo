// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

public class MediaOperateEvent implements RTSBizInform {

    @SerializedName("mic")
    @VideoChatUserInfo.MicStatus
    public int mic;
    @SerializedName("camera")
    @VideoChatUserInfo.CameraStatus
    public int camera;

    @Override
    public String toString() {
        return "MediaOperateEvent{" +
                "mic=" + mic +
                ", camera=" + camera +
                '}';
    }
}
