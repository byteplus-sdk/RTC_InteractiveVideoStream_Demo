//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSettingSingleSelectView : UIView
@property (nonatomic, copy) void (^itemChangeBlock)(NSInteger index);

- (instancetype)initWithTitle:(NSString *)title optionArray:(NSArray *)optionArray;

- (void)setSelectedIndex:(NSInteger)selectedIndex;
@end

NS_ASSUME_NONNULL_END
