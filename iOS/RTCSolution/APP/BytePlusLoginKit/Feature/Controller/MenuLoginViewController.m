// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "MenuLoginViewController.h"
#import "MenuCreateTextFieldView.h"
#import "PhonePrivacyView.h"
#import "LoginControlComponent.h"
#import "BuildConfig.h"

@interface MenuLoginViewController ()

@property (nonatomic, strong) UIImageView *maskImageView;
@property (nonatomic, strong) UILabel *appTitleLable;
@property (nonatomic, strong) MenuCreateTextFieldView *userNameTextFieldView;
@property (nonatomic, strong) UIButton *loginButton;
@property (nonatomic, strong) PhonePrivacyView *privacyView;
@property (nonatomic, strong) UILabel *verLabel;

@end

@implementation MenuLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [self addMakeConstraints];
    
    __weak __typeof(self) wself = self;
    self.userNameTextFieldView.textFieldChangeBlock = ^(NSString * _Nonnull text) {
        [wself updateLoginButtonStatus];
    };
    self.privacyView.changeAgree = ^(BOOL isAgree) {
        [wself updateLoginButtonStatus];
    };
    [self updateLoginButtonStatus];
    
    NSString *sdkVer = [BaseRTCManager getSdkVersion];
    NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    self.verLabel.text = [NSString stringWithFormat:@"%@ v%@ / %@ v%@", LocalizedString(@"App Version"), appVer, LocalizedString(@"SDK Version"), sdkVer];
}

#pragma mark - Private Action

- (void)keyBoardDidShow:(NSNotification *)notifiction {
    CGRect keyboardRect = [[notifiction.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    [UIView animateWithDuration:0.25 animations:^{
        [self.loginButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-keyboardRect.size.height - 80/2);
        }];
    }];
    self.appTitleLable.hidden = SCREEN_WIDTH <= 320 ? YES : NO;
    [self.view layoutIfNeeded];
}

- (void)keyBoardDidHide:(NSNotification *)notifiction {
    [UIView animateWithDuration:0.25 animations:^{
        [self.loginButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-(SCREEN_HEIGHT * 0.3) - [DeviceInforTool getVirtualHomeHeight]);
        }];
    }];
    self.appTitleLable.hidden = NO;
    [self.view layoutIfNeeded];
}

- (void)loginButtonAction:(UIButton *)sender {
    NSAssert(NOEmptyStr(HeadUrl), @"Missing Login Url! Please configure information at BuildConfig.h");
    __weak __typeof(self) wself = self;
    [[ToastComponent shareToastComponent] showLoading];
    [LoginControlComponent passwordFreeLogin:self.userNameTextFieldView.text
                                        block:^(BOOL result, NSString * _Nullable errorStr) {
        [[ToastComponent shareToastComponent] dismiss];
        if (result) {
            [wself dismissViewControllerAnimated:YES completion:^{
                
            }];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:errorStr];
        }
    }];
}

- (void)maskAction {
    [self.userNameTextFieldView resignFirstResponder];
}

#pragma mark - Private Action

- (void)updateLoginButtonStatus {
    BOOL isDisable = YES;
    BOOL isIllega = NO;
    isDisable = IsEmptyStr(self.userNameTextFieldView.text);
    isIllega = self.userNameTextFieldView.isIllega;
    BOOL isAgree = self.privacyView.isAgree;
    if (isDisable || isIllega || !isAgree) {
        self.loginButton.userInteractionEnabled = NO;
        self.loginButton.backgroundColor = [UIColor colorFromRGBHexString:@"#4080FF" andAlpha:0.3 * 255];
        [self.loginButton setTitleColor:[UIColor colorFromRGBHexString:@"#ffffff" andAlpha:0.3 * 255] forState:UIControlStateNormal];
    } else {
        self.loginButton.userInteractionEnabled = YES;
        self.loginButton.backgroundColor = [UIColor colorFromHexString:@"#0E42D2"];
        [self.loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
}

- (void)addMakeConstraints {
    [self.view addSubview:self.maskImageView];
    [self.maskImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.appTitleLable];
    [self.appTitleLable mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(100 + [DeviceInforTool getStatusBarHight]);
    }];
    
    [self.view addSubview:self.loginButton];
    [self.loginButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(30);
        make.right.mas_equalTo(-30);
        make.height.mas_equalTo(50);
        make.bottom.equalTo(self.view).offset(-(SCREEN_HEIGHT * 0.3) - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.userNameTextFieldView];
    [self.userNameTextFieldView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(30);
        make.right.mas_equalTo(-30);
        make.height.mas_equalTo(32);
        make.bottom.equalTo(self.loginButton.mas_top).offset(-94);
    }];
    
    [self.view addSubview:self.privacyView];
    [self.privacyView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(304, 22));
        make.left.equalTo(self.userNameTextFieldView);
        make.top.equalTo(self.userNameTextFieldView.mas_bottom).offset(32);
    }];
    
    [self.view addSubview:self.verLabel];
    [self.verLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-([DeviceInforTool getVirtualHomeHeight] + 20));
    }];
}

#pragma mark - Getter

- (MenuCreateTextFieldView *)userNameTextFieldView {
    if (!_userNameTextFieldView) {
        _userNameTextFieldView = [[MenuCreateTextFieldView alloc] initWithModify:NO];
        _userNameTextFieldView.placeholderStr = LocalizedString(@"Username");
        _userNameTextFieldView.maxLimit = 18;
    }
    return _userNameTextFieldView;
}

- (UIImageView *)maskImageView {
    if (!_maskImageView) {
        _maskImageView = [[UIImageView alloc] init];
        _maskImageView.image = [UIImage imageNamed:@"menu_mask" bundleName:HomeBundleName];
        _maskImageView.contentMode = UIViewContentModeScaleAspectFill;
        _maskImageView.clipsToBounds = YES;
        
        UIView *view = [[UIView alloc] init];
        view.userInteractionEnabled = NO;
        view.backgroundColor = [UIColor colorFromRGBHexString:@"#141C2C" andAlpha:0.7 * 255];
        [_maskImageView addSubview:view];
        [view mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_maskImageView);
        }];
        
        _maskImageView.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(maskAction)];
        [_maskImageView addGestureRecognizer:tap];
    }
    return _maskImageView;
}

- (UILabel *)appTitleLable {
    if (!_appTitleLable) {
        _appTitleLable = [[UILabel alloc] init];
        _appTitleLable.text = @"BytePlus RTC";
        _appTitleLable.textColor = [UIColor whiteColor];
        _appTitleLable.font = [UIFont systemFontOfSize:28 weight:UIFontWeightBold];
    }
    return _appTitleLable;
}

- (UIButton *)loginButton {
    if (!_loginButton) {
        _loginButton = [[UIButton alloc] init];
        _loginButton.layer.masksToBounds = YES;
        _loginButton.layer.cornerRadius = 50/2;
        [_loginButton setTitle:LocalizedString(@"Log in") forState:UIControlStateNormal];
        _loginButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_loginButton addTarget:self action:@selector(loginButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _loginButton;
}

- (PhonePrivacyView *)privacyView {
    if (!_privacyView) {
        _privacyView = [[PhonePrivacyView alloc] init];
    }
    return _privacyView;
}

- (UILabel *)verLabel {
    if (!_verLabel) {
        _verLabel = [[UILabel alloc] init];
        _verLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
        _verLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    }
    return _verLabel;
}

- (void)dealloc {

}

@end
