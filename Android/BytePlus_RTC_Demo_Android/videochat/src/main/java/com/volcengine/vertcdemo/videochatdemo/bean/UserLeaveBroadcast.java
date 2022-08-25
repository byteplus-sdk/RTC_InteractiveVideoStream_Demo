/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

public class UserLeaveBroadcast {
   public String uid;
    public int reason;

    public UserLeaveBroadcast(String uid,int reason) {
        this.uid = uid;
        this.reason = reason;
    }
}
