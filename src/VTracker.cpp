#include "VTracker.h"
#include "VTrackerVersion.h"



std::string cr::vtracker::VTracker::getVersion()
{
    return VTRACKER_VERSION;
}



cr::vtracker::VTrackerParams &cr::vtracker::VTrackerParams::operator= (const cr::vtracker::VTrackerParams &src)
{
    // Check yourself.
    if (this == &src)
        return *this;

    mode = src.mode;
    rectX = src.rectX;
    rectY = src.rectY;
    rectWidth = src.rectWidth;
    rectHeight = src.rectHeight;
    objectX = src.objectX;
    objectY = src.objectY;
    objectWidth = src.objectWidth;

    objectHeight = src.objectHeight;
    lostModeFrameCounter = src.lostModeFrameCounter;
    frameCounter = src.frameCounter;
    frameWidth = src.frameWidth;
    frameHeight = src.frameHeight;
    searchWindowWidth = src.searchWindowWidth;
    searchWindowHeight = src.searchWindowHeight;
    searchWindowX = src.searchWindowX;

    searchWindowY = src.searchWindowY;
    lostModeOption = src.lostModeOption;
    frameBufferSize = src.frameBufferSize;
    maxFramesInLostMode = src.maxFramesInLostMode;
    processedFrameId = src.processedFrameId;
    frameId = src.frameId;
    velX = src.velX;
    velY = src.velY;

    detectionProbability = src.detectionProbability;
    rectAutoSize = src.rectAutoSize;
    rectAutoPosition = src.rectAutoPosition;
    multipleThreads = src.multipleThreads;
    numChannels = src.numChannels;
    type = src.type;
    processingTimeMks = src.processingTimeMks;
    custom1 = src.custom1;

    custom2 = src.custom2;
    custom3 = src.custom3;

    return *this;
}



void cr::vtracker::VTrackerParams::encode(
        uint8_t* data, int& size, cr::vtracker::VTrackerParamsMask* mask)
{
    // Encode version.
    int pos = 0;
    data[pos] = 0x02; pos += 1;
    data[pos] = VTRACKER_MAJOR_VERSION; pos += 1;
    data[pos] = VTRACKER_MINOR_VERSION; pos += 1;

    if (mask == nullptr)
    {
        // Prepare mask.
        data[pos] = 0xFF; pos += 1;
        data[pos] = 0xFF; pos += 1;
        data[pos] = 0xFF; pos += 1;
        data[pos] = 0xFF; pos += 1;
        data[pos] = 0xFF; pos += 1;

        // Encode data.
        memcpy(&data[pos], &mode, 4); pos += 4;
        memcpy(&data[pos], &rectX, 4); pos += 4;
        memcpy(&data[pos], &rectY, 4); pos += 4;
        memcpy(&data[pos], &rectWidth, 4); pos += 4;
        memcpy(&data[pos], &rectHeight, 4); pos += 4;
        memcpy(&data[pos], &objectX, 4); pos += 4;
        memcpy(&data[pos], &objectY, 4); pos += 4;
        memcpy(&data[pos], &objectWidth, 4); pos += 4;

        memcpy(&data[pos], &objectHeight, 4); pos += 4;
        memcpy(&data[pos], &lostModeFrameCounter, 4); pos += 4;
        memcpy(&data[pos], &frameCounter, 4); pos += 4;
        memcpy(&data[pos], &frameWidth, 4); pos += 4;
        memcpy(&data[pos], &frameHeight, 4); pos += 4;
        memcpy(&data[pos], &searchWindowWidth, 4); pos += 4;
        memcpy(&data[pos], &searchWindowHeight, 4); pos += 4;
        memcpy(&data[pos], &searchWindowX, 4); pos += 4;

        memcpy(&data[pos], &searchWindowY, 4); pos += 4;
        memcpy(&data[pos], &lostModeOption, 4); pos += 4;
        memcpy(&data[pos], &frameBufferSize, 4); pos += 4;
        memcpy(&data[pos], &maxFramesInLostMode, 4); pos += 4;
        memcpy(&data[pos], &processedFrameId, 4); pos += 4;
        memcpy(&data[pos], &frameId, 4); pos += 4;
        memcpy(&data[pos], &velX, 4); pos += 4;
        memcpy(&data[pos], &velY, 4); pos += 4;

        memcpy(&data[pos], &detectionProbability, 4); pos += 4;
        data[pos] = rectAutoSize == true ? 0x01 : 0x00; pos += 1;
        data[pos] = rectAutoPosition == true ? 0x01 : 0x00; pos += 1;
        data[pos] = multipleThreads == true ? 0x01 : 0x00; pos += 1;
        memcpy(&data[pos], &numChannels, 4); pos += 4;
        memcpy(&data[pos], &type, 4); pos += 4;
        memcpy(&data[pos], &processingTimeMks, 4); pos += 4;
        memcpy(&data[pos], &custom1, 4); pos += 4;

        memcpy(&data[pos], &custom2, 4); pos += 4;
        memcpy(&data[pos], &custom3, 4); pos += 4;   

        size = pos;

        return;
    }

    // Prepare mask.
    data[pos] = 0;
    data[pos] = data[pos] | (mask->mode ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectX ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectY ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectWidth ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectHeight ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->objectX ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->objectY ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->objectWidth ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->objectHeight ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->lostModeFrameCounter ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->frameCounter ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->frameWidth ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->frameHeight ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->searchWindowWidth ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->searchWindowHeight ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->searchWindowX ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->searchWindowY ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->lostModeOption ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->frameBufferSize ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->maxFramesInLostMode ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->processedFrameId ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->frameId ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->velX ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->velY ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->detectionProbability ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectAutoSize ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (mask->rectAutoPosition ? (uint8_t)32 : (uint8_t)0);
    data[pos] = data[pos] | (mask->multipleThreads ? (uint8_t)16 : (uint8_t)0);
    data[pos] = data[pos] | (mask->numChannels ? (uint8_t)8 : (uint8_t)0);
    data[pos] = data[pos] | (mask->type ? (uint8_t)4 : (uint8_t)0);
    data[pos] = data[pos] | (mask->processingTimeMks ? (uint8_t)2 : (uint8_t)0);
    data[pos] = data[pos] | (mask->custom1 ? (uint8_t)1 : (uint8_t)0);
    pos += 1;
    data[pos] = 0;
    data[pos] = data[pos] | (mask->custom2 ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (mask->custom3 ? (uint8_t)64 : (uint8_t)0);
    pos += 1;

    if (mask->mode)
    {
        memcpy(&data[pos], &mode, 4); pos += 4;
    }
    if (mask->rectX)
    {
        memcpy(&data[pos], &rectX, 4); pos += 4;
    }
    if (mask->rectY)
    {
        memcpy(&data[pos], &rectY, 4); pos += 4;
    }
    if (mask->rectWidth)
    {
        memcpy(&data[pos], &rectWidth, 4); pos += 4;
    }
    if (mask->rectHeight)
    {
        memcpy(&data[pos], &rectHeight, 4); pos += 4;
    }
    if (mask->objectX)
    {
        memcpy(&data[pos], &objectX, 4); pos += 4;
    }
    if (mask->objectY)
    {
        memcpy(&data[pos], &objectY, 4); pos += 4;
    }
    if (mask->objectWidth)
    {
        memcpy(&data[pos], &objectWidth, 4); pos += 4;
    }


    if (mask->objectHeight)
    {
        memcpy(&data[pos], &objectHeight, 4); pos += 4;
    }
    if (mask->lostModeFrameCounter)
    {
        memcpy(&data[pos], &lostModeFrameCounter, 4); pos += 4;
    }
    if (mask->frameCounter)
    {
        memcpy(&data[pos], &frameCounter, 4); pos += 4;
    }
    if (mask->frameWidth)
    {
        memcpy(&data[pos], &frameWidth, 4); pos += 4;
    }
    if (mask->frameHeight)
    {
        memcpy(&data[pos], &frameHeight, 4); pos += 4;
    }
    if (mask->searchWindowWidth)
    {
        memcpy(&data[pos], &searchWindowWidth, 4); pos += 4;
    }
    if (mask->searchWindowHeight)
    {
        memcpy(&data[pos], &searchWindowHeight, 4); pos += 4;
    }
    if (mask->searchWindowX)
    {
        memcpy(&data[pos], &searchWindowX, 4); pos += 4;
    }


    if (mask->searchWindowY)
    {
        memcpy(&data[pos], &searchWindowY, 4); pos += 4;
    }
    if (mask->lostModeOption)
    {
        memcpy(&data[pos], &lostModeOption, 4); pos += 4;
    }
    if (mask->frameBufferSize)
    {
        memcpy(&data[pos], &frameBufferSize, 4); pos += 4;
    }
    if (mask->maxFramesInLostMode)
    {
        memcpy(&data[pos], &maxFramesInLostMode, 4); pos += 4;
    }
    if (mask->processedFrameId)
    {
        memcpy(&data[pos], &processedFrameId, 4); pos += 4;
    }
    if (mask->frameId)
    {
        memcpy(&data[pos], &frameId, 4); pos += 4;
    }
    if (mask->velX)
    {
        memcpy(&data[pos], &velX, 4); pos += 4;
    }
    if (mask->velY)
    {
        memcpy(&data[pos], &velY, 4); pos += 4;
    }



    if (mask->detectionProbability)
    {
        memcpy(&data[pos], &detectionProbability, 4); pos += 4;
    }
    if (mask->rectAutoSize)
    {
        data[pos] = rectAutoSize == true ? 0x01 : 0x00; pos += 1;
    }
    if (mask->rectAutoPosition)
    {
        data[pos] = rectAutoPosition == true ? 0x01 : 0x00; pos += 1;
    }
    if (mask->multipleThreads)
    {
        data[pos] = multipleThreads == true ? 0x01 : 0x00; pos += 1;
    }
    if (mask->numChannels)
    {
        memcpy(&data[pos], &numChannels, 4); pos += 4;
    }
    if (mask->type)
    {
        memcpy(&data[pos], &type, 4); pos += 4;
    }
    if (mask->processingTimeMks)
    {
        memcpy(&data[pos], &processingTimeMks, 4); pos += 4;
    }
    if (mask->custom1)
    {
        memcpy(&data[pos], &custom1, 4); pos += 4;
    }


    if (mask->custom2)
    {
        memcpy(&data[pos], &custom2, 4); pos += 4;
    }
    if (mask->custom3)
    {
        memcpy(&data[pos], &custom3, 4); pos += 4;
    }

    size = pos;
}



bool cr::vtracker::VTrackerParams::decode(uint8_t* data)
{
    // Check header.
    if (data[0] != 0x02)
        return false;

    // Check version version.
    if (data[1] != VTRACKER_MAJOR_VERSION || data[2] != VTRACKER_MINOR_VERSION)
        return false;




    // Decode data.
    int pos = 8;
    if ((data[3] & (uint8_t)128) == (uint8_t)128)
    {
        memcpy(&mode, &data[pos], 4); pos += 4;
    }
    else
    {
        mode = 0;
    }
    if ((data[3] & (uint8_t)64) == (uint8_t)64)
    {
        memcpy(&rectX, &data[pos], 4); pos += 4;
    }
    else
    {
        rectX = 0;
    }
    if ((data[3] & (uint8_t)32) == (uint8_t)32)
    {
        memcpy(&rectY, &data[pos], 4); pos += 4;
    }
    else
    {
        rectY = 0;
    }
    if ((data[3] & (uint8_t)16) == (uint8_t)16)
    {
        memcpy(&rectWidth, &data[pos], 4); pos += 4;
    }
    else
    {
        rectWidth = 0;
    }
    if ((data[3] & (uint8_t)8) == (uint8_t)8)
    {
        memcpy(&rectHeight, &data[pos], 4); pos += 4;
    }
    else
    {
        rectHeight = 0;
    }
    if ((data[3] & (uint8_t)4) == (uint8_t)4)
    {
        memcpy(&objectX, &data[pos], 4); pos += 4;
    }
    else
    {
        objectX = 0;
    }
    if ((data[3] & (uint8_t)2) == (uint8_t)2)
    {
        memcpy(&objectY, &data[pos], 4); pos += 4;
    }
    else
    {
        objectY = 0;
    }
    if ((data[3] & (uint8_t)1) == (uint8_t)1)
    {
        memcpy(&objectWidth, &data[pos], 4); pos += 4;
    }
    else
    {
        objectWidth = 0;
    }



    if ((data[4] & (uint8_t)128) == (uint8_t)128)
    {
        memcpy(&objectHeight, &data[pos], 4); pos += 4;
    }
    else
    {
        objectHeight = 0;
    }
    if ((data[4] & (uint8_t)64) == (uint8_t)64)
    {
        memcpy(&lostModeFrameCounter, &data[pos], 4); pos += 4;
    }
    else
    {
        lostModeFrameCounter = 0;
    }
    if ((data[4] & (uint8_t)32) == (uint8_t)32)
    {
        memcpy(&frameCounter, &data[pos], 4); pos += 4;
    }
    else
    {
        frameCounter = 0;
    }
    if ((data[4] & (uint8_t)16) == (uint8_t)16)
    {
        memcpy(&frameWidth, &data[pos], 4); pos += 4;
    }
    else
    {
        frameWidth = 0;
    }
    if ((data[4] & (uint8_t)8) == (uint8_t)8)
    {
        memcpy(&frameHeight, &data[pos], 4); pos += 4;
    }
    else
    {
        frameHeight = 0;
    }
    if ((data[4] & (uint8_t)4) == (uint8_t)4)
    {
        memcpy(&searchWindowWidth, &data[pos], 4); pos += 4;
    }
    else
    {
        searchWindowWidth = 0;
    }
    if ((data[4] & (uint8_t)2) == (uint8_t)2)
    {
        memcpy(&searchWindowHeight, &data[pos], 4); pos += 4;
    }
    else
    {
        searchWindowHeight = 0;
    }
    if ((data[4] & (uint8_t)1) == (uint8_t)1)
    {
        memcpy(&searchWindowX, &data[pos], 4); pos += 4;
    }
    else
    {
        searchWindowX = 0;
    }



    if ((data[5] & (uint8_t)128) == (uint8_t)128)
    {
        memcpy(&searchWindowY, &data[pos], 4); pos += 4;
    }
    else
    {
        searchWindowY = 0;
    }
    if ((data[5] & (uint8_t)64) == (uint8_t)64)
    {
        memcpy(&lostModeOption, &data[pos], 4); pos += 4;
    }
    else
    {
        lostModeOption = 0;
    }
    if ((data[5] & (uint8_t)32) == (uint8_t)32)
    {
        memcpy(&frameBufferSize, &data[pos], 4); pos += 4;
    }
    else
    {
        frameBufferSize = 0;
    }
    if ((data[5] & (uint8_t)16) == (uint8_t)16)
    {
        memcpy(&maxFramesInLostMode, &data[pos], 4); pos += 4;
    }
    else
    {
        maxFramesInLostMode = 0;
    }
    if ((data[5] & (uint8_t)8) == (uint8_t)8)
    {
        memcpy(&processedFrameId, &data[pos], 4); pos += 4;
    }
    else
    {
        processedFrameId = 0;
    }
    if ((data[5] & (uint8_t)4) == (uint8_t)4)
    {
        memcpy(&frameId, &data[pos], 4); pos += 4;
    }
    else
    {
        frameId = 0;
    }
    if ((data[5] & (uint8_t)2) == (uint8_t)2)
    {
        memcpy(&velX, &data[pos], 4); pos += 4;
    }
    else
    {
        velX = 0.0f;
    }
    if ((data[5] & (uint8_t)1) == (uint8_t)1)
    {
        memcpy(&velY, &data[pos], 4); pos += 4;
    }
    else
    {
        velY = 0.0f;
    }



    if ((data[6] & (uint8_t)128) == (uint8_t)128)
    {
        memcpy(&detectionProbability, &data[pos], 4); pos += 4;
    }
    else
    {
        detectionProbability = 0.0f;
    }
    if ((data[6] & (uint8_t)64) == (uint8_t)64)
    {
        rectAutoSize = data[pos] == 0x00 ? false : true; pos += 1;
    }
    else
    {
        rectAutoSize = false;
    }
    if ((data[6] & (uint8_t)32) == (uint8_t)32)
    {
        rectAutoPosition = data[pos] == 0x00 ? false : true; pos += 1;
    }
    else
    {
        rectAutoPosition = false;
    }
    if ((data[6] & (uint8_t)16) == (uint8_t)16)
    {
       multipleThreads = data[pos] == 0x00 ? false : true; pos += 1;
    }
    else
    {
        multipleThreads = false;
    }
    if ((data[6] & (uint8_t)8) == (uint8_t)8)
    {
        memcpy(&numChannels, &data[pos], 4); pos += 4;
    }
    else
    {
        numChannels = 0;
    }
    if ((data[6] & (uint8_t)4) == (uint8_t)4)
    {
        memcpy(&type, &data[pos], 4); pos += 4;
    }
    else
    {
        type = 0;
    }
    if ((data[6] & (uint8_t)2) == (uint8_t)2)
    {
        memcpy(&processingTimeMks, &data[pos], 4); pos += 4;
    }
    else
    {
        processingTimeMks = 0;
    }
    if ((data[6] & (uint8_t)1) == (uint8_t)1)
    {
        memcpy(&custom1, &data[pos], 4); pos += 4;
    }
    else
    {
        custom1 = 0.0f;
    }

    if ((data[7] & (uint8_t)128) == (uint8_t)128)
    {
        memcpy(&custom2, &data[pos], 4); pos += 4;
    }
    else
    {
        custom2 = 0.0f;
    }
    if ((data[7] & (uint8_t)64) == (uint8_t)64)
    {
        memcpy(&custom3, &data[pos], 4);
    }
    else
    {
        custom3 = 0.0f;
    }
    
    return true;
}



void cr::vtracker::VTracker::encodeSetParamCommand(
        uint8_t* data, int& size, cr::vtracker::VTrackerParam id, float value)
{
    // Fill header.
    data[0] = 0x01;
    data[1] = VTRACKER_MAJOR_VERSION;
    data[2] = VTRACKER_MINOR_VERSION;

    // Fill data.
    int paramId = (int)id;
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], &value, 4);
    size = 11;
}



void cr::vtracker::VTracker::encodeCommand(
        uint8_t* data, int& size, VTrackerCommand id,
        float arg1, float arg2, float arg3)
{
    // Fill header.
    data[0] = 0x00;
    data[1] = VTRACKER_MAJOR_VERSION;
    data[2] = VTRACKER_MINOR_VERSION;

    // Fill data.
    int commandId = (int)id;
    memcpy(&data[3], &commandId, 4);
    memcpy(&data[7], &arg1, 4);
    memcpy(&data[11], &arg2, 4);
    memcpy(&data[15], &arg3, 4);
    size = 19;
}



int cr::vtracker::VTracker::decodeCommand(
                            uint8_t* data,
                            int size,
                            VTrackerParam& paramId,
                            VTrackerCommand& commandId,
                            float& value1,
                            float& value2,
                            float& value3)
{
    // Check size.
    if (size < 11)
        return -1;

    // Check version.
    if (data[1] != VTRACKER_MAJOR_VERSION ||
        data[2] != VTRACKER_MINOR_VERSION)
        return -1;

    // Extract data.
    int id = 0;
    memcpy(&id, &data[3], 4);
    value1 = 0.0f;
    value2 = 0.0f;
    value3 = 0.0f;

    // Check command type.
    if (data[0] == 0x00)
    {
        // Check size.
        if (size != 19)
            return false;

        // Decode command ID and arguments.
        commandId = (VTrackerCommand)id;
        memcpy(&value1, &data[7], 4);
        memcpy(&value2, &data[11], 4);
        memcpy(&value3, &data[15], 4);
        return 0;
    }
    else if (data[0] == 0x01)
    {
        // Check size.
        if (size != 11)
            return false;

        paramId = (VTrackerParam)id;
        memcpy(&value1, &data[7], 4);
        return 1;
    }

    return -1;
}


