/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SceneButtonModel : NSObject
@property (nonatomic, copy) NSString *iconName;
@property (nonatomic, copy) NSString *bgName;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong) NSObject *scenes;

@end

NS_ASSUME_NONNULL_END
