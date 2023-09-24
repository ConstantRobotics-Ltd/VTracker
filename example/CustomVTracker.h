#pragma once
#include "VTracker.h"



namespace cr
{
namespace vtracker
{
/// Custom video tracker class.
class CustomVTracker: public VTracker
{
public:

    /// Class constructor.
    CustomVTracker();

    /// Class destructor.
    ~CustomVTracker();

    /// Get string of current library version.
    static std::string getVersion();

    /// Init video tracker.
    bool initVTracker(VTrackerParams& params);

    /// Set video tracker param.
    bool setParam(VTrackerParam id, float value);

    /// Get video tracker param value.
    float getParam(VTrackerParam id);

    /// Get video tracker params (results).
    VTrackerParams getParams();

    /// Execute command.
    bool executeCommand(VTrackerCommand id,
                                float arg1 = 0,
                                float arg2 = 0,
                                float arg3 = 0);

    /// Process frame.
    bool processFrame(cr::video::Frame& frame);

    /// Get image of internal surfaces.
    void getImage(int type, cr::video::Frame& image);

public:

    /// Video tracker params (default params).
    VTrackerParams m_params;
};
}
}




