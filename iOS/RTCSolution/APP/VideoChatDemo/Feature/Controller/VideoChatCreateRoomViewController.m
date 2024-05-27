//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatCreateRoomViewController.h"
#import "BytedEffectProtocol.h"
#import "VideoChatCreateRoomControlView.h"
#import "VideoChatCreateRoomTipView.h"
#import "VideoChatRTCManager.h"
#import "VideoChatRoomSettingComponent.h"
#import "VideoChatRoomViewController.h"

@interface VideoChatCreateRoomViewController () <VideoChatCreateRoomControlViewDelegate>

@property (nonatomic, strong) VideoChatCreateRoomTipView *tipView;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) UIButton *joinButton;
@property (nonatomic, strong) VideoChatCreateRoomControlView *controlView;

@property (nonatomic, strong) VideoChatRoomSettingComponent *settingComponent;
@property (nonatomic, strong) BytedEffectProtocol *beautyComponent;

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
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    [self addSubviewAndConstraints];

    // Start camera capture
    [[VideoChatRTCManager shareRtc] switchVideoCapture:YES];

    // Show local render view
    NSString *localUid = [LocalUserComponent userModel].uid;
    [[VideoChatRTCManager shareRtc] bindCanvasViewToUid:localUid];
    UIView *streamView = [[VideoChatRTCManager shareRtc] getStreamViewWithUid:localUid];
    streamView.hidden = NO;
    [self.renderView addSubview:streamView];
    [streamView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.renderView);
    }];

    // Resume local render effect
    [self.beautyComponent resume];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    self.navTitle = @"";
    self.navLeftImage = [UIImage imageNamed:@"video_cancel" bundleName:HomeBundleName];
}

- (void)joinButtonAction:(UIButton *)sender {
    [[ToastComponent shareToastComponent] showLoading];

    [PublicParameterComponent share].roomId = _roomModel.roomID;
    __weak __typeof(self) wself = self;
    [VideoChatRTSManager startLive:_roomModel.roomID
                             block:^(RTSACKModel *_Nonnull model) {
                                 if (model.result) {
                                     VideoChatRoomViewController *next = [[VideoChatRoomViewController alloc]
                                         initWithRoomModel:wself.roomModel
                                                  rtcToken:wself.rtcToekn
                                             hostUserModel:wself.userModel];
                                     [wself.navigationController pushViewController:next animated:YES];
                                 } else {
                                     [[ToastComponent shareToastComponent] showWithMessage:model.message];
                                 }
                                 [[ToastComponent shareToastComponent] dismiss];
                             }];
}

#pragma mark - LiveCreateRoomControlViewDelegate

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSwitchCameraButton:(UIButton *)button {
    [[VideoChatRTCManager shareRtc] switchCamera];
}

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedBeautyButton:(UIButton *)button {
    if (self.beautyComponent) {
        self.controlView.hidden = YES;
        __weak __typeof(self) wself = self;
        [self.beautyComponent showWithView:self.view
                              dismissBlock:^(BOOL result) {
                                  wself.controlView.hidden = NO;
                              }];
    } else {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"not_support_beauty_error")];
    }
}

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSettingButton:(UIButton *)button {
    [self.settingComponent showWithType:VideoChatRoomSettingTypeCreateRoom
                          fromSuperView:self.view
                              roomModel:self.roomModel];
}

#pragma mark - Private Action

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.renderView];
    [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];

    [self.view bringSubviewToFront:self.navView];
    self.navView.backgroundColor = [UIColor clearColor];

    [self.view addSubview:self.tipView];
    [self.tipView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.left.mas_equalTo(0);
        make.top.equalTo(self.navView.mas_bottom).offset(8);
    }];

    [self.view addSubview:self.joinButton];
    [self.joinButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.width.mas_equalTo(171);
        make.height.mas_equalTo(50);
        make.bottom.mas_equalTo(-([DeviceInforTool getVirtualHomeHeight] + 48));
    }];

    [self.view addSubview:self.controlView];
    [self.controlView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.joinButton.mas_top).offset(-10);
        make.centerX.equalTo(self.view);
        make.width.mas_equalTo(212);
        make.height.mas_equalTo(82);
    }];
}

#pragma mark - Getter

- (UIButton *)joinButton {
    if (!_joinButton) {
        _joinButton = [[UIButton alloc] init];
        [_joinButton setBackgroundColor:[UIColor colorFromHexString:@"#165DFF"]];
        [_joinButton setTitle:LocalizedString(@"video_chat_start_live") forState:UIControlStateNormal];
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
        _tipView.message = [NSString stringWithFormat:LocalizedString(@"application_experiencing_%@_title"), @"20"];
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

- (BytedEffectProtocol *)beautyComponent {
    if (!_beautyComponent) {
        _beautyComponent = [[BytedEffectProtocol alloc] initWithRTCEngineKit:[VideoChatRTCManager shareRtc].rtcEngineKit];
    }
    return _beautyComponent;
}

- (VideoChatRoomSettingComponent *)settingComponent {
    if (!_settingComponent) {
        _settingComponent = [[VideoChatRoomSettingComponent alloc] initWithHost:NO];
    }
    return _settingComponent;
}

- (void)dealloc {
    [[VideoChatRTCManager shareRtc] leaveRTCRoom];
}

@end
