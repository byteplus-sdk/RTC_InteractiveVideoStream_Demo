/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomViewController.h"
#import "VideoChatRoomViewController+SocketControl.h"
#import "VideoChatStaticView.h"
#import "VideoChatRoomBottomView.h"
#import "VideoChatPeopleNumView.h"
#import "VideoChatSeatComponent.h"
#import "VideoChatMusicComponent.h"
#import "VideoChatTextInputComponent.h"
#import "VideoChatRoomUserListComponent.h"
#import "VideoChatIMComponent.h"
#import "VideoChatRoomSettingComponent.h"
#import "BytedEffectProtocol.h"
#import "VideoChatPKUserListComponents.h"
#import "VideoChatPKComponents.h"
#import "NetworkingTool.h"

@interface VideoChatRoomViewController ()
<
VideoChatRoomBottomViewDelegate,
VideoChatRTCManagerDelegate,
VideoChatSeatDelegate
>

@property (nonatomic, strong) UIImageView *bgImageImageView;
@property (nonatomic, strong) VideoChatStaticView *staticView;
@property (nonatomic, strong) VideoChatRoomBottomView *bottomView;
@property (nonatomic, strong) VideoChatMusicComponent *musicComponent;
@property (nonatomic, strong) VideoChatTextInputComponent *textInputComponent;
@property (nonatomic, strong) VideoChatRoomUserListComponent *userListComponent;
@property (nonatomic, strong) VideoChatRoomSettingComponent *settingComponent;
@property (nonatomic, strong) BytedEffectProtocol *beautyComponent;
@property (nonatomic, strong) VideoChatIMComponent *imComponent;
@property (nonatomic, strong) VideoChatSeatComponent *seatComponent;
@property (nonatomic, strong) VideoChatPKUserListComponents *pkUserListComponents;
@property (nonatomic, strong) VideoChatPKComponents *pkComponents;
@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, strong) VideoChatUserModel *hostUserModel;
@property (nonatomic, copy) NSString *rtcToken;

@property (nonatomic, assign) VideoChatRoomMode chatRoomMode;

@end

@implementation VideoChatRoomViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel {
    self = [super init];
    if (self) {
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
    
    [self.beautyComponent resumeLocalEffect];
    
    __weak typeof(self) weakSelf = self;
    [VideoChatRTCManager shareRtc].rtcJoinRoomBlock = ^(NSString * _Nonnull roomId, NSInteger errorCode, NSInteger joinType) {
        [weakSelf receivedJoinRoom:roomId errorCode:errorCode joinType:joinType];
    };
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

- (void)receivedJoinRoom:(NSString *)roomId
               errorCode:(NSInteger)errorCode
                joinType:(NSInteger)joinType {
    if ([roomId isEqualToString:self.roomModel.roomID]) {
        if (errorCode == 0) {

        }
        if (joinType != 0 && errorCode == 0) {
            [self reconnectVideoChatRoom];
        }
        return;
    }
}

- (void)reconnectVideoChatRoom {
    [VideoChatRTMManager reconnectWithBlock:^(NSString * _Nonnull RTCToken,
                                              VideoChatRoomModel * _Nonnull roomModel,
                                              VideoChatUserModel * _Nonnull userModel,
                                              VideoChatUserModel * _Nonnull hostUserModel,
                                              NSArray<VideoChatSeatModel *> * _Nonnull seatList,
                                              NSArray<VideoChatUserModel *> * _Nonnull anchorList,
                                              NSArray<VideoChatUserModel *> * _Nonnull anchorInteractList,
                                              RTMACKModel * _Nonnull model) {
        
        if (model.result) {
            [self updateRoomViewWithData:RTCToken
                               roomModel:roomModel
                               userModel:userModel
                           hostUserModel:hostUserModel
                                seatList:seatList
                              anchorList:anchorList];
            
            if ([self isHost] && anchorInteractList.count > 0) {
                for (VideoChatUserModel *anchorModel in anchorInteractList) {
                    if (![anchorModel.uid isEqualToString:self.hostUserModel.uid]) {
                        [self.pkUserListComponents startForwardStream:anchorModel.roomID token:anchorModel.pkToken];
                        break;
                    }
                    
                }
            }
            
            for (VideoChatSeatModel *seatModel in seatList) {
                if ([seatModel.userModel.uid isEqualToString:userModel.uid]) {
                    // Reconnect after disconnection, I need to turn on the microphone to collect
                    self.settingComponent.mic = userModel.mic == VideoChatUserMicOn;
                    self.settingComponent.camera = userModel.camera == VideoChatUserCameraOn;
                    [[VideoChatRTCManager shareRtc] enableLocalAudio:self.settingComponent.mic];
                    [[VideoChatRTCManager shareRtc] enableLocalVideo:self.settingComponent.camera];
                    [[VideoChatRTCManager shareRtc] setUserVisibility:YES];
                    
                    break;
                }
            }
        } else if (model.code == RTMStatusCodeUserIsInactive ||
                   model.code == RTMStatusCodeRoomDisbanded ||
                   model.code == RTMStatusCodeUserNotFound) {
            [self hangUp:NO];
        }
    }];
}

- (void)clearRedNotification {
    [self.bottomView updateButtonStatus:VideoChatRoomBottomStatusPhone isRed:NO];
    [self.userListComponent updateWithRed:NO];
}

#pragma mark - SocketControl


- (void)receivedJoinUser:(VideoChatUserModel *)userModel
                   count:(NSInteger)count {
    VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
    model.userModel = userModel;
    model.isJoin = YES;
    [self.imComponent addIM:model];
    [self.staticView updatePeopleNum:count];
    [self.userListComponent update];
}

- (void)receivedLeaveUser:(VideoChatUserModel *)userModel
                    count:(NSInteger)count {
    VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
    model.userModel = userModel;
    model.isJoin = NO;
    [self.imComponent addIM:model];
    [self.staticView updatePeopleNum:count];
    [self.userListComponent update];
}

- (void)receivedFinishLive:(NSInteger)type roomID:(NSString *)roomID {
    if (![roomID isEqualToString:self.roomModel.roomID]) {
        return;
    }
    [self hangUp:NO];
    if (type == 3) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Room has been closed due to violations of Terms of Service.") delay:0.8];
    }
    else if (type == 2 && [self isHost]) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"The duration of this LIVE has reached 10 minutes.") delay:0.8];
    } else {
        if (![self isHost]) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"LIVE has ended") delay:0.8];
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
        [self.bottomView updateBottomLists:userModel];

        self.settingComponent.mic = (userModel.mic == VideoChatUserMicOn);
        self.settingComponent.camera = (userModel.camera == VideoChatUserCameraOn);
        // RTC Start Audio Capture
        [[VideoChatRTCManager shareRtc] setUserVisibility:YES];
        [[VideoChatRTCManager shareRtc] enableLocalAudio:self.settingComponent.mic];
        [[VideoChatRTCManager shareRtc] enableLocalVideo:self.settingComponent.camera];
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been a guest\0")];
    }
    
    //IM
    VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
    NSString *message = [NSString stringWithFormat:LocalizedString(@"%@ becomes a guest"),userModel.name];
    model.message = message;
    [self.imComponent addIM:model];
}

- (void)receivedLeaveInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID
                                 type:(NSInteger)type {
    [self.seatComponent removeUserModel:userModel];
    [self.userListComponent update];
    if ([userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        [self.bottomView updateBottomLists:userModel];
        // RTC Stop Audio Capture
        [[VideoChatRTCManager shareRtc] setUserVisibility:NO];
        [[VideoChatRTCManager shareRtc] enableLocalAudio:NO];
        [[VideoChatRTCManager shareRtc] enableLocalVideo:NO];
        [[VideoChatRTCManager shareRtc] updateCameraID:YES];
        if (type == 1) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been removed from guest.")];
        } else if (type == 2) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been an audience")];
        }
    }
    
    //IM
    VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
    NSString *message = [NSString stringWithFormat:LocalizedString(@"%@ becomes an audience"),userModel.name];
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
    
    if (self.chatRoomMode == VideoChatRoomModePK) {
        [self.pkComponents updateUserModel:userModel];
        if ([userModel.uid isEqualToString:self.hostUserModel.uid]) {
            self.seatComponent.hostUserModel = userModel;
        }
    }
    else {
        VideoChatSeatModel *seatModel = [[VideoChatSeatModel alloc] init];
        seatModel.status = 1;
        seatModel.userModel = userModel;
        seatModel.index = seatID.integerValue;
        [self.seatComponent updateSeatModel:seatModel];
    }
    
    
    if ([userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        // RTC Mute/Unmute Audio Capture
        [[VideoChatRTCManager shareRtc] muteLocalAudio:userModel.mic == VideoChatUserMicOff];
        [[VideoChatRTCManager shareRtc] muteLocalVideo:userModel.camera == VideoChatUserCameraOff];
        [self.settingComponent updateUserMic:userModel.mic == VideoChatUserMicOn];
        
    }
}

- (void)receivedMessageWithUser:(VideoChatUserModel *)userModel
                        message:(NSString *)message {
    if (![userModel.uid isEqualToString:[LocalUserComponent userModel].uid]) {
        VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
        NSString *imMessage = [NSString stringWithFormat:@"%@：%@",
                               userModel.name,
                               message];
        model.userModel = userModel;
        model.message = imMessage;
        [self.imComponent addIM:model];
    }
}

- (void)receivedInviteInteractWithUser:(VideoChatUserModel *)hostUserModel
                                seatID:(NSString *)seatID {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = LocalizedString(@"Accept");
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = LocalizedString(@"Decline");
    [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"Host is inviting you to go LIVE together") actions:@[cancelModel, alertModel]];
    
    __weak __typeof(self) wself = self;
    alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"Accept")]) {
            [wself loadDataWithReplyInvite:1];
        }
    };
    cancelModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"Decline")]) {
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
        NSString *message = [NSString stringWithFormat:LocalizedString(@"%@ declines your invitation"), hostUserModel.name];
        [[ToastComponent shareToastComponent] showWithMessage:message];
    }
    
    if ([self isHost]) {
        [self.userListComponent resetInviteInteractionWaitingReplyStstus];
    }
}

- (void)receivedMediaOperatWithUid:(NSInteger)mic camera:(NSInteger)camera {
    [VideoChatRTMManager updateMediaStatus:self.roomModel.roomID
                                              mic:mic
                                           camera:camera
                                            block:^(RTMACKModel * _Nonnull model) {
        
    }];
    if (mic) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been unmuted")];
    } else {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"You have been muted")];
    }
}

- (void)receivedClearUserWithUid:(NSString *)uid {
    [self hangUp:NO];
    [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"A user with the same ID has logged in. You will be forced to log out.") delay:0.8];
}

- (void)hangUp:(BOOL)isServer {
    if (isServer) {
        // socket api
        if ([self isHost]) {
            [VideoChatRTMManager finishLive:self.roomModel.roomID];
        } else {
            [VideoChatRTMManager leaveLiveRoom:self.roomModel.roomID];
        }
    }
    // sdk api
    [[VideoChatRTCManager shareRtc] leaveChannel];
    // ui
    [self navigationControllerPop];
}

- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel {
    [self.pkUserListComponents receivedAnchorPKInvite:anchorModel];
}

- (void)receivedAnchorPKReply:(VideoChatPKReply)reply
                       roomID:(NSString *)roomID
                        token:(NSString *)token
                  anchorModel:(VideoChatUserModel *)anchorModel {
    [self.pkUserListComponents resetPkWaitingReplyStstus];
    
    if (reply == VideoChatPKReplyAccept) {
        [self.pkUserListComponents startForwardStream:roomID token:token];
    }
    else {
        [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"%@ declined your invitation"), anchorModel.name]];
    }
}

- (void)receivedAnchorPKNewAnchorJoined:(VideoChatUserModel *)anchorModel {
    self.chatRoomMode = VideoChatRoomModePK;
    self.pkComponents.anchorModel = anchorModel;
    [self.bottomView updateBottomListsWithPK:YES];
}

- (void)receivedAnchorPKEnd {
    if ([self isHost]) {
        if (self.pkComponents.activeEndPK) {
            [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"You have disconnected with %@"), self.pkComponents.anchorModel.name]];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:[NSString stringWithFormat:LocalizedString(@"%@ has left"), self.pkComponents.anchorModel.name]];
        }
        [self.pkComponents rtcStopForwardStream];
        self.pkComponents.activeEndPK = NO;
    }
    self.pkComponents.anchorModel = nil;
    [self.bottomView updateBottomListsWithPK:NO];
}

- (void)receiverCloseChatRoomMode {
    self.chatRoomMode = VideoChatRoomModePK;
}

- (void)receivedMuteOtherAnchorRoomID:(NSString *)roomID otherAnchorUserID:(NSString *)otherAnchorUserID type:(VideoChatOtherAnchorMicType)type {
    [self.pkComponents muteOtherAnchorRoomID:roomID otherAnchorUserID:otherAnchorUserID type:type];
}

#pragma mark - Load Data

- (void)loadDataWithJoinRoom {
    [[VideoChatRTCManager shareRtc] setDefaultVideoEncoderConfig];
    
    __weak __typeof(self) wself = self;
    [VideoChatRTMManager joinLiveRoom:self.roomModel.roomID
                             userName:[LocalUserComponent userModel].name
                                block:^(NSString * _Nonnull RTCToken, VideoChatRoomModel * _Nonnull roomModel, VideoChatUserModel * _Nonnull userModel, VideoChatUserModel * _Nonnull hostUserModel,
                                        NSArray<VideoChatSeatModel *> * _Nonnull seatList,
                                            NSArray<VideoChatUserModel *> * _Nonnull anchorList,
                                            RTMACKModel * _Nonnull model) {
        if (NOEmptyStr(roomModel.roomID)) {
            [wself updateRoomViewWithData:RTCToken
                                roomModel:roomModel
                                userModel:userModel
                            hostUserModel:hostUserModel
                                 seatList:seatList
                               anchorList:anchorList];
        } else {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = LocalizedString(@"OK");
            alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"OK")]) {
                    [wself hangUp:NO];
                }
            };
            [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"Joining the room failed. You will be taken to the list page.") actions:@[alertModel]];
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
        self.textInputComponent.clickSenderBlock = ^(NSString * _Nonnull text) {
            VideoChatIMModel *model = [[VideoChatIMModel alloc] init];
            NSString *message = [NSString stringWithFormat:@"%@：%@",
                                 [LocalUserComponent userModel].name,
                                 text];
            model.message = message;
            [wself.imComponent addIM:model];
        };
    } else if (status == VideoChatRoomBottomStatusPhone) {
        if (self.pkUserListComponents.isPKWaitingReply) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"The Invited is busy")];
            return;
        }
        if ([self isHost]) {
            if (self.pkComponents.anchorModel) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"A host is in your room. Failed to add a guest")];
            }
            else {
                [self.userListComponent showRoomModel:self.roomModel
                                                seatID:@"-1"
                                          dismissBlock:^{
                    
                }];
            }
        }
        else {
            [self.seatComponent audienceApplyInteraction];
        }
        
    } else if (status == VideoChatRoomBottomStatusBeauty) {
        if (self.beautyComponent) {
            [self.beautyComponent showWithType:EffectBeautyRoleTypeHost
                                  fromSuperView:self.view
                                   dismissBlock:^(BOOL result) {
                
            }];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:@"This open-source project doesn't support Effects-related function. Please download BytePlus demo to experience it."];
        }
    } else if (status == VideoChatRoomBottomStatusSet) {
        [self.settingComponent showWithType:VideoChatRoomSettingTypeGuest
                               fromSuperView:self.view
                                   roomModel:self.roomModel];
    }
    else if (status == VideoChatRoomBottomStatusPK) {
        
        if (self.userListComponent.isInviteInteractionWaitingReply) {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"The Invited is busy")];
            return;
        }
        
        if (itemButton.status == ButtonStatusActive) {
            
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = LocalizedString(@"Confirm");
            AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
            cancelModel.title = LocalizedString(@"Cancel");
            [[AlertActionManager shareAlertActionManager] showWithMessage:LocalizedString(@"Confirm disconnecting?") actions:@[cancelModel, alertModel]];
            
            __weak typeof(self) weakSelf = self;
            alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"Confirm")]) {
                    [weakSelf.pkComponents reqeustStopForwardStream];
                }
            };
            cancelModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:LocalizedString(@"Cancel")]) {
                }
            };
        }
        else {
            if (self.chatRoomMode == VideoChatRoomModeChatRoom) {
                [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"The Invited is busy")];
            } else {
                [self.pkUserListComponents showAnchorList];
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

- (void)videoChatRTCManager:(VideoChatRTCManager * _Nonnull)videoChatRTCManager reportAllAudioVolume:(NSDictionary<NSString *,NSNumber *> * _Nonnull)volumeInfo {
    if (volumeInfo.count > 0) {
        [self.seatComponent updateSeatVolume:volumeInfo];
    }
}

- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager onFirstRemoteVideoUid:(NSString *)uid {
    if (self.chatRoomMode == VideoChatRoomModePK) {
        [self.pkComponents updateRenderView:uid];
    }
    else {
        [self.seatComponent updateSeatRender:uid];
    }
}

#pragma mark - Network request

- (void)loadDataWithReplyInvite:(NSInteger)type {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismissAnchorInvite) object:nil];
    [VideoChatRTMManager replyInvite:self.roomModel.roomID
                               reply:type
                               block:^(RTMACKModel * _Nonnull model) {
        if (!model.result) {
            [[ToastComponent shareToastComponent] showWithMessage:model.message];
        }
    }];
}

- (void)dismissAnchorInvite {
    [[AlertActionManager shareAlertActionManager] dismiss:^{
        
    }];
}

#pragma mark - Private Action

- (void)joinRoom {
    if (IsEmptyStr(self.hostUserModel.uid)) {
        [self loadDataWithJoinRoom];
        self.staticView.roomModel = self.roomModel;
    } else {
        [self updateRoomViewWithData:self.rtcToken
                           roomModel:self.roomModel
                           userModel:self.hostUserModel
                       hostUserModel:self.hostUserModel
                            seatList:[self getDefaultSeatDataList]
                          anchorList:nil];
    }
}

- (void)updateRoomViewWithData:(NSString *)rtcToken
                     roomModel:(VideoChatRoomModel *)roomModel
                     userModel:(VideoChatUserModel *)userModel
                 hostUserModel:(VideoChatUserModel *)hostUserModel
                      seatList:(NSArray<VideoChatSeatModel *> *)seatList
                    anchorList:(NSArray<VideoChatUserModel *> *)anchorList {
    _hostUserModel = hostUserModel;
    _roomModel = roomModel;
    _rtcToken = rtcToken;
    //Activate SDK
    [[VideoChatRTCManager shareRtc] setUserVisibility:userModel.userRole == VideoChatUserRoleHost];
    [VideoChatRTCManager shareRtc].delegate = self;
    [[VideoChatRTCManager shareRtc] joinChannelWithToken:rtcToken
                                                  roomID:self.roomModel.roomID
                                                     uid:[LocalUserComponent userModel].uid];
    if (userModel.userRole == VideoChatUserRoleHost) {
        
        self.settingComponent.mic = userModel.mic == VideoChatUserMicOn;
        self.settingComponent.camera = userModel.camera == VideoChatUserCameraOn;
        
        [[VideoChatRTCManager shareRtc] setUserVisibility:YES];
        [[VideoChatRTCManager shareRtc] enableLocalAudio:self.settingComponent.mic];
        [[VideoChatRTCManager shareRtc] enableLocalVideo:self.settingComponent.camera];
    }
    self.staticView.roomModel = self.roomModel;
    [self.bottomView updateBottomLists:userModel isPKing:anchorList.count >= 2];
    
    if (roomModel.roomStatus == VideoChatRoomStatusLianmai) {
        self.chatRoomMode = VideoChatRoomModeChatRoom;
    } else {
        self.chatRoomMode = VideoChatRoomModePK;
    }
    
    self.pkComponents.hostModel = hostUserModel;
    if (self.chatRoomMode == VideoChatRoomModePK) {
        self.seatComponent.loginUserModel = userModel;
        self.seatComponent.hostUserModel = hostUserModel;
        [self.pkComponents updateRenderView:hostUserModel.uid];
        BOOL hasOtherAnchor = NO;
        for (VideoChatUserModel *anchorModel in anchorList) {
            if (![anchorModel.uid isEqualToString:self.hostUserModel.uid]) {
                self.pkComponents.anchorModel = anchorModel;
                [self.pkComponents muteOtherAnchorRoomID:anchorModel.roomID
                                       otherAnchorUserID:anchorModel.uid
                                                    type:anchorModel.otherAnchorMicType];
                hasOtherAnchor = YES;
                break;
            }
        }
        if (!hasOtherAnchor) {
            self.pkComponents.anchorModel = nil;
        }
    }
    else {
        [self.seatComponent showSeatView:seatList
                           loginUserModel:userModel
                            hostUserModel:hostUserModel];
    }
    
    __weak __typeof(self) weakSelf = self;
    [[VideoChatRTCManager shareRtc] didChangeNetworkQuality:^(VideoChatNetworkQualityStatus status, NSString * _Nonnull uid) {
        dispatch_queue_async_safe(dispatch_get_main_queue(), ^{
            if (weakSelf.chatRoomMode == VideoChatRoomModePK) {
                [weakSelf.pkComponents updateNetworkQuality:status uid:uid];
            } else {
                [weakSelf.seatComponent updateNetworkQuality:status uid:uid];
            }
        });
    }];
}

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.bgImageImageView];
    [self.bgImageImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self pkComponents];
    [self staticView];
//    [self.view addSubview:self.staticView];
//    [self.staticView mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.edges.equalTo(self.view);
//    }];
    
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
    alertModel.title = LocalizedString(@"End LIVE");
    alertModel.alertModelClickBlock = ^(UIAlertAction *_Nonnull action) {
        if ([action.title isEqualToString:LocalizedString(@"End LIVE")]) {
            [wself hangUp:YES];
        }
    };
    AlertActionModel *alertCancelModel = [[AlertActionModel alloc] init];
    alertCancelModel.title = LocalizedString(@"Cancel");
    NSString *message = LocalizedString(@"Are you sure end this LIVE?");
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
    self.pkComponents.hostModel = self.hostUserModel;
    self.seatComponent.hostUserModel = self.hostUserModel;
    [self.pkComponents changeChatRoomMode:chatRoomMode];
    [self.seatComponent changeChatRoomMode:chatRoomMode];
    [self.userListComponent updateCloseChatRoom:chatRoomMode == VideoChatRoomModePK];
    self.bottomView.chatRoomMode = chatRoomMode;
    
    if (chatRoomMode == VideoChatRoomModeChatRoom && [self isHost]) {
        [self.userListComponent changeChatRoomModeDismissUserListView];
    }
    else {
        if (![self isHost]) {
            [self.bottomView audienceResetBottomLists];
            self.seatComponent.loginUserModel.status = VideoChatUserStatusDefault;
        }
    }
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

- (VideoChatIMComponent *)imComponent {
    if (!_imComponent) {
        _imComponent = [[VideoChatIMComponent alloc] initWithSuperView:self.view];
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

- (VideoChatPKUserListComponents *)pkUserListComponents {
    if (!_pkUserListComponents) {
        _pkUserListComponents = [[VideoChatPKUserListComponents alloc] initWithRoomModel:self.roomModel];
    }
    return _pkUserListComponents;
}

- (VideoChatPKComponents *)pkComponents {
    if (!_pkComponents) {
        _pkComponents = [[VideoChatPKComponents alloc] initWithSuperView:self.view roomModel:self.roomModel];
    }
    return _pkComponents;
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
