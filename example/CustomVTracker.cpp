#include "CustomVTracker.h"
#include "CustomVTrackerVersion.h"




cr::vtracker::CustomVTracker::CustomVTracker()
{

}



cr::vtracker::CustomVTracker::~CustomVTracker()
{

}



std::string cr::vtracker::CustomVTracker::getVersion()
{
    return CUSTOM_VTRACKER_VERSION;
}



bool cr::vtracker::CustomVTracker::initVTracker(cr::vtracker::VTrackerParams& params)
{
    // Copy params.
    m_params = params;

    return false;
}



bool cr::vtracker::CustomVTracker::setParam(cr::vtracker::VTrackerParam id, float value)
{
    // Check parameter ID.
    switch (id)
    {
    case cr::vtracker::VTrackerParam::SEARCH_WINDOW_WIDTH:
    {
        m_params.searchWindowWidth = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::SEARCH_WINDOW_HEIGHT:
    {
        m_params.searchWindowHeight = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::RECT_WIDTH:
    {
        m_params.rectWidth = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::RECT_HEIGHT:
    {
        m_params.rectHeight = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::LOST_MODE_OPTION:
    {
        m_params.lostModeOption = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::FRAME_BUFFER_SIZE:
    {
        m_params.frameBufferSize = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::MAX_FRAMES_IN_LOST_MODE:
    {
        m_params.maxFramesInLostMode = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::RECT_AUTO_SIZE:
    {
        m_params.rectAutoSize = (int)value == 0 ? false : true;
        return true;
    }
    case cr::vtracker::VTrackerParam::RECT_AUTO_POSITION:
    {
        m_params.rectAutoPosition = (int)value == 0 ? false : true;
        return true;
    }
    case cr::vtracker::VTrackerParam::MULTIPLE_THREADS:
    {
        m_params.multipleThreads = (int)value == 0 ? false : true;
        return true;
    }
    case cr::vtracker::VTrackerParam::NUM_CHANNELS:
    {
        m_params.numChannels = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::TYPE:
    {
        m_params.type = (int)value;
        return true;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_1:
    {
        m_params.custom1 = value;
        return true;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_2:
    {
        m_params.custom2 = value;
        return true;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_3:
    {
        m_params.custom3 = value;
        return true;
    }
    default:
    {
        return false;
    }
    }

    return false;
}



float cr::vtracker::CustomVTracker::getParam(cr::vtracker::VTrackerParam id)
{
    // Check parameter ID.
    switch (id)
    {
    case cr::vtracker::VTrackerParam::SEARCH_WINDOW_WIDTH:
    {
        return (float)m_params.searchWindowWidth;
    }
    case cr::vtracker::VTrackerParam::SEARCH_WINDOW_HEIGHT:
    {
        return (float)m_params.searchWindowHeight;
    }
    case cr::vtracker::VTrackerParam::RECT_WIDTH:
    {
        return (float)m_params.rectWidth;
    }
    case cr::vtracker::VTrackerParam::RECT_HEIGHT:
    {
        return (float)m_params.rectHeight;
    }
    case cr::vtracker::VTrackerParam::LOST_MODE_OPTION:
    {
        return (float)m_params.lostModeOption;
    }
    case cr::vtracker::VTrackerParam::FRAME_BUFFER_SIZE:
    {
        return (float)m_params.frameBufferSize;
    }
    case cr::vtracker::VTrackerParam::MAX_FRAMES_IN_LOST_MODE:
    {
        return (float)m_params.maxFramesInLostMode;
    }
    case cr::vtracker::VTrackerParam::RECT_AUTO_SIZE:
    {
        return m_params.rectAutoSize ? 1.0f : 0.0f;
    }
    case cr::vtracker::VTrackerParam::RECT_AUTO_POSITION:
    {
        return m_params.rectAutoPosition ? 1.0f : 0.0f;
    }
    case cr::vtracker::VTrackerParam::MULTIPLE_THREADS:
    {
        return m_params.multipleThreads ? 1.0f : 0.0f;
    }
    case cr::vtracker::VTrackerParam::NUM_CHANNELS:
    {
        return (float)m_params.numChannels;
    }
    case cr::vtracker::VTrackerParam::TYPE:
    {
        return (float)m_params.type;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_1:
    {
        return (float)m_params.custom1;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_2:
    {
        return (float)m_params.custom2;
    }
    case cr::vtracker::VTrackerParam::CUSTOM_3:
    {
        return (float)m_params.custom3;
    }
    default:
    {
        return -1.0f;
    }
    }

    return -1.0f;
}



cr::vtracker::VTrackerParams cr::vtracker::CustomVTracker::getParams()
{
    return m_params;
}



bool cr::vtracker::CustomVTracker::executeCommand(
                    cr::vtracker::VTrackerCommand id,
                    float arg1,
                    float arg2,
                    float arg3)
{
    // Check command ID.
    switch (id)
    {
    case cr::vtracker::VTrackerCommand::CAPTURE:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::CAPTURE_PERCENTS:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::RESET:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_INERTIAL_MODE:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_LOST_MODE:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_STATIC_MODE:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::ADJUST_RECT_SIZE:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::ADJUST_RECT_POSITION:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::MOVE_RECT:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_RECT_POSITION:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_RECT_POSITION_PERCENTS:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::MOVE_SEARCH_WINDOW:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_SEARCH_WINDOW_POSITION:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::SET_SEARCH_WINDOW_POSITION_PERCENTS:
    {
        return true;
    }
    case cr::vtracker::VTrackerCommand::CHANGE_RECT_SIZE:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }

    return false;
}



bool cr::vtracker::CustomVTracker::processFrame(cr::video::Frame& frame)
{
    return true;
}



void cr::vtracker::CustomVTracker::getImage(int type, cr::video::Frame& image)
{

}
