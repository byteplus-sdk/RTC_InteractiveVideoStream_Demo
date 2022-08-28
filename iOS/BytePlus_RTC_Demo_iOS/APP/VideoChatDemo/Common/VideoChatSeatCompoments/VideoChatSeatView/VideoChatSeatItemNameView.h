/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSeatItemNameView : UIView

@property (nonatomic, strong) VideoChatUserModel *userModel;
@property (nonatomic, assign) BOOL isPK;

@end

NS_ASSUME_NONNULL_END
