/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatCreateRoomViewController.h"
#import "VideoChatRoomViewController.h"
#import "VideoChatCreateRoomTipView.h"
#import "VideoChatCreateRoomControlView.h"
#import "BytedEffectProtocol.h"
#import "VideoChatRoomSettingCompoments.h"
#import "VideoChatRTCManager.h"

@interface VideoChatCreateRoomViewController () <VideoChatCreateRoomControlViewDelegate>

@property (nonatomic, strong) VideoChatCreateRoomTipView *tipView;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) UIButton *joinButton;
@property (nonatomic, strong) VideoChatCreateRoomControlView *controlView;

@property (nonatomic, strong) VideoChatRoomSettingCompoments *settingCompoments;
@property (nonatomic, strong) BytedEffectProtocol *beautyCompoments;

@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, strong) VideoChatUserModel *userModel;
@property (nonatomic, copy) NSString *rtcToekn;

@end

@implementation VideoChatCreateRoomViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                        userModel:(VideoChatUserModel *)userModel
                         rtcToekn:(NSString *)rtcToekn {
    self = [super init];
    if (self) {
        _rtcToekn = rtcToekn;
        _roomModel = roomModel;
        _userModel = userModel;
        [[VideoChatRTCManager shareRtc] updateVideoConfigWithHost:YES];
        [[VideoChatRTCManager shareRtc] bingCanvasViewToUid:userModel.uid];
        [[VideoChatRTCManager shareRtc] enableLocalVideo:YES];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    [self addSubviewAndConstraints];
    
    // show local render view
    UIView *streamView = [[VideoChatRTCManager shareRtc] getStreamViewWithUid:_userModel.uid];
    streamView.hidden = NO;
    [self.renderView addSubview:streamView];
    [streamView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.renderView);
    }];
    
    // resume local render effect
    [self.beautyCompoments resumeLocalEffect];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navTitle = @"";
    [self.leftButton setImage:[UIImage imageNamed:@"video_cancel" bundleName:HomeBundleName] forState:UIControlStateNormal];
}

- (void)joinButtonAction:(UIButton *)sender {
    sender.userInteractionEnabled = NO;
    
    [[ToastComponents shareToastComponents] showLoading];
    [PublicParameterCompoments share].roomId = _roomModel.roomID;
    __weak __typeof(self) wself = self;
    [VideoChatRTMManager startLive:_roomModel.roomID
                                    block:^(RTMACKModel * _Nonnull model) {
        if (model.result) {
            [[ToastComponents shareToastComponents] dismiss];
            VideoChatRoomViewController *next = [[VideoChatRoomViewController alloc]
                                                 initWithRoomModel:wself.roomModel
                                                 rtcToken:wself.rtcToekn
                                                 hostUserModel:wself.userModel];
            [wself.navigationController pushViewController:next animated:YES];
        } else {
            [[ToastComponents shareToastComponents] showWithMessage:model.message];
        }
        sender.userInteractionEnabled = YES;
    }];
}

#pragma mark - LiveCreateRoomControlViewDelegate

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSwitchCameraButton:(UIButton *)button {
    [[VideoChatRTCManager shareRtc] switchCamera];
}

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedBeautyButton:(UIButton *)button {
    if (self.beautyCompoments) {
        self.controlView.hidden = YES;
        __weak __typeof(self) wself = self;
        [self.beautyCompoments showWithType:EffectBeautyRoleTypeHost
                              fromSuperView:self.view
                               dismissBlock:^(BOOL result) {
            wself.controlView.hidden = NO;
        }];
    } else {
        [[ToastComponents shareToastComponents] showWithMessage:@"This open-source project doesn't support Effects-related function. Please download BytePlus demo to experience it."];
    }
}

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSettingButton:(UIButton *)button {
    [self.settingCompoments showWithType:VideoChatRoomSettingTypeCreateRoom
                           fromSuperView:self.view
                               roomModel:self.roomModel];
}

#pragma mark - Private Action

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.renderView];
    [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.leftButton];
    [self.leftButton mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.height.width.mas_equalTo(24);
        make.left.mas_equalTo(20);
        make.centerY.equalTo(self.navView).offset([DeviceInforTool getStatusBarHight]/2);
    }];
    
    [self.view addSubview:self.tipView];
    [self.tipView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.left.mas_equalTo(0);
        make.top.equalTo(self.leftButton.mas_bottom).offset(8);
    }];
    
    [self.view addSubview:self.joinButton];
    [self.joinButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.width.mas_equalTo(171);
        make.height.mas_equalTo(50);
        make.bottom.mas_equalTo(- ([DeviceInforTool getVirtualHomeHeight] + 48));
    }];
    
    [self.view addSubview:self.controlView];
    [self.controlView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.joinButton.mas_top).offset(-10);
        make.centerX.equalTo(self.view);
        make.width.mas_equalTo(212);
        make.height.mas_equalTo(82);
    }];
}

#pragma mark - getter

- (UIButton *)joinButton {
    if (!_joinButton) {
        _joinButton = [[UIButton alloc] init];
        [_joinButton setBackgroundColor:[UIColor colorFromHexString:@"#165DFF"]];
        [_joinButton setTitle:LocalizedString(@"Go LIVE") forState:UIControlStateNormal];
        [_joinButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        _joinButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_joinButton addTarget:self action:@selector(joinButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        _joinButton.layer.cornerRadius = 25;
        _joinButton.layer.masksToBounds = YES;
    }
    return _joinButton;
}

- (VideoChatCreateRoomTipView *)tipView {
    if (!_tipView) {
        _tipView = [[VideoChatCreateRoomTipView alloc] init];
        _tipView.message = LocalizedString(@"Welcome to embrace engagement in real-time.");
    }
    return _tipView;
}

- (UIView *)renderView {
    if (!_renderView) {
        _renderView = [[UIView alloc] init];
        _renderView.backgroundColor = [UIColor clearColor];
    }
    return _renderView;
}

- (VideoChatCreateRoomControlView *)controlView {
    if (!_controlView) {
        _controlView = [[VideoChatCreateRoomControlView alloc] init];
        _controlView.delegate = self;
    }
    return _controlView;
}

- (BytedEffectProtocol *)beautyCompoments {
    if (!_beautyCompoments) {
        _beautyCompoments = [[BytedEffectProtocol alloc] initWithRTCEngineKit:[VideoChatRTCManager shareRtc].rtcEngineKit];
    }
    return _beautyCompoments;
}

- (VideoChatRoomSettingCompoments *)settingCompoments {
    if (!_settingCompoments) {
        _settingCompoments = [[VideoChatRoomSettingCompoments alloc] initWithHost:NO];
    }
    return _settingCompoments;
}

- (void)dealloc {
    [[VideoChatRTCManager shareRtc] leaveChannel];
}

@end
