//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatSeatItemButton.h"

@interface VideoChatSeatItemButton ()

@property (nonatomic, strong) UILabel *desLabel;

@end

@implementation VideoChatSeatItemButton

- (instancetype)init {
    self = [super init];
    if (self) {
        self.clipsToBounds = NO;

        [self addSubview:self.desLabel];
        [self.desLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self).offset(0);
            make.centerX.equalTo(self);
        }];
    }
    return self;
}

- (void)setDesTitle:(NSString *)desTitle {
    _desTitle = desTitle;

    self.desLabel.text = desTitle;
}

#pragma mark - Getter

- (UILabel *)desLabel {
    if (!_desLabel) {
        _desLabel = [[UILabel alloc] init];
        _desLabel.textColor = [UIColor colorFromHexString:@"#FFFFFF"];
        _desLabel.font = [UIFont systemFontOfSize:12];
    }
    return _desLabel;
}

@end
