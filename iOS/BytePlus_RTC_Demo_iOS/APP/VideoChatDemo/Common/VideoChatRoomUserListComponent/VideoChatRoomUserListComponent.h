/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#import "VideoChatRoomAudienceListsView.h"
#import "VideoChatRoomRaiseHandListsView.h"

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
