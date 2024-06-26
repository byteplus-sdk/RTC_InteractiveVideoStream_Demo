//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ToastViewContentType) {
    ToastViewContentTypeNone,
    ToastViewContentTypeMeesage,
    ToastViewContentTypeActivityIndicator,
};

@interface ToastView : UIView

@property (nonatomic, assign) ToastViewContentType contentType;

- (void)setMeesage:(NSString *)message;

- (void)startLoading;
- (void)stopLoaidng;

@end

NS_ASSUME_NONNULL_END
