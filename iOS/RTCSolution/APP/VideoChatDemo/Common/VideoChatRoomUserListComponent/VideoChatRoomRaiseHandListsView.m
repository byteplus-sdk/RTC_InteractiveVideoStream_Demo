//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatRoomRaiseHandListsView.h"
#import "VideoChatEmptyComponent.h"

@interface VideoChatRoomRaiseHandListsView () <UITableViewDelegate, UITableViewDataSource, VideoChatRoomUserListtCellDelegate>

@property (nonatomic, strong) UITableView *roomTableView;
@property (nonatomic, strong) VideoChatEmptyComponent *emptyComponent;

@end

@implementation VideoChatRoomRaiseHandListsView

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
    if (dataLists.count == 0) {
        [[NSNotificationCenter defaultCenter] postNotificationName:KClearRedNotification object:nil];
    }
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

- (void)videoChatRoomUserListtCell:(VideoChatRoomUserListtCell *)VideoChatRoomUserListtCell clickButton:(UIButton *)button model:(VideoChatUserModel *)model {
    if ([self.delegate respondsToSelector:@selector(videoChatRoomRaiseHandListsView:clickButton:model:)]) {
        [self.delegate videoChatRoomRaiseHandListsView:self clickButton:button model:model];
    }
}

#pragma mark - Getter

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
                                                                message:LocalizedString(@"video_chat_no_news")];
    }
    return _emptyComponent;
}

- (void)dealloc {
    NSLog(@"dealloc %@", NSStringFromClass([self class]));
}

@end
