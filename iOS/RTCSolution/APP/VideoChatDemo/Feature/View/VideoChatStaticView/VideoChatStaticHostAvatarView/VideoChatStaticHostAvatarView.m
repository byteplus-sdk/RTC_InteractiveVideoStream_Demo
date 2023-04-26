// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatStaticHostAvatarView.h"
#import "VideoChatAvatarComponent.h"

@interface VideoChatStaticHostAvatarView ()

@property (nonatomic, strong) VideoChatAvatarComponent *avatarView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *roomIDLabel;

@end

@implementation VideoChatStaticHostAvatarView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self addSubview:self.avatarView];
        [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(36, 36));
            make.left.mas_equalTo(0);
            make.centerY.equalTo(self);
        }];

        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.mas_equalTo(5);
            make.left.equalTo(self.avatarView.mas_right).offset(8);
        }];
        
        [self addSubview:self.roomIDLabel];
        [self.roomIDLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.titleLabel.mas_bottom).offset(0);
            make.left.equalTo(self.titleLabel);
        }];

        [self mas_updateConstraints:^(MASConstraintMaker *make) {
            make.right.greaterThanOrEqualTo(self.titleLabel.mas_right).offset(20);
            make.right.greaterThanOrEqualTo(self.roomIDLabel.mas_right).offset(20);
        }];
    }
    return self;
}

- (void)setRoomModel:(VideoChatRoomModel *)roomModel {
    _roomModel = roomModel;

    self.avatarView.text = roomModel.hostName;
    self.titleLabel.text = roomModel.hostName;
    self.roomIDLabel.text = [NSString stringWithFormat:@"ID:%@", roomModel.roomID];
}

#pragma mark - Getter

- (UILabel *)titleLabel {
    if (_titleLabel == nil) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        _titleLabel.font = [UIFont systemFontOfSize:12];
    }
    return _titleLabel;
}

- (VideoChatAvatarComponent *)avatarView {
    if (_avatarView == nil) {
        _avatarView = [[VideoChatAvatarComponent alloc] init];
        _avatarView.layer.masksToBounds = YES;
        _avatarView.layer.cornerRadius = 16;
        _avatarView.fontSize = 16;
    }
    return _avatarView;
}

- (UILabel *)roomIDLabel {
    if (!_roomIDLabel) {
        _roomIDLabel = [[UILabel alloc] init];
        _roomIDLabel.textColor = [UIColor colorFromRGBHexString:@"#FFFFFF"
                                                       andAlpha:0.6 * 255];
        _roomIDLabel.textAlignment = NSTextAlignmentCenter;
        _roomIDLabel.font = [UIFont systemFontOfSize:8];
    }
    return _roomIDLabel;
}

@end
