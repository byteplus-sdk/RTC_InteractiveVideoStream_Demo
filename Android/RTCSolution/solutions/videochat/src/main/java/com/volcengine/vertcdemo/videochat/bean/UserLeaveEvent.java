// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

public class UserLeaveEvent {
   public String uid;
    public int reason;

    public UserLeaveEvent(String uid, int reason) {
        this.uid = uid;
        this.reason = reason;
    }

    @Override
    public String toString() {
        return "UserLeaveEvent{" +
                "uid='" + uid + '\'' +
                ", reason=" + reason +
                '}';
    }
}
