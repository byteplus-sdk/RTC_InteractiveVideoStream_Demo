/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.ss.bytertc.engine.UserInfo;

public class UserJoinedBroadcast {
    public UserInfo userInfo;

    public UserJoinedBroadcast(UserInfo userInfo) {
        this.userInfo = userInfo;
    }
}
