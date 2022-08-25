/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.bean;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.SerializedName;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class JoinRoomResponse implements Parcelable, RTMBizResponse {
    public boolean isFromCreate = true;
    @SerializedName("room_info")
    public VCRoomInfo roomInfo;
    @SerializedName("user_info")
    public VCUserInfo userInfo;
    @SerializedName("rtc_token")
    public String rtcToken;
    @SerializedName("host_info")
    public VCUserInfo hostInfo;
    @SerializedName("seat_list")
    public Map<Integer, VCSeatInfo> seatMap;
    @SerializedName("audience_count")
    public int audienceCount;
    @SerializedName("anchor_list")
    public List<AnchorInfo> anchorList;
    @SerializedName("interact_info_list")
    public List<InteractInfo> interactInfos;

    @Override
    public String toString() {
        return "JoinRoomResponse{" +
                "isFromCreate=" + isFromCreate +
                ", roomInfo=" + roomInfo +
                ", userInfo=" + userInfo +
                ", rtcToken='" + rtcToken + '\'' +
                ", hostInfo=" + hostInfo +
                ", seatMap=" + seatMap +
                ", audienceCount=" + audienceCount +
                ", anchorList=" + anchorList +
                ", interactInfos=" + interactInfos +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeByte(this.isFromCreate ? (byte) 1 : (byte) 0);
        dest.writeParcelable(this.roomInfo, flags);
        dest.writeParcelable(this.userInfo, flags);
        dest.writeString(this.rtcToken);
        dest.writeParcelable(this.hostInfo, flags);
        dest.writeInt(this.seatMap.size());
        for (Map.Entry<Integer, VCSeatInfo> entry : this.seatMap.entrySet()) {
            dest.writeValue(entry.getKey());
            dest.writeParcelable(entry.getValue(), flags);
        }
        dest.writeInt(this.audienceCount);
        dest.writeList(this.anchorList);
        dest.writeList(this.interactInfos);
    }

    public void readFromParcel(Parcel source) {
        this.isFromCreate = source.readByte() != 0;
        this.roomInfo = source.readParcelable(VCRoomInfo.class.getClassLoader());
        this.userInfo = source.readParcelable(VCUserInfo.class.getClassLoader());
        this.rtcToken = source.readString();
        this.hostInfo = source.readParcelable(VCUserInfo.class.getClassLoader());
        int seatMapSize = source.readInt();
        this.seatMap = new HashMap<Integer, VCSeatInfo>(seatMapSize);
        for (int i = 0; i < seatMapSize; i++) {
            Integer key = (Integer) source.readValue(Integer.class.getClassLoader());
            VCSeatInfo value = source.readParcelable(VCSeatInfo.class.getClassLoader());
            this.seatMap.put(key, value);
        }
        this.audienceCount = source.readInt();
        this.anchorList = new ArrayList<AnchorInfo>();
        source.readList(this.anchorList, AnchorInfo.class.getClassLoader());
        this.interactInfos = new ArrayList<InteractInfo>();
        source.readList(this.interactInfos, InteractInfo.class.getClassLoader());
    }

    public JoinRoomResponse() {
    }

    protected JoinRoomResponse(Parcel in) {
        this.isFromCreate = in.readByte() != 0;
        this.roomInfo = in.readParcelable(VCRoomInfo.class.getClassLoader());
        this.userInfo = in.readParcelable(VCUserInfo.class.getClassLoader());
        this.rtcToken = in.readString();
        this.hostInfo = in.readParcelable(VCUserInfo.class.getClassLoader());
        int seatMapSize = in.readInt();
        this.seatMap = new HashMap<Integer, VCSeatInfo>(seatMapSize);
        for (int i = 0; i < seatMapSize; i++) {
            Integer key = (Integer) in.readValue(Integer.class.getClassLoader());
            VCSeatInfo value = in.readParcelable(VCSeatInfo.class.getClassLoader());
            this.seatMap.put(key, value);
        }
        this.audienceCount = in.readInt();
        this.anchorList = new ArrayList<AnchorInfo>();
        in.readList(this.anchorList, AnchorInfo.class.getClassLoader());
        this.interactInfos = new ArrayList<InteractInfo>();
        in.readList(this.interactInfos, InteractInfo.class.getClassLoader());
    }

    public static final Parcelable.Creator<JoinRoomResponse> CREATOR = new Parcelable.Creator<JoinRoomResponse>() {
        @Override
        public JoinRoomResponse createFromParcel(Parcel source) {
            return new JoinRoomResponse(source);
        }

        @Override
        public JoinRoomResponse[] newArray(int size) {
            return new JoinRoomResponse[size];
        }
    };
}
