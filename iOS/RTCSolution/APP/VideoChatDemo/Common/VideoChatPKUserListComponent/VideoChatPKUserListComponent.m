// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatPKUserListComponent.h"
#import "VideoChatPKUserListView.h"

@interface VideoChatPKUserListComponent ()<VideoChatPKUserListViewDelegate>

@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, strong) UIControl *dismissControl;
@property (nonatomic, strong) VideoChatPKUserListView *userListView;

@end

@implementation VideoChatPKUserListComponent

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel {
    if (self = [super init]) {
        self.roomModel = roomModel;
    }
    return self;
}

- (void)showAnchorList {
    if (self.isPKWaitingReply) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_sent_invitation")];
        return;
    }
    
    UIViewController *rootVC = [DeviceInforTool topViewController];
    CGFloat height = ((300.0 / 667.0) * SCREEN_HEIGHT) + 52 + 48;
    
    [rootVC.view addSubview:self.dismissControl];
    [self.dismissControl addSubview:self.userListView];
    
    [self.dismissControl mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(rootVC.view);
    }];
    [self.userListView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.dismissControl);
        make.top.equalTo(self.dismissControl.mas_bottom);
        make.height.mas_equalTo(height);
    }];
    [rootVC.view layoutIfNeeded];
    [UIView animateWithDuration:0.25 animations:^{
        [self.userListView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self.dismissControl);
            make.bottom.equalTo(self.dismissControl.mas_bottom);
            make.height.mas_equalTo(height);
        }];
        [rootVC.view layoutIfNeeded];
    }];
    
    [self requestPKUserListData];
}

- (void)requestPKUserListData {
    __weak typeof(self) weakSelf = self;
    [VideoChatRTSManager requestPKUserListComplete:^(NSArray<VideoChatUserModel *> * _Nonnull userList, RTSACKModel * _Nonnull model) {
        if (model.result) {
            weakSelf.userListView.dataArray = userList;
        }
    }];
}

#pragma mark - VideoChatPKUserListViewDelegate
- (void)videoChatPKUserListView:(VideoChatPKUserListView *)view
              didClickUserModel:(VideoChatUserModel *)userModel {
    [self dismiss];
    __weak typeof(self) weakSelf = self;
    view.userInteractionEnabled = NO;
    [VideoChatRTSManager requestInviteAnchorWithFromRoomID:self.roomModel.roomID
                                                fromUserID:self.roomModel.hostUid
                                                  toRoomID:userModel.roomID
                                                  toUserID:userModel.uid
                                                    seatID:0
                                                  complete:^(RTSACKModel * _Nonnull model) {
        view.userInteractionEnabled = YES;
        if (model.result) {
            NSString *message = [NSString stringWithFormat:LocalizedString(@"invitation_sent_%@_waiting"), userModel.name];
            [[ToastComponent shareToastComponent] showWithMessage:message];
            weakSelf.isPKWaitingReply = YES;
            [weakSelf performSelector:@selector(resetPkWaitingReplyStstus) withObject:nil afterDelay:5];
        } else {
            if (model.code == 550 || model.code == 551) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"host_busy")];
            } else {
                [[ToastComponent shareToastComponent] showWithMessage:model.message];
            }
        }
    }];
}

#pragma mark - Received
- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"accept");
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = LocalizedString(@"decline");
    [[AlertActionManager shareAlertActionManager] showWithMessage:[NSString stringWithFormat:LocalizedString(@"%@_invites_you_connect"), anchorModel.name] actions:@[cancelModel, alertModel]];
    
    __weak typeof(self) weakSelf = self;
    alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"accept")]) {
            [weakSelf replyInvite:anchorModel.roomID userID:anchorModel.uid reply:VideoChatPKReplyAccept];
        }
    };
    cancelModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"decline")]) {
            [weakSelf replyInvite:anchorModel.roomID userID:anchorModel.uid reply:VideoChatPKReplyReject];
        }
    };
    [self performSelector:@selector(alertControllerDismiss) withObject:nil afterDelay:5];
}

- (void)alertControllerDismiss {
    [[AlertActionManager shareAlertActionManager] dismiss:^{
        
    }];
}

- (void)replyInvite:(NSString *)inviterRoomID userID:(NSString *)inviterUserID reply:(VideoChatPKReply)reply {
    
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(alertControllerDismiss) object:nil];
    
    __weak typeof(self) weakSelf = self;
    [VideoChatRTSManager replyInviteWithInviterRoomID:inviterRoomID
                                               inviterUserID:inviterUserID
                                                      roomID:self.roomModel.roomID
                                                      userID:self.roomModel.hostUid
                                                       reply:reply
                                                    complete:^(NSString * _Nonnull roomID, NSString * _Nonnull token, RTSACKModel * _Nonnull model) {
        if (model.result) {
            if (reply == 1) {
                [weakSelf startForwardStream:roomID token:token];
            }
        }
        else {
            [[ToastComponent shareToastComponent] showWithMessage:model.message];
        }
    }];
}

- (void)startForwardStream:(NSString *)roomID token:(NSString *)token {
    [[VideoChatRTCManager shareRtc] startForwardStream:roomID token:token];
}

- (void)resetPkWaitingReplyStstus {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(resetPkWaitingReplyStstus) object:nil];
    self.isPKWaitingReply = NO;
}

#pragma mark - Actions
- (void)dismiss {
    [self.userListView removeFromSuperview];
    [self.dismissControl removeFromSuperview];
}

#pragma mark - Getter
- (VideoChatPKUserListView *)userListView {
    if (!_userListView) {
        _userListView = [[VideoChatPKUserListView alloc] init];
        _userListView.delegate = self;
    }
    return _userListView;
}

- (UIControl *)dismissControl {
    if (!_dismissControl) {
        _dismissControl = [[UIControl alloc] init];
        [_dismissControl addTarget:self action:@selector(dismiss) forControlEvents:UIControlEventTouchUpInside];
    }
    return _dismissControl;
}

@end
