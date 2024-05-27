//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatSettingSingleSelectView.h"

@interface VideoChatSettingSingleSelectView ()
@property (nonatomic, strong) UILabel *leftLabel;

@property (nonatomic, strong) UIButton *selectedButton;

@property (nonatomic, strong) NSMutableArray *buttons;
@end

@implementation VideoChatSettingSingleSelectView

- (instancetype)initWithTitle:(NSString *)title optionArray:(NSArray *)optionArray {
    if (self = [super init]) {
        self.leftLabel.text = title;
        [self addSubview:self.leftLabel];
        [self.leftLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(16);
            make.width.mas_equalTo(60);
            make.centerY.equalTo(self);
        }];

        __block __weak UIButton *lastButton;

        for (int i = 0; i < optionArray.count; i++) {
            NSString *text = optionArray[i];

            UIButton *button = [[UIButton alloc] init];

            UIColor *color = [UIColor colorFromHexString:@"#86909C"];
            [button setTitleColor:color forState:UIControlStateNormal];
            button.layer.borderColor = color.CGColor;
            button.layer.cornerRadius = 5;
            button.layer.borderWidth = 1;
            button.titleLabel.font = [UIFont systemFontOfSize:14];

            button.tag = i;
            [button setTitle:text forState:UIControlStateNormal];
            [button addTarget:self action:@selector(itemButtonClicked:) forControlEvents:UIControlEventTouchUpInside];

            [self addSubview:button];

            [button mas_makeConstraints:^(MASConstraintMaker *make) {
                if (i == 0) {
                    make.left.mas_equalTo(80);
                } else {
                    make.left.equalTo(lastButton.mas_right).offset(8);
                }
                lastButton = button;

                make.centerY.equalTo(self.leftLabel);
                make.width.equalTo(self.mas_width).multipliedBy(0.25).offset(-30);
                make.height.mas_equalTo(30);
            }];

            if (i == 0) {
                [self itemButtonClicked:button];
                self.selectedButton = button;
            }

            [self.buttons addObject:button];
        }
    }
    return self;
}

- (void)setSelectedIndex:(NSInteger)selectedIndex {
    UIButton *button = self.buttons[selectedIndex];
    [self itemButtonClicked:button];
}

- (void)itemButtonClicked:(UIButton *)sender {
    UIColor *color = [UIColor colorFromHexString:@"#86909C"];
    self.selectedButton.layer.borderColor = color.CGColor;
    [self.selectedButton setTitleColor:color forState:UIControlStateNormal];

    sender.layer.borderColor = [UIColor colorFromHexString:@"#165DFF"].CGColor;
    [sender setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    self.selectedButton = sender;
    if (self.itemChangeBlock) {
        self.itemChangeBlock(sender.tag);
    }
}

#pragma mark - Getter

- (UILabel *)leftLabel {
    if (!_leftLabel) {
        _leftLabel = [[UILabel alloc] init];
        _leftLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _leftLabel.font = [UIFont systemFontOfSize:16];
        _leftLabel.adjustsFontSizeToFitWidth = YES;
    }
    return _leftLabel;
}

- (NSMutableArray *)buttons {
    if (!_buttons) {
        _buttons = [[NSMutableArray alloc] init];
    }
    return _buttons;
}
@end
