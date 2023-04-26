// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.ss.bytertc.engine.UserInfo;

public class UserJoinedEvent {
    public UserInfo userInfo;

    public UserJoinedEvent(UserInfo userInfo) {
        this.userInfo = userInfo;
    }

    @Override
    public String toString() {
        return "UserJoinedEvent{" +
                "userInfo=" + userInfo +
                '}';
    }
}
