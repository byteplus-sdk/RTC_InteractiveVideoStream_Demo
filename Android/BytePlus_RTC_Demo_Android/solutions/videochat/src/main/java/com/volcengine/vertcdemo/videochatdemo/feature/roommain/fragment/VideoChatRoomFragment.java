/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain.fragment;

import static com.volcengine.vertcdemo.videochatdemo.bean.InteractChangedBroadcast.FINISH_INTERACT_TYPE_HOST;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.CAMERA_STATUS_OFF;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.CAMERA_STATUS_ON;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.MIC_STATUS_ON;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_INTERACT;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_NORMAL;

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

import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.AudioVolumeInfo;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.volcengine.vertcdemo.common.IAction;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.InteractChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.JoinRoomResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.MediaChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.MediaOperateBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.SeatChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCSeatInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochatdemo.core.event.AudioVolumeEvent;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.AudienceManagerDialog;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.SeatOptionDialog;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.VideoChatRoomMainActivity;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.VideoChatSeatsGroupLayout;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class VideoChatRoomFragment extends Fragment {
    private static final String TAG = "VideoChatRoomFragment";
    public static final String KEY_JOIN_DATA = "JOIN_ROOM_DATA";

    private VideoChatSeatsGroupLayout mSeatsGroupLayout;
    private AudienceManagerDialog.ICloseChatRoom mICloseChatRoom;
    private final IAction<VCSeatInfo> mOnSeatClick = seatInfo -> {
        Activity hostActivity = getActivity();
        if (!(hostActivity instanceof VideoChatRoomMainActivity)) {
            return;
        }

        if (seatInfo != null && !getSelfUserInfo().isHost() && seatInfo.isLocked()) {
            return;
        }
        VCUserInfo userInfo = seatInfo == null ? null : seatInfo.userInfo;
        String userId = userInfo == null ? null : userInfo.userId;
        String selfUserId = SolutionDataManager.ins().getUserId();
        boolean isSelf = TextUtils.equals(selfUserId, userId);
        boolean isSelfHost = TextUtils.equals(selfUserId, getHostUserInfo().userId);
        if (!isSelfHost && !isSelf) {
            if (userInfo != null) {
                return;
            }
            if (getSelfUserInfo().userStatus == USER_STATUS_INTERACT) {
                SafeToast.show(R.string.already_co_host_msg);
                return;
            } else if (getSelfUserInfo().userStatus == USER_STATUS_NORMAL) {
                if (VideoChatDataManager.ins().getSelfApply()) {
                    SafeToast.show(R.string.already_send_application_msg);
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
    private JoinRoomResponse mJoinRoomResponse;

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

    private void initViewWithData(JoinRoomResponse data) {
        mSeatsGroupLayout.bindHostInfo(data.hostInfo);
        mSeatsGroupLayout.bindSeatInfo(data.seatMap);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedBroadcast event) {
        Log.i(TAG, "VideoChatRoomFragment onInteractChangedBroadcast event:" + event);
        if (mSeatsGroupLayout != null) {
            VCSeatInfo info = new VCSeatInfo();
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
            SafeToast.show(R.string.you_has_co_host_txt);
            VideoChatRTCManager.ins().setUserVisibility(true);
            VideoChatRTCManager.ins().startAudioCapture(event.userInfo.isMicOn());
            VideoChatRTCManager.ins().startMuteAudio(false);
            VideoChatRTCManager.ins().startVideoCapture(event.userInfo.isCameraOn());
            VideoChatRTCManager.ins().startMuteVideo(false);
        } else {
            if (event.type == FINISH_INTERACT_TYPE_HOST) {
                SafeToast.show(R.string.video_you_has_be_audience_txt);
            } else {
                SafeToast.show(R.string.you_has_audience_txt);
            }
            VideoChatRTCManager.ins().setUserVisibility(false);
            VideoChatRTCManager.ins().startAudioCapture(false);
            VideoChatRTCManager.ins().startMuteAudio(true);
            VideoChatRTCManager.ins().startVideoCapture(false);
            VideoChatRTCManager.ins().startMuteVideo(true);
        }
    }

    public void onMediaChangedBroadcast(MediaChangedBroadcast event) {
        mSeatsGroupLayout.updateUserMediaStatus(event.userInfo.userId, event.userInfo.mic == MIC_STATUS_ON, event.userInfo.camera == CAMERA_STATUS_ON);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSeatChangedBroadcast(SeatChangedBroadcast event) {
        mSeatsGroupLayout.updateSeatStatus(event.seatId, event.type);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaOperateBroadcast(MediaOperateBroadcast event) {
        Log.i(TAG, "VideoChatRoomFragment onMediaOperateBroadcast event:" + event);
        boolean isMicOn = event.mic == MIC_STATUS_ON;
        VideoChatDataManager.ins().mCameraOn = event.camera == CAMERA_STATUS_ON;
        SafeToast.show(isMicOn ? R.string.you_unmuted_txt : R.string.you_be_muted_txt);
        mSeatsGroupLayout.updateUserMediaStatus(SolutionDataManager.ins().getUserId(), isMicOn, isCameraOn());
        VideoChatRTCManager.ins().turnOnMic(isMicOn);
        int option = isMicOn ? VideoChatDataManager.MIC_OPTION_ON : VideoChatDataManager.MIC_OPTION_OFF;
        VideoChatRTCManager.ins().getRTMClient().updateMediaStatus(getRoomInfo().roomId,
                getSelfUserInfo().userId, option, isCameraOn() ? CAMERA_STATUS_ON : CAMERA_STATUS_OFF, null);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudioVolumeEvent(AudioVolumeEvent event) {
        AudioVolumeInfo[] infos = event.speakers;
        if (infos != null && infos.length != 0) {
            for (AudioVolumeInfo info : infos) {
                mSeatsGroupLayout.onUserSpeaker(info.uid, info.linearVolume);
            }
        }
    }

    private VCUserInfo getHostUserInfo() {
        return VideoChatDataManager.ins().hostUserInfo;
    }

    private VCUserInfo getSelfUserInfo() {
        return VideoChatDataManager.ins().selfUserInfo;
    }

    private VCRoomInfo getRoomInfo() {
        return VideoChatDataManager.ins().roomInfo;
    }

    private boolean isCameraOn() {
        return VideoChatDataManager.ins().mCameraOn;
    }
}
