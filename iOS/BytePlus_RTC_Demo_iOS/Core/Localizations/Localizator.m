/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "Localizator.h"

@interface Localizator ()

@end

@implementation Localizator

+ (NSString *)localizedStringForKey:(NSString *)key bundleName:(NSString *)bundleName {
    NSBundle *resourceBundle = nil;
    if (bundleName == nil || bundleName.length == 0) {
        resourceBundle = [NSBundle mainBundle];
    } else {
        NSString *bundlePath = [[[NSBundle mainBundle] pathForResource:bundleName ofType:@"bundle"] stringByAppendingPathComponent:@"Localizable.bundle"];
        resourceBundle = [NSBundle bundleWithPath:bundlePath];
    }
    return [resourceBundle localizedStringForKey:key value:@"" table:nil];
}

@end
