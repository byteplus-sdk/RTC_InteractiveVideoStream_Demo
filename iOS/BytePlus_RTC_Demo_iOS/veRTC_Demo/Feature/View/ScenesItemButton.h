/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>
#import "SceneButtonModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ScenesItemButton : UIButton
@property (nonatomic, assign) SceneButtonModel *model;
- (void)addItemLayer;

@end

NS_ASSUME_NONNULL_END
