/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatIMComponent.h"
#import "VideoChatIMView.h"

@interface VideoChatIMComponent ()

@property (nonatomic, strong) VideoChatIMView *VideoChatIMView;

@end

@implementation VideoChatIMComponent

- (instancetype)initWithSuperView:(UIView *)superView {
    self = [super init];
    if (self) {
        [superView addSubview:self.VideoChatIMView];
        [self.VideoChatIMView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(16);
            make.right.mas_equalTo(-16);
            make.bottom.mas_equalTo(-101 - ([DeviceInforTool getVirtualHomeHeight]));
            
            CGFloat seatHeight = SCREEN_WIDTH / 3 * 2;
            CGFloat seatTop = 72 + [DeviceInforTool getStatusBarHight];
            make.top.mas_equalTo(seatHeight + seatTop + 40);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)addIM:(VideoChatIMModel *)model {
    NSMutableArray *datas = [[NSMutableArray alloc] initWithArray:self.VideoChatIMView.dataLists];
    [datas addObject:model];
    self.VideoChatIMView.dataLists = [datas copy];
}

#pragma mark - getter

- (VideoChatIMView *)VideoChatIMView {
    if (!_VideoChatIMView) {
        _VideoChatIMView = [[VideoChatIMView alloc] init];
    }
    return _VideoChatIMView;
}

@end
