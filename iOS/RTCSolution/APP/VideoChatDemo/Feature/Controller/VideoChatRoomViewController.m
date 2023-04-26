// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "BytedEffectProtocol.h"
#import "ToolKit.h"
#import "VideoChatMusicComponent.h"
#import "VideoChatPKComponent.h"
#import "VideoChatPKUserListComponent.h"
#import "VideoChatPeopleNumView.h"
#import "VideoChatRoomBottomView.h"
#import "VideoChatRoomSettingComponent.h"
#import "VideoChatRoomUserListComponent.h"
#import "VideoChatRoomViewController+SocketControl.h"
#import "VideoChatRoomViewController.h"
#import "VideoChatSeatComponent.h"
#import "VideoChatStaticView.h"
#import "VideoChatTextInputComponent.h"

@interface VideoChatRoomViewController () <
    VideoChatRoomBottomViewDelegate,
    VideoChatRTCManagerDelegate,
    VideoChatSeatDelegate>

@property (nonatomic, strong) UIImageView *bgImageImageView;
@property (nonatomic, strong) VideoChatStaticView *staticView;
@property (nonatomic, strong) VideoChatRoomBottomView *bottomView;
@property (nonatomic, strong) VideoChatMusicComponent *musicComponent;
@property (nonatomic, strong) VideoChatTextInputComponent *textInputComponent;
@property (nonatomic, strong) VideoChatRoomUserListComponent *userListComponent;
@property (nonatomic, strong) VideoChatRoomSettingComponent *settingComponent;
@property (nonatomic, strong) BytedEffectProtocol *beautyComponent;
@property (nonatomic, strong) BaseIMComponent *imComponent;
@property (nonatomic, strong) VideoChatSeatComponent *seatComponent;
@property (nonatomic, strong) VideoChatPKUserListComponent *pkUserListComponent;
@property (nonatomic, strong) VideoChatPKComponent *pkComponent;

@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, strong) VideoChatUserModel *hostUserModel;
@property (nonatomic, assign) VideoChatRoomMode chatRoomMode;
@property (nonatomic, copy) NSString *rtcToken;

@end

@implementation VideoChatRoomViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel {
    self = [super init];
    if (self) {
        // Audience initialization
        _roomModel = roomModel;
        [[VideoChatRTCManager shareRtc] updateVideoConfigWithHost:NO];
    }
    return self;
}

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                         rtcToken:(NSString *)rtcToken
                    hostUserModel:(VideoChatUserModel *)hostUserModel {
    self = [super init];
    if (self) {
        // Host initialization
        _hostUserModel = hostUserModel;
        _roomModel = roomModel;
        _rtcToken = rtcToken;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    self.view.backgroundColor = [UIColor colorFromHexString:@"#394254"];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(clearRedNotification) name:KClearRedNotification object:nil];
    [self addSocketListener];
    [self addSubviewAndConstraints];
    [self joinRoom];
    [self.beautyComponent resume];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.navigationController.interactivePopGestureRecognizer.enabled = NO;
}

#pragma mark - Notification

- (void)clearRedNotification {
    [self.bottomView updateButtonStatus:VideoChatRoomBottomStatusPhone isRed:NO];
    [self.userListComponent updateWithRed:NO];
}

#pragma mark - SocketControl

- (void)receivedJoinUser:(VideoChatUserModel *)userModel
                   count:(NSInteger)count {
    [self addIMMessage:YES userModel:userModel];
    [self.staticView updatePeopleNum:count];
    [self.userListComponent update];
}

- (void)receivedLeaveUser:(VideoChatUserModel *)userModel
                    count:(NSInteger)count {
    [self addIMMessage:NO userModel:userModel];
    [self.staticView updatePeopleNum:count];
    [self.userListComponent update];
}

- (void)receivedFinishLive:(NSInteger)type roomID:(NSString *)roomID {
    if (![roomID isEqualToString:self.roomModel.roomID]) {
        return;
    }
    [self hangUp:NO];
    if (type == 3) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"closed_terms_service") delay:0.8];
    } else if (type == 2 && [self isHost]) {
        [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"experience_time_exceeded_%@_minutes"), @"20"] delay:0.8];
    } else {
        if (![self isHost]) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_live_ended") delay:0.8];
        }
    }
}

- (void)receivedJoinInteractWithUser:(VideoChatUserModel *)userModel
                              seatID:(NSString *)seatID {
    self.chatRoomMode = VideoChatRoomModeChatRoom;

    VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
    seatModel.status = 1;
    seatModel.userModel = userModel;
    seatModel.index = seatID.integerValue;
    [self.seatComponent addSeatModel:seatModel];
    [self.userListComponent update];
    if ([userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        // The logged-in user make guest
        [self.bottomView updateBottomLists:userModel];

        self.settingComponent.mic = (userModel.mic == VideoChatUserMicOn);
        self.settingComponent.camera = (userModel.camera == VideoChatUserCameraOn);
        [[VideoChatRTCManager shareRtc] makeGuest:self.settingComponent.camera
                                       microphone:self.settingComponent.mic];
        
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_chat_you_on-mic")];
    }
    // Show local IM messages
    BaseIMModel *model = [[BaseIMModel alloc] init];
    NSString *message = [NSString stringWithFormat:LocalizedString(@"video_chat_%@_you_on-mic"), userModel.name];
    model.message = message;
    [self.imComponent addIM:model];
}

- (void)receivedLeaveInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID
                                 type:(NSInteger)type {
    [self.seatComponent removeUserModel:userModel];
    [self.userListComponent update];
    if ([userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        // The logged-in user make audience
        [self.bottomView updateBottomLists:userModel];
        [[VideoChatRTCManager shareRtc] makeAudience];
        if (type == 1) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_chat_removed_on-mic")];
        } else if (type == 2) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_chat_you_off-mic")];
        }
    }
    // Show local IM messages
    BaseIMModel *model = [[BaseIMModel alloc] init];
    NSString *message = [NSString stringWithFormat:LocalizedString(@"video_chat_%@_you_off-mic"), userModel.name];
    model.message = message;
    [self.imComponent addIM:model];
}

- (void)receivedSeatStatusChange:(NSString *)seatID
                            type:(NSInteger)type {
    VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
    seatModel.status = type;
    seatModel.userModel = nil;
    seatModel.index = seatID.integerValue;
    [self.seatComponent updateSeatModel:seatModel];
}

- (void)receivedMediaStatusChangeWithUser:(VideoChatUserModel *)userModel
                                   seatID:(NSString *)seatID
                                      mic:(NSInteger)mic
                                   camera:(NSInteger)camera {
    if ([userModel.uid isEqualToString:self.hostUserModel.uid]) {
        self.hostUserModel = userModel;
    }

    if (self.chatRoomMode == VideoChatRoomModeMakeCoHost) {
        [self.pkComponent updateUserModel:userModel];
        if ([userModel.uid isEqualToString:self.hostUserModel.uid]) {
            self.seatComponent.hostUserModel = userModel;
        }
    } else {
        VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
        seatModel.status = 1;
        seatModel.userModel = userModel;
        seatModel.index = seatID.integerValue;
        [self.seatComponent updateSeatModel:seatModel];
    }

    if ([userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        // Update the audio and video streaming status of the logged-in user
        [[VideoChatRTCManager shareRtc] publishAudioStream:(userModel.mic == VideoChatUserMicOff) ? NO : YES];
        [[VideoChatRTCManager shareRtc] publishVideoStream:(userModel.camera == VideoChatUserCameraOff) ? NO : YES];
        [self.settingComponent updateUserMic:userModel.mic == VideoChatUserMicOn];
    }
}

- (void)receivedMessageWithUser:(VideoChatUserModel *)userModel
                        message:(NSString *)message {
    if (![userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        // Remote IM message received
        BaseIMModel *model = [[BaseIMModel alloc] init];
        NSString *imMessage = [NSString stringWithFormat:@"%@：%@",
                                                         userModel.name,
                                                         message];
        model.message = imMessage;
        [self.imComponent addIM:model];
    }
}

- (void)receivedInviteInteractWithUser:(VideoChatUserModel *)hostUserModel
                                seatID:(NSString *)seatID {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"accept");
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = LocalizedString(@"decline");
    [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"host_invited_you_on-mic") actions:@[ cancelModel, alertModel ]];

    __weak __typeof(self) wself = self;
    alertModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
      if ([action.title isEqualToString:LocalizedString(@"accept")]) {
          [wself loadDataWithReplyInvite:1];
      }
    };
    cancelModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
      if ([action.title isEqualToString:LocalizedString(@"decline")]) {
          [wself loadDataWithReplyInvite:2];
      }
    };
    [self performSelector:@selector(dismissAnchorInvite) withObject:nil afterDelay:5];
}

- (void)receivedApplyInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID {
    if ([self isHost]) {
        [self.bottomView updateButtonStatus:VideoChatRoomBottomStatusPhone isRed:YES];
        [self.userListComponent updateWithRed:YES];
        [self.userListComponent update];
    }
}

- (void)receivedInviteResultWithUser:(VideoChatUserModel *)hostUserModel
                               reply:(NSInteger)reply {
    if ([self isHost] && reply == 2) {
        NSString *message = [NSString stringWithFormat:LocalizedString(@"video_%@_declined_invitation"), hostUserModel.name];
        [[ToastComponent shareToastComponent] showWithMessage:message];
        [self.userListComponent update];
    }

    if ([self isHost]) {
        [self.userListComponent resetInviteInteractionWaitingReplyStstus];
    }
}

- (void)receivedMediaOperatWithUid:(NSInteger)mic camera:(NSInteger)camera {
    [VideoChatRTSManager updateMediaStatus:self.roomModel.roomID
                                       mic:mic
                                    camera:camera
                                     block:^(RTSACKModel *_Nonnull model){

                                     }];
    if (mic) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"host_unmuted_you")];
    } else {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"you_muted_by_host_title")];
    }
}

- (void)receivedClearUserWithUid:(NSString *)uid {
    [self hangUp:NO];
    [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"same_logged_in") delay:0.8];
}

- (void)hangUp:(BOOL)isServer {
    if (isServer) {
        if ([self isHost]) {
            [VideoChatRTSManager finishLive:self.roomModel.roomID];
        } else {
            [VideoChatRTSManager leaveLiveRoom:self.roomModel.roomID];
        }
    }
    [[VideoChatRTCManager shareRtc] leaveRTCRoom];
    [self navigationControllerPop];
}

- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel {
    [self.pkUserListComponent receivedAnchorPKInvite:anchorModel];
}

- (void)receivedAnchorPKReply:(VideoChatPKReply)reply
                       roomID:(NSString *)roomID
                        token:(NSString *)token
                  anchorModel:(VideoChatUserModel *)anchorModel {
    [self.pkUserListComponent resetPkWaitingReplyStstus];

    if (reply == VideoChatPKReplyAccept) {
        [self.pkUserListComponent startForwardStream:roomID token:token];
    } else {
        [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"video_%@_declined_invitation"), anchorModel.name]];
    }
}

- (void)receivedAnchorPKNewAnchorJoined:(VideoChatUserModel *)anchorModel {
    self.chatRoomMode = VideoChatRoomModeMakeCoHost;
    self.pkComponent.anchorModel = anchorModel;
    [self.bottomView updateBottomListsWithPK:YES];
}

- (void)receivedAnchorPKEnd {
    if ([self isHost]) {
        if (self.pkComponent.activeEndPK) {
            [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"video_disconnected_%@"), self.pkComponent.anchorModel.name]];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"video_%@_has_left"), self.pkComponent.anchorModel.name]];
        }
        [self.pkComponent rtcStopForwardStream];
        self.pkComponent.activeEndPK = NO;
    }
    self.pkComponent.anchorModel = nil;
    [self.bottomView updateBottomListsWithPK:NO];
}

- (void)receiverCloseChatRoomMode {
    self.chatRoomMode = VideoChatRoomModeMakeCoHost;
}

- (void)receivedMuteOtherAnchorRoomID:(NSString *)roomID otherAnchorUserID:(NSString *)otherAnchorUserID type:(VideoChatOtherAnchorMicType)type {
    [self.pkComponent muteOtherAnchorRoomID:roomID otherAnchorUserID:otherAnchorUserID type:type];
}

#pragma mark - Load Data

- (void)loadDataWithJoinRoom {
    __weak __typeof(self) wself = self;
    [VideoChatRTSManager joinLiveRoom:self.roomModel.roomID
                             userName:[LocalUserComponent userModel].name
                                block:^(NSString * _Nonnull RTCToken,
                                        VideoChatRoomModel *_Nonnull roomModel,
                                        VideoChatUserModel *_Nonnull userModel,
                                        VideoChatUserModel *_Nonnull hostUserModel,
                                        NSArray<VideoChatSeatModel *> * _Nonnull seatList,
                                        NSArray<VideoChatUserModel *> * _Nonnull anchorList,
                                        RTSACKModel * _Nonnull model) {
        if (NOEmptyStr(roomModel.roomID)) {
            [wself joinRTCRoomWithData:RTCToken
                             roomModel:roomModel
                             userModel:userModel
                         hostUserModel:hostUserModel
                              seatList:seatList
                            anchorList:anchorList];
        } else {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = LocalizedString(@"ok");
            alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"ok")]) {
                    [wself hangUp:NO];
                }
            };
            [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"joining_room_failed") actions:@[alertModel]];
        }
    }];
}

- (void)loadDataWithReplyInvite:(NSInteger)type {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismissAnchorInvite) object:nil];
    [VideoChatRTSManager replyInvite:self.roomModel.roomID
                                      reply:type
                                      block:^(RTSACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponent shareToastComponent] showWithMessage:model.message];
        }
    }];
}

#pragma mark - VideoChatRoomBottomViewDelegate

- (void)videoChatRoomBottomView:(VideoChatRoomBottomView *_Nonnull)videoChatRoomBottomView
                     itemButton:(VideoChatRoomItemButton *_Nullable)itemButton
                didSelectStatus:(VideoChatRoomBottomStatus)status {
    if (status == VideoChatRoomBottomStatusInput) {
        [self.textInputComponent showWithRoomModel:self.roomModel];
        __weak __typeof(self) wself = self;
        self.textInputComponent.clickSenderBlock = ^(NSString *_Nonnull text) {
          BaseIMModel *model = [[BaseIMModel alloc] init];
          NSString *message = [NSString stringWithFormat:@"%@：%@",
                                                         [LocalUserComponent userModel].name,
                                                         text];
          model.message = message;
          [wself.imComponent addIM:model];
        };
    } else if (status == VideoChatRoomBottomStatusPhone) {
        if (self.pkUserListComponent.isPKWaitingReply) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"host_busy")];
            return;
        }
        if ([self isHost]) {
            if (self.pkComponent.anchorModel) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"video_host_in_room_title")];
            } else {
                [self.userListComponent showRoomModel:self.roomModel
                                               seatID:@"-1"
                                         dismissBlock:^{

                                         }];
            }
        } else {
            [self.seatComponent audienceApplyInteraction];
        }

    } else if (status == VideoChatRoomBottomStatusBeauty) {
        if (self.beautyComponent) {
            [self.beautyComponent showWithView:self.view
                                  dismissBlock:^(BOOL result){

                                  }];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"not_support_beauty_error")];
        }
    } else if (status == VideoChatRoomBottomStatusSet) {
        [self.settingComponent showWithType:VideoChatRoomSettingTypeGuest
                              fromSuperView:self.view
                                  roomModel:self.roomModel];
    } else if (status == VideoChatRoomBottomStatusPK) {
        if (self.userListComponent.isInviteInteractionWaitingReply) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"host_busy")];
            return;
        }

        if (itemButton.status == ButtonStatusActive) {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = LocalizedString(@"ok");
            AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
            cancelModel.title = LocalizedString(@"cancel");
            [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"video_confirm_disconnecting") actions:@[ cancelModel, alertModel ]];

            __weak typeof(self) weakSelf = self;
            alertModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"ok")]) {
                    [weakSelf.pkComponent reqeustStopForwardStream];
                }
            };
            cancelModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"cancel")]) {
                }
            };
        } else {
            if (self.chatRoomMode == VideoChatRoomModeChatRoom) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"host_busy")];
            } else {
                [self.pkUserListComponent showAnchorList];
            }
        }
    }
}

#pragma mark - VideoChatSeatDelegate

- (void)VideoChatSeatComponent:(VideoChatSeatComponent *)VideoChatSeatComponent
                   clickButton:(VideoChatSeatModel *)seatModel
                   sheetStatus:(VideoChatSheetStatus)sheetStatus {
    if (sheetStatus == VideoChatSheetStatusInvite) {
        [self.userListComponent showRoomModel:self.roomModel
                                       seatID:[NSString stringWithFormat:@"%ld", (long)seatModel.index]
                                 dismissBlock:^{

                                 }];
    }
}

#pragma mark - VideoChatRTCManagerDelegate

- (void)videoChatRTCManager:(VideoChatRTCManager *)manager onRoomStateChanged:(RTCJoinModel *)joinModel {
    if ([joinModel.roomId isEqualToString:self.roomModel.roomID]) {
        if (joinModel.joinType != 0 && joinModel.errorCode == 0) {
            [self reconnectVideoChatRoom];
        }
    }
}

- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager reportAllAudioVolume:(NSDictionary<NSString *, NSNumber *> *_Nonnull)volumeInfo {
    if (volumeInfo.count > 0) {
        [self.seatComponent updateSeatVolume:volumeInfo];
    }
}

- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager
      onFirstRemoteVideoUid:(NSString *)uid {
    if (self.chatRoomMode == VideoChatRoomModeMakeCoHost) {
        [self.pkComponent updateRenderView:uid];
    } else {
        [self.seatComponent updateSeatRender:uid];
    }
}

- (void)videoChatRTCManager:(VideoChatRTCManager *)videoChatRTCManager didChangeNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid {
    dispatch_queue_async_safe(dispatch_get_main_queue(), ^{
        if (self.chatRoomMode == VideoChatRoomModeMakeCoHost) {
            [self.pkComponent updateNetworkQuality:status uid:uid];
        } else {
            [self.seatComponent updateNetworkQuality:status uid:uid];
        }
    });
}

#pragma mark - Private Action

- (void)joinRoom {
    if (IsEmptyStr(self.hostUserModel.uid)) {
        // Audience join the room
        [self loadDataWithJoinRoom];
        self.staticView.roomModel = self.roomModel;
    } else {
        // The streamer joins the room. The anchor enters through the room interface, no need to execute the -loadDataWithJoinRoom method
        [self joinRTCRoomWithData:self.rtcToken
                        roomModel:self.roomModel
                        userModel:self.hostUserModel
                    hostUserModel:self.hostUserModel
                         seatList:[self getDefaultSeatDataList]
                       anchorList:nil];
    }
}

- (void)joinRTCRoomWithData:(NSString *)rtcToken
                  roomModel:(VideoChatRoomModel *)roomModel
                  userModel:(VideoChatUserModel *)userModel
              hostUserModel:(VideoChatUserModel *)hostUserModel
                   seatList:(NSArray<VideoChatSeatModel *> *)seatList
                 anchorList:(NSArray<VideoChatUserModel *> *)anchorList {
    _hostUserModel = hostUserModel;
    _roomModel = roomModel;
    _rtcToken = rtcToken;
    BOOL isHost = (userModel.userRole == VideoChatUserRoleHost) ? YES : NO;
    
    [VideoChatRTCManager shareRtc].delegate = self;
    [[VideoChatRTCManager shareRtc] joinRTCRoomWithToken:rtcToken
                                                  roomID:self.roomModel.roomID
                                                     uid:[LocalUserComponent userModel].uid
                                                userRole:isHost];
    if (isHost) {
        self.settingComponent.mic = userModel.mic == VideoChatUserMicOn;
        self.settingComponent.camera = userModel.camera == VideoChatUserCameraOn;
        [[VideoChatRTCManager shareRtc] makeGuest:self.settingComponent.camera
                                       microphone:self.settingComponent.mic];
    }
    self.staticView.roomModel = self.roomModel;
    [self.bottomView updateBottomLists:userModel isPKing:anchorList.count >= 2];
    if (roomModel.roomStatus == VideoChatRoomStatusMakeGuest) {
        self.chatRoomMode = VideoChatRoomModeChatRoom;
    } else {
        self.chatRoomMode = VideoChatRoomModeMakeCoHost;
    }
    self.pkComponent.hostModel = hostUserModel;
    if (self.chatRoomMode == VideoChatRoomModeMakeCoHost) {
        // CoHost mode
        // Update seat component data
        self.seatComponent.loginUserModel = userModel;
        self.seatComponent.hostUserModel = hostUserModel;
        // Update make cohost component data
        [self.pkComponent updateRenderView:hostUserModel.uid];
        [self.pkComponent updateInformationOtherHost:anchorList
                                      currentHostUid:hostUserModel.uid];
    } else {
        // Chat mode
        [self.seatComponent showSeatView:seatList
                          loginUserModel:userModel
                           hostUserModel:hostUserModel];
    }
}

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.bgImageImageView];
    [self.bgImageImageView mas_makeConstraints:^(MASConstraintMaker *make) {
      make.edges.equalTo(self.view);
    }];

    [self pkComponent];
    [self staticView];
    
    [self.view addSubview:self.bottomView];
    [self.bottomView mas_makeConstraints:^(MASConstraintMaker *make) {
      make.height.mas_equalTo([DeviceInforTool getVirtualHomeHeight] + 36 + 32);
      make.left.equalTo(self.view).offset(16);
      make.right.equalTo(self.view).offset(-16);
      make.bottom.equalTo(self.view);
    }];

    [self imComponent];
    [self textInputComponent];
}

- (void)showEndView {
    __weak __typeof(self) wself = self;
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"video_chat_end_live");
    alertModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"video_chat_end_live")]) {
            [wself hangUp:YES];
        }
    };
    AlertActionModel *alertCancelModel = [[AlertActionModel alloc] init];
    alertCancelModel.title = LocalizedString(@"cancel");
    NSString *message = LocalizedString(@"video_chat_end_live_alert");
    [[AlertActionManager shareAlertActionManager] showWithMessage:message actions:@[ alertCancelModel, alertModel ]];
}

- (void)navigationControllerPop {
    UIViewController *jumpVC = nil;
    for (UIViewController *vc in self.navigationController.viewControllers) {
        if ([NSStringFromClass([vc class]) isEqualToString:@"VideoChatRoomListsViewController"]) {
            jumpVC = vc;
            break;
        }
    }
    if (jumpVC) {
        [self.navigationController popToViewController:jumpVC animated:YES];
    } else {
        [self.navigationController popViewControllerAnimated:YES];
    }
}

- (BOOL)isHost {
    return [self.roomModel.hostUid isEqualToString:[LocalUserComponent userModel].uid];
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

- (void)setChatRoomMode:(VideoChatRoomMode)chatRoomMode {
    if (_chatRoomMode == chatRoomMode) {
        return;
    }
    _chatRoomMode = chatRoomMode;
    self.pkComponent.hostModel = self.hostUserModel;
    self.seatComponent.hostUserModel = self.hostUserModel;
    [self.pkComponent changeChatRoomMode:chatRoomMode];
    [self.seatComponent changeChatRoomMode:chatRoomMode];
    [self.userListComponent updateCloseChatRoom:chatRoomMode == VideoChatRoomModeMakeCoHost];
    self.bottomView.chatRoomMode = chatRoomMode;

    if (chatRoomMode == VideoChatRoomModeChatRoom && [self isHost]) {
        [self.userListComponent changeChatRoomModeDismissUserListView];
    } else {
        if (![self isHost]) {
            [self.bottomView audienceResetBottomLists];
            self.seatComponent.loginUserModel.status = VideoChatUserStatusDefault;
        }
    }
}

- (void)addIMMessage:(BOOL)isJoin
           userModel:(VideoChatUserModel *)userModel {
    NSString *unitStr = isJoin ? LocalizedString(@"video_chat_join_room") : LocalizedString(@"video_chat_left_room");
    BaseIMModel *imModel = [[BaseIMModel alloc] init];
    imModel.message = [NSString stringWithFormat:@"%@ %@", userModel.name, unitStr];
    [self.imComponent addIM:imModel];
}

- (void)reconnectVideoChatRoom {
    [VideoChatRTSManager reconnectWithBlock:^(NSString * _Nonnull RTCToken,
                                              VideoChatRoomModel * _Nonnull roomModel,
                                              VideoChatUserModel * _Nonnull userModel,
                                              VideoChatUserModel * _Nonnull hostUserModel,
                                              NSArray<VideoChatSeatModel *> * _Nonnull seatList,
                                              NSArray<VideoChatUserModel *> * _Nonnull anchorList,
                                              NSArray<VideoChatUserModel *> * _Nonnull anchorInteractList,
                                              RTSACKModel * _Nonnull model) {
        
        if (model.result) {
            [self joinRTCRoomWithData:RTCToken
                            roomModel:roomModel
                            userModel:userModel
                        hostUserModel:hostUserModel
                             seatList:seatList
                           anchorList:anchorList];
            
            if ([self isHost] && anchorInteractList.count > 0) {
                for (VideoChatUserModel *anchorModel in anchorInteractList) {
                    if (![anchorModel.uid isEqualToString:self.hostUserModel.uid]) {
                        [self.pkUserListComponent startForwardStream:anchorModel.roomID token:anchorModel.pkToken];
                        break;
                    }
                    
                }
            }
            
            for (VideoChatSeatModel *seatModel in seatList) {
                if ([seatModel.userModel.uid isEqualToString:userModel.uid]) {
                    // Reconnect after disconnection, I need to turn on the microphone to collect
                    self.settingComponent.mic = userModel.mic == VideoChatUserMicOn;
                    self.settingComponent.camera = userModel.camera == VideoChatUserCameraOn;
                    [[VideoChatRTCManager shareRtc] makeGuest:self.settingComponent.camera
                                                         microphone:self.settingComponent.mic];
                    
                    break;
                }
            }
        } else if (model.code == RTSStatusCodeUserIsInactive ||
                   model.code == RTSStatusCodeRoomDisbanded ||
                   model.code == RTSStatusCodeUserNotFound) {
            [self hangUp:NO];
            [[ToastComponent shareToastComponent] showWithMessage:model.message delay:0.8];
        }
    }];
}

- (void)dismissAnchorInvite {
    [[AlertActionManager shareAlertActionManager] dismiss:^{

    }];
}

#pragma mark - Getter

- (VideoChatTextInputComponent *)textInputComponent {
    if (!_textInputComponent) {
        _textInputComponent = [[VideoChatTextInputComponent alloc] init];
    }
    return _textInputComponent;
}

- (VideoChatStaticView *)staticView {
    if (!_staticView) {
        _staticView = [[VideoChatStaticView alloc] initWithSuperView:self.view];
        __weak typeof(self) weakSelf = self;
        _staticView.quitLiveBlock = ^{
            if ([weakSelf isHost]) {
                [weakSelf showEndView];
            } else {
                [weakSelf hangUp:YES];
            }
        };
    }
    return _staticView;
}

- (VideoChatSeatComponent *)seatComponent {
    if (!_seatComponent) {
        _seatComponent = [[VideoChatSeatComponent alloc] initWithSuperView:self.view];
        _seatComponent.delegate = self;
    }
    return _seatComponent;
}

- (VideoChatRoomBottomView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[VideoChatRoomBottomView alloc] init];
        _bottomView.delegate = self;
    }
    return _bottomView;
}

- (VideoChatRoomUserListComponent *)userListComponent {
    if (!_userListComponent) {
        _userListComponent = [[VideoChatRoomUserListComponent alloc] init];
    }
    return _userListComponent;
}

- (BaseIMComponent *)imComponent {
    if (!_imComponent) {
        _imComponent = [[BaseIMComponent alloc] initWithSuperView:self.view];
    }
    return _imComponent;
}

- (VideoChatMusicComponent *)musicComponent {
    if (!_musicComponent) {
        _musicComponent = [[VideoChatMusicComponent alloc] init];
    }
    return _musicComponent;
}

- (BytedEffectProtocol *)beautyComponent {
    if (!_beautyComponent) {
        _beautyComponent = [[BytedEffectProtocol alloc] initWithRTCEngineKit:[VideoChatRTCManager shareRtc].rtcEngineKit];
    }
    return _beautyComponent;
}

- (VideoChatRoomSettingComponent *)settingComponent {
    if (!_settingComponent) {
        _settingComponent = [[VideoChatRoomSettingComponent alloc] initWithHost:[self isHost]];
        __weak typeof(self) weakSelf = self;
        _settingComponent.clickMusicBlock = ^{
            [weakSelf.musicComponent show];
        };
    }
    return _settingComponent;
}

- (VideoChatPKUserListComponent *)pkUserListComponent {
    if (!_pkUserListComponent) {
        _pkUserListComponent = [[VideoChatPKUserListComponent alloc] initWithRoomModel:self.roomModel];
    }
    return _pkUserListComponent;
}

- (VideoChatPKComponent *)pkComponent {
    if (!_pkComponent) {
        _pkComponent = [[VideoChatPKComponent alloc] initWithSuperView:self.view roomModel:self.roomModel];
    }
    return _pkComponent;
}

- (UIImageView *)bgImageImageView {
    if (!_bgImageImageView) {
        NSString *bgImageName = @"videochat_room";
        _bgImageImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:bgImageName bundleName:HomeBundleName]];
        _bgImageImageView.contentMode = UIViewContentModeScaleAspectFill;
        _bgImageImageView.clipsToBounds = YES;
    }
    return _bgImageImageView;
}

- (void)dealloc {
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [[AlertActionManager shareAlertActionManager] dismiss:^{

    }];
}

@end
