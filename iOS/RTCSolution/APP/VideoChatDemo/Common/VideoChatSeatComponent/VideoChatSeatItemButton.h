//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "BaseButton.h"

typedef NS_ENUM(NSInteger, VideoChatSheetStatus) {
    // The host initiates an invitation
    VideoChatSheetStatusInvite = 0,
    // The host invites guests to mic
    VideoChatSheetStatusKick,
    // Turn on the microphone
    VideoChatSheetStatusOpenMic,
    // Turn off the microphone
    VideoChatSheetStatusCloseMic,
    // Block microphone
    VideoChatSheetStatusLock,
    // Unlock microphone
    VideoChatSheetStatusUnlock,
    // Audience apply for mic
    VideoChatSheetStatusApply,
    // The guests took the initiative to take the mic
    VideoChatSheetStatusLeave,
};

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSeatItemButton : BaseButton

@property (nonatomic, copy) NSString *desTitle;

@property (nonatomic, assign) VideoChatSheetStatus sheetState;

@end

NS_ASSUME_NONNULL_END
