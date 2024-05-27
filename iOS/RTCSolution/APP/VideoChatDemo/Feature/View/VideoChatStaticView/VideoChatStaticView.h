//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatStaticView : NSObject

@property (nonatomic, strong) VideoChatRoomModel *roomModel;
@property (nonatomic, copy) void (^quitLiveBlock)(void);

- (instancetype)initWithSuperView:(UIView *)superView;
- (void)updatePeopleNum:(NSInteger)count;

@end

NS_ASSUME_NONNULL_END
