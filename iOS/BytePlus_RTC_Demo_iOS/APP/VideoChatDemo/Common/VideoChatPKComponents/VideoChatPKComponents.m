/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatPKComponents.h"
#import "VideoChatPKItemView.h"

@interface VideoChatPKComponents ()

@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, weak) UIView *superView;
@property (nonatomic, strong) VideoChatRoomModel *roomModel;

@property (nonatomic, strong) VideoChatPKItemView *hostItemView;
@property (nonatomic, strong) VideoChatPKItemView *anchorItemView;
@property (nonatomic, strong) UIImageView *pkImageView;
@property (nonatomic, strong) UILabel *pkLabel;

@end

@implementation VideoChatPKComponents
- (instancetype)initWithSuperView:(UIView *)superView roomModel:(nonnull VideoChatRoomModel *)roomModel {
    if (self = [super init]) {
        self.roomModel = roomModel;
        self.superView = superView;
        [superView addSubview:self.contentView];
        [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(superView);
        }];
        [self.contentView addSubview:self.hostItemView];
        [self.contentView addSubview:self.anchorItemView];
        [self.contentView addSubview:self.pkImageView];
        [self.contentView addSubview:self.pkLabel];
        [self resetUI];
    }
    return self;
}

- (void)resetUI {
    self.contentView.hidden = NO;
    self.hostItemView.contentView.hidden = YES;
    [self.hostItemView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.superView);
    }];
    self.anchorItemView.hidden = YES;
    self.pkImageView.hidden = YES;
    self.pkLabel.hidden = YES;
//    [self.anchorItemView updateMuteOtherAnchor:NO];
}

#pragma mark - Methods
- (void)changeChatRoomMode:(VideoChatRoomMode)mode {
    if (mode == VideoChatRoomModePK) {
        [self resetUI];
        [self updateRenderView:self.hostModel.uid];
    }
    else {
        self.contentView.hidden = YES;
    }
}

- (void)updateRenderView:(NSString *)userID {
    if ([userID isEqualToString:self.hostModel.uid]) {
        self.hostItemView.userModel = self.hostModel;
    }
    else if ([userID isEqualToString:self.anchorModel.uid]) {
        self.anchorItemView.userModel = self.anchorModel;
    }
    
}

- (void)setAnchorModel:(VideoChatUserModel *)anchorModel {
    _anchorModel = anchorModel;
    if (!anchorModel) {
        [self endPK];
        return;
    }
    self.anchorItemView.userModel = anchorModel;
    [self startPK];
}

- (void)startPK {
    [self.hostItemView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.superView);
        make.right.equalTo(self.superView.mas_centerX);
        make.top.equalTo(self.superView).offset(124);
        make.height.equalTo(self.hostItemView.mas_width).multipliedBy(270.0/188.0);
    }];
    [self.anchorItemView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.hostItemView.mas_right);
        make.right.equalTo(self.superView);
        make.top.bottom.equalTo(self.hostItemView);
    }];
    [self.pkLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.hostItemView);
        make.centerX.equalTo(self.superView);
        make.height.mas_equalTo(20);
    }];
    [self.pkImageView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.hostItemView);
        make.centerX.equalTo(self.pkLabel);
        make.width.mas_greaterThanOrEqualTo(90);
        make.left.lessThanOrEqualTo(self.pkLabel).offset(-16);
        make.right.greaterThanOrEqualTo(self.pkLabel).offset(16);
    }];
    self.anchorItemView.hidden = NO;
    self.pkLabel.hidden = NO;
    self.pkImageView.hidden = NO;
    self.hostItemView.contentView.hidden = NO;
}

- (void)endPK {
    [self resetUI];
}

- (void)muteOtherAnchor:(BOOL)isMute {
    if (![self.hostModel.uid isEqualToString:[LocalUserComponents userModel].uid]) {
        return;
    }
    VideoChatOtherAnchorMicType type = isMute? VideoChatOtherAnchorMicTypeMute:VideoChatOtherAnchorMicTypeUnmute;
    [VideoChatRTMManager requestMuteOtherAnchorRoomID:self.roomModel.roomID
                                           otherAnchorUserID:self.anchorModel.uid
                                                        type:type
                                                    complete:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponents shareToastComponents] showWithMessage:model.message];
        }
    }];
}

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid {
    if (!self.anchorModel) {
        return;
    }
    if ([self.hostModel.uid isEqualToString:uid]) {
        [self.hostItemView updateNetworkQuality:status];
    } else {
        [self.anchorItemView updateNetworkQuality:status];
    }
}

- (void)updateUserModel:(VideoChatUserModel *)userModel {
    if ([userModel.uid isEqualToString:self.hostModel.uid]) {
        self.hostModel = userModel;
        self.hostItemView.userModel = self.hostModel;
    }
    else if ([userModel.uid isEqualToString:self.anchorModel.uid]) {
        self.anchorModel = userModel;
        self.anchorItemView.userModel = self.anchorModel;
    }
}

- (void)muteOtherAnchorRoomID:(NSString *)roomID otherAnchorUserID:(NSString *)otherAnchorUserID type:(VideoChatOtherAnchorMicType)type {
    BOOL isMute = type == VideoChatOtherAnchorMicTypeMute? YES:NO;
    [[VideoChatRTCManager shareRtc] muteOtherAnchorUserID:otherAnchorUserID mute:isMute];
    [self.anchorItemView updateMuteOtherAnchor:isMute];
}

- (void)reqeustStopForwardStream {
    self.activeEndPK = YES;
    __weak typeof(self) weakSelf = self;
    [VideoChatRTMManager requestStopPKWithRoomID:self.roomModel.roomID userID:self.roomModel.hostUid complete:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            weakSelf.activeEndPK = NO;
            [[ToastComponents shareToastComponents] showWithMessage:model.message];
        }
    }];
}

- (void)rtcStopForwardStream {
    [[VideoChatRTCManager shareRtc] stopForwardStream];
}

#pragma mark - getter
- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
    }
    return _contentView;
}

- (VideoChatPKItemView *)hostItemView {
    if (!_hostItemView) {
        _hostItemView = [[VideoChatPKItemView alloc] initWithOtherAcnhor:NO];
    }
    return _hostItemView;
}

- (VideoChatPKItemView *)anchorItemView {
    if (!_anchorItemView) {
        _anchorItemView = [[VideoChatPKItemView alloc] initWithOtherAcnhor:YES];
        __weak typeof(self) weakSelf = self;
        _anchorItemView.clickMuteButtonBlock = ^(BOOL isMute) {
            [weakSelf muteOtherAnchor:isMute];
        };
    }
    return _anchorItemView;
}

- (UIImageView *)pkImageView {
    if (!_pkImageView) {
        _pkImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"videochat_pkcomponents_pking" bundleName:HomeBundleName]];
    }
    return _pkImageView;
}

- (UILabel *)pkLabel {
    if (!_pkLabel) {
        _pkLabel = [[UILabel alloc] init];
        _pkLabel.text = LocalizedString(@"Connecting");
        _pkLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightMedium];
        _pkLabel.textColor = [UIColor whiteColor];
    }
    return _pkLabel;
}

@end
