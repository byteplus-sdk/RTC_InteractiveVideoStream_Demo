/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizInform;

public class MediaOperateBroadcast implements RTMBizInform {

    @SerializedName("mic")
    @VCUserInfo.MicStatus
    public int mic;
    @SerializedName("camera")
    @VCUserInfo.CameraStatus
    public int camera;

    @Override
    public String toString() {
        return "MediaOperateBroadcast{" +
                "mic=" + mic +
                ", camera=" + camera +
                '}';
    }
}
