/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.feature.roommain;

import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.INTERACT_STATUS_NORMAL;
import static com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager.SEAT_STATUS_UNLOCKED;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo.ROOM_STATUS_CHATTING;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo.ROOM_STATUS_LIVING;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo.ROOM_STATUS_PK_ING;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_INTERACT;
import static com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo.USER_STATUS_NORMAL;
import static com.volcengine.vertcdemo.videochatdemo.feature.roommain.AudienceManagerDialog.SEAT_ID_BY_SERVER;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.util.ArrayMap;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.common.InputTextDialogFragment;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.annotation.CameraStatus;
import com.volcengine.vertcdemo.core.annotation.MicStatus;
import com.volcengine.vertcdemo.core.eventbus.SocketConnectEvent;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.rtm.RTSBizResponse;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.CommonDialog;
import com.volcengine.vertcdemo.videochatdemo.bean.AnchorInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.AnchorPkFinishBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.AudienceApplyBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.AudienceChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.ClearUserBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.CloseChatRoomBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.FinishLiveBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.InteractChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.InteractInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.InteractResultBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.InviteAnchorBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.InviteAnchorReplyBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.JoinRoomResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.MediaChangedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.MessageBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.ReceivedInteractBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.ReplyAnchorsResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.ReplyResponse;
import com.volcengine.vertcdemo.videochatdemo.bean.VCRoomInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCSeatInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.common.VideoChatSettingDialog;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatDataManager;
import com.volcengine.vertcdemo.videochatdemo.core.VideoChatRTCManager;
import com.volcengine.vertcdemo.videochatdemo.core.event.AudioStatsEvent;
import com.volcengine.vertcdemo.videochatdemo.feature.createroom.effect.VideoEffectDialog;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.fragment.VideoAnchorPkFragment;
import com.volcengine.vertcdemo.videochatdemo.feature.roommain.fragment.VideoChatRoomFragment;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.util.Map;
import java.util.concurrent.TimeUnit;

public class VideoChatRoomMainActivity extends BaseActivity {

    private static final String TAG = "VideoChatRoom";
    private static final String TAG_FRAGMENT_CHAT_ROOM = "fragment_chat_room";
    private static final String TAG_FRAGMENT_ANCHOR_PK = "fragment_anchor_pk";
    private static final String REFER_KEY = "refer";
    private static final String REFER_FROM_CREATE = "create";
    private static final String REFER_FROM_LIST = "list";
    private static final String REFER_EXTRA_ROOM = "extra_room";
    private static final String REFER_EXTRA_USER = "extra_user";
    private static final String REFER_EXTRA_CREATE_JSON = "extra_create_json";

    // 房主信息
    private TextView mHostPrefixNameTv;
    private TextView mHostNameTv;
    private TextView mHostIDTv;

    private View mTopTip;
    private TextView mAudienceCountTv;
    private TextView mLocalAnchorNameTv;
    private FrameLayout mLocalAnchorNameFl;
    private ImageView mLeaveIv;
    private FrameLayout mLocalLiveFl;
    private FrameLayout mBizFl;
    private VideoChatBottomOptionLayout mBottomOptionLayout;
    private RecyclerView mVCChatRv;
    private boolean mAgreeHostInvite;

    private VCChatAdapter mVCChatAdapter;
    private boolean isLeaveByKickOut = false;
    private VideoChatRoomFragment mVideoChatFragment;
    private VideoAnchorPkFragment mVideoPkFragment;
    private final Handler mHandler = new Handler(Looper.getMainLooper());

    private boolean mSelfEndPk = false;

    private final IRequestCallback<JoinRoomResponse> mJoinCallback = new IRequestCallback<JoinRoomResponse>() {
        @Override
        public void onSuccess(JoinRoomResponse data) {
            data.isFromCreate = true;
            initViewWithData(data);
        }

        @Override
        public void onError(int errorCode, String message) {
            if (errorCode == 422) {
                message = getString(R.string.room_not_exist);
            }
            onArgsError(message);
        }
    };

    private final IRequestCallback<RTSBizResponse> mSendMessageCallback = new IRequestCallback<RTSBizResponse>() {
        @Override
        public void onSuccess(RTSBizResponse data) {

        }

        @Override
        public void onError(int errorCode, String message) {

        }
    };

    private final IRequestCallback<RTSBizResponse> mFinishCallback = new IRequestCallback<RTSBizResponse>() {
        @Override
        public void onSuccess(RTSBizResponse data) {

        }

        @Override
        public void onError(int errorCode, String message) {

        }
    };

    private final IRequestCallback<RTSBizResponse> mLeaveCallback = new IRequestCallback<RTSBizResponse>() {
        @Override
        public void onSuccess(RTSBizResponse data) {

        }

        @Override
        public void onError(int errorCode, String message) {

        }
    };

    private final AudienceManagerDialog.ICloseChatRoom mCloseChatRoom = new AudienceManagerDialog.ICloseChatRoom() {
        @Override
        public void closeChatRoom() {
            CommonDialog dialog = new CommonDialog(VideoChatRoomMainActivity.this);
            dialog.setMessage(getString(R.string.close_room_mode));
            dialog.setPositiveBtnText(R.string.btn_confirm);
            dialog.setPositiveListener(v -> {
                VideoChatRTCManager.ins().getRTMClient().closeChatRoom(
                        VideoChatDataManager.ins().hostUserInfo.roomId,
                        VideoChatDataManager.ins().hostUserInfo.userId,
                        new IRequestCallback<RTSBizResponse>() {
                            @Override
                            public void onSuccess(RTSBizResponse data) {
                                mBizFl.post(VideoChatRoomMainActivity.this::closeChat);
                            }

                            @Override
                            public void onError(int errorCode, String message) {
                                Log.i(TAG, "closeChatRoom onError errorCode:" + errorCode + ",message:" + message);
                            }
                        });
                dialog.dismiss();
            });
            dialog.setNegativeListener(v -> {
                dialog.dismiss();
            });
            dialog.show();
        }
    };

    private final IRequestCallback<JoinRoomResponse> mReconnectCallback = new IRequestCallback<JoinRoomResponse>() {
        @Override
        public void onSuccess(JoinRoomResponse data) {
            data.isFromCreate = false;
            initViewWithData(data);
        }

        @Override
        public void onError(int errorCode, String message) {
            finish();
        }
    };

    private final VideoChatBottomOptionLayout.IBottomOptions mIBottomOptions = new VideoChatBottomOptionLayout.IBottomOptions() {
        @Override
        public void onInputClick() {
            openInput();
        }

        @Override
        public void onPkClick() {
            if (getRoomInfo().status == ROOM_STATUS_CHATTING) {
                SafeToast.show(R.string.invite_user_busy);
                return;
            }
            if (VideoChatDataManager.ins().selfInviteStatus == VideoChatDataManager.INTERACT_STATUS_INVITING_CHAT) {
                SafeToast.show(R.string.invite_user_busy);
                return;
            }
            if (VideoChatDataManager.ins().selfInviteStatus == VideoChatDataManager.INTERACT_STATUS_INVITING_PK) {
                SafeToast.show(R.string.have_sent_invite_txt);
                return;
            }
            if (getRoomInfo().status == ROOM_STATUS_PK_ING) {
                CommonDialog dialog = new CommonDialog(VideoChatRoomMainActivity.this);
                dialog.setMessage(getString(R.string.inviting_confirm_end_txt));
                dialog.setPositiveBtnText(R.string.btn_confirm);
                dialog.setPositiveListener(v -> {
                    mSelfEndPk = true;
                    VideoChatRTCManager.ins().getRTMClient().finishAnchorInteract(getRoomInfo().roomId,
                            new IRequestCallback<RTSBizResponse>() {
                                @Override
                                public void onSuccess(RTSBizResponse data) {
                                    Log.i(TAG, "onPkClick mVideoPkFragment:" + mVideoPkFragment);
                                    if (mVideoPkFragment != null) {
                                        SafeToast.show(getString(R.string.removed_from_co_host, mVideoPkFragment.getPeerUname()));
                                    }
                                    closePk();
                                    dialog.dismiss();
                                }

                                @Override
                                public void onError(int errorCode, String message) {
                                    dialog.dismiss();
                                }
                            });
                });
                dialog.setNegativeListener(v -> dialog.dismiss());
                dialog.show();
                return;
            }
            RemoteAnchorsManagerDialog dialog = new RemoteAnchorsManagerDialog(VideoChatRoomMainActivity.this);
            dialog.show();
        }

        @Override
        public void onInteractClick() {
            boolean isHost = getSelfUserInfo() != null && getSelfUserInfo().isHost();
            if (getSelfInteractStatus() == VideoChatDataManager.INTERACT_STATUS_INVITING_PK) {
                SafeToast.show(R.string.invite_user_busy);
                return;
            }
            if (VideoChatDataManager.ins().selfInviteStatus == VideoChatDataManager.INTERACT_STATUS_INVITING_CHAT && !isHost) {
                SafeToast.show(R.string.already_send_application_msg);
                return;
            }
            if (getRoomInfo().status == ROOM_STATUS_PK_ING) {
                SafeToast.show(R.string.co_host_busy);
                return;
            }
            if (isHost) {
                AudienceManagerDialog dialog = new AudienceManagerDialog(VideoChatRoomMainActivity.this);
                dialog.setData(getRoomInfo().roomId, VideoChatDataManager.ins().hasNewApply(), SEAT_ID_BY_SERVER);
                dialog.setICloseChatRoom(mCloseChatRoom);
                dialog.show();
                return;
            }
            int selfStatus = getSelfUserInfo() != null ? getSelfUserInfo().userStatus : USER_STATUS_NORMAL;
            if (selfStatus == VCUserInfo.USER_STATUS_APPLYING) {
                SafeToast.show(R.string.already_send_application_msg);
            } else if (selfStatus == USER_STATUS_INTERACT) {
                SafeToast.show(R.string.already_co_host_msg);
            } else if (selfStatus == USER_STATUS_NORMAL) {
                SeatOptionDialog dialog = new SeatOptionDialog(VideoChatRoomMainActivity.this);
                VCSeatInfo seatInfo = new VCSeatInfo();
                seatInfo.userInfo = null;
                seatInfo.seatIndex = SEAT_ID_BY_SERVER;
                seatInfo.status = SEAT_STATUS_UNLOCKED;
                dialog.setData(getRoomInfo().roomId, seatInfo, getSelfUserInfo().userRole, getSelfUserInfo().userStatus);
                dialog.setICloseChatRoom(mCloseChatRoom);
                dialog.show();
            }
        }

        public void onBGMClick() {
            VideoChatBGMSettingDialog dialog = new VideoChatBGMSettingDialog(VideoChatRoomMainActivity.this);
            dialog.setData(VideoChatDataManager.ins().getBGMOpening(),
                    VideoChatDataManager.ins().getBGMVolume(),
                    VideoChatDataManager.ins().getUserVolume());
            dialog.show();
        }

        @Override
        public void onEffectClick() {
            new VideoEffectDialog(VideoChatRoomMainActivity.this).show();
        }

        @Override
        public void onSettingsClick() {
            new VideoChatSettingDialog(VideoChatRoomMainActivity.this,
                    getSelfUserInfo().isHost(),
                    getRoomInfo().roomId,
                    obj -> onBGMClick()).show();
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_class_video_chat_demo_main);
        SolutionDemoEventManager.register(this);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();
        findViewById(R.id.video_chat_main_root).setOnClickListener((v) -> {
            closeInput();
        });
        mTopTip = findViewById(R.id.main_disconnect_tip);
        mHostPrefixNameTv = findViewById(R.id.video_chat_main_title_tv1);
        mHostNameTv = findViewById(R.id.video_chat_main_title_tv2);
        mHostIDTv = findViewById(R.id.video_chat_main_title_tv3);
        mLeaveIv = findViewById(R.id.leave_iv);
        mLeaveIv.setOnClickListener(v -> attemptLeave());
        mAudienceCountTv = findViewById(R.id.voice_chat_demo_main_audience_num);
        mLocalAnchorNameFl = findViewById(R.id.local_anchor_name_fl);
        mLocalAnchorNameTv = findViewById(R.id.local_name_tv);

        mLocalLiveFl = findViewById(R.id.local_live_fl);
        mBizFl = findViewById(R.id.biz_fl);

        mBottomOptionLayout = findViewById(R.id.voice_chat_demo_main_bottom_option);
        mBottomOptionLayout.setOptionCallback(mIBottomOptions);

        mVCChatAdapter = new VCChatAdapter();
        mVCChatRv = findViewById(R.id.voice_chat_demo_main_chat_rv);
        mVCChatRv.setLayoutManager(new LinearLayoutManager(VideoChatRoomMainActivity.this, RecyclerView.VERTICAL, false));
        mVCChatRv.setAdapter(mVCChatAdapter);
        mVCChatRv.setOnClickListener((v) -> closeInput());

        closeInput();
        if (!checkArgs()) {
            onArgsError(getString(R.string.back_to_room_list));
        }
    }

    private boolean checkArgs() {
        Intent intent = getIntent();
        if (intent == null) {
            return false;
        }
        String refer = intent.getStringExtra(REFER_KEY);
        String roomJson = intent.getStringExtra(REFER_EXTRA_ROOM);
        String selfJson = intent.getStringExtra(REFER_EXTRA_USER);
        VCRoomInfo roomInfo = GsonUtils.gson().fromJson(roomJson, VCRoomInfo.class);
        VCUserInfo selfInfo = GsonUtils.gson().fromJson(selfJson, VCUserInfo.class);
        if (TextUtils.equals(refer, REFER_FROM_LIST)) {
            VideoChatRTCManager.ins().getRTMClient().requestJoinRoom(selfInfo.userName, roomInfo.roomId, mJoinCallback);
            return true;
        } else if (TextUtils.equals(refer, REFER_FROM_CREATE)) {
            String createJson = intent.getStringExtra(REFER_EXTRA_CREATE_JSON);
            if (TextUtils.isEmpty(createJson)) {
                return false;
            }
            JoinRoomResponse createResponse = GsonUtils.gson().fromJson(createJson, JoinRoomResponse.class);
            initViewWithData(createResponse);
            return true;
        } else {
            return false;
        }
    }

    private void initViewWithData(JoinRoomResponse data) {
        mAudienceCountTv.setText(String.valueOf(data.audienceCount + 1));
        VideoChatDataManager.ins().roomInfo = data.roomInfo;
        VideoChatDataManager.ins().hostUserInfo = data.hostInfo;
        VideoChatDataManager.ins().selfUserInfo = data.userInfo;
        String appId = data.roomInfo.appId;
        if (data.isFromCreate) {
            VideoChatRTCManager.ins().joinRoom(data.roomInfo.roomId, data.rtcToken, data.userInfo.userId, data.userInfo.isHost());
        }
        String hostNamePrefix = getRoomInfo().hostUserName.substring(0, 1);
        mHostPrefixNameTv.setText(hostNamePrefix);
        mHostNameTv.setText(getRoomInfo().hostUserName);
        mLocalAnchorNameTv.setText(hostNamePrefix);
        mHostIDTv.setText("ID:" + getRoomInfo().roomId);
        mBottomOptionLayout.updateUIByRoleAndStatus(data.roomInfo.status, data.userInfo.userRole, data.userInfo.userStatus);

        int roomStatus = data.roomInfo.status;
        if (roomStatus == ROOM_STATUS_CHATTING) {//已经在聊天中，自己只能是观众
            boolean isSelfHost = TextUtils.equals(data.userInfo.userId, getHostUserInfo().userId);
            boolean isInteract = data.userInfo.userStatus == USER_STATUS_INTERACT;
            VideoChatRTCManager.ins().startAudioCapture(isSelfHost || isInteract);
            VideoChatRTCManager.ins().startMuteAudio(!data.userInfo.isMicOn());
            if (isSelfHost || isInteract) {
                VideoChatRTCManager.ins().startVideoCapture(true);
            }
            startChatRoom(data);
        } else if (roomStatus == VCRoomInfo.ROOM_STATUS_PK_ING) {//已经PK中，自己只能是观众
            if (data.anchorList == null || data.anchorList.size() != 2) {
                Log.i(TAG, "anchors or hostInfo is null!!");
                finish();
                return;
            }
            AnchorInfo peerAnchor = null;
            AnchorInfo localAnchor = null;
            for (AnchorInfo info : data.anchorList) {
                if (info == null) continue;
                if (TextUtils.equals(info.userId, getHostUserInfo().userId)) {
                    localAnchor = info;
                } else {
                    peerAnchor = info;
                }
            }
            if (peerAnchor != null && localAnchor != null) {
                startPk(peerAnchor, localAnchor, null);
            }
        } else if (roomStatus == VCRoomInfo.ROOM_STATUS_LIVING) {
            if (getSelfUserInfo() != null && getSelfUserInfo().isHost()) {
                VideoChatRTCManager.ins().startAudioCapture(true);
                VideoChatRTCManager.ins().startMuteAudio(!data.userInfo.isMicOn());
                VideoChatRTCManager.ins().startVideoCapture(true);
            }
            setLocalLive();
        }
    }

    private void startChatRoom(JoinRoomResponse data) {
        mVideoChatFragment = new VideoChatRoomFragment();
        mVideoChatFragment.setICloseChatRoom(mCloseChatRoom);
        Bundle args = new Bundle();
        args.putParcelable(VideoChatRoomFragment.KEY_JOIN_DATA, data);
        mVideoChatFragment.setArguments(args);
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction()
                .add(R.id.biz_fl, mVideoChatFragment, TAG_FRAGMENT_CHAT_ROOM)
                .commit();
        mLocalLiveFl.removeAllViews();
        mLocalAnchorNameFl.setVisibility(View.GONE);
    }

    private void setLocalLive() {
        final VCUserInfo userInfo = getHostUserInfo();
        TextureView renderView = VideoChatRTCManager.ins().getUserRenderView(userInfo.userId);
        Utilities.removeFromParent(renderView);
        if (getSelfUserInfo() != null && getSelfUserInfo().isHost()) {
            VideoChatRTCManager.ins().setLocalVideoView(renderView);
        } else {
            VideoChatRTCManager.ins().setRemoteVideoView(userInfo.roomId, userInfo.userId, renderView);
        }
        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        mLocalLiveFl.addView(renderView, params);
        if (userInfo.camera == VCUserInfo.CAMERA_STATUS_OFF) {
            mLocalAnchorNameFl.setVisibility(View.VISIBLE);
        }
    }

    @Override
    public void onBackPressed() {
        attemptLeave();
    }

    @Override
    public void finish() {
        super.finish();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        closeInput();
        VideoChatDataManager.ins().clearData();
        SolutionDemoEventManager.unregister(this);
        VideoChatRTCManager.ins().leaveRoom();
        VideoChatRTCManager.ins().startAudioMixing(false);
        VideoChatRTCManager.ins().startVideoCapture(false);
        VideoChatRTCManager.ins().startAudioCapture(false);
        if (getSelfUserInfo() == null || getRoomInfo() == null) {
            return;
        }
        if (isLeaveByKickOut) {
            return;
        }
        if (getSelfUserInfo().isHost()) {
            VideoChatRTCManager.ins().getRTMClient().requestFinishLive(getRoomInfo().roomId, mFinishCallback);
        } else {
            VideoChatRTCManager.ins().getRTMClient().requestLeaveRoom(getRoomInfo().roomId, mLeaveCallback);
        }
    }

    private void onArgsError(String message) {
        CommonDialog dialog = new CommonDialog(this);
        dialog.setMessage(message);
        dialog.setCancelable(false);
        dialog.setPositiveListener((v) -> {
            finish();
            dialog.dismiss();
        });
        dialog.show();
    }

    private void attemptLeave() {
        if (getSelfUserInfo() == null || !getSelfUserInfo().isHost()) {
            SafeToast.show(R.string.you_has_audience_txt);
            finish();
            return;
        }
        CommonDialog dialog = new CommonDialog(this);
        dialog.setMessage(getString(R.string.confirm_end_live));
        dialog.setPositiveListener((v) -> {
            finish();
            dialog.dismiss();
        });
        dialog.setPositiveBtnText(R.string.confirm_end_live_btn_txt);
        dialog.setNegativeListener((v) -> dialog.dismiss());
        dialog.show();
    }

    /**
     * 打开聊天消息输入对话框
     */
    public void openInput() {
        InputTextDialogFragment.showInput(getSupportFragmentManager(), (this::onSendMessage));
    }


    private void onSendMessage(InputTextDialogFragment fragment, String message) {
        if (getRoomInfo() == null) {
            return;
        }
        if (TextUtils.isEmpty(message)) {
            SafeToast.show(R.string.add_comments);
            return;
        }
        closeInput();
        onReceivedMessage(String.format("%s : %s", getSelfUserInfo().userName, message));
        try {
            message = URLEncoder.encode(message, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        VideoChatRTCManager.ins().getRTMClient().sendMessage(getRoomInfo().roomId, message, mSendMessageCallback);
        fragment.dismiss();
    }

    /**
     * 关闭聊天消息发送
     */
    public void closeInput() {
        IMEUtils.closeIME(mVCChatRv);
    }

    private void onReceivedMessage(String message) {
        mVCChatAdapter.addChatMsg(message);
        mVCChatRv.post(() -> mVCChatRv.smoothScrollToPosition(mVCChatAdapter.getItemCount()));
    }

    private void showTopTip() {
        mTopTip.setVisibility(View.VISIBLE);
    }

    private void hideTopTip() {
        mTopTip.setVisibility(View.GONE);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudienceChangedBroadcast(AudienceChangedBroadcast event) {
        String msg = getString(event.isJoin ? R.string.user_enter_room : R.string.user_exit_room, event.userInfo.userName);
        onReceivedMessage(msg);
        mAudienceCountTv.setText(String.valueOf(event.audienceCount + 1));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onFinishLiveBroadcast(FinishLiveBroadcast event) {
        if (getRoomInfo() == null || !TextUtils.equals(event.roomId, getRoomInfo().roomId)) {
            return;
        }
        String message = null;
        boolean isHost = getSelfUserInfo() != null && getSelfUserInfo().isHost();
        if (event.type == FinishLiveBroadcast.FINISH_TYPE_AGAINST) {
            message = getString(R.string.room_close_cause_by_violations);
        } else if (event.type == FinishLiveBroadcast.FINISH_TYPE_TIMEOUT && isHost) {
            message = getString(R.string.live_exceed_time);
        } else if (!isHost) {
            message = getString(R.string.live_ended_txt);
        }
        if (!TextUtils.isEmpty(message)) {
            SafeToast.show(message);
        }
        finish();
    }


    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCloseChatRoomBroadcast(CloseChatRoomBroadcast event) {
        boolean chatVisible = mVideoChatFragment != null && mVideoChatFragment.isVisible();
        Log.i(TAG, "onCloseChatRoomBroadcast event:" + event + ",chatVisible:" + chatVisible);
        if (!chatVisible) {
            return;
        }
        if (getRoomInfo() == null || !TextUtils.equals(event.roomId, getRoomInfo().roomId)) {
            return;
        }
        if (!getSelfUserInfo().isHost()) {
            SafeToast.show(R.string.co_host_left);
        }
        mBizFl.post(VideoChatRoomMainActivity.this::closeChat);
        if (!getSelfUserInfo().isHost()) {
            VideoChatRTCManager.ins().startMuteAudio(true);
        }
    }

    private void closeChat() {
        if (mVideoChatFragment == null || !mVideoChatFragment.isVisible()) {
            Log.i(TAG, "mVideoChatFragment un visible");
            return;
        }
        getRoomInfo().status = ROOM_STATUS_LIVING;
        getSelfUserInfo().userStatus = USER_STATUS_NORMAL;
        VideoChatDataManager.ins().selfInviteStatus = INTERACT_STATUS_NORMAL;
        mBottomOptionLayout.updateUIByRoleAndStatus(ROOM_STATUS_LIVING, getSelfUserInfo().userRole, USER_STATUS_NORMAL);
        FragmentManager fragmentManager = getSupportFragmentManager();
        Fragment videoChatFragment = fragmentManager.findFragmentByTag(TAG_FRAGMENT_CHAT_ROOM);
        if (videoChatFragment == mVideoChatFragment && videoChatFragment != null) {
            fragmentManager.beginTransaction()
                    .remove(videoChatFragment)
                    .commitAllowingStateLoss();
            Log.i(TAG, "closeChat remove ChatFragment");
            mBizFl.removeAllViews();
            mVideoChatFragment = null;
        }
        setLocalLive();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMessageBroadcast(MessageBroadcast event) {
        if (TextUtils.equals(event.userInfo.userId, getSelfUserInfo().userId)) {
            return;
        }
        String message;
        try {
            message = URLDecoder.decode(event.message, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            message = event.message;
        }
        onReceivedMessage(String.format("%s : %s", event.userInfo.userName, message));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractChangedBroadcast(InteractChangedBroadcast event) {
        Log.i(TAG, "onInteractChangedBroadcast:" + event + ",mAgreeHostInvite:" + mAgreeHostInvite);
        if (mAgreeHostInvite) {
            return;
        }
        VCSeatInfo info = new VCSeatInfo();
        info.userInfo = event.userInfo;
        info.status = SEAT_STATUS_UNLOCKED;
        String msg = event.isStart ? getString(R.string.user_become_co_host_txt, event.userInfo.userName) : getString(R.string.user_become_audi_txt, event.userInfo.userName);
        onReceivedMessage(msg);
        boolean isSelf = TextUtils.equals(SolutionDataManager.ins().getUserId(), event.userInfo.userId);
        if (isSelf) {
            getSelfUserInfo().userStatus = event.isStart ? USER_STATUS_INTERACT : USER_STATUS_NORMAL;
        }
        mBottomOptionLayout.updateUIByRoleAndStatus(ROOM_STATUS_CHATTING, getSelfUserInfo().userRole, getSelfUserInfo().userStatus);
        if (event.isStart && getRoomInfo().status != ROOM_STATUS_CHATTING) {
            getRoomInfo().status = ROOM_STATUS_CHATTING;
            VideoChatDataManager.ins().selfInviteStatus = INTERACT_STATUS_NORMAL;
            JoinRoomResponse response = new JoinRoomResponse();
            response.roomInfo = getRoomInfo();
            response.userInfo = getSelfUserInfo();
            response.hostInfo = getHostUserInfo();
            Map<Integer, VCSeatInfo> seatMap = new ArrayMap<>(1);
            seatMap.put(event.seatId, info);
            response.seatMap = seatMap;
            startChatRoom(response);
            mBizFl.post(() -> {
                mVideoChatFragment.onInteractChangedBroadcast(event);
            });
        }
    }

    private CommonDialog mInviteInteractDialog;
    private final Runnable mCloseInviteInteractDialogTask = () -> {
        if (mInviteInteractDialog != null) {
            mInviteInteractDialog.dismiss();
        }
    };

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onReceivedInteractBroadcast(ReceivedInteractBroadcast event) {
        int oldRoomStatus = getRoomInfo().status;
        Log.i(TAG, "onReceivedInteractBroadcast:" + event + ",oldRoomStatus:" + oldRoomStatus);
        mInviteInteractDialog = new CommonDialog(this);
        mInviteInteractDialog.setMessage(getString(R.string.invitation_to_be_co_host));
        mInviteInteractDialog.setPositiveBtnText(R.string.accept);
        mInviteInteractDialog.setPositiveListener((v) -> {
            mAgreeHostInvite = true;
            VideoChatRTCManager.ins().getRTMClient().replyInvite(
                    getRoomInfo().roomId,
                    VideoChatDataManager.REPLY_TYPE_ACCEPT,
                    event.seatId,
                    new IRequestCallback<ReplyResponse>() {
                        @Override
                        public void onSuccess(ReplyResponse data) {
                            mAgreeHostInvite = false;
                            getRoomInfo().status = ROOM_STATUS_CHATTING;
                            VideoChatDataManager.ins().selfInviteStatus = INTERACT_STATUS_NORMAL;
                            mBottomOptionLayout.updateUIByRoleAndStatus(ROOM_STATUS_CHATTING, getSelfUserInfo().userRole, USER_STATUS_INTERACT);
                            if (oldRoomStatus == ROOM_STATUS_CHATTING) {
                                return;
                            }
                            JoinRoomResponse response = new JoinRoomResponse();
                            VCUserInfo selfUserInfo = getSelfUserInfo();
                            selfUserInfo.userStatus = USER_STATUS_INTERACT;
                            response.roomInfo = getRoomInfo();
                            response.userInfo = getSelfUserInfo();
                            response.hostInfo = getHostUserInfo();
                            Map<Integer, VCSeatInfo> seatMap = new ArrayMap<>(1);
                            VCSeatInfo seatInfo = new VCSeatInfo();
                            seatInfo.userInfo = getSelfUserInfo();
                            seatInfo.seatIndex = event.seatId;
                            seatMap.put(event.seatId, seatInfo);
                            response.seatMap = seatMap;
                            startChatRoom(response);
                            mBizFl.post(() -> {
                                InteractChangedBroadcast info = new InteractChangedBroadcast();
                                info.isStart = true;
                                info.userInfo = getSelfUserInfo();
                                info.seatId = event.seatId;
                                mVideoChatFragment.onInteractChangedBroadcast(info);
                            });
                        }

                        @Override
                        public void onError(int errorCode, String message) {
                            mAgreeHostInvite = false;
                            VideoChatDataManager.ins().selfInviteStatus = INTERACT_STATUS_NORMAL;
                            Log.i(TAG, "replyInvite onError errorCode:" + errorCode + ",message:" + message);
                            if (errorCode == 506) {
                                SafeToast.show(R.string.all_seats_filled_up_txt);
                            }
                        }
                    });
            mInviteInteractDialog.dismiss();
            mHandler.removeCallbacks(mCloseInviteInteractDialogTask);
        });
        mInviteInteractDialog.setNegativeBtnText(R.string.btn_decline);
        mInviteInteractDialog.setNegativeListener((v) -> {
            VideoChatRTCManager.ins().getRTMClient().replyInvite(
                    getRoomInfo().roomId,
                    VideoChatDataManager.REPLY_TYPE_REJECT,
                    event.seatId,
                    new IRequestCallback<ReplyResponse>() {
                        @Override
                        public void onSuccess(ReplyResponse data) {
                        }

                        @Override
                        public void onError(int errorCode, String message) {
                        }
                    });
            mInviteInteractDialog.dismiss();
            mHandler.removeCallbacks(mCloseInviteInteractDialogTask);
        });
        mInviteInteractDialog.show();
        mHandler.postDelayed(mCloseInviteInteractDialogTask, TimeUnit.SECONDS.toMillis(5));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudienceApplyBroadcast(AudienceApplyBroadcast event) {
        VideoChatDataManager.ins().setNewApply(event.hasNewApply);
        mBottomOptionLayout.updateDotTip(event.hasNewApply);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onClearUserBroadcast(ClearUserBroadcast event) {
        if (TextUtils.equals(getRoomInfo().roomId, event.roomId) &&
                TextUtils.equals(SolutionDataManager.ins().getUserId(), event.userId)) {
            SafeToast.show(R.string.you_force_log_out);
            isLeaveByKickOut = true;
            finish();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAudioStatsEvent(AudioStatsEvent event) {
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInteractResultBroadcast(InteractResultBroadcast event) {
        Log.i(TAG, "onInteractResultBroadcast event:" + event);
        VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_NORMAL;
        if (event.reply == VideoChatDataManager.REPLY_TYPE_REJECT) {
            SafeToast.show(getString(R.string.video_user_decline_you_invite, event.userInfo.userName));
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMediaChangedBroadcast(MediaChangedBroadcast event) {
        Log.i(TAG, "MediaChangedBroadcast event:" + event);
        String hostUid = getHostUserInfo() == null ? null : getHostUserInfo().userId;
        if (TextUtils.equals(hostUid, event.userInfo.userId)) {
            getHostUserInfo().mic = event.userInfo.mic;
            getHostUserInfo().camera = event.userInfo.camera;
            if (getRoomInfo().status == ROOM_STATUS_LIVING) {
                if (event.userInfo.camera == VCUserInfo.CAMERA_STATUS_OFF) {
                    mLocalLiveFl.setVisibility(View.GONE);
                    mLocalAnchorNameFl.setVisibility(View.VISIBLE);
                } else if (event.userInfo.camera == VCUserInfo.CAMERA_STATUS_ON) {
                    mLocalLiveFl.setVisibility(View.VISIBLE);
                    mLocalAnchorNameFl.setVisibility(View.GONE);
                }
            }
        }
        if (mVideoChatFragment != null && mVideoChatFragment.isVisible()) {
            mVideoChatFragment.onMediaChangedBroadcast(event);
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (event.status == SocketConnectEvent.ConnectStatus.DISCONNECTED) {
            showTopTip();
        } else if (event.status == SocketConnectEvent.ConnectStatus.RECONNECTED) {
            Log.i(TAG, "onSocketConnectEvent event:" + event);
            VideoChatRTCManager.ins().getRTMClient().reconnectToServer(mReconnectCallback);
        } else if (event.status == SocketConnectEvent.ConnectStatus.CONNECTED) {
            hideTopTip();
        }
    }

    private CommonDialog mOnInviteAnchorDialog;
    private final Runnable mCloseInviteAnchorDialogTask = () -> {
        if (mOnInviteAnchorDialog != null) {
            mOnInviteAnchorDialog.dismiss();
        }
    };

    /***收到主播连麦邀请*/
    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onInviteAnchor(InviteAnchorBroadcast event) {
        Log.i(TAG, "onInviteAnchor event:" + event);
        if (mOnInviteAnchorDialog != null) {
            mOnInviteAnchorDialog.dismiss();
        }
        mOnInviteAnchorDialog = new CommonDialog(this);

        mOnInviteAnchorDialog.setMessage(getString(R.string.invited_you_tobe_co_host, event.fromUserName));
        TextView posBtn = mOnInviteAnchorDialog.findViewById(com.ss.video.rtc.demo.basic_module.R.id.dialog_positive_btn);
        if (posBtn != null) posBtn.setText(R.string.accept);
        TextView negBtn = mOnInviteAnchorDialog.findViewById(com.ss.video.rtc.demo.basic_module.R.id.dialog_negative_btn);
        if (negBtn != null) negBtn.setText(R.string.btn_decline);
        mOnInviteAnchorDialog.setPositiveListener(v -> {
            VideoChatRTCManager.ins().getRTMClient().replyAnchor(
                    VideoChatDataManager.ins().selfUserInfo.roomId,
                    VideoChatDataManager.ins().selfUserInfo.userId,
                    event.fromRoomId, event.fromUserId,
                    1, new IRequestCallback<ReplyAnchorsResponse>() {
                        @Override
                        public void onSuccess(ReplyAnchorsResponse data) {
                            Log.i(TAG, "onInviteAnchor replyAnchor onSuccess:" + data);
                            if (data == null || data.interactInfoList == null
                                    || data.interactInfoList.size() == 0
                                    || data.interactInfoList.get(0) == null) {
                                return;
                            }
                            InteractInfo info = data.interactInfoList.get(0);
                            AnchorInfo peerAnchor = new AnchorInfo();
                            peerAnchor.roomId = info.roomId;
                            peerAnchor.userId = info.userId;
                            peerAnchor.userName = info.userName;
                            peerAnchor.mic = info.mic;
                            peerAnchor.camera = info.camera;
                            peerAnchor.audioStatusThisRoom = 1;
                            AnchorInfo localAnchor = new AnchorInfo();
                            localAnchor.mic = VideoChatRTCManager.ins().isMicOn() ? MicStatus.ON : MicStatus.OFF;
                            localAnchor.camera = VideoChatRTCManager.ins().isCameraOn() ? CameraStatus.ON : CameraStatus.OFF;
                            startPk(peerAnchor, localAnchor, info.token);
                        }

                        @Override
                        public void onError(int errorCode, String message) {
                            Log.i(TAG, "onInviteAnchor replyAnchor onError:" + errorCode + "," + message);
                        }
                    });
            mOnInviteAnchorDialog.cancel();
            mHandler.removeCallbacks(mCloseInviteAnchorDialogTask);
        });
        mOnInviteAnchorDialog.setNegativeListener(v -> {
            VideoChatRTCManager.ins().getRTMClient().replyAnchor(
                    VideoChatDataManager.ins().selfUserInfo.roomId,
                    VideoChatDataManager.ins().selfUserInfo.userId,
                    event.fromRoomId, event.fromUserId,
                    2, null);
            mOnInviteAnchorDialog.cancel();
            mHandler.removeCallbacks(mCloseInviteAnchorDialogTask);
        });
        mOnInviteAnchorDialog.show();
        mHandler.postDelayed(mCloseInviteAnchorDialogTask, TimeUnit.SECONDS.toMillis(5));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    /****收到主播连麦回复*/
    public void onInviteAnchorReply(InviteAnchorReplyBroadcast event) {
        Log.i(TAG, "onInviteAnchorReply event:" + event);
        VideoChatDataManager.ins().selfInviteStatus = VideoChatDataManager.INTERACT_STATUS_NORMAL;
        if (event.reply == VideoChatDataManager.REPLY_TYPE_REJECT) {
            SafeToast.show(getString(R.string.video_user_decline_you_invite, event.toUserName));
        } else if (event.reply == VideoChatDataManager.REPLY_TYPE_ACCEPT) {
            AnchorInfo peerAnchor = new AnchorInfo();
            peerAnchor.roomId = event.toRoomId;
            peerAnchor.userId = event.toUserId;
            peerAnchor.userName = event.toUserName;
            peerAnchor.mic = event.interactInfo.mic;
            peerAnchor.camera = event.interactInfo.camera;
            AnchorInfo localAnchor = new AnchorInfo();
            localAnchor.mic = VideoChatRTCManager.ins().isMicOn() ? MicStatus.ON : MicStatus.OFF;
            localAnchor.camera = VideoChatRTCManager.ins().isCameraOn() ? CameraStatus.ON : CameraStatus.OFF;
            startPk(peerAnchor, localAnchor, event.interactInfo.token);
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAnchorPkFinish(AnchorPkFinishBroadcast event) {
        boolean pkVisible = mVideoPkFragment != null && mVideoPkFragment.isVisible();
        Log.i(TAG, "onAnchorPkFinish event:" + event + ",pkVisible:" + pkVisible);
        if (!pkVisible) {
            return;
        }
        String peerName = "";
        if (mVideoPkFragment != null) {
            peerName = mVideoPkFragment.getPeerUname();
        }
        if (!TextUtils.isEmpty(peerName) && getSelfUserInfo().isHost()) {
            if (mSelfEndPk) {
                SafeToast.show(getString(R.string.removed_from_co_host, peerName));
            } else {
                SafeToast.show(getString(R.string.user_has_left, peerName));
            }
        }
        closePk();

        mSelfEndPk = false;
    }

    private void closePk() {
        boolean pkVisible = mVideoPkFragment != null && mVideoPkFragment.isVisible();
        Log.i(TAG, "closePk pkVisible:" + pkVisible);
        if (!pkVisible) {
            return;
        }
        FragmentManager fragmentManager = getSupportFragmentManager();
        Fragment videoPkFragment = fragmentManager.findFragmentByTag(TAG_FRAGMENT_ANCHOR_PK);
        if (videoPkFragment == mVideoPkFragment && videoPkFragment != null) {
            fragmentManager.beginTransaction()
                    .remove(mVideoPkFragment)
                    .commitAllowingStateLoss();
            mVideoPkFragment = null;
            mBizFl.removeAllViews();
            Log.i(TAG, "closePk remove PkFragment");
        }
        setLocalLive();
        getRoomInfo().status = ROOM_STATUS_LIVING;
        getSelfUserInfo().userStatus = USER_STATUS_NORMAL;
        mBottomOptionLayout.updateUIByRoleAndStatus(ROOM_STATUS_LIVING, getSelfUserInfo().userRole, getSelfUserInfo().userStatus);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onOnNewAnchorJoin(VCUserInfo event) {
        if (getSelfUserInfo() != null && getSelfUserInfo().isHost()) {
            return;
        }
        Log.i(TAG, "onOnNewAnchorJoin event:" + event);
        AnchorInfo peerAnchor = new AnchorInfo();
        peerAnchor.roomId = event.roomId;
        peerAnchor.userId = event.userId;
        peerAnchor.userName = event.userName;
        peerAnchor.mic = event.mic;
        peerAnchor.camera = event.camera;
        AnchorInfo localAnchor = new AnchorInfo();
        localAnchor.mic = getHostUserInfo().mic;
        localAnchor.camera = getHostUserInfo().camera;
        startPk(peerAnchor, localAnchor, null);
    }

    private void startPk(AnchorInfo peerAnchor, AnchorInfo localAnchor, String rtcToken) {
        getRoomInfo().status = ROOM_STATUS_PK_ING;
        mBottomOptionLayout.updateUIByRoleAndStatus(ROOM_STATUS_PK_ING, getSelfUserInfo().userRole, getSelfUserInfo().userStatus);
        mVideoPkFragment = new VideoAnchorPkFragment();
        Bundle args = new Bundle();
        args.putString(VideoAnchorPkFragment.KEY_PEER_ROOM_ID, peerAnchor.roomId);
        args.putString(VideoAnchorPkFragment.KEY_PEER_USER_ID, peerAnchor.userId);
        args.putString(VideoAnchorPkFragment.KEY_PEER_USER_NAME, peerAnchor.userName);
        args.putString(VideoAnchorPkFragment.KEY_RTC_TOKEN, rtcToken);
        args.putBoolean(VideoAnchorPkFragment.KEY_PEER_ANCHOR_MUTED, peerAnchor.audioStatusThisRoom == 0);
        args.putBoolean(VideoAnchorPkFragment.KEY_PEER_ANCHOR_MIC_ON, peerAnchor.mic == 1);
        args.putBoolean(VideoAnchorPkFragment.KEY_PEER_ANCHOR_CAMERA_ON, peerAnchor.camera == 1);
        args.putBoolean(VideoAnchorPkFragment.KEY_LOCAL_ANCHOR_MIC_ON, localAnchor.mic == 1);
        args.putBoolean(VideoAnchorPkFragment.KEY_LOCAL_ANCHOR_CAMERA_ON, localAnchor.camera == 1);
        mVideoPkFragment.setArguments(args);
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction()
                .add(R.id.biz_fl, mVideoPkFragment, TAG_FRAGMENT_ANCHOR_PK)
                .commit();
        mLocalLiveFl.removeAllViews();
        mLocalAnchorNameFl.setVisibility(View.GONE);
    }

    public static void openFromList(Activity activity, VCRoomInfo roomInfo) {
        Intent intent = new Intent(activity, VideoChatRoomMainActivity.class);
        intent.putExtra(REFER_KEY, REFER_FROM_LIST);
        intent.putExtra(REFER_EXTRA_ROOM, GsonUtils.gson().toJson(roomInfo));
        VCUserInfo userInfo = new VCUserInfo();
        userInfo.userId = SolutionDataManager.ins().getUserId();
        userInfo.userName = SolutionDataManager.ins().getUserName();
        intent.putExtra(REFER_EXTRA_USER, GsonUtils.gson().toJson(userInfo));
        activity.startActivity(intent);
    }

    public static void openFromCreate(Activity activity, VCRoomInfo roomInfo, VCUserInfo userInfo, String rtcToken) {
        Intent intent = new Intent(activity, VideoChatRoomMainActivity.class);
        intent.putExtra(REFER_KEY, REFER_FROM_CREATE);
        JoinRoomResponse response = new JoinRoomResponse();
        response.hostInfo = userInfo;
        response.userInfo = userInfo;
        response.roomInfo = roomInfo;
        response.rtcToken = rtcToken;
        response.audienceCount = 0;
        intent.putExtra(REFER_EXTRA_CREATE_JSON, GsonUtils.gson().toJson(response));
        activity.startActivity(intent);
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

    private int getSelfInteractStatus() {
        return VideoChatDataManager.ins().selfInviteStatus;
    }

}
