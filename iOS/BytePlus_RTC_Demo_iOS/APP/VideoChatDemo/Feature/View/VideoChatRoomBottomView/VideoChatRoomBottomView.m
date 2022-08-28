/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomBottomView.h"
#import "UIView+Fillet.h"

@interface VideoChatRoomBottomView ()

@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, strong) VideoChatRoomItemButton *inputButton;
@property (nonatomic, strong) NSMutableArray *buttonLists;
@property (nonatomic, strong) VideoChatUserModel *loginUserModel;
@property (nonatomic, assign) BOOL isPKing;

@end

@implementation VideoChatRoomBottomView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.clipsToBounds = NO;
        self.backgroundColor = [UIColor clearColor];
        
        [self addSubview:self.contentView];
        [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.top.bottom.equalTo(self);
            make.width.mas_equalTo(0);
        }];
        
        [self addSubview:self.inputButton];
        [self.inputButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(36);
            make.left.top.equalTo(self);
            make.right.equalTo(self.contentView.mas_left).offset(-18);
        }];
        
        [self addSubviewAndConstraints];
    }
    return self;
}

- (void)inputButtonAction {
    if ([self.delegate respondsToSelector:@selector(videoChatRoomBottomView:itemButton:didSelectStatus:)]) {
        [self.delegate videoChatRoomBottomView:self itemButton:self.inputButton didSelectStatus:VideoChatRoomBottomStatusInput];
    }
}

- (void)buttonAction:(VideoChatRoomItemButton *)sender {
    if ([self.delegate respondsToSelector:@selector(videoChatRoomBottomView:itemButton:didSelectStatus:)]) {
        [self.delegate videoChatRoomBottomView:self itemButton:sender didSelectStatus:sender.tagNum];
    }
}

- (void)addSubviewAndConstraints {
    NSInteger groupNum = 5;
    for (int i = 0; i < groupNum; i++) {
        VideoChatRoomItemButton *button = [[VideoChatRoomItemButton alloc] init];
        [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
        [self.buttonLists addObject:button];
        [self.contentView addSubview:button];
    }
}

#pragma mark - Publish Action

- (void)setChatRoomMode:(VideoChatRoomMode)chatRoomMode {
    _chatRoomMode = chatRoomMode;
    [self updateBottomLists:self.loginUserModel isPKing:self.isPKing];
}

- (void)updateBottomListsWithPK:(BOOL)isPKing {
    [self updateBottomLists:self.loginUserModel isPKing:isPKing];
}

- (void)updateBottomLists:(VideoChatUserModel *)userModel {
    [self updateBottomLists:userModel isPKing:NO];
}

- (void)audienceResetBottomLists {
    if (VideoChatUserStatusActive == self.loginUserModel.status) {
        self.loginUserModel.status = VideoChatUserStatusDefault;
        [self updateBottomLists:self.loginUserModel isPKing:NO];
        [[ToastComponents shareToastComponents] showWithMessage:LocalizedString(@"Host has disconnected with you")];
        
        [[VideoChatRTCManager shareRtc] enableLocalAudio:NO];
        [[VideoChatRTCManager shareRtc] enableLocalVideo:NO];
        [[VideoChatRTCManager shareRtc] updateCameraID:YES];
        [[VideoChatRTCManager shareRtc] setUserVisibility:NO];
    }
}

- (void)updateBottomLists:(VideoChatUserModel *)userModel isPKing:(BOOL)isPKing {
    _loginUserModel = userModel;
    _isPKing = isPKing;
    CGFloat itemWidth = 36;
    
    NSArray *status = [self getBottomListsWithModel:userModel isPKing:isPKing];
    NSNumber *number = status.firstObject;
    if (number.integerValue == VideoChatRoomBottomStatusInput) {
        self.inputButton.hidden = NO;
        NSMutableArray *mutableStatus = [status mutableCopy];
        [mutableStatus removeObjectAtIndex:0];
        status = [mutableStatus copy];
    } else {
        self.inputButton.hidden = YES;
    }
    
    NSMutableArray *lists = [[NSMutableArray alloc] init];
    for (int i = 0; i < self.buttonLists.count; i++) {
        VideoChatRoomItemButton *button = self.buttonLists[i];
        if (i < status.count) {
            NSNumber *number = status[i];
            VideoChatRoomBottomStatus bottomStatus = number.integerValue;
            
            button.tagNum = bottomStatus;
            NSString *imageName = [self getImageWithStatus:bottomStatus];
            UIImage *image = [UIImage imageNamed:imageName bundleName:HomeBundleName];
            [button bingImage:image status:ButtonStatusNone];
            [button bingImage:[self getSelectImageWithStatus:bottomStatus] status:ButtonStatusActive];
            button.hidden = NO;
            button.status = ButtonStatusNone;
            [lists addObject:button];
        } else {
            button.hidden = YES;
        }
    }
    
    if (isPKing && self.loginUserModel.userRole == VideoChatUserRoleHost) {
        [self updateButtonStatus:VideoChatRoomBottomStatusPK isSelect:YES];
    }
    
    if (lists.count > 1) {
        [lists mas_remakeConstraints:^(MASConstraintMaker *make) {
                
        }];
        [lists mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:itemWidth leadSpacing:0 tailSpacing:0];
        [lists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView);
            make.height.mas_equalTo(36);
        }];
    } else {
        VideoChatRoomItemButton *button = lists.firstObject;
        [button mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView);
            make.height.mas_equalTo(36);
            make.right.equalTo(self.contentView);
            make.width.mas_equalTo(itemWidth);
        }];
    }
    
    if (status.count == 0) {
        [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(0);
        }];
    } else {
        CGFloat counentWidth = (itemWidth * status.count) + ((status.count - 1) * 12);
        [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(counentWidth);
        }];
    }
}

- (void)updateButtonStatus:(VideoChatRoomBottomStatus)status isSelect:(BOOL)isSelect {
    VideoChatRoomItemButton *selectButton = nil;
    for (VideoChatRoomItemButton *button in self.buttonLists) {
        if (button.tagNum == status) {
            selectButton = button;
            break;
        }
    }
    if (selectButton) {
        selectButton.status = isSelect ? ButtonStatusActive : ButtonStatusNone;
    }
}

- (void)updateButtonStatus:(VideoChatRoomBottomStatus)status isRed:(BOOL)isRed {
    VideoChatRoomItemButton *selectButton = nil;
    for (VideoChatRoomItemButton *button in self.buttonLists) {
        if (button.tagNum == status) {
            selectButton = button;
            break;
        }
    }
    if (selectButton) {
        selectButton.isRed = isRed;
    }
}

#pragma mark - Private Action

- (NSArray *)getBottomListsWithModel:(VideoChatUserModel *)userModel isPKing:(BOOL)isPKing {
    NSArray *bottomLists = nil;
    if (VideoChatUserRoleHost == userModel.userRole) {
        bottomLists = @[@(VideoChatRoomBottomStatusInput),
                        @(VideoChatRoomBottomStatusPK),
                        @(VideoChatRoomBottomStatusPhone),
                        @(VideoChatRoomBottomStatusBeauty),
                        @(VideoChatRoomBottomStatusSet)];
    } else {
        if (VideoChatUserStatusActive == userModel.status) {
            bottomLists = @[@(VideoChatRoomBottomStatusInput),
                            @(VideoChatRoomBottomStatusBeauty),
                            @(VideoChatRoomBottomStatusSet)];
        } else {
            if (_chatRoomMode == VideoChatRoomModePK && !isPKing) {
                bottomLists = @[@(VideoChatRoomBottomStatusInput),
                                @(VideoChatRoomBottomStatusPhone)];
            } else {
                bottomLists = @[@(VideoChatRoomBottomStatusInput)];
            }
        }
    }
    return bottomLists;
}

- (NSString *)getImageWithStatus:(VideoChatRoomBottomStatus)status {
    NSString *name = @"";
    switch (status) {
        case VideoChatRoomBottomStatusPhone:
            name = @"videochat_bottom_phone";
            break;
        case VideoChatRoomBottomStatusBeauty:
            name = @"videochat_bottom_be";
            break;
        case VideoChatRoomBottomStatusSet:
            name = @"videochat_bottom_set";
            break;
        case VideoChatRoomBottomStatusPK:
            name = @"videochat_pk";
            break;
        default:
            break;
    }
    return name;
}

- (UIImage *)getSelectImageWithStatus:(VideoChatRoomBottomStatus)status {
    NSString *name = @"";
    switch (status) {
        case VideoChatRoomBottomStatusPhone:
            name = @"videochat_bottom_phone";
            break;
        case VideoChatRoomBottomStatusBeauty:
            name = @"videochat_bottom_be";
            break;
        case VideoChatRoomBottomStatusSet:
            name = @"videochat_bottom_set";
            break;
        case VideoChatRoomBottomStatusPK:
            name = @"videochat_pking";
            break;
        default:
            break;
    }
    return [UIImage imageNamed:name bundleName:HomeBundleName];
}

#pragma mark - getter

- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
        _contentView.backgroundColor = [UIColor clearColor];
    }
    return _contentView;
}

- (NSMutableArray *)buttonLists {
    if (!_buttonLists) {
        _buttonLists = [[NSMutableArray alloc] init];
    }
    return _buttonLists;
}

- (VideoChatRoomItemButton *)inputButton {
    if (!_inputButton) {
        _inputButton = [[VideoChatRoomItemButton alloc] init];
        _inputButton.titleLabel.font = [UIFont systemFontOfSize:14 weight:UIFontWeightRegular];
        _inputButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
        [_inputButton setTitle:LocalizedString(@"Add comment") forState:UIControlStateNormal];
        [_inputButton setTitleColor:[UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.7 * 255] forState:UIControlStateNormal];
        [_inputButton setTitleEdgeInsets:UIEdgeInsetsMake(0, 12, 0, -12)];
        [_inputButton setBackgroundImage:[UIImage imageNamed:@"videochat_textinput_border" bundleName:HomeBundleName] forState:UIControlStateNormal];
        [_inputButton addTarget:self action:@selector(inputButtonAction) forControlEvents:UIControlEventTouchUpInside];
        _inputButton.hidden = YES;
    }
    return _inputButton;
}

@end
