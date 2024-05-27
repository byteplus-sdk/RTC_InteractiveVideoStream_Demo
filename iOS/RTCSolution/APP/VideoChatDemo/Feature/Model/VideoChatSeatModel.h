//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatUserModel.h"
#import <Foundation/Foundation.h>

@interface VideoChatSeatModel : NSObject

// status. 0 : close seat, 1 : open seat
@property (nonatomic, assign) NSInteger status;

@property (nonatomic, assign) NSInteger index;

@property (nonatomic, strong) VideoChatUserModel *userModel;

@end
