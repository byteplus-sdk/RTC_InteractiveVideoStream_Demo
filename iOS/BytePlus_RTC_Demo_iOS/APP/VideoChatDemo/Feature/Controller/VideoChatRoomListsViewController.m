/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
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
    self.bgView.hidden = NO;
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
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navTitle = LocalizedString(@"Interactive Video streaming");
    [self.rightButton setImage:[UIImage imageNamed:@"edu_refresh" bundleName:HomeBundleName] forState:UIControlStateNormal];
    
    [self loadDataWithGetLists];
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
    
    [VideoChatRTMManager clearUser:^(RTMACKModel * _Nonnull model) {
        [VideoChatRTMManager getActiveLiveRoomListWithBlock:^(NSArray<VideoChatRoomModel *> * _Nonnull roomList, RTMACKModel * _Nonnull model) {
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
    NSString *roomName = [NSString stringWithFormat:LocalizedString(@"%@'s room"), [LocalUserComponent userModel].name];
    [[ToastComponent shareToastComponent] showLoading];
    [VideoChatRTMManager createRoom:roomName
                                  userName:[LocalUserComponent userModel].name
                               bgImageName:@""
                                     block:^(NSString * _Nonnull RTCToken,
                                             VideoChatRoomModel * _Nonnull roomModel,
                                             VideoChatUserModel * _Nonnull hostUserModel,
                                             RTMACKModel * _Nonnull model) {
        if (model.result) {
            [[ToastComponent shareToastComponent] dismiss];
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

#pragma mark - getter

- (UIButton *)createButton {
    if (!_createButton) {
        _createButton = [[UIButton alloc] init];
        _createButton.backgroundColor = [UIColor colorFromHexString:@"#4080FF"];
        [_createButton addTarget:self action:@selector(createButtonAction) forControlEvents:UIControlEventTouchUpInside];
        _createButton.layer.cornerRadius = 25;
        _createButton.layer.masksToBounds = YES;
        _createButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        _createButton.adjustsImageWhenHighlighted = NO;
        [_createButton setImage:[UIImage imageNamed:@"video_add" bundleName:HomeBundleName] forState:UIControlStateNormal];
        [_createButton setTitle:LocalizedString(@"Create a Room") forState:UIControlStateNormal];
        [_createButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [_createButton setImageEdgeInsets:UIEdgeInsetsMake(0, -4, 0, 4)];
        [_createButton setTitleEdgeInsets:UIEdgeInsetsMake(0, 4, 0, -4)];
        [_createButton setContentEdgeInsets:UIEdgeInsetsMake(0, 15, 0, 15)];
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
