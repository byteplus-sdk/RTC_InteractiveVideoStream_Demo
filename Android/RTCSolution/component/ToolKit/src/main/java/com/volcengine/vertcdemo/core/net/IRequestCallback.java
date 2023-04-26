// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.core.net;

public interface IRequestCallback<T>  {

    void onSuccess(T data);

    void onError(int errorCode, String message);
}
