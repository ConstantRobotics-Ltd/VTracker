#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include "VTracker.h"



namespace rapidpixel
{
/**
 * @brief Custom video tracker class. Example of VTracker interface
 * implementation: it validates all values received from outside and protects
 * the params by a mutex, so all methods can be called from any thread.
 */
class CustomVTracker : public VTracker
{
public:

    /**
     * @brief Class constructor.
     */
    CustomVTracker();

    /**
     * @brief Class destructor.
     */
    ~CustomVTracker() override;

    /**
     * @brief Copy constructor is deleted (the class owns a mutex).
     */
    CustomVTracker(const CustomVTracker&) = delete;

    /**
     * @brief Move constructor is deleted (the class owns a mutex).
     */
    CustomVTracker(CustomVTracker&&) = delete;

    /**
     * @brief Copy assignment is deleted (the class owns a mutex).
     * @return Reference to this object.
     */
    CustomVTracker& operator= (const CustomVTracker&) = delete;

    /**
     * @brief Move assignment is deleted (the class owns a mutex).
     * @return Reference to this object.
     */
    CustomVTracker& operator= (CustomVTracker&&) = delete;

    /**
     * @brief Get string of current class version.
     * @return String of current class version.
     */
    static std::string getVersion();

    /**
     * @brief Init video tracker.
     * @param params Video tracker params. Values are checked.
     * @return TRUE if the params are valid and the video tracker initialized
     * or FALSE if not. The current params are not changed in case of error.
     */
    bool initVTracker(VTrackerParams& params) override;

    /**
     * @brief Set video tracker param.
     * @param id Param ID.
     * @param value Param value. Integer params must be finite and inside the
     * range of int.
     * @return TRUE if the param was set or FALSE if the param ID is unknown
     * or the value is not valid.
     */
    bool setParam(VTrackerParam id, float value) override;

    /**
     * @brief Get video tracker param value.
     * @param id Param ID.
     * @return Param value or -1 if the param ID is unknown.
     */
    float getParam(VTrackerParam id) override;

    /**
     * @brief Get video tracker params (results).
     * @param params Video tracker params structure.
     */
    void getParams(VTrackerParams& params) override;

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @param arg1 First argument. Value depends on command ID.
     * @param arg2 Second argument. Value depends on command ID.
     * @param arg3 Third argument. Value depends on command ID.
     * @return TRUE if the command accepted or FALSE if the command ID is
     * unknown.
     */
    bool executeCommand(VTrackerCommand id,
                        float arg1 = 0,
                        float arg2 = 0,
                        float arg3 = 0) override;

    /**
     * @brief Process frame.
     * @param frame Source video frame.
     * @return TRUE if the frame was processed.
     */
    bool processFrame(rapidpixel::Frame& frame) override;

    /**
     * @brief Get image of internal surfaces.
     * @param type Type of image to get.
     * @param image Output frame.
     */
    void getImage(int type, rapidpixel::Frame& image) override;

    /**
     * @brief Decode and execute command.
     * @param data Pointer to command data.
     * @param size Size of data, bytes.
     * @return TRUE if the command decoded and executed or FALSE if not.
     */
    bool decodeAndExecuteCommand(uint8_t* data, int size) override;

private:

    /// Video tracker params. Protected by m_paramsMutex.
    VTrackerParams m_params;
    /// Mutex to protect m_params.
    std::mutex m_paramsMutex;
};
}
