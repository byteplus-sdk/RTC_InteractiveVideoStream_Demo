/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room Internal API
*/

@interface RTCRoom ()

- (instancetype _Nonnull)initWithRtcRoom:(bytertc::IRTCRoom *_Nonnull)rtcRoom roomId:(NSString *_Nonnull)roomId;

- (void)enableSubscribeSelf:(BOOL)enable;

- (void)destroyResourceInternal;

- (void)setEngine:(id _Nullable)engine;

@end
