/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatPKUserListComponents : NSObject

@property (nonatomic, assign) BOOL isPKWaitingReply;

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel;

- (void)showAnchorList;

- (void)startForwardStream:(NSString *)roomID token:(NSString *)token;

- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel;

- (void)resetPkWaitingReplyStstus;

@end

NS_ASSUME_NONNULL_END
