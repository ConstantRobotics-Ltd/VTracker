#pragma once
#include "Frame.h"
#include "ConfigReader.h"



namespace cr
{
namespace vtracker
{
/**
 * @brief Mask structure for video tracker params.
 */
typedef struct VTrackerParamsMask
{
    bool mode{true};
    bool rectX{true};
    bool rectY{true};
    bool rectWidth{true};
    bool rectHeight{true};
    bool objectX{true};
    bool objectY{true};
    bool objectWidth{true};
    bool objectHeight{true};
    bool lostModeFrameCounter{true};
    bool frameCounter{true};
    bool frameWidth{true};
    bool frameHeight{true};
    bool searchWindowWidth{true};
    bool searchWindowHeight{true};
    bool searchWindowX{true};
    bool searchWindowY{true};
    bool lostModeOption{true};
    bool frameBufferSize{true};
    bool maxFramesInLostMode{true};
    bool processedFrameId{true};
    bool frameId{true};
    bool velX{true};
    bool velY{true};
    bool detectionProbability{true};
    bool rectAutoSize{true};
    bool rectAutoPosition{true};
    bool multipleThreads{true};
    bool numChannels{true};
    bool type{true};
    bool processingTimeMks{true};
    bool custom1{true};
    bool custom2{true};
    bool custom3{true};
} VTrackerParamsMask;



/**
 * @brief Video tracker params and processing results class.
 */
class VTrackerParams
{
public:
    /// Tracker mode index: 0 - FREE, 1 - TRACKING, 2 - INERTIAL, 3 - STATIC.
    int mode{0};
    /// Tracking rectangle horizontal center position.
    int rectX{0};
    /// Tracking rectangle vertical center position.
    int rectY{0};
    /// Tracking rectangle width.
    int rectWidth{72};
    /// Tracking rectangle height.
    int rectHeight{72};
    /// Estimated horizontal position of object center.
    int objectX{0};
    /// Estimated vertical position of object center.
    int objectY{0};
    /// Estimated object width.
    int objectWidth{72};
    /// Estimated object height.
    int objectHeight{72};
    /// Frame counter in LOST mode.
    int lostModeFrameCounter{0};
    /// Counter for processed frames after capture object.
    int frameCounter{0};
    /// Width of processed video frame.
    int frameWidth{0};
    /// Height of processed video frame.
    int frameHeight{0};
    /// Width of search window.
    int searchWindowWidth{256};
    /// Height of search window.
    int searchWindowHeight{256};
    /// Horizontal position of search window center.
    int searchWindowX{0};
    /// Vertical position of search window center.
    int searchWindowY{0};
    /// Option for LOST mode.
    int lostModeOption{0};
    /// Size of frame buffer (number of frames to store).
    int frameBufferSize{128};
    /// Maximum number of frames in LOST mode to auto reset of algorithm.
    int maxFramesInLostMode{128};
    /// ID of last processed frame in frame buffer.
    int processedFrameId{0};
    /// ID of last added frame to frame buffer.
    int frameId{0};
    /// Horizontal velocity of object on video frames ( pixel/frame ).
    float velX{0.0f};
    /// Vertical velocity of object on video frames ( pixel/frame ).
    float velY{0.0f};
    /// Estimated probability of object detection.
    float detectionProbability{0.0f};
    /// Use tracking rectangle auto size flag: false - no use, true - use.
    bool rectAutoSize{false};
    /// Use tracking rectangle auto position: false - no use, true - use.
    bool rectAutoPosition{false};
    /// Use multiple threads for calculations.
    bool multipleThreads{false};
    /// Number of channels for processing. E.g., number of color channels.
    int numChannels{3};
    /// Tracker type. Depends on implementation.
    int type{0};
    /// Processing time for last frame, mks.
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
                  custom3);

    /**
     * @brief operator =
     * @param src Source object.
     * @return VTrackerParams object.
     */
    VTrackerParams& operator= (const VTrackerParams& src);

    /**
     * @brief Encode params.
     * @param data Pointer to data buffer.
     * @param size Size of data.
     * @param mask Pointer to parameters mask.
     */
    void encode(uint8_t* data, int& size, VTrackerParamsMask* mask = nullptr);

    /**
     * @brief Decode params.
     * @param data Pointer to data.
     * @return TRUE is params decoded or FALSE if not.
     */
    bool decode(uint8_t* data);
};



/**
 * @brief Video tracker commands enum.
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
    /// arg2 - Rectangle center X coordinate, percents of frame height.
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
    /// arg2 - Search window center X coordinate, percents of frame height.
    SET_SEARCH_WINDOW_POSITION_PERCENTS,
    /// Change tracking rectagle size. Arguments:
    /// arg1 - horizontal size add, pixels.
    /// arg2 - vertical size add, pixels.
    CHANGE_RECT_SIZE
};



/**
 * @brief Video tracker params enum. Params whick defines algorithm parameters.
 */
enum class VTrackerParam
{
    /// Width of search window.
    SEARCH_WINDOW_WIDTH = 1,
    /// Height of search window.
    SEARCH_WINDOW_HEIGHT,
    /// Option for LOST mode.
    LOST_MODE_OPTION,
    /// Size of frame buffer (number of frames to store).
    FRAME_BUFFER_SIZE,
    /// Maximum number of frames in LOST mode to auto reset of algorithm.
    MAX_FRAMES_IN_LOST_MODE,
    /// Use tracking rectangle auto size flag: 0 - no use, 1 - use.
    RECT_AUTO_SIZE,
    /// Use tracking rectangle auto position: 0 - no use, 1 - use.
    RECT_AUTO_POSITION,
    /// Use multiple threads for calculations. 0 - one thread, 1 - multiple.
    MULTIPLE_THREADS,
    /// Number of channels for processing. E.g., number of color channels.
    NUM_CHANNELS,
    /// Tracker type. Depends on implementation.
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
 */
class VTracker
{
public:

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
     * @param id Param ID.
     * @param value Param value to set.
     * @return TRUE if param was set of FALSE.
     */
    virtual bool setParam(VTrackerParam id, float value) = 0;

    /**
     * @brief Get video tracker param value.
     * @param id Param ID.
     * @return Param value or -1.
     */
    virtual float getParam(VTrackerParam id) = 0;

    /**
     * @brief Get video tracker params (results).
     * @return Video tracker params structure.
     */
    virtual VTrackerParams getParams() = 0;

    /**
     * @brief Execute command.
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
    virtual bool processFrame(cr::video::Frame& frame) = 0;

    /**
     * @brief Get image of internal surfaces.
     * @param type Type of image to get. Depends on implementation.
     * @param image Pointer to image buffer. Must be 128x128 = 16384 bytes.
     */
    virtual void getImage(int type, cr::video::Frame& image) = 0;

    /**
     * @brief Encode set param command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Param id.
     * @param value Param value.
     */
    static void encodeSetParamCommand(
            uint8_t* data, int& size, VTrackerParam id, float value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
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
     * @param data Pointer to command data.
     * @param size Size of data.
     * @param paramId Output command ID.
     * @param commandId Output command ID.
     * @param value1 Param or command argument 1.
     * @param value2 Command argument 2.
     * @param value3 Command argument 3.
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             VTrackerParam& paramId,
                             VTrackerCommand& commandId,
                             float& value1,
                             float& value2,
                             float& value3);
};
}
}




