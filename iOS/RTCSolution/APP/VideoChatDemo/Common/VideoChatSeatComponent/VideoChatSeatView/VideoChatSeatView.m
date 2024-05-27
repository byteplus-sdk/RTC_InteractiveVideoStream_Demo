//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatSeatView.h"
#import "VideoChatSeatItemView.h"

static const NSInteger MaxNumber = 6;

@interface VideoChatSeatView ()

@property (nonatomic, strong) NSMutableArray<VideoChatSeatItemView *> *itemViewLists;
@property (nonatomic, strong) GCDTimer *timer;
@property (nonatomic, copy) NSDictionary *volumeDic;

@end

@implementation VideoChatSeatView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubviewAndConstraints];
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:0.6 block:^(BOOL result) {
            [wself timerMethod];
        }];
    }
    return self;
}

- (void)setSeatList:(NSArray<VideoChatSeatModel *> *)seatList {
    _seatList = seatList;

    for (int i = 0; i < self.itemViewLists.count; i++) {
        VideoChatSeatItemView *itemView = self.itemViewLists[i];
        if (i < seatList.count) {
            itemView.seatModel = seatList[i];
        } else {
            itemView.seatModel = nil;
        }
    }
}

- (void)addSeatModel:(VideoChatSeatModel *)seatModel {
    VideoChatSeatItemView *selectItemView = nil;
    for (VideoChatSeatItemView *itemView in self.itemViewLists) {
        if (itemView.index == seatModel.index) {
            selectItemView = itemView;
            break;
        }
    }
    if (selectItemView) {
        selectItemView.seatModel = seatModel;
    }
}

- (void)removeUserModel:(VideoChatUserModel *)userModel {
    VideoChatSeatItemView *deleteItemView = nil;
    for (VideoChatSeatItemView *itemView in self.itemViewLists) {
        if ([itemView.seatModel.userModel.uid isEqualToString:userModel.uid]) {
            deleteItemView = itemView;
            break;
        }
    }
    if (deleteItemView) {
        VideoChatSeatModel *seatModel = deleteItemView.seatModel;
        seatModel.userModel = nil;
        deleteItemView.seatModel = seatModel;
    }
}

- (void)updateSeatModel:(VideoChatSeatModel *)seatModel {
    VideoChatSeatItemView *updateItemView = nil;
    for (VideoChatSeatItemView *itemView in self.itemViewLists) {
        if (itemView.index == seatModel.index) {
            updateItemView = itemView;
            break;
        }
    }
    if (updateItemView) {
        updateItemView.seatModel = seatModel;
    }
}

- (void)updateSeatVolume:(NSDictionary *)volumeDic {
    _volumeDic = volumeDic;
}

- (void)updateSeatRender:(NSString *)uid {
    VideoChatSeatItemView *updateItemView = nil;
    for (VideoChatSeatItemView *itemView in self.itemViewLists) {
        if ([itemView.seatModel.userModel.uid isEqualToString:uid]) {
            updateItemView = itemView;
            break;
        }
    }
    if (updateItemView) {
        [updateItemView updateRender];
    }
}

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid {
    for (VideoChatSeatItemView *itemView in self.itemViewLists) {
        if ([itemView.seatModel.userModel.uid isEqualToString:uid]) {
            [itemView updateNetworkQualityStstus:status];
            break;
        }
    }
}

#pragma mark - Private Action

- (void)timerMethod {
    if (_volumeDic.count > 0) {
        for (VideoChatSeatItemView *itemView in self.itemViewLists) {
            VideoChatSeatModel *tempSeatModel = itemView.seatModel;
            NSNumber *volumeValue = _volumeDic[tempSeatModel.userModel.uid];
            if (NOEmptyStr(tempSeatModel.userModel.uid) &&
                volumeValue.floatValue > 0) {
                tempSeatModel.userModel.volume = volumeValue.floatValue;
            } else {
                tempSeatModel.userModel.volume = 0;
            }
            itemView.seatModel = tempSeatModel;
        }
    }
}

- (void)addSubviewAndConstraints {
    NSMutableArray *line1List = [[NSMutableArray alloc] init];
    for (int i = 0; i < MaxNumber / 2; i++) {
        VideoChatSeatItemView *itemView = [[VideoChatSeatItemView alloc] init];
        itemView.index = i;
        [self addSubview:itemView];
        [line1List addObject:itemView];
        [self.itemViewLists addObject:itemView];

        __weak __typeof(self) wself = self;
        itemView.clickBlock = ^(VideoChatSeatModel *seatModel) {
            if (wself.clickBlock) {
                wself.clickBlock(seatModel);
            }
        };
    }
    [line1List mas_distributeViewsAlongAxis:MASAxisTypeHorizontal
                           withFixedSpacing:0
                                leadSpacing:0
                                tailSpacing:0];
    [line1List mas_updateConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self);
        make.height.mas_equalTo(SCREEN_WIDTH / 3);
    }];

    NSMutableArray *line2List = [[NSMutableArray alloc] init];
    for (int i = 0; i < MaxNumber / 2; i++) {
        VideoChatSeatItemView *itemView = [[VideoChatSeatItemView alloc] init];
        itemView.index = i + (MaxNumber / 2);
        [self addSubview:itemView];
        [line2List addObject:itemView];
        [self.itemViewLists addObject:itemView];

        __weak __typeof(self) wself = self;
        itemView.clickBlock = ^(VideoChatSeatModel *seatModel) {
            if (wself.clickBlock) {
                wself.clickBlock(seatModel);
            }
        };
    }
    [line2List mas_distributeViewsAlongAxis:MASAxisTypeHorizontal
                           withFixedSpacing:0
                                leadSpacing:0
                                tailSpacing:0];
    [line2List mas_updateConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self);
        make.height.mas_equalTo(SCREEN_WIDTH / 3);
    }];
}

#pragma mark - Getter

- (NSMutableArray<VideoChatSeatItemView *> *)itemViewLists {
    if (!_itemViewLists) {
        _itemViewLists = [[NSMutableArray alloc] init];
    }
    return _itemViewLists;
}

- (GCDTimer *)timer {
    if (!_timer) {
        _timer = [[GCDTimer alloc] init];
    }
    return _timer;
}

@end
