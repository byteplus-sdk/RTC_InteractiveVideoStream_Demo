/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.core.net.rtm;

import android.text.TextUtils;

import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

import java.nio.ByteBuffer;
import java.util.Map;

public abstract class RTCEventHandlerWithRTM extends IRTCEngineEventHandler {
    private static final String UID_BIZ_SERVER = "server";
    RTMBaseClient baseClient;

    public void setBaseClient(RTMBaseClient baseClient) {
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
    public void onRoomMessageReceived(String uid, String message) {
        onMessageReceived(uid, message);
    }

    @Override
    public void onUserMessageReceived(String uid, String message) {
        onMessageReceived(uid, message);
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
     * @param fromUid 发送消息uid
     * @param message 发送内容
     */
    protected void onRTCMessageReceived(String fromUid, String message) {
    }

    /**
     * 判断 onRoomStateChanged 中的extraInfo，是不是加入房间成功了
     * @param extraInfo 额外信息
     * @return true:加入房间成功
     */
    protected boolean checkExtraInfoIfJoinRoomSuccess(String extraInfo) {
        int joinType = -1;
        try {
            Map extra = GsonUtils.gson().fromJson(extraInfo, Map.class);
            // 341后 SDK传的固定键
            joinType = (int) Double.parseDouble(extra.get("join_type").toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return joinType == 0;
    }
}
