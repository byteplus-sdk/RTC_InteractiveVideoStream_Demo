//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatRTSManager.h"
#import "JoinRTSParams.h"

@implementation VideoChatRTSManager

#pragma mark - Get Video data

+ (void)createRoom:(NSString *)roomName
          userName:(NSString *)userName
       bgImageName:(NSString *)bgImageName
             block:(void (^)(NSString *RTCToken,
                             VideoChatRoomModel *roomModel,
                             VideoChatUserModel *hostUserModel,
                             RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_name": roomName ?: @"",
                          @"background_image_name": @"bgImageName",
                          @"user_name": userName ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viCreateRoom" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSString *RTCToken = @"";
        VideoChatRoomModel *roomModel = nil;
        VideoChatUserModel *hostUserModel = nil;
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            roomModel = [VideoChatRoomModel yy_modelWithJSON:ackModel.response[@"room_info"]];
            hostUserModel = [VideoChatUserModel yy_modelWithJSON:ackModel.response[@"user_info"]];
            RTCToken = [NSString stringWithFormat:@"%@", ackModel.response[@"rtc_token"]];
        }
        if (block) {
            block(RTCToken, roomModel, hostUserModel, ackModel);
        }
        NSLog(@"[%@]-viCreateRoom %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)startLive:(NSString *)roomID
            block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viStartLive" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viStartLive %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)getAudienceList:(NSString *)roomID
                  block:(void (^)(NSArray<VideoChatUserModel *> *userLists,
                                  RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viGetAudienceList" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSMutableArray<VideoChatUserModel *> *userLists = [[NSMutableArray alloc] init];
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            NSArray *list = ackModel.response[@"audience_list"];
            for (int i = 0; i < list.count; i++) {
                VideoChatUserModel *userModel = [VideoChatUserModel yy_modelWithJSON:list[i]];
                [userLists addObject:userModel];
            }
        }
        if (block) {
            block([userLists copy], ackModel);
        }
        NSLog(@"[%@]-viGetAudienceList %@ | %@", [self class], dic, ackModel.response);
    }];
}

+ (void)getApplyAudienceList:(NSString *)roomID
                       block:(void (^)(NSArray<VideoChatUserModel *> *userLists,
                                       RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viGetApplyAudienceList" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSMutableArray<VideoChatUserModel *> *userLists = [[NSMutableArray alloc] init];
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            NSArray *list = ackModel.response[@"audience_list"];
            for (int i = 0; i < list.count; i++) {
                VideoChatUserModel *userModel = [VideoChatUserModel yy_modelWithJSON:list[i]];
                [userLists addObject:userModel];
            }
        }
        if (block) {
            block([userLists copy], ackModel);
        }
        NSLog(@"[%@]-viGetApplyAudienceList %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)inviteInteract:(NSString *)roomID
                   uid:(NSString *)uid
                seatID:(NSString *)seatID
                 block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"audience_user_id": uid ?: @"",
                          @"seat_id": @(seatID.integerValue)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viInviteInteract" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viInviteInteract %@ | %@", [self class], dic, ackModel.response);
    }];
}

+ (void)agreeApply:(NSString *)roomID
               uid:(NSString *)uid
             block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"audience_user_id": uid ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viAgreeApply" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viAgreeApply %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)managerInteractApply:(NSString *)roomID
                        type:(NSInteger)type
                       block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"type": @(type)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viManageInteractApply" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viManagerInteractApply %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)managerSeat:(NSString *)roomID
             seatID:(NSString *)seatID
               type:(NSInteger)type
              block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"seat_id": @(seatID.integerValue),
                          @"type": @(type)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viManageSeat" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viManageSeat %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)finishLive:(NSString *)roomID {
    if (IsEmptyStr(roomID)) {
        return;
    }
    NSDictionary *dic = @{@"room_id": roomID ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viFinishLive" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSLog(@"[%@]-viFinishLive %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)requestPKUserListComplete:(void (^)(NSArray<VideoChatUserModel *> *userList, RTSACKModel *model))complete {
    NSDictionary *dic = @{};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viGetAnchorList" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSMutableArray<VideoChatUserModel *> *userLists = [[NSMutableArray alloc] init];
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            NSArray *list = ackModel.response[@"anchor_list"];
            for (int i = 0; i < list.count; i++) {
                VideoChatUserModel *userModel = [VideoChatUserModel yy_modelWithJSON:list[i]];
                [userLists addObject:userModel];
            }
        }
        if (complete) {
            complete([userLists copy], ackModel);
        }
        NSLog(@"[%@]-viGetAnchorList %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)requestInviteAnchorWithFromRoomID:(NSString *)fromRoomID
                               fromUserID:(NSString *)fromUserID
                                 toRoomID:(NSString *)toRoomID
                                 toUserID:(NSString *)toUserID
                                   seatID:(NSInteger)seatID
                                 complete:(void (^)(RTSACKModel *_Nonnull))complete {
    NSDictionary *dic = @{
        @"inviter_room_id": fromRoomID ?: @"",
        @"inviter_user_id": fromUserID ?: @"",
        @"invitee_room_id": toRoomID ?: @"",
        @"invitee_user_id": toUserID ?: @"",
        @"seat_id": @(seatID),
    };
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viInviteAnchor" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (complete) {
            complete(ackModel);
        }
        NSLog(@"[%@]-viInviteAnchor %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)replyInviteWithInviterRoomID:(NSString *)inviterRoomID
                       inviterUserID:(NSString *)inviterUserID
                              roomID:(NSString *)roomID
                              userID:(NSString *)userID
                               reply:(VideoChatPKReply)reply
                            complete:(void (^)(NSString *roomID, NSString *token, RTSACKModel *model))complete {
    NSDictionary *dic = @{
        @"inviter_room_id": inviterRoomID ?: @"",
        @"inviter_user_id": inviterUserID ?: @"",
        @"invitee_room_id": roomID ?: @"",
        @"invitee_user_id": userID ?: @"",
        @"reply": @(reply),
    };
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viReplyAnchor" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSString *roomID = @"";
        NSString *token = @"";
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            NSArray *list = ackModel.response[@"interact_info_list"];
            if (list.count > 0 && [list.firstObject isKindOfClass:[NSDictionary class]]) {
                NSDictionary *info = list.firstObject;
                roomID = info[@"room_id"];
                token = info[@"token"];
            }
        }
        if (complete) {
            complete(roomID, token, ackModel);
        }
        NSLog(@"[%@]-viReplyAnchor %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)requestStopPKWithRoomID:(NSString *)roomID
                         userID:(NSString *)userID
                       complete:(void (^)(RTSACKModel *model))complete {
    NSDictionary *dic = @{
        @"room_id": roomID ?: @"",
        @"user_id": userID ?: @"",
    };
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viFinishAnchorInteract" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (complete) {
            complete(ackModel);
        }
        NSLog(@"[%@]-viFinishAnchorInteract %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)requestCloseChatRoomMode:(NSString *)roomID
                        complete:(void (^)(RTSACKModel *model))complete {
    NSDictionary *dic = @{
        @"room_id": roomID ?: @"",
    };
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viCloseChatRoom" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (complete) {
            complete(ackModel);
        }
        NSLog(@"[%@]-viCloseChatRoom %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)requestMuteOtherAnchorRoomID:(NSString *)roomID
                   otherAnchorUserID:(NSString *)otherAnchorUserID
                                type:(VideoChatOtherAnchorMicType)type
                            complete:(void (^)(RTSACKModel *model))complete {
    NSDictionary *dic = @{
        @"room_id": roomID ?: @"",
        @"other_anchor_user_id": otherAnchorUserID ?: @"",
        @"type": @(type),
    };
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viManageOtherAnchor" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (complete) {
            complete(ackModel);
        }
        NSLog(@"[%@]-viManageOtherAnchor %@ \n %@", [self class], dic, ackModel.response);
    }];
}

#pragma mark - Audience API

+ (void)joinLiveRoom:(NSString *)roomID
            userName:(NSString *)userName
               block:(void (^)(NSString *RTCToken,
                               VideoChatRoomModel *roomModel,
                               VideoChatUserModel *userModel,
                               VideoChatUserModel *hostUserModel,
                               NSArray<VideoChatSeatModel *> *seatList,
                               NSArray<VideoChatUserModel *> *anchorList,
                               RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"user_name": userName ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viJoinLiveRoom" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSString *RTCToken = @"";
        VideoChatRoomModel *roomModel = nil;
        VideoChatUserModel *hostUserModel = nil;
        VideoChatUserModel *userModel = nil;
        NSArray<VideoChatUserModel *> *anchorList = nil;
        NSMutableArray<VideoChatSeatModel *> *seatList = [[NSMutableArray alloc] init];
        ;
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            roomModel = [VideoChatRoomModel yy_modelWithJSON:ackModel.response[@"room_info"]];
            roomModel.audienceCount = [[NSString stringWithFormat:@"%@", ackModel.response[@"audience_count"]] integerValue];
            hostUserModel = [VideoChatUserModel yy_modelWithJSON:ackModel.response[@"host_info"]];
            userModel = [VideoChatUserModel yy_modelWithJSON:ackModel.response[@"user_info"]];
            RTCToken = [NSString stringWithFormat:@"%@", ackModel.response[@"rtc_token"]];
            NSDictionary *seatDic = ackModel.response[@"seat_list"];
            for (int i = 0; i < seatDic.allKeys.count; i++) {
                NSString *keyStr = [NSString stringWithFormat:@"%ld", (long)(i + 1)];
                VideoChatSeatModel *seatModel = [VideoChatSeatModel yy_modelWithJSON:seatDic[keyStr]];
                seatModel.index = keyStr.integerValue;
                [seatList addObject:seatModel];
            }
            NSArray *anchorDictList = ackModel.response[@"anchor_list"];
            anchorList = [NSArray yy_modelArrayWithClass:[VideoChatUserModel class] json:anchorDictList];
        }
        if (block) {
            block(RTCToken,
                  roomModel,
                  userModel,
                  hostUserModel,
                  [seatList copy],
                  anchorList,
                  ackModel);
        }
        NSLog(@"[%@]-viJoinLiveRoom %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)replyInvite:(NSString *)roomID
              reply:(NSInteger)reply
              block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"reply": @(reply)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viReplyInvite" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viReplyInvite %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)finishInteract:(NSString *)roomID
                seatID:(NSString *)seatID
                 block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"seat_id": @(seatID.integerValue)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viFinishInteract" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viFinishInteract %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)applyInteract:(NSString *)roomID
               seatID:(NSString *)seatID
                block:(void (^)(BOOL isNeedApply,
                                RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"seat_id": @(seatID.integerValue)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viApplyInteract" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        BOOL isNeedApply = NO;
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            isNeedApply = [[NSString stringWithFormat:@"%@", ackModel.response[@"is_need_apply"]] boolValue];
        }
        if (block) {
            block(isNeedApply, ackModel);
        }
        NSLog(@"[%@]-viApplyInteract %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)leaveLiveRoom:(NSString *)roomID {
    NSDictionary *dic = @{@"room_id": roomID ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viLeaveLiveRoom" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSLog(@"[%@]-viLeaveLiveRoom %@ \n %@", [self class], dic, ackModel.response);
    }];
}

#pragma mark - Publish API

+ (void)getActiveLiveRoomListWithBlock:(void (^)(NSArray<VideoChatRoomModel *> *roomList,
                                                 RTSACKModel *model))block {
    NSDictionary *dic = [JoinRTSParams addTokenToParams:nil];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viGetActiveLiveRoomList" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        NSMutableArray<VideoChatRoomModel *> *roomModelList = [[NSMutableArray alloc] init];
        if ([VideoChatRTSManager ackModelResponseClass:ackModel]) {
            NSArray *list = ackModel.response[@"room_list"];
            for (int i = 0; i < list.count; i++) {
                VideoChatRoomModel *roomModel = [VideoChatRoomModel yy_modelWithJSON:list[i]];
                [roomModelList addObject:roomModel];
            }
        }
        if (block) {
            block([roomModelList copy], ackModel);
        }
        NSLog(@"[%@]-viGetActiveLiveRoomList %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)clearUser:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = [JoinRTSParams addTokenToParams:nil];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viClearUser" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viClearUser %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)sendMessage:(NSString *)roomID
            message:(NSString *)message
              block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"message": message ?: @""};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viSendMessage" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viSendMessage %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)updateMediaStatus:(NSString *)roomID
                      mic:(NSInteger)mic
                   camera:(NSInteger)camera
                    block:(void (^)(RTSACKModel *model))block {
    NSDictionary *dic = @{@"room_id": roomID ?: @"",
                          @"mic": @(mic),
                          @"camera": @(camera)};
    dic = [JoinRTSParams addTokenToParams:dic];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viUpdateMediaStatus" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        if (block) {
            block(ackModel);
        }
        NSLog(@"[%@]-viUpdateMediaStatus %@ \n %@", [self class], dic, ackModel.response);
    }];
}

+ (void)reconnectWithBlock:(void (^)(NSString *RTCToken,
                                     VideoChatRoomModel *roomModel,
                                     VideoChatUserModel *userModel,
                                     VideoChatUserModel *hostUserModel,
                                     NSArray<VideoChatSeatModel *> *seatList,
                                     NSArray<VideoChatUserModel *> *anchorList,
                                     NSArray<VideoChatUserModel *> *anchorInteractList,
                                     RTSACKModel *model))block {
    NSDictionary *dic = [JoinRTSParams addTokenToParams:nil];

    [[VideoChatRTCManager shareRtc] emitWithAck:@"viReconnect" with:dic block:^(RTSACKModel *_Nonnull ackModel) {
        VideoChatRoomModel *roomModel = nil;
        VideoChatUserModel *hostUserModel = nil;
        VideoChatUserModel *userModel = nil;
        NSArray<VideoChatUserModel *> *anchorList = nil;
        NSArray<VideoChatUserModel *> *anchorInteractList = nil;
        NSMutableArray<VideoChatSeatModel *> *seatList = [[NSMutableArray alloc] init];
        NSString *RTCToken = @"";
        if (ackModel.response &&
            [ackModel.response isKindOfClass:[NSDictionary class]]) {
            roomModel = [VideoChatRoomModel yy_modelWithJSON:ackModel.response[@"room_info"]];
            hostUserModel = [VideoChatUserModel yy_modelWithJSON:ackModel.response[@"host_info"]];
            userModel = [VideoChatUserModel yy_modelWithJSON:ackModel.response[@"user_info"]];
            NSDictionary *seatDic = ackModel.response[@"seat_list"];
            for (int i = 0; i < seatDic.allKeys.count; i++) {
                NSString *keyStr = [NSString stringWithFormat:@"%ld", (long)(i + 1)];
                VideoChatSeatModel *seatModel = [VideoChatSeatModel yy_modelWithJSON:seatDic[keyStr]];
                seatModel.index = keyStr.integerValue;
                [seatList addObject:seatModel];
            }
            RTCToken = [NSString stringWithFormat:@"%@", ackModel.response[@"rtc_token"]];

            anchorList = [NSArray yy_modelArrayWithClass:[VideoChatUserModel class] json:ackModel.response[@"anchor_list"]];
            anchorInteractList = [NSArray yy_modelArrayWithClass:[VideoChatUserModel class] json:ackModel.response[@"interact_info_list"]];
        }
        if (block) {
            block(RTCToken,
                  roomModel,
                  userModel,
                  hostUserModel,
                  [seatList copy],
                  anchorList,
                  anchorInteractList,
                  ackModel);
        }
        NSLog(@"[%@]-viReconnect %@ \n %@", [self class], dic, ackModel.response);
    }];
}

#pragma mark - Notification Message

+ (void)onAudienceJoinRoomWithBlock:(void (^)(VideoChatUserModel *userModel,
                                              NSInteger count))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnAudienceJoinRoom" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSInteger count = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"audience_count"]];
            count = [str integerValue];
        }
        if (block) {
            block(model, count);
        }
        NSLog(@"[%@]-viOnAudienceJoinRoom %@", [self class], noticeModel.data);
    }];
}

+ (void)onAudienceLeaveRoomWithBlock:(void (^)(VideoChatUserModel *userModel,
                                               NSInteger count))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnAudienceLeaveRoom" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSInteger count = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"audience_count"]];
            count = [str integerValue];
        }
        if (block) {
            block(model, count);
        }
        NSLog(@"[%@]-viOnAudienceLeaveRoom %@", [self class], noticeModel.data);
    }];
}

+ (void)onFinishLiveWithBlock:(void (^)(NSString *rommID, NSInteger type))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnFinishLive" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSInteger type = -1;
        NSString *rommID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"type"]];
            type = [str integerValue];
            rommID = [NSString stringWithFormat:@"%@", noticeModel.data[@"room_id"]];
        }
        if (block) {
            block(rommID, type);
        }
        NSLog(@"[%@]-viOnFinishLive %@", [self class], noticeModel.data);
    }];
}

+ (void)onJoinInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                          NSString *seatID))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnJoinInteract" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *seatID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
        }
        if (block) {
            block(model, seatID);
        }
        NSLog(@"[%@]-viOnJoinInteract %@", [self class], noticeModel.data);
    }];
}

+ (void)onFinishInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                            NSString *seatID,
                                            NSInteger type))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnFinishInteract" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *seatID = @"";
        NSInteger type = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"type"]];
            type = [str integerValue];
        }
        if (block) {
            block(model, seatID, type);
        }
        NSLog(@"[%@]-viOnFinishInteract %@", [self class], noticeModel.data);
    }];
}

+ (void)onSeatStatusChangeWithBlock:(void (^)(NSString *seatID,
                                              NSInteger type))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnSeatStatusChange" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSInteger type = -1;
        NSString *seatID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"type"]];
            type = [str integerValue];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
        }
        if (block) {
            block(seatID, type);
        }
        NSLog(@"[%@]-viOnSeatStatusChange %@", [self class], noticeModel.data);
    }];
}

+ (void)onMediaStatusChangeWithBlock:(void (^)(VideoChatUserModel *userModel,
                                               NSString *seatID,
                                               NSInteger mic,
                                               NSInteger camera))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnMediaStatusChange" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *seatID = @"";
        NSInteger mic = -1;
        NSInteger camera = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            [model bindOtherAnchorMicType:noticeModel.data];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"mic"]];
            mic = [str integerValue];

            NSString *cameraStr = [NSString stringWithFormat:@"%@", noticeModel.data[@"camera"]];
            camera = [cameraStr integerValue];
        }
        if (block) {
            block(model, seatID, mic, camera);
        }
        NSLog(@"[%@]-viOnMediaStatusChange %@", [self class], noticeModel.data);
    }];
}

+ (void)onMessageWithBlock:(void (^)(VideoChatUserModel *userModel,
                                     NSString *message))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnMessage" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *message = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            message = [NSString stringWithFormat:@"%@", noticeModel.data[@"message"]];
            message = [message stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        }
        if (block) {
            block(model, message);
        }
        NSLog(@"[%@]-viOnMessage %@", [self class], noticeModel.data);
    }];
}

#pragma mark - Single Notification Message

+ (void)onInviteInteractWithBlock:(void (^)(VideoChatUserModel *hostUserModel,
                                            NSString *seatID))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnInviteInteract" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *seatID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"host_info"]];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
        }
        if (block) {
            block(model, seatID);
        }
        NSLog(@"[%@]-viOnInviteInteract %@", [self class], noticeModel.data);
    }];
}

+ (void)onInviteResultWithBlock:(void (^)(VideoChatUserModel *userModel,
                                          NSInteger reply))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnInviteResult" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSInteger reply = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"reply"]];
            reply = [str integerValue];
        }
        if (block) {
            block(model, reply);
        }
        NSLog(@"[%@]-viOnInviteResult %@", [self class], noticeModel.data);
    }];
}

+ (void)onApplyInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                           NSString *seatID))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnApplyInteract" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *model = nil;
        NSString *seatID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            model = [VideoChatUserModel yy_modelWithJSON:noticeModel.data[@"user_info"]];
            seatID = [NSString stringWithFormat:@"%@", noticeModel.data[@"seat_id"]];
        }
        if (block) {
            block(model, seatID);
        }
        NSLog(@"[%@]-viOnApplyInteract %@", [self class], noticeModel.data);
    }];
}

+ (void)onMediaOperateWithBlock:(void (^)(NSInteger mic, NSInteger camera))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnMediaOperate" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSInteger mic = -1;
        NSInteger camera = -1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            NSString *str = [NSString stringWithFormat:@"%@", noticeModel.data[@"mic"]];
            mic = [str integerValue];

            NSString *cameraStr = [NSString stringWithFormat:@"%@", noticeModel.data[@"camera"]];
            camera = [cameraStr integerValue];
        }
        if (block) {
            block(mic, camera);
        }
        NSLog(@"[%@]-viOnMediaOperate %@", [self class], noticeModel.data);
    }];
}

+ (void)onClearUserWithBlock:(void (^)(NSString *uid))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnClearUser" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSString *uid = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            uid = [NSString stringWithFormat:@"%@", noticeModel.data[@"user_id"]];
        }
        if (block) {
            block(uid);
        }
        NSLog(@"[%@]-viOnClearUser %@", [self class], noticeModel.data);
    }];
}

+ (void)onAnchorInviteWithBlock:(void (^)(VideoChatUserModel *_Nonnull))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnAnchorInvite" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *anchorModel = nil;

        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            anchorModel = [VideoChatUserModel yy_modelWithJSON:noticeModel.data];
        }
        if (block) {
            block(anchorModel);
        }
        NSLog(@"[%@]-viOnAnchorInvite %@", [self class], noticeModel.data);
    }];
}

+ (void)onAnchorReplyWithBlock:(void (^)(VideoChatPKReply, NSString *_Nonnull, NSString *_Nonnull, VideoChatUserModel *_Nonnull))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnAnchorReply" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatPKReply reply = VideoChatPKReplyTimeOut;
        NSString *roomID = @"";
        NSString *token = @"";
        VideoChatUserModel *anchorModel = nil;

        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            reply = [noticeModel.data[@"reply"] integerValue];
            anchorModel = [VideoChatUserModel yy_modelWithJSON:noticeModel.data];
            NSDictionary *info = noticeModel.data[@"interact_info"];
            if (reply == VideoChatPKReplyAccept && [info isKindOfClass:[NSDictionary class]]) {
                roomID = [NSString stringWithFormat:@"%@", info[@"room_id"]];
                token = [NSString stringWithFormat:@"%@", info[@"token"]];
            }
        }
        if (block) {
            block(reply, roomID, token, anchorModel);
        }
        NSLog(@"[%@]-viOnAnchorReply %@", [self class], noticeModel.data);
    }];
}

+ (void)onNewAnchorJoinWithBlock:(void (^)(VideoChatUserModel *_Nonnull))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnNewAnchorJoin" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        VideoChatUserModel *anchorModel = nil;

        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            anchorModel = [VideoChatUserModel yy_modelWithJSON:noticeModel.data];
            anchorModel.otherAnchorMicType = VideoChatOtherAnchorMicTypeUnmute;
        }
        if (block) {
            block(anchorModel);
        }
        NSLog(@"[%@]-viOnNewAnchorJoin %@", [self class], noticeModel.data);
    }];
}

+ (void)onAnchorPKEndWithBlock:(void (^)(void))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnAnchorInteractFinish" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        if (block) {
            block();
        }
        NSLog(@"[%@]-viOnAnchorInteractFinish %@", [self class], noticeModel.data);
    }];
}

+ (void)onClosedChatRoomModeWithBlock:(void (^)(NSString *roomID))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnCloseChatRoom" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSString *roomID = @"";
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            roomID = [NSString stringWithFormat:@"%@", noticeModel.data[@"room_id"]];
        }
        if (block) {
            block(roomID);
        }
        NSLog(@"[%@]-viOnCloseChatRoom %@", [self class], noticeModel.data);
    }];
}

+ (void)onMuteOtherAnchorWithBlock:(void (^)(NSString *roomID, NSString *otherAnchorUserID, VideoChatOtherAnchorMicType type))block {
    [[VideoChatRTCManager shareRtc] onSceneListener:@"viOnManageOtherAnchor" block:^(RTSNoticeModel *_Nonnull noticeModel) {
        NSString *roomID = @"";
        NSString *otherAnchorUserID = @"";
        NSInteger type = 1;
        if (noticeModel.data && [noticeModel.data isKindOfClass:[NSDictionary class]]) {
            roomID = [NSString stringWithFormat:@"%@", noticeModel.data[@"room_id"]];
            otherAnchorUserID = [NSString stringWithFormat:@"%@", noticeModel.data[@"other_anchor_user_id"]];
            type = [noticeModel.data[@"type"] integerValue];
        }
        if (block) {
            block(roomID, otherAnchorUserID, type);
        }
        NSLog(@"[%@]-viOnManageOtherAnchor %@", [self class], noticeModel.data);
    }];
}

#pragma mark - Tool

+ (BOOL)ackModelResponseClass:(RTSACKModel *)ackModel {
    if ([ackModel.response isKindOfClass:[NSDictionary class]]) {
        return YES;
    } else {
        return NO;
    }
}

@end
