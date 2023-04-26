// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomViewController : UIViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel;

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                         rtcToken:(NSString *)rtcToken
                    hostUserModel:(VideoChatUserModel *)hostUserModel;

#pragma mark - RTS Listener

/**
 * @brief Received the user joined the room
 * @param userModel user model
 * @param count the number of users in the current room
 */
- (void)receivedJoinUser:(VideoChatUserModel *)userModel
                   count:(NSInteger)count;

/**
 * @brief Received when the user left the room
 * @param userModel user model
 * @param count the number of users in the current room
 */
- (void)receivedLeaveUser:(VideoChatUserModel *)userModel
                    count:(NSInteger)count;

/**
 * @brief received the message that the live broadcast ended
 * @param type The end type of the live broadcast. 2: Closed due to timeout, 3: Closed due to violation.
 */
- (void)receivedFinishLive:(NSInteger)type
                    roomID:(NSString *)roomID;


/**
 * @brief Received the status change message of the seat
 * @param seatID seat ID
 * @param type state. 0 : Block the microphone, 1 : Unlock the microphone
 */
- (void)receivedSeatStatusChange:(NSString *)seatID
                            type:(NSInteger)type;

/**
 * @brief received camera microphone status change message
 * @param userModel user model
 * @param seatID seat ID
 * @param mic microphone acquisition status
 * @param camera camera acquisition status
 */
- (void)receivedMediaStatusChangeWithUser:(VideoChatUserModel *)userModel
                                   seatID:(NSString *)seatID
                                      mic:(NSInteger)mic
                                   camera:(NSInteger)camera;

/**
 * @brief IM message received
 * @param userModel user model
 * @param message message
 */
- (void)receivedMessageWithUser:(VideoChatUserModel *)userModel
                        message:(NSString *)message;

/**
 * @brief Received news of changes in your camera and microphone
 * @param mic microphone acquisition status
 * @param camera camera acquisition status
 */
- (void)receivedMediaOperatWithUid:(NSInteger)mic
                            camera:(NSInteger)camera;

/**
 * @brief Receive account to log in repeatedly, single sign-on
 * @param uid user ID
 */
- (void)receivedClearUserWithUid:(NSString *)uid;

#pragma mark - Listener Guests

/**
 * @brief Received the news that the make guest
 * @param userModel guest user model
 * @param seatID seat ID
 */
- (void)receivedJoinInteractWithUser:(VideoChatUserModel *)userModel
                              seatID:(NSString *)seatID;

/**
 * @brief Received the news that the leave interact
 * @param userModel guest user model
 * @param seatID seat ID
 * @param type state. 1 : passive mic, 2 : active mic
 */
- (void)receivedLeaveInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID
                                 type:(NSInteger)type;

/**
 * @brief The audience received the host's invitation to make guest news
 * @param hostUserModel anchor user model
 * @param seatID seat ID
 */
- (void)receivedInviteInteractWithUser:(VideoChatUserModel *)hostUserModel
                                seatID:(NSString *)seatID;

/**
 * @brief The anchor received the news that the audience applied for make guest
 * @param userModel audience user model
 * @param seatID seat ID
 */
- (void)receivedApplyInteractWithUser:(VideoChatUserModel *)userModel
                               seatID:(NSString *)seatID;

/**
 * @brief The host received a message that the audience invitation was rejected
 * @param hostUserModel anchor user model
 * @param reply reply
 */
- (void)receivedInviteResultWithUser:(VideoChatUserModel *)hostUserModel
                               reply:(NSInteger)reply;

/**
 * @brief Received the news that the make guest ended
 */
- (void)receiverCloseChatRoomMode;

#pragma mark - Listener Cohost

/**
 * @brief Received an invitation from make cohost
 * @param anchorModel anchor user model
 */
- (void)receivedAnchorPKInvite:(VideoChatUserModel *)anchorModel;

/**
 * @brief received a reply from make cohost invitation
 * @param reply The reply type. 1: accept, 2: reject, 3: timeout
 * @param roomID room ID
 * @param token Token required to join the RTC room
 * @param anchorModel anchor user model
 */
- (void)receivedAnchorPKReply:(VideoChatPKReply)reply
                       roomID:(NSString *)roomID
                        token:(NSString *)token
                  anchorModel:(VideoChatUserModel *)anchorModel;

/**
 * @brief Received make cohost open
 * @param anchorModel anchor user model
 */
- (void)receivedAnchorPKNewAnchorJoined:(VideoChatUserModel *)anchorModel;

/**
 * @brief Received make cohost end
 */
- (void)receivedAnchorPKEnd;

/**
 * @brief Received the message that the anchor muted the other anchor
 * @param roomID room ID
 * @param otherAnchorUserID The other anchor user ID
 * @param type type. 0: mute, 1: unmute
 */
- (void)receivedMuteOtherAnchorRoomID:(NSString *)roomID
                    otherAnchorUserID:(NSString *)otherAnchorUserID
                                 type:(VideoChatOtherAnchorMicType)type;

@end

NS_ASSUME_NONNULL_END
