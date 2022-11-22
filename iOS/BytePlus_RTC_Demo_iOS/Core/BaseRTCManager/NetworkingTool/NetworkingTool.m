/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <CommonCrypto/CommonCrypto.h>
#import "NetworkingTool.h"
#import "Localizator.h"

@implementation NetworkingTool

+ (NSString *)messageFromResponseCode:(RTMStatusCode)code {
    NSString *message = @"";
    switch (code) {
        case RTMStatusCodeRoomDisbanded:
            message = CLocalizedString(@"The room is closed");
            break;
        case RTMStatusCodeSensitiveWords:
            message = CLocalizedString(@"Your comment may be uncomfortable to others. Please rethink before posting");
            break;
        case RTMStatusCodeVerificationCodeExpired:
            message = CLocalizedString(@"Verification failed. Please click Resend and try again.");
            break;
        case RTMStatusCodeInvalidVerificationCode:
            message = CLocalizedString(@"Wrong code. Please click Resend and try again.");
            break;
        case RTMStatusCodeTokenExpired:
            message = CLocalizedString(@"Login has expired. Please try to log in again.");
            break;
        case RTMStatusCodeSendMessageFaild:
        case RTMStatusCodeInternalServerError:
            message = CLocalizedString(@"Request failed. Please retry.");
            break;
        case RTMStatusCodeTransferUserOnMicExceedLimit:
            message = CLocalizedString(@"All host seats have been filled up");
            break;
        case RTMStatusCodeBuildTokenFaild:
            message = CLocalizedString(@"Generating token failed. Please try again");
            break;
        case RTMStatusCodeAPPInfoFaild:
        case RTMStatusCodeAPPInfoExistFaild:
            message = CLocalizedString(@"Failed to get RTM configuration parameters");
            break;
            
        default:
            break;
    }
    return message;
}

+ (NSString *)getWisd {
    NSString *timeStr = [NSString stringWithFormat:@"%.0f", ([[NSDate date] timeIntervalSince1970] * 1000)];
    NSString *arcStr = [NSString stringWithFormat:@"%ld", (long)arc4random()%10000];
    return [NSString stringWithFormat:@"%@%@", timeStr, arcStr];
}

+ (NSString *)getDeviceId {
    NSString *deviceId = [[NSUserDefaults standardUserDefaults] objectForKey:@"deviceId_key"];
    if (!deviceId || ![deviceId isKindOfClass:[NSString class]] || deviceId.length <= 0) {
        deviceId = [self getWisd];
        [[NSUserDefaults standardUserDefaults] setValue:deviceId forKey:@"deviceId_key"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    return deviceId;
}

+ (NSString *)MD5ForLower16Bate:(NSString *)str {
    NSString *md5Str = [self MD5ForLower32Bate:str];
    NSString *string;
    if (md5Str.length >= 24) {
        string = [md5Str substringWithRange:NSMakeRange(8, 16)];
    }
    return string;
}

+ (NSString *)MD5ForLower32Bate:(NSString *)str {
    const char *input = [str UTF8String];
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5(input, (CC_LONG)strlen(input), result);
    NSMutableString *digest = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for (NSInteger i = 0; i < CC_MD5_DIGEST_LENGTH; i++) {
        [digest appendFormat:@"%02x", result[i]];
    }
    return digest;
}

+ (NSDictionary *)decodeJsonMessage:(NSString *)message {
    NSData *jsonData = [message dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dic = nil;
    if (jsonData) {
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:NULL];
        if (![dic isKindOfClass:[NSDictionary class]]) dic = nil;
    }
    return dic;
}

@end
