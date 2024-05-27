//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatStaticView.h"
#import "VideoChatPeopleNumView.h"
#import "VideoChatStaticHostAvatarView.h"

@interface VideoChatStaticView ()

@property (nonatomic, strong) VideoChatStaticHostAvatarView *hostAvatarView;
@property (nonatomic, strong) VideoChatPeopleNumView *peopleNumView;
@property (nonatomic, strong) UIButton *closeButton;

@end

@implementation VideoChatStaticView

- (instancetype)initWithSuperView:(UIView *)superView {
    self = [super init];
    if (self) {
        [superView addSubview:self.closeButton];
        [superView addSubview:self.peopleNumView];
        [self.closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(superView).offset(-16);
            make.width.height.mas_equalTo(24);
            make.centerY.equalTo(self.peopleNumView);
        }];
        [self.peopleNumView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(32);
            make.right.equalTo(self.closeButton.mas_left).offset(-16);
            make.top.equalTo(superView).offset([DeviceInforTool getStatusBarHight] + 16);
        }];

        [superView addSubview:self.hostAvatarView];
        [self.hostAvatarView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(36);
            make.left.equalTo(superView).offset(16);
            make.top.equalTo(superView).offset([DeviceInforTool getStatusBarHight] + 6);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setRoomModel:(VideoChatRoomModel *)roomModel {
    _roomModel = roomModel;

    self.hostAvatarView.roomModel = roomModel;
    [self.peopleNumView updateTitleLabel:roomModel.audienceCount];
}

- (void)updatePeopleNum:(NSInteger)count {
    [self.peopleNumView updateTitleLabel:count];
}

- (void)closeButtonClick {
    if (self.quitLiveBlock) {
        self.quitLiveBlock();
    }
}

#pragma mark - Getter

- (VideoChatStaticHostAvatarView *)hostAvatarView {
    if (!_hostAvatarView) {
        _hostAvatarView = [[VideoChatStaticHostAvatarView alloc] init];
        _hostAvatarView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
        _hostAvatarView.layer.cornerRadius = 18;
        _hostAvatarView.layer.masksToBounds = YES;
    }
    return _hostAvatarView;
}

- (VideoChatPeopleNumView *)peopleNumView {
    if (!_peopleNumView) {
        _peopleNumView = [[VideoChatPeopleNumView alloc] init];
        _peopleNumView.backgroundColor = [UIColor colorFromRGBHexString:@"#000000" andAlpha:0.2 * 255];
        _peopleNumView.layer.cornerRadius = 16;
        _peopleNumView.layer.masksToBounds = YES;
    }
    return _peopleNumView;
}

- (UIButton *)closeButton {
    if (!_closeButton) {
        _closeButton = [[UIButton alloc] init];
        [_closeButton setImage:[UIImage imageNamed:@"videochat_quit_live" bundleName:HomeBundleName] forState:UIControlStateNormal];
        [_closeButton addTarget:self action:@selector(closeButtonClick) forControlEvents:UIControlEventTouchUpInside];
    }
    return _closeButton;
}

@end
