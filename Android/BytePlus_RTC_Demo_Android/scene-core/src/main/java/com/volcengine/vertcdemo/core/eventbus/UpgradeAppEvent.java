/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.core.eventbus;

import com.volcengine.vertcdemo.entity.AuditStateResult;

public class UpgradeAppEvent {
    public AuditStateResult result;

    public UpgradeAppEvent(AuditStateResult result) {
        this.result = result;
    }
}
