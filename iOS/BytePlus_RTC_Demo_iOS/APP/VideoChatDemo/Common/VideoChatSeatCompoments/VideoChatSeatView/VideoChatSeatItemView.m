/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatSeatItemView.h"
#import "VideoChatSeatItemCenterView.h"
#import "VideoChatSeatItemNameView.h"
#import "VideoChatAvatarCompoments.h"
#import "VideoChatSeatNetworkQualityView.h"

typedef NS_ENUM(NSInteger, VideoChatSeatItemStatue) {
    VideoChatSeatItemStatueNull = 0,    //Unmanned or empty model
    VideoChatSeatItemStatueLock,        //Lock seat
    VideoChatSeatItemStatueUser,        //There are mic users
};

@interface VideoChatSeatItemView ()

@property (nonatomic, strong) UIImageView *borderImageView;
@property (nonatomic, strong) UIView *animationView;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) VideoChatAvatarCompoments *avatarCompoments;
@property (nonatomic, strong) VideoChatSeatItemNameView *userNameView;
@property (nonatomic, strong) VideoChatSeatItemCenterView *centerImageView;
@property (nonatomic, strong) VideoChatSeatNetworkQualityView *networkQualityView;

@end

@implementation VideoChatSeatItemView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.borderImageView];
        [self addSubview:self.renderView];
        [self addSubview:self.animationView];
        [self addSubview:self.userNameView];
        [self addSubview:self.centerImageView];
        [self addSubview:self.networkQualityView];
        
        [self.borderImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self.animationView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.width.height.mas_equalTo(62);
        }];
        
        [self.userNameView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(18);
            make.left.right.bottom.equalTo(self);
        }];
        
        [self.centerImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(40, 50));
            make.center.equalTo(self);
        }];
        [self.networkQualityView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(8);
            make.right.equalTo(self).offset(-8);
            make.top.equalTo(self).offset(8);
            make.height.mas_equalTo(11);
        }];
        
        [self addSubview:self.avatarCompoments];
        [self.avatarCompoments mas_makeConstraints:^(MASConstraintMaker *make) {
            make.width.height.mas_equalTo(48);
            make.center.equalTo(self);
        }];
        
        self.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapAction)];
        [self addGestureRecognizer:tap];
    }
    return self;
}

- (void)updateRender {
    [self setSeatModel:self.seatModel];
}

- (void)setSeatModel:(VideoChatSeatModel *)seatModel {
    _seatModel = seatModel;
    if (seatModel) {
        if (seatModel.status == 1) {
            if (NOEmptyStr(seatModel.userModel.uid)) {
                [self updateUI:VideoChatSeatItemStatueUser seatModel:seatModel];
            } else {
                [self updateUI:VideoChatSeatItemStatueNull seatModel:seatModel];
            }
        } else {
            [self updateUI:VideoChatSeatItemStatueLock seatModel:seatModel];
        }
    } else {
        [self updateUI:VideoChatSeatItemStatueNull seatModel:seatModel];
    }
}

- (void)updateUI:(VideoChatSeatItemStatue)statue
       seatModel:(VideoChatSeatModel *)seatModel {
    self.animationView.hidden = YES;
    
    if (statue == VideoChatSeatItemStatueNull) {
        [self.centerImageView updateImageName:@"videochat_seat_null"
                                      message:LocalizedString(@"Seat")];
        self.userNameView.userModel = seatModel.userModel;
        
        self.centerImageView.hidden = NO;
        self.renderView.hidden = YES;
        self.userNameView.hidden = YES;
        self.avatarCompoments.hidden = YES;
        self.networkQualityView.hidden = YES;
    } else if (statue == VideoChatSeatItemStatueLock) {
        [self.centerImageView updateImageName:@"videochat_seat_lock"
                                      message:LocalizedString(@"Seat")];
        self.userNameView.userModel = seatModel.userModel;
        
        self.centerImageView.hidden = NO;
        self.renderView.hidden = YES;
        self.userNameView.hidden = YES;
        self.avatarCompoments.hidden = YES;
        self.networkQualityView.hidden = YES;
    } else if (statue == VideoChatSeatItemStatueUser) {
        self.userNameView.userModel = seatModel.userModel;
        self.avatarCompoments.text = seatModel.userModel.name;
        self.avatarCompoments.hidden = (seatModel.userModel.camera == VideoChatUserCameraOn) ? YES : NO;
        self.renderView.hidden = (seatModel.userModel.camera == VideoChatUserCameraOn) ? NO : YES;
        if (!self.renderView.hidden) {
            [self updateRenderView:seatModel.userModel];
        }
        
        self.centerImageView.hidden = YES;
        self.userNameView.hidden = NO;
        self.networkQualityView.hidden = NO;
        
    } else {
        //error
    }
}

- (void)updateRenderView:(VideoChatUserModel *)userModel {
    UIView *streamView = [[VideoChatRTCManager shareRtc] getStreamViewWithUid:userModel.uid];
    streamView.hidden = NO;
    [self.renderView addSubview:streamView];
    [streamView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.renderView);
    }];
}

- (void)tapAction {
    if (self.clickBlock) {
        self.clickBlock(self.seatModel);
    }
}

- (void)addWiggleAnimation:(UIView *)view {
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:@"transform.scale"];
    animation.values = @[@(0.81), @(1.0), @(1.0)];
    animation.keyTimes = @[@(0), @(0.27), @(1.0)];
    
    CAKeyframeAnimation *animation2 = [CAKeyframeAnimation animationWithKeyPath:@"opacity"];
    animation2.values = @[@(0), @(0.2), @(0.4), @(0.2)];
    animation2.keyTimes = @[@(0), @(0.27), @(0.27), @(1.0)];
    
    CAAnimationGroup *group = [CAAnimationGroup animation];
    group.animations = @[animation,animation2];
    group.duration = 1.1;
    group.repeatCount = MAXFLOAT;
    group.removedOnCompletion = NO;
    group.fillMode = kCAFillModeForwards;
    [view.layer addAnimation:group forKey:@"transformKey"];
}

- (void)updateNetworkQualityStstus:(VideoChatNetworkQualityStatus)status {
    [self.networkQualityView updateNetworkQualityStstus:status];
}

#pragma mark - getter

- (UIView *)animationView {
    if (!_animationView) {
        _animationView = [[UIView alloc] init];
        _animationView.backgroundColor = [UIColor colorFromRGBHexString:@"#F93D89"];
        _animationView.layer.cornerRadius = 62 / 2;
        _animationView.layer.masksToBounds = YES;
        _animationView.hidden = YES;
        [self addWiggleAnimation:_animationView];
    }
    return _animationView;
}

- (VideoChatSeatItemNameView *)userNameView {
    if (!_userNameView) {
        _userNameView = [[VideoChatSeatItemNameView alloc] init];
    }
    return _userNameView;
}

- (VideoChatSeatItemCenterView *)centerImageView {
    if (!_centerImageView) {
        _centerImageView = [[VideoChatSeatItemCenterView alloc] init];
    }
    return _centerImageView;
}

- (UIImageView *)borderImageView {
    if (!_borderImageView) {
        _borderImageView = [[UIImageView alloc] init];
        _borderImageView.image = [UIImage imageNamed:@"videochat_border" bundleName:HomeBundleName];
    }
    return _borderImageView;
}

- (UIView *)renderView {
    if (!_renderView) {
        _renderView = [[UIView alloc] init];
        _renderView.backgroundColor = [UIColor clearColor];
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
        _networkQualityView.hidden = YES;
    }
    return _networkQualityView;
}

@end
