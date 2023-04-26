// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.event;


import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;

public class UserStatusChangedEvent {

    public VideoChatUserInfo userInfo;
    @VideoChatUserInfo.UserStatus
    public int status;

    public UserStatusChangedEvent(VideoChatUserInfo userInfo, @VideoChatUserInfo.UserStatus int status) {
        this.userInfo = userInfo;
        this.status = status;
    }
}
