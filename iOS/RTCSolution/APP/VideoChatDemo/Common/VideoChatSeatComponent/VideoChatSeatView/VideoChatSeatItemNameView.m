// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatSeatItemNameView.h"

@interface VideoChatSeatItemNameView ()

@property (nonatomic, strong) UIImageView *maskImageView;
@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) UIImageView *micImageView;
@property (nonatomic, strong) UIImageView *hostImageView;

@end

@implementation VideoChatSeatItemNameView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.maskImageView];
        [self addSubview:self.nameLabel];
        [self addSubview:self.micImageView];
        [self addSubview:self.hostImageView];
        
        [self.maskImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.bottom.equalTo(self);
            make.height.mas_equalTo(18);
        }];
        
        [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self);
            make.width.lessThanOrEqualTo(self).multipliedBy(0.5);
        }];
        
        [self.micImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(12, 12));
            make.centerY.equalTo(self);
            make.right.equalTo(self.nameLabel.mas_left).offset(-4);
        }];
        
        [self.hostImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(26, 12));
            make.bottom.mas_equalTo(-3);
            make.right.mas_equalTo(-3);
        }];
    }
    return self;
}

- (void)setIsPK:(BOOL)isPK {
    _isPK = isPK;
    if (isPK) {
        [self.micImageView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(12, 12));
            make.centerY.equalTo(self);
            make.left.equalTo(self.nameLabel.mas_right).offset(4);
        }];
    }
}

- (void)setUserModel:(VideoChatUserModel *)userModel {
    _userModel = userModel;
    
    self.nameLabel.text = userModel.name;
    self.micImageView.hidden = (userModel.mic == VideoChatUserMicOn) ? YES : NO;
    if (userModel.userRole == VideoChatUserRoleHost && !self.isPK) {
        self.hostImageView.hidden = NO;
    } else {
        self.hostImageView.hidden = YES;
    }
}

#pragma mark - Getter

- (UIImageView *)maskImageView {
    if (!_maskImageView) {
        _maskImageView = [[UIImageView alloc] init];
        _maskImageView.image = [UIImage imageNamed:@"videochat_seat_mask" bundleName:HomeBundleName];
    }
    return _maskImageView;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] init];
        _nameLabel.textColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.9 * 255];
        _nameLabel.font = [UIFont systemFontOfSize:10];
    }
    return _nameLabel;
}

- (UIImageView *)micImageView {
    if (!_micImageView) {
        _micImageView = [[UIImageView alloc] init];
        _micImageView.image = [UIImage imageNamed:@"videochat_mute_mic" bundleName:HomeBundleName];
    }
    return _micImageView;
}

- (UIImageView *)hostImageView {
    if (!_hostImageView) {
        _hostImageView = [[UIImageView alloc] init];
        _hostImageView.image = [UIImage imageNamed:@"videochat_host" bundleName:HomeBundleName];
    }
    return _hostImageView;
}

@end
