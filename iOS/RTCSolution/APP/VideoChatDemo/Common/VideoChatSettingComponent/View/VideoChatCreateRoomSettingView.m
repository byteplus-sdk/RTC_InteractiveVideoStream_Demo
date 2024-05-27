//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatCreateRoomSettingView.h"
#import "VideoChatSettingBitrateView.h"
#import "VideoChatSettingSingleSelectView.h"

@interface VideoChatCreateRoomSettingView ()
@property (nonatomic, strong) UILabel *titleLabel;

@property (nonatomic, strong) VideoChatSettingSingleSelectView *fpsSelectView;
@property (nonatomic, strong) VideoChatSettingSingleSelectView *resolutoinSelectView;
@property (nonatomic, strong) VideoChatSettingBitrateView *bitrateSelectView;
@property (nonatomic, strong) UIView *lineView;

@end

@implementation VideoChatCreateRoomSettingView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.backgroundColor = [UIColor colorFromRGBHexString:@"#0E0825" andAlpha:0.95 * 255];

        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.height.mas_equalTo(48);
            make.top.mas_equalTo(0);
        }];

        [self addSubview:self.fpsSelectView];
        [self.fpsSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self);
            make.top.equalTo(self.titleLabel.mas_bottom).offset(24);
            make.height.mas_equalTo(32);
        }];

        [self addSubview:self.resolutoinSelectView];
        [self.resolutoinSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.height.equalTo(self.fpsSelectView);
            make.top.equalTo(self.fpsSelectView.mas_bottom).offset(24);
        }];

        [self addSubview:self.bitrateSelectView];
        [self.bitrateSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self.fpsSelectView);
            make.top.equalTo(self.resolutoinSelectView.mas_bottom).offset(24);
            make.height.mas_equalTo(48);
        }];

        [self addSubview:self.lineView];
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self);
            make.height.mas_equalTo(1);
            make.top.equalTo(self.titleLabel.mas_bottom);
        }];

        __weak __typeof(self) wself = self;
        [self.fpsSelectView setItemChangeBlock:^(NSInteger index) {
            [wself fpsDidChanged:index];
        }];

        [self.resolutoinSelectView setItemChangeBlock:^(NSInteger index) {
            [wself resolutionDidChanged:index];
        }];

        [self.bitrateSelectView setBitrateDidChangedBlock:^(NSInteger bitrate) {
            [wself bitrateDidChanged:bitrate];
        }];
    }
    return self;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
}

- (void)setVideoConfig:(VideoChatSettingVideoConfig *)videoConfig {
    _videoConfig = videoConfig;
    [self.fpsSelectView setSelectedIndex:videoConfig.fpsType];
    [self.resolutoinSelectView setSelectedIndex:videoConfig.resolutionType];

    self.bitrateSelectView.maxBitrate = videoConfig.maxBitrate;
    self.bitrateSelectView.minBitrate = videoConfig.minBitrate;
    self.bitrateSelectView.bitrate = videoConfig.bitrate;
}

- (void)fpsDidChanged:(NSInteger)index {
    self.videoConfig.fpsType = index;

    if ([self.delegate respondsToSelector:@selector(videoChatCreateRoomSettingView:didChangefpsType:)]) {
        [self.delegate videoChatCreateRoomSettingView:self didChangefpsType:index];
    }
}

- (void)resolutionDidChanged:(NSInteger)index {
    self.videoConfig.resolutionType = index;
    self.bitrateSelectView.maxBitrate = self.videoConfig.maxBitrate;
    self.bitrateSelectView.minBitrate = self.videoConfig.minBitrate;
    self.bitrateSelectView.bitrate = self.videoConfig.bitrate;

    if ([self.delegate respondsToSelector:@selector(videoChatCreateRoomSettingView:didChangeResolution:)]) {
        [self.delegate videoChatCreateRoomSettingView:self didChangeResolution:index];
    }
}

- (void)bitrateDidChanged:(NSInteger)bitrate {
    self.videoConfig.bitrate = bitrate;
    if ([self.delegate respondsToSelector:@selector(videoChatCreateRoomSettingView:didChangeBitrate:)]) {
        [self.delegate videoChatCreateRoomSettingView:self didChangeBitrate:bitrate];
    }
}

#pragma mark - Getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.text = LocalizedString(@"settings");
        _titleLabel.font = [UIFont systemFontOfSize:16];
        _titleLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
    }
    return _titleLabel;
}

- (VideoChatSettingSingleSelectView *)fpsSelectView {
    if (!_fpsSelectView) {
        _fpsSelectView = [[VideoChatSettingSingleSelectView alloc] initWithTitle:LocalizedString(@"frame_rate") optionArray:@[@"15", @"20"]];
    }
    return _fpsSelectView;
}

- (VideoChatSettingSingleSelectView *)resolutoinSelectView {
    if (!_resolutoinSelectView) {
        _resolutoinSelectView = [[VideoChatSettingSingleSelectView alloc] initWithTitle:LocalizedString(@"resolution") optionArray:@[@"480p", @"540p", @"720p", @"1080p"]];
    }
    return _resolutoinSelectView;
}

- (VideoChatSettingBitrateView *)bitrateSelectView {
    if (!_bitrateSelectView) {
        _bitrateSelectView = [[VideoChatSettingBitrateView alloc] init];
    }
    return _bitrateSelectView;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#2A2441"];
    }
    return _lineView;
}

@end
