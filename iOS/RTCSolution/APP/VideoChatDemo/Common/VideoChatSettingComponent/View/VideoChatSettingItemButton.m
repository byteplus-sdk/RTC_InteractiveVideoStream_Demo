//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatSettingItemButton.h"

@interface VideoChatSettingItemButton ()

@property (nonatomic, strong) UIView *bgView;

@property (nonatomic, strong) UIImageView *iconView;

@property (nonatomic, strong) UILabel *label;

@end

@implementation VideoChatSettingItemButton

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.active = YES;

        [self addSubview:self.bgView];
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.mas_equalTo(0);
            make.centerX.equalTo(self);
            make.width.height.mas_equalTo(44);
        }];

        [self.bgView addSubview:self.iconView];
        [self.iconView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self.bgView);
        }];

        [self addSubview:self.label];
        [self.label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.top.equalTo(self.bgView.mas_bottom).offset(8);
        }];

        [self addTarget:self action:@selector(touchDown) forControlEvents:UIControlEventTouchDown];
        [self addTarget:self action:@selector(touchDown) forControlEvents:UIControlEventTouchUpInside];
        [self addTarget:self action:@selector(touchUp) forControlEvents:UIControlEventTouchUpInside];
        [self addTarget:self action:@selector(touchUp) forControlEvents:UIControlEventTouchCancel];
        [self addTarget:self action:@selector(touchUp) forControlEvents:UIControlEventTouchUpOutside];
    }
    return self;
}

- (void)touchDown {
    self.iconView.alpha = 0.6;
}

- (void)touchUp {
    self.iconView.alpha = 1.0;
}

- (void)setImageName:(NSString *)imageName {
    _imageName = imageName;
    self.iconView.image = [UIImage imageNamed:imageName bundleName:HomeBundleName];
}

- (void)setImageNameSelected:(NSString *)imageNameSelected {
    _imageNameSelected = imageNameSelected;
}

- (void)setTitle:(NSString *)title {
    _title = title;
    self.label.text = title;
}

- (void)setSelected:(BOOL)selected {
    [super setSelected:selected];

    if (selected && self.imageNameSelected.length) {
        self.iconView.image = [UIImage imageNamed:self.imageNameSelected bundleName:HomeBundleName];
    }

    if (!selected && self.imageName.length) {
        self.iconView.image = [UIImage imageNamed:self.imageName bundleName:HomeBundleName];
    }
}

- (void)setActive:(BOOL)active {
    _active = active;
    if (active) {
        self.label.textColor = [UIColor whiteColor];
    } else {
        self.label.textColor = [UIColor colorFromHexString:@"#86909C"];
    }
}

#pragma mark - Getter

- (UILabel *)label {
    if (!_label) {
        _label = [[UILabel alloc] init];
        _label.font = [UIFont systemFontOfSize:12];
        _label.userInteractionEnabled = NO;
        _label.textColor = [UIColor whiteColor];
    }
    return _label;
}

- (UIImageView *)iconView {
    if (!_iconView) {
        _iconView = [[UIImageView alloc] init];
        _iconView.userInteractionEnabled = NO;
    }
    return _iconView;
}

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.userInteractionEnabled = NO;
        _bgView.layer.cornerRadius = 44 * 0.5;
        _bgView.layer.masksToBounds = YES;
        _bgView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
    }
    return _bgView;
}

@end
