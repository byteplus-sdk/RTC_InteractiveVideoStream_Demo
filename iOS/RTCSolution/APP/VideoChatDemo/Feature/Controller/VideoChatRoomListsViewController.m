// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatRoomListsViewController.h"
#import "VideoChatCreateRoomViewController.h"
#import "VideoChatRoomViewController.h"
#import "VideoChatRoomTableView.h"

@interface VideoChatRoomListsViewController () <VideoChatRoomTableViewDelegate>

@property (nonatomic, strong) UIButton *createButton;
@property (nonatomic, strong) VideoChatRoomTableView *roomTableView;
@property (nonatomic, copy) NSString *currentAppid;

@end

@implementation VideoChatRoomListsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navView.backgroundColor = [UIColor clearColor];
    
    [self.view addSubview:self.roomTableView];
    [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(self.view);
        make.top.equalTo(self.navView.mas_bottom);
    }];
    
    [self.view addSubview:self.createButton];
    [self.createButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(171, 50));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(- 48 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self loadDataWithGetLists];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navTitle = LocalizedString(@"video_chat");
    self.navRightImage = [UIImage imageNamed:@"edu_refresh" bundleName:HomeBundleName];
}

- (void)rightButtonAction:(BaseButton *)sender {
    [super rightButtonAction:sender];
    
    [self loadDataWithGetLists];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
}

#pragma mark - load data

- (void)loadDataWithGetLists {
    __weak __typeof(self) wself = self;
    
    [[ToastComponent shareToastComponent] showLoading];
    [VideoChatRTSManager clearUser:^(RTSACKModel * _Nonnull model) {
        [VideoChatRTSManager getActiveLiveRoomListWithBlock:^(NSArray<VideoChatRoomModel *> * _Nonnull roomList, RTSACKModel * _Nonnull model) {
            [[ToastComponent shareToastComponent] dismiss];
            if (model.result) {
                wself.roomTableView.dataLists = roomList;
            } else {
                wself.roomTableView.dataLists = @[];
                [[ToastComponent shareToastComponent] showWithMessage:model.message];
            }
        }];
    }];
}

#pragma mark - VideoChatRoomTableViewDelegate

- (void)VideoChatRoomTableView:(VideoChatRoomTableView *)VideoChatRoomTableView didSelectRowAtIndexPath:(VideoChatRoomModel *)model {
    [PublicParameterComponent share].roomId = model.roomID;
    VideoChatRoomViewController *next = [[VideoChatRoomViewController alloc]
                                         initWithRoomModel:model];
    [self.navigationController pushViewController:next animated:YES];
}

#pragma mark - Touch Action

- (void)createButtonAction {
    __weak __typeof(self) wself = self;
    NSString *roomName = [NSString stringWithFormat:LocalizedString(@"video_chat_%@_live"), [LocalUserComponent userModel].name];
    [[ToastComponent shareToastComponent] showLoading];
    [VideoChatRTSManager createRoom:roomName
                                  userName:[LocalUserComponent userModel].name
                               bgImageName:@""
                                     block:^(NSString * _Nonnull RTCToken,
                                             VideoChatRoomModel * _Nonnull roomModel,
                                             VideoChatUserModel * _Nonnull hostUserModel,
                                             RTSACKModel * _Nonnull model) {
        [[ToastComponent shareToastComponent] dismiss];
        if (model.result) {
            VideoChatCreateRoomViewController *next = [[VideoChatCreateRoomViewController alloc]
                                                       initWithRoomModel:roomModel
                                                       userModel:hostUserModel
                                                       rtcToekn:RTCToken];
            [wself.navigationController pushViewController:next animated:YES];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:model.message];
        }
    }];
}

#pragma mark - Getter

- (UIButton *)createButton {
    if (!_createButton) {
        _createButton = [[UIButton alloc] init];
        _createButton.backgroundColor = [UIColor colorFromHexString:@"#4080FF"];
        [_createButton addTarget:self action:@selector(createButtonAction) forControlEvents:UIControlEventTouchUpInside];
        _createButton.layer.cornerRadius = 25;
        _createButton.layer.masksToBounds = YES;
        
        UIView *contentView = [[UIView alloc] init];
        contentView.backgroundColor = [UIColor redColor];
        [_createButton addSubview:contentView];
        [contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_createButton);
        }];
        
        UIImageView *iconImageView = [[UIImageView alloc] init];
        iconImageView.image = [UIImage imageNamed:@"video_add" bundleName:HomeBundleName];
        [contentView addSubview:iconImageView];
        [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(20, 20));
            make.centerY.equalTo(_createButton);
            make.left.equalTo(contentView);
        }];
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.text = LocalizedString(@"video_chat_create_room");
        titleLabel.textColor = [UIColor whiteColor];
        titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [contentView addSubview:titleLabel];
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(_createButton);
            make.left.equalTo(iconImageView.mas_right).offset(10);
            make.right.equalTo(contentView);
        }];
    }
    return _createButton;
}

- (VideoChatRoomTableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[VideoChatRoomTableView alloc] init];
        _roomTableView.delegate = self;
    }
    return _roomTableView;
}

- (void)dealloc {
    [[VideoChatRTCManager shareRtc] disconnect];
    [PublicParameterComponent clear];
}


@end
