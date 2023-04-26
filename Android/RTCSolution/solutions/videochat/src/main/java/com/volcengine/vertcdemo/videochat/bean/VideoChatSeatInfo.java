// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.bean;

import static com.volcengine.vertcdemo.videochat.core.VideoChatDataManager.SEAT_STATUS_LOCKED;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;

public class VideoChatSeatInfo implements Parcelable {
    public int seatIndex = -1;
    @SerializedName("status")
    @VideoChatDataManager.SeatStatus
    public int status;
    @SerializedName("guest_info")
    public VideoChatUserInfo userInfo;

    public boolean isLocked() {
        return status == SEAT_STATUS_LOCKED;
    }

    public VideoChatSeatInfo deepCopy() {
        VideoChatSeatInfo info = new VideoChatSeatInfo();
        info.seatIndex = seatIndex;
        info.status = status;
        info.userInfo = userInfo == null ? null : userInfo.deepCopy();
        return info;
    }

    @Override
    public String toString() {
        return "VideoChatSeatInfo{" +
                "seatIndex=" + seatIndex +
                ", status=" + status +
                ", userInfo=" + userInfo +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(this.seatIndex);
        dest.writeInt(this.status);
        dest.writeParcelable(this.userInfo, flags);
    }

    public void readFromParcel(Parcel source) {
        this.seatIndex = source.readInt();
        this.status = source.readInt();
        this.userInfo = source.readParcelable(VideoChatUserInfo.class.getClassLoader());
    }

    public VideoChatSeatInfo() {
    }

    protected VideoChatSeatInfo(Parcel in) {
        this.seatIndex = in.readInt();
        this.status = in.readInt();
        this.userInfo = in.readParcelable(VideoChatUserInfo.class.getClassLoader());
    }

    public static final Parcelable.Creator<VideoChatSeatInfo> CREATOR = new Parcelable.Creator<VideoChatSeatInfo>() {
        @Override
        public VideoChatSeatInfo createFromParcel(Parcel source) {
            return new VideoChatSeatInfo(source);
        }

        @Override
        public VideoChatSeatInfo[] newArray(int size) {
            return new VideoChatSeatInfo[size];
        }
    };
}
