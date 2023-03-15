/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.core.net.rtm;

import android.text.TextUtils;

import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;

import java.nio.ByteBuffer;

public abstract class RTCEventHandlerWithRTS extends IRTCVideoEventHandler {
    private static final String UID_BIZ_SERVER = "server";
    RTSBaseClient baseClient;

    public void setBaseClient(RTSBaseClient baseClient) {
        this.baseClient = baseClient;
    }

    @Override
    public void onLoginResult(String uid, int errorCode, int elapsed) {
        if (baseClient != null) {
            baseClient.onLoginResult(uid, errorCode, elapsed);
        }
    }

    @Override
    public void onServerParamsSetResult(int error) {
        if (baseClient != null) {
            baseClient.onServerParamsSetResult(error);
        }
    }

    @Override
    public void onServerMessageSendResult(long msgid, int error, ByteBuffer message) {
        super.onServerMessageSendResult(msgid, error, message);
        if (baseClient != null) {
            baseClient.onServerMessageSendResult(msgid, error);
        }
    }

    @Override
    public void onUserMessageReceivedOutsideRoom(String uid, String message) {
        onMessageReceived(uid, message);
    }

    private void onMessageReceived(String fromUid, String message) {
        //来自业务服务器的响应或者通知
        if (TextUtils.equals(UID_BIZ_SERVER, fromUid)) {
            if (baseClient != null) {
                baseClient.onMessageReceived(fromUid, message);
            }
            return;
        }
        //客户端直接的通讯
        onRTCMessageReceived(fromUid, message);
    }

    /**
     * 非来自业务服务器的消息
     *
     * @param fromUid 发送消息uid
     * @param message 发送内容
     */
    protected void onRTCMessageReceived(String fromUid, String message) {

    }
}
