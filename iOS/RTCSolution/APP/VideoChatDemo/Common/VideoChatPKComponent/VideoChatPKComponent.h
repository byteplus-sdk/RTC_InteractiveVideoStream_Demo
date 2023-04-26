// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatPKComponent : NSObject

@property (nonatomic, strong) VideoChatUserModel *hostModel;
@property (nonatomic, strong) VideoChatUserModel *_Nullable anchorModel;
@property (nonatomic, assign) BOOL activeEndPK;

- (instancetype)initWithSuperView:(UIView *)superView roomModel:(VideoChatRoomModel *)roomModel;

- (void)changeChatRoomMode:(VideoChatRoomMode)mode;

- (void)updateRenderView:(NSString *)userID;

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid;

- (void)updateUserModel:(VideoChatUserModel *)userModel;

- (void)updateInformationOtherHost:(NSArray<VideoChatUserModel *> *)hostList
                    currentHostUid:(NSString *)currentHostUid;

- (void)muteOtherAnchorRoomID:(NSString *)roomID otherAnchorUserID:(NSString *)otherAnchorUserID type:(VideoChatOtherAnchorMicType)type;

- (void)reqeustStopForwardStream;

- (void)rtcStopForwardStream;


@end

NS_ASSUME_NONNULL_END
