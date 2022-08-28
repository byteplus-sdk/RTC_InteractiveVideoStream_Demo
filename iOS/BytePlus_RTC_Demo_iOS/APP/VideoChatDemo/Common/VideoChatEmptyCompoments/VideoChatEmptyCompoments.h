/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatEmptyCompoments : NSObject

- (instancetype)initWithView:(UIView *)view message:(NSString *)message;

- (void)show;

- (void)dismiss;

@end

NS_ASSUME_NONNULL_END
