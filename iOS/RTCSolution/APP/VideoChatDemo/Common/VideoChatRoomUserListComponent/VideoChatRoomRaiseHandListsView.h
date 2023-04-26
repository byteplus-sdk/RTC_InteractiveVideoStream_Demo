// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>
#import "VideoChatRoomUserListtCell.h"
@class VideoChatRoomRaiseHandListsView;

NS_ASSUME_NONNULL_BEGIN

static NSString *const KClearRedNotification = @"KClearRedNotification";

@protocol VideoChatRoomRaiseHandListsViewDelegate <NSObject>

- (void)videoChatRoomRaiseHandListsView:(VideoChatRoomRaiseHandListsView *)videoChatRoomRaiseHandListsView
                            clickButton:(UIButton *)button
                                  model:(VideoChatUserModel *)model;

@end

@interface VideoChatRoomRaiseHandListsView : UIView

@property (nonatomic, copy) NSArray<VideoChatUserModel *> *dataLists;

@property (nonatomic, weak) id<VideoChatRoomRaiseHandListsViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
