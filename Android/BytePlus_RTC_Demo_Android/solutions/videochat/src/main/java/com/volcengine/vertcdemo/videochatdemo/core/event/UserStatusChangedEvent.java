/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.core.event;


import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;

public class UserStatusChangedEvent {

    public VCUserInfo userInfo;
    @VCUserInfo.UserStatus
    public int status;

    public UserStatusChangedEvent(VCUserInfo userInfo, @VCUserInfo.UserStatus int status) {
        this.userInfo = userInfo;
        this.status = status;
    }
}
