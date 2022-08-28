/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomViewController : UIViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel;

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                         rtcToken:(NSString *)rtcToken
                    hostUserModel:(VideoChatUserModel *)hostUserModel;

- (void)receivedJoinUser:(VideoChatUserModel *)userModel
                   count:(NSInteger)count;

- (void)receivedLeaveUser:(VideoChatUserModel *)userModel
                    count:(NSInteger)count;

- (void)receivedFinishLive:(NSInteger)type roomID:(NSString *)roomID;

- (void)receivedJoinInteractWithUser:(VideoChatUserModel *)userModel
                              seatID:(NSString *)seatID;

- (void)receivedLeaveInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID
                                 type:(NSInteger)type;

- (void)receivedSeatStatusChange:(NSString *)seatID
                            type:(NSInteger)type;

- (void)receivedMediaStatusChangeWithUser:(VideoChatUserModel *)userModel
                                   seatID:(NSString *)seatID
                                      mic:(NSInteger)mic
                                   camera:(NSInteger)camera;

- (void)receivedMessageWithUser:(VideoChatUserModel *)userModel
                            message:(NSString *)message;

- (void)receivedInviteInteractWithUser:(VideoChatUserModel *)hostUserModel
                                seatID:(NSString *)seatID;

- (void)receivedApplyInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID;


- (void)receivedInviteResultWithUser:(VideoChatUserModel *)hostUserModel
                               reply:(NSInteger)reply;

- (void)receivedMediaOperatWithUid:(NSInteger)mic camera:(NSInteger)camera;

- (void)receivedClearUserWithUid:(NSString *)uid;

- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel;

- (void)receivedAnchorPKReply:(VideoChatPKReply)reply
                       roomID:(NSString *)roomID
                        token:(NSString *)token
                  anchorModel:(VideoChatUserModel *)anchorModel;

- (void)receivedAnchorPKNewAnchorJoined:(VideoChatUserModel *)anchorModel;

- (void)receivedAnchorPKEnd;

- (void)receiverCloseChatRoomMode;

- (void)receivedMuteOtherAnchorRoomID:(NSString *)roomID otherAnchorUserID:(NSString *)otherAnchorUserID type:(VideoChatOtherAnchorMicType)type;

@end

NS_ASSUME_NONNULL_END
