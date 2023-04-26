// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>
#import "VideoChatRoomCell.h"
@class VideoChatRoomTableView;

NS_ASSUME_NONNULL_BEGIN

@protocol VideoChatRoomTableViewDelegate <NSObject>

- (void)VideoChatRoomTableView:(VideoChatRoomTableView *)VideoChatRoomTableView didSelectRowAtIndexPath:(VideoChatRoomModel *)model;

@end

@interface VideoChatRoomTableView : UIView

@property (nonatomic, copy) NSArray *dataLists;

@property (nonatomic, weak) id<VideoChatRoomTableViewDelegate> delegate;


@end

NS_ASSUME_NONNULL_END
