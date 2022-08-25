/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.entity;

public class AuditStateResult {

    public static final int NORMAL = 0;
    public static final int UPDATE = 1;

    public int state;
    public String text;
    public String url;

    @Override
    public String toString() {
        return "AuditStateResult{" +
                "state=" + state +
                ", text='" + text + '\'' +
                ", url='" + url + '\'' +
                '}';
    }
}
