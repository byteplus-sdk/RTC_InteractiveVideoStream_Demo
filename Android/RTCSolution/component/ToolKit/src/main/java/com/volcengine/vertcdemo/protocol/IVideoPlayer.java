// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.protocol;

import android.content.Context;
import android.view.View;

import androidx.annotation.IntDef;

import com.volcengine.vertcdemo.common.IAction;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public interface IVideoPlayer {
    // default
    int MODE_NONE = 0;
    // keep aspect to fit
    int MODE_ASPECT_FIT = 1;
    // keep aspect to fill
    int MODE_ASPECT_FILL = 2;
    // ignore aspect to fill
    int MODE_FILL = 3;

    @IntDef({MODE_NONE, MODE_ASPECT_FIT, MODE_ASPECT_FILL, MODE_FILL})
    @Retention(RetentionPolicy.SOURCE)
    @interface ScalingMode {
    }
    /**
     * configuration Player
     */
    void startWithConfiguration(Context context);


    void setSEICallback(IAction<String> SEICallback);
    /**
     * Set playback address, parent view
     * @param url stream URL
     * @param container parent class view
     */
    void setPlayerUrl(String url, View container);
    /**
     * update playback scale mode
     * @param scalingMode playback scale mode
     */
    void updatePlayScaleModel(@ScalingMode int scalingMode);
    /**
     * start playing
     */
    void play();
    /**
     * Update the new playback address
     * @param url new play URL
     */
    void replacePlayWithUrl(String url);
    /**
     * stop playback
     */
    void stop();
    /**
     * Whether the player supports SEI function
     * @return BOOL YES supports SEI, NO does not support SEI
     */
    boolean isSupportSEI();
    /**
     * release player resources
     */
    void destroy();
}
