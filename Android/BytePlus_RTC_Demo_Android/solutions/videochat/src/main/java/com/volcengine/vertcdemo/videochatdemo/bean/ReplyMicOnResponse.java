/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizResponse;

public class ReplyMicOnResponse implements RTSBizResponse {

    @SerializedName("is_need_apply")
    public boolean needApply = false;

    @Override
    public String toString() {
        return "ReplyMicOnRequest{" +
                "needApply=" + needApply +
                '}';
    }
}
