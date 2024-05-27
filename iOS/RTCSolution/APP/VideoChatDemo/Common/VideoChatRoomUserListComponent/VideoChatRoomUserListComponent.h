//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatRoomAudienceListsView.h"
#import "VideoChatRoomRaiseHandListsView.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomUserListComponent : NSObject

@property (nonatomic, assign) BOOL isInviteInteractionWaitingReply;

- (void)showRoomModel:(VideoChatRoomModel *)roomModel
               seatID:(NSString *)seatID
         dismissBlock:(void (^)(void))dismissBlock;

- (void)update;

- (void)updateWithRed:(BOOL)isRed;

- (void)updateCloseChatRoom:(BOOL)isHidden;

- (void)changeChatRoomModeDismissUserListView;

- (void)resetInviteInteractionWaitingReplyStstus;

@end

NS_ASSUME_NONNULL_END
