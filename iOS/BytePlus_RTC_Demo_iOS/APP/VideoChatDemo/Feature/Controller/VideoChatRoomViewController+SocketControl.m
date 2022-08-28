/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatRoomViewController+SocketControl.h"

@implementation VideoChatRoomViewController (SocketControl)

- (void)addSocketListener {
    __weak __typeof(self) wself = self;
    [VideoChatRTMManager onAudienceJoinRoomWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSInteger count) {
        if (wself) {
            [wself receivedJoinUser:userModel count:count];
        }
    }];
    
    
    [VideoChatRTMManager onAudienceLeaveRoomWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSInteger count) {
        if (wself) {
            [wself receivedLeaveUser:userModel count:count];
        }
    }];

    
    [VideoChatRTMManager onFinishLiveWithBlock:^(NSString * _Nonnull rommID, NSInteger type) {
        if (wself) {
            [wself receivedFinishLive:type roomID:rommID];
        }
    }];

    
    [VideoChatRTMManager onJoinInteractWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSString * _Nonnull seatID) {
        if (wself) {
            [wself receivedJoinInteractWithUser:userModel seatID:seatID];
        }
    }];

    
    [VideoChatRTMManager onFinishInteractWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSString * _Nonnull seatID, NSInteger type) {
        if (wself) {
            [wself receivedLeaveInteractWithUser:userModel seatID:seatID type:type];
        }
    }];

    
    [VideoChatRTMManager onSeatStatusChangeWithBlock:^(NSString * _Nonnull seatID, NSInteger type) {
        if (wself) {
            [wself receivedSeatStatusChange:seatID type:type];
        }
    }];

    
    [VideoChatRTMManager onMediaStatusChangeWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSString * _Nonnull seatID, NSInteger mic, NSInteger camera) {
        if (wself) {
            [wself receivedMediaStatusChangeWithUser:userModel
                                              seatID:seatID
                                                 mic:mic
                                              camera:camera];
        }
    }];

    
    [VideoChatRTMManager onMessageWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSString * _Nonnull message) {
        if (wself) {
            message = [message stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
            [wself receivedMessageWithUser:userModel message:message];
        }
    }];

    //Single Notification Message
    
    [VideoChatRTMManager onInviteInteractWithBlock:^(VideoChatUserModel * _Nonnull hostUserModel, NSString * _Nonnull seatID) {
        if (wself) {
            [wself receivedInviteInteractWithUser:hostUserModel seatID:seatID];
        }
    }];
    
    [VideoChatRTMManager onApplyInteractWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSString * _Nonnull seatID) {
        if (wself) {
            [wself receivedApplyInteractWithUser:userModel seatID:seatID];
        }
    }];

    [VideoChatRTMManager onInviteResultWithBlock:^(VideoChatUserModel * _Nonnull userModel, NSInteger reply) {
        if (wself) {
            [wself receivedInviteResultWithUser:userModel reply:reply];
        }
    }];
    
    [VideoChatRTMManager onMediaOperateWithBlock:^(NSInteger mic, NSInteger camera) {
        if (wself) {
            [wself receivedMediaOperatWithUid:mic camera:camera];
        }
    }];

    [VideoChatRTMManager onClearUserWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            [wself receivedClearUserWithUid:uid];
        }
    }];
    
    [VideoChatRTMManager onAnchorInviteWithBlock:^(VideoChatUserModel * _Nonnull anchorModel) {
        if (wself) {
            [wself receivedAnchorPKInvite:anchorModel];
        }
    }];
    
    [VideoChatRTMManager onAnchorReplyWithBlock:^(VideoChatPKReply reply, NSString * _Nonnull roomID, NSString * _Nonnull token, VideoChatUserModel * _Nonnull anchorModel) {
        [wself receivedAnchorPKReply:reply roomID:roomID token:token anchorModel:anchorModel];
    }];
    
    [VideoChatRTMManager onNewAnchorJoinWithBlock:^(VideoChatUserModel * _Nonnull anchorModel) {
        [wself receivedAnchorPKNewAnchorJoined:anchorModel];
    }];
    
    [VideoChatRTMManager onAnchorPKEndWithBlock:^{
        [wself receivedAnchorPKEnd];
    }];
    
    [VideoChatRTMManager onClosedChatRoomModeWithBlock:^(NSString * _Nonnull roomID) {
        [wself receiverCloseChatRoomMode];
    }];
    
    [VideoChatRTMManager onMuteOtherAnchorWithBlock:^(NSString * _Nonnull roomID, NSString * _Nonnull otherAnchorUserID, VideoChatOtherAnchorMicType type) {
        [wself receivedMuteOtherAnchorRoomID:roomID otherAnchorUserID:otherAnchorUserID type:type];
    }];
}
@end
