//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "ToolKit.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseViewController : UIViewController

@property (nonatomic, strong) UIView *navView;

@property (nonatomic, copy) NSString *navTitle;

@property (nonatomic, copy) NSString *navRightTitle;

@property (nonatomic, strong) UIImage *navLeftImage;

@property (nonatomic, strong) UIImage *navRightImage;

- (void)rightButtonAction:(BaseButton *)sender;

@end

NS_ASSUME_NONNULL_END
