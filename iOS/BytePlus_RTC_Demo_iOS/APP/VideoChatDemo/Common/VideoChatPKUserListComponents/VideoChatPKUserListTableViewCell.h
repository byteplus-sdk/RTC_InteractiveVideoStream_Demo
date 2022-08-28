/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>
@class VideoChatPKUserListTableViewCell;

NS_ASSUME_NONNULL_BEGIN

@protocol VideoChatPKUserListTableViewCellDelegate <NSObject>

- (void)videoChatPKUserListTableViewCell:(VideoChatPKUserListTableViewCell *)cell didClickUserModel:(VideoChatUserModel *)model;

@end

@interface VideoChatPKUserListTableViewCell : UITableViewCell

@property (nonatomic, strong) VideoChatUserModel *model;
@property (nonatomic, weak) id<VideoChatPKUserListTableViewCellDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
