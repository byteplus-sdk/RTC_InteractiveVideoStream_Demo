// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSettingItemButton : UIButton
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *imageName;
@property (nonatomic, copy) NSString *imageNameSelected;
@property (nonatomic, assign) BOOL active;
@end

NS_ASSUME_NONNULL_END
