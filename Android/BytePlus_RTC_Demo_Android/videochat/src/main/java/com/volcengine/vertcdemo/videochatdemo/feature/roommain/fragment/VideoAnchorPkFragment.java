/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain.fragment;

import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;

import com.ss.bytertc.engine.data.ForwardStreamInfo;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.NetworkQuality;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.rtm.RTMBizResponse;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.ManageOtherAnchorBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.MediaChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.NetStatusBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.UserJoinedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class VideoAnchorPkFragment extends Fragment {
    private static final String TAG = "VideoAnchorPkFragment";

    public static final String KEY_RTC_TOKEN = "rtc_token";
    public static final String KEY_PEER_ROOM_ID = "peer_room_id";
    public static final String KEY_PEER_USER_ID = "peer_user_id";
    public static final String KEY_PEER_USER_NAME = "peer_user_name";
    public static final String KEY_PEER_ANCHOR_MUTED = "peer_anchor_muted";
    public static final String KEY_PEER_ANCHOR_MIC_ON = "peer_anchor_mic_on";
    public static final String KEY_PEER_ANCHOR_CAMERA_ON = "peer_anchor_camera_on";
    public static final String KEY_LOCAL_ANCHOR_MIC_ON = "local_anchor_mic_on";
    public static final String KEY_LOCAL_ANCHOR_CAMERA_ON = "local_anchor_camera_on";

    private FrameLayout mLocalVideoContainer;
    private FrameLayout mRemoteVideoContainer;
    private TextView mLocalStatusTv;
    private TextView mRemoteStatusTv;
    private TextView mLocalNameTv;
    private TextView mRemoteNameTv;
    private ImageView mMuteRemoteIv;

    private String mPeerRoomId;
    private String mPeerUid;
    private String mPeerUname;

    private boolean mPeerAnchorMuted;
    private boolean mPeerAnchorCameraOn;
    private boolean mPeerAnchorMicOn;
    private boolean mLocalAnchorCameraOn;
    private boolean mLocalAnchorMicOn;

    private boolean mMutingPeerAnchor;
    private boolean mSelfMutePeerAnchor;

    public VideoAnchorPkFragment() {
        super();
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SolutionDemoEventManager.register(this);
        Bundle args = getArguments();
        String rtcToken = null;
        if (args != null) {
            mPeerRoomId = args.getString(KEY_PEER_ROOM_ID);
            mPeerUid = args.getString(KEY_PEER_USER_ID);
            mPeerUname = args.getString(KEY_PEER_USER_NAME);
            rtcToken = args.getString(KEY_RTC_TOKEN);
            mPeerAnchorMuted = args.getBoolean(KEY_PEER_ANCHOR_MUTED);
            mPeerAnchorCameraOn = args.getBoolean(KEY_PEER_ANCHOR_CAMERA_ON);
            mPeerAnchorMicOn = args.getBoolean(KEY_PEER_ANCHOR_MIC_ON);
            mLocalAnchorCameraOn = args.getBoolean(KEY_LOCAL_ANCHOR_CAMERA_ON);
            mLocalAnchorMicOn = args.getBoolean(KEY_LOCAL_ANCHOR_MIC_ON);
        }
        startForwardStream(rtcToken, mPeerRoomId);
    }

    private void startForwardStream(String rtcToken, String peerRoomId) {
        if (!getSelfUserInfo().isHost()) {
            return;
        }
        if (!VideoChatRTCManager.ins().isTest && TextUtils.isEmpty(rtcToken)) {
            return;
        }
        if (TextUtils.isEmpty(peerRoomId)) {
            return;
        }
        Log.i(TAG, "startForwardStream mPeerRoomId:" + peerRoomId + ",rtcToken:" + rtcToken);
        VideoChatRTCManager.ins().forwardStreamToRoom(new ForwardStreamInfo(peerRoomId, rtcToken));
    }

    private void stopForwardStream() {
        if (!getSelfUserInfo().isHost()) {
            return;
        }
        VideoChatRTCManager.ins().stopForwardStreamToRoom();
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_video_pk, container, false);
        TextView mLocalUserNamePrefixTv = view.findViewById(R.id.local_name_tv);
        TextView mRemoteUserNamePrefixTv = view.findViewById(R.id.remote_name_tv);
        mLocalVideoContainer = view.findViewById(R.id.local_video_container);
        mRemoteVideoContainer = view.findViewById(R.id.remote_video_container);
        mLocalStatusTv = view.findViewById(R.id.local_network_status_tv);
        mRemoteStatusTv = view.findViewById(R.id.remote_network_status_tv);
        mLocalNameTv = view.findViewById(R.id.local_user_name_tv);
        mRemoteNameTv = view.findViewById(R.id.remote_user_name_tv);
        mMuteRemoteIv = view.findViewById(R.id.mute_remote_user_iv);
        if (getSelfUserInfo().isHost()) {
            addLocalVideo();
        } else {
            addSelfAnchorVideo();
        }
        addRemoteAnchorVideo();
        String localName = getLocalUserName();
        mLocalNameTv.setText(localName);
        mLocalUserNamePrefixTv.setText(TextUtils.isEmpty(localName) ? "" : localName.substring(0, 1));
        mRemoteNameTv.setText(mPeerUname);
        mRemoteUserNamePrefixTv.setText(TextUtils.isEmpty(mPeerUname) ? "" : mPeerUname.substring(0, 1));

        Drawable localMicDrawable = mLocalAnchorMicOn ? null : ContextCompat.getDrawable(Utilities.getApplicationContext(), R.drawable.mic_off_1x);
        mLocalNameTv.setCompoundDrawablesWithIntrinsicBounds(null, null, localMicDrawable, null);
        mLocalVideoContainer.setVisibility(mLocalAnchorCameraOn ? View.VISIBLE : View.INVISIBLE);

        Drawable peerMicDrawable = mPeerAnchorMicOn ? null : ContextCompat.getDrawable(Utilities.getApplicationContext(), R.drawable.mic_off_1x);
        mRemoteNameTv.setCompoundDrawablesWithIntrinsicBounds(null, null, peerMicDrawable, null);
        mRemoteVideoContainer.setVisibility(mPeerAnchorCameraOn ? View.VISIBLE : View.INVISIBLE);

        mMuteRemoteIv.setImageResource(mPeerAnchorMuted
                ? R.drawable.voice_chat_demo_main_pk_mute_remote
                : R.drawable.voice_chat_demo_main_pk_unmute_remote);
        //观众没有mute权限
        if (getSelfUserInfo() != null && getSelfUserInfo().isHost()) {
            mMuteRemoteIv.setOnClickListener(v -> {
                if (mMutingPeerAnchor) {
                    return;
                }
                mMutingPeerAnchor = true;
                mSelfMutePeerAnchor = true;
                int targetType = mPeerAnchorMuted ? VideoChatDataManager.TYPE_UN_MUTE : VideoChatDataManager.TYPE_MUTE;
                VideoChatRTCManager.ins().getRTMClient().manageOtherAnchor(
                        VideoChatDataManager.ins().selfUserInfo.userId,
                        VideoChatDataManager.ins().selfUserInfo.roomId,
                        mPeerUid, targetType, new IRequestCallback<RTMBizResponse>() {
                    @Override
                    public void onSuccess(RTMBizResponse data) {
                        mMutingPeerAnchor = false;
                        VideoChatRTCManager.ins().muteRemoteAudio(mPeerUid, !mPeerAnchorMuted);
                        mPeerAnchorMuted = !mPeerAnchorMuted;
                        mMuteRemoteIv.setImageResource(mPeerAnchorMuted
                                ? R.drawable.voice_chat_demo_main_pk_mute_remote
                                : R.drawable.voice_chat_demo_main_pk_unmute_remote);
                    }

                    @Override
                    public void onError(int errorCode, String message) {
                        mMutingPeerAnchor = false;
                        String msg = mPeerAnchorMuted ? "解除远端主播静音失败:" : "静音远端主播失败:";
                        SafeToast.show(msg + errorCode + "," + message);
                    }
                });

            });
        }
        return view;
    }

    private String getLocalUserName() {
        if (getSelfUserInfo() != null && getSelfUserInfo().isHost()) {
            return getSelfUserInfo().userName;
        }
        if (getHostUserInfo() != null) {
            return getHostUserInfo().userName;
        }
        return "";
    }

    private void addLocalVideo() {
        if (getSelfUserInfo() == null || TextUtils.isEmpty(getSelfUserInfo().userId)) {
            return;
        }
        TextureView localVideoView = VideoChatRTCManager.ins().getUserRenderView(getSelfUserInfo().userId);
        Utilities.removeFromParent(localVideoView);
        mLocalVideoContainer.removeAllViews();
        mLocalVideoContainer.addView(localVideoView, new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
    }

    private void addSelfAnchorVideo() {
        if (getHostUserInfo() == null || TextUtils.isEmpty(getHostUserInfo().userId)) {
            return;
        }
        TextureView remoteVideoView = new TextureView(getContext());
        VideoChatRTCManager.ins().setRemoteVideoView(getHostUserInfo().userId, remoteVideoView);
        mLocalVideoContainer.removeAllViews();
        mLocalVideoContainer.addView(remoteVideoView, new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
    }

    private void addRemoteAnchorVideo() {
        if (TextUtils.isEmpty(mPeerUid)) {
            return;
        }
        TextureView remoteVideoView = new TextureView(getContext());
        VideoChatRTCManager.ins().setRemoteVideoView(mPeerUid, remoteVideoView);
        mRemoteVideoContainer.removeAllViews();
        mRemoteVideoContainer.addView(remoteVideoView, new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        stopForwardStream();
        SolutionDemoEventManager.unregister(this);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onManageOtherAnchor(ManageOtherAnchorBroadcast event) {
        Log.i(TAG, "onManageOtherAnchor event:" + event);
        if (TextUtils.equals(event.otherAnchorUid, mPeerUid) && !mSelfMutePeerAnchor) {
            mPeerAnchorMuted = event.type == VideoChatDataManager.TYPE_MUTE;
            mMuteRemoteIv.setImageResource(mPeerAnchorMuted
                    ? R.drawable.voice_chat_demo_main_pk_mute_remote
                    : R.drawable.voice_chat_demo_main_pk_unmute_remote);
            if (getSelfUserInfo() != null && !getSelfUserInfo().isHost()
                    && TextUtils.equals(event.otherAnchorUid, mPeerUid)) {
                VideoChatRTCManager.ins().muteRemoteAudio(mPeerUid, mPeerAnchorMuted);
            }
        }
        if (mSelfMutePeerAnchor) {
            mSelfMutePeerAnchor = false;
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUserJoined(UserJoinedBroadcast event) {
        Log.i(TAG, "onUserJoined event:" + event);
        if (TextUtils.equals(event.userInfo.getUid(), mPeerUid)) {
            addRemoteAnchorVideo();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaChangedBroadcast(MediaChangedBroadcast event) {
        Log.i(TAG, "onMediaChangedBroadcast event:" + event);
        if (event == null || event.userInfo == null || TextUtils.isEmpty(event.userInfo.userId)) {
            return;
        }
        Drawable drawable = event.userInfo.mic == 1 ? null : ContextCompat.getDrawable(Utilities.getApplicationContext(), R.drawable.mic_off_1x);
        if (TextUtils.equals(event.userInfo.userId, mPeerUid)) {
            mRemoteNameTv.setCompoundDrawablesWithIntrinsicBounds(null, null, drawable, null);
            mRemoteVideoContainer.setVisibility(event.userInfo.camera == 1 ? View.VISIBLE : View.INVISIBLE);
            return;
        }
        if (getHostUserInfo() != null && TextUtils.equals(getHostUserInfo().userId, event.userInfo.userId)) {
            mLocalNameTv.setCompoundDrawablesWithIntrinsicBounds(null, null, drawable, null);
            mLocalVideoContainer.setVisibility(event.userInfo.camera == 1 ? View.VISIBLE : View.INVISIBLE);
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onNetStatus(NetStatusBroadcast stats) {
        if (TextUtils.equals(stats.uid, mPeerUid)) {
            updateNetStatus(mRemoteStatusTv, stats.txQuality);
            return;
        }
        //自己端主播
        if (getHostUserInfo() != null
                && TextUtils.equals(stats.uid, getHostUserInfo().userId)) {
            updateNetStatus(mLocalStatusTv, stats.txQuality);
        }
    }

    public String getPeerUid() {
        return mPeerUid;
    }

    public String getPeerUname() {
        return TextUtils.isEmpty(mPeerUname) ? "" : mPeerUname;
    }

    private VCUserInfo getHostUserInfo() {
        return VideoChatDataManager.ins().hostUserInfo;
    }

    private VCUserInfo getSelfUserInfo() {
        return VideoChatDataManager.ins().selfUserInfo;
    }

    private void updateNetStatus(TextView textView, int networkQuality) {
        if (textView == null) {
            return;
        }
        boolean good = networkQuality == NetworkQuality.NETWORK_QUALITY_GOOD ||
                networkQuality == NetworkQuality.NETWORK_QUALITY_EXCELLENT;
        textView.setText(good ? R.string.network_good : R.string.network_bad);
        Drawable netStatusDrawable = ContextCompat.getDrawable(Utilities.getApplicationContext(), good ? R.drawable.net_status_good : R.drawable.net_status_bad);
        textView.setCompoundDrawablesWithIntrinsicBounds(netStatusDrawable, null, null, null);
    }

}
