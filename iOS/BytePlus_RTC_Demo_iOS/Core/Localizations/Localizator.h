/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef HomeBundleName
#define HomeBundleName @""
#endif

#define LocalizedString(key) LocalizedStringFromBundle(key, HomeBundleName)
#define LocalizedStringFromBundle(key, bundle) \
        [Localizator localizedStringForKey:(key) bundleName:bundle]

@interface Localizator : NSObject

+ (NSString *)localizedStringForKey:(NSString *)key bundleName:(nullable NSString *)bundleName;

@end

NS_ASSUME_NONNULL_END
