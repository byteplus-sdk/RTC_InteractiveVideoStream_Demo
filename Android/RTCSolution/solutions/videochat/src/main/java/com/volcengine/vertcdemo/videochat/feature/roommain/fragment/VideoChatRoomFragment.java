// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.feature.roommain.fragment;

import static com.volcengine.vertcdemo.videochat.bean.InteractChangedEvent.FINISH_INTERACT_TYPE_HOST;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.CAMERA_STATUS_OFF;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.CAMERA_STATUS_ON;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.MIC_STATUS_ON;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_STATUS_INTERACT;
import static com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo.USER_STATUS_NORMAL;

import android.app.Activity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.volcengine.vertcdemo.common.SolutionToast;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochat.bean.InteractChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.JoinRoomEvent;
import com.volcengine.vertcdemo.videochat.bean.MediaChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.MediaOperateEvent;
import com.volcengine.vertcdemo.videochat.bean.SeatChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatRoomInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatSeatInfo;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochat.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochat.event.SDKAudioPropertiesEvent;
import com.volcengine.vertcdemo.videochat.feature.roommain.AudienceManagerDialog;
import com.volcengine.vertcdemo.videochat.feature.roommain.SeatOptionDialog;
import com.volcengine.vertcdemo.videochat.feature.roommain.VideoChatRoomMainActivity;
import com.volcengine.vertcdemo.videochat.feature.roommain.VideoChatSeatsGroupLayout;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.List;

public class VideoChatRoomFragment extends Fragment {
    private static final String TAG = "VideoChatRoomFragment";
    public static final String KEY_JOIN_DATA = "JOIN_ROOM_DATA";

    private VideoChatSeatsGroupLayout mSeatsGroupLayout;
    private AudienceManagerDialog.ICloseChatRoom mICloseChatRoom;
    private final IAction<VideoChatSeatInfo> mOnSeatClick = seatInfo -> {
        Activity hostActivity = getActivity();
        if (!(hostActivity instanceof VideoChatRoomMainActivity)) {
            return;
        }

        if (seatInfo != null && !getSelfUserInfo().isHost() && seatInfo.isLocked()) {
            return;
        }
        VideoChatUserInfo userInfo = seatInfo == null ? null : seatInfo.userInfo;
        String userId = userInfo == null ? null : userInfo.userId;
        String selfUserId = SolutionDataManager.ins().getUserId();
        boolean isSelf = TextUtils.equals(selfUserId, userId);
        boolean isSelfHost = TextUtils.equals(selfUserId, getHostUserInfo().userId);
        if (!isSelfHost && !isSelf) {
            if (userInfo != null) {
                return;
            }
            if (getSelfUserInfo().userStatus == USER_STATUS_INTERACT) {
                SolutionToast.show(R.string.video_chat_already_on_mic);
                return;
            } else if (getSelfUserInfo().userStatus == USER_STATUS_NORMAL) {
                if (VideoChatDataManager.ins().getSelfApply()) {
                    SolutionToast.show(R.string.application_sent_host);
                    return;
                }
            }
        } else if (isSelf && isSelfHost) {
            return;
        }
        SeatOptionDialog dialog = new SeatOptionDialog(getContext());
        dialog.setData(getRoomInfo().roomId, seatInfo, getSelfUserInfo().userRole, getSelfUserInfo().userStatus);
        dialog.setICloseChatRoom(mICloseChatRoom);
        dialog.show();
    };
    private JoinRoomEvent mJoinRoomResponse;

    public VideoChatRoomFragment() {
        super();
    }

    public void setICloseChatRoom(AudienceManagerDialog.ICloseChatRoom mICloseChatRoom) {
        this.mICloseChatRoom = mICloseChatRoom;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mJoinRoomResponse = getArguments() == null ? null : getArguments().getParcelable(KEY_JOIN_DATA);
        SolutionDemoEventManager.register(this);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_video_chat, container, false);
        mSeatsGroupLayout = view.findViewById(R.id.voice_chat_demo_main_seat_group);
        mSeatsGroupLayout.setSeatClick(mOnSeatClick);
        Log.i(TAG, "VideoChatRoomFragment onCreateView");
        initViewWithData(mJoinRoomResponse);
        return view;
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
        SolutionDemoEventManager.unregister(this);
    }

    private void initViewWithData(JoinRoomEvent data) {
        mSeatsGroupLayout.bindHostInfo(data.hostInfo);
        mSeatsGroupLayout.bindSeatInfo(data.seatMap);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedEvent event) {
        Log.i(TAG, "VideoChatRoomFragment onInteractChangedBroadcast event:" + event);
        if (mSeatsGroupLayout != null) {
            VideoChatSeatInfo info = new VideoChatSeatInfo();
            info.userInfo = event.userInfo;
            info.status = VideoChatDataManager.SEAT_STATUS_UNLOCKED;
            mSeatsGroupLayout.bindSeatInfo(event.seatId, event.isStart ? info : null);
        }

        boolean isSelf = TextUtils.equals(SolutionDataManager.ins().getUserId(), event.userInfo.userId);
        if (!isSelf) {
            return;
        }
        VideoChatDataManager.ins().setSelfApply(false);
        if (event.isStart) {
            SolutionToast.show(R.string.video_chat_you_on_mic);
            VideoChatRTCManager.ins().setUserVisibility(true);
            VideoChatRTCManager.ins().startAudioCapture(event.userInfo.isMicOn());
            VideoChatRTCManager.ins().startMuteAudio(false);
            VideoChatRTCManager.ins().startVideoCapture(event.userInfo.isCameraOn());
            VideoChatRTCManager.ins().startMuteVideo(false);
        } else {
            if (event.type == FINISH_INTERACT_TYPE_HOST) {
                SolutionToast.show(R.string.video_chat_removed_on_mic);
            } else {
                SolutionToast.show(R.string.video_chat_you_off_mic);
            }
            VideoChatRTCManager.ins().setUserVisibility(false);
            VideoChatRTCManager.ins().startAudioCapture(false);
            VideoChatRTCManager.ins().startMuteAudio(true);
            VideoChatRTCManager.ins().startVideoCapture(false);
            VideoChatRTCManager.ins().startMuteVideo(true);
        }
    }

    public void onMediaChangedBroadcast(MediaChangedEvent event) {
        mSeatsGroupLayout.updateUserMediaStatus(event.userInfo.userId, event.userInfo.mic == MIC_STATUS_ON, event.userInfo.camera == CAMERA_STATUS_ON);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSeatChangedBroadcast(SeatChangedEvent event) {
        mSeatsGroupLayout.updateSeatStatus(event.seatId, event.type);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaOperateBroadcast(MediaOperateEvent event) {
        Log.i(TAG, "VideoChatRoomFragment onMediaOperateBroadcast event:" + event);
        boolean isMicOn = event.mic == MIC_STATUS_ON;
        VideoChatDataManager.ins().mCameraOn = event.camera == CAMERA_STATUS_ON;
        SolutionToast.show(isMicOn ? R.string.host_unmuted_you : R.string.you_muted_by_host_title);
        mSeatsGroupLayout.updateUserMediaStatus(SolutionDataManager.ins().getUserId(), isMicOn, isCameraOn());
        VideoChatRTCManager.ins().turnOnMic(isMicOn);
        int option = isMicOn ? VideoChatDataManager.MIC_OPTION_ON : VideoChatDataManager.MIC_OPTION_OFF;
        VideoChatRTCManager.ins().getRTSClient().updateMediaStatus(getRoomInfo().roomId,
                getSelfUserInfo().userId, option, isCameraOn() ? CAMERA_STATUS_ON : CAMERA_STATUS_OFF, null);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSDKAudioPropertiesEvent(SDKAudioPropertiesEvent event) {
        List<SDKAudioPropertiesEvent.SDKAudioProperties> infos = event.audioPropertiesList;
        if (infos != null && infos.size() != 0) {
            for (SDKAudioPropertiesEvent.SDKAudioProperties info : infos) {
                mSeatsGroupLayout.onUserSpeaker(info.userId, 0);
            }
        }
    }

    private VideoChatUserInfo getHostUserInfo() {
        return VideoChatDataManager.ins().hostUserInfo;
    }

    private VideoChatUserInfo getSelfUserInfo() {
        return VideoChatDataManager.ins().selfUserInfo;
    }

    private VideoChatRoomInfo getRoomInfo() {
        return VideoChatDataManager.ins().roomInfo;
    }

    private boolean isCameraOn() {
        return VideoChatDataManager.ins().mCameraOn;
    }
}
