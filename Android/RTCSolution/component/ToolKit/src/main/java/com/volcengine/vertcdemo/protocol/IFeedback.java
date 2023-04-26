// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.protocol;

import android.view.View;

import java.util.Set;

public interface IFeedback {

    void initWithViewGroup(View view, Set<String> availableSceneNameAbbr);
}
