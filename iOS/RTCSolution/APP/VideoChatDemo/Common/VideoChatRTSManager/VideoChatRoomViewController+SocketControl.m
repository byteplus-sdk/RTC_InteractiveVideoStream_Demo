//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatRoomViewController+SocketControl.h"

@implementation VideoChatRoomViewController (SocketControl)

- (void)addSocketListener {
    __weak __typeof(self) wself = self;
    [VideoChatRTSManager onAudienceJoinRoomWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSInteger count) {
        if (wself) {
            [wself receivedJoinUser:userModel count:count];
        }
    }];

    [VideoChatRTSManager onAudienceLeaveRoomWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSInteger count) {
        if (wself) {
            [wself receivedLeaveUser:userModel count:count];
        }
    }];

    [VideoChatRTSManager onFinishLiveWithBlock:^(NSString *_Nonnull rommID, NSInteger type) {
        if (wself) {
            [wself receivedFinishLive:type roomID:rommID];
        }
    }];

    [VideoChatRTSManager onJoinInteractWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSString *_Nonnull seatID) {
        if (wself) {
            [wself receivedJoinInteractWithUser:userModel seatID:seatID];
        }
    }];

    [VideoChatRTSManager onFinishInteractWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSString *_Nonnull seatID, NSInteger type) {
        if (wself) {
            [wself receivedLeaveInteractWithUser:userModel seatID:seatID type:type];
        }
    }];

    [VideoChatRTSManager onSeatStatusChangeWithBlock:^(NSString *_Nonnull seatID, NSInteger type) {
        if (wself) {
            [wself receivedSeatStatusChange:seatID type:type];
        }
    }];

    [VideoChatRTSManager onMediaStatusChangeWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSString *_Nonnull seatID, NSInteger mic, NSInteger camera) {
        if (wself) {
            [wself receivedMediaStatusChangeWithUser:userModel
                                              seatID:seatID
                                                 mic:mic
                                              camera:camera];
        }
    }];

    [VideoChatRTSManager onMessageWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSString *_Nonnull message) {
        if (wself) {
            [wself receivedMessageWithUser:userModel message:message];
        }
    }];

    // Single Notification Message

    [VideoChatRTSManager onInviteInteractWithBlock:^(VideoChatUserModel *_Nonnull hostUserModel, NSString *_Nonnull seatID) {
        if (wself) {
            [wself receivedInviteInteractWithUser:hostUserModel seatID:seatID];
        }
    }];

    [VideoChatRTSManager onApplyInteractWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSString *_Nonnull seatID) {
        if (wself) {
            [wself receivedApplyInteractWithUser:userModel seatID:seatID];
        }
    }];

    [VideoChatRTSManager onInviteResultWithBlock:^(VideoChatUserModel *_Nonnull userModel, NSInteger reply) {
        if (wself) {
            [wself receivedInviteResultWithUser:userModel reply:reply];
        }
    }];

    [VideoChatRTSManager onMediaOperateWithBlock:^(NSInteger mic, NSInteger camera) {
        if (wself) {
            [wself receivedMediaOperatWithUid:mic camera:camera];
        }
    }];

    [VideoChatRTSManager onClearUserWithBlock:^(NSString *_Nonnull uid) {
        if (wself) {
            [wself receivedClearUserWithUid:uid];
        }
    }];

    [VideoChatRTSManager onAnchorInviteWithBlock:^(VideoChatUserModel *_Nonnull anchorModel) {
        if (wself) {
            [wself receivedAnchorPKInvite:anchorModel];
        }
    }];

    [VideoChatRTSManager onAnchorReplyWithBlock:^(VideoChatPKReply reply, NSString *_Nonnull roomID, NSString *_Nonnull token, VideoChatUserModel *_Nonnull anchorModel) {
        [wself receivedAnchorPKReply:reply roomID:roomID token:token anchorModel:anchorModel];
    }];

    [VideoChatRTSManager onNewAnchorJoinWithBlock:^(VideoChatUserModel *_Nonnull anchorModel) {
        [wself receivedAnchorPKNewAnchorJoined:anchorModel];
    }];

    [VideoChatRTSManager onAnchorPKEndWithBlock:^{
        [wself receivedAnchorPKEnd];
    }];

    [VideoChatRTSManager onClosedChatRoomModeWithBlock:^(NSString *_Nonnull roomID) {
        [wself receiverCloseChatRoomMode];
    }];

    [VideoChatRTSManager onMuteOtherAnchorWithBlock:^(NSString *_Nonnull roomID, NSString *_Nonnull otherAnchorUserID, VideoChatOtherAnchorMicType type) {
        [wself receivedMuteOtherAnchorRoomID:roomID otherAnchorUserID:otherAnchorUserID type:type];
    }];
}
@end
