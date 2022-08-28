/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>
#import "VideoChatRoomUserListtCell.h"
@class VideoChatRoomAudienceListsView;

NS_ASSUME_NONNULL_BEGIN

@protocol VideoChatRoomAudienceListsViewDelegate <NSObject>

- (void)VideoChatRoomAudienceListsView:(VideoChatRoomAudienceListsView *)VideoChatRoomAudienceListsView clickButton:(VideoChatUserModel *)model;

@end


@interface VideoChatRoomAudienceListsView : UIView

@property (nonatomic, copy) NSArray<VideoChatUserModel *> *dataLists;

@property (nonatomic, weak) id<VideoChatRoomAudienceListsViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
