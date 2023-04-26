// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.core.eventbus;
/**
 * SDK reconnection into room event
 */
public class SDKReconnectToRoomEvent {

    public String roomId;

    public SDKReconnectToRoomEvent(String roomId) {
        this.roomId = roomId;
    }
}
