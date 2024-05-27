//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "SceneButtonModel.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScenesItemButton : UIButton

@property (nonatomic, assign) SceneButtonModel *model;

- (void)addItemLayer;

@end

NS_ASSUME_NONNULL_END
