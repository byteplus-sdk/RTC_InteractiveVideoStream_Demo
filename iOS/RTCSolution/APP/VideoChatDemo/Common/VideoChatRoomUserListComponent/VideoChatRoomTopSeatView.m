//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatRoomTopSeatView.h"

@interface VideoChatRoomTopSeatView ()

@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UIButton *closeChatRoomButton;

@end

@implementation VideoChatRoomTopSeatView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromRGBHexString:@"#0E0825" andAlpha:0.95 * 255];

        [self addSubview:self.lineView];
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self);
            make.height.mas_equalTo(1);
            make.bottom.mas_equalTo(-1);
        }];

        [self addSubview:self.closeChatRoomButton];
        [self.closeChatRoomButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(self).offset(-12.5);
            make.centerY.equalTo(self);
            make.top.bottom.equalTo(self);
        }];
    }
    return self;
}

- (void)closeChatRoomButtonClick {
    if (self.clickCloseChatRoomBlock) {
        self.clickCloseChatRoomBlock();
    }
}

- (void)updateCloseChatRoom:(BOOL)isHidden {
    self.closeChatRoomButton.hidden = isHidden;
}

#pragma mark - Getter

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#2A2441"];
    }
    return _lineView;
}

- (UIButton *)closeChatRoomButton {
    if (!_closeChatRoomButton) {
        _closeChatRoomButton = [[UIButton alloc] init];
        //        _closeChatRoomButton.hidden = YES;
        [_closeChatRoomButton addTarget:self action:@selector(closeChatRoomButtonClick) forControlEvents:UIControlEventTouchUpInside];

        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"videochat_seatlist_close_chatroom" bundleName:HomeBundleName]];
        UILabel *label = [[UILabel alloc] init];
        label.font = [UIFont systemFontOfSize:16];
        label.textColor = UIColor.whiteColor;
        label.text = LocalizedString(@"video_host_close_room");
        [_closeChatRoomButton addSubview:imageView];
        [_closeChatRoomButton addSubview:label];
        [imageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.centerY.equalTo(_closeChatRoomButton);
        }];
        [label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(imageView.mas_right).offset(8);
            make.right.centerY.equalTo(_closeChatRoomButton);
        }];
    }
    return _closeChatRoomButton;
}

@end
