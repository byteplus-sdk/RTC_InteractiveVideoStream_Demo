/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatRoomSettingCompoments.h"
#import "VideoChatRTMManager.h"
#import "VideoChatCreateRoomSettingView.h"
#import "VideoChatRTCManager.h"
#import "VideoChatRoomGuestSettingView.h"
#import "VideoChatSettingVideoConfig.h"

@interface VideoChatRoomSettingCompoments () <VideoChatCreateRoomSettingViewDelegate, VideoChatRoomGuestSettingViewDelegate>

@property (nonatomic, weak) UIView *superView;
@property (nonatomic, strong) VideoChatCreateRoomSettingView *createRoomSettingView;
@property (nonatomic, strong) VideoChatRoomGuestSettingView *guestSettingView;
@property (nonatomic, strong) VideoChatRoomModel *videoChatRoomModel;
@property (nonatomic, strong) UIButton *maskButton;
@property (nonatomic, assign) BOOL isHost;

@end

@implementation VideoChatRoomSettingCompoments

- (void)dealloc {
    NSLog(@"%@,%s", [NSThread currentThread], __func__);
}

- (instancetype)initWithHost:(BOOL)isHost {
    self = [super init];
    if (self) {
        _mic = YES;
        _camera = YES;
        self.isHost = isHost;
    }
    return self;
}

- (void)showWithType:(VideoChatRoomSettingType)type
       fromSuperView:(UIView *)superView
           roomModel:(VideoChatRoomModel *)videoChatRoomModel {
    
    self.superView = superView;
    _videoChatRoomModel = videoChatRoomModel;
    
    [superView addSubview:self.maskButton];
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(superView);
    }];

    switch (type) {
        case VideoChatRoomSettingTypeCreateRoom: {
            [superView addSubview:self.createRoomSettingView];
            [self.createRoomSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
                CGFloat height = 256 + [DeviceInforTool getVirtualHomeHeight];
                make.left.right.equalTo(superView);
                make.height.mas_equalTo(height);
                make.bottom.equalTo(superView).offset(height);
            }];
            [superView layoutIfNeeded];
            [superView setNeedsUpdateConstraints];

            [UIView animateWithDuration:0.25
                             animations:^{
               [self.createRoomSettingView mas_updateConstraints:^(MASConstraintMaker *make) {
                   make.bottom.equalTo(superView);
               }];
               [superView layoutIfNeeded];
             }];
        } break;
        
        case VideoChatRoomSettingTypeGuest: {
            self.guestSettingView.isMicOn = _mic;
            self.guestSettingView.isCameraOn = _camera;
            [superView addSubview:self.guestSettingView];
            [self.guestSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
                CGFloat height = 164 + [DeviceInforTool getVirtualHomeHeight];
                make.left.right.equalTo(superView);
                make.height.mas_equalTo(height);
                make.bottom.equalTo(superView).offset(height);
            }];
            [superView layoutIfNeeded];
            [superView setNeedsUpdateConstraints];

            [UIView animateWithDuration:0.25
                             animations:^{
               [self.guestSettingView mas_updateConstraints:^(MASConstraintMaker *make) {
                   make.bottom.equalTo(superView);
               }];
               [superView layoutIfNeeded];
             }];
        } break;
        

        default:
            break;
    }
}

- (void)maskButtonAction {
    [self close];
}

- (void)close {
    if (_createRoomSettingView.superview) {
        [_createRoomSettingView removeFromSuperview];
    }
    if (_guestSettingView.superview) {
        [_guestSettingView removeFromSuperview];
    }
    if (self.maskButton.superview) {
        [self.maskButton removeFromSuperview];
        self.maskButton = nil;
    }
}

- (void)updateUserMic:(BOOL)isEnable {
    _mic = isEnable;
    [self close];
}

- (void)resetMicAndCameraStatus {
    _mic = YES;
    _camera = YES;
    self.guestSettingView.isMicOn = _mic;
    self.guestSettingView.isCameraOn = _camera;
}

- (void)setMic:(BOOL)mic {
    _mic = mic;
    self.guestSettingView.isMicOn = mic;
}

- (void)setCamera:(BOOL)camera {
    _camera = camera;
    self.guestSettingView.isCameraOn = camera;
}

#pragma mark - VideoChatCreateRoomSettingViewDelegate

- (void)videoChatCreateRoomSettingView:(nonnull VideoChatCreateRoomSettingView *)settingView didChangeBitrate:(NSInteger)bitrate {
    VideoChatSettingVideoConfig *videoConfig = settingView.videoConfig;
    [[VideoChatRTCManager shareRtc] updateKBitrate:videoConfig.bitrate];
}

- (void)videoChatCreateRoomSettingView:(nonnull VideoChatCreateRoomSettingView *)settingView didChangeResolution:(NSInteger)index {
    VideoChatSettingVideoConfig *videoConfig = settingView.videoConfig;
    [[VideoChatRTCManager shareRtc] updateRes:videoConfig.videoSize];
}

- (void)videoChatCreateRoomSettingView:(nonnull VideoChatCreateRoomSettingView *)settingView didChangefpsType:(VideoChatSettingVideoFpsType)fps {
    VideoChatSettingVideoConfig *videoConfig = settingView.videoConfig;
    [[VideoChatRTCManager shareRtc] updateFPS:videoConfig.fps];
}

#pragma mark - VideoChatRoomGuestSettingViewDelegate

- (void)videoChatRoomGuestSettingView:(nonnull VideoChatRoomGuestSettingView *)settingView didChangeCameraState:(BOOL)isOn {
    _camera = !isOn;
    [VideoChatRTMManager updateMediaStatus:self.videoChatRoomModel.roomID
                                              mic:_mic ? 1 : 0
                                           camera:_camera ? 1 : 0
                                            block:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponents shareToastComponents] showWithMessage:model.message];
        }
    }];
}

- (void)videoChatRoomGuestSettingView:(nonnull VideoChatRoomGuestSettingView *)settingView didChangeMicState:(BOOL)isOn {
    _mic = !isOn;
    [VideoChatRTMManager updateMediaStatus:self.videoChatRoomModel.roomID
                                              mic:_mic ? 1 : 0
                                           camera:_camera ? 1 : 0
                                            block:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponents shareToastComponents] showWithMessage:model.message];
        }
    }];
}

- (void)videoChatRoomGuestSettingView:(nonnull VideoChatRoomGuestSettingView *)settingView didSwitchCamera:(BOOL)isFront {
    [[VideoChatRTCManager shareRtc] switchCamera];
}

- (void)videoChatRoomGuestSettingViewDidClickMusic:(VideoChatRoomGuestSettingView *)settingView {
    [self close];
    if (self.clickMusicBlock) {
        self.clickMusicBlock();
    }
}


#pragma mark - getter

- (VideoChatRoomGuestSettingView *)guestSettingView {
    if (!_guestSettingView) {
        _guestSettingView = [[VideoChatRoomGuestSettingView alloc] initWithHost:self.isHost];
        _guestSettingView.delegate = self;
    }
    return _guestSettingView;
}

- (VideoChatCreateRoomSettingView *)createRoomSettingView {
    if (!_createRoomSettingView) {
        _createRoomSettingView = [[VideoChatCreateRoomSettingView alloc] init];
        _createRoomSettingView.videoConfig = [VideoChatSettingVideoConfig defultVideoConfig];
        _createRoomSettingView.delegate = self;
    }
    return _createRoomSettingView;
}

- (UIButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[UIButton alloc] init];
        [_maskButton addTarget:self action:@selector(maskButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_maskButton setBackgroundColor:[UIColor clearColor]];
    }
    return _maskButton;
}

@end
