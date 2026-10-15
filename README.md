![vtracker_logo](./static/vtracker_web_logo.png)



# **VTracker interface C++ library**

**v1.4.6**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [Required operating principles](#required-operating-principles)
- [VTracker class description](#vtracker-class-description)
  - [VTracker class declaration](#vtracker-class-declaration)
  - [getVersion method](#getversion-method)
  - [initVTracker method](#initvtracker-method)
  - [setParam method](#setparam-method)
  - [getParam method](#getparam-method)
  - [getParams method](#getparams-method)
  - [executeCommand method](#executecommand-method)
  - [processFrame method](#processframe-method)
  - [getImage method](#getimage-method)
  - [encodeSetParamCommand method](#encodesetparamcommand-method)
  - [encodeCommand method](#encodecommand-method)
  - [decodeCommand method](#decodecommand-method)
  - [decodeAndExecuteCommand method](#decodeandexecutecommand-method)
- [Data structures](#data-structures)
  - [VTrackerCommand enum](#vtrackercommand-enum)
  - [VTrackerParam enum](#vtrackerparam-enum)
- [VTrackerParams class description](#vtrackerparams-class-description)
  - [VTrackerParams class declaration](#vtrackerparams-class-declaration)
  - [Serialize video tracker params](#serialize-video-tracker-params)
  - [Deserialize video tracker params](#deserialize-video-tracker-params)
  - [Read params from JSON file and write to JSON file](#read-params-from-json-file-and-write-to-json-file)
- [Build and connect to your project](#build-and-connect-to-your-project)
  - [Build stand alone](#build-stand-alone)
  - [CMake options](#cmake-options)
  - [Connect to your project](#connect-to-your-project)
- [How to make custom implementation](#how-to-make-custom-implementation)
- [Portability](#portability)
- [Testing](#testing)



# Overview

**VTracker** C++ library provides standard interface as well defines data structures and rules for different video trackers. **VTracker** interface class does nothing, just provides interface, defines data structures and provides methods to encode/decode commands and encode/decode params. Different video trackers inherit interface form **VTracker** C++ class. **VTracker.h** file contains list of data structures ([VTrackerCommand enum](#vtrackercommand-enum), [VTrackerParam enum](#vtrackerparam-enum) and [VTrackerParams class](#vtrackerparams-class-description)) and **VTracker** class declaration. [VTrackerParams class](#vtrackerparams-class-description) contains video tracker params and includes methods to encode and decode params. [VTrackerCommand enum](#vtrackercommand-enum) contains IDs of commands. [VTrackerParam enum](#vtrackerparam-enum) contains IDs of params. All video trackers should include params and commands listed in **VTracker.h** file. **VTracker** interface class depends on [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class (describes video frame and video frame data structures) and [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library (provides methods to read/write JSON config files). The source code of these libraries is not included in the **VTracker** repository: the repositories must be placed in the same folder as the **VTracker** repository (see [Build and connect to your project](#build-and-connect-to-your-project) section). It uses C++17 standard.



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | 20.07.2023   | First version.                                               |
| 1.1.0   | 10.08.2023   | - Data structures updated.                                   |
| 1.2.0   | 24.09.2023   | - Updated encode(...) and decode(...) methods of VTrackerParams.<br />- Added decodeAndExecuteCommand(...) method.<br />- Added example of video tracker implementation. |
| 1.3.0   | 26.09.2023   | - Signature of getParams(...) method changed.                |
| 1.3.1   | 13.11.2023   | - Frame class updated.                                       |
| 1.4.1   | 13.12.2023   | - Virtual destructor added. <br />- Frame class updated.     |
| 1.4.2   | 19.03.2024   | - Documentation updated.<br />- Frame class updated.<br />- ConfigReader class updated. |
| 1.4.3   | 21.05.2024   | - Documentation updated.<br />- Submodules updated.          |
| 1.4.4   | 06.07.2024   | - CMake updated.<br />- Submodules updated.                  |
| 1.4.5   | 28.09.2026   | - Submodules updated.<br />- Compiler warnings fixed.        |
| 1.4.6   | 15.10.2026   | - Sub-repositories (Frame, ConfigReader) removed.<br />- Hardening options of the compilers and the linkers added.<br />- **Fixed:** decodeCommand(...) returned 0 (command decoded) for a command of wrong size.<br />- **Security:** decodeCommand(...) accepts only exact sizes (11 or 19 bytes) and known IDs, decode(...) of VTrackerParams does not change the object if the data is invalid, null pointers are rejected.<br />- Tests extended (invalid data, damaged data, JSON), example of video tracker rewritten (validation of values, thread safety, decodeAndExecuteCommand(...) implemented).<br />- Documentation and code comments updated. |



# Library files

The library supplied by source code only. The user would be given a set of files in the form of a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ------------------ Main CMake file of the library.
example ------------------------- Folder with custom video tracker class.
    CMakeLists.txt -------------- CMake file for custom video tracker class.
    CustomVTracker.cpp ---------- C++ implementation file.
    CustomVTracker.h ------------ Header with CustomVTracker class declaration.
    CustomVTrackerVersion.h ----- Header file which includes CustomVTracker version.
    CustomVTrackerVersion.h.in -- CMake service file to generate version file.
test ---------------------------- Folder with VTracker test application.
    CMakeLists.txt -------------- CMake file for VTracker test application.
    main.cpp -------------------- Source code file of VTracker class test application.
src ----------------------------- Folder with source code of the library.
    CMakeLists.txt -------------- CMake file of the library.
    VTracker.cpp ---------------- C++ implementation file.
    VTracker.h ------------------ Header file which includes VTracker class declaration.
    VTrackerVersion.h ----------- Header file which includes version of the library.
    VTrackerVersion.h.in -------- CMake service file to generate version file.
```



# Required operating principles

The video tracker shall provide the following principle of operation: each video frame without dropping must be send to the tracker for processing regardless of the current tracker operation mode. If the tracker is not in tracking mode, the tracker does not perform frame processing, but the processing function must be called by user. Tracker should calculate at least tracking rectangle position (aka object position) for each processed video frame. Figure 1 shows basic principles of object search on video frames.

![vtracker_algorithm_principle](./static/vtracker_algorithm_principle.png)

**Figure 1** - Basic principles of object search. (**1** - object image on the current frame, **2** - tracking rectangle calculated after processing of the current frame, **3** - position of the tracking rectangle on the previous frame, **4** - object search window on the current frame relative to the position of the tracking rectangle on the previous frame, **5** - current video frame).

At the moment of object capturing, the rectangular area of the video frame (capture rectangle) specified in the capture parameters (position and size) is taken as the object reference image, on the basis of which the pattern is formed. The algorithm then searches an object in each frame of the video in particular search window. Search window is area bounded by the algorithm's parameters with the center coinciding with the calculated center of the tracking rectangle on the previous video frame (or the center of the capture rectangle if the first frame after capture is being processed, position of search window can be change by user for any video frame). The calculated most probable position of the tracking object (with highest value of correlation function) in the current video frame (calculated center of the tracking rectangle) is taken as the coordinates of the object. Figure 1 shows a schematic representation of a video frame **(5)** that contains an image of a object **(1)**. Assume that on the previous video frame the object was in the area corresponding to area **(3)**, which is the area of the tracking rectangle (the most probable position of the object) in the previous video frame. The library performs object search in the area **(4)** whose center coincides with the position of the center of the tracking rectangle **(3)** in the previous video frame. Tracker should support (if it possible) follow modes.

**Table 2** - Tracking algorithm operating modes.

| Mode                                | Description                                                  |
| ----------------------------------- | ------------------------------------------------------------ |
| FREE - free mode.                   | In this mode, video tracker does not perform any calculations. Video tracker only adds video frames to the frame buffer or drop frame if no frame buffer in particular implementation. Conditions for entering FREE mode: **1.** Once the video tracker has been initialized. This mode is the default mode. **2.** Automatically when the automatic tracking reset criteria are met. **3.** After command RESET. |
| TRACKING - tracking mode.           | In this mode the video tracker calculates the automatic tracking and updates all calculated (estimated) object parameters. Criteria for entering TRACKING mode: **1.** After the CAPTURE command. **2.** Automatically from LOST mode when object detection criteria are met. |
| LOST - object loss  mode.           | In this mode, the video tracker searches object for automatic recapturing (switching to TRACKING mode) and updates it’s coordinates in one of the ways specified  in the parameters. LOST mode contains the following additional modes: **0.** Tracking rectangle coordinates are not updated (remain the same as  before entering LOST mode). **1.** The tracking rectangle coordinates are updated based on the components of the object's speed calculated before going into LOST mode. When the tracking rectangle reaches any edge of the frame, the coordinate update in the corresponding direction stops. **2.** The tracking rectangle coordinates are updated based on the components of the speed of objects in the video frames calculated before going into LOST mode. When the tracking reset criteria is met, the device switches to FREE mode. Criteria for entering LOST mode: **1.** Automatically when object loss is detected. **2.** On command from TRACKING mode. 3. On command from INERTIAL mode. 4. On command from STATIC mode. |
| INERTIAL - inertial  tracking mode. | In this mode the video tracker does not search for an object to recapture automatically, but only updates the coordinates of the tracking rectangle based on the previously calculated velocity components of the objects. Criteria for entering INERTIAL mode: **1.** On command from TRACKING mode. **2.** On command from LOST mode. **3.** On command from STATIC mode. |
| STATIC - static  mode.              | This mode does not perform any calculations and the tracking rectangle coordinates remain the same as before going into this mode. This mode is  necessary to “freeze” the tracking algorithm for a certain number of frames. For example, if the tracking system is exposed to strong vibrations, it is possible to “freeze” the tracking algorithm until the vibration ends. |

Figure 2 shows the operating mode graph and the possible transitions between them. The words "Auto" in figure 2 indicate the ability to change the mode automatically if the relevant criteria are met. the words "Command" indicated the ability to change mode by user's command.

![vtracker_algorithm_modes](./static/vtracker_algorithm_modes.png)

**Figure 2** - Operation modes of the tracking algorithm. ("Auto" – automatic mode change capability).

Figure 2 shows the graph of operation modes. There are the following conditions for automatic mode changes (word “Auto” in figure 2): **1.** Automatic switching from TRACKING to FREE mode is possible only if the tracking rectangle center has touched (coincided in coordinates) any of the video frame edges. **2.** The automatic switching from TRACKING to LOST mode is possible when an object loss is detected – when the calculated object detection probability falls below the threshold. **3.** Automatic switching from LOST to TRACKING mode is possible when an object is detected again after a loss - when the calculated object detection probability exceeds the threshold. **4.** Automatic reset of tracking in the LOST mode (switch to FREE mode) is possible when the center of the tracking rectangle touches the edge of the video frame (if the LOST mode option set to 2), as well as when the number of frames specified in the parameters has  expired, at which the algorithm is continuously in LOST mode. **5.** Automatic reset of tracking in INERTIAL mode (switch to FREE mode) is possible when the  center of the tracking rectangle reaches the edge of the frame.



# VTracker class description



## VTracker class declaration

**VTracker** interface class declared in **VTracker.h** file. Class declaration:

```cpp
namespace cr
{
namespace vtracker
{
class VTracker
{
public:

    /// Class destructor.
    virtual ~VTracker();

    /// Get string of current library version.
    static std::string getVersion();

    /// Init video tracker.
    virtual bool initVTracker(VTrackerParams& params) = 0;

    /// Set video tracker param.
    virtual bool setParam(VTrackerParam id, float value) = 0;

    /// Get video tracker param value.
    virtual float getParam(VTrackerParam id) = 0;

    /// Get video tracker params (results).
    virtual void getParams(VTrackerParams& params) = 0;

    /// Execute command.
    virtual bool executeCommand(VTrackerCommand id,
                                float arg1 = 0,
                                float arg2 = 0,
                                float arg3 = 0) = 0;

    /// Process frame.
    virtual bool processFrame(cr::video::Frame& frame) = 0;

    /// Get image of internal surfaces.
    virtual void getImage(int type, cr::video::Frame& image) = 0;

    /// Encode set param command.
    static void encodeSetParamCommand(
            uint8_t* data, int& size, VTrackerParam id, float value);

    /// Encode command.
    static void encodeCommand(
            uint8_t* data, int& size, VTrackerCommand id,
            float arg1 = 0, float arg2 = 0, float arg3 = 0);

    /// Decode command.
    static int decodeCommand(uint8_t* data,
                             int size,
                             VTrackerParam& paramId,
                             VTrackerCommand& commandId,
                             float& value1,
                             float& value2,
                             float& value3);

    /// Decode and execute command.
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;

protected:

    /// Default constructor. The class can be used as a base only.
    VTracker() = default;

    /// Copy constructor.
    VTracker(const VTracker& src) = default;

    /// Move constructor.
    VTracker(VTracker&& src) = default;

    /// Copy assignment operator.
    VTracker& operator= (const VTracker& src) = default;

    /// Move assignment operator.
    VTracker& operator= (VTracker&& src) = default;
};
}
}
```

The class has no data members, the constructors and assignment operators are protected: the class can be used as a base class only.



## getVersion method

The **getVersion()** method returns string of current version of **VTracker** class. Particular video tracker can have it's own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **VTracker** class instance:

```cpp
std::cout << "VTracker class version: " << VTracker::getVersion() << std::endl;
```

Console output:

```bash
VTracker class version: 1.4.6
```



## initVTracker method

The **initVTracker(...)** method initializes video tracker by set of parameters. Method declaration:

```cpp
virtual bool initVTracker(VTrackerParams& params) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| params    | Video tracker params class. Video tracker should initialize all parameters listed in [VTrackerParams class](#vtrackerparams-class-description). |

**Returns:** TRUE if the video tracker initialized or FALSE if not.



## setParam method

The **setParam(...)** method sets new video tracker parameter value. The particular implementation of the video tracker must provide thread-safe **setParam(...)** method call. This means that the **setParam(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool setParam(VTrackerParam id, float value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Parameter ID according to [VTrackerParam enum](#vtrackerparam-enum). |
| value     | Parameter value. Value depends on parameter ID.              |

**Returns:** TRUE if the parameter was set or FALSE if not.



## getParam method

The **getParam(...)** method returns video tracker parameter value. The particular implementation of the video tracker must provide thread-safe **getParam(...)** method call. This means that the **getParam(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual float getParam(VTrackerParam id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Parameter ID according to [VTrackerParam enum](#vtrackerparam-enum). |

**Returns:** parameter value or -1 of the parameters doesn't exist in particular video tracker.



## getParams method

The **getParams(...)** method returns video tracker params class and tracking results. The particular implementation of the video tracker must provide thread-safe **getParams(...)** method call. This means that the **getParams(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual void getParams(VTrackerParams& params) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| params    | Video tracker parameters class object ([VTrackerParams](#vtrackerparams-class-description) object). |



## executeCommand method

The **executeCommand(...)** method executes video tracker command. The particular implementation of the video tracker must provide thread-safe **executeCommand(...)** method call. This means that the **executeCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool executeCommand(VTrackerCommand id, float arg1 = 0, float arg2 = 0, float arg3 = 0) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Command ID according to [VTrackerCommand enum](#vtrackercommand-enum). |
| arg1      | First argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |
| arg2      | Second argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |
| arg3      | Third argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |

**Returns:** TRUE is the command was executed or FALSE if not.



## processFrame method

The **processFrame(...)** method processes video frame. Method declaration:

```cpp
virtual bool processFrame(cr::video::Frame& frame) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| frame     | Video frame for processing. Video tracker processes only RAW pixel formats (BGR24, RGB24, GRAY, YUYV24, YUYV, UYVY, NV12, NV21, YV12, YU12, see [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class description). Video trackers should implement all RAW pixel format listed above. |

**Returns:** TRUE is the video frame was processed FALSE if not. If video tracker not in tracking mode the method should return TRUE.



## getImage method

The **getImage(...)** method designed to obtain images of internal matrixes. Depends on implementation. Method declaration:

```cpp
virtual void getImage(int type, cr::video::Frame& image) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| type      | Image type. Depends on implementation.                       |
| frame     | Output frame (see [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class description). Pixel format depends on implementation. |



## encodeSetParamCommand method

The **encodeSetParamCommand(...)** static method designed to encode command to change any parameter in remote video tracker. To control video tracker remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VTracker** class contains static methods for encoding the control command. The **VTracker** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeSetParamCommand(...)** designed to encode SET_PARAM command. Method declaration:

```cpp
static void encodeSetParamCommand(uint8_t* data, int& size, VTrackerParam id, float value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must not be nullptr, must have size >= 11. |
| size      | Size of encoded data. Will be 11 bytes (0 if **data** is nullptr). |
| id        | Parameter ID according to [VTrackerParam enum](#vtrackerparam-enum). |
| value     | Parameter value. Value depends on parameter ID (see [VTrackerParam enum](#vtrackerparam-enum) description). |

**encodeSetParamCommand(...)** is static and used without **VTracker** class instance. This method used on client side (control system). Command encoding example:

```cpp
uint8_t data[1024];
int size = 0;
float outValue = static_cast<float>(rand() % 20);
VTracker::encodeSetParamCommand(
        data, size, VTrackerParam::MULTIPLE_THREADS, outValue);
```



## encodeCommand method

The **encodeCommand(...)** static method designed to encode command for remote video tracker. To control video tracker remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VTracker** class contains static methods for encoding the control command. The **VTracker** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeCommand(...)** designed to encode COMMAND (action command). Method declaration:

```cpp
static void encodeCommand(uint8_t* data, int& size, VTrackerCommand id, float arg1 = 0, float arg2 = 0, float arg3 = 0);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must not be nullptr, must have size >= 19. |
| size      | Size of encoded data. Will be 19 bytes (0 if **data** is nullptr). |
| id        | Command ID according to [VTrackerCommand enum](#vtrackercommand-enum). |
| arg1      | First argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |
| arg2      | Second argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |
| arg3      | Third argument. Value depends on command ID (see [VTrackerCommand enum](#vtrackercommand-enum) description). |

**encodeCommand(...)** is static and used without **VTracker** class instance. This method used on client side (control system). Command encoding example:

```cpp
uint8_t data[1024];
int size = 0;
float outValue = static_cast<float>(rand() % 20);
float arg1 = static_cast<float>(rand() % 20);
float arg2 = static_cast<float>(rand() % 20);
float arg3 = static_cast<float>(rand() % 20);
VTracker::encodeCommand(data, size, VTrackerCommand::CAPTURE, arg1, arg2, arg3);
```



## decodeCommand method

The **decodeCommand(...)** static method designed to decode command on video tracker side (edge device) which encoded by [encodeSetParamCommand(...)](#encodesetparamcommand-method) or [encodeCommand(...)](#encodecommand-method) methods. Method declaration:

```cpp
static int decodeCommand(uint8_t* data, int size, VTrackerParam& paramId, VTrackerCommand& commandId, float& value1, float& value2, float& value3);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command. Must not be nullptr.               |
| size      | Size of command. Must be exactly 11 bytes for SET_PARAM or exactly 19 bytes for COMMAND. |
| paramId   | Parameter ID according to [VTrackerParam enum](#vtrackerparam-enum). After decoding SET_PARAM command the method will return parameter ID. |
| commandId | Command ID according to [VTrackerCommand enum](#vtrackercommand-enum). After decoding COMMAND the method will return command ID. |
| value1    | Parameter value (SET_PARAM) or first command argument (COMMAND). |
| value2    | Second command argument. After decoding COMMAND.             |
| value3    | Third command argument. After decoding COMMAND.              |

**Returns:** **0** - in case decoding COMMAND, **1** - in case decoding SET_PARAM command or **-1** in case errors: null pointer, wrong size, wrong version (the first two numbers of the library version must be equal to the version of the library which encoded the command), unknown data type or unknown command / parameter ID (IDs must be inside the range of [VTrackerCommand enum](#vtrackercommand-enum) / [VTrackerParam enum](#vtrackerparam-enum)). In case of an error **paramId** and **commandId** are not changed. The values of the arguments (**value1**, **value2**, **value3**) are not checked: the video tracker must validate them before use.

**decodeCommand(...)** is static and used without **VTracker** class instance. Command decoding example:

```cpp
// Encode command.
uint8_t data[1024];
int size = 0;
float outValue = static_cast<float>(rand() % 20);
float arg1 = static_cast<float>(rand() % 20);
float arg2 = static_cast<float>(rand() % 20);
float arg3 = static_cast<float>(rand() % 20);
VTracker::encodeCommand(data, size, VTrackerCommand::CAPTURE, arg1, arg2, arg3);

// Decode command.
VTrackerCommand commandId;
VTrackerParam paramId;
float inArg1 = static_cast<float>(rand() % 20);
float inArg2 = static_cast<float>(rand() % 20);
float inArg3 = static_cast<float>(rand() % 20);
if (VTracker::decodeCommand(data, size, paramId, commandId, inArg1, inArg2, inArg3) != 0)
{
    std::cout << "Command not decoded" << std::endl;
    return false;
}
```



## decodeAndExecuteCommand method

The **decodeAndExecuteCommand(...)** method decodes and executes command on video tracker side. The particular implementation of the video tracker must provide thread-safe **decodeAndExecuteCommand(...)** method call. This means that the **decodeAndExecuteCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command.                                    |
| size      | Size of command. Must be exactly 11 bytes for SET_PARAM or exactly 19 bytes for COMMAND. |

**Returns:** TRUE if command decoded (SET_PARAM or COMMAND) and executed (action command or set param command). A particular implementation should call [decodeCommand(...)](#decodecommand-method) and must return FALSE if the decoding fails.



# Data structures



## VTrackerCommand enum

**VTrackerCommand** enum describes commands supported by video tracker. **VTrackerCommand** enum declared in **VTracker.h** file. Enum declaration:

```cpp
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
```

**Table 3** - Video tracker commands description. Some commands maybe unsupported by particular video tracker class. Recommended arguments for **executeCommand(...)** and **encodeCommand(...)**.

| Command                             | Description                                                  |
| ----------------------------------- | ------------------------------------------------------------ |
| CAPTURE                             | Object capture. Arguments: arg1 - Capture rectangle center X coordinate. -1 - default coordinate, arg2 - Capture rectangle center Y coordinate. -1 - default coordinate, arg3 - frame ID. -1 - Capture on last frame. |
| CAPTURE_PERCENTS                    | Object capture command. Arguments: arg1 - Capture rectangle center X coordinate, percents of frame width, arg2 - Capture rectangle center Y coordinate, percents of frame height. |
| RESET                               | Reset command. No arguments.                                 |
| SET_INERTIAL_MODE                   | Set INERTIAL mode. No arguments.                             |
| SET_LOST_MODE                       | Set LOST mode. No arguments.                                 |
| SET_STATIC_MODE                     | Set STATIC mode. No arguments.                               |
| ADJUST_RECT_SIZE                    | Adjust tracking rectangle size automatically once. No arguments. |
| ADJUST_RECT_POSITION                | Adjust tracking rectangle position automatically once. No arguments. |
| MOVE_RECT                           | Move tracking rectangle (change position). Arguments: arg1 - add to X coordinate, pixels. 0 - no change, arg2 - add to Y coordinate, pixels. 0 - no change. |
| SET_RECT_POSITION                   | Set tracking rectangle position in FREE mode. Arguments: arg1 - Rectangle center X coordinate, arg2 - Rectangle center Y coordinate. |
| SET_RECT_POSITION_PERCENTS          | Set tracking rectangle position in FREE mode in percents of frame size. Arguments: arg1 - Rectangle center X coordinate, percents of frame width, arg2 - Rectangle center Y coordinate, percents of frame height. |
| MOVE_SEARCH_WINDOW                  | Move search window (change position). Arguments: arg1 - add to X coordinate, pixels. 0 - no change, arg2 - add to Y coordinate, pixels. 0 - no change. |
| SET_SEARCH_WINDOW_POSITION          | Set search window position. Arguments: arg1 - Search window center X coordinate, arg2 - Search window center Y coordinate. |
| SET_SEARCH_WINDOW_POSITION_PERCENTS | Set search window position in percents of frame size. Arguments: arg1 - Search window center X coordinate, percents of frame width, arg2 - Search window center Y coordinate, percents of frame height. |
| CHANGE_RECT_SIZE                    | Change tracking rectangle size. Arguments: arg1 - horizontal size add, pixels, arg2 - vertical size add, pixels. |



## VTrackerParam enum

**VTrackerParam** enum describes parameters supported by video tracker. **VTrackerParam** enum declared in **VTracker.h** file. Enum declaration:

```cpp
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
```

**Table 4** - Video tracker params description. Some params maybe unsupported by particular video tracker.

| Parameter               | Access       | Description                                                  |
| ----------------------- | ------------ | ------------------------------------------------------------ |
| SEARCH_WINDOW_WIDTH     | read / write | Width of search window, pixels. Set by user. (see **Required operating principles**). |
| SEARCH_WINDOW_HEIGHT    | read / write | Height of search window, pixels. Set by user. (see **Required operating principles**). |
| RECT_WIDTH              | read / write | Tracking rectangle width, pixels. (see **Required operating principles**). Set by user or can be changed by tracking algorithm if RECT_AUTO_SIZE == 1. |
| RECT_HEIGHT             | read / write | Tracking rectangle height, pixels (see **Required operating principles**). Set by user or can be changed by tracking algorithm if RECT_AUTO_SIZE == 1. |
| LOST_MODE_OPTION        | read / write | Option for LOST mode. Parameter that defines the behavior of the tracking  algorithm in LOST mode. Default is 0. Possible values:<br />**0.** In LOST mode, the coordinates of the center of the  tracking rectangle are not updated and remain the  same as before entering LOST mode.<br />**1.** The coordinates of the center of the tracking  rectangle are updated based on the components  of the object’s speed calculated before going into  LOST mode. If the tracking rectangle “touches” the  edge of the video frame, the coordinate updating  for this component (horizontal or vertical) will stop.<br />**2.** The coordinates of the center of the tracking  rectangle are updated based on the components  of the object’s speed calculated before going into  LOST mode. The tracking is reset if the center of  the tracking rectangle touches any of the edges of  the video frame. |
| FRAME_BUFFER_SIZE       | read / write | Size of frame buffer (number of frames to store). Set by user. |
| MAX_FRAMES_IN_LOST_MODE | read / write | Maximum number of frames in LOST mode to auto reset of algorithm. Set by user. |
| RECT_AUTO_SIZE          | read / write | Use tracking rectangle auto size flag: 0 - no use, 1 - use. Set by user. |
| RECT_AUTO_POSITION      | read / write | Use tracking rectangle auto position: 0 - no use, 1 - use. Set by user. |
| MULTIPLE_THREADS        | read / write | Use multiple threads for calculations. 0 - one thread, 1 - multiple. Set by user. |
| NUM_CHANNELS            | read / write | Number of channels for processing. E.g., number of color channels. Set by user. |
| TYPE                    | read / write | Tracker type. Depends on implementation. Set by user.        |
| CUSTOM_1                | read / write | Custom parameter. Depends on implementation.                 |
| CUSTOM_2                | read / write | Custom parameter. Depends on implementation.                 |
| CUSTOM_3                | read / write | Custom parameter. Depends on implementation.                 |



# VTrackerParams class description



## VTrackerParams class declaration

**VTrackerParams** class used for video tracker initialization (**initVTracker(...)** method) or to get all actual params and tracking results (**getParams()** method). Also **VTrackerParams** provide structure to write/read params from JSON files (**JSON_READABLE** macro, see [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) class description) and provides methods to encode and decode params. Class declaration:

```cpp
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
    /// Estimated vertical position of object center, pixels.Calculated by
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

    JSON_READABLE(VTrackerParams, rectWidth, rectHeight, searchWindowWidth,
                  searchWindowHeight, lostModeOption, frameBufferSize,
                  maxFramesInLostMode, rectAutoSize, rectAutoPosition,
                  multipleThreads, numChannels, type, custom1, custom2, custom3)

    /// Default constructor.
    VTrackerParams() = default;

    /// Copy constructor.
    VTrackerParams(const VTrackerParams& src) = default;

    /// operator =
    VTrackerParams& operator= (const VTrackerParams& src) = default;

    /// Encode params.
    bool encode(uint8_t* data, int bufferSize,
                int& size, VTrackerParamsMask* mask = nullptr);

    /// Decode params.
    bool decode(uint8_t* data, int dataSize);
};
```

**Table 5** - VTrackerParams class fields description.

| Field                | Type  | Description                                                  |
| -------------------- | ----- | ------------------------------------------------------------ |
| mode                 | int   | Tracker mode index: 0 - FREE, 1 - TRACKING, 2 - INERTIAL, 3 - STATIC. Set by video tracker according to processing results or after command execution. |
| rectX                | int   | Tracking rectangle horizontal center position, pixels. Calculated by tracking algorithm. |
| rectY                | int   | Tracking rectangle vertical center position, pixels. Calculated by tracking algorithm. |
| rectWidth            | int   | Tracking rectangle width, pixels. Set by user or can be changed by tracking algorithm if rectAutoSize == true. |
| rectHeight           | int   | Tracking rectangle height, pixels. Set by user or can be changed by tracking algorithm if rectAutoSize == true. |
| objectX              | int   | Estimated horizontal position of object center, pixels. Calculated by video tracker. |
| objectY              | int   | Estimated vertical position of object center, pixels. Calculated by video tracker. |
| objectWidth          | int   | Estimated object width, pixels. Calculated by video tracker. |
| objectHeight         | int   | Estimated object height, pixels. Calculated by video tracker. |
| lostModeFrameCounter | int   | Frame counter in LOST mode. After switching in LOST mode the video tracker start counting from 0. After switching to another mode from LOST mode the video tracker will reset this counter. |
| frameCounter         | int   | Counter for processed frames after capture object. After reset tracking the video tracker will reset counter. |
| frameWidth           | int   | Width of processed video frame. Set by video tracker after processing first video frame. |
| frameHeight          | int   | Height of processed video frame. Set by video tracker after processing first video frame. |
| searchWindowWidth    | int   | Width of search window, pixels. Set by user.                 |
| searchWindowHeight   | int   | Height of search window, pixels. Set by user.                |
| searchWindowX        | int   | Horizontal position of search window center. This position will be used for next video frame. Usually it coincides with data tracking rectangle center but can be set by user to move search window for new video frame. |
| searchWindowY        | int   | Vertical position of search window center. This position will be used for next video frame. Usually it coincides with data tracking rectangle center but can be set by user to move search window for new video frame. |
| lostModeOption       | int   | Option for LOST mode. Parameter that defines the behavior of the tracking  algorithm in LOST mode. Default is 0. Possible values:<br/>**0.** In LOST mode, the coordinates of the center of the  tracking rectangle are not updated and remain the  same as before entering LOST mode.<br/>**1.** The coordinates of the center of the tracking  rectangle are updated based on the components  of the object’s speed calculated before going into  LOST mode. If the tracking rectangle “touches” the  edge of the video frame, the coordinate updating  for this component (horizontal or vertical) will stop.<br />**2.** The coordinates of the center of the tracking  rectangle are updated based on the components  of the object’s speed calculated before going into  LOST mode. The tracking is reset if the center of the tracking rectangle touches any of the edges of  the video frame. |
| frameBufferSize      | int   | Size of frame buffer (number of frames to store). Set by user. |
| maxFramesInLostMode  | int   | Maximum number of frames in LOST mode to auto reset of algorithm. Set by user. |
| processedFrameId     | int   | ID of last processed frame in frame buffer. Set by video tracker. |
| frameId              | int   | ID of last added frame to frame buffer. Set by video tracker. |
| velX                 | float | Horizontal velocity of object on video frames (pixel/frame). Calculated by video tracker. |
| velY                 | float | Vertical velocity of object on video frames (pixel/frame). Calculated by video tracker. |
| detectionProbability | float | Estimated probability of object detection. Calculated by video tracker. |
| rectAutoSize         | bool  | Use tracking rectangle auto size flag: false - no use, true - use. Set by user. |
| rectAutoPosition     | bool  | Use tracking rectangle auto position: false - no use, true - use. Set by user. |
| multipleThreads      | bool  | Use multiple threads for calculations. Set by user.          |
| numChannels          | int   | Number of channels for processing. E.g., number of color channels. Set by user. |
| type                 | int   | Tracker type. Depends on implementation. Set by user.        |
| processingTimeMks    | int   | Processing time for last frame, mks. Calculated by video tracker. |
| custom1              | float | Custom parameter. Depends on implementation.                 |
| custom2              | float | Custom parameter. Depends on implementation.                 |
| custom3              | float | Custom parameter. Depends on implementation.                 |



## Serialize video tracker params

[VTrackerParams](#vtrackerparams-class-description) class provides method **encode(...)** to serialize video tracker params (fields of VTrackerParams class, see Table 5). Serialization of params necessary in case when you need to send params via communication channels. Method provides options to exclude particular parameters from serialization. To do this method inserts binary mask (5 bytes) where each bit represents particular parameter and **decode(...)** method recognizes it. The encoded data has the following layout: 1 byte data type (**0x02**), 2 bytes of the library version (major and minor numbers: data encoded by a library with other major or minor number is rejected by **decode(...)**), 5 bytes of the mask and the fields selected by the mask in the order of Table 5. Integer and float fields are stored as 4 bytes in the byte order of the host (little endian, see [Portability](#portability)), boolean fields as 1 byte (0 or 1). The first field (mode) is the most significant bit of the first mask byte. Method declaration:

```cpp
bool encode(uint8_t* data, int bufferSize, int& size, VTrackerParamsMask* mask = nullptr);
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| data       | Pointer to data buffer. Must not be nullptr.                 |
| bufferSize | Data buffer size. Must be at least **135** bytes (size of all fields), otherwise the method returns FALSE regardless of the mask. |
| size       | Size of encoded data. Set to 0 if the method returns FALSE.  |
| mask       | Parameters mask - pointer to **VTrackerParamsMask** structure. **VTrackerParamsMask** (declared in VTracker.h file) determines flags for each field (parameter) declared in [VTrackerParams class](#vtrackerparams-class-description). If the pointer is nullptr all fields are encoded. If the user wants to exclude a particular parameter from serialization, he should clear (set to false) the corresponding flag in the **VTrackerParamsMask** structure (all flags are true by default). |

**Returns:** TRUE if data encoded (serialized) or FALSE if not (**data** is nullptr or the buffer is too small).

**VTrackerParamsMask** structure declaration:

```cpp
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
```

Example without parameters mask:

```cpp
// Prepare random parameters.
VTrackerParams in;
in.mode = rand() % 255;
in.rectX = rand() % 255;
in.rectY = rand() % 255;

// Encode data.
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size))
{
    std::cout << "Can't encode data" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;
```

Example with parameters mask:

```cpp
// Prepare random parameters.
VTrackerParams in;
in.mode = rand() % 255;
in.rectX = rand() % 255;
in.rectY = rand() % 255;

// Prepare mask.
VTrackerParamsMask mask;
mask.mode = true;
mask.rectX = false;
mask.rectY = true;

// Encode data.
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size, &mask))
{
    std::cout << "Can't encode data" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;
```



## Deserialize video tracker params

[VTrackerParams](#vtrackerparams-class-description) class provides method **decode(...)** to deserialize params (fields of VTrackerParams class, see Table 5). Deserialization of params necessary in case when you need to receive params via communication channels. Method automatically recognizes which parameters were serialized by **encode(...)** method. Method declaration:

```cpp
bool decode(uint8_t* data, int dataSize);
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to encoded data buffer. Must not be nullptr.         |
| dataSize  | Size of the encoded data, bytes. Bytes after the last decoded field are ignored. |

**Returns:** TRUE if data decoded (deserialized) or FALSE if not (null pointer, data shorter than the header or than the fields selected by the mask, wrong data type or wrong version). If the method returns FALSE the object is not changed. Fields which are not selected by the mask are set to 0 (false for boolean fields). Any non zero byte of a boolean field is decoded as true. The method does not check the values of the fields (for example, **frameBufferSize** can be negative or very large): the video tracker must validate the values before use (see [Limits and guarantees](#limits-and-guarantees)).

Example:

```cpp
// Prepare random parameters.
VTrackerParams in;
in.mode = rand() % 255;
in.rectX = rand() % 255;
in.rectY = rand() % 255;

// Encode data.
uint8_t data[1024];
int size = 0;
if (!in.encode(data, 1024, size))
{
    std::cout << "Can't encode data" << std::endl;
    return false;
}
std::cout << "Encoded data size: " << size << " bytes" << std::endl;

// Decode data.
VTrackerParams out;
if (!out.decode(data, size))
{
    std::cout << "Can't decode data" << std::endl;
    return false;
}
```



## Read params from JSON file and write to JSON file

**VTracker** library depends on [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library which provides methods to read parameters from a JSON file and to write parameters to a JSON file. Example of writing to and reading from a JSON file:

```cpp
// Prepare random parameters.
VTrackerParams in;
in.mode = rand() % 255;
in.rectX = rand() % 255;
in.rectY = rand() % 255;

// Write parameters to the file.
cr::utils::ConfigReader inConfig;
if (!inConfig.set(in, "VTrackerParams") ||
    !inConfig.writeToFile("VTrackerParams.json"))
{
    std::cout << "Can't write config file" << std::endl;
    return false;
}

// Read parameters from the file.
cr::utils::ConfigReader outConfig;
if(!outConfig.readFromFile("VTrackerParams.json"))
{
    std::cout << "Can't open config file" << std::endl;
    return false;
}

// Obtain parameters from the config reader.
VTrackerParams out;
if(!outConfig.get(out, "VTrackerParams"))
{
    std::cout << "Can't read params from file" << std::endl;
    return false;
}
```

**VTrackerParams.json** will look like:

```json
{
    "VTrackerParams": {
        "rectWidth": 2,
        "rectHeight": 18,
        "searchWindowWidth": 195,
        "searchWindowHeight": 19,
        "lostModeOption": 65,
        "frameBufferSize": 130,
        "maxFramesInLostMode": 111,
        "rectAutoSize": true,
        "rectAutoPosition": true,
        "multipleThreads": true,
        "numChannels": 47,
        "type": 213,
        "custom1": 155.0,
        "custom2": 239.0,
        "custom3": 79.0
    }
}
```

Only the fields listed in the **JSON_READABLE** macro of [VTrackerParams class](#vtrackerparams-class-description) are stored in the file (the fields calculated by the video tracker are not stored). All these fields are required: if the file is not a valid JSON document, if the object is missing, if any field is missing or if a value can not be converted to the type of the field (a string, null, an array or an integer outside of the range of int), the **get(...)** method of **ConfigReader** returns FALSE and the params object is not changed. Numbers are converted to the type of the field (a fractional number is truncated for an integer field, any non zero number is true for a boolean field). The values are not checked against any range (for example, **frameBufferSize** can be negative or very large): the video tracker must validate the values before use (see [Limits and guarantees](#limits-and-guarantees)).



# Build and connect to your project



## Build stand alone

The **VTracker** repository does not contain sub-repositories. The libraries **VTracker** depends on (**Frame** and **ConfigReader**) must be cloned into the same folder as **VTracker**. The folder structure must be:

```bash
<work folder>
    VTracker
    Frame
    ConfigReader
```

Typical commands to build **VTracker** library, the test application and the example (use the URLs of the repositories provided to you):

```bash
git clone <VTracker repository URL>
git clone <Frame repository URL>
git clone <ConfigReader repository URL>
cd VTracker
mkdir build
cd build
cmake ..
make
```

On Windows use `cmake --build . --config Release` instead of `make`. The test application **VTrackerTest** is placed in the **bin** folder of the build folder. If **VTracker** is the top-level CMake project, the main **CMakeLists.txt** file adds the folders **../Frame** and **../ConfigReader** (in this order) before the library itself. If the folders do not exist CMake stops with an error.



## CMake options

**Table 6** - CMake options of the repository. In the options below **${PARENT}** is the prefix defined by the top-level project (empty if **VTracker** is the top-level project).

| Option                               | Default                                          | Description                                                  |
| ------------------------------------ | ------------------------------------------------ | ------------------------------------------------------------ |
| ${PARENT}_VTRACKER                   | ON                                               | Build the library.                                           |
| ${PARENT}_VTRACKER_TEST              | ON (stand alone), OFF (included in other project) | Build the test application.                                  |
| ${PARENT}_VTRACKER_EXAMPLE           | ON (stand alone), OFF (included in other project) | Build the example of the custom video tracker.               |
| ${PARENT}_SUBMODULE_CACHE_OVERWRITE  | ON                                               | Forced rewriting of the options above in the CMake cache. The top-level project should set it to OFF when it includes **VTracker** as a sub-repository. |
| CMAKE_BUILD_TYPE                     | Release (if not specified)                       | Build type.                                                  |



## Connect to your project

If you want connect **VTracker** library to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

You can add repositories **VTracker**, **Frame** and **ConfigReader** as sub-repositories by commands (use the URLs of the repositories provided to you):

```bash
cd <your repository folder>
git submodule add <Frame repository URL> 3rdparty/Frame
git submodule add <ConfigReader repository URL> 3rdparty/ConfigReader
git submodule add <VTracker repository URL> 3rdparty/VTracker
```

New structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    Frame
    ConfigReader
    VTracker
```

**VTracker** does not add its dependencies if it is included in other project: **Frame** and **ConfigReader** must be added by your project. Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_FRAME                           ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_FRAME)
    SET(${PARENT}_FRAME                                 ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_FRAME_TEST                            OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_CONFIG_READER                   ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_CONFIG_READER)
    SET(${PARENT}_CONFIG_READER                         ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_EXAMPLES                OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_TESTS                   OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_VTRACKER                        ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VTRACKER)
    SET(${PARENT}_VTRACKER                              ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_VTRACKER_TEST                         OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_VTRACKER_EXAMPLE                      OFF CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_FRAME)
    add_subdirectory(Frame)
endif()

if (${PARENT}_SUBMODULE_CONFIG_READER)
    add_subdirectory(ConfigReader)
endif()

if (${PARENT}_SUBMODULE_VTRACKER)
    add_subdirectory(VTracker)
endif()
```

File **3rdparty/CMakeLists.txt** adds folders **Frame**, **ConfigReader** and **VTracker** (in the order of their dependencies) to your project and excludes test applications and examples from compiling (by default test application and example excluded from compiling if **VTracker** included as sub-repository). Your repository new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    Frame
    ConfigReader
    VTracker
```

Next you need include folder 3rdparty in main **CMakeLists.txt** file of your repository. Add string at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next you have to include VTracker library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} VTracker)
```

Done!



# How to make custom implementation

The **VTracker** class provides only an interface, data structures, and methods for encoding and decoding commands and params. To create your own implementation of the video tracker, you must include the VTracker repository in your project (see [Build and connect to your project](#build-and-connect-to-your-project) section). The catalogue **example** (see [Library files](#library-files) section) includes an example of the design of the custom video tracker. You must implement all the methods of the VTracker interface class (including **decodeAndExecuteCommand(...)**). Custom video tracker class declaration:

```cpp
class CustomVTracker : public VTracker
{
public:

    /// Class constructor.
    CustomVTracker();

    /// Class destructor.
    ~CustomVTracker() override;

    /// Copy and move constructors and assignment operators are deleted.
    CustomVTracker(const CustomVTracker&) = delete;
    CustomVTracker(CustomVTracker&&) = delete;
    CustomVTracker& operator= (const CustomVTracker&) = delete;
    CustomVTracker& operator= (CustomVTracker&&) = delete;

    /// Get string of current class version.
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

    /// Decode and execute command.
    bool decodeAndExecuteCommand(uint8_t* data, int size) override;

private:

    /// Video tracker params. Protected by m_paramsMutex.
    VTrackerParams m_params;
    /// Mutex to protect m_params.
    std::mutex m_paramsMutex;
};
```

The example shows the recommended safe usage of the interface:

- values which come from outside (**initVTracker(...)** params, **setParam(...)** values, command arguments) are checked before use: the example rejects params outside of documented ranges and does not convert a float value to int if the value is NaN or outside of the range of int (such a conversion is undefined behavior);
- all methods which access the params are protected by a mutex, so they can be called from any thread (see the thread safety requirements in the description of the methods of the **VTracker** class);
- **decodeAndExecuteCommand(...)** calls [decodeCommand(...)](#decodecommand-method), returns FALSE if the decoding fails and calls **executeCommand(...)** or **setParam(...)** according to the decoded command type;
- an unknown parameter or command ID is rejected (**setParam(...)** and **executeCommand(...)** return FALSE, **getParam(...)** returns -1).

The example does not implement any tracking algorithm: **processFrame(...)** and **getImage(...)** do nothing and **executeCommand(...)** accepts the known commands without any action.



# Portability

The library has no SIMD code, no inline assembler and no platform specific code. The encoded data (params and commands) stores integer and float values in the byte order of the host: the library supports little endian hosts with 4 bytes **int** and **float** (size checked at compile time, IEEE 754 format of **float**), for example x86-64 and ARM (aarch64). Big endian hosts are not supported (the byte order is not converted). Data encoded on one supported platform is decoded identically on all other supported platforms (the same encoded data is produced by MSVC, GCC and Clang on x86-64 and by GCC and Clang on aarch64).



# Testing

The test application **VTrackerTest** (folder **test**) is built together with the library if the library is built stand alone (see [Build stand alone](#build-stand-alone)). Run it from the **bin** folder of the build folder:

```bash
./bin/VTrackerTest
```

The application prints the result of each test and returns 0 if all tests passed. The tests cover: copying of params, encoding and decoding of params (with and without the mask, with random masks, buffer sizes and the null pointer), decoding of invalid and damaged data (the params object must not change), encoding and decoding of commands (all IDs, wrong sizes, wrong version, unknown IDs), the version string and reading/writing of the JSON files (including invalid JSON documents). The tests use a deterministic generator and are reproducible. The test application does not leave files after the run.

To run the tests with the sanitizers configure the build with the options of the compiler, for example for GCC or Clang:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-sanitize-recover=undefined -fno-omit-frame-pointer" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" ..
make
./bin/VTrackerTest
```

For ThreadSanitizer use **-fsanitize=thread** instead.
