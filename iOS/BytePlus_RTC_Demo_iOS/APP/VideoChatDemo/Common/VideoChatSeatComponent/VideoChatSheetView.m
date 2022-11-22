/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatSheetView.h"

@interface VideoChatSheetView ()

@property (nonatomic, strong) UIButton *maskButton;
@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, strong) NSMutableArray *buttonList;

@end

@implementation VideoChatSheetView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.maskButton];
        [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.width.left.height.equalTo(self);
            make.top.equalTo(self).offset(SCREEN_HEIGHT);
        }];
        
        [self.maskButton addSubview:self.contentView];
        [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.bottom.equalTo(self.maskButton);
            make.height.mas_equalTo(108 + [DeviceInforTool getVirtualHomeHeight]);
        }];
        
        for (int i = 0; i < 3; i++) {
            VideoChatSeatItemButton *button = [[VideoChatSeatItemButton alloc] init];
            [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
            [button setImageEdgeInsets:UIEdgeInsetsMake(0, 0, 24, 0)];
            button.imageView.contentMode = UIViewContentModeScaleAspectFit;
            [self.contentView addSubview:button];
            [self.buttonList addObject:button];
        }
    }
    return self;
}

- (void)buttonAction:(VideoChatSeatItemButton *)sender {
    if ([self.delegate respondsToSelector:@selector(VideoChatSheetView:clickButton:)]) {
        [self.delegate VideoChatSheetView:self clickButton:sender.sheetState];
    }
}

#pragma mark - Publish Action

- (void)showWithSeatModel:(VideoChatSeatModel *)seatModel
           loginUserModel:(VideoChatUserModel *)loginUserModel {
    _seatModel = seatModel;
    _loginUserModel = loginUserModel;
    
    NSArray *statusList = [self getSheetListWithModel:seatModel
                                       loginUserModel:loginUserModel];
    if (statusList.count <= 0) {
        [self dismiss];
        return;
    }
    // Start animation
    [self layoutIfNeeded];
    [self.maskButton.superview setNeedsUpdateConstraints];
    [UIView animateWithDuration:0.25
                     animations:^{
        [self.maskButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self).offset(0);
        }];
        [self.maskButton.superview layoutIfNeeded];
    }];
    CGFloat num = statusList.count;
    CGFloat itemWidth = SCREEN_WIDTH / num;
    
    NSMutableArray *list = [[NSMutableArray alloc] init];
    for (int i = 0; i < self.buttonList.count; i++) {
        VideoChatSeatItemButton *button = self.buttonList[i];
        if (i < num) {
            NSNumber *number = statusList[i];
            VideoChatSheetStatus state = number.integerValue;
            button.hidden = NO;
            UIImage *image = [UIImage imageNamed:[self getImageNameWithStatus:state] bundleName:HomeBundleName];
            [button bingImage:image status:ButtonStatusNone];
            button.desTitle = [self getTitleWithStatus:state];
            button.sheetState = state;
            [list addObject:button];
        } else {
            button.hidden = YES;
        }
    }
    if (list.count <= 1) {
        VideoChatSeatItemButton *button = self.buttonList.firstObject;
        [button mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView).offset(20);
            make.height.mas_equalTo(68);
            make.width.mas_equalTo(125);
            make.centerX.equalTo(self.contentView);
        }];
    } else {
        [list mas_remakeConstraints:^(MASConstraintMaker *make) {
                
        }];
        [list mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:itemWidth leadSpacing:0 tailSpacing:0];
        [list mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView).offset(20);
            make.height.mas_equalTo(68);
        }];
    }
}

- (void)dismiss {
    [self.maskButton removeFromSuperview];
    self.maskButton = nil;
    
    [self removeFromSuperview];
}

#pragma mark - Private Action

- (NSArray *)getSheetListWithModel:(VideoChatSeatModel *)seatModel
                    loginUserModel:(VideoChatUserModel *)loginUserModel {
    NSArray *list = nil;
    if (seatModel.userModel.userRole == VideoChatUserRoleHost) {
        // 点击主播
    } else {
        if (loginUserModel.userRole == VideoChatUserRoleHost) {
            if (seatModel) {
                if (seatModel.status == 1) {
                    // unlock
                    if (NOEmptyStr(seatModel.userModel.uid)) {
                        if (seatModel.userModel.mic) {
                            // 存在用户 下麦 & 静音 & 锁麦
                            list = @[@(VideoChatSheetStatusKick),
                                     @(VideoChatSheetStatusCloseMic),
                                     @(VideoChatSheetStatusLock)];
                        } else {
                            // 存在用户 下麦 & 打开麦克风 & 锁麦
                            list = @[@(VideoChatSheetStatusKick),
                                     @(VideoChatSheetStatusOpenMic),
                                     @(VideoChatSheetStatusLock)];
                        }
                    } else {
                        // 不存在用户， 邀请上麦，锁麦
                        list = @[@(VideoChatSheetStatusInvite),
                                 @(VideoChatSheetStatusLock)];
                    }
                } else {
                    // lock, 解锁
                    list = @[@(VideoChatSheetStatusUnlock)];
                }
            } else {
                // 麦位为空，邀请上麦 & 锁麦位
                list = @[@(VideoChatSheetStatusInvite),
                         @(VideoChatSheetStatusLock)];
            }
        } else {
            if (seatModel.status == 0) {
                // 麦位被锁
            } else {
                if ([loginUserModel.uid isEqualToString:seatModel.userModel.uid]) {
                    // 主动下麦
                    list = @[@(VideoChatSheetStatusLeave)];
                } else {
                    if (NOEmptyStr(seatModel.userModel.uid)) {
                        // 麦位有人
                    } else {
                        if (loginUserModel.status == VideoChatUserStatusApply) {
                            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Guest request sent")];
                        } else if (loginUserModel.status == VideoChatUserStatusActive) {
                            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been a guest")];
                        } else {
                            // 申请上麦
                            list = @[@(VideoChatSheetStatusApply)];
                        }
                    }
                }
            }
        }
    }
    return list;
}

- (void)maskButtonAction {
    [self dismiss];
}

- (NSString *)getImageNameWithStatus:(VideoChatSheetStatus)status {
    NSString *name = @"";
    switch (status) {
        case VideoChatSheetStatusInvite:
            name = @"videochat_sheet_phone";
            break;
        case VideoChatSheetStatusKick:
            name = @"videochat_sheet_leave";
            break;
        case VideoChatSheetStatusOpenMic:
            name = @"videochat_sheet_mic_s";
            break;
        case VideoChatSheetStatusCloseMic:
            name = @"videochat_sheet_mic";
            break;
        case VideoChatSheetStatusLock:
            name = @"videochat_sheet_lock";
            break;
        case VideoChatSheetStatusUnlock:
            name = @"videochat_sheet_unlock";
            break;
        case VideoChatSheetStatusApply:
            name = @"videochat_sheet_phone";
            break;
        case VideoChatSheetStatusLeave:
            name = @"videochat_sheet_leave";
            break;
        default:
            break;
    }
    return name;
}

- (NSString *)getTitleWithStatus:(VideoChatSheetStatus)status {
    NSString *name = @"";
    switch (status) {
        case VideoChatSheetStatusInvite:
            name = LocalizedString(@"Invite");
            break;
        case VideoChatSheetStatusKick:
            name = LocalizedString(@"Disconnect");
            break;
        case VideoChatSheetStatusOpenMic:
            name = LocalizedString(@"Unmute");
            break;
        case VideoChatSheetStatusCloseMic:
            name = LocalizedString(@"Mute");
            break;
        case VideoChatSheetStatusLock:
            name = LocalizedString(@"Block");
            break;
        case VideoChatSheetStatusUnlock:
            name = LocalizedString(@"Unblock");
            break;
        case VideoChatSheetStatusApply:
            name = LocalizedString(@"Request");
            break;
        case VideoChatSheetStatusLeave:
            name = LocalizedString(@"Disconnect\0");
            break;
        default:
            break;
    }
    return name;
}

#pragma mark - Getter

- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
        _contentView.backgroundColor = [UIColor colorFromRGBHexString:@"#0E0825" andAlpha:0.95 * 255];
    }
    return _contentView;
}

- (UIButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[UIButton alloc] init];
        [_maskButton addTarget:self action:@selector(maskButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_maskButton setBackgroundColor:[UIColor clearColor]];
    }
    return _maskButton;
}

- (NSMutableArray *)buttonList {
    if (!_buttonList) {
        _buttonList = [[NSMutableArray alloc] init];
    }
    return _buttonList;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
