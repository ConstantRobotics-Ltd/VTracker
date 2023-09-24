#include <iostream>
#include "VTracker.h"



// Link namesapces.
using namespace cr::vtracker;
using namespace std;



// Copy test.
bool copyTest();

// Encode/decode test.
bool encodeDecodeTest();

/// Encode/decode test with params mask.
bool encodeDecodeWithMaskTest();

/// Encode/decode commands test.
bool encodeDecodeCommandsTest();

/// JSON read/write test.
bool jsonReadWriteTest();



// Entry point.
int main(void)
{
    cout << "#####################################" << endl;
    cout << "#                                   #" << endl;
    cout << "# VTracker test                     #" << endl;
    cout << "#                                   #" << endl;
    cout << "#####################################" << endl;
    cout << endl;

    cout << "Copy test:" << endl;
    if (copyTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode test:" << endl;
    if (encodeDecodeTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode test with params mask:" << endl;
    if (encodeDecodeWithMaskTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode commands test:" << endl;
    if (encodeDecodeCommandsTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "JSON read/write test:" << endl;
    if (jsonReadWriteTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    return 1;
}



// Copy test.
bool copyTest()
{
    // Prepare random params.
    VTrackerParams in;
    in.mode = rand() % 255;
    in.rectX = rand() % 255;
    in.rectY = rand() % 255;
    in.rectWidth = rand() % 255;
    in.rectHeight = rand() % 255;
    in.objectX = rand() % 255;
    in.objectY = rand() % 255;
    in.objectWidth = rand() % 255;
    in.objectHeight = rand() % 255;
    in.lostModeFrameCounter = rand() % 255;
    in.frameCounter = rand() % 255;
    in.frameWidth = rand() % 255;
    in.frameHeight = rand() % 255;
    in.searchWindowWidth = rand() % 255;
    in.searchWindowHeight = rand() % 255;
    in.searchWindowX = rand() % 255;
    in.searchWindowY = rand() % 255;
    in.lostModeOption = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.maxFramesInLostMode = rand() % 255;
    in.processedFrameId = rand() % 255;
    in.frameId = rand() % 255;
    in.velX = rand() % 255;
    in.velY = rand() % 255;
    in.detectionProbability = rand() % 255;
    in.rectAutoSize = rand() % 255;
    in.rectAutoPosition = rand() % 255;
    in.multipleThreads = rand() % 255;
    in.numChannels = rand() % 255;
    in.type = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Copy params.
    VTrackerParams out = in;

    // Compare params.
    if (in.mode != out.mode)
    {
        cout << "in.mode" << endl;
        return false;
    }
    if (in.rectX != out.rectX)
    {
        cout << "in.rectX" << endl;
        return false;
    }
    if (in.rectY != out.rectY)
    {
        cout << "in.rectY" << endl;
        return false;
    }
    if (in.rectWidth != out.rectWidth)
    {
        cout << "in.rectWidth" << endl;
        return false;
    }
    if (in.rectHeight != out.rectHeight)
    {
        cout << "in.rectHeight" << endl;
        return false;
    }
    if (in.objectX != out.objectX)
    {
        cout << "in.objectX" << endl;
        return false;
    }
    if (in.objectY != out.objectY)
    {
        cout << "in.objectY" << endl;
        return false;
    }
    if (in.objectWidth != out.objectWidth)
    {
        cout << "in.objectWidth" << endl;
        return false;
    }
    if (in.objectHeight != out.objectHeight)
    {
        cout << "in.objectHeight" << endl;
        return false;
    }
    if (in.lostModeFrameCounter != out.lostModeFrameCounter)
    {
        cout << "in.lostModeFrameCounter" << endl;
        return false;
    }
    if (in.frameCounter != out.frameCounter)
    {
        cout << "in.frameCounter" << endl;
        return false;
    }
    if (in.frameWidth != out.frameWidth)
    {
        cout << "in.frameWidth" << endl;
        return false;
    }
    if (in.frameHeight != out.frameHeight)
    {
        cout << "in.frameHeight" << endl;
        return false;
    }
    if (in.searchWindowWidth != out.searchWindowWidth)
    {
        cout << "in.searchWindowWidth" << endl;
        return false;
    }
    if (in.searchWindowHeight != out.searchWindowHeight)
    {
        cout << "in.searchWindowHeight" << endl;
        return false;
    }
    if (in.searchWindowX != out.searchWindowX)
    {
        cout << "in.searchWindowX" << endl;
        return false;
    }
    if (in.searchWindowY != out.searchWindowY)
    {
        cout << "in.searchWindowY" << endl;
        return false;
    }
    if (in.lostModeOption != out.lostModeOption)
    {
        cout << "in.lostModeOption" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.maxFramesInLostMode != out.maxFramesInLostMode)
    {
        cout << "in.maxFramesInLostMode" << endl;
        return false;
    }
    if (in.processedFrameId != out.processedFrameId)
    {
        cout << "in.processedFrameId" << endl;
        return false;
    }
    if (in.frameId != out.frameId)
    {
        cout << "in.frameId" << endl;
        return false;
    }
    if (in.velX != out.velX)
    {
        cout << "in.velX" << endl;
        return false;
    }
    if (in.velY != out.velY)
    {
        cout << "in.velY" << endl;
        return false;
    }
    if (in.detectionProbability != out.detectionProbability)
    {
        cout << "in.detectionProbability" << endl;
        return false;
    }
    if (in.rectAutoSize != out.rectAutoSize)
    {
        cout << "in.rectAutoSize" << endl;
        return false;
    }
    if (in.rectAutoPosition != out.rectAutoPosition)
    {
        cout << "in.rectAutoPosition" << endl;
        return false;
    }
    if (in.multipleThreads != out.multipleThreads)
    {
        cout << "in.multipleThreads" << endl;
        return false;
    }
    if (in.numChannels != out.numChannels)
    {
        cout << "in.numChannels" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
}



// Encode/decode test.
bool encodeDecodeTest()
{
    // Prepare random params.
    VTrackerParams in;
    in.mode = rand() % 255;
    in.rectX = rand() % 255;
    in.rectY = rand() % 255;
    in.rectWidth = rand() % 255;
    in.rectHeight = rand() % 255;
    in.objectX = rand() % 255;
    in.objectY = rand() % 255;
    in.objectWidth = rand() % 255;
    in.objectHeight = rand() % 255;
    in.lostModeFrameCounter = rand() % 255;
    in.frameCounter = rand() % 255;
    in.frameWidth = rand() % 255;
    in.frameHeight = rand() % 255;
    in.searchWindowWidth = rand() % 255;
    in.searchWindowHeight = rand() % 255;
    in.searchWindowX = rand() % 255;
    in.searchWindowY = rand() % 255;
    in.lostModeOption = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.maxFramesInLostMode = rand() % 255;
    in.processedFrameId = rand() % 255;
    in.frameId = rand() % 255;
    in.velX = rand() % 255;
    in.velY = rand() % 255;
    in.detectionProbability = rand() % 255;
    in.rectAutoSize = rand() % 255;
    in.rectAutoPosition = rand() % 255;
    in.multipleThreads = rand() % 255;
    in.numChannels = rand() % 255;
    in.type = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, 1024, size);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    VTrackerParams out;
    if (!out.decode(data, size))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    if (in.mode != out.mode)
    {
        cout << "in.mode" << endl;
        return false;
    }
    if (in.rectX != out.rectX)
    {
        cout << "in.rectX" << endl;
        return false;
    }
    if (in.rectY != out.rectY)
    {
        cout << "in.rectY" << endl;
        return false;
    }
    if (in.rectWidth != out.rectWidth)
    {
        cout << "in.rectWidth" << endl;
        return false;
    }
    if (in.rectHeight != out.rectHeight)
    {
        cout << "in.rectHeight" << endl;
        return false;
    }
    if (in.objectX != out.objectX)
    {
        cout << "in.objectX" << endl;
        return false;
    }
    if (in.objectY != out.objectY)
    {
        cout << "in.objectY" << endl;
        return false;
    }
    if (in.objectWidth != out.objectWidth)
    {
        cout << "in.objectWidth" << endl;
        return false;
    }
    if (in.objectHeight != out.objectHeight)
    {
        cout << "in.objectHeight" << endl;
        return false;
    }
    if (in.lostModeFrameCounter != out.lostModeFrameCounter)
    {
        cout << "in.lostModeFrameCounter" << endl;
        return false;
    }
    if (in.frameCounter != out.frameCounter)
    {
        cout << "in.frameCounter" << endl;
        return false;
    }
    if (in.frameWidth != out.frameWidth)
    {
        cout << "in.frameWidth" << endl;
        return false;
    }
    if (in.frameHeight != out.frameHeight)
    {
        cout << "in.frameHeight" << endl;
        return false;
    }
    if (in.searchWindowWidth != out.searchWindowWidth)
    {
        cout << "in.searchWindowWidth" << endl;
        return false;
    }
    if (in.searchWindowHeight != out.searchWindowHeight)
    {
        cout << "in.searchWindowHeight" << endl;
        return false;
    }
    if (in.searchWindowX != out.searchWindowX)
    {
        cout << "in.searchWindowX" << endl;
        return false;
    }
    if (in.searchWindowY != out.searchWindowY)
    {
        cout << "in.searchWindowY" << endl;
        return false;
    }
    if (in.lostModeOption != out.lostModeOption)
    {
        cout << "in.lostModeOption" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.maxFramesInLostMode != out.maxFramesInLostMode)
    {
        cout << "in.maxFramesInLostMode" << endl;
        return false;
    }
    if (in.processedFrameId != out.processedFrameId)
    {
        cout << "in.processedFrameId" << endl;
        return false;
    }
    if (in.frameId != out.frameId)
    {
        cout << "in.frameId" << endl;
        return false;
    }
    if (in.velX != out.velX)
    {
        cout << "in.velX" << endl;
        return false;
    }
    if (in.velY != out.velY)
    {
        cout << "in.velY" << endl;
        return false;
    }
    if (in.detectionProbability != out.detectionProbability)
    {
        cout << "in.detectionProbability" << endl;
        return false;
    }
    if (in.rectAutoSize != out.rectAutoSize)
    {
        cout << "in.rectAutoSize" << endl;
        return false;
    }
    if (in.rectAutoPosition != out.rectAutoPosition)
    {
        cout << "in.rectAutoPosition" << endl;
        return false;
    }
    if (in.multipleThreads != out.multipleThreads)
    {
        cout << "in.multipleThreads" << endl;
        return false;
    }
    if (in.numChannels != out.numChannels)
    {
        cout << "in.numChannels" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
}



// Encode/decode commands test.
bool encodeDecodeCommandsTest()
{
    // Encode command.
    uint8_t data[1024];
    int size = 0;
    float outValue = (float)(rand() % 20);
    float arg1 = (float)(rand() % 20);
    float arg2 = (float)(rand() % 20);
    float arg3 = (float)(rand() % 20);
    VTracker::encodeCommand(data, size, VTrackerCommand::CAPTURE, arg1, arg2, arg3);

    // Decode command.
    VTrackerCommand commandId;
    VTrackerParam paramId;
    float inArg1 = (float)(rand() % 20);
    float inArg2 = (float)(rand() % 20);
    float inArg3 = (float)(rand() % 20);
    if (VTracker::decodeCommand(data, size, paramId, commandId, inArg1, inArg2, inArg3) != 0)
    {
        cout << "Command not decoded" << endl;
        return false;
    }

    // Checkk ID and args.
    if (commandId != VTrackerCommand::CAPTURE)
    {
        cout << "not a VTrackerCommand::CAPTURE" << endl;
        return false;
    }
    if (inArg1 != arg1)
    {
        cout << "inArg1" << endl;
        return false;
    }
    if (inArg2 != arg2)
    {
        cout << "inArg2" << endl;
        return false;
    }
    if (inArg3 != arg3)
    {
        cout << "inArg3" << endl;
        return false;
    }

    // Encode param.
    outValue = (float)(rand() % 20);
    VTracker::encodeSetParamCommand(
    data, size, VTrackerParam::MULTIPLE_THREADS, outValue);

    // Decode command.
    inArg1 = (float)(rand() % 20);
    inArg2 = (float)(rand() % 20);
    inArg3 = (float)(rand() % 20);
    if (VTracker::decodeCommand(data, size, paramId, commandId, inArg1, inArg2, inArg3) != 1)
    {
        cout << "Set param command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (paramId != VTrackerParam::MULTIPLE_THREADS)
    {
        cout << "not a VTrackerParam::MULTIPLE_THREADS" << endl;
        return false;
    }
    if (inArg1 != outValue)
    {
        cout << "not equal param value" << endl;
        return false;
    }

    return true;
}



/// JSON read/write test.
bool jsonReadWriteTest()
{
    // Prepare random params.
    VTrackerParams in;
    in.mode = rand() % 255;
    in.rectX = rand() % 255;
    in.rectY = rand() % 255;
    in.rectWidth = rand() % 255;
    in.rectHeight = rand() % 255;
    in.objectX = rand() % 255;
    in.objectY = rand() % 255;
    in.objectWidth = rand() % 255;
    in.objectHeight = rand() % 255;
    in.lostModeFrameCounter = rand() % 255;
    in.frameCounter = rand() % 255;
    in.frameWidth = rand() % 255;
    in.frameHeight = rand() % 255;
    in.searchWindowWidth = rand() % 255;
    in.searchWindowHeight = rand() % 255;
    in.searchWindowX = rand() % 255;
    in.searchWindowY = rand() % 255;
    in.lostModeOption = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.maxFramesInLostMode = rand() % 255;
    in.processedFrameId = rand() % 255;
    in.frameId = rand() % 255;
    in.velX = rand() % 255;
    in.velY = rand() % 255;
    in.detectionProbability = rand() % 255;
    in.rectAutoSize = rand() % 255;
    in.rectAutoPosition = rand() % 255;
    in.multipleThreads = rand() % 255;
    in.numChannels = rand() % 255;
    in.type = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Write params to file.
    cr::utils::ConfigReader inConfig;
    inConfig.set(in, "VTrackerParams");
    inConfig.writeToFile("VTrackerParams.json");

    // Read params from file.
    cr::utils::ConfigReader outConfig;
    if(!outConfig.readFromFile("VTrackerParams.json"))
    {
        cout << "Can't open config file" << endl;
        return false;
    }

    VTrackerParams out;
    if(!outConfig.get(out, "VTrackerParams"))
    {
        cout << "Can't read params from file" << endl;
        return false;
    }

    // Compare params.
    if (in.rectWidth != out.rectWidth)
    {
        cout << "in.rectWidth" << endl;
        return false;
    }
    if (in.rectHeight != out.rectHeight)
    {
        cout << "in.rectHeight" << endl;
        return false;
    }
    if (in.searchWindowWidth != out.searchWindowWidth)
    {
        cout << "in.searchWindowWidth" << endl;
        return false;
    }
    if (in.searchWindowHeight != out.searchWindowHeight)
    {
        cout << "in.searchWindowHeight" << endl;
        return false;
    }
    if (in.lostModeOption != out.lostModeOption)
    {
        cout << "in.lostModeOption" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.maxFramesInLostMode != out.maxFramesInLostMode)
    {
        cout << "in.maxFramesInLostMode" << endl;
        return false;
    }
    if (in.rectAutoSize != out.rectAutoSize)
    {
        cout << "in.rectAutoSize" << endl;
        return false;
    }
    if (in.rectAutoPosition != out.rectAutoPosition)
    {
        cout << "in.rectAutoPosition" << endl;
        return false;
    }
    if (in.multipleThreads != out.multipleThreads)
    {
        cout << "in.multipleThreads" << endl;
        return false;
    }
    if (in.numChannels != out.numChannels)
    {
        cout << "in.numChannels" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
}



/// Encode/decode test with params mask.
bool encodeDecodeWithMaskTest()
{
    // Prepare random params.
    VTrackerParams in;
    in.mode = rand() % 255;
    in.rectX = rand() % 255;
    in.rectY = rand() % 255;
    in.rectWidth = rand() % 255;
    in.rectHeight = rand() % 255;
    in.objectX = rand() % 255;
    in.objectY = rand() % 255;
    in.objectWidth = rand() % 255;
    in.objectHeight = rand() % 255;
    in.lostModeFrameCounter = rand() % 255;
    in.frameCounter = rand() % 255;
    in.frameWidth = rand() % 255;
    in.frameHeight = rand() % 255;
    in.searchWindowWidth = rand() % 255;
    in.searchWindowHeight = rand() % 255;
    in.searchWindowX = rand() % 255;
    in.searchWindowY = rand() % 255;
    in.lostModeOption = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.maxFramesInLostMode = rand() % 255;
    in.processedFrameId = rand() % 255;
    in.frameId = rand() % 255;
    in.velX = rand() % 255;
    in.velY = rand() % 255;
    in.detectionProbability = rand() % 255;
    in.rectAutoSize = rand() % 255;
    in.rectAutoPosition = rand() % 255;
    in.multipleThreads = rand() % 255;
    in.numChannels = rand() % 255;
    in.type = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Prepare mask.
    VTrackerParamsMask mask;
    mask.mode = true;
    mask.rectX = false;
    mask.rectY = true;
    mask.rectWidth = false;
    mask.rectHeight = true;
    mask.objectX = false;
    mask.objectY = true;
    mask.objectWidth = false;
    mask.objectHeight = true;
    mask.lostModeFrameCounter = false;
    mask.frameCounter = true;
    mask.frameWidth = false;
    mask.frameHeight = true;
    mask.searchWindowWidth = false;
    mask.searchWindowHeight = true;
    mask.searchWindowX = false;
    mask.searchWindowY = true;
    mask.lostModeOption = false;
    mask.frameBufferSize = true;
    mask.maxFramesInLostMode = false;
    mask.processedFrameId = true;
    mask.frameId = false;
    mask.velX = true;
    mask.velY = false;
    mask.detectionProbability = true;
    mask.rectAutoSize = false;
    mask.rectAutoPosition = true;
    mask.multipleThreads = false;
    mask.numChannels = true;
    mask.type = false;
    mask.processingTimeMks = true;
    mask.custom1 = false;
    mask.custom2 = true;
    mask.custom3 = false;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, 1024, size, &mask);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    VTrackerParams out;
    if (!out.decode(data, size))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    if (in.mode != out.mode)
    {
        cout << "in.mode" << endl;
        return false;
    }
    if (0 != out.rectX)
    {
        cout << "in.rectX" << endl;
        return false;
    }
    if (in.rectY != out.rectY)
    {
        cout << "in.rectY" << endl;
        return false;
    }
    if (0 != out.rectWidth)
    {
        cout << "in.rectWidth" << endl;
        return false;
    }
    if (in.rectHeight != out.rectHeight)
    {
        cout << "in.rectHeight" << endl;
        return false;
    }
    if (0 != out.objectX)
    {
        cout << "in.objectX" << endl;
        return false;
    }
    if (in.objectY != out.objectY)
    {
        cout << "in.objectY" << endl;
        return false;
    }
    if (0 != out.objectWidth)
    {
        cout << "in.objectWidth" << endl;
        return false;
    }
    if (in.objectHeight != out.objectHeight)
    {
        cout << "in.objectHeight" << endl;
        return false;
    }
    if (0 != out.lostModeFrameCounter)
    {
        cout << "in.lostModeFrameCounter" << endl;
        return false;
    }
    if (in.frameCounter != out.frameCounter)
    {
        cout << "in.frameCounter" << endl;
        return false;
    }
    if (0 != out.frameWidth)
    {
        cout << "in.frameWidth" << endl;
        return false;
    }
    if (in.frameHeight != out.frameHeight)
    {
        cout << "in.frameHeight" << endl;
        return false;
    }
    if (0 != out.searchWindowWidth)
    {
        cout << "in.searchWindowWidth" << endl;
        return false;
    }
    if (in.searchWindowHeight != out.searchWindowHeight)
    {
        cout << "in.searchWindowHeight" << endl;
        return false;
    }
    if (0!= out.searchWindowX)
    {
        cout << "in.searchWindowX" << endl;
        return false;
    }
    if (in.searchWindowY != out.searchWindowY)
    {
        cout << "in.searchWindowY" << endl;
        return false;
    }
    if (0 != out.lostModeOption)
    {
        cout << "in.lostModeOption" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (0 != out.maxFramesInLostMode)
    {
        cout << "in.maxFramesInLostMode" << endl;
        return false;
    }
    if (in.processedFrameId != out.processedFrameId)
    {
        cout << "in.processedFrameId" << endl;
        return false;
    }
    if (0 != out.frameId)
    {
        cout << "in.frameId" << endl;
        return false;
    }
    if (in.velX != out.velX)
    {
        cout << "in.velX" << endl;
        return false;
    }
    if (0 != out.velY)
    {
        cout << "in.velY" << endl;
        return false;
    }
    if (in.detectionProbability != out.detectionProbability)
    {
        cout << "in.detectionProbability" << endl;
        return false;
    }
    if (false != out.rectAutoSize)
    {
        cout << "in.rectAutoSize" << endl;
        return false;
    }
    if (in.rectAutoPosition != out.rectAutoPosition)
    {
        cout << "in.rectAutoPosition" << endl;
        return false;
    }
    if (false != out.multipleThreads)
    {
        cout << "in.multipleThreads" << endl;
        return false;
    }
    if (in.numChannels != out.numChannels)
    {
        cout << "in.numChannels" << endl;
        return false;
    }
    if (0 != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (0 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (0 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
}


