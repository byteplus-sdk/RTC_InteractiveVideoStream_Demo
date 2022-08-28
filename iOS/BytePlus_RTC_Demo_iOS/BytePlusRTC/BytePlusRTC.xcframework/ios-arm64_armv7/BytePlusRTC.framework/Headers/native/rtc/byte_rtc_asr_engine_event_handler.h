//
// Created by shenpengliang on 2021/8/23.
//

#pragma once

namespace bytertc {
/**  
 * @hidden
 * @type keytype
 * @brief  Speech recognition service usage status callback
 */
class IRTCASREngineEventHandler {
public:
    /**  
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCASREngineEventHandler() {
    }
    /**  
     * @hidden
     * @type callback
     * @brief  Speech recognition service starts successful callback
     */
    virtual void onSuccess() = 0;
    /**  
     * @hidden
     * @type callback
     * @brief The voice-to-text callback is successful, and the callback returns the full amount of messages after recognition.
     * @param  [in] message Text message obtained after the completion of the recognition
     * @notes  If the network connection is interrupted during the recognition process, the callback information after the reconnection contains only the text message recognized after the reconnection, and no longer contains the last connection. The message identified after.
     */
    virtual void onMessage(const char* message) = 0;
    /**  
     * @hidden
     * @type callback
     * @brief This callback is triggered when an error event occurs within the speech recognition service.
     * @param  [in] error_code Error code <br>
     *         + < 0: parameter error or API call order error. See RTCASRErrorCode{@link #RTCASRErrorCode}; <br> 
     *         + > 0: see [speech recognition service error code](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#VPknqs)  
     * @param  [in] error_message Error reason description
     */
    virtual void onError(int error_code, const char* error_message) = 0;
};
}  // namespace bytertc
