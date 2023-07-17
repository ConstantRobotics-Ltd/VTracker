#include <iostream>
#include "ObjectDetector.h"



/// Link namesapces.
using namespace cr::detector;
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
    cout << "# ObjectDetector test               #" << endl;
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
    ObjectDetectorParams in;
    in.logMode = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.minObjectWidth = rand() % 255;
    in.maxObjectWidth = rand() % 255;
    in.minObjectHeight = rand() % 255;
    in.maxObjectHeight = rand() % 255;
    in.minXSpeed = rand() % 255;
    in.maxXSpeed = rand() % 255;
    in.minYSpeed = rand() % 255;
    in.maxYSpeed = rand() % 255;
    in.xDetectionCriteria = rand() % 255;
    in.yDetectionCriteria = rand() % 255;
    in.resetCriteria = rand() % 255;
    in.sensitivity = rand() % 255;
    in.scaleFactor = rand() % 255;
    in.numThreads = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.type = rand() % 255;
    in.enable = false;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;
    in.minDetectionProbability = rand() % 255;
    in.initString = "serfrerferf";
    in.objects.clear();
    for (int i = 0; i < 5; ++i)
    {
        Object obj;
        obj.id = rand() % 255;
        obj.type = rand() % 255;
        obj.width = rand() % 255;
        obj.height = rand() % 255;
        obj.x = rand() % 255;
        obj.y = rand() % 255;
        obj.vX = rand() % 255;
        obj.vY = rand() % 255;
        obj.p = rand() % 255;
        in.objects.push_back(obj);
    }

    // Copy params.
    ObjectDetectorParams out = in;

    // Compare params.
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.minObjectWidth != out.minObjectWidth)
    {
        cout << "in.minObjectWidth" << endl;
        return false;
    }
    if (in.maxObjectWidth != out.maxObjectWidth)
    {
        cout << "in.maxObjectWidth" << endl;
        return false;
    }
    if (in.minObjectHeight != out.minObjectHeight)
    {
        cout << "in.minObjectHeight" << endl;
        return false;
    }
    if (in.maxObjectHeight != out.maxObjectHeight)
    {
        cout << "in.maxObjectHeight" << endl;
        return false;
    }
    if (in.minXSpeed != out.minXSpeed)
    {
        cout << "in.minXSpeed" << endl;
        return false;
    }
    if (in.maxXSpeed != out.maxXSpeed)
    {
        cout << "in.maxXSpeed" << endl;
        return false;
    }
    if (in.minYSpeed != out.minYSpeed)
    {
        cout << "in.minYSpeed" << endl;
        return false;
    }
    if (in.maxYSpeed != out.maxYSpeed)
    {
        cout << "in.maxYSpeed" << endl;
        return false;
    }
    if (in.xDetectionCriteria != out.xDetectionCriteria)
    {
        cout << "in.xDetectionCriteria" << endl;
        return false;
    }
    if (in.yDetectionCriteria != out.yDetectionCriteria)
    {
        cout << "in.yDetectionCriteria" << endl;
        return false;
    }
    if (in.resetCriteria != out.resetCriteria)
    {
        cout << "in.resetCriteria" << endl;
        return false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        return false;
    }
    if (in.scaleFactor != out.scaleFactor)
    {
        cout << "in.scaleFactor" << endl;
        return false;
    }
    if (in.numThreads != out.numThreads)
    {
        cout << "in.numThreads" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
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
    if (in.objects.size() != out.objects.size())
    {
        cout << "in.objects.size()" << endl;
        return false;
    }
    for (int i = 0; i < in.objects.size(); ++i)
    {
        if (in.objects[i].id != out.objects[i].id)
        {
            cout << "in.objects[" << i << "].id" << endl;
            return false;
        }
        if (in.objects[i].type != out.objects[i].type)
        {
            cout << "in.objects[" << i << "].type" << endl;
            return false;
        }
        if (in.objects[i].width != out.objects[i].width)
        {
            cout << "in.objects[" << i << "].width" << endl;
            return false;
        }
        if (in.objects[i].height != out.objects[i].height)
        {
            cout << "in.objects[" << i << "].height" << endl;
            return false;
        }
        if (in.objects[i].x != out.objects[i].x)
        {
            cout << "in.objects[" << i << "].x" << endl;
            return false;
        }
        if (in.objects[i].y != out.objects[i].y)
        {
            cout << "in.objects[" << i << "].y" << endl;
            return false;
        }
        if (in.objects[i].vX != out.objects[i].vX)
        {
            cout << "in.objects[" << i << "].vX" << endl;
            return false;
        }
        if (in.objects[i].vY != out.objects[i].vY)
        {
            cout << "in.objects[" << i << "].vY" << endl;
            return false;
        }
        if (in.objects[i].p != out.objects[i].p)
        {
            cout << "in.objects[" << i << "].p" << endl;
            return false;
        }
    }
    if (in.initString != out.initString)
    {
        cout << "in.in.initString" << endl;
        return false;
    }

    return true;
}



// Encode/decode test.
bool encodeDecodeTest()
{
    // Prepare random params.
    ObjectDetectorParams in;
    in.logMode = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.minObjectWidth = rand() % 255;
    in.maxObjectWidth = rand() % 255;
    in.minObjectHeight = rand() % 255;
    in.maxObjectHeight = rand() % 255;
    in.minXSpeed = rand() % 255;
    in.maxXSpeed = rand() % 255;
    in.minYSpeed = rand() % 255;
    in.maxYSpeed = rand() % 255;
    in.xDetectionCriteria = rand() % 255;
    in.yDetectionCriteria = rand() % 255;
    in.resetCriteria = rand() % 255;
    in.sensitivity = rand() % 255;
    in.scaleFactor = rand() % 255;
    in.numThreads = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.type = rand() % 255;
    in.enable = false;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;
    in.minDetectionProbability = rand() % 255;
    in.initString = "alsjfhkjlkjsa";
    in.objects.clear();
    for (int i = 0; i < 5; ++i)
    {
        Object obj;
        obj.id = rand() % 255;
        obj.type = rand() % 255;
        obj.width = rand() % 255;
        obj.height = rand() % 255;
        obj.x = rand() % 255;
        obj.y = rand() % 255;
        obj.vX = rand() % 255;
        obj.vY = rand() % 255;
        obj.p = rand() % 255;
        in.objects.push_back(obj);
    }

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, size);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    ObjectDetectorParams out;
    if (!out.decode(data))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.minObjectWidth != out.minObjectWidth)
    {
        cout << "in.minObjectWidth" << endl;
        return false;
    }
    if (in.maxObjectWidth != out.maxObjectWidth)
    {
        cout << "in.maxObjectWidth" << endl;
        return false;
    }
    if (in.minObjectHeight != out.minObjectHeight)
    {
        cout << "in.minObjectHeight" << endl;
        return false;
    }
    if (in.maxObjectHeight != out.maxObjectHeight)
    {
        cout << "in.maxObjectHeight" << endl;
        return false;
    }
    if (in.minXSpeed != out.minXSpeed)
    {
        cout << "in.minXSpeed" << endl;
        return false;
    }
    if (in.maxXSpeed != out.maxXSpeed)
    {
        cout << "in.maxXSpeed" << endl;
        return false;
    }
    if (in.minYSpeed != out.minYSpeed)
    {
        cout << "in.minYSpeed" << endl;
        return false;
    }
    if (in.maxYSpeed != out.maxYSpeed)
    {
        cout << "in.maxYSpeed" << endl;
        return false;
    }
    if (in.xDetectionCriteria != out.xDetectionCriteria)
    {
        cout << "in.xDetectionCriteria" << endl;
        return false;
    }
    if (in.yDetectionCriteria != out.yDetectionCriteria)
    {
        cout << "in.yDetectionCriteria" << endl;
        return false;
    }
    if (in.resetCriteria != out.resetCriteria)
    {
        cout << "in.resetCriteria" << endl;
        return false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        return false;
    }
    if (in.scaleFactor != out.scaleFactor)
    {
        cout << "in.scaleFactor" << endl;
        return false;
    }
    if (in.numThreads != out.numThreads)
    {
        cout << "in.numThreads" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
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
    if (in.minDetectionProbability != out.minDetectionProbability)
    {
        cout << "in.minDetectionProbability" << endl;
        return false;
    }
    if (in.objects.size() != out.objects.size())
    {
        cout << "in.objects.size()" << endl;
        return false;
    }
    for (int i = 0; i < in.objects.size(); ++i)
    {
        if (in.objects[i].id != out.objects[i].id)
        {
            cout << "in.objects[" << i << "].id" << endl;
            return false;
        }
        if (in.objects[i].type != out.objects[i].type)
        {
            cout << "in.objects[" << i << "].type" << endl;
            return false;
        }
        if (in.objects[i].width != out.objects[i].width)
        {
            cout << "in.objects[" << i << "].width" << endl;
            return false;
        }
        if (in.objects[i].height != out.objects[i].height)
        {
            cout << "in.objects[" << i << "].height" << endl;
            return false;
        }
        if (in.objects[i].x != out.objects[i].x)
        {
            cout << "in.objects[" << i << "].x" << endl;
            return false;
        }
        if (in.objects[i].y != out.objects[i].y)
        {
            cout << "in.objects[" << i << "].y" << endl;
            return false;
        }
        if (in.objects[i].vX != out.objects[i].vX)
        {
            cout << "in.objects[" << i << "].vX" << endl;
            return false;
        }
        if (in.objects[i].vY != out.objects[i].vY)
        {
            cout << "in.objects[" << i << "].vY" << endl;
            return false;
        }
        if (in.objects[i].p != out.objects[i].p)
        {
            cout << "in.objects[" << i << "].p" << endl;
            return false;
        }
    }
    if ("" != out.initString)
    {
        cout << "in.initString" << endl;
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
    ObjectDetector::encodeCommand(data, size, ObjectDetectorCommand::RESET);

    // Decode command.
    ObjectDetectorCommand commandId;
    ObjectDetectorParam paramId;
    float value = 0.0f;
    if (ObjectDetector::decodeCommand(data, size, paramId, commandId, value) != 0)
    {
        cout << "Command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (commandId != ObjectDetectorCommand::RESET)
    {
        cout << "not a VSourceCommand::RESTART" << endl;
        return false;
    }

    // Encode param.
    outValue = (float)(rand() % 20);
    ObjectDetector::encodeSetParamCommand(
    data, size, ObjectDetectorParam::NUM_THREADS, outValue);

    // Decode command.
    value = 0.0f;
    if (ObjectDetector::decodeCommand(data, size, paramId, commandId, value) != 1)
    {
        cout << "Set param command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (paramId != ObjectDetectorParam::NUM_THREADS)
    {
        cout << "not a VSourceParam::EXPOSURE" << endl;
        return false;
    }
    if (value != outValue)
    {
        cout << "not equal value" << endl;
        return false;
    }

    return true;
}



/// JSON read/write test.
bool jsonReadWriteTest()
{
    // Prepare random params.
    ObjectDetectorParams in;
    in.logMode = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.minObjectWidth = rand() % 255;
    in.maxObjectWidth = rand() % 255;
    in.minObjectHeight = rand() % 255;
    in.maxObjectHeight = rand() % 255;
    in.minXSpeed = rand() % 255;
    in.maxXSpeed = rand() % 255;
    in.minYSpeed = rand() % 255;
    in.maxYSpeed = rand() % 255;
    in.xDetectionCriteria = rand() % 255;
    in.yDetectionCriteria = rand() % 255;
    in.resetCriteria = rand() % 255;
    in.sensitivity = rand() % 255;
    in.scaleFactor = rand() % 255;
    in.numThreads = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.type = rand() % 255;
    in.enable = false;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;
    in.minDetectionProbability = rand() % 255;
    in.initString = "sfsfsfsfsf";
    in.objects.clear();
    for (int i = 0; i < 5; ++i)
    {
        Object obj;
        obj.id = rand() % 255;
        obj.type = rand() % 255;
        obj.width = rand() % 255;
        obj.height = rand() % 255;
        obj.x = rand() % 255;
        obj.y = rand() % 255;
        obj.vX = rand() % 255;
        obj.vY = rand() % 255;
        obj.p = rand() % 255;
        in.objects.push_back(obj);
    }

    // Write params to file.
    cr::utils::ConfigReader inConfig;
    inConfig.set(in, "ObjectDetectorParams");
    inConfig.writeToFile("ObjectDetectorParams.json");

    // Read params from file.
    cr::utils::ConfigReader outConfig;
    if(!outConfig.readFromFile("ObjectDetectorParams.json"))
    {
        cout << "Can't open config file" << endl;
        return false;
    }

    ObjectDetectorParams out;
    if(!outConfig.get(out, "ObjectDetectorParams"))
    {
        cout << "Can't read params from file" << endl;
        return false;
    }

    // Compare params.
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        return false;
    }
    if (in.frameBufferSize != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.minObjectWidth != out.minObjectWidth)
    {
        cout << "in.minObjectWidth" << endl;
        return false;
    }
    if (in.maxObjectWidth != out.maxObjectWidth)
    {
        cout << "in.maxObjectWidth" << endl;
        return false;
    }
    if (in.minObjectHeight != out.minObjectHeight)
    {
        cout << "in.minObjectHeight" << endl;
        return false;
    }
    if (in.maxObjectHeight != out.maxObjectHeight)
    {
        cout << "in.maxObjectHeight" << endl;
        return false;
    }
    if (in.minXSpeed != out.minXSpeed)
    {
        cout << "in.minXSpeed" << endl;
        return false;
    }
    if (in.maxXSpeed != out.maxXSpeed)
    {
        cout << "in.maxXSpeed" << endl;
        return false;
    }
    if (in.minYSpeed != out.minYSpeed)
    {
        cout << "in.minYSpeed" << endl;
        return false;
    }
    if (in.maxYSpeed != out.maxYSpeed)
    {
        cout << "in.maxYSpeed" << endl;
        return false;
    }
    if (in.xDetectionCriteria != out.xDetectionCriteria)
    {
        cout << "in.xDetectionCriteria" << endl;
        return false;
    }
    if (in.yDetectionCriteria != out.yDetectionCriteria)
    {
        cout << "in.yDetectionCriteria" << endl;
        return false;
    }
    if (in.resetCriteria != out.resetCriteria)
    {
        cout << "in.resetCriteria" << endl;
        return false;
    }
    if (in.sensitivity != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        return false;
    }
    if (in.scaleFactor != out.scaleFactor)
    {
        cout << "in.scaleFactor" << endl;
        return false;
    }
    if (in.numThreads != out.numThreads)
    {
        cout << "in.numThreads" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
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
    if (in.minDetectionProbability != out.minDetectionProbability)
    {
        cout << "in.minDetectionProbability" << endl;
        return false;
    }
    if (in.initString != out.initString)
    {
        cout << "in.initString" << endl;
        return false;
    }

    return true;
}



/// Encode/decode test with params mask.
bool encodeDecodeWithMaskTest()
{
    // Prepare random params.
    ObjectDetectorParams in;
    in.logMode = rand() % 255;
    in.frameBufferSize = rand() % 255;
    in.minObjectWidth = rand() % 255;
    in.maxObjectWidth = rand() % 255;
    in.minObjectHeight = rand() % 255;
    in.maxObjectHeight = rand() % 255;
    in.minXSpeed = rand() % 255;
    in.maxXSpeed = rand() % 255;
    in.minYSpeed = rand() % 255;
    in.maxYSpeed = rand() % 255;
    in.xDetectionCriteria = rand() % 255;
    in.yDetectionCriteria = rand() % 255;
    in.resetCriteria = rand() % 255;
    in.sensitivity = rand() % 255;
    in.scaleFactor = rand() % 255;
    in.numThreads = rand() % 255;
    in.processingTimeMks = rand() % 255;
    in.type = rand() % 255;
    in.enable = false;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;
    in.minDetectionProbability = rand() % 255;
    in.objects.clear();
    for (int i = 0; i < 5; ++i)
    {
        Object obj;
        obj.id = rand() % 255;
        obj.type = rand() % 255;
        obj.width = rand() % 255;
        obj.height = rand() % 255;
        obj.x = rand() % 255;
        obj.y = rand() % 255;
        obj.vX = rand() % 255;
        obj.vY = rand() % 255;
        obj.p = rand() % 255;
        in.objects.push_back(obj);
    }

    // Prepare mask.
    ObjectDetectorParamsMask mask;
    mask.logMode = true;
    mask.frameBufferSize = false;
    mask.minObjectWidth = true;
    mask.maxObjectWidth = false;
    mask.minObjectHeight = true;
    mask.maxObjectHeight = false;
    mask.minXSpeed = true;
    mask.maxXSpeed = false;
    mask.minYSpeed = true;
    mask.maxYSpeed = false;
    mask.xDetectionCriteria = true;
    mask.yDetectionCriteria = false;
    mask.resetCriteria = true;
    mask.sensitivity = false;
    mask.scaleFactor = true;
    mask.numThreads = false;
    mask.processingTimeMks = true;
    mask.type = false;
    mask.enable = true;
    mask.custom1 = false;
    mask.custom2 = true;
    mask.custom3 = false;
    mask.objects = true;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, size, &mask);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    ObjectDetectorParams out;
    if (!out.decode(data))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    if (in.logMode != out.logMode)
    {
        cout << "in.logMode" << endl;
        return false;
    }
    if (0 != out.frameBufferSize)
    {
        cout << "in.frameBufferSize" << endl;
        return false;
    }
    if (in.minObjectWidth != out.minObjectWidth)
    {
        cout << "in.minObjectWidth" << endl;
        return false;
    }
    if (0 != out.maxObjectWidth)
    {
        cout << "in.maxObjectWidth" << endl;
        return false;
    }
    if (in.minObjectHeight != out.minObjectHeight)
    {
        cout << "in.minObjectHeight" << endl;
        return false;
    }
    if (0 != out.maxObjectHeight)
    {
        cout << "in.maxObjectHeight" << endl;
        return false;
    }
    if (in.minXSpeed != out.minXSpeed)
    {
        cout << "in.minXSpeed" << endl;
        return false;
    }
    if (0 != out.maxXSpeed)
    {
        cout << "in.maxXSpeed" << endl;
        return false;
    }
    if (in.minYSpeed != out.minYSpeed)
    {
        cout << "in.minYSpeed" << endl;
        return false;
    }
    if (0 != out.maxYSpeed)
    {
        cout << "in.maxYSpeed" << endl;
        return false;
    }
    if (in.xDetectionCriteria != out.xDetectionCriteria)
    {
        cout << "in.xDetectionCriteria" << endl;
        return false;
    }
    if (0 != out.yDetectionCriteria)
    {
        cout << "in.yDetectionCriteria" << endl;
        return false;
    }
    if (in.resetCriteria != out.resetCriteria)
    {
        cout << "in.resetCriteria" << endl;
        return false;
    }
    if (0 != out.sensitivity)
    {
        cout << "in.sensitivity" << endl;
        return false;
    }
    if (in.scaleFactor != out.scaleFactor)
    {
        cout << "in.scaleFactor" << endl;
        return false;
    }
    if (0 != out.numThreads)
    {
        cout << "in.numThreads" << endl;
        return false;
    }
    if (in.processingTimeMks != out.processingTimeMks)
    {
        cout << "in.processingTimeMks" << endl;
        return false;
    }
    if (0 != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
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
    if (in.minDetectionProbability != out.minDetectionProbability)
    {
        cout << "in.minDetectionProbability" << endl;
        return false;
    }
    if (in.objects.size() != out.objects.size())
    {
        cout << "in.objects.size()" << endl;
        return false;
    }
    for (int i = 0; i < in.objects.size(); ++i)
    {
        if (in.objects[i].id != out.objects[i].id)
        {
            cout << "in.objects[" << i << "].id" << endl;
            return false;
        }
        if (in.objects[i].type != out.objects[i].type)
        {
            cout << "in.objects[" << i << "].type" << endl;
            return false;
        }
        if (in.objects[i].width != out.objects[i].width)
        {
            cout << "in.objects[" << i << "].width" << endl;
            return false;
        }
        if (in.objects[i].height != out.objects[i].height)
        {
            cout << "in.objects[" << i << "].height" << endl;
            return false;
        }
        if (in.objects[i].x != out.objects[i].x)
        {
            cout << "in.objects[" << i << "].x" << endl;
            return false;
        }
        if (in.objects[i].y != out.objects[i].y)
        {
            cout << "in.objects[" << i << "].y" << endl;
            return false;
        }
        if (in.objects[i].vX != out.objects[i].vX)
        {
            cout << "in.objects[" << i << "].vX" << endl;
            return false;
        }
        if (in.objects[i].vY != out.objects[i].vY)
        {
            cout << "in.objects[" << i << "].vY" << endl;
            return false;
        }
        if (in.objects[i].p != out.objects[i].p)
        {
            cout << "in.objects[" << i << "].p" << endl;
            return false;
        }
    }

    return true;
}














