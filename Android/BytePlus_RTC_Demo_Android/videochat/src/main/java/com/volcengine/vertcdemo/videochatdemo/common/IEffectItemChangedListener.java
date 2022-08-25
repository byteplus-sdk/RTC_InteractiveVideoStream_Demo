/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.common;

import android.view.View;

public interface IEffectItemChangedListener {
    void onChanged(View newItem, View lastItem);
}
