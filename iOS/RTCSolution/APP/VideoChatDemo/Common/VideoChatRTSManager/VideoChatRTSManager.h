//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "RTSACKModel.h"
#import "VideoChatControlRecordModel.h"
#import "VideoChatRoomModel.h"
#import "VideoChatSeatModel.h"
#import "VideoChatUserModel.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRTSManager : NSObject

#pragma mark - Host API

/// The host creates a live room
/// @param roomName Room Name
/// @param userName User Name
/// @param bgImageName Bg Image Name
/// @param block Callback
+ (void)createRoom:(NSString *)roomName
          userName:(NSString *)userName
       bgImageName:(NSString *)bgImageName
             block:(void (^)(NSString *RTCToken,
                             VideoChatRoomModel *roomModel,
                             VideoChatUserModel *hostUserModel,
                             RTSACKModel *model))block;

/// The host start a live room
/// @param block Callback
+ (void)startLive:(NSString *)roomID
            block:(void (^)(RTSACKModel *model))block;

/// Get the list of audience in the room
/// @param roomID Room ID
/// @param block Callback
+ (void)getAudienceList:(NSString *)roomID
                  block:(void (^)(NSArray<VideoChatUserModel *> *userLists,
                                  RTSACKModel *model))block;

/// Get the list of audiences applied for in the room
/// @param roomID Room ID
/// @param block Callback
+ (void)getApplyAudienceList:(NSString *)roomID
                       block:(void (^)(NSArray<VideoChatUserModel *> *userLists,
                                       RTSACKModel *model))block;

/// The anchor invites the audience to come on stage
/// @param roomID Room ID
/// @param uid User ID
/// @param seatID Seat ID
/// @param block Callback
+ (void)inviteInteract:(NSString *)roomID
                   uid:(NSString *)uid
                seatID:(NSString *)seatID
                 block:(void (^)(RTSACKModel *model))block;

/// The anchor agrees to the audience's application
/// @param roomID Room ID
/// @param uid User ID
/// @param block Callback
+ (void)agreeApply:(NSString *)roomID
               uid:(NSString *)uid
             block:(void (^)(RTSACKModel *model))block;

/// Whether the host switch is turned on to apply
/// @param roomID Room ID
/// @param type 1 open, other close
/// @param block Callback
+ (void)managerInteractApply:(NSString *)roomID
                        type:(NSInteger)type
                       block:(void (^)(RTSACKModel *model))block;

/// Host management Shangmai guests
/// @param roomID Room ID
/// @param seatID Seat ID
/// @param type management
/// @param block Callback
+ (void)managerSeat:(NSString *)roomID
             seatID:(NSString *)seatID
               type:(NSInteger)type
              block:(void (^)(RTSACKModel *model))block;

/// The host ends the live broadcast
/// @param roomID Room ID
+ (void)finishLive:(NSString *)roomID;

/// Request the list of PK user
/// @param complete Callback
+ (void)requestPKUserListComplete:(void (^)(NSArray<VideoChatUserModel *> *userList, RTSACKModel *model))complete;

/// Invite anchor pk
/// @param fromRoomID From roomID
/// @param fromUserID from userID
/// @param toRoomID To roomID
/// @param toUserID To userID
/// @param seatID SeatID
/// @param complete Callback
+ (void)requestInviteAnchorWithFromRoomID:(NSString *)fromRoomID
                               fromUserID:(NSString *)fromUserID
                                 toRoomID:(NSString *)toRoomID
                                 toUserID:(NSString *)toUserID
                                   seatID:(NSInteger)seatID
                                 complete:(void (^)(RTSACKModel *model))complete;

/// Reply to host invitation
/// @param inviterRoomID Inviter roomID
/// @param inviterUserID Inviter userID
/// @param roomID RoomID
/// @param userID UserID
/// @param reply Reply
/// @param complete Callback
+ (void)replyInviteWithInviterRoomID:(NSString *)inviterRoomID
                       inviterUserID:(NSString *)inviterUserID
                              roomID:(NSString *)roomID
                              userID:(NSString *)userID
                               reply:(VideoChatPKReply)reply
                            complete:(void (^)(NSString *roomID, NSString *token, RTSACKModel *model))complete;

/// Request end PK
/// @param roomID RoomID
/// @param userID UserID
/// @param complete Callback
+ (void)requestStopPKWithRoomID:(NSString *)roomID
                         userID:(NSString *)userID
                       complete:(void (^)(RTSACKModel *model))complete;

/// Request close chat room mode
/// @param roomID RoomID
/// @param complete Callback
+ (void)requestCloseChatRoomMode:(NSString *)roomID
                        complete:(void (^)(RTSACKModel *model))complete;

/// Request mute other anchor
/// @param roomID RoomID
/// @param otherAnchorUserID Other anchor userID
/// @param type Type 1: mute 2 unmute
/// @param complete Callback
+ (void)requestMuteOtherAnchorRoomID:(NSString *)roomID
                   otherAnchorUserID:(NSString *)otherAnchorUserID
                                type:(VideoChatOtherAnchorMicType)type
                            complete:(void (^)(RTSACKModel *model))complete;

#pragma mark - Audience API

/// The audience joins the room
/// @param roomID Room ID
/// @param userName User Name
/// @param block Callback
+ (void)joinLiveRoom:(NSString *)roomID
            userName:(NSString *)userName
               block:(void (^)(NSString *RTCToken,
                               VideoChatRoomModel *roomModel,
                               VideoChatUserModel *userModel,
                               VideoChatUserModel *hostUserModel,
                               NSArray<VideoChatSeatModel *> *seatList,
                               NSArray<VideoChatUserModel *> *anchorList,
                               RTSACKModel *model))block;

/// Reply to the host’s invitation
/// @param roomID Room ID
/// @param reply 1 accept, 2 Refuse
/// @param block Callback
+ (void)replyInvite:(NSString *)roomID
              reply:(NSInteger)reply
              block:(void (^)(RTSACKModel *model))block;

/// Distinguished guests
/// @param roomID Room ID
/// @param seatID Seat ID
/// @param block Callback
+ (void)finishInteract:(NSString *)roomID
                seatID:(NSString *)seatID
                 block:(void (^)(RTSACKModel *model))block;

/// Audience application on stage
/// @param roomID Room ID
/// @param seatID Seat ID [1-8]
/// @param block Callback
+ (void)applyInteract:(NSString *)roomID
               seatID:(NSString *)seatID
                block:(void (^)(BOOL isNeedApply,
                                RTSACKModel *model))block;

/// The audience leaves the room
/// @param roomID Room ID
+ (void)leaveLiveRoom:(NSString *)roomID;

#pragma mark - Publish API

/// Received the audience
/// @param block Callback
+ (void)getActiveLiveRoomListWithBlock:(void (^)(NSArray<VideoChatRoomModel *> *roomList,
                                                 RTSACKModel *model))block;

/// Mutual kick notification
/// @param block Callback
+ (void)clearUser:(void (^)(RTSACKModel *model))block;

/// Send IM message
/// @param roomID Room ID
/// @param message Message
/// @param block Callback
+ (void)sendMessage:(NSString *)roomID
            message:(NSString *)message
              block:(void (^)(RTSACKModel *model))block;

/// Update microphone status
/// @param roomID Room ID
/// @param mic 0 close ,1 open
/// @param block Callback
+ (void)updateMediaStatus:(NSString *)roomID
                      mic:(NSInteger)mic
                   camera:(NSInteger)camera
                    block:(void (^)(RTSACKModel *model))block;

/// reconnect
/// @param block Callback
+ (void)reconnectWithBlock:(void (^)(NSString *RTCToken,
                                     VideoChatRoomModel *roomModel,
                                     VideoChatUserModel *userModel,
                                     VideoChatUserModel *hostUserModel,
                                     NSArray<VideoChatSeatModel *> *seatList,
                                     NSArray<VideoChatUserModel *> *anchorList,
                                     NSArray<VideoChatUserModel *> *anchorInteractList,
                                     RTSACKModel *model))block;

#pragma mark - Notification Message

/// The audience joins the room
/// @param block Callback
+ (void)onAudienceJoinRoomWithBlock:(void (^)(VideoChatUserModel *userModel,
                                              NSInteger count))block;

/// The audience leaves the room
/// @param block Callback
+ (void)onAudienceLeaveRoomWithBlock:(void (^)(VideoChatUserModel *userModel,
                                               NSInteger count))block;

/// Received the end of the live broadcast room
/// @param block Callback
+ (void)onFinishLiveWithBlock:(void (^)(NSString *rommID, NSInteger type))block;

/// Successful audience
/// @param block Callback
+ (void)onJoinInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                          NSString *seatID))block;

/// Distinguished guests
/// @param block Callback
+ (void)onFinishInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                            NSString *seatID,
                                            NSInteger type))block;

/// Seat status changes
/// @param block Callback
+ (void)onSeatStatusChangeWithBlock:(void (^)(NSString *seatID,
                                              NSInteger type))block;

/// Microphone status changes
/// @param block Callback
+ (void)onMediaStatusChangeWithBlock:(void (^)(VideoChatUserModel *userModel,
                                               NSString *seatID,
                                               NSInteger mic,
                                               NSInteger camera))block;

/// IM message received
/// @param block Callback
+ (void)onMessageWithBlock:(void (^)(VideoChatUserModel *userModel,
                                     NSString *message))block;

#pragma mark - Single Notification Message

/// Received an invitation
/// @param block Callback
+ (void)onInviteInteractWithBlock:(void (^)(VideoChatUserModel *hostUserModel,
                                            NSString *seatID))block;

/// Application received
/// @param block Callback
+ (void)onApplyInteractWithBlock:(void (^)(VideoChatUserModel *userModel,
                                           NSString *seatID))block;

/// Receipt of invitation result
/// @param block Callback
+ (void)onInviteResultWithBlock:(void (^)(VideoChatUserModel *userModel,
                                          NSInteger reply))block;

/// Receive guest/host microphone changes
/// @param block Callback
+ (void)onMediaOperateWithBlock:(void (^)(NSInteger mic,
                                          NSInteger camera))block;

/// Received mutual kick notification
/// @param block Callback
+ (void)onClearUserWithBlock:(void (^)(NSString *uid))block;

/// Received anchor invite
/// @param block CallBack
+ (void)onAnchorInviteWithBlock:(void (^)(VideoChatUserModel *anchorModel))block;

/// Received anchor reply
/// @param block Callback
+ (void)onAnchorReplyWithBlock:(void (^)(VideoChatPKReply reply, NSString *roomID, NSString *token, VideoChatUserModel *anchorModel))block;

/// Received new anchor joined
/// @param block Callback
+ (void)onNewAnchorJoinWithBlock:(void (^)(VideoChatUserModel *anchorModel))block;

/// Received anchor pk end
/// @param block Callback
+ (void)onAnchorPKEndWithBlock:(void (^)(void))block;

/// Received close chat room mode
/// @param block Callback
+ (void)onClosedChatRoomModeWithBlock:(void (^)(NSString *roomID))block;

/// Received mute other anchor
/// @param block Callback
+ (void)onMuteOtherAnchorWithBlock:(void (^)(NSString *roomID, NSString *otherAnchorUserID, VideoChatOtherAnchorMicType type))block;

@end

NS_ASSUME_NONNULL_END
