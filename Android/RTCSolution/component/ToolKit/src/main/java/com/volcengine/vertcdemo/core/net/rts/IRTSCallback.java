// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.core.net.rts;

import androidx.annotation.Nullable;

public interface IRTSCallback {
    void onSuccess(@Nullable String data);

    void onError(int errorCode, @Nullable String message);
}
