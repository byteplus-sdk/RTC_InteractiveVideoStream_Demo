/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>
#import "VideoChatRoomItemButton.h"
@class VideoChatRoomBottomView;

typedef NS_ENUM(NSInteger, VideoChatRoomBottomStatus) {
    VideoChatRoomBottomStatusPhone = 0,
    VideoChatRoomBottomStatusBeauty,
    VideoChatRoomBottomStatusSet,
    VideoChatRoomBottomStatusInput,
    VideoChatRoomBottomStatusPK,
};

@protocol VideoChatRoomBottomViewDelegate <NSObject>

- (void)videoChatRoomBottomView:(VideoChatRoomBottomView *_Nonnull)videoChatRoomBottomView
                     itemButton:(VideoChatRoomItemButton *_Nullable)itemButton
                didSelectStatus:(VideoChatRoomBottomStatus)status;

@end

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomBottomView : UIView

@property (nonatomic, weak) id<VideoChatRoomBottomViewDelegate> delegate;
@property (nonatomic, assign) VideoChatRoomMode chatRoomMode;

- (void)updateBottomLists:(VideoChatUserModel *)userModel;

- (void)updateBottomListsWithPK:(BOOL)isPKing;

- (void)updateBottomLists:(VideoChatUserModel *)userModel isPKing:(BOOL)isPKing;

- (void)updateButtonStatus:(VideoChatRoomBottomStatus)status isSelect:(BOOL)isSelect;

- (void)updateButtonStatus:(VideoChatRoomBottomStatus)status isRed:(BOOL)isRed;

- (void)audienceResetBottomLists;

@end

NS_ASSUME_NONNULL_END
