// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.protocol;

import android.content.Context;

import com.volcengine.vertcdemo.common.IAction;

public interface ILogin {

    void showLoginView(Context context);

    void closeAccount(IAction<Boolean> action);
}
