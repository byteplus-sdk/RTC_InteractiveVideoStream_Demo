/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.SEAT_STATUS_LOCKED;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;

public class VCSeatInfo implements Parcelable {
    public int seatIndex = -1;
    @SerializedName("status")
    @VideoChatDataManager.SeatStatus
    public int status;
    @SerializedName("guest_info")
    public VCUserInfo userInfo;

    public boolean isLocked() {
        return status == SEAT_STATUS_LOCKED;
    }

    public VCSeatInfo deepCopy() {
        VCSeatInfo info = new VCSeatInfo();
        info.seatIndex = seatIndex;
        info.status = status;
        info.userInfo = userInfo == null ? null : userInfo.deepCopy();
        return info;
    }

    @Override
    public String toString() {
        return "VCSeatInfo{" +
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
        this.userInfo = source.readParcelable(VCUserInfo.class.getClassLoader());
    }

    public VCSeatInfo() {
    }

    protected VCSeatInfo(Parcel in) {
        this.seatIndex = in.readInt();
        this.status = in.readInt();
        this.userInfo = in.readParcelable(VCUserInfo.class.getClassLoader());
    }

    public static final Parcelable.Creator<VCSeatInfo> CREATOR = new Parcelable.Creator<VCSeatInfo>() {
        @Override
        public VCSeatInfo createFromParcel(Parcel source) {
            return new VCSeatInfo(source);
        }

        @Override
        public VCSeatInfo[] newArray(int size) {
            return new VCSeatInfo[size];
        }
    };
}
