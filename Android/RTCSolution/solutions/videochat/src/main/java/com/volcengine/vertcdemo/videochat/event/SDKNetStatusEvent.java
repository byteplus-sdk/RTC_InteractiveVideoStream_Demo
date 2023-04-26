// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.event;

/**
 * SDK 网络质量状态回调事件
 */
public class SDKNetStatusEvent {
    public String uid; // 用户id
    public int networkQuality; // 网络质量

    public SDKNetStatusEvent(String uid, int networkQuality) {
        this.uid = uid;
        this.networkQuality = networkQuality;
    }
}
