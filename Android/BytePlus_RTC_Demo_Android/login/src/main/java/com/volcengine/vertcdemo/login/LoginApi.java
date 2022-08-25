/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.login;

import android.util.Log;

import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.ServerResponse;
import com.volcengine.vertcdemo.core.net.http.HttpRequestHelper;
import com.volcengine.vertcdemo.entity.LoginInfo;

import org.json.JSONObject;

public class LoginApi {
    private static final String TAG = "LoginApi";
    private static boolean debug = false;

    public static void sendLoginSms(String phoneNum) {
        if (debug) {
            Log.d(TAG, "debug mode, any code will pass.");
            return;
        }
        final IRequestCallback<ServerResponse<Void>> callBack = new IRequestCallback<ServerResponse<Void>>() {
            @Override
            public void onSuccess(ServerResponse<Void> data) {
                Log.d(TAG, "sendLoginSms result: " + data.getCode());
            }

            @Override
            public void onError(int errorCode, String message) {
                Log.d(TAG, "sendLoginSms result: " + errorCode + "; " + message);
            }
        };

        try {
            JSONObject content = new JSONObject();
            content.put("cell_phone", phoneNum);
            content.put("country_code", "86");

            JSONObject params = new JSONObject();
            params.put("event_name", "sendLoginSms");
            params.put("content", content.toString());
            params.put("device_id", SolutionDataManager.ins().getDeviceId());

            HttpRequestHelper.sendPost(params, Void.class, callBack);
        } catch (Exception e) {
            Log.d(TAG, "sendLoginSms failed:", e);
            callBack.onError(-1, "Content Error");
        }
    }


    public static void verifyLoginSms(String phoneNum,
                                      String code,
                                      IRequestCallback<ServerResponse<LoginInfo>> callBack) {
        if (debug) {
            passwordFreeLogin(phoneNum, callBack);
            return;
        }
        try {
            JSONObject content = new JSONObject();
            content.put("cell_phone", phoneNum);
            content.put("country_code", "86");
            content.put("code", code);

            JSONObject params = new JSONObject();
            params.put("event_name", "verifyLoginSms");
            params.put("content", content.toString());
            params.put("device_id", SolutionDataManager.ins().getDeviceId());

            HttpRequestHelper.sendPost(params, LoginInfo.class, callBack);
        } catch (Exception e) {
            Log.d(TAG, "verifyLoginSms failed:" + e.getMessage());
            callBack.onError(-1, "Content Error");
        }

    }

    public static void passwordFreeLogin(String userName, IRequestCallback<ServerResponse<LoginInfo>> callBack) {
        try {
            JSONObject content = new JSONObject();
            content.put("user_name", userName);

            JSONObject params = new JSONObject();
            params.put("event_name", "passwordFreeLogin");
            params.put("content", content.toString());
            params.put("device_id", SolutionDataManager.ins().getDeviceId());

            HttpRequestHelper.sendPost(params, LoginInfo.class, callBack);
        } catch (Exception e) {
            Log.d(TAG, "verifyLoginSms failed:", e);
            callBack.onError(-1, "Content Error");
        }
    }

    public static void changeUserName(String userName, String loginToken, IRequestCallback<ServerResponse<Void>> callBack) {
        try {
            JSONObject content = new JSONObject();
            content.put("user_name", userName);
            content.put("login_token", loginToken);

            JSONObject params = new JSONObject();
            params.put("event_name", "changeUserName");
            params.put("content", content.toString());
            params.put("device_id", SolutionDataManager.ins().getDeviceId());

            HttpRequestHelper.sendPost(params, Void.class, callBack);
        } catch (Exception e) {
            Log.d(TAG, "changeUserName failed:", e);
            callBack.onError(-1, "Content Error");
        }
    }
}
