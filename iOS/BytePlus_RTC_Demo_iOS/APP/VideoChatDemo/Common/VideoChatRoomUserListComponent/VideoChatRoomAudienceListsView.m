/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomAudienceListsView.h"
#import "VideoChatEmptyComponent.h"

@interface VideoChatRoomAudienceListsView ()<UITableViewDelegate, UITableViewDataSource, VideoChatRoomUserListtCellDelegate>

@property (nonatomic, strong) UITableView *roomTableView;
@property (nonatomic, strong) VideoChatEmptyComponent *emptyComponent;

@end


@implementation VideoChatRoomAudienceListsView


- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.roomTableView];
        [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setDataLists:(NSArray *)dataLists {
    _dataLists = dataLists;
    
    [self.roomTableView reloadData];
    if (dataLists.count <= 0) {
        [self.emptyComponent show];
    } else {
        [self.emptyComponent dismiss];
    }
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    VideoChatRoomUserListtCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoChatRoomUserListtCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.model = self.dataLists[indexPath.row];
    cell.delegate = self;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60;
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataLists.count;
}

#pragma mark - VideoChatRoomUserListtCellDelegate

- (void)VideoChatRoomUserListtCell:(VideoChatRoomUserListtCell *)VideoChatRoomUserListtCell clickButton:(nonnull UIButton *)button model:(nonnull id)model {
    if ([self.delegate respondsToSelector:@selector(VideoChatRoomAudienceListsView:clickButton:model:)]) {
        [self.delegate VideoChatRoomAudienceListsView:self clickButton:button model:model];
    }
}

#pragma mark - getter

- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:VideoChatRoomUserListtCell.class forCellReuseIdentifier:@"videoChatRoomUserListtCellID"];
        _roomTableView.backgroundColor = [UIColor clearColor];
    }
    return _roomTableView;
}

- (VideoChatEmptyComponent *)emptyComponent {
    if (!_emptyComponent) {
        _emptyComponent = [[VideoChatEmptyComponent alloc] initWithView:self
                                                                  message:LocalizedString(@"No audience")];
    }
    return _emptyComponent;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
