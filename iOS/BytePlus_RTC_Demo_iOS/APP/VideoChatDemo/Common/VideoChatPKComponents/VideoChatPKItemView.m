/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatPKItemView.h"
#import "VideoChatAvatarCompoments.h"
#import "VideoChatSeatNetworkQualityView.h"
#import "VideoChatSeatItemNameView.h"

@interface VideoChatPKItemView ()

@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) VideoChatAvatarCompoments *avatarCompoments;
@property (nonatomic, strong) UIButton *muteButton;
@property (nonatomic, strong) VideoChatSeatNetworkQualityView *networkQualityView;
@property (nonatomic, strong) VideoChatSeatItemNameView *userNameView;

@property (nonatomic, assign) BOOL isOtherAnchor;

@end

@implementation VideoChatPKItemView

- (instancetype)initWithOtherAcnhor:(BOOL)isOtherAnchor {
    if (self = [super init]) {
        self.isOtherAnchor = isOtherAnchor;
        [self setupViews];
    }
    return self;
}

- (void)setupViews {
    [self addSubview:self.renderView];
    [self addSubview:self.avatarCompoments];
    [self addSubview:self.contentView];
    [self.contentView addSubview:self.networkQualityView];
    [self.contentView addSubview:self.userNameView];
    
    [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    [self.avatarCompoments mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(48);
        make.center.equalTo(self);
    }];
    [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    [self.userNameView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(18);
        make.left.right.bottom.equalTo(self);
    }];
    [self.networkQualityView mas_makeConstraints:^(MASConstraintMaker *make) {
        if (self.isOtherAnchor) {
            make.right.equalTo(self).offset(-8);
        } else {
            make.left.equalTo(self).offset(8);
        }
        
        make.top.equalTo(self).offset(8);
        make.height.mas_equalTo(11);
    }];
    if (self.isOtherAnchor) {
        [self.contentView addSubview:self.muteButton];
        [self.muteButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.contentView).offset(-32);
            make.right.equalTo(self.contentView).offset(-8);
        }];
    }
    
}

- (void)setUserModel:(VideoChatUserModel *)userModel {
    _userModel = userModel;
    self.avatarCompoments.text = userModel.name;
    self.userNameView.userModel = userModel;
    self.muteButton.selected = userModel.otherAnchorMicType == VideoChatOtherAnchorMicTypeMute;
    
    if (userModel.camera == VideoChatUserCameraOn) {
        UIView *streamView = [[VideoChatRTCManager shareRtc] getStreamViewWithUid:userModel.uid];
        if (streamView) {
            [self.renderView removeAllSubviews];
            [self.renderView addSubview:streamView];
            streamView.hidden = NO;
            [streamView mas_remakeConstraints:^(MASConstraintMaker *make) {
                make.edges.equalTo(self.renderView);
            }];
            self.avatarCompoments.hidden = YES;
            self.renderView.hidden = NO;
        }
    } else {
        self.avatarCompoments.hidden = NO;
        self.renderView.hidden = YES;
    }
    
    // TODO
    if (self.isOtherAnchor && [userModel.uid isEqualToString:[LocalUserComponents userModel].uid]) {
        NSLog(@"error");
    }
}

- (void)updateMuteOtherAnchor:(BOOL)isMute {
    self.muteButton.selected = isMute;
}

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status {
    [self.networkQualityView updateNetworkQualityStstus:status];
}

- (void)muteButtonClick {
    if (self.clickMuteButtonBlock) {
        self.clickMuteButtonBlock(!self.muteButton.isSelected);
    }
}

#pragma mark - getter
- (UIView *)renderView {
    if (!_renderView) {
        _renderView = [[UIView alloc] init];
    }
    return _renderView;
}

- (VideoChatAvatarCompoments *)avatarCompoments {
    if (!_avatarCompoments) {
        _avatarCompoments = [[VideoChatAvatarCompoments alloc] init];
        _avatarCompoments.layer.cornerRadius = 24;
        _avatarCompoments.layer.masksToBounds = YES;
        _avatarCompoments.fontSize = 24;
        _avatarCompoments.hidden = YES;
    }
    return _avatarCompoments;
}

- (VideoChatSeatNetworkQualityView *)networkQualityView {
    if (!_networkQualityView) {
        _networkQualityView = [[VideoChatSeatNetworkQualityView alloc] init];
    }
    return _networkQualityView;
}

- (VideoChatSeatItemNameView *)userNameView {
    if (!_userNameView) {
        _userNameView = [[VideoChatSeatItemNameView alloc] init];
        _userNameView.isPK = YES;
    }
    return _userNameView;
}

- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
    }
    return _contentView;
}

- (UIButton *)muteButton {
    if (!_muteButton) {
        _muteButton = [[UIButton alloc] init];
        _muteButton.adjustsImageWhenHighlighted = NO;
        [_muteButton setImage:[UIImage imageNamed:@"videochat_pk_other_mute_off" bundleName:HomeBundleName] forState:UIControlStateNormal];
        [_muteButton setImage:[UIImage imageNamed:@"videochat_pk_other_mute_on" bundleName:HomeBundleName] forState:UIControlStateSelected];
        
        [_muteButton addTarget:self action:@selector(muteButtonClick) forControlEvents:UIControlEventTouchUpInside];
    }
    return _muteButton;
}


@end
