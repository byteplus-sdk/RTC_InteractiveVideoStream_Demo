/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatSeatComponent.h"
#import "VideoChatSeatView.h"

@interface VideoChatSeatComponent () <VideoChatSheetViewDelegate>

@property (nonatomic, weak) VideoChatSeatView *seatView;
@property (nonatomic, weak) VideoChatSheetView *sheetView;
@property (nonatomic, weak) UIView *superView;


@end

@implementation VideoChatSeatComponent

- (instancetype)initWithSuperView:(UIView *)superView {
    self = [super init];
    if (self) {
        _superView = superView;
    }
    return self;
}

#pragma mark - Publish Action

- (void)showSeatView:(NSArray<VideoChatSeatModel *> *)seatList
      loginUserModel:(VideoChatUserModel *)loginUserModel
       hostUserModel:(VideoChatUserModel *)hostUserModel {
    _loginUserModel = loginUserModel;
    self.hostUserModel = hostUserModel;
    
    if (!_seatView) {
        VideoChatSeatView *seatView = [[VideoChatSeatView alloc] init];
        [_superView addSubview:seatView];
        [seatView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(0);
            make.right.mas_equalTo(0);
            make.height.mas_equalTo(SCREEN_WIDTH / 3 * 2);
            make.top.mas_equalTo(72 + [DeviceInforTool getStatusBarHight]);
        }];
        _seatView = seatView;
    }
    
    // Add host
    NSMutableArray *seatMutableList = [seatList mutableCopy];
    VideoChatSeatModel *hostSeatModel = [[VideoChatSeatModel alloc] init];
    hostSeatModel.status = 1;
    hostSeatModel.index = 0;
    hostSeatModel.userModel = hostUserModel;
    [seatMutableList insertObject:hostSeatModel atIndex:0];
    seatList = [seatMutableList copy];
    
    _seatView.seatList = seatList;
    
    __weak __typeof(self) wself = self;
    _seatView.clickBlock = ^(VideoChatSeatModel * _Nonnull seatModel) {
        VideoChatSheetView *sheetView = [[VideoChatSheetView alloc] init];
        sheetView.delegate = wself;
        [wself.superView addSubview:sheetView];
        [sheetView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(wself.superView);
        }];
        [sheetView showWithSeatModel:seatModel
                      loginUserModel:wself.loginUserModel];
        wself.sheetView = sheetView;
    };
}

- (void)addSeatModel:(VideoChatSeatModel *)seatModel {
    [_seatView addSeatModel:seatModel];
    [self updateSeatModel:seatModel];
}

- (void)removeUserModel:(VideoChatUserModel *)userModel {
    [_seatView removeUserModel:userModel];
    if ([userModel.uid isEqualToString:_loginUserModel.uid]) {
        _loginUserModel = userModel;
    }
    NSString *sheetUid = self.sheetView.seatModel.userModel.uid;
    if (self.sheetView &&
        [userModel.uid isEqualToString:sheetUid]) {
        // update the new one to open the sheet user
        [self.sheetView dismiss];
    }
}

- (void)updateSeatModel:(VideoChatSeatModel *)seatModel {
    [_seatView updateSeatModel:seatModel];
    if ([seatModel.userModel.uid isEqualToString:_loginUserModel.uid]) {
        _loginUserModel = seatModel.userModel;
    }
    NSString *sheetUid = self.sheetView.seatModel.userModel.uid;
    if (self.sheetView &&
        [seatModel.userModel.uid isEqualToString:sheetUid]) {
        // update the new one to open the sheet user
        [self.sheetView dismiss];
    }
}

- (void)updateSeatVolume:(NSDictionary *)volumeDic {
    [_seatView updateSeatVolume:volumeDic];
}

- (void)updateSeatRender:(NSString *)uid {
    [_seatView updateSeatRender:uid];
}

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid {
    [self.seatView updateNetworkQuality:status uid:uid];
}

- (void)changeChatRoomMode:(VideoChatRoomMode)mode {
    if (mode == VideoChatRoomModeChatRoom) {
        [self showSeatView:[self getDefaultSeatDataList] loginUserModel:self.loginUserModel hostUserModel:self.hostUserModel];
    }
    else {
        [_seatView removeFromSuperview];
        _seatView = nil;
    }
}

- (void)audienceApplyInteraction {
    VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
    seatModel.status = 1;
    seatModel.index = -1;
    
    VideoChatSheetView *sheetView = [[VideoChatSheetView alloc] init];
    sheetView.delegate = self;
    [self.superView addSubview:sheetView];
    [sheetView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.superView);
    }];
    [sheetView showWithSeatModel:seatModel
                  loginUserModel:self.loginUserModel];
    self.sheetView = sheetView;
}

- (NSArray *)getDefaultSeatDataList {
    NSMutableArray *list = [[NSMutableArray alloc] init];
    for (int i = 0; i < 5; i++) {
        VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
        seatModel.status = 1;
        seatModel.index = i + 1;
        [list addObject:seatModel];
    }
    return [list copy];
}

#pragma mark - VideoChatSheetViewDelegate

- (void)VideoChatSheetView:(VideoChatSheetView *)VideoChatSheetView
               clickButton:(VideoChatSheetStatus)sheetState {
    if (sheetState == VideoChatSheetStatusInvite) {
        if ([self.delegate respondsToSelector:@selector
             (VideoChatSeatComponent:clickButton:sheetStatus:)]) {
            [self.delegate VideoChatSeatComponent:self
                                       clickButton:VideoChatSheetView.seatModel
                                       sheetStatus:sheetState];
        }
        [VideoChatSheetView dismiss];
    } else if (sheetState == VideoChatSheetStatusKick) {
        [self loadDataManager:5 sheetView:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusOpenMic) {
        [self loadDataManager:4 sheetView:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusCloseMic) {
        [self loadDataManager:3 sheetView:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusLock) {
        [self showAlertWithLockSeat:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusUnlock) {
        [self loadDataManager:2 sheetView:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusApply) {
        [self loadDataApply:VideoChatSheetView];
    } else if (sheetState == VideoChatSheetStatusLeave) {
        [self loadDataLeave:VideoChatSheetView];
    } else {
        //error
    }
}

#pragma mark - Private Action

- (void)loadDataManager:(NSInteger)type
              sheetView:(VideoChatSheetView *)VideoChatSheetView {
    NSString *seatID = [NSString stringWithFormat:@"%ld", (long)VideoChatSheetView.seatModel.index];
    [VideoChatRTMManager managerSeat:VideoChatSheetView.loginUserModel.roomID
                                     seatID:seatID
                                       type:type
                                      block:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Please try again")];
        } else {
            [VideoChatSheetView dismiss];
        }
    }];
}

- (void)loadDataApply:(VideoChatSheetView *)VideoChatSheetView {
    NSString *seatID = [NSString stringWithFormat:@"%ld", (long)VideoChatSheetView.seatModel.index];
    [VideoChatRTMManager applyInteract:VideoChatSheetView.loginUserModel.roomID
                                       seatID:seatID
                                        block:^(BOOL isNeedApply,
                                                RTMACKModel * _Nonnull model) {
        if (!model.result) {
            if (model.code == 550 || model.code == 551) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"The Invited is busy")];
            } else {
                [[ToastComponent shareToastComponent] showWithMessage:model.message];
            }
        } else {
            if (isNeedApply) {
                VideoChatSheetView.loginUserModel.status = VideoChatUserStatusApply;
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Guest request sent")];
            }
            [VideoChatSheetView dismiss];
        }
    }];
}


- (void)loadDataLeave:(VideoChatSheetView *)VideoChatSheetView {
    NSString *seatID = [NSString stringWithFormat:@"%ld", (long)VideoChatSheetView.seatModel.index];
    [VideoChatRTMManager finishInteract:VideoChatSheetView.loginUserModel.roomID
                                        seatID:seatID
                                         block:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Please try again")];
        } else {
            [VideoChatSheetView dismiss];
        }
    }];
}

- (void)showAlertWithLockSeat:(VideoChatSheetView *)VideoChatSheetView {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"OK");
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = LocalizedString(@"Cancel");
    [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"Sure to block this guest seat? If so, an audience can't be a guest in the seat, and the guest in the seat will be changed into an audience.") actions:@[ cancelModel, alertModel ]];
    __weak __typeof(self) wself = self;
    alertModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"OK")]) {
            [wself loadDataManager:1 sheetView:VideoChatSheetView];
        }
    };
}



@end
