/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.core;

import static com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_HIDDEN;
import static com.ss.bytertc.engine.data.AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
import static com.ss.bytertc.engine.type.RemoteUserPriority.REMOTE_USER_PRIORITY_HIGH;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.util.Pair;
import android.view.TextureView;

import androidx.annotation.NonNull;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCStream;
import com.ss.bytertc.engine.SubscribeVideoConfig;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoStreamDescription;
import com.ss.bytertc.engine.data.AudioMixingConfig;
import com.ss.bytertc.engine.data.CameraId;
import com.ss.bytertc.engine.data.ForwardStreamEventInfo;
import com.ss.bytertc.engine.data.ForwardStreamInfo;
import com.ss.bytertc.engine.data.ForwardStreamStateInfo;
import com.ss.bytertc.engine.data.MuteState;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoFrameInfo;
import com.ss.bytertc.engine.type.AudioVolumeInfo;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.LocalStreamStats;
import com.ss.bytertc.engine.type.RemoteStreamStats;
import com.ss.bytertc.engine.type.SubscribeMediaType;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.rtm.RTCEventHandlerWithRTM;
import com.volcengine.vertcdemo.core.net.rtm.RtmInfo;
import com.volcengine.vertcdemo.videochatdemo.bean.NetStatusBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.UserJoinedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.UserLeaveBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.core.event.AudioVolumeEvent;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class VideoChatRTCManager {

    private static final String TAG = "VideoChatRTCManager";

    private static VideoChatRTCManager sInstance;

    private final RTCEventHandlerWithRTM mIRTCEngineEventHandler = new RTCEventHandlerWithRTM() {

        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            Log.d(TAG, String.format("onRoomStateChanged: %s, %s, %d, %s", roomId, uid, state, extraInfo));
        }

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

        @Override
        public void onLocalStreamStats(LocalStreamStats stats) {
            super.onLocalStreamStats(stats);
            String selfUid = VideoChatDataManager.ins().selfUserInfo != null ? VideoChatDataManager.ins().selfUserInfo.userId : null;
            SolutionDemoEventManager.post(new NetStatusBroadcast(selfUid, stats.txQuality, stats.rxQuality));
        }

        @Override
        public void onRemoteStreamStats(RemoteStreamStats stats) {
            super.onRemoteStreamStats(stats);
            SolutionDemoEventManager.post(new NetStatusBroadcast(stats.uid, stats.txQuality, stats.rxQuality));
        }

        @Override
        public void onFirstRemoteVideoFrameRendered(RemoteStreamKey remoteStreamKey, VideoFrameInfo frameInfo) {
            Log.d(TAG, String.format("onFirstRemoteVideoFrameRendered: %s", remoteStreamKey.toString()));
        }

        @Override
        public void onForwardStreamStateChanged(ForwardStreamStateInfo[] stateInfos) {
            String result = "";
            for (ForwardStreamStateInfo info : stateInfos) {
                result = result.concat("|" + info.roomId + "," + info.error + "," + info.state + "|");
            }
            Log.d(TAG, String.format("onForwardStreamStateChanged: %s", result));
        }

        @Override
        public void onForwardStreamEvent(ForwardStreamEventInfo[] eventInfos) {
            String result = "";
            for (ForwardStreamEventInfo info : eventInfos) {
                result = result.concat("|" + info.roomId + "," + info.event + "|");
            }
            Log.d(TAG, String.format("onForwardStreamStateChanged: %s", result));
        }

        @Override
        public void onStreamAdd(RTCStream stream) {
            Log.d(TAG, String.format("onStreamAdd: %s", stream.toString()));
        }

        @Override
        public void onAudioVolumeIndication(AudioVolumeInfo[] speakers, int totalRemoteVolume) {
            super.onAudioVolumeIndication(speakers, totalRemoteVolume);
            SolutionDemoEventManager.post(new AudioVolumeEvent(speakers));
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            Log.d(TAG, String.format("onUserJoined: %s, %d", userInfo.getUid(), elapsed));
            SolutionDemoEventManager.post(new UserJoinedBroadcast(userInfo));
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            Log.d(TAG, String.format("onUserLeave: %s, %d", uid, reason));
            SolutionDemoEventManager.post(new UserLeaveBroadcast(uid, reason));
        }
    };

    private VideoChatRtmClient mRTMClient;

    private RTCEngine mRTCEngine;

    private final Map<String, TextureView> mUidViewMap = new HashMap<>();

    private boolean mIsCameraOn = true;
    private boolean mIsMicOn = true;
    private boolean mIsFront = true;
    private int mFrameRate = 15;
    private int mFrameWidth = 720;
    private int mFrameHeight = 1280;
    private int mBitrate = 1600;
    public boolean isTest = false;

    public static VideoChatRTCManager ins() {
        if (sInstance == null) {
            sInstance = new VideoChatRTCManager();
        }
        return sInstance;
    }

    public void initEngine(RtmInfo info) {
        destroyEngine();
        mRTCEngine = RTCEngine.createEngine(Utilities.getApplicationContext(), info.appId, mIRTCEngineEventHandler, null, null);
        mRTCEngine.stopVideoCapture();
        mRTCEngine.setAudioVolumeIndicationInterval(2000);

        VideoStreamDescription description = new VideoStreamDescription();
        description.videoSize = new Pair<>(720, 1280);
        description.frameRate = 15;
        description.maxKbps = 1600;
        mRTCEngine.setVideoEncoderConfig(Collections.singletonList(description));
        switchCamera(mIsFront);

        initBGMRes();
        mRTMClient = new VideoChatRtmClient(mRTCEngine, info);
        mIRTCEngineEventHandler.setBaseClient(mRTMClient);
    }

    public VideoChatRtmClient getRTMClient() {
        return mRTMClient;
    }

    public void switchCamera(boolean isFront) {
        if (mRTCEngine != null) {
            mRTCEngine.switchCamera(isFront ? CameraId.CAMERA_ID_FRONT : CameraId.CAMERA_ID_BACK);
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
        if (mRTCEngine != null) {
            if (isMicOn) {
                mRTCEngine.startAudioCapture();
                mRTCEngine.muteLocalAudio(MuteState.MUTE_STATE_OFF);
            } else {
                mRTCEngine.stopAudioCapture();
                mRTCEngine.muteLocalAudio(MuteState.MUTE_STATE_ON);
            }
        }
        Log.d(TAG, "turnOnMic : " + isMicOn);
        mIsMicOn = isMicOn;
        updateMicAndCameraStatus();
        postMediaStatus();
    }

    public void turnOnMic() {
        turnOnMic(!mIsMicOn);
    }

    public void turnOnCamera(boolean isCameraOn) {
        if (mRTCEngine != null) {
            if (isCameraOn) {
                mRTCEngine.startVideoCapture();
            } else {
                mRTCEngine.stopVideoCapture();
            }
        }
        mIsCameraOn = isCameraOn;
        Log.d(TAG, "turnOnCamera : " + isCameraOn);
        updateMicAndCameraStatus();
        postMediaStatus();
    }

    private void updateMicAndCameraStatus() {
        VCUserInfo selfUserInfo = VideoChatDataManager.ins().selfUserInfo;
        if (selfUserInfo == null) {
            return;
        }
        String hostUid = VideoChatDataManager.ins().hostUserInfo == null ? null : VideoChatDataManager.ins().hostUserInfo.userId;
        VideoChatDataManager.ins().selfUserInfo.mic = mIsMicOn ? VCUserInfo.MIC_STATUS_ON : VCUserInfo.MIC_STATUS_OFF;
        VideoChatDataManager.ins().selfUserInfo.camera = mIsCameraOn ? VCUserInfo.CAMERA_STATUS_ON : VCUserInfo.CAMERA_STATUS_OFF;
        if (selfUserInfo.isHost() && TextUtils.equals(selfUserInfo.userId, hostUid)) {
            VideoChatDataManager.ins().hostUserInfo.mic = mIsMicOn ? VCUserInfo.MIC_STATUS_ON : VCUserInfo.MIC_STATUS_OFF;
            VideoChatDataManager.ins().hostUserInfo.camera = mIsCameraOn ? VCUserInfo.CAMERA_STATUS_ON : VCUserInfo.CAMERA_STATUS_OFF;
        }
    }

    private void postMediaStatus() {
        // TODO handle the event
//        MediaChangedEvent event = new MediaChangedEvent();
//        String selfUid = SolutionDataManager.ins().getUserId();
//        event.userId = selfUid;
//        event.operatorUserId = selfUid;
//        event.mic = mIsMicOn ? LiveDataManager.MEDIA_STATUS_ON : LiveDataManager.MEDIA_STATUS_OFF;
//        event.camera = mIsCameraOn ? LiveDataManager.MEDIA_STATUS_ON : LiveDataManager.MEDIA_STATUS_OFF;
//        SolutionDemoEventManager.post(event);
    }

    public void turnOnCamera() {
        turnOnCamera(!mIsCameraOn);
    }

    public void setFrameRate(int frameRate) {
        mFrameRate = frameRate;
        updateVideoConfig();
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

    public int getFrameRate(){
        return mFrameRate;
    }
    public int getFrameWidth() {
        return mFrameWidth;
    }

    public int getBitrate() {
        return mBitrate;
    }

    private void updateVideoConfig() {
        if (mRTCEngine != null) {
            VideoStreamDescription description = new VideoStreamDescription();
            description.videoSize = new Pair<>(mFrameWidth, mFrameHeight);
            description.frameRate = mFrameRate;
            description.maxKbps = mBitrate;
            // mRTCEngine.setVideoEncoderConfig(Collections.singletonList(description));
        }
    }

    public void startMuteVideo(boolean isStart) {
        if (mRTCEngine != null) {
            mRTCEngine.muteLocalVideo(isStart ? MuteState.MUTE_STATE_ON : MuteState.MUTE_STATE_OFF);
        }
        Log.d(TAG, "startMuteVideo : " + isStart);
    }

    public void startVideoCapture(boolean isStart) {
        if (mRTCEngine != null) {
            if (isStart) {
                mRTCEngine.startVideoCapture();
            } else {
                mRTCEngine.stopVideoCapture();
            }
        }
        mIsCameraOn = isStart;
        Log.d(TAG, "startCaptureVideo : " + isStart);
    }

    public void startAudioCapture(boolean isStart) {
        if (mRTCEngine != null) {
            if (isStart) {
                mRTCEngine.startAudioCapture();
            } else {
                mRTCEngine.stopAudioCapture();
            }
        }
        mIsMicOn = isStart;
        Log.d(TAG, "startCaptureAudio : " + isStart);
    }

    public void setLocalVideoView(@NonNull TextureView surfaceView) {
        if (mRTCEngine == null) {
            return;
        }
        VideoCanvas videoCanvas = new VideoCanvas(surfaceView, RENDER_MODE_HIDDEN, "", false);
        mRTCEngine.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, null);
        mRTCEngine.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
        Log.d(TAG, "setLocalVideoView");
    }

    public TextureView getUserRenderView(String userId) {
        if (TextUtils.isEmpty(userId)) {
            return null;
        }
        TextureView view = mUidViewMap.get(userId);
        if (view == null) {
            view = new TextureView(Utilities.getApplicationContext());
            mUidViewMap.put(userId, view);
        }
        return view;
    }

    public void setRemoteVideoView(String userId, TextureView textureView) {
        Log.d(TAG, "setRemoteVideoView : " + userId + " ,rtc : " + mRTCEngine);
        if (mRTCEngine != null) {
            VideoCanvas canvas = new VideoCanvas(textureView, RENDER_MODE_HIDDEN, userId, false);
            mRTCEngine.setRemoteVideoCanvas(userId, StreamIndex.STREAM_INDEX_MAIN, null);
            mRTCEngine.setRemoteVideoCanvas(userId, StreamIndex.STREAM_INDEX_MAIN, canvas);
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
                copyAssetFile(Utilities.getApplicationContext(), "voicechat_bgm.mp3", bgmPath.getAbsolutePath());
            }
        });
    }

    private String getExternalResourcePath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/";
    }


    public void destroyEngine() {
        Log.d(TAG, "destroyEngine");
        RTCEngine.destroyEngine(mRTCEngine);
    }

    public void joinRoom(String roomId, String token, String userId, boolean userVisible) {
        Log.d(TAG, String.format("joinRoom: %s %s %s", roomId, userId, token));
        if (mRTCEngine != null) {
            RTCRoomConfig config = new RTCRoomConfig(
                    ChannelProfile.CHANNEL_PROFILE_LIVE_BROADCASTING,
                    true, true, true);
            setUserVisibility(userVisible);
            mRTCEngine.joinRoom(token, roomId, new UserInfo(userId, null), config);
        }
    }

    public void leaveRoom() {
        Log.d(TAG, "leaveRoom");
        if (mRTCEngine != null) {
            mRTCEngine.leaveRoom();
        }
    }

    public void startMuteAudio(boolean isStart) {
        Log.d(TAG, String.format("startMuteAudio: %b", isStart));
        if (mRTCEngine != null) {
            MuteState state = isStart ? MuteState.MUTE_STATE_ON : MuteState.MUTE_STATE_OFF;
            mRTCEngine.muteLocalAudio(state);
        }
    }

    public void startAudioMixing(boolean isStart) {
        Log.d(TAG, String.format("startAudioMixing: %b", isStart));
        if (mRTCEngine != null) {
            if (isStart) {
                String bgmPath = getExternalResourcePath() + "bgm/voicechat_bgm.mp3";
                mRTCEngine.getAudioMixingManager().preloadAudioMixing(0, bgmPath);
                AudioMixingConfig config = new AudioMixingConfig(AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH, -1);
                mRTCEngine.getAudioMixingManager().startAudioMixing(0, bgmPath, config);
            } else {
                mRTCEngine.getAudioMixingManager().stopAudioMixing(0);
            }
        }
    }

    public void resumeAudioMixing() {
        Log.d(TAG, "resumeAudioMixing");
        if (mRTCEngine != null) {
            mRTCEngine.getAudioMixingManager().resumeAudioMixing(0);
        }
    }

    public void pauseAudioMixing() {
        Log.d(TAG, "pauseAudioMixing");
        if (mRTCEngine != null) {
            mRTCEngine.getAudioMixingManager().pauseAudioMixing(0);
        }
    }

    public void adjustBGMVolume(int progress) {
        Log.d(TAG, String.format("adjustBGMVolume: %d", progress));
        if (mRTCEngine != null) {
            mRTCEngine.getAudioMixingManager().setAudioMixingVolume(0, progress, AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH);
        }
    }

    public void adjustUserVolume(int progress) {
        Log.d(TAG, String.format("adjustUserVolume: %d", progress));
        if (mRTCEngine != null) {
            mRTCEngine.setCaptureVolume(StreamIndex.STREAM_INDEX_MAIN, progress);
        }
    }

    public void forwardStreamToRoom(ForwardStreamInfo targetRoomInfo) {
        if (mRTCEngine != null) {
            ArrayList<ForwardStreamInfo> list = new ArrayList<>(1);
            list.add(targetRoomInfo);
            int result = mRTCEngine.startForwardStreamToRooms(list);
            Log.d(TAG, String.format("forwardStreamToRoom result: %d", result));
        }
    }

    public void stopForwardStreamToRoom() {
        if (mRTCEngine != null) {
            Log.d(TAG, "stopForwardStreamToRoom");
            mRTCEngine.stopForwardStreamToRooms();
        }
    }

    public void muteRemoteAudio(String uid, boolean mute) {
        Log.d(TAG, "muteRemoteAudio uid:" + uid + ",mute:" + mute);
        if (mRTCEngine != null) {
            SubscribeMediaType type = mute ? SubscribeMediaType.RTC_SUBSCRIBE_MEDIA_TYPE_VIDEO_ONLY
                    : SubscribeMediaType.RTC_SUBSCRIBE_MEDIA_TYPE_AUDIO_AND_VIDEO;
            SubscribeVideoConfig config = new SubscribeVideoConfig(0, REMOTE_USER_PRIORITY_HIGH.value());
            mRTCEngine.subscribeUserStream(uid, StreamIndex.STREAM_INDEX_MAIN, type, config);
        }
    }

    public void setUserVisibility(boolean userVisible) {
        if (mRTCEngine != null) {
            mRTCEngine.setUserVisibility(userVisible);
        }
    }

    public static boolean copyAssetFolder(Context context, String srcName, String dstName) {
        try {
            boolean result = true;
            String fileList[] = context.getAssets().list(srcName);
            if (fileList == null) return false;

            if (fileList.length == 0) {
                result = copyAssetFile(context, srcName, dstName);
            } else {
                File file = new File(dstName);
                result = file.mkdirs();
                for (String filename : fileList) {
                    result &= copyAssetFolder(context, srcName + File.separator + filename, dstName + File.separator + filename);
                }
            }
            return result;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }


    public static boolean copyAssetFile(Context context, String srcName, String dstName) {
        try {
            InputStream in = context.getAssets().open(srcName);
            File outFile = new File(dstName);
            OutputStream out = new FileOutputStream(outFile);
            byte[] buffer = new byte[1024];
            int read;
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
            in.close();
            out.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
}
