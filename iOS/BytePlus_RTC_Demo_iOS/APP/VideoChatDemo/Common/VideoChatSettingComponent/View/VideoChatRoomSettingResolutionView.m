/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatRoomSettingResolutionView.h"

@interface VideoChatRoomSettingResolutionView ()

@property (nonatomic, strong) UILabel *titleLabel;

@property (nonatomic, strong) UIButton *backButton;

@property (nonatomic, strong) UIButton *selectedButton;

@property (nonatomic, strong) NSMutableArray *buttons;

@end

@implementation VideoChatRoomSettingResolutionView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];

        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
          make.centerX.equalTo(self);
          make.top.mas_equalTo(16);
        }];

        [self addSubview:self.backButton];
        [self.backButton mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.mas_equalTo(20);
          make.centerY.equalTo(self.titleLabel);
          make.width.mas_equalTo(15);
          make.height.mas_equalTo(27);
        }];

        NSArray *items = @[ @"480p", @"540p", @"720p", @"1080p" ];

        for (int i = 0; i < items.count; i++) {
            NSString *title = items[i];
            UIButton *button = [[UIButton alloc] init];

            UIColor *color = [UIColor colorFromHexString:@"#86909C"];
            [button setTitleColor:color forState:UIControlStateNormal];
            button.layer.borderColor = color.CGColor;
            button.layer.cornerRadius = 5;
            button.layer.borderWidth = 1;
            button.titleLabel.font = [UIFont systemFontOfSize:14];

            button.tag = i;
            [button setTitle:title forState:UIControlStateNormal];
            [button addTarget:self action:@selector(itemButtonClicked:) forControlEvents:UIControlEventTouchUpInside];

            [self addSubview:button];

            [button mas_makeConstraints:^(MASConstraintMaker *make) {
              make.centerX.equalTo(self).multipliedBy(0.5 * i + 0.25);
              make.top.equalTo(self.titleLabel.mas_bottom).offset(32);
              make.width.mas_equalTo(64);
              make.height.mas_equalTo(32);
            }];

            [self.buttons addObject:button];
        }
    }
    return self;
}

- (void)setSelectedResKey:(NSString *)resKey {
    NSInteger res = [resKey integerValue];
    NSInteger selectedIndex = 0;
    switch (res) {
        case 480: {
            selectedIndex = 0;
        } break;
        case 540: {
            selectedIndex = 1;
        } break;
        case 720: {
            selectedIndex = 2;
        } break;
        case 1080: {
            selectedIndex = 3;
        } break;

        default: {
            selectedIndex = 2;
        } break;
    }

    UIButton *button = self.buttons[selectedIndex];
    [self selectButton:button];
}

- (void)selectButton:(UIButton *)sender {
    UIColor *color = [UIColor colorFromHexString:@"#86909C"];
    self.selectedButton.layer.borderColor = color.CGColor;
    [self.selectedButton setTitleColor:color forState:UIControlStateNormal];

    sender.layer.borderColor = [UIColor colorFromHexString:@"#165DFF"].CGColor;
    [sender setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    self.selectedButton = sender;
}

- (void)itemButtonClicked:(UIButton *)sender {
    [self selectButton:sender];

    if (self.resolutionChangeBlock) {
        self.resolutionChangeBlock(sender.tag);
    }
}

- (void)close {
    self.hidden = YES;
}
#pragma mark - getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.text = LocalizedString(@"Resolution");
        _titleLabel.font = [UIFont systemFontOfSize:16];
        _titleLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
    }
    return _titleLabel;
}

- (UIButton *)backButton {
    if (!_backButton) {
        _backButton = [[UIButton alloc] init];
        [_backButton setImage:[UIImage imageNamed:@"InteractiveVideoChat_setting_back" bundleName:HomeBundleName] forState:UIControlStateNormal];
        [_backButton addTarget:self action:@selector(close) forControlEvents:UIControlEventTouchUpInside];
    }
    return _backButton;
}

- (NSMutableArray *)buttons {
    if (!_buttons) {
        _buttons = [[NSMutableArray alloc] init];
    }
    return _buttons;
}
@end
