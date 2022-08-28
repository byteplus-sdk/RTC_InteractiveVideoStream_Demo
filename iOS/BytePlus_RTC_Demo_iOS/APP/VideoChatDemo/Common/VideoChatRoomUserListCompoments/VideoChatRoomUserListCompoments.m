/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomUserListCompoments.h"
#import "VideoChatRoomTopSelectView.h"
#import "VideoChatRoomTopSeatView.h"

@interface VideoChatRoomUserListCompoments () <VideoChatRoomTopSelectViewDelegate, VideoChatRoomRaiseHandListsViewDelegate, VideoChatRoomAudienceListsViewDelegate>

@property (nonatomic, strong) VideoChatRoomTopSeatView *topSeatView;
@property (nonatomic, strong) VideoChatRoomTopSelectView *topSelectView;
@property (nonatomic, strong) VideoChatRoomRaiseHandListsView *applyListsView;
@property (nonatomic, strong) VideoChatRoomAudienceListsView *onlineListsView;
@property (nonatomic, strong) UIButton *maskButton;

@property (nonatomic, copy) void (^dismissBlock)(void);
@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, copy) NSString *seatID;
@property (nonatomic, assign) BOOL isRed;

@end


@implementation VideoChatRoomUserListCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        _isRed = NO;
    }
    return self;
}

#pragma mark - Publish Action

- (void)showRoomModel:(VideoChatRoomModel *)roomModel
               seatID:(NSString *)seatID
         dismissBlock:(void (^)(void))dismissBlock {
    _roomModel = roomModel;
    _seatID = seatID;
    self.dismissBlock = dismissBlock;
    UIViewController *rootVC = [DeviceInforTool topViewController];
    
    [rootVC.view addSubview:self.maskButton];
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.left.height.equalTo(rootVC.view);
        make.top.equalTo(rootVC.view).offset(SCREEN_HEIGHT);
    }];
    
    [self.maskButton addSubview:self.applyListsView];
    [self.applyListsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.right.mas_equalTo(0);
        CGFloat hetight = ((300.0 / 667.0) * SCREEN_HEIGHT);
        make.height.mas_offset(hetight + [DeviceInforTool getVirtualHomeHeight]);
        make.bottom.mas_offset(0);
    }];
    
    [self.maskButton addSubview:self.onlineListsView];
    [self.onlineListsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.applyListsView);
    }];
    
    [self.maskButton addSubview:self.topSelectView];
    [self.topSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.maskButton);
        make.bottom.equalTo(self.applyListsView.mas_top);
        make.height.mas_equalTo(52);
    }];
    
    [self.maskButton addSubview:self.topSeatView];
    [self.topSeatView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.maskButton);
        make.bottom.equalTo(self.topSelectView.mas_top);
        make.height.mas_equalTo(48);
    }];
    
    // Start animation
    [rootVC.view layoutIfNeeded];
    [self.maskButton.superview setNeedsUpdateConstraints];
    [UIView animateWithDuration:0.25
                     animations:^{
        [self.maskButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(rootVC.view).offset(0);
        }];
        [self.maskButton.superview layoutIfNeeded];
    }];
    
    if (_isRed) {
        [self loadDataWithApplyLists];
        [self.topSelectView updateSelectItem:NO];
        self.onlineListsView.hidden = YES;
        self.applyListsView.hidden = NO;
    } else {
        [self loadDataWithOnlineLists];
        [self.topSelectView updateSelectItem:YES];
        self.onlineListsView.hidden = NO;
        self.applyListsView.hidden = YES;
    }
    
    __weak typeof(self) weakSelf = self;
    self.topSeatView.clickCloseChatRoomBlock = ^{
        [weakSelf closeChatRoom];
    };
}

- (void)update {
    if (self.onlineListsView.superview && !self.onlineListsView.hidden) {
        [self loadDataWithOnlineLists];
    } else if (self.applyListsView.superview && !self.applyListsView.hidden) {
        [self loadDataWithApplyLists];
    } else {
        
    }
}

- (void)updateWithRed:(BOOL)isRed {
    _isRed = isRed;
    [self.topSelectView updateWithRed:isRed];
}

- (void)updateCloseChatRoom:(BOOL)isHidden {
    self.topSeatView.hidden = isHidden;
}

- (void)resetInviteInteractionWaitingReplyStstus {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(resetInviteInteractionWaitingReplyStstus) object:nil];
    self.isInviteInteractionWaitingReply = NO;
}

#pragma mark - Load Data

- (void)loadDataWithOnlineLists {
    __weak __typeof(self) wself = self;
    [VideoChatRTMManager getAudienceList:_roomModel.roomID
                                          block:^(NSArray<VideoChatUserModel *> * _Nonnull userLists, RTMACKModel * _Nonnull model) {
        if (model.result) {
            wself.onlineListsView.dataLists = userLists;
        }
    }];
}

- (void)loadDataWithApplyLists {
    __weak __typeof(self) wself = self;
    [VideoChatRTMManager getApplyAudienceList:_roomModel.roomID
                                               block:^(NSArray<VideoChatUserModel *> * _Nonnull userLists, RTMACKModel * _Nonnull model) {
        if (model.result) {
            wself.applyListsView.dataLists = userLists;
        }
    }];
}

#pragma mark - VideoChatRoomTopSelectViewDelegate

- (void)VideoChatRoomTopSelectView:(VideoChatRoomTopSelectView *)VideoChatRoomTopSelectView clickCancelAction:(id)model {
    [self dismissUserListView];
}

- (void)VideoChatRoomTopSelectView:(VideoChatRoomTopSelectView *)VideoChatRoomTopSelectView clickSwitchItem:(BOOL)isAudience {
    if (isAudience) {
        self.onlineListsView.hidden = YES;
        self.applyListsView.hidden = NO;
        [self loadDataWithApplyLists];
    } else {
        self.onlineListsView.hidden = NO;
        self.applyListsView.hidden = YES;
        [self loadDataWithOnlineLists];
    }
}

#pragma mark - VideoChatRoomonlineListsViewDelegate

- (void)VideoChatRoomAudienceListsView:(VideoChatRoomRaiseHandListsView *)VideoChatRoomAudienceListsView clickButton:(VideoChatUserModel *)model {
    [self clickTableViewWithModel:model dataLists:VideoChatRoomAudienceListsView.dataLists];
}

#pragma mark - VideoChatRoomapplyListsViewDelegate

- (void)VideoChatRoomRaiseHandListsView:(VideoChatRoomRaiseHandListsView *)VideoChatRoomRaiseHandListsView clickButton:(VideoChatUserModel *)model {
    [self clickTableViewWithModel:model dataLists:VideoChatRoomRaiseHandListsView.dataLists];
}

#pragma mark - Private Action

- (void)clickTableViewWithModel:(VideoChatUserModel *)userModel dataLists:(NSArray<VideoChatUserModel *> *)dataLists {
    if (userModel.status == VideoChatUserStatusDefault) {
        __weak typeof(self) weakSelf = self;
        [VideoChatRTMManager inviteInteract:userModel.roomID
                                               uid:userModel.uid
                                            seatID:_seatID
                                             block:^(RTMACKModel * _Nonnull model) {
            if (!model.result) {
                [[ToastComponents shareToastComponents] showWithMessage:model.message];
            } else {
                [[ToastComponents shareToastComponents] showWithMessage:LocalizedString(@"Invitation has been sent. Waiting for responding.")];
                [weakSelf dismissUserListView];
                
                weakSelf.isInviteInteractionWaitingReply = YES;
                [weakSelf performSelector:@selector(resetInviteInteractionWaitingReplyStstus) withObject:nil afterDelay:5];
            }
        }];
    } else if (userModel.status == VideoChatUserStatusApply) {
        __weak __typeof(self)wself = self;
        [VideoChatRTMManager agreeApply:userModel.roomID
                                           uid:userModel.uid
                                         block:^(RTMACKModel * _Nonnull model) {
            if (model.result) {
                userModel.status = VideoChatUserStatusApply;
                [wself updateDataLists:dataLists model:userModel];
            } else {
                [[ToastComponents shareToastComponents] showWithMessage:model.message];
            }
        }];
    } else {
        
    }
}



- (void)updateDataLists:(NSArray<VideoChatUserModel *> *)dataLists
                  model:(VideoChatUserModel *)model {
    for (int i = 0; i < dataLists.count; i++) {
        VideoChatUserModel *currentModel = dataLists[i];
        if ([currentModel.uid isEqualToString:model.uid]) {
            NSMutableArray *mutableLists = [[NSMutableArray alloc] initWithArray:dataLists];
            [mutableLists replaceObjectAtIndex:i withObject:model];
            break;
        }
    }
}

- (void)removeDataLists:(NSArray<VideoChatUserModel *> *)dataLists model:(VideoChatUserModel *)model {
    VideoChatUserModel *deleteModel = nil;
    for (int i = 0; i < dataLists.count; i++) {
        VideoChatUserModel *currentModel = dataLists[i];
        if ([currentModel.uid isEqualToString:model.uid]) {
            deleteModel = currentModel;
            break;
        }
    }

    if (deleteModel) {
        NSMutableArray *mutableLists = [[NSMutableArray alloc] initWithArray:dataLists];
        [mutableLists removeObject:deleteModel];
        dataLists = [mutableLists copy];
    }
}

- (void)maskButtonAction {
    [self dismissUserListView];
}

- (void)changeChatRoomModeDismissUserListView {
    if (self.roomModel.roomID) {
        [self loadDataWithApplyLists];
    }
    [self dismissUserListView];
}

- (void)dismissUserListView {
    _seatID = @"-1";
    [self.maskButton removeAllSubviews];
    [self.maskButton removeFromSuperview];
    self.maskButton = nil;
    if (self.dismissBlock) {
        self.dismissBlock();
    }
}

- (void)closeChatRoom {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"Confirm");
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = LocalizedString(@"Cancel");
    [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"Turn off chat room mode?") actions:@[cancelModel, alertModel]];
    
    __weak typeof(self) weakSelf = self;
    alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"Confirm")]) {
            [VideoChatRTMManager requestCloseChatRoomMode:weakSelf.roomModel.roomID complete:^(RTMACKModel * _Nonnull model) {
                if (!model.result) {
                    [[ToastComponents shareToastComponents] showWithMessage:model.message];
                } else {
                    [weakSelf dismissUserListView];
                }
            }];
        }
    };
    cancelModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"Cancel")]) {
            
        }
    };
}

#pragma mark - Getter

- (VideoChatRoomRaiseHandListsView *)applyListsView {
    if (!_applyListsView) {
        _applyListsView = [[VideoChatRoomRaiseHandListsView alloc] init];
        _applyListsView.delegate = self;
        _applyListsView.backgroundColor = [UIColor colorFromRGBHexString:@"#0E0825" andAlpha:0.95 * 255];
    }
    return _applyListsView;
}

- (VideoChatRoomAudienceListsView *)onlineListsView {
    if (!_onlineListsView) {
        _onlineListsView = [[VideoChatRoomAudienceListsView alloc] init];
        _onlineListsView.delegate = self;
        _onlineListsView.backgroundColor = [UIColor colorFromRGBHexString:@"#0E0825" andAlpha:0.95 * 255];
    }
    return _onlineListsView;
}

- (UIButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[UIButton alloc] init];
        [_maskButton addTarget:self action:@selector(maskButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_maskButton setBackgroundColor:[UIColor clearColor]];
    }
    return _maskButton;
}

- (VideoChatRoomTopSelectView *)topSelectView {
    if (!_topSelectView) {
        _topSelectView = [[VideoChatRoomTopSelectView alloc] init];
        _topSelectView.delegate = self;
    }
    return _topSelectView;
}

- (VideoChatRoomTopSeatView *)topSeatView {
    if (!_topSeatView) {
        _topSeatView = [[VideoChatRoomTopSeatView alloc] init];
    }
    return _topSeatView;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
