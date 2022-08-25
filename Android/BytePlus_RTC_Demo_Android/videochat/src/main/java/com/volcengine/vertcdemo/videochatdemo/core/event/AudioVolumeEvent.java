/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.core.event;

import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.AudioVolumeInfo;

public class AudioVolumeEvent {
    public AudioVolumeInfo[] speakers;

    public AudioVolumeEvent(AudioVolumeInfo[] speakers) {
        this.speakers = speakers;
    }
}
