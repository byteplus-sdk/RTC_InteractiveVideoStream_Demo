//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "BaseIMModel.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseIMComponent : NSObject

- (instancetype)initWithSuperView:(UIView *)superView;

- (void)addIM:(BaseIMModel *)model;

- (void)updaetHidden:(BOOL)isHidden;

- (void)updateUserInteractionEnabled:(BOOL)isEnabled;

@end

NS_ASSUME_NONNULL_END
