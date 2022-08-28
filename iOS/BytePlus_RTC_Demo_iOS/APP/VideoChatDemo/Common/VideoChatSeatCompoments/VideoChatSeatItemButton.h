/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "BaseButton.h"

typedef NS_ENUM(NSInteger, VideoChatSheetStatus) {
    VideoChatSheetStatusInvite = 0,
    VideoChatSheetStatusKick,
    VideoChatSheetStatusOpenMic,
    VideoChatSheetStatusCloseMic,
    VideoChatSheetStatusLock,
    VideoChatSheetStatusUnlock,
    VideoChatSheetStatusApply,      //观众申请上麦
    VideoChatSheetStatusLeave,      //嘉宾主动下麦
};

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSeatItemButton : BaseButton

@property (nonatomic, copy) NSString *desTitle;

@property (nonatomic, assign) VideoChatSheetStatus sheetState;

@end

NS_ASSUME_NONNULL_END
