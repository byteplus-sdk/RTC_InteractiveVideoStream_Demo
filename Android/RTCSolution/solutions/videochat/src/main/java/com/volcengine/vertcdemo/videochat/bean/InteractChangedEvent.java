// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import androidx.annotation.IntDef;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public class InteractChangedEvent implements RTSBizInform {

    public static final int FINISH_INTERACT_TYPE_HOST = 1;
    public static final int FINISH_INTERACT_TYPE_SELF = 2;

    @IntDef({FINISH_INTERACT_TYPE_HOST, FINISH_INTERACT_TYPE_SELF})
    @Retention(RetentionPolicy.SOURCE)
    public @interface FinishInteractType {
    }

    public boolean isStart;
    @SerializedName("user_info")
    public VideoChatUserInfo userInfo;
    @SerializedName("seat_id")
    public int seatId;
    @SerializedName("type")
    @FinishInteractType
    public int type = FINISH_INTERACT_TYPE_HOST;

    public boolean isByHost() {
        return type == FINISH_INTERACT_TYPE_HOST;
    }

    @Override
    public String toString() {
        return "InteractChangedEvent{" +
                "isStart=" + isStart +
                ", userInfo=" + userInfo +
                ", seatId=" + seatId +
                ", type=" + type +
                '}';
    }
}
