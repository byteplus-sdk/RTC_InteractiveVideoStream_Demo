/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomUserListtCell.h"
#import "VideoChatAvatarCompoments.h"

@interface VideoChatRoomUserListtCell ()

@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) BaseButton *rightButton;
@property (nonatomic, strong) VideoChatAvatarCompoments *avatarView;

@end

@implementation VideoChatRoomUserListtCell


- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

- (void)setModel:(VideoChatUserModel *)model {
    _model = model;
    self.nameLabel.text = model.name;
    self.avatarView.text = model.name;
    
    if (model.status == VideoChatUserStatusActive) {
        [self.rightButton setTitle:LocalizedString(@"Connected") forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#94C2FF"];
        self.rightButton.hidden = NO;
    } else if (model.status == VideoChatUserStatusApply) {
        [self.rightButton setTitle:LocalizedString(@"Accept") forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#1664FF"];
        self.rightButton.hidden = NO;
    } else if (model.status == VideoChatUserStatusInvite) {
        [self.rightButton setTitle:LocalizedString(@"Invited") forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#94C2FF"];
        self.rightButton.hidden = NO;
    } else if (model.status == VideoChatUserStatusDefault) {
        [self.rightButton setTitle:LocalizedString(@"Invite") forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#1664FF"];
        self.rightButton.hidden = NO;
    } else {
        self.rightButton.hidden = YES;
    }
}

- (void)createUIComponents {
    [self.contentView addSubview:self.avatarView];
    [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(40, 40));
        make.left.mas_equalTo(16);
        make.bottom.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.rightButton];
    [self.rightButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_greaterThanOrEqualTo(88);
        make.height.mas_equalTo(28);
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self.avatarView);
    }];
    
    [self.contentView addSubview:self.nameLabel];
    [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.avatarView.mas_right).mas_offset(9);
        make.centerY.equalTo(self.avatarView);
        make.right.mas_lessThanOrEqualTo(self.rightButton.mas_left).offset(-9);
    }];
}

- (void)rightButtonAction:(BaseButton *)sender {
    if ([self.delegate respondsToSelector:@selector(VideoChatRoomUserListtCell:clickButton:)]) {
        [self.delegate VideoChatRoomUserListtCell:self clickButton:self.model];
    }
}

#pragma mark - getter

- (BaseButton *)rightButton {
    if (!_rightButton) {
        _rightButton = [[BaseButton alloc] init];
        _rightButton.layer.cornerRadius = 14;
        _rightButton.layer.masksToBounds = YES;
        _rightButton.titleLabel.font = [UIFont systemFontOfSize:14];
        [_rightButton setContentEdgeInsets:UIEdgeInsetsMake(0, 15, 0, 15)];
        [_rightButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _rightButton;
}

- (VideoChatAvatarCompoments *)avatarView {
    if (!_avatarView) {
        _avatarView = [[VideoChatAvatarCompoments alloc] init];
        _avatarView.layer.cornerRadius = 20;
        _avatarView.layer.masksToBounds = YES;
        _avatarView.fontSize = 20;
    }
    return _avatarView;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] init];
        _nameLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _nameLabel.font = [UIFont systemFontOfSize:16];
    }
    return _nameLabel;
}

@end
