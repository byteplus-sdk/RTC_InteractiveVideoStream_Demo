/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseHomeDemo : NSObject

- (void)pushDemoViewControllerBlock:(void (^)(BOOL result))block;

@end

NS_ASSUME_NONNULL_END
