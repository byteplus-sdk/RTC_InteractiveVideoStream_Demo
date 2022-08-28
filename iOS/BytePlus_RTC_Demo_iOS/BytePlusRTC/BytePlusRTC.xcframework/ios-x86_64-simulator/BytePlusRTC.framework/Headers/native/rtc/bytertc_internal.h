/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Internal API
*/

#pragma once

#ifndef BYTE_RTC_INTERNAL_H__
#define BYTE_RTC_INTERNAL_H__

#include "bytertc_engine_interface.h"
#include <stdint.h>
#include <stdarg.h>

namespace bytertc {

/** 
 * @brief Customize user roles
 * @notes You should call this method before entering the room.
 */
BYTERTC_API void setCustomUserRole(IRtcEngine* engine, const char* role);

/** 
 * @brief Set ByteRTC SDK to use QUIC to get configuration by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableQuicGetAccess();

/** 
 * @brief Set ByteRTC SDK to use KCP to get configuration by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableKcpGetAccess();

/** 
 * @brief Set ByteRTC SDK to enable pre-call network detection by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableNetworkDetect();

/** 
 * @brief Set ByteRTC SDK to use KCP message channel by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableKcpDataChannel();

struct VideoStreamDescription {
    unsigned int width;
    unsigned int height;
    unsigned int frame_rate;
    unsigned int max_kbps;
    VideoStreamScaleMode scale_mode;
};

enum class PixelFormat {
      kDefault = 0,
      kI420 = 1,
      kRGBA = 2,
      kTexture = 3,
};

enum class NetworkFamily {
    kNetworkFamilyNone = 0,
    kNetworkFamilyIPv4 = 1,
    kNetworkFamilyIPv6 = 2,
    kNetworkFamilyBoth = 3,
};

enum StreamFlag {
    kStreamFlagNone = 0,
    kStreamFlagNormal = 1 << 0,
    kStreamFlagDocShare = 1 << 1,
    kStreamFlagMCU = 1 << 2,
    kStreamFlagMeetTogether = 1 << 3
};

class IEngineInternalEventHandler {
public:
    virtual ~IEngineInternalEventHandler() {
    }
    /** 
     * @brief Whether the current engine is enabled for ice reuse
     * @param [in] muxed Whether the current engine is enabled for ice reuse  <br>
     *       + true  : Yes
     *       + false : No
     */
    virtual void onPeerConnectionICEMux(bool muxed){};
    //TODO(shenpengliang) remove this method
    virtual void onSystemInfoLog(double app_cpu_usage, double total_cpu_usage, double app_memery_usage){};
    virtual void onSignalingAddrChanged(const char* addr){};
    virtual void onConfigAddrChanged(const char* addr){};
    virtual void onMediaServerAddrChanged(const char* addr){};
};

/** 
 * @brief Set the internal callback event for the current engine
 * @param [in] engine RTC engine for current app
 * @param [in] handler Internal event callback handle for the current app
 * @notes You must call this method before entering the room
 */
BYTERTC_API void setEngineInternalEventHandler(
      IRtcEngine *engine,
      IEngineInternalEventHandler* handler);
      
}  // namespace bytertc

#endif // BYTE_RTC_INTERNAL_H__ 
