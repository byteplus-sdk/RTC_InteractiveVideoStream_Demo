// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatRTCManager.h"
#import "VideoChatSettingVideoConfig.h"

@interface VideoChatRTCManager () <ByteRTCVideoDelegate>

// RTC / RTS room object
@property (nonatomic, strong, nullable) ByteRTCRoom *rtcRoom;
@property (nonatomic, assign) int audioMixingID;
@property (nonatomic, assign) ByteRTCCameraID cameraID;
@property (nonatomic, strong) NSMutableDictionary<NSString *, UIView *> *streamViewDic;
@property (nonatomic, copy) VideoChatNetworkQualityChangeBlock networkQualityBlock;
@property (nonatomic, strong) ByteRTCVideoEncoderConfig *encoderConfig;

@end

@implementation VideoChatRTCManager

+ (VideoChatRTCManager *_Nullable)shareRtc {
    static VideoChatRTCManager *rtcManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        rtcManager = [[VideoChatRTCManager alloc] init];
    });
    return rtcManager;
}

- (void)configeRTCEngine {
    [super configeRTCEngine];
    _cameraID = ByteRTCCameraIDFront;
    _audioMixingID = 3001;
}

- (void)joinRTCRoomWithToken:(NSString *)token
                      roomID:(NSString *)roomID
                         uid:(NSString *)uid
                    userRole:(BOOL)isHost {
    // Set the audio routing mode, YES speaker/NO earpiece
    [self.rtcEngineKit setDefaultAudioRoute:ByteRTCAudioRouteSpeakerphone];
    // Turn on/off speaker volume keying
    ByteRTCAudioPropertiesConfig *audioPropertiesConfig = [[ByteRTCAudioPropertiesConfig alloc] init];
    audioPropertiesConfig.interval = 300;
    [self.rtcEngineKit enableAudioPropertiesReport:audioPropertiesConfig];
    // Enable local and encoded mirroring
    if (self.cameraID == ByteRTCCameraIDFront) {
        [self.rtcEngineKit setLocalVideoMirrorType:ByteRTCMirrorTypeRenderAndEncoder];
    } else {
        [self.rtcEngineKit setLocalVideoMirrorType:ByteRTCMirrorTypeNone];
    }
    // Join the room, start connecting the microphone, you need to apply for AppId and Token
    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = uid;
    
    ByteRTCRoomConfig *config = [[ByteRTCRoomConfig alloc] init];
    config.profile = ByteRTCRoomProfileInteractivePodcast;
    config.isAutoPublish = YES;
    config.isAutoSubscribeAudio = YES;
    config.isAutoSubscribeVideo = YES;
    
    self.rtcRoom = [self.rtcEngineKit createRTCRoom:roomID];
    self.rtcRoom.delegate = self;
    [self.rtcRoom joinRoom:token userInfo:userInfo roomConfig:config];
    
    if (!isHost) {
        // Local audio/video capture needs to be turned off when audience join the room
        [self.rtcEngineKit stopAudioCapture];
        [self.rtcEngineKit stopVideoCapture];
        
        // When audience join the room, they need to be set as invisible
        [self.rtcRoom setUserVisibility:NO];
    }
}

- (void)leaveRTCRoom {
    // Leave the RTC room
    ByteRTCAudioEffectPlayer *audioManager = [self.rtcEngineKit getAudioEffectPlayer];
    [audioManager stop:_audioMixingID];
    [self.rtcEngineKit stopAudioCapture];
    [self switchFrontFacingCamera:YES];
    [self.rtcRoom leaveRoom];
    [self.streamViewDic removeAllObjects];
}

#pragma mark - Make Guest

- (void)makeGuest:(BOOL)camera
       microphone:(BOOL)microphone {
    [self.rtcRoom setUserVisibility:YES];
    // Switch microphone, camera capture
    [self switchVideoCapture:camera];
    [self switchAudioCapture:microphone];
}

- (void)makeAudience {
    [self.rtcRoom setUserVisibility:NO];
    // Switch microphone, camera capture
    [self switchVideoCapture:NO];
    [self switchAudioCapture:NO];
    // switch to front camera
    [self switchFrontFacingCamera:YES];
}

#pragma mark - Make CoHost

- (void)startForwardStream:(NSString *)roomID token:(NSString *)token {
    [self stopForwardStream];
    // enable start forward stream
    ByteRTCForwardStreamConfiguration *configuration = [[ByteRTCForwardStreamConfiguration alloc] init];
    configuration.roomId = roomID;
    configuration.token = token;
    [self.rtcRoom startForwardStreamToRooms:@[configuration]];
}

- (void)stopForwardStream {
    // enable stop forward stream
    [self.rtcRoom stopForwardStreamToRooms];
}

#pragma mark - Setting

- (void)switchVideoCapture:(BOOL)enable {
    // Turn on/off local video capture
    if (enable) {
        [SystemAuthority authorizationStatusWithType:AuthorizationTypeCamera
                                               block:^(BOOL isAuthorize) {
            if (isAuthorize) {
                [self.rtcEngineKit startVideoCapture];
                [self.rtcRoom publishStream:ByteRTCMediaStreamTypeVideo];
            }
        }];
    } else {
        [self.rtcEngineKit stopVideoCapture];
    }
}

- (void)switchCamera {
    // Switch front/rear camera
    if (self.cameraID == ByteRTCCameraIDFront) {
        self.cameraID = ByteRTCCameraIDBack;
    } else {
        self.cameraID = ByteRTCCameraIDFront;
    }
    [self switchFrontFacingCamera:(self.cameraID == ByteRTCCameraIDFront)];
}

- (void)publishVideoStream:(BOOL)isPublish {
    if (isPublish) {
        [self.rtcRoom publishStream:ByteRTCMediaStreamTypeVideo];
    } else {
        [self.rtcRoom unpublishStream:ByteRTCMediaStreamTypeVideo];
    }
}

- (void)publishAudioStream:(BOOL)isPublish {
    if (isPublish) {
        [self.rtcRoom publishStream:ByteRTCMediaStreamTypeAudio];
    } else {
        [self.rtcRoom unpublishStream:ByteRTCMediaStreamTypeAudio];
    }
}

- (void)subscribeRemoteAudioStream:(NSString *)userID
                         subscribe:(BOOL)isSubscribe {
    // Subscribe/Unsubscribe remote audio stream
    if (isSubscribe) {
        [self.rtcRoom subscribeStream:userID
                      mediaStreamType:ByteRTCMediaStreamTypeAudio];
    } else {
        [self.rtcRoom unsubscribeStream:userID
                        mediaStreamType:ByteRTCMediaStreamTypeAudio];
    }
}

- (void)updateVideoConfigWithHost:(BOOL)isHost {
    if (isHost) {
        VideoChatSettingVideoConfig *config = [VideoChatSettingVideoConfig defultVideoConfig];
        
        self.encoderConfig.width = config.videoSize.width;
        self.encoderConfig.height = config.videoSize.height;
        self.encoderConfig.frameRate = config.fps;
        self.encoderConfig.maxBitrate = config.bitrate;
        
        [self.rtcEngineKit setMaxVideoEncoderConfig:self.encoderConfig];
    } else {
        self.encoderConfig.width = 240;
        self.encoderConfig.height = 320;
        self.encoderConfig.frameRate = 15;
        self.encoderConfig.maxBitrate = 400;
        [self.rtcEngineKit setMaxVideoEncoderConfig:self.encoderConfig];
    }
}

- (void)updateResolution:(CGSize)size {
    self.encoderConfig.width = size.width;
    self.encoderConfig.height = size.height;
    [self.rtcEngineKit setMaxVideoEncoderConfig:self.encoderConfig];
}

- (void)updateFrameRate:(CGFloat)fps {
    self.encoderConfig.frameRate = fps;
    [self.rtcEngineKit setMaxVideoEncoderConfig:self.encoderConfig];
}

- (void)updateBitRate:(NSInteger)bitRate {
    self.encoderConfig.maxBitrate = bitRate;
    [self.rtcEngineKit setMaxVideoEncoderConfig:self.encoderConfig];
}

#pragma mark - Background Music Method

- (void)startBackgroundMusic:(NSString *)filePath {
    if (IsEmptyStr(filePath)) {
        return;
    }
    ByteRTCAudioEffectPlayer *audioManager = [self.rtcEngineKit getAudioEffectPlayer];
    
    ByteRTCAudioEffectPlayerConfig *config = [[ByteRTCAudioEffectPlayerConfig alloc] init];
    config.type = ByteRTCAudioMixingTypePlayoutAndPublish;
    config.playCount = -1;
    [audioManager start:_audioMixingID filePath:filePath config:config];
}

- (void)pauseBackgroundMusic {
    ByteRTCAudioEffectPlayer *audioManager = [self.rtcEngineKit getAudioEffectPlayer];
    
    [audioManager pause:_audioMixingID];
}

- (void)resumeBackgroundMusic {
    ByteRTCAudioEffectPlayer *audioManager = [self.rtcEngineKit getAudioEffectPlayer];
    
    [audioManager resume:_audioMixingID];
}

- (void)setRecordingVolume:(NSInteger)volume {
    [self.rtcEngineKit setCaptureVolume:ByteRTCStreamIndexMain volume:(int)volume];
}

- (void)setMusicVolume:(NSInteger)volume {
    ByteRTCAudioEffectPlayer *audioManager = [self.rtcEngineKit getAudioEffectPlayer];
    
    [audioManager setVolume:_audioMixingID volume:(int)volume];
}

#pragma mark - Render

- (UIView *)getStreamViewWithUid:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return nil;
    }
    NSString *typeStr = @"";
    if ([uid isEqualToString:[LocalUserComponent userModel].uid]) {
        typeStr = @"self";
    } else {
        typeStr = @"remote";
    }
    NSString *key = [NSString stringWithFormat:@"%@_%@", typeStr, uid];
    UIView *view = self.streamViewDic[key];
    return view;
}

- (void)bindCanvasViewToUid:(NSString *)uid {
    dispatch_queue_async_safe(dispatch_get_main_queue(), (^{
        if ([uid isEqualToString:[LocalUserComponent userModel].uid]) {
            UIView *view = [self getStreamViewWithUid:uid];
            if (!view) {
                UIView *streamView = [[UIView alloc] init];
                streamView.hidden = YES;
                ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
                canvas.renderMode = ByteRTCRenderModeHidden;
                canvas.view.backgroundColor = [UIColor clearColor];
                canvas.view = streamView;
                [self.rtcEngineKit setLocalVideoCanvas:ByteRTCStreamIndexMain
                                            withCanvas:canvas];
                NSString *key = [NSString stringWithFormat:@"self_%@", uid];
                [self.streamViewDic setValue:streamView forKey:key];
            }
        } else {
            UIView *remoteRoomView = [self getStreamViewWithUid:uid];
            if (!remoteRoomView) {
                remoteRoomView = [[UIView alloc] init];
                remoteRoomView.hidden = NO;
                ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
                canvas.renderMode = ByteRTCRenderModeHidden;
                canvas.view.backgroundColor = [UIColor clearColor];
                canvas.view = remoteRoomView;
                
                ByteRTCRemoteStreamKey *streamKey = [[ByteRTCRemoteStreamKey alloc] init];
                streamKey.userId = uid;
                streamKey.roomId = self.rtcRoom.getRoomId;
                streamKey.streamIndex = ByteRTCStreamIndexMain;
                
                [self.rtcEngineKit setRemoteVideoCanvas:streamKey withCanvas:canvas];
                
                NSString *groupKey = [NSString stringWithFormat:@"remote_%@", uid];
                [self.streamViewDic setValue:remoteRoomView forKey:groupKey];
            }
        }
    }));
}

#pragma mark - NetworkQuality

- (void)didChangeNetworkQuality:(VideoChatNetworkQualityChangeBlock)block {
    self.networkQualityBlock = block;
}

#pragma mark - ByteRTCRoomDelegate

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomStateChanged:(NSString *)roomId
        withUid:(NSString *)uid
          state:(NSInteger)state
      extraInfo:(NSString *)extraInfo {
    [super rtcRoom:rtcRoom onRoomStateChanged:roomId withUid:uid state:state extraInfo:extraInfo];
    [[VideoChatRTCManager shareRtc] bindCanvasViewToUid:uid];
    
    dispatch_queue_async_safe(dispatch_get_main_queue(), ^{
        RTCJoinModel *joinModel = [RTCJoinModel modelArrayWithClass:extraInfo state:state roomId:roomId];
        if ([self.delegate respondsToSelector:@selector(videoChatRTCManager:onRoomStateChanged:)]) {
            [self.delegate videoChatRTCManager:self onRoomStateChanged:joinModel];
        }
    });
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed {
    [[VideoChatRTCManager shareRtc] bindCanvasViewToUid:userInfo.userId];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *)stats {

    VideoChatNetworkQualityStatus liveStatus = VideoChatNetworkQualityStatusNone;
    if (stats.txQuality == ByteRTCNetworkQualityExcellent ||
        stats.txQuality == ByteRTCNetworkQualityGood) {
        liveStatus = VideoChatNetworkQualityStatusGood;
    } else {
        liveStatus = VideoChatNetworkQualityStatusBad;
    }
    if ([self.delegate respondsToSelector:@selector(videoChatRTCManager:didChangeNetworkQuality:uid:)]) {
        [self.delegate videoChatRTCManager:self
                   didChangeNetworkQuality:liveStatus
                                       uid:[LocalUserComponent userModel].uid];
    }
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *)stats {
    VideoChatNetworkQualityStatus liveStatus = VideoChatNetworkQualityStatusNone;
    if (stats.txQuality == ByteRTCNetworkQualityExcellent ||
        stats.txQuality == ByteRTCNetworkQualityGood) {
        liveStatus = VideoChatNetworkQualityStatusGood;
    } else {
        liveStatus = VideoChatNetworkQualityStatusBad;
    }
    if ([self.delegate respondsToSelector:@selector(videoChatRTCManager:didChangeNetworkQuality:uid:)]) {
        [self.delegate videoChatRTCManager:self
                   didChangeNetworkQuality:liveStatus
                                       uid:stats.uid];
    }
}

#pragma mark - ByteRTCVideoDelegate

- (void)rtcEngine:(ByteRTCVideo *)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey *)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *)frameInfo {
    dispatch_queue_async_safe(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(videoChatRTCManager:onFirstRemoteVideoUid:)]) {
            [self.delegate videoChatRTCManager:self onFirstRemoteVideoUid:streamKey.userId];
        }
    });   
}

- (void)rtcEngine:(ByteRTCVideo *)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> *)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    for (int i = 0; i < audioPropertiesInfos.count; i++) {
        ByteRTCRemoteAudioPropertiesInfo *model = audioPropertiesInfos[i];
        [dic setValue:@(model.audioPropertiesInfo.linearVolume) forKey:model.streamKey.userId];
    }
    if ([self.delegate respondsToSelector:@selector(videoChatRTCManager:reportAllAudioVolume:)]) {
        [self.delegate videoChatRTCManager:self reportAllAudioVolume:dic];
    }
}

#pragma mark - Private Action

- (void)switchAudioCapture:(BOOL)enable {
    // Turn on/off local audio capture
    if (enable) {
        [SystemAuthority authorizationStatusWithType:AuthorizationTypeAudio
                                               block:^(BOOL isAuthorize) {
            if (isAuthorize) {
                [self.rtcEngineKit startAudioCapture];
                [self.rtcRoom publishStream:ByteRTCMediaStreamTypeAudio];
            }
        }];
    } else {
        [self.rtcEngineKit stopAudioCapture];
    }
}

- (void)switchFrontFacingCamera:(BOOL)isFront {
    self.cameraID = isFront ? ByteRTCCameraIDFront : ByteRTCCameraIDBack;
    
    if (self.cameraID == ByteRTCCameraIDFront) {
        [self.rtcEngineKit setLocalVideoMirrorType:ByteRTCMirrorTypeRenderAndEncoder];
    } else {
        [self.rtcEngineKit setLocalVideoMirrorType:ByteRTCMirrorTypeNone];
    }
    
    [self.rtcEngineKit switchCamera:self.cameraID];
}

#pragma mark - Getter

- (NSMutableDictionary<NSString *, UIView *> *)streamViewDic {
    if (!_streamViewDic) {
        _streamViewDic = [[NSMutableDictionary alloc] init];
    }
    return _streamViewDic;
}

- (ByteRTCVideoEncoderConfig *)encoderConfig {
    if(!_encoderConfig) {
        _encoderConfig = [[ByteRTCVideoEncoderConfig alloc] init];
    }
    return _encoderConfig;
}
@end
