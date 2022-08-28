/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

@class VideoChatRoomUserListtCell;

NS_ASSUME_NONNULL_BEGIN

@protocol VideoChatRoomUserListtCellDelegate <NSObject>

- (void)VideoChatRoomUserListtCell:(VideoChatRoomUserListtCell *)VideoChatRoomUserListtCell clickButton:(id)model;

@end

@interface VideoChatRoomUserListtCell : UITableViewCell

@property (nonatomic, strong) VideoChatUserModel *model;

@property (nonatomic, weak) id<VideoChatRoomUserListtCellDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
