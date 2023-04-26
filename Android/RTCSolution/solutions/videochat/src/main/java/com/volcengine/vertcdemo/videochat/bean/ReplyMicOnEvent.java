// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import com.google.gson.annotations.SerializedName;

public class ReplyMicOnEvent extends VideoChatResponse {

    @SerializedName("is_need_apply")
    public boolean needApply = false;

    @Override
    public String toString() {
        return "ReplyMicOnEvent{" +
                "needApply=" + needApply +
                '}';
    }
}
