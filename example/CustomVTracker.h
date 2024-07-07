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
    bool initVTracker(VTrackerParams& params) override;

    /// Set video tracker param.
    bool setParam(VTrackerParam id, float value) override;

    /// Get video tracker param value.
    float getParam(VTrackerParam id) override;

    /// Get video tracker params (results).
    void getParams(VTrackerParams& params) override;

    /// Execute command.
    bool executeCommand(VTrackerCommand id,
                                float arg1 = 0,
                                float arg2 = 0,
                                float arg3 = 0) override;

    /// Process frame.
    bool processFrame(cr::video::Frame& frame) override;

    /// Get image of internal surfaces.
    void getImage(int type, cr::video::Frame& image) override;

public:

    /// Video tracker params (default params).
    VTrackerParams m_params;
};
}
}




