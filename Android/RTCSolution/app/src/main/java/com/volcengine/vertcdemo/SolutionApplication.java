// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo;

import android.app.Application;
import android.text.TextUtils;

import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.net.http.AppNetworkStatusUtil;
import com.volcengine.vertcdemo.utils.ActivityDataManager;
import com.volcengine.vertcdemo.utils.AppUtil;

public class SolutionApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        AppUtil.initApp(this);
        initIMService();
        ActivityDataManager.getInstance().init(this);
        new CrashHandler(this);
        AppNetworkStatusUtil.registerNetworkCallback(this);
    }

    public void initIMService() {
    }
}
