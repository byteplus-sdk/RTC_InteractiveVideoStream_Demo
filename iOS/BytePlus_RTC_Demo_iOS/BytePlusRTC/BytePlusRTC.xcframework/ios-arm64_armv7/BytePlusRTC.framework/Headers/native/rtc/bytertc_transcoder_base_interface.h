//
//  bytertc_transcoder_base_interface.h
//  ByteRTC
//
#pragma once

namespace bytertc {
/** 
 * @hidden
 * @type keytype
 * @brief  Confluence room status
 */
enum TranscoderRoomStatus {
    /**
     * @brief join room status
     */
    kRoomStatusJoinRoom,
    /**
     * @brief leave room status
     */
    kRoomStatusLeaveRoom,
    /**
     * @brief room status was offline
     */
    kRoomStatusOffline,
    /**
     * @brief room status was online
     */
    kRoomStatusOnline,
};

/** 
 * @type keytype
 * @brief  Confluence output content type
 */
enum TranscoderContentControlType {
    /** 
     * @brief The output of the mixed stream contains audio and video
     */
    kHasAudioAndVideo = 0,
    /** 
     * @brief The output mix contains only audio
     */
    kHasAudioOnly = 1,
    /** 
     * @brief The output of the mixed stream contains only video
     */
    kHasVideoOnly = 2,
};
/** 
 * @type keytype
 * @brief Properties of the mixing stream
 */
class ITranscoderParamBase {
public:
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Get the confluence room ID
     * @return Confluence room ID
     */
    virtual const char* roomID() = 0;
    /** 
     * @hidden
     * @type api
     * @region  retweet live
     * @brief  Get other data
     * @return other data
     */
    virtual const char* other() = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Get the json format content json
     * @return Format data converted by the flatten{@link #ITranscoderParamBase#flatten} method
     */
    virtual const char* jsonContent() = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Get the number of windows in the confluence parameter
     * @return The number of windows in the confluence parameter
     */
    virtual int32_t layoutRegionsSize() = 0;
    /** 
     * @type api
     * @region  turn to push live
     * @brief  Get background color
     * @return  Background color
     */
    virtual const char* backgroundColor() = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Set the confluence room ID
     * @param  [in] room_id The room ID of the user who initiated the confluence
     */
    virtual void setRoomID(const char* room_id) = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Settings jsonContent <br>
     *        Passing in json format content obtained by converting the flatten{@link #ITranscoderParamBase#flatten} method
     * @param  [in] json_content Json format content
     */
    virtual void setJsonContent(const char* json_content) = 0;
    /** 
     * @hidden
     * @type api
     * @region  Forward to live broadcast
     * @brief  Settings other data
     * @param  [in] other other data
     */
    virtual void setOther(const char* other) = 0;
    /** 
     * @type api
     * @region Forward push live broadcast
     * @brief Turn the confluence parameter into json string
     * @param  [in] contentType Content attribute to indicate the confluence signaling
     * @param  [in] action Confluence status. The optional values are as follows: <br>
     *                + Started: open the confluence <br>
     *                + LayoutChanged: update the confluence layout <br>
     *                + Stopped: Stop Confluence
     * @return Converted json string
     */
    virtual const char* flatten(const char* contentType, const char* action) = 0;
    /**
     * @hidden
     */
    ~ITranscoderParamBase() = default;
};
}/*namespace bytertc*/
