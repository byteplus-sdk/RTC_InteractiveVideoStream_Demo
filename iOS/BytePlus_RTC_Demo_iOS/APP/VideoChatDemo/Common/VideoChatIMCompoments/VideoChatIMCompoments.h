/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#import "VideoChatIMModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatIMCompoments : NSObject

- (instancetype)initWithSuperView:(UIView *)superView;

- (void)addIM:(VideoChatIMModel *)model;

@end

NS_ASSUME_NONNULL_END
