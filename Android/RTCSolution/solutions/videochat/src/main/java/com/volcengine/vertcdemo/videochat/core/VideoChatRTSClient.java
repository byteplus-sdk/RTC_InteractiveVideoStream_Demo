// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.core;

import static com.volcengine.vertcdemo.videochat.core.VideoChatDataManager.REPLY_TYPE_ACCEPT;

import android.text.TextUtils;

import com.google.gson.JsonObject;
import com.ss.bytertc.engine.RTCVideo;
import com.volcengine.vertcdemo.common.AbsBroadcast;
import com.volcengine.vertcdemo.common.AppExecutors;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.IRequestCallback;
import com.volcengine.vertcdemo.core.net.RequestCallbackAdapter;
import com.volcengine.vertcdemo.core.net.rts.RTSBaseClient;
import com.volcengine.vertcdemo.core.net.rts.RTSBizInform;
import com.volcengine.vertcdemo.core.net.rts.RTSInfo;
import com.volcengine.vertcdemo.videochat.bean.AnchorPkFinishEvent;
import com.volcengine.vertcdemo.videochat.bean.AudienceApplyEvent;
import com.volcengine.vertcdemo.videochat.bean.AudienceChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.ChatMessageEvent;
import com.volcengine.vertcdemo.videochat.bean.ClearUserEvent;
import com.volcengine.vertcdemo.videochat.bean.CloseChatRoomEvent;
import com.volcengine.vertcdemo.videochat.bean.CreateRoomEvent;
import com.volcengine.vertcdemo.videochat.bean.FinishLiveEvent;
import com.volcengine.vertcdemo.videochat.bean.GetActiveRoomListEvent;
import com.volcengine.vertcdemo.videochat.bean.GetAnchorsEvent;
import com.volcengine.vertcdemo.videochat.bean.GetAudienceEvent;
import com.volcengine.vertcdemo.videochat.bean.InteractChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.InteractReplyEvent;
import com.volcengine.vertcdemo.videochat.bean.InteractResultEvent;
import com.volcengine.vertcdemo.videochat.bean.InviteAnchorEvent;
import com.volcengine.vertcdemo.videochat.bean.InviteAnchorReplyEvent;
import com.volcengine.vertcdemo.videochat.bean.JoinRoomEvent;
import com.volcengine.vertcdemo.videochat.bean.ManageOtherAnchorEvent;
import com.volcengine.vertcdemo.videochat.bean.MediaChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.MediaOperateEvent;
import com.volcengine.vertcdemo.videochat.bean.ReceivedInteractEvent;
import com.volcengine.vertcdemo.videochat.bean.ReplyAnchorsEvent;
import com.volcengine.vertcdemo.videochat.bean.ReplyMicOnEvent;
import com.volcengine.vertcdemo.videochat.bean.SeatChangedEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatResponse;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.event.UserStatusChangedEvent;

import java.util.UUID;

public class VideoChatRTSClient extends RTSBaseClient {

    private static final String CMD_CREATE_ROOM = "viCreateRoom";
    private static final String CMD_START_LIVE = "viStartLive";
    private static final String CMD_GET_AUDIENCE_LIST = "viGetAudienceList";
    private static final String CMD_GET_APPLY_AUDIENCE_LIST = "viGetApplyAudienceList";
    private static final String CMD_INVITE_INTERACT = "viInviteInteract";
    private static final String CMD_AGREE_APPLY = "viAgreeApply";
    private static final String CMD_MANAGE_INTERACT_APPLY = "viManageInteractApply";
    private static final String CMD_MANAGE_SEAT = "viManageSeat";
    private static final String CMD_FINISH_LIVE = "viFinishLive";
    private static final String CMD_JOIN_LIVE_ROOM = "viJoinLiveRoom";
    private static final String CMD_REPLY_INVITE = "viReplyInvite";
    private static final String CMD_FINISH_INTERACT = "viFinishInteract";
    private static final String CMD_APPLY_INTERACT = "viApplyInteract";
    private static final String CMD_LEAVE_LIVE_ROOM = "viLeaveLiveRoom";
    private static final String CMD_GET_ACTIVE_LIVE_ROOM_LIST = "viGetActiveLiveRoomList";
    private static final String CMD_SEND_MESSAGE = "viSendMessage";
    private static final String CMD_RECONNECT = "viReconnect";
    private static final String CMD_CLEAR_USER = "viClearUser";
    private static final String CMD_UPDATE_MEDIA_STATUS = "viUpdateMediaStatus";
    private static final String CMD_CLOSE_CHAT_ROOM = "viCloseChatRoom";
    private static final String CMD_GET_ANCHORS = "viGetAnchorList";
    private static final String CMD_INVITE_ANCHOR = "viInviteAnchor";
    private static final String CMD_REPLY_ANCHOR = "viReplyAnchor";
    private static final String CMD_FINISH_ANCHOR_INTERACT = "viFinishAnchorInteract";
    private static final String CMD_MANAGE_OTHER_ANCHOR = "viManageOtherAnchor";

    private static final String ON_AUDIENCE_JOIN_ROOM = "viOnAudienceJoinRoom";
    private static final String ON_AUDIENCE_LEAVE_ROOM = "viOnAudienceLeaveRoom";
    private static final String ON_FINISH_LIVE = "viOnFinishLive";
    private static final String ON_JOIN_INTERACT = "viOnJoinInteract";
    private static final String ON_FINISH_INTERACT = "viOnFinishInteract";
    private static final String ON_SEAT_STATUS_CHANGE = "viOnSeatStatusChange";
    private static final String ON_MEDIA_STATUS_CHANGE = "viOnMediaStatusChange";
    private static final String ON_MESSAGE = "viOnMessage";
    private static final String ON_INVITE_INTERACT = "viOnInviteInteract";
    private static final String ON_APPLY_INTERACT = "viOnApplyInteract";
    private static final String ON_INVITE_RESULT = "viOnInviteResult";
    private static final String ON_MEDIA_OPERATE = "viOnMediaOperate";
    private static final String ON_CLEAR_USER = "viOnClearUser";
    private static final String ON_ANCHOR_INVITE = "viOnAnchorInvite";
    private static final String ON_ANCHOR_REPLY = "viOnAnchorReply";
    private static final String ON_NEW_ANCHOR_JOIN = "viOnNewAnchorJoin";
    private static final String ON_ANCHOR_INTERACT_FINISH = "viOnAnchorInteractFinish";
    private static final String ON_MANAGE_OTHER_ANCHOR = "viOnManageOtherAnchor";
    private static final String ON_CLOSE_CHAT_ROOM = "viOnCloseChatRoom";

    public VideoChatRTSClient(RTCVideo rtcVideo, RTSInfo rtmInfo) {
        super(rtcVideo, rtmInfo);
        initEventListener();
    }

    private JsonObject getCommonParams(String cmd) {
        JsonObject params = new JsonObject();
        params.addProperty("app_id", mRTSInfo.appId);
        params.addProperty("room_id", "");
        params.addProperty("user_id", SolutionDataManager.ins().getUserId());
        params.addProperty("event_name", cmd);
        params.addProperty("request_id", UUID.randomUUID().toString());
        params.addProperty("device_id", SolutionDataManager.ins().getDeviceId());
        return params;
    }

    private void initEventListener() {
        putEventListener(new AbsBroadcast<>(ON_AUDIENCE_JOIN_ROOM, AudienceChangedEvent.class, (data) -> {
            data.isJoin = true;
            SolutionDemoEventManager.post(data);
        }));

        putEventListener(new AbsBroadcast<>(ON_AUDIENCE_LEAVE_ROOM, AudienceChangedEvent.class, (data) -> {
            data.isJoin = false;
            SolutionDemoEventManager.post(data);
        }));

        putEventListener(new AbsBroadcast<>(ON_FINISH_LIVE, FinishLiveEvent.class,
                SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_JOIN_INTERACT, InteractChangedEvent.class, (data) -> {
            data.isStart = true;
            SolutionDemoEventManager.post(data);
        }));

        putEventListener(new AbsBroadcast<>(ON_FINISH_INTERACT, InteractChangedEvent.class, (data) -> {
            data.isStart = false;
            SolutionDemoEventManager.post(data);

            UserStatusChangedEvent event = new UserStatusChangedEvent(data.userInfo, VideoChatUserInfo.USER_STATUS_NORMAL);
            SolutionDemoEventManager.post(event);
        }));

        putEventListener(new AbsBroadcast<>(ON_SEAT_STATUS_CHANGE, SeatChangedEvent.class,
                SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_MEDIA_STATUS_CHANGE, MediaChangedEvent.class,
                SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_MESSAGE, ChatMessageEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_INVITE_INTERACT, ReceivedInteractEvent.class, (data) -> {
            UserStatusChangedEvent event = new UserStatusChangedEvent(data.userInfo, VideoChatUserInfo.USER_STATUS_INVITING);
            SolutionDemoEventManager.post(event);
            SolutionDemoEventManager.post(data);
        }));

        putEventListener(new AbsBroadcast<>(ON_APPLY_INTERACT, AudienceApplyEvent.class, (data) -> {
            data.hasNewApply = true;
            SolutionDemoEventManager.post(data);
            UserStatusChangedEvent event = new UserStatusChangedEvent(data.userInfo, VideoChatUserInfo.USER_STATUS_APPLYING);
            SolutionDemoEventManager.post(event);
        }));

        putEventListener(new AbsBroadcast<>(ON_INVITE_RESULT, InteractResultEvent.class, (data) -> {
            SolutionDemoEventManager.post(data);
            int statue = data.reply == REPLY_TYPE_ACCEPT ? VideoChatUserInfo.USER_STATUS_INTERACT : VideoChatUserInfo.USER_STATUS_NORMAL;
            UserStatusChangedEvent event = new UserStatusChangedEvent(data.userInfo, statue);
            SolutionDemoEventManager.post(event);
        }));

        putEventListener(new AbsBroadcast<>(ON_MEDIA_OPERATE, MediaOperateEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_CLEAR_USER, ClearUserEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_ANCHOR_INVITE, InviteAnchorEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_ANCHOR_REPLY, InviteAnchorReplyEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_NEW_ANCHOR_JOIN, VideoChatUserInfo.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_ANCHOR_INTERACT_FINISH, AnchorPkFinishEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_MANAGE_OTHER_ANCHOR, ManageOtherAnchorEvent.class, SolutionDemoEventManager::post));

        putEventListener(new AbsBroadcast<>(ON_CLOSE_CHAT_ROOM, CloseChatRoomEvent.class, SolutionDemoEventManager::post));
    }

    private void putEventListener(AbsBroadcast<? extends RTSBizInform> absBroadcast) {
        mEventListeners.put(absBroadcast.getEvent(), absBroadcast);
    }

    public void removeAllEventListener() {
        mEventListeners.remove(ON_AUDIENCE_JOIN_ROOM);
        mEventListeners.remove(ON_AUDIENCE_LEAVE_ROOM);
        mEventListeners.remove(ON_FINISH_LIVE);
        mEventListeners.remove(ON_JOIN_INTERACT);
        mEventListeners.remove(ON_FINISH_INTERACT);
        mEventListeners.remove(ON_SEAT_STATUS_CHANGE);
        mEventListeners.remove(ON_MEDIA_STATUS_CHANGE);
        mEventListeners.remove(ON_MESSAGE);
        mEventListeners.remove(ON_INVITE_INTERACT);
        mEventListeners.remove(ON_APPLY_INTERACT);
        mEventListeners.remove(ON_INVITE_RESULT);
        mEventListeners.remove(ON_MEDIA_OPERATE);
        mEventListeners.remove(ON_CLEAR_USER);
        mEventListeners.remove(ON_ANCHOR_INVITE);
        mEventListeners.remove(ON_ANCHOR_REPLY);
        mEventListeners.remove(ON_NEW_ANCHOR_JOIN);
        mEventListeners.remove(ON_ANCHOR_INTERACT_FINISH);
        mEventListeners.remove(ON_MANAGE_OTHER_ANCHOR);
        mEventListeners.remove(ON_CLOSE_CHAT_ROOM);
    }

    private <T extends VideoChatResponse> void sendServerMessageOnNetwork(
            String roomId, JsonObject content, Class<T> resultClass, IRequestCallback<T> callback) {
        String cmd = content.get("event_name").getAsString();
        if (TextUtils.isEmpty(cmd)) {
            return;
        }
        AppExecutors.networkIO().execute(() -> {
            sendServerMessage(cmd, roomId, content, resultClass, callback);
        });
    }

    public void requestAudienceList(String roomId, IRequestCallback<GetAudienceEvent> callback) {
        JsonObject params = getCommonParams(CMD_GET_AUDIENCE_LIST);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, GetAudienceEvent.class, callback);
    }

    public void requestApplyAudienceList(String roomId, IRequestCallback<GetAudienceEvent> callback) {
        JsonObject params = getCommonParams(CMD_GET_APPLY_AUDIENCE_LIST);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, GetAudienceEvent.class, callback);
    }

    public void inviteInteract(String roomId, String audienceUserId, int seatId,
                               IRequestCallback<VideoChatResponse> callback) {

        JsonObject params = getCommonParams(CMD_INVITE_INTERACT);
        params.addProperty("room_id", roomId);
        params.addProperty("audience_user_id", audienceUserId);
        params.addProperty("seat_id", seatId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void agreeApply(String roomId, String audienceUserId, String audienceRoomId,
                           IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_AGREE_APPLY);
        params.addProperty("room_id", roomId);
        params.addProperty("audience_user_id", audienceUserId);
        params.addProperty("audience_room_id", audienceRoomId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void manageInteractApply(String roomId, int type, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_MANAGE_INTERACT_APPLY);
        params.addProperty("room_id", roomId);
        params.addProperty("type", type);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void managerSeat(String roomId, int seatId, @VideoChatDataManager.SeatOption int type,
                            IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_MANAGE_SEAT);
        params.addProperty("room_id", roomId);
        params.addProperty("seat_id", seatId);
        params.addProperty("type", type);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void requestFinishLive(String roomId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_FINISH_LIVE);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void requestJoinRoom(String userName, String roomId,
                                IRequestCallback<JoinRoomEvent> callback) {

        JsonObject params = getCommonParams(CMD_JOIN_LIVE_ROOM);
        params.addProperty("user_name", userName);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, JoinRoomEvent.class, callback);
    }

    public void replyInvite(String roomId, @VideoChatDataManager.ReplyType int reply, int seatId,
                            IRequestCallback<InteractReplyEvent> callback) {
        JsonObject params = getCommonParams(CMD_REPLY_INVITE);
        params.addProperty("room_id", roomId);
        params.addProperty("reply", reply);
        params.addProperty("seat_id", seatId);
        sendServerMessageOnNetwork(roomId, params, InteractReplyEvent.class, callback);
    }

    public void finishInteract(String roomId, int seatId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_FINISH_INTERACT);
        params.addProperty("room_id", roomId);
        params.addProperty("seat_id", seatId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void applyInteract(String roomId, int seatId, IRequestCallback<ReplyMicOnEvent> callback) {
        JsonObject params = getCommonParams(CMD_APPLY_INTERACT);
        params.addProperty("room_id", roomId);
        params.addProperty("seat_id", seatId);
        sendServerMessageOnNetwork(roomId, params, ReplyMicOnEvent.class, callback);
    }

    public void requestLeaveRoom(String roomId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_LEAVE_LIVE_ROOM);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void getActiveRoomList(IRequestCallback<GetActiveRoomListEvent> callback) {
        JsonObject params = getCommonParams(CMD_GET_ACTIVE_LIVE_ROOM_LIST);
        sendServerMessageOnNetwork("", params, GetActiveRoomListEvent.class, callback);
    }

    public void sendMessage(String roomId, String message, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_SEND_MESSAGE);
        params.addProperty("room_id", roomId);
        params.addProperty("message", message);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void reconnectToServer(IRequestCallback<JoinRoomEvent> callback) {
        reconnectToServer("", callback);
    }

    public void reconnectToServer(String roomId, IRequestCallback<JoinRoomEvent> callback) {
        JsonObject params = getCommonParams(CMD_RECONNECT);
        sendServerMessageOnNetwork(roomId, params, JoinRoomEvent.class, callback);
    }

    public void requestClearUser(Runnable next) {
        JsonObject params = getCommonParams(CMD_CLEAR_USER);
        sendServerMessageOnNetwork("", params, VideoChatResponse.class, RequestCallbackAdapter.create(next));
    }

    public void updateMediaStatus(String roomId, String userId, int micOption, int cameraStatus,
                                  IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_UPDATE_MEDIA_STATUS);
        params.addProperty("room_id", roomId);
        params.addProperty("user_id", userId);
        params.addProperty("mic", micOption);
        params.addProperty("camera", cameraStatus);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void requestCreateRoom(String userName, String roomName, String backgroundImageName,
                                  IRequestCallback<CreateRoomEvent> callback) {
        JsonObject params = getCommonParams(CMD_CREATE_ROOM);
        params.addProperty("user_name", userName);
        params.addProperty("room_name", roomName);
        params.addProperty("background_image_name", backgroundImageName);
        sendServerMessageOnNetwork("", params, CreateRoomEvent.class, callback);
    }

    public void requestStartLive(String roomId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_START_LIVE);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void getAnchorList(IRequestCallback<GetAnchorsEvent> callback) {
        JsonObject params = getCommonParams(CMD_GET_ANCHORS);
        sendServerMessageOnNetwork("", params, GetAnchorsEvent.class, callback);
    }

    public void inviteAnchor(String roomId, String userId,
                             String peerRoomId, String peerUid, int seatId,
                             IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_INVITE_ANCHOR);
        params.addProperty("inviter_room_id", roomId);
        params.addProperty("inviter_user_id", userId);
        params.addProperty("invitee_room_id", peerRoomId);
        params.addProperty("invitee_user_id", peerUid);
        params.addProperty("seat_id", seatId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    /**
     * 回复PK邀请
     *
     * @param peerRoomId
     * @param peerUid
     * @param reply      1: 接受 2:拒绝
     * @param callback
     */
    public void replyAnchor(String roomId, String userId,
                            String peerRoomId, String peerUid, int reply,
                            IRequestCallback<ReplyAnchorsEvent> callback) {
        JsonObject params = getCommonParams(CMD_REPLY_ANCHOR);
        params.addProperty("inviter_room_id", peerRoomId);
        params.addProperty("inviter_user_id", peerUid);
        params.addProperty("invitee_room_id", roomId);
        params.addProperty("invitee_user_id", userId);
        params.addProperty("reply", reply);
        sendServerMessageOnNetwork(roomId, params, ReplyAnchorsEvent.class, callback);
    }

    public void finishAnchorInteract(String roomId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_FINISH_ANCHOR_INTERACT);
        params.addProperty("room_id", roomId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    /**
     * 管理对端主播状态，例如：mute或者unmute对端主播
     *
     * @param peerUid
     * @param type     0: mute 1:unmute
     * @param callback
     */
    public void manageOtherAnchor(String userId, String roomId, String peerUid, int type,
                                  IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_MANAGE_OTHER_ANCHOR);
        params.addProperty("room_id", roomId);
        params.addProperty("user_id", userId);
        params.addProperty("other_anchor_user_id", peerUid);
        params.addProperty("type", type);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }

    public void closeChatRoom(String roomId, String userId, IRequestCallback<VideoChatResponse> callback) {
        JsonObject params = getCommonParams(CMD_CLOSE_CHAT_ROOM);
        params.addProperty("room_id", roomId);
        params.addProperty("user_id", userId);
        sendServerMessageOnNetwork(roomId, params, VideoChatResponse.class, callback);
    }
}
