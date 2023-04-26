// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.core;

import androidx.annotation.IntDef;

import com.volcengine.vertcdemo.videochat.bean.VideoChatRoomInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public class VideoChatDataManager {
    private static final String TAG = "VideoChatDataManager";

    public VideoChatRoomInfo roomInfo;
    public VideoChatUserInfo hostUserInfo;
    public VideoChatUserInfo selfUserInfo;
    public boolean mCameraOn = false;

    public static final int INTERACT_STATUS_NORMAL = 0;
    public static final int INTERACT_STATUS_INVITING_CHAT = 1;
    public static final int INTERACT_STATUS_INVITING_PK = 2;
    @IntDef({INTERACT_STATUS_NORMAL,INTERACT_STATUS_INVITING_CHAT, INTERACT_STATUS_INVITING_PK})
    @Retention(RetentionPolicy.SOURCE)
    public @interface SelfInteractStatusType {
    }
    public int selfInviteStatus;

    public static final int SEAT_STATUS_LOCKED = 0;
    public static final int SEAT_STATUS_UNLOCKED = 1;

    @IntDef({SEAT_STATUS_LOCKED, SEAT_STATUS_UNLOCKED})
    @Retention(RetentionPolicy.SOURCE)
    public @interface SeatStatus {
    }

    public static final int SEAT_OPTION_LOCK = 1;
    public static final int SEAT_OPTION_UNLOCK = 2;
    public static final int SEAT_OPTION_MIC_OFF = 3;
    public static final int SEAT_OPTION_MIC_ON = 4;
    public static final int SEAT_OPTION_END_INTERACT = 5;

    @IntDef({SEAT_OPTION_LOCK, SEAT_OPTION_UNLOCK, SEAT_OPTION_MIC_OFF, SEAT_OPTION_MIC_ON, SEAT_OPTION_END_INTERACT})
    @Retention(RetentionPolicy.SOURCE)
    public @interface SeatOption {
    }

    public static final int REPLY_TYPE_ACCEPT = 1;
    public static final int REPLY_TYPE_REJECT = 2;

    @IntDef({REPLY_TYPE_ACCEPT, REPLY_TYPE_REJECT})
    @Retention(RetentionPolicy.SOURCE)
    public @interface ReplyType {
    }


    public static final int MIC_OPTION_OFF = 0;
    public static final int MIC_OPTION_ON = 1;

    @IntDef({MIC_OPTION_OFF, MIC_OPTION_ON})
    @Retention(RetentionPolicy.SOURCE)
    public @interface MicOption {
    }

    public static final int TYPE_MUTE = 0;
    public static final int TYPE_UN_MUTE = 1;

    private static VideoChatDataManager sInstance;

    public static VideoChatDataManager ins() {
        if (sInstance == null) {
            sInstance = new VideoChatDataManager();
        }
        return sInstance;
    }

    private boolean isBGMOpening = false;
    private boolean hasNewApply = false;
    private int mBGMVolume = 100;
    private int mUserVolume = 100;
    private boolean isFirstSetBGMSwitch = true;
    private boolean isSelfApply = false;

    public void clearData() {
        selfUserInfo = null;
        hostUserInfo = null;
        roomInfo = null;
        isBGMOpening = false;
        hasNewApply = false;
        mBGMVolume = 100;
        mUserVolume = 100;
        isFirstSetBGMSwitch = true;
        isSelfApply = false;
        selfInviteStatus = INTERACT_STATUS_NORMAL;
    }

    public void setBGMOpening(boolean isBGMOpening) {
        this.isBGMOpening = isBGMOpening;
    }

    public boolean getBGMOpening() {
        return isBGMOpening;
    }

    public void setBGMVolume(int bgmVolume) {
        mBGMVolume = bgmVolume;
    }

    public int getBGMVolume() {
        return mBGMVolume;
    }

    public void setUserVolume(int userVolume) {
        mUserVolume = userVolume;
    }

    public int getUserVolume() {
        return mUserVolume;
    }

    public boolean hasNewApply() {
        return hasNewApply;
    }

    public void setNewApply(boolean hasNewApply) {
        this.hasNewApply = hasNewApply;
    }

    public void setIsFirstSetBGMSwitch(boolean isFirstSetBGMSwitch) {
        this.isFirstSetBGMSwitch = isFirstSetBGMSwitch;
    }

    public boolean getIsFirstSetBGMSwitch() {
        return isFirstSetBGMSwitch;
    }

    public void setSelfApply(boolean isSelfApply) {
        this.isSelfApply = isSelfApply;
    }

    public boolean getSelfApply() {
        return isSelfApply;
    }
}
