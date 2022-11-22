/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "JoinRTSInputModel.h"
#import "JoinRTSParamsModel.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JoinRTSParams : NSObject

/*
 * Get RTS login information
 * @param Input data model
 * @param block callback
 */
+ (void)getJoinRTSParams:(JoinRTSInputModel *)inputModel
                   block:(void (^)(JoinRTSParamsModel *model))block;

/*
 * Network request public parameter usage
 * @param dic Dic parameter, can be nil
 */
+ (NSDictionary *)addTokenToParams:(NSDictionary *_Nullable)dic;

@end

NS_ASSUME_NONNULL_END
