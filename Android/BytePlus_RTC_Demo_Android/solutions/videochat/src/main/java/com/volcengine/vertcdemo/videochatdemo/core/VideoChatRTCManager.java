/**
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

package com.volcengine.vertcdemo.videochatdemo.core;

import static com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_HIDDEN;
import static com.ss.bytertc.engine.data.AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;

import androidx.annotation.NonNull;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCStream;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.data.AudioMixingConfig;
import com.ss.bytertc.engine.data.AudioPropertiesConfig;
import com.ss.bytertc.engine.data.CameraId;
import com.ss.bytertc.engine.data.ForwardStreamEventInfo;
import com.ss.bytertc.engine.data.ForwardStreamInfo;
import com.ss.bytertc.engine.data.ForwardStreamStateInfo;
import com.ss.bytertc.engine.data.MirrorType;
import com.ss.bytertc.engine.data.RemoteAudioPropertiesInfo;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoFrameInfo;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.LocalStreamStats;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RemoteStreamStats;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.volcengine.vertcdemo.core.SolutionDataManager;
import com.volcengine.vertcdemo.core.eventbus.AudioVolumeEvent;
import com.volcengine.vertcdemo.core.eventbus.SolutionDemoEventManager;
import com.volcengine.vertcdemo.core.net.rtm.RTCEventHandlerWithRTS;
import com.volcengine.vertcdemo.core.net.rtm.RTCRoomEventHandlerWithRTS;
import com.volcengine.vertcdemo.core.net.rtm.RTSInfo;
import com.volcengine.vertcdemo.videochat.R;
import com.volcengine.vertcdemo.videochatdemo.bean.NetStatusBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.UserJoinedBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.UserLeaveBroadcast;
import com.volcengine.vertcdemo.videochatdemo.bean.VCUserInfo;
import com.volcengine.vertcdemo.videochatdemo.common.VideoChatEffectBeautyLayout;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class VideoChatRTCManager {

    private static final String TAG = "VideoChatRTCManager";

    private static VideoChatRTCManager sInstance;

    private final RTCEventHandlerWithRTS mRTCVideoEventHandler = new RTCEventHandlerWithRTS() {

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
        public void onFirstRemoteVideoFrameRendered(RemoteStreamKey remoteStreamKey, VideoFrameInfo frameInfo) {
            Log.d(TAG, String.format("onFirstRemoteVideoFrameRendered: %s", remoteStreamKey.toString()));
        }

        @Override
        public void onRemoteAudioPropertiesReport(RemoteAudioPropertiesInfo[] audioPropertiesInfos, int totalRemoteVolume) {
            super.onRemoteAudioPropertiesReport(audioPropertiesInfos, totalRemoteVolume);
            AudioVolumeEvent.Info[] infos = new AudioVolumeEvent.Info[audioPropertiesInfos.length];
            for (int i = 0; i < audioPropertiesInfos.length; i++) {
                final RemoteAudioPropertiesInfo property = audioPropertiesInfos[i];
                infos[i] = new AudioVolumeEvent.Info(
                        property.streamKey.getUserId(),
                        property.audioPropertiesInfo.linearVolume
                );
            }
            SolutionDemoEventManager.post(new AudioVolumeEvent(infos));
        }
    };

    private final RTCRoomEventHandlerWithRTS mRTCRoomEventHandler = new RTCRoomEventHandlerWithRTS() {

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

        @Override
        public void onStreamAdd(RTCStream stream) {
            Log.d(TAG, String.format("onStreamAdd: %s", stream.toString()));
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
        public void onForwardStreamStateChanged(ForwardStreamStateInfo[] stateInfos) {
            String result = "";
            for (ForwardStreamStateInfo info : stateInfos) {
                result = result.concat("|" + info.roomId + "," + info.error + "," + info.state + "|");
            }
            Log.d(TAG, String.format("onForwardStreamStateChanged: %s", result));
        }
    };

    private VideoChatRTSClient mRTMClient;

    private RTCVideo mRTCVideo;
    private RTCRoom mRTCRoom;
    // Effect
    private final ArrayList<String> mEffectPathList = new ArrayList<>();
    private String mLastFilter = "";
    private float mLastFilterValue = 0;
    private String mLastStickerPath = "";
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

    public void initEngine(RTSInfo info) {
        destroyEngine();
        mRTCVideo = RTCVideo.createRTCVideo(Utilities.getApplicationContext(), info.appId, mRTCVideoEventHandler, null, null);
        mRTCVideo.enableAudioPropertiesReport(new AudioPropertiesConfig(2000));
        mRTCVideo.stopVideoCapture();

        mRTCVideo.setLocalVideoMirrorType(MirrorType.MIRROR_TYPE_RENDER_AND_ENCODER);

        final VideoEncoderConfig encoderConfig = new VideoEncoderConfig(720, 1280,
                15,
                1600);
        mRTCVideo.setVideoEncoderConfig(encoderConfig);
        switchCamera(mIsFront);

        AppExecutors.diskIO().execute(this::initEffect);
        initBGMRes();
        mRTMClient = new VideoChatRTSClient(mRTCVideo, info);
        mRTCVideoEventHandler.setBaseClient(mRTMClient);
        mRTCRoomEventHandler.setBaseClient(mRTMClient);
    }

    public VideoChatRTSClient getRTMClient() {
        return mRTMClient;
    }

    public void switchCamera(boolean isFront) {
        if (mRTCVideo != null) {
            mRTCVideo.switchCamera(isFront ? CameraId.CAMERA_ID_FRONT : CameraId.CAMERA_ID_BACK);
            mIsFront = isFront;
            setLocalVideoMirror();
        }
    }

    /**
     * 设置视频镜像，前置摄像头开启镜像，后置摄像头不开启镜像
     */
    private void setLocalVideoMirror() {
        mRTCVideo.setLocalVideoMirrorType(mIsFront
                ? MirrorType.MIRROR_TYPE_RENDER_AND_ENCODER
                : MirrorType.MIRROR_TYPE_NONE);
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
        postMediaStatus();
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

    public int getFrameRate() {
        return mFrameRate;
    }

    public int getFrameWidth() {
        return mFrameWidth;
    }

    public int getBitrate() {
        return mBitrate;
    }

    private void updateVideoConfig() {
        if (mRTCVideo != null) {
            final VideoEncoderConfig solution = new VideoEncoderConfig(mFrameWidth, mFrameHeight,
                    mFrameRate,
                    mBitrate);
            // mRTCVideo.setVideoEncoderConfig(solution);
        }
    }

    public void startMuteVideo(boolean isStart) {
        if (mRTCRoom != null) {
            if (isStart) {
                mRTCRoom.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_VIDEO);
            } else {
                mRTCRoom.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_VIDEO);
            }
        }
        Log.d(TAG, "startMuteVideo : " + isStart);
    }

    public void startVideoCapture(boolean isStart) {
        if (mRTCVideo != null) {
            if (isStart) {
                mRTCVideo.startVideoCapture();
            } else {
                mRTCVideo.stopVideoCapture();
            }
            mIsCameraOn = isStart;
        }
        Log.d(TAG, "startCaptureVideo : " + isStart);
    }

    public void startAudioCapture(boolean isStart) {
        if (mRTCVideo != null) {
            if (isStart) {
                mRTCVideo.startAudioCapture();
            } else {
                mRTCVideo.stopAudioCapture();
            }
            mIsMicOn = isStart;
        }
        Log.d(TAG, "startCaptureAudio : " + isStart);
    }

    public void setLocalVideoView(@NonNull TextureView textureView) {
        if (mRTCVideo == null) {
            return;
        }
        VideoCanvas videoCanvas = new VideoCanvas(textureView, RENDER_MODE_HIDDEN,
                SolutionDataManager.ins().getUserId(), false);
        mRTCVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
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

    public void setRemoteVideoView(String roomId, String userId, TextureView textureView) {
        Log.d(TAG, "setRemoteVideoView : " + userId + " ,rtc : " + mRTCVideo);
        if (mRTCVideo != null) {
            VideoCanvas canvas = new VideoCanvas(textureView, RENDER_MODE_HIDDEN, userId, false);
            canvas.roomId = roomId;
            mRTCVideo.setRemoteVideoCanvas(userId, StreamIndex.STREAM_INDEX_MAIN, canvas);
        }
    }

    private void initEffect() {
        if (mRTCVideo != null) {
            initEffectPath();
            mRTCVideo.checkVideoEffectLicense(Utilities.getApplicationContext(), getLicensePath());
            mRTCVideo.setVideoEffectAlgoModelPath(getEffectAlgoModelPath());
            mRTCVideo.enableVideoEffect(true);

            mEffectPathList.add(getByteComposePath());
            mEffectPathList.add(getByteShapePath());
            setVideoEffectNodes(mEffectPathList);
            setStickerNodes(mLastStickerPath);

            updateVideoEffectNode();

            setVideoEffectColorFilter(mLastFilter);
            updateColorFilterIntensity(mLastFilterValue);

            initBeautyValue();
        }
    }

    private void initBeautyValue() {
        for (Map.Entry<Integer, Integer> entry : VideoChatEffectBeautyLayout.sSeekBarProgressMap.entrySet()) {
            int key = entry.getKey();
            float value = ((float) entry.getValue() / 100);
            if (key == R.id.effect_whiten) {
                updateVideoEffectNode(getByteComposePath(), "whiten", value);
            } else if (key == R.id.effect_smooth) {
                updateVideoEffectNode(getByteComposePath(), "smooth", value);
            } else if (key == R.id.effect_big_eye) {
                updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Eye", value);
            } else if (key == R.id.effect_sharp) {
                updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Overall", value);
            }
        }
    }

    private void initEffectPath() {
        File licensePath = new File(getExternalResourcePath(), "cvlab/LicenseBag.bundle");
        if (!licensePath.exists()) {
            copyAssetFolder(Utilities.getApplicationContext(), "cvlab/LicenseBag.bundle", licensePath.getAbsolutePath());
        }
        File modelPath = new File(getExternalResourcePath(), "cvlab/ModelResource.bundle");
        if (!modelPath.exists()) {
            copyAssetFolder(Utilities.getApplicationContext(), "cvlab/ModelResource.bundle", modelPath.getAbsolutePath());
        }
        File stickerPath = new File(getExternalResourcePath(), "cvlab/StickerResource.bundle");
        if (!stickerPath.exists()) {
            copyAssetFolder(Utilities.getApplicationContext(), "cvlab/StickerResource.bundle", stickerPath.getAbsolutePath());
        }
        File filterPath = new File(getExternalResourcePath(), "cvlab/FilterResource.bundle");
        if (!filterPath.exists()) {
            copyAssetFolder(Utilities.getApplicationContext(), "cvlab/FilterResource.bundle", filterPath.getAbsolutePath());
        }
        File composerPath = new File(getExternalResourcePath(), "cvlab/ComposeMakeup.bundle");
        if (!composerPath.exists()) {
            copyAssetFolder(Utilities.getApplicationContext(), "cvlab/ComposeMakeup.bundle", composerPath.getAbsolutePath());
        }
    }

    private String getLicensePath() {
        return new File(getExternalResourcePath(), "cvlab/LicenseBag.bundle").getAbsolutePath() +
                "";
    }

    private String getEffectAlgoModelPath() {
        return new File(getExternalResourcePath(), "cvlab/ModelResource.bundle").getAbsolutePath();
    }

    private Map<String, Map<String, Float>> mEffectValue = new HashMap<>();

    public String getByteStickerPath() {
        File stickerPath = new File(Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/", "cvlab/StickerResource.bundle");
        return stickerPath.getAbsolutePath() + "/";
    }

    private String getByteComposePath() {
        File composerPath = new File(Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath() + "/ComposeMakeup/beauty_Android_live";
    }

    private String getByteShapePath() {
        File composerPath = new File(Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath() + "/ComposeMakeup/reshape_live";
    }

    public void setVideoEffectNodes(List<String> pathList) {
        if (mRTCVideo != null) {
            mRTCVideo.setVideoEffectNodes(pathList);
        }
    }

    public void setStickerNodes(String path) {
        if (mRTCVideo != null) {
            ArrayList<String> pathList = new ArrayList<>(mEffectPathList);
            if (!TextUtils.isEmpty(path)) {
                pathList.add(getByteStickerPath() + path);
            }
            mRTCVideo.setVideoEffectNodes(pathList);
        }
        mLastStickerPath = path;
    }

    public String getStickerPath() {
        return mLastStickerPath;
    }

    private void updateVideoEffectNode() {
        if (mRTCVideo != null) {
            for (Map.Entry<String, Map<String, Float>> entry : mEffectValue.entrySet()) {
                String path = entry.getKey();
                Map<String, Float> keyValue = entry.getValue();
                for (Map.Entry<String, Float> temp : keyValue.entrySet()) {
                    updateVideoEffectNode(path, temp.getKey(), temp.getValue());
                }
            }
        }
    }

    public void updateVideoEffectNode(String path, String key, float val) {
        if (mRTCVideo != null) {
            mRTCVideo.updateVideoEffectNode(path, key, val);
        }
        Map<String, Float> keyValue = mEffectValue.get(path);
        if (keyValue == null) {
            keyValue = new HashMap<>();
            mEffectValue.put(path, keyValue);
        }
        keyValue.put(key, val);
    }

    public void setVideoEffectColorFilter(String path) {
        if (mRTCVideo != null) {
            mRTCVideo.setVideoEffectColorFilter(path);
        }
        mLastFilter = path;
    }

    public void updateColorFilterIntensity(float intensity) {
        if (mRTCVideo != null) {
            mRTCVideo.setVideoEffectColorFilterIntensity(intensity);
        }
        mLastFilterValue = intensity;
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
        RTCVideo.destroyRTCVideo();
    }

    public void joinRoom(String roomId, String token, String userId, boolean userVisible) {
        Log.d(TAG, String.format("joinRoom: %s %s %s", roomId, userId, token));
        if (mRTCVideo != null) {
            RTCRoomConfig config = new RTCRoomConfig(
                    ChannelProfile.CHANNEL_PROFILE_COMMUNICATION,
                    true, true, true);

            mRTCRoom = mRTCVideo.createRTCRoom(roomId);
            mRTCRoom.setRTCRoomEventHandler(mRTCRoomEventHandler);
            mRTCRoom.setUserVisibility(userVisible);
            mRTCRoom.joinRoom(token, new UserInfo(userId, null), config);
        }
    }

    public void leaveRoom() {
        Log.d(TAG, "leaveRoom");
        if (mRTCRoom != null) {
            mRTCRoom.leaveRoom();
            mRTCRoom.destroy();
        }
    }

    public void startMuteAudio(boolean mute) {
        Log.d(TAG, String.format("startMuteAudio: %b", mute));
        if (mRTCRoom != null) {
            if (mute) {
                mRTCRoom.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            } else {
                mRTCRoom.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
            }
        }
    }

    public void startAudioMixing(boolean isStart) {
        Log.d(TAG, String.format("startAudioMixing: %b", isStart));
        if (mRTCVideo != null) {
            if (isStart) {
                String bgmPath = getExternalResourcePath() + "bgm/voicechat_bgm.mp3";
                mRTCVideo.getAudioMixingManager().preloadAudioMixing(0, bgmPath);
                AudioMixingConfig config = new AudioMixingConfig(AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH, -1);
                mRTCVideo.getAudioMixingManager().startAudioMixing(0, bgmPath, config);
            } else {
                mRTCVideo.getAudioMixingManager().stopAudioMixing(0);
            }
        }
    }

    public void resumeAudioMixing() {
        Log.d(TAG, "resumeAudioMixing");
        if (mRTCVideo != null) {
            mRTCVideo.getAudioMixingManager().resumeAudioMixing(0);
        }
    }

    public void pauseAudioMixing() {
        Log.d(TAG, "pauseAudioMixing");
        if (mRTCVideo != null) {
            mRTCVideo.getAudioMixingManager().pauseAudioMixing(0);
        }
    }

    public void adjustBGMVolume(int progress) {
        Log.d(TAG, String.format("adjustBGMVolume: %d", progress));
        if (mRTCVideo != null) {
            mRTCVideo.getAudioMixingManager().setAudioMixingVolume(0, progress, AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH);
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
            int result = mRTCRoom.startForwardStreamToRooms(Collections.singletonList(targetRoomInfo));
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
