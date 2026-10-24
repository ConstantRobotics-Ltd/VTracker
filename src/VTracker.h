#pragma once
#include <cstdint>
#include <string>
#include "Frame.h"
#include "ConfigReader.h"



namespace rapidpixel
{
/**
 * @brief Mask structure for video tracker params.
 *
 * Each flag enables serialization of the VTrackerParams field with the same
 * name (see VTrackerParams::encode(...)).
 */
typedef struct VTrackerParamsMask
{
    bool mode{true};                  ///< Serialize mode field.
    bool rectX{true};                 ///< Serialize rectX field.
    bool rectY{true};                 ///< Serialize rectY field.
    bool rectWidth{true};             ///< Serialize rectWidth field.
    bool rectHeight{true};            ///< Serialize rectHeight field.
    bool objectX{true};               ///< Serialize objectX field.
    bool objectY{true};               ///< Serialize objectY field.
    bool objectWidth{true};           ///< Serialize objectWidth field.
    bool objectHeight{true};          ///< Serialize objectHeight field.
    bool lostModeFrameCounter{true};  ///< Serialize lostModeFrameCounter field.
    bool frameCounter{true};          ///< Serialize frameCounter field.
    bool frameWidth{true};            ///< Serialize frameWidth field.
    bool frameHeight{true};           ///< Serialize frameHeight field.
    bool searchWindowWidth{true};     ///< Serialize searchWindowWidth field.
    bool searchWindowHeight{true};    ///< Serialize searchWindowHeight field.
    bool searchWindowX{true};         ///< Serialize searchWindowX field.
    bool searchWindowY{true};         ///< Serialize searchWindowY field.
    bool lostModeOption{true};        ///< Serialize lostModeOption field.
    bool frameBufferSize{true};       ///< Serialize frameBufferSize field.
    bool maxFramesInLostMode{true};   ///< Serialize maxFramesInLostMode field.
    bool processedFrameId{true};      ///< Serialize processedFrameId field.
    bool frameId{true};               ///< Serialize frameId field.
    bool velX{true};                  ///< Serialize velX field.
    bool velY{true};                  ///< Serialize velY field.
    bool detectionProbability{true};  ///< Serialize detectionProbability field.
    bool rectAutoSize{true};          ///< Serialize rectAutoSize field.
    bool rectAutoPosition{true};      ///< Serialize rectAutoPosition field.
    bool multipleThreads{true};       ///< Serialize multipleThreads field.
    bool numChannels{true};           ///< Serialize numChannels field.
    bool type{true};                  ///< Serialize type field.
    bool processingTimeMks{true};     ///< Serialize processingTimeMks field.
    bool custom1{true};               ///< Serialize custom1 field.
    bool custom2{true};               ///< Serialize custom2 field.
    bool custom3{true};               ///< Serialize custom3 field.
} VTrackerParamsMask;



/**
 * @brief Video tracker params and processing results class.
 *
 * @note The class is not thread-safe: an object must not be accessed from
 * several threads at the same time without external synchronization.
 */
class VTrackerParams
{
public:
    /// Tracker mode index: 0 - FREE, 1 - TRACKING, 2 - INERTIAL, 3 - STATIC.
    /// Set by video tracker according to processing results or after command
    /// execution.
    int mode{0};
    /// Tracking rectangle horizontal center position. Calculated by tracking
    /// algorithm.
    int rectX{0};
    /// Tracking rectangle vertical center position. Calculated by tracking
    /// algorithm.
    int rectY{0};
    /// Tracking rectangle width, pixels. Set by user or can be changed by
    /// tracking algorithm if rectAutoSize == true.
    int rectWidth{72};
    /// Tracking rectangle height, pixels. Set by user or can be changed by
    /// tracking algorithm if rectAutoSize == true.
    int rectHeight{72};
    /// Estimated horizontal position of object center, pixels. Calculated by
    /// video tracker.
    int objectX{0};
    /// Estimated vertical position of object center, pixels. Calculated by
    /// video tracker.
    int objectY{0};
    /// Estimated object width, pixels. Calculated by video tracker.
    int objectWidth{72};
    /// Estimated object height, pixels. Calculated by video tracker.
    int objectHeight{72};
    /// Frame counter in LOST mode. After switching in LOST mode the video
    /// tracker start counting from 0. After switching to another mode from
    /// LOST mode the video tracker will reset this counter.
    int lostModeFrameCounter{0};
    /// Counter for processed frames after capture object. After reset tracking
    /// the video tracker will reset counter.
    int frameCounter{0};
    /// Width of processed video frame. Set by video tracker after processing
    /// first video frame.
    int frameWidth{0};
    /// Height of processed video frame. Set by video tracker after processing
    /// first video frame.
    int frameHeight{0};
    /// Width of search window, pixels. Set by user.
    int searchWindowWidth{256};
    /// Height of search window, pixels. Set by user.
    int searchWindowHeight{256};
    /// Horizontal position of search window center. This position will be used
    /// for next video frame. Usually it coincides with data tracking rectangle
    /// center but can be set by user to move search window for new video frame.
    int searchWindowX{0};
    /// Vertical position of search window center. This position will be used
    /// for next video frame. Usually it coincides with data tracking rectangle
    /// center but can be set by user to move search window for new video frame.
    int searchWindowY{0};
    /// Option for LOST mode. Parameter that defines the behavior of the
    /// tracking algorithm in LOST mode. Default is 0. Possible values:
    /// 0. In LOST mode, the coordinates of the center of the tracking
    ///    rectangle are not updated and remain the same as before entering
    ///    LOST mode.
    /// 1. The coordinates of the center of the tracking rectangle are updated
    ///    based on the components of the object's speed calculated before
    ///    going into LOST mode. If the tracking rectangle "touches" the edge
    ///    of the video frame, the coordinate updating for this component
    ///    (horizontal or vertical) will stop.
    /// 2. The coordinates of the center of the tracking rectangle are
    ///    updated based on the components of the object's speed calculated
    ///    before going into LOST mode. The tracking is reset if the center of
    ///    the tracking rectangle touches any of the edges of the video frame.
    int lostModeOption{0};
    /// Size of frame buffer (number of frames to store). Set by user.
    int frameBufferSize{128};
    /// Maximum number of frames in LOST mode to auto reset of algorithm. Set
    /// by user.
    int maxFramesInLostMode{128};
    /// ID of last processed frame in frame buffer. Set by video tracker.
    int processedFrameId{0};
    /// ID of last added frame to frame buffer. Set by video tracker.
    int frameId{0};
    /// Horizontal velocity of object on video frames (pixel/frame). Calculated
    /// by video tracker.
    float velX{0.0f};
    /// Vertical velocity of object on video frames (pixel/frame). Calculated
    /// by video tracker.
    float velY{0.0f};
    /// Estimated probability of object detection. Calculated by video tracker.
    float detectionProbability{0.0f};
    /// Use tracking rectangle auto size flag: false - no use, true - use. Set
    /// by user.
    bool rectAutoSize{false};
    /// Use tracking rectangle auto position: false - no use, true - use. Set
    /// by user.
    bool rectAutoPosition{false};
    /// Use multiple threads for calculations. Set by user.
    bool multipleThreads{false};
    /// Number of channels for processing. E.g., number of color channels. Set
    /// by user.
    int numChannels{3};
    /// Tracker type. Depends on implementation. Set by user.
    int type{0};
    /// Processing time for last frame, mks. Calculated by video tracker.
    int processingTimeMks{0};
    /// Custom parameter. Depends on implementation.
    float custom1{0.0f};
    /// Custom parameter. Depends on implementation.
    float custom2{0.0f};
    /// Custom parameter. Depends on implementation.
    float custom3{0.0f};

    JSON_READABLE(VTrackerParams,
                  rectWidth,
                  rectHeight,
                  searchWindowWidth,
                  searchWindowHeight,
                  lostModeOption,
                  frameBufferSize,
                  maxFramesInLostMode,
                  rectAutoSize,
                  rectAutoPosition,
                  multipleThreads,
                  numChannels,
                  type,
                  custom1,
                  custom2,
                  custom3)

    /**
     * @brief Default constructor.
     */
    VTrackerParams() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    VTrackerParams(const VTrackerParams& src) = default;

    /**
     * @brief operator =
     * @param src Source object.
     * @return VTrackerParams object.
     */
    VTrackerParams& operator= (const VTrackerParams& src) = default;

    /**
     * @brief Encode (serialize) params.
     *
     * The encoded data has a fixed layout: 1 byte data type (0x02), 2 bytes
     * of library major and minor version, 5 bytes of fields mask and the
     * fields selected by the mask. Integer and float fields are stored as
     * 4 bytes in the byte order of the host (little endian), boolean fields
     * as 1 byte (0 or 1).
     *
     * @param data Pointer to output data buffer. Must not be nullptr.
     * @param bufferSize Size of the data buffer, bytes. Must be at least 135
     * bytes (size of all fields).
     * @param size Size of encoded data, bytes. Set to 0 if params were not
     * encoded.
     * @param mask Pointer to parameters mask. If nullptr all fields are
     * encoded. A field with false flag is not encoded.
     * @return TRUE if data encoded (serialized) or FALSE if not (data is
     * nullptr or the buffer is too small).
     */
    bool encode(uint8_t* data, int bufferSize,
                int& size, VTrackerParamsMask* mask = nullptr);

    /**
     * @brief Decode (deserialize) params encoded by encode(...) method.
     *
     * The method checks data type, version and size of the data before
     * reading each field. Fields which are not present in the data are set to
     * 0 (false for boolean fields). Values of fields are not checked against
     * any range: the video tracker implementation must validate them before
     * use. Bytes after the last decoded field are ignored.
     *
     * @param data Pointer to encoded data. Must not be nullptr.
     * @param dataSize Size of the encoded data, bytes.
     * @return TRUE if params decoded or FALSE if not. If FALSE is returned
     * the object is not changed.
     */
    bool decode(uint8_t* data, int dataSize);
};



/**
 * @brief Video tracker commands enum.
 *
 * @note CHANGE_RECT_SIZE must stay the last value: it is used by
 * VTracker::decodeCommand(...) to reject unknown command IDs.
 */
enum class VTrackerCommand
{
    /// Object capture. Arguments:
    /// arg1 - Capture rectangle center X coordinate. -1 - default coordinate.
    /// arg2 - Capture rectangle center Y coordinate. -1 - default coordinate.
    /// arg3 - frame ID. -1 - Capture on last frame.
    CAPTURE = 1,
    /// Object capture command. Arguments:
    /// arg1 - Capture rectangle center X coordinate, percents of frame width.
    /// arg2 - Capture rectangle center Y coordinate, percents of frame width.
    CAPTURE_PERCENTS,
    /// Reset command. No arguments.
    RESET,
    /// Set INERTIAL mode. No arguments.
    SET_INERTIAL_MODE,
    /// Set LOST mode. No arguments.
    SET_LOST_MODE,
    /// Set STATIC mode. No arguments.
    SET_STATIC_MODE,
    /// Adjust tracking rectangle size automatically once. No arguments.
    ADJUST_RECT_SIZE,
    /// Adjust tracking rectangle position automatically once. No arguments.
    ADJUST_RECT_POSITION,
    /// Move tracking rectangle (change position). Arguments:
    /// arg1 - add to X coordinate, pixels. 0 - no change.
    /// arg2 - add to Y coordinate, pixels. 0 - no change.
    MOVE_RECT,
    /// Set tracking rectangle position in FREE mode. Arguments:
    /// arg1 - Rectangle center X coordinate.
    /// arg2 - Rectangle center Y coordinate.
    SET_RECT_POSITION,
    /// Set tracking rectangle position in FREE mode in percents of frame size.
    /// Arguments:
    /// arg1 - Rectangle center X coordinate, percents of frame width.
    /// arg2 - Rectangle center Y coordinate, percents of frame height.
    SET_RECT_POSITION_PERCENTS,
    /// Move search window (change position). Arguments:
    /// arg1 - add to X coordinate, pixels. 0 - no change.
    /// arg2 - add to Y coordinate, pixels. 0 - no change.
    MOVE_SEARCH_WINDOW,
    /// Set search window position. Arguments:
    /// arg1 - Search window center X coordinate.
    /// arg2 - Search window center Y coordinate.
    SET_SEARCH_WINDOW_POSITION,
    /// Set search window position in percents of frame size. Arguments:
    /// arg1 - Search window center X coordinate, percents of frame width.
    /// arg2 - Search window center Y coordinate, percents of frame height.
    SET_SEARCH_WINDOW_POSITION_PERCENTS,
    /// Change tracking rectangle size. Arguments:
    /// arg1 - horizontal size add, pixels.
    /// arg2 - vertical size add, pixels.
    CHANGE_RECT_SIZE
};



/**
 * @brief Video tracker params enum. Params which defines algorithm parameters.
 *
 * @note CUSTOM_3 must stay the last value: it is used by
 * VTracker::decodeCommand(...) to reject unknown param IDs.
 */
enum class VTrackerParam
{
    /// Width of search window, pixels. Set by user.
    SEARCH_WINDOW_WIDTH = 1,
    /// Height of search window, pixels. Set by user.
    SEARCH_WINDOW_HEIGHT,
    /// Tracking rectangle width, pixels. Set by user or can be changed by
    /// tracking algorithm if rectAutoSize == true.
    RECT_WIDTH,
    /// Tracking rectangle height, pixels. Set by user or can be changed by
    /// tracking algorithm if rectAutoSize == true.
    RECT_HEIGHT,
    /// Option for LOST mode. Parameter that defines the behavior of the
    /// tracking algorithm in LOST mode. Default is 0. Possible values:
    /// 0. In LOST mode, the coordinates of the center of the tracking
    ///    rectangle are not updated and remain the same as before entering
    ///    LOST mode.
    /// 1. The coordinates of the center of the tracking rectangle are updated
    ///    based on the components of the object's speed calculated before
    ///    going into LOST mode. If the tracking rectangle "touches" the edge
    ///    of the video frame, the coordinate updating for this component
    ///    (horizontal or vertical) will stop.
    /// 2. The coordinates of the center of the tracking rectangle are
    ///    updated based on the components of the object's speed calculated
    ///    before going into LOST mode. The tracking is reset if the center of
    ///    the tracking rectangle touches any of the edges of the video frame.
    LOST_MODE_OPTION,
    /// Size of frame buffer (number of frames to store). Set by user.
    FRAME_BUFFER_SIZE,
    /// Maximum number of frames in LOST mode to auto reset of algorithm. Set
    /// by user.
    MAX_FRAMES_IN_LOST_MODE,
    /// Use tracking rectangle auto size flag: 0 - no use, 1 - use. Set by user.
    RECT_AUTO_SIZE,
    /// Use tracking rectangle auto position: 0 - no use, 1 - use. Set by user.
    RECT_AUTO_POSITION,
    /// Use multiple threads for calculations. 0 - one thread, 1 - multiple. Set
    /// by user.
    MULTIPLE_THREADS,
    /// Number of channels for processing. E.g., number of color channels. Set
    /// by user.
    NUM_CHANNELS,
    /// Tracker type. Depends on implementation. Set by user.
    TYPE,
    /// Custom parameter. Depends on implementation.
    CUSTOM_1,
    /// Custom parameter. Depends on implementation.
    CUSTOM_2,
    /// Custom parameter. Depends on implementation.
    CUSTOM_3
};



/**
 * @brief Video tracker interface class.
 *
 * The class defines the interface only. The thread safety of the interface
 * methods is a requirement for an implementation (see description of each
 * method).
 */
class VTracker
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~VTracker();

    /**
     * @brief Get string of current library version.
     * @return String of current library version.
     */
    static std::string getVersion();

    /**
     * @brief Init video tracker. All params will be set.
     * @param params Parameters class.
     * @return TRUE if the video tracker init or FALSE if not.
     */
    virtual bool initVTracker(VTrackerParams& params) = 0;

    /**
     * @brief Set video tracker param.
     * @note The implementation must be thread-safe.
     * @param id Param ID.
     * @param value Param value to set.
     * @return TRUE if param was set or FALSE if not.
     */
    virtual bool setParam(VTrackerParam id, float value) = 0;

    /**
     * @brief Get video tracker param value.
     * @note The implementation must be thread-safe.
     * @param id Param ID.
     * @return Param value or -1 if the param does not exist.
     */
    virtual float getParam(VTrackerParam id) = 0;

    /**
     * @brief Get video tracker params (results).
     * @note The implementation must be thread-safe.
     * @param params Video tracker params structure.
     */
    virtual void getParams(VTrackerParams& params) = 0;

    /**
     * @brief Execute command.
     * @note The implementation must be thread-safe.
     * @param id Command ID.
     * @param arg1 First argument. Value depends on command ID.
     * @param arg2 Second argument. Value depends on command ID.
     * @param arg3 Third argument. Value depends on command ID.
     * @return TRUE if the command accepted or FALSE if not.
     */
    virtual bool executeCommand(VTrackerCommand id,
                                float arg1 = 0,
                                float arg2 = 0,
                                float arg3 = 0) = 0;

    /**
     * @brief Process frame. Must be used for each input video frame.
     * @param frame Source video frame.
     * @return TRUE if video frame was processed or FALSE if not.
     */
    virtual bool processFrame(rapidpixel::Frame& frame) = 0;

    /**
     * @brief Get image of internal surfaces.
     * @param type Type of image to get. Depends on implementation.
     * @param image Output frame. Pixel format depends on implementation.
     */
    virtual void getImage(int type, rapidpixel::Frame& image) = 0;

    /**
     * @brief Encode set param command.
     * @param data Pointer to data buffer. Must not be nullptr and must have
     * size >= 11 bytes.
     * @param size Size of encoded data (11 bytes). Set to 0 if data is
     * nullptr.
     * @param id Param id.
     * @param value Param value.
     */
    static void encodeSetParamCommand(
            uint8_t* data, int& size, VTrackerParam id, float value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must not be nullptr and must have
     * size >= 19 bytes.
     * @param size Size of encoded data (19 bytes). Set to 0 if data is
     * nullptr.
     * @param id Command ID.
     * @param arg1 First argument. Value depends on command ID.
     * @param arg2 Second argument. Value depends on command ID.
     * @param arg3 Third argument. Value depends on command ID.
     */
    static void encodeCommand(
            uint8_t* data, int& size, VTrackerCommand id,
            float arg1 = 0, float arg2 = 0, float arg3 = 0);

    /**
     * @brief Decode command.
     *
     * The method checks the pointer, the size (exactly 11 bytes for set param
     * command and exactly 19 bytes for command), the version and the ID.
     * Output values are not changed if the version check fails.
     *
     * @param data Pointer to command data. Must not be nullptr.
     * @param size Size of data, bytes.
     * @param paramId Output param ID. Set if set param command decoded.
     * @param commandId Output command ID. Set if command decoded.
     * @param value1 Param value or command argument 1.
     * @param value2 Command argument 2.
     * @param value3 Command argument 3.
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error
     * (invalid pointer, size, version, data type or unknown ID).
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             VTrackerParam& paramId,
                             VTrackerCommand& commandId,
                             float& value1,
                             float& value2,
                             float& value3);

    /**
     * @brief Decode and execute command.
     * @note The implementation must be thread-safe.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @return TRUE if command decoded and executed or FALSE if not.
     */
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;

protected:

    /**
     * @brief Default constructor. The class can be used as a base only.
     */
    VTracker() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    VTracker(const VTracker& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    VTracker(VTracker&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VTracker& operator= (const VTracker& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VTracker& operator= (VTracker&& src) = default;
};
}



// Compatibility: the names of namespace rapidpixel are also available in
// namespace cr::vtracker.
namespace cr
{
namespace vtracker
{
using namespace ::rapidpixel;
}
}
