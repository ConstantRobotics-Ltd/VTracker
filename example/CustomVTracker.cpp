#include "CustomVTracker.h"
#include "CustomVTrackerVersion.h"
#include <cstdint>
#include <limits>
#include <mutex>
#include <string>
#include "VTracker.h"



namespace
{
/// Maximum value of an int param.
constexpr int MAX_INT{std::numeric_limits<int>::max()};
/// Maximum size of frame buffer. The example does not store frames, but an
/// implementation which allocates memory according to this value must limit
/// it: the value can come from outside (JSON file, network command).
constexpr int MAX_FRAME_BUFFER_SIZE{1024};
/// Maximum number of channels for processing (the widest RAW pixel format
/// has 4 channels).
constexpr int MAX_NUM_CHANNELS{4};
/// Maximum value of the LOST mode option (see VTrackerParams::lostModeOption).
constexpr int MAX_LOST_MODE_OPTION{2};
/// Limit of float values which can be converted to int. 2^31 is exactly
/// representable as float, so (-LIMIT <= value < LIMIT) is the exact range
/// of int.
constexpr float INT_RANGE_LIMIT{2147483648.0f};



/// Convert float param value to int. A conversion of NaN or of a value outside
/// of the int range is undefined behavior, so such values are rejected.
bool toInt(float value, int& result)
{
    if (!(value >= -INT_RANGE_LIMIT && value < INT_RANGE_LIMIT))
    {
        return false;
    }
    result = static_cast<int>(value);
    return true;
}



/// Assign the value to the target if the value is inside [minValue, maxValue].
bool assignInRange(int& target, int value, int minValue, int maxValue)
{
    if (value < minValue || value > maxValue)
    {
        return false;
    }
    target = value;
    return true;
}



/// Check values of the params which can be set by user.
bool isValid(const rapidpixel::VTrackerParams& params)
{
    return params.rectWidth >= 1 &&
           params.rectHeight >= 1 &&
           params.searchWindowWidth >= 1 &&
           params.searchWindowHeight >= 1 &&
           params.lostModeOption >= 0 &&
           params.lostModeOption <= MAX_LOST_MODE_OPTION &&
           params.frameBufferSize >= 1 &&
           params.frameBufferSize <= MAX_FRAME_BUFFER_SIZE &&
           params.maxFramesInLostMode >= 0 &&
           params.numChannels >= 1 &&
           params.numChannels <= MAX_NUM_CHANNELS;
}
}



rapidpixel::CustomVTracker::CustomVTracker()
{

}



rapidpixel::CustomVTracker::~CustomVTracker()
{

}



std::string rapidpixel::CustomVTracker::getVersion()
{
    return CUSTOM_VTRACKER_VERSION;
}



bool rapidpixel::CustomVTracker::initVTracker(
        rapidpixel::VTrackerParams& params)
{
    // Params can come from outside (JSON file, network): check them.
    if (!isValid(params))
    {
        return false;
    }

    // Copy params.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    m_params = params;

    return true;
}



bool rapidpixel::CustomVTracker::setParam(
        rapidpixel::VTrackerParam id, float value)
{
    // Custom params are float, they do not need conversion.
    if (id == rapidpixel::VTrackerParam::CUSTOM_1 ||
        id == rapidpixel::VTrackerParam::CUSTOM_2 ||
        id == rapidpixel::VTrackerParam::CUSTOM_3)
    {
        const std::lock_guard<std::mutex> lock(m_paramsMutex);
        if (id == rapidpixel::VTrackerParam::CUSTOM_1)
        {
            m_params.custom1 = value;
        }
        else if (id == rapidpixel::VTrackerParam::CUSTOM_2)
        {
            m_params.custom2 = value;
        }
        else
        {
            m_params.custom3 = value;
        }
        return true;
    }

    // All other params are integer or flags.
    int number{0};
    if (!toInt(value, number))
    {
        return false;
    }

    // Check parameter ID and value.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    switch (id)
    {
    case rapidpixel::VTrackerParam::SEARCH_WINDOW_WIDTH:
    {
        return assignInRange(m_params.searchWindowWidth, number, 1, MAX_INT);
    }
    case rapidpixel::VTrackerParam::SEARCH_WINDOW_HEIGHT:
    {
        return assignInRange(m_params.searchWindowHeight, number, 1, MAX_INT);
    }
    case rapidpixel::VTrackerParam::RECT_WIDTH:
    {
        return assignInRange(m_params.rectWidth, number, 1, MAX_INT);
    }
    case rapidpixel::VTrackerParam::RECT_HEIGHT:
    {
        return assignInRange(m_params.rectHeight, number, 1, MAX_INT);
    }
    case rapidpixel::VTrackerParam::LOST_MODE_OPTION:
    {
        return assignInRange(
                    m_params.lostModeOption, number, 0, MAX_LOST_MODE_OPTION);
    }
    case rapidpixel::VTrackerParam::FRAME_BUFFER_SIZE:
    {
        return assignInRange(
                    m_params.frameBufferSize, number, 1, MAX_FRAME_BUFFER_SIZE);
    }
    case rapidpixel::VTrackerParam::MAX_FRAMES_IN_LOST_MODE:
    {
        return assignInRange(m_params.maxFramesInLostMode, number, 0, MAX_INT);
    }
    case rapidpixel::VTrackerParam::RECT_AUTO_SIZE:
    {
        m_params.rectAutoSize = number != 0;
        return true;
    }
    case rapidpixel::VTrackerParam::RECT_AUTO_POSITION:
    {
        m_params.rectAutoPosition = number != 0;
        return true;
    }
    case rapidpixel::VTrackerParam::MULTIPLE_THREADS:
    {
        m_params.multipleThreads = number != 0;
        return true;
    }
    case rapidpixel::VTrackerParam::NUM_CHANNELS:
    {
        return assignInRange(
                    m_params.numChannels, number, 1, MAX_NUM_CHANNELS);
    }
    case rapidpixel::VTrackerParam::TYPE:
    {
        m_params.type = number;
        return true;
    }
    default:
    {
        return false;
    }
    }
}



float rapidpixel::CustomVTracker::getParam(rapidpixel::VTrackerParam id)
{
    // Check parameter ID.
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    switch (id)
    {
    case rapidpixel::VTrackerParam::SEARCH_WINDOW_WIDTH:
    {
        return static_cast<float>(m_params.searchWindowWidth);
    }
    case rapidpixel::VTrackerParam::SEARCH_WINDOW_HEIGHT:
    {
        return static_cast<float>(m_params.searchWindowHeight);
    }
    case rapidpixel::VTrackerParam::RECT_WIDTH:
    {
        return static_cast<float>(m_params.rectWidth);
    }
    case rapidpixel::VTrackerParam::RECT_HEIGHT:
    {
        return static_cast<float>(m_params.rectHeight);
    }
    case rapidpixel::VTrackerParam::LOST_MODE_OPTION:
    {
        return static_cast<float>(m_params.lostModeOption);
    }
    case rapidpixel::VTrackerParam::FRAME_BUFFER_SIZE:
    {
        return static_cast<float>(m_params.frameBufferSize);
    }
    case rapidpixel::VTrackerParam::MAX_FRAMES_IN_LOST_MODE:
    {
        return static_cast<float>(m_params.maxFramesInLostMode);
    }
    case rapidpixel::VTrackerParam::RECT_AUTO_SIZE:
    {
        return m_params.rectAutoSize ? 1.0f : 0.0f;
    }
    case rapidpixel::VTrackerParam::RECT_AUTO_POSITION:
    {
        return m_params.rectAutoPosition ? 1.0f : 0.0f;
    }
    case rapidpixel::VTrackerParam::MULTIPLE_THREADS:
    {
        return m_params.multipleThreads ? 1.0f : 0.0f;
    }
    case rapidpixel::VTrackerParam::NUM_CHANNELS:
    {
        return static_cast<float>(m_params.numChannels);
    }
    case rapidpixel::VTrackerParam::TYPE:
    {
        return static_cast<float>(m_params.type);
    }
    case rapidpixel::VTrackerParam::CUSTOM_1:
    {
        return m_params.custom1;
    }
    case rapidpixel::VTrackerParam::CUSTOM_2:
    {
        return m_params.custom2;
    }
    case rapidpixel::VTrackerParam::CUSTOM_3:
    {
        return m_params.custom3;
    }
    default:
    {
        return -1.0f;
    }
    }
}



void rapidpixel::CustomVTracker::getParams(VTrackerParams& params)
{
    const std::lock_guard<std::mutex> lock(m_paramsMutex);
    params = m_params;
}



bool rapidpixel::CustomVTracker::executeCommand(
                    rapidpixel::VTrackerCommand id, float, float, float)
{
    // Check command ID. The example accepts all known commands and does
    // nothing: a real tracker must validate the arguments here.
    switch (id)
    {
    case rapidpixel::VTrackerCommand::CAPTURE:
    case rapidpixel::VTrackerCommand::CAPTURE_PERCENTS:
    case rapidpixel::VTrackerCommand::RESET:
    case rapidpixel::VTrackerCommand::SET_INERTIAL_MODE:
    case rapidpixel::VTrackerCommand::SET_LOST_MODE:
    case rapidpixel::VTrackerCommand::SET_STATIC_MODE:
    case rapidpixel::VTrackerCommand::ADJUST_RECT_SIZE:
    case rapidpixel::VTrackerCommand::ADJUST_RECT_POSITION:
    case rapidpixel::VTrackerCommand::MOVE_RECT:
    case rapidpixel::VTrackerCommand::SET_RECT_POSITION:
    case rapidpixel::VTrackerCommand::SET_RECT_POSITION_PERCENTS:
    case rapidpixel::VTrackerCommand::MOVE_SEARCH_WINDOW:
    case rapidpixel::VTrackerCommand::SET_SEARCH_WINDOW_POSITION:
    case rapidpixel::VTrackerCommand::SET_SEARCH_WINDOW_POSITION_PERCENTS:
    case rapidpixel::VTrackerCommand::CHANGE_RECT_SIZE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}



bool rapidpixel::CustomVTracker::processFrame(rapidpixel::Frame&)
{
    return true;
}



void rapidpixel::CustomVTracker::getImage(int, rapidpixel::Frame&)
{

}



bool rapidpixel::CustomVTracker::decodeAndExecuteCommand(
        uint8_t* data, int size)
{
    // Decode command. The decoder checks the size, the version and the IDs.
    VTrackerParam paramId{VTrackerParam::SEARCH_WINDOW_WIDTH};
    VTrackerCommand commandId{VTrackerCommand::RESET};
    float value1{0.0f};
    float value2{0.0f};
    float value3{0.0f};
    const int result = VTracker::decodeCommand(
                data, size, paramId, commandId, value1, value2, value3);

    // Execute the decoded command.
    if (result == 0)
    {
        return executeCommand(commandId, value1, value2, value3);
    }
    if (result == 1)
    {
        return setParam(paramId, value1);
    }

    return false;
}
