// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT

package com.volcengine.vertcdemo.videochat.core;

import static com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_HIDDEN;
import static com.ss.bytertc.engine.data.AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
import static com.volcengine.vertcdemo.utils.FileUtils.copyAssetFile;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;

import androidx.annotation.NonNull;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.audio.IAudioEffectPlayer;
import com.ss.bytertc.engine.data.AudioEffectPlayerConfig;
import com.ss.bytertc.engine.data.AudioMixingConfig;
import com.ss.bytertc.engine.data.AudioPropertiesConfig;
import com.ss.bytertc.engine.data.CameraId;
import com.ss.bytertc.engine.data.ForwardStreamEventInfo;
import com.ss.bytertc.engine.data.ForwardStreamInfo;
import com.ss.bytertc.engine.data.ForwardStreamStateInfo;
import com.ss.bytertc.engine.data.LocalAudioPropertiesInfo;
import com.ss.bytertc.engine.data.MirrorType;
import com.ss.bytertc.engine.data.RemoteAudioPropertiesInfo;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.NetworkQualityStats;
import com.volcengine.vertcdemo.common.AppExecutors;
import com.volcengine.vertcdemo.core.eventbus.SDKReconnectToRoomEvent;
import com.volcengine.vertcdemo.utils.AppUtil;
import com.volcengine.vertcdemo.common.MLog;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.rts.RTCRoomEventHandlerWithRTS;
import com.volcengine.vertcdemo.core.net.rts.RTCVideoEventHandlerWithRTS;
import com.volcengine.vertcdemo.core.net.rts.RTSInfo;
import com.volcengine.vertcdemo.protocol.IEffect;
import com.volcengine.vertcdemo.protocol.ProtocolUtil;
import com.volcengine.vertcdemo.videochat.bean.UserJoinedEvent;
import com.volcengine.vertcdemo.videochat.bean.UserLeaveEvent;
import com.volcengine.vertcdemo.videochat.bean.VideoChatUserInfo;
import com.volcengine.vertcdemo.videochat.event.SDKAudioPropertiesEvent;
import com.volcengine.vertcdemo.videochat.event.SDKNetStatusEvent;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * RTC object management class
 *
 * Use the singleton form, call the RTC interface, and update the VideoChatDataManager data in the call
 * Internal record switch status
 *
 * Function:
 * 1. Switch and media status
 * 2. Get the current media status
 * 3. Receive various RTC callbacks, such as: user check-in and check-out, media status change, media status data callback, network status callback, volume callback
 * 4. Manage user video rendering view
 * 5. Join and leave the room
 * 6. Create and destroy engine
 */
public class VideoChatRTCManager {

    private static final String TAG = "VideoChatRTCManager";

    private static VideoChatRTCManager sInstance;

    private final RTCVideoEventHandlerWithRTS mRTCVideoEventHandler = new RTCVideoEventHandlerWithRTS() {

        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            Log.d(TAG, String.format("onWarning: %d", warn));
        }

        @Override
        public void onError(int err) {
            super.onError(err);
            Log.d(TAG, String.format("onError: %d", err));
        }
        // Local volume record.
        private SDKAudioPropertiesEvent.SDKAudioProperties mLocalProperties = null;

        /**
         * Local audio includes microphone audio and screen audio collected using the internal
         * mechanism of the RTC SDK.
         * @param audioPropertiesInfos Local audio information, see LocalAudioPropertiesInfo for details.
         */
        @Override
        public void onLocalAudioPropertiesReport(LocalAudioPropertiesInfo[] audioPropertiesInfos) {
            super.onLocalAudioPropertiesReport(audioPropertiesInfos);
            if (audioPropertiesInfos == null) {
                return;
            }
            for (LocalAudioPropertiesInfo info : audioPropertiesInfos) {
                if (info.streamIndex == StreamIndex.STREAM_INDEX_MAIN) {
                    SDKAudioPropertiesEvent.SDKAudioProperties properties = new SDKAudioPropertiesEvent.SDKAudioProperties(
                            SolutionDataManager.ins().getUserId(),
                            info.audioPropertiesInfo);
                    mLocalProperties = properties;
                    List<SDKAudioPropertiesEvent.SDKAudioProperties> audioPropertiesList = new ArrayList<>();
                    audioPropertiesList.add(properties);
                    SolutionDemoEventManager.post(new SDKAudioPropertiesEvent(audioPropertiesList));
                    return;
                }
            }
        }

        /**
         * The audio of remote users includes microphone audio and screen audio collected using
         * the RTC SDK internal mechanism/custom mechanism.
         * @param audioPropertiesInfos Remote audio information, including audio stream properties,
         *                            room ID and user ID, see RemoteAudioPropertiesInfo for details.
         * @param totalRemoteVolume The total volume of all subscribed remote streams.
         */
        @Override
        public void onRemoteAudioPropertiesReport(RemoteAudioPropertiesInfo[] audioPropertiesInfos, int totalRemoteVolume) {
            super.onRemoteAudioPropertiesReport(audioPropertiesInfos, totalRemoteVolume);
            if (audioPropertiesInfos == null) {
                return;
            }
            List<SDKAudioPropertiesEvent.SDKAudioProperties> audioPropertiesList = new ArrayList<>();
            if (mLocalProperties != null) {
                audioPropertiesList.add(mLocalProperties);
            }
            for (RemoteAudioPropertiesInfo info : audioPropertiesInfos) {
                if (info.streamKey.getStreamIndex() == StreamIndex.STREAM_INDEX_MAIN) {
                    audioPropertiesList.add(new SDKAudioPropertiesEvent.SDKAudioProperties(
                            info.streamKey.getUserId(),
                            info.audioPropertiesInfo));
                }
            }
            SolutionDemoEventManager.post(new SDKAudioPropertiesEvent(audioPropertiesList));
        }
    };

    /**
     * RTC room callback events listener.
     */
    private final RTCRoomEventHandlerWithRTS mRTCRoomEventHandler = new RTCRoomEventHandlerWithRTS() {

        /**
         * Room status change callback, this callback will be received when joining a room,
         * leaving a room, or when a room-related warning or error occurs.
         * @param roomId room id
         * @param uid user id
         * @param state room status code
         * @param extraInfo extra information
         */
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            Log.d(TAG, String.format("onRoomStateChanged: %s, %s, %d, %s", roomId, uid, state, extraInfo));
            mRoomId = roomId;
            if (isReconnectSuccess(state, extraInfo)) {
                SolutionDemoEventManager.post(new SDKReconnectToRoomEvent(roomId));
            }
        }

        /**
         * Callback when visible users join the room, or invisible users in the room switch to visible.
         * @param userInfo user information
         * @param elapsed The elapsed time from when the host role user calls joinRoom to join the room to when other users in the room receive the event, in ms.
         */
        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            Log.d(TAG, String.format("onUserJoined: %s, %d", userInfo.getUid(), elapsed));
            SolutionDemoEventManager.post(new UserJoinedEvent(userInfo));
            setRemoteVideoView(userInfo.getUid(), mRoomId, getUserRenderView(userInfo.getUid()));
        }

        /**
         * When the remote user leaves the room or becomes invisible, the local user will receive this event
         * @param uid Remote user ID to leave room, or switch to invisible.
         * @param reason The reason why the user left the room:
         * • 0: The remote user calls leaveRoom to actively leave the room.
         * • 1: The remote user is disconnected due to Token expiration or network reasons.
         * • 2: The remote user calls setUserVisibility to switch to the invisible state.
         * • 3: The server calls OpenAPI to kick the remote user out of the room.
         */
        @Override
        public void onUserLeave(String uid, int reason) {
            Log.d(TAG, String.format("onUserLeave: %s, %d", uid, reason));
            SolutionDemoEventManager.post(new UserLeaveEvent(uid, reason));
        }

        /**
         * Added a callback for the far-end camera/microphone to collect audio and video streams in the room.
         * @param uid The user ID of the remote stream publishing user.
         * @param type The type of remote media stream, see MediaStreamType.
         */
        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            if (type != MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO && !TextUtils.isEmpty(mRoomId)) {
                setRemoteVideoView(uid, mRoomId, getUserRenderView(uid));
            }
        }

        /**
         * After joining the room, report the user's network quality information every 2 seconds
         *
         * @param localQuality Local network quality, see NetworkQualityStats for details.
         * @param remoteQualities The network quality of subscribed users, see NetworkQualityStats for details.
         * @see NetworkQualityStats
         */
        @Override
        public void onNetworkQuality(NetworkQualityStats localQuality, NetworkQualityStats[] remoteQualities) {
            super.onNetworkQuality(localQuality, remoteQualities);
            SolutionDemoEventManager.post(new SDKNetStatusEvent(localQuality.uid, localQuality.txQuality));
            if (remoteQualities != null) {
                for (NetworkQualityStats stats : remoteQualities) {
                    SolutionDemoEventManager.post(new SDKNetStatusEvent(stats.uid, stats.rxQuality));
                }
            }
        }

        /**
         * Callback returning the state and errors during relaying the media stream to each of the rooms
         * @param stateInfos Array of the state and errors of each designated room. see ForwardStreamStateInfo for more information.
         */
        @Override
        public void onForwardStreamStateChanged(ForwardStreamStateInfo[] stateInfos) {
            String result = "";
            for (ForwardStreamStateInfo info : stateInfos) {
                result = result.concat("|" + info.roomId + "," + info.error + "," + info.state + "|");
            }
            Log.d(TAG, String.format("onForwardStreamStateChanged: %s", result));
        }

        /**
         * Callback returning the events during relaying the media stream to each room
         * @param eventInfos Array of the event of each designated room. Refer to ForwardStreamEventInfo for more information.
         */
        @Override
        public void onForwardStreamEvent(ForwardStreamEventInfo[] eventInfos) {
            String result = "";
            for (ForwardStreamEventInfo info : eventInfos) {
                result = result.concat("|" + info.roomId + "," + info.event + "|");
            }
            Log.d(TAG, String.format("onForwardStreamStateChanged: %s", result));
        }
    };

    private static final int AUDIO_EFFECT_ID = 0;

    private VideoChatRTSClient mRTSClient;

    private RTCVideo mRTCVideo;
    private RTCRoom mRTCRoom;

    private final Map<String, TextureView> mUidViewMap = new HashMap<>();

    private boolean mIsCameraOn = true;
    private boolean mIsMicOn = true;
    private boolean mIsFront = true;
    private int mFrameRate = 15;
    private int mFrameWidth = 720;
    private int mFrameHeight = 1280;
    private int mBitrate = 1600;
    public boolean isTest = false;
    // RoomId of the currently joined RTC room.
    private String mRoomId = "";

    public static VideoChatRTCManager ins() {
        if (sInstance == null) {
            sInstance = new VideoChatRTCManager();
        }
        return sInstance;
    }

    /**
     * initialize RTC.
     */
    public void initEngine(RTSInfo info) {
        destroyEngine();
        mRTCVideo = RTCVideo.createRTCVideo(AppUtil.getApplicationContext(), info.appId, mRTCVideoEventHandler, null, null);
        mRTCVideo.setBusinessId(info.bid);
        mRTCVideo.stopVideoCapture();
        enableAudioVolumeIndication(2000);

        VideoEncoderConfig config = new VideoEncoderConfig();
        config.width = 720;
        config.height = 1280;
        config.frameRate = 15;
        config.maxBitrate = 1600;
        mRTCVideo.setVideoEncoderConfig(config);
        switchCamera(mIsFront);

        initVideoEffect();
        initBGMRes();
        mRTSClient = new VideoChatRTSClient(mRTCVideo, info);
        mRTCVideoEventHandler.setBaseClient(mRTSClient);
        mRTCRoomEventHandler.setBaseClient(mRTSClient);
    }

    /**
     * Get the RTS Client object.
     * @return Video chat scenario RTS client object, enabling users to send and receive messages in the RTC room.
     */
    public VideoChatRTSClient getRTSClient() {
        return mRTSClient;
    }

    /**
     * Enable audio volume indication.
     * @param interval Callback period.
     */
    public void enableAudioVolumeIndication(int interval) {
        MLog.d(TAG, String.format(Locale.ENGLISH, "enableAudioVolumeIndication: %d", interval));
        if (mRTCVideo == null) {
            return;
        }
        AudioPropertiesConfig config = new AudioPropertiesConfig(interval);
        mRTCVideo.enableAudioPropertiesReport(config);
    }

    /**
     * flip camera
     * @param isFront is the front camera
     */
    public void switchCamera(boolean isFront) {
        if (mRTCVideo != null) {
            mRTCVideo.setLocalVideoMirrorType(isFront ? MirrorType.MIRROR_TYPE_RENDER_AND_ENCODER : MirrorType.MIRROR_TYPE_NONE);
            mRTCVideo.switchCamera(isFront ? CameraId.CAMERA_ID_FRONT : CameraId.CAMERA_ID_BACK);
        }
        mIsFront = isFront;
    }

    public void switchCamera() {
        switchCamera(!mIsFront);
    }

    public boolean isCameraOn() {
        return mIsCameraOn;
    }

    public boolean isMicOn() {
        return mIsMicOn;
    }

    public void turnOnMic(boolean isMicOn) {
        if (mRTCVideo != null) {
            if (isMicOn) {
                mRTCVideo.startAudioCapture();
            } else {
                mRTCVideo.stopAudioCapture();
            }
        }
        if (mRTCRoom != null) {
            if (isMicOn) {
                mRTCRoom.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            } else {
                mRTCRoom.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            }
        }

        Log.d(TAG, "turnOnMic : " + isMicOn);
        mIsMicOn = isMicOn;
        updateMicAndCameraStatus();
    }

    public void turnOnMic() {
        turnOnMic(!mIsMicOn);
    }

    public void turnOnCamera(boolean isCameraOn) {
        if (mRTCVideo != null) {
            if (isCameraOn) {
                mRTCVideo.startVideoCapture();
            } else {
                mRTCVideo.stopVideoCapture();
            }
        }
        mIsCameraOn = isCameraOn;
        Log.d(TAG, "turnOnCamera : " + isCameraOn);
        updateMicAndCameraStatus();
    }

    private void updateMicAndCameraStatus() {
        VideoChatUserInfo selfUserInfo = VideoChatDataManager.ins().selfUserInfo;
        if (selfUserInfo == null) {
            return;
        }
        String hostUid = VideoChatDataManager.ins().hostUserInfo == null ? null : VideoChatDataManager.ins().hostUserInfo.userId;
        VideoChatDataManager.ins().selfUserInfo.mic = mIsMicOn ? VideoChatUserInfo.MIC_STATUS_ON : VideoChatUserInfo.MIC_STATUS_OFF;
        VideoChatDataManager.ins().selfUserInfo.camera = mIsCameraOn ? VideoChatUserInfo.CAMERA_STATUS_ON : VideoChatUserInfo.CAMERA_STATUS_OFF;
        if (selfUserInfo.isHost() && TextUtils.equals(selfUserInfo.userId, hostUid)) {
            VideoChatDataManager.ins().hostUserInfo.mic = mIsMicOn ? VideoChatUserInfo.MIC_STATUS_ON : VideoChatUserInfo.MIC_STATUS_OFF;
            VideoChatDataManager.ins().hostUserInfo.camera = mIsCameraOn ? VideoChatUserInfo.CAMERA_STATUS_ON : VideoChatUserInfo.CAMERA_STATUS_OFF;
        }
    }

    public void turnOnCamera() {
        turnOnCamera(!mIsCameraOn);
    }

    public void setFrameRate(int frameRate) {
        mFrameRate = frameRate;
        updateVideoConfig();
    }

    public int getFrameRate() {
        return mFrameRate;
    }

    public void setResolution(int width, int height) {
        mFrameWidth = width;
        mFrameHeight = height;
        updateVideoConfig();
    }

    public void setBitrate(int bitrate) {
        mBitrate = bitrate;
        updateVideoConfig();
    }

    public int getBitrate() {
        return mBitrate;
    }

    public int getFrameWidth() {
        return mFrameWidth;
    }

    private void updateVideoConfig() {
        if (mRTCVideo != null) {
            VideoEncoderConfig config = new VideoEncoderConfig();
            config.width = mFrameWidth;
            config.height = mFrameHeight;
            config.frameRate = mFrameRate;
            config.maxBitrate = mBitrate;
            mRTCVideo.setVideoEncoderConfig(config);
        }
    }

    public void startMuteVideo(boolean isStart) {
        Log.d(TAG, "startMuteVideo : " + isStart);
        if (mRTCRoom != null) {
            if (isStart) {
                mRTCRoom.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_VIDEO);
            } else {
                mRTCRoom.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_VIDEO);
            }
        }
    }

    public void startMuteAudio(boolean isStart) {
        Log.d(TAG, String.format("startMuteAudio: %b", isStart));
        if (mRTCRoom != null) {
            if (isStart) {
                mRTCRoom.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            } else {
                mRTCRoom.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            }
        }
    }

    /**
     * When a visible user in the room calls startVideoCapture to start internal video capture,
     * other users in the room will receive this callback.
     * @param isStart true: Start video capture.
     *                false: Close video capture.
     */
    public void startVideoCapture(boolean isStart) {
        if (mRTCVideo != null) {
            if (isStart) {
                mRTCVideo.startVideoCapture();
            } else {
                mRTCVideo.stopVideoCapture();
            }
        }
        mIsCameraOn = isStart;
        Log.d(TAG, "startCaptureVideo : " + isStart);
    }

    /**
     * When a visible user in the room calls startAudioCapture to start internal audio capture,
     * other users in the room will receive this callback.
     * @param isStart true: Start audio capture.
     *                false: Close audio capture.
     */
    public void startAudioCapture(boolean isStart) {
        if (mRTCVideo != null) {
            if (isStart) {
                mRTCVideo.startAudioCapture();
            } else {
                mRTCVideo.stopAudioCapture();
            }
        }
        mIsMicOn = isStart;
        Log.d(TAG, "startCaptureAudio : " + isStart);
    }

    public void setLocalVideoView(@NonNull TextureView surfaceView) {
        if (mRTCVideo == null) {
            return;
        }
        VideoCanvas videoCanvas = new VideoCanvas(surfaceView, RENDER_MODE_HIDDEN);
        mRTCVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
        Log.d(TAG, "setLocalVideoView");
    }

    public TextureView getUserRenderView(String userId) {
        if (TextUtils.isEmpty(userId)) {
            return null;
        }
        TextureView view = mUidViewMap.get(userId);
        if (view == null) {
            view = new TextureView(AppUtil.getApplicationContext());
            mUidViewMap.put(userId, view);
        }
        return view;
    }

    public void setRemoteVideoView(String userId, String roomId, TextureView textureView) {
        Log.d(TAG, String.format(Locale.ENGLISH, "setRemoteVideoView : %s  %s", userId, roomId));
        if (mRTCVideo != null) {
            VideoCanvas canvas = new VideoCanvas(textureView, RENDER_MODE_HIDDEN);
            RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomId, userId, StreamIndex.STREAM_INDEX_MAIN);
            mRTCVideo.setRemoteVideoCanvas(remoteStreamKey, canvas);
        }
    }

    private void initBGMRes() {
        AppExecutors.diskIO().execute(() -> {
            File bgmPath = new File(getExternalResourcePath(), "bgm/voicechat_bgm.mp3");
            if (!bgmPath.exists()) {
                File dir = new File(getExternalResourcePath() + "bgm");
                if (!dir.exists()) {
                    //noinspection ResultOfMethodCallIgnored
                    dir.mkdirs();
                }
                copyAssetFile(AppUtil.getApplicationContext(), "voicechat_bgm.mp3", bgmPath.getAbsolutePath());
            }
        });
    }

    private String getExternalResourcePath() {
        return AppUtil.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/";
    }

    public void destroyEngine() {
        Log.d(TAG, "destroyEngine");
        if (mRTCRoom != null) {
            mRTCRoom.leaveRoom();
            mRTCRoom.destroy();
        }
        mRTCRoom = null;
        if (mRTCVideo == null) {
            return;
        }
        RTCVideo.destroyRTCVideo();
        mRTCVideo = null;
    }

    /**
     * Join the RTC room.
     * @param token  Dynamic key. It is used to authenticate users who enter the room.
     *               A Token is required to enter the room. During the test,
     *               you can use the console to generate a temporary Token.
     *               To officially go online, you need to use the key SDK to
     *               generate and issue a Token on your server.
     * @param roomId RTC room id.
     * @param userId User id.
     * @param userVisible Whether the user is visible to other users in the room.
     */
    public void joinRoom(String roomId, String token, String userId, boolean userVisible) {
        Log.d(TAG, String.format("joinRoom: %s %s %s", roomId, userId, token));
        leaveRoom();
        if (mRTCVideo == null) {
            return;
        }
        mRTCRoom = mRTCVideo.createRTCRoom(roomId);
        mRTCRoom.setRTCRoomEventHandler(mRTCRoomEventHandler);
        UserInfo userInfo = new UserInfo(userId, null);
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_COMMUNICATION,
                true, true, true);
        mRTCRoom.joinRoom(token, userInfo, roomConfig);
    }

    /**
     * Leave the room.
     */
    public void leaveRoom() {
        Log.d(TAG, "leaveRoom");
        if (mRTCRoom != null) {
            mRTCRoom.leaveRoom();
            mRTCRoom.destroy();
            mRTCRoom = null;
        }
    }

    public void startAudioMixing(boolean isStart) {
        Log.d(TAG, String.format("startAudioMixing: %b", isStart));
        if (mRTCVideo != null) {
            IAudioEffectPlayer effectPlayer = mRTCVideo.getAudioEffectPlayer();
            if (isStart) {
                String bgmPath = getExternalResourcePath() + "bgm/voicechat_bgm.mp3";
                effectPlayer.preload(AUDIO_EFFECT_ID, bgmPath);
                AudioEffectPlayerConfig config = new AudioEffectPlayerConfig();
                config.type = AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
                config.playCount = -1;
                effectPlayer.start(AUDIO_EFFECT_ID, bgmPath, config);
            } else {
                effectPlayer.stop(AUDIO_EFFECT_ID);
            }
        }
    }

    public void resumeAudioMixing() {
        Log.d(TAG, "resumeAudioMixing");
        if (mRTCVideo != null) {
            IAudioEffectPlayer effectPlayer = mRTCVideo.getAudioEffectPlayer();
            effectPlayer.resume(AUDIO_EFFECT_ID);
        }
    }

    public void pauseAudioMixing() {
        Log.d(TAG, "pauseAudioMixing");
        if (mRTCVideo != null) {
            IAudioEffectPlayer effectPlayer = mRTCVideo.getAudioEffectPlayer();
            effectPlayer.pause(AUDIO_EFFECT_ID);
        }
    }

    public void stopAudioMixing() {
        Log.d(TAG, "stopAudioMixing");
        if (mRTCVideo != null) {
            IAudioEffectPlayer effectPlayer = mRTCVideo.getAudioEffectPlayer();
            effectPlayer.stop(AUDIO_EFFECT_ID);
        }
    }

    public void adjustBGMVolume(int progress) {
        Log.d(TAG, String.format("adjustBGMVolume: %d", progress));
        if (mRTCVideo != null) {
            IAudioEffectPlayer effectPlayer = mRTCVideo.getAudioEffectPlayer();
            effectPlayer.setVolume(AUDIO_EFFECT_ID, progress);
        }
    }

    public void adjustUserVolume(int progress) {
        Log.d(TAG, String.format("adjustUserVolume: %d", progress));
        if (mRTCVideo != null) {
            mRTCVideo.setCaptureVolume(StreamIndex.STREAM_INDEX_MAIN, progress);
        }
    }

    public void forwardStreamToRoom(ForwardStreamInfo targetRoomInfo) {
        if (mRTCRoom != null) {
            ArrayList<ForwardStreamInfo> list = new ArrayList<>(1);
            list.add(targetRoomInfo);
            int result = mRTCRoom.startForwardStreamToRooms(list);
            Log.d(TAG, String.format("forwardStreamToRoom result: %d", result));
        }
    }

    public void stopForwardStreamToRoom() {
        if (mRTCRoom != null) {
            Log.d(TAG, "stopForwardStreamToRoom");
            mRTCRoom.stopForwardStreamToRooms();
        }
    }

    public void muteRemoteAudio(String uid, boolean mute) {
        Log.d(TAG, "muteRemoteAudio uid:" + uid + ",mute:" + mute);
        if (mRTCRoom != null) {
            if (mute) {
                mRTCRoom.unsubscribeStream(uid, MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            } else {
                mRTCRoom.subscribeStream(uid, MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            }
        }
    }

    public void setUserVisibility(boolean userVisible) {
        if (mRTCRoom != null) {
            mRTCRoom.setUserVisibility(userVisible);
        }
    }

    /**
     * Initialize video effect.
     */
    private void initVideoEffect() {
        IEffect effect = ProtocolUtil.getIEffect();
        if (effect != null) {
            effect.initWithRTCVideo(mRTCVideo);
        }
    }

    public void resumeVideoEffect() {
        IEffect effect = ProtocolUtil.getIEffect();
        if (effect != null) {
            effect.resume();
        }
    }

    /**
     * Open effect dialog.
     * @param context context object.
     */
    public void openEffectDialog(Context context) {
        IEffect effect = ProtocolUtil.getIEffect();
        if (effect != null) {
            effect.showEffectDialog(context, null);
        }
    }
}
