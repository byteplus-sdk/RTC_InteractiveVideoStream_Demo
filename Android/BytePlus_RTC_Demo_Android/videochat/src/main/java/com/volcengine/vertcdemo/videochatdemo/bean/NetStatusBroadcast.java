/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

public class NetStatusBroadcast {
    public String uid;
    public int txQuality;
    public int rxQuality;

    public NetStatusBroadcast(String uid, int txQuality, int rxQuality) {
        this.uid = uid;
        this.txQuality = txQuality;
        this.rxQuality = rxQuality;
    }
}
