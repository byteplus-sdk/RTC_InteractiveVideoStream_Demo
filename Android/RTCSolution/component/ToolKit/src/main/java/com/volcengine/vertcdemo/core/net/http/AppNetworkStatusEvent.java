// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.core.net.http;

import androidx.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
/**
 * Network state connection state change event
 */
public class AppNetworkStatusEvent {

    public static final int NETWORK_STATUS_DISCONNECTED = 0;
    public static final int NETWORK_STATUS_CONNECTED = 1;

    @IntDef({NETWORK_STATUS_CONNECTED, NETWORK_STATUS_DISCONNECTED})
    @Retention(RetentionPolicy.SOURCE)
    public @interface AppNetworkStatus {}

    public final @AppNetworkStatus int status;

    public AppNetworkStatusEvent(int status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "AppNetworkStatusEvent{" +
                "status=" + status +
                '}';
    }
}
