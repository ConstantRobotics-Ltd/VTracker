#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include "ConfigReader.h"
#include "VTracker.h"
#include "VTrackerVersion.h"



namespace
{
/// Size of encoded params with all fields, bytes.
constexpr int PARAMS_MAX_SIZE{135};
/// Size of encoded params header (data type, version, mask), bytes.
constexpr int PARAMS_HEADER_SIZE{8};
/// Size of encoded command, bytes.
constexpr int COMMAND_SIZE{19};
/// Size of encoded set param command, bytes.
constexpr int SET_PARAM_COMMAND_SIZE{11};
/// ID of the first and the last command.
constexpr int FIRST_COMMAND_ID{1};
constexpr int LAST_COMMAND_ID{15};
/// ID of the first and the last param.
constexpr int FIRST_PARAM_ID{1};
constexpr int LAST_PARAM_ID{15};
/// Number of iterations of the random tests.
constexpr int RANDOM_ITERATIONS{2000};
/// Number of iterations of the corruption test.
constexpr int CORRUPTION_ITERATIONS{50000};
/// Name of the JSON file used by the JSON file test.
const char* const JSON_FILE_NAME{"VTrackerParams.json"};

/// State of the test random generator. The tests use own deterministic
/// generator: results must be reproducible on all platforms.
uint32_t g_randomState{20240915U};



/// Get next random number in [0, limit).
int randomInt(int limit)
{
    g_randomState = g_randomState * 1664525U + 1013904223U;
    return static_cast<int>((g_randomState >> 8) %
                            static_cast<uint32_t>(limit));
}



float randomFloat(int limit)
{
    return static_cast<float>(randomInt(limit));
}



bool randomBool()
{
    return randomInt(2) == 1;
}



/// Fill all fields of params by random values.
void randomize(cr::vtracker::VTrackerParams& p)
{
    p.mode = randomInt(255);
    p.rectX = randomInt(255);
    p.rectY = randomInt(255);
    p.rectWidth = randomInt(255);
    p.rectHeight = randomInt(255);
    p.objectX = randomInt(255);
    p.objectY = randomInt(255);
    p.objectWidth = randomInt(255);
    p.objectHeight = randomInt(255);
    p.lostModeFrameCounter = randomInt(255);
    p.frameCounter = randomInt(255);
    p.frameWidth = randomInt(255);
    p.frameHeight = randomInt(255);
    p.searchWindowWidth = randomInt(255);
    p.searchWindowHeight = randomInt(255);
    p.searchWindowX = randomInt(255);
    p.searchWindowY = randomInt(255);
    p.lostModeOption = randomInt(255);
    p.frameBufferSize = randomInt(255);
    p.maxFramesInLostMode = randomInt(255);
    p.processedFrameId = randomInt(255);
    p.frameId = randomInt(255);
    p.velX = randomFloat(255);
    p.velY = randomFloat(255);
    p.detectionProbability = randomFloat(255);
    p.rectAutoSize = randomBool();
    p.rectAutoPosition = randomBool();
    p.multipleThreads = randomBool();
    p.numChannels = randomInt(255);
    p.type = randomInt(255);
    p.processingTimeMks = randomInt(255);
    p.custom1 = randomFloat(255);
    p.custom2 = randomFloat(255);
    p.custom3 = randomFloat(255);
}



/// Fill all flags of the mask by random values.
void randomize(cr::vtracker::VTrackerParamsMask& m)
{
    m.mode = randomBool();
    m.rectX = randomBool();
    m.rectY = randomBool();
    m.rectWidth = randomBool();
    m.rectHeight = randomBool();
    m.objectX = randomBool();
    m.objectY = randomBool();
    m.objectWidth = randomBool();
    m.objectHeight = randomBool();
    m.lostModeFrameCounter = randomBool();
    m.frameCounter = randomBool();
    m.frameWidth = randomBool();
    m.frameHeight = randomBool();
    m.searchWindowWidth = randomBool();
    m.searchWindowHeight = randomBool();
    m.searchWindowX = randomBool();
    m.searchWindowY = randomBool();
    m.lostModeOption = randomBool();
    m.frameBufferSize = randomBool();
    m.maxFramesInLostMode = randomBool();
    m.processedFrameId = randomBool();
    m.frameId = randomBool();
    m.velX = randomBool();
    m.velY = randomBool();
    m.detectionProbability = randomBool();
    m.rectAutoSize = randomBool();
    m.rectAutoPosition = randomBool();
    m.multipleThreads = randomBool();
    m.numChannels = randomBool();
    m.type = randomBool();
    m.processingTimeMks = randomBool();
    m.custom1 = randomBool();
    m.custom2 = randomBool();
    m.custom3 = randomBool();
}



/// Set all flags of the mask.
void setAll(cr::vtracker::VTrackerParamsMask& m, bool value)
{
    m.mode = value;
    m.rectX = value;
    m.rectY = value;
    m.rectWidth = value;
    m.rectHeight = value;
    m.objectX = value;
    m.objectY = value;
    m.objectWidth = value;
    m.objectHeight = value;
    m.lostModeFrameCounter = value;
    m.frameCounter = value;
    m.frameWidth = value;
    m.frameHeight = value;
    m.searchWindowWidth = value;
    m.searchWindowHeight = value;
    m.searchWindowX = value;
    m.searchWindowY = value;
    m.lostModeOption = value;
    m.frameBufferSize = value;
    m.maxFramesInLostMode = value;
    m.processedFrameId = value;
    m.frameId = value;
    m.velX = value;
    m.velY = value;
    m.detectionProbability = value;
    m.rectAutoSize = value;
    m.rectAutoPosition = value;
    m.multipleThreads = value;
    m.numChannels = value;
    m.type = value;
    m.processingTimeMks = value;
    m.custom1 = value;
    m.custom2 = value;
    m.custom3 = value;
}



/// Expected size of encoded params for the mask, bytes.
int expectedSize(const cr::vtracker::VTrackerParamsMask& m)
{
    const bool values[] = {
        m.mode, m.rectX, m.rectY, m.rectWidth, m.rectHeight, m.objectX,
        m.objectY, m.objectWidth, m.objectHeight, m.lostModeFrameCounter,
        m.frameCounter, m.frameWidth, m.frameHeight, m.searchWindowWidth,
        m.searchWindowHeight, m.searchWindowX, m.searchWindowY,
        m.lostModeOption, m.frameBufferSize, m.maxFramesInLostMode,
        m.processedFrameId, m.frameId, m.velX, m.velY, m.detectionProbability,
        m.numChannels, m.type, m.processingTimeMks, m.custom1, m.custom2,
        m.custom3};
    int size = PARAMS_HEADER_SIZE;
    for (const bool selected : values)
    {
        size += selected ? 4 : 0;
    }
    size += m.rectAutoSize ? 1 : 0;
    size += m.rectAutoPosition ? 1 : 0;
    size += m.multipleThreads ? 1 : 0;
    return size;
}



/// Get bits of a float: encoded floats must be restored exactly.
uint32_t bitsOf(float value)
{
    uint32_t bits{0};
    static_assert(sizeof(bits) == sizeof(value), "wrong size of float");
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}



/// Get the value of an int or bool field for comparison.
int bitsOf(int value)
{
    return value;
}



int bitsOf(bool value)
{
    return value ? 1 : 0;
}



/// Compare a field: the output must be equal to the input if the field is
/// selected and equal to zero if not. The number of mismatches is incremented
/// for each wrong field.
template <class T>
void checkField(const char* name, T in, T out, bool selected, int& errors)
{
    const T expected = selected ? in : T{};
    if (bitsOf(expected) != bitsOf(out))
    {
        std::cout << "Mismatch in field " << name << std::endl;
        ++errors;
    }
}



/// Compare all fields of params. Fields which are not selected by the mask
/// must be zero in the output params.
bool compareParams(const cr::vtracker::VTrackerParams& in,
                   const cr::vtracker::VTrackerParams& out,
                   const cr::vtracker::VTrackerParamsMask& m)
{
    int errors = 0;
    checkField("mode", in.mode, out.mode, m.mode, errors);
    checkField("rectX", in.rectX, out.rectX, m.rectX, errors);
    checkField("rectY", in.rectY, out.rectY, m.rectY, errors);
    checkField("rectWidth", in.rectWidth, out.rectWidth,
               m.rectWidth, errors);
    checkField("rectHeight", in.rectHeight, out.rectHeight,
               m.rectHeight, errors);
    checkField("objectX", in.objectX, out.objectX, m.objectX, errors);
    checkField("objectY", in.objectY, out.objectY, m.objectY, errors);
    checkField("objectWidth", in.objectWidth, out.objectWidth,
               m.objectWidth, errors);
    checkField("objectHeight", in.objectHeight, out.objectHeight,
               m.objectHeight, errors);
    checkField("lostModeFrameCounter", in.lostModeFrameCounter,
               out.lostModeFrameCounter, m.lostModeFrameCounter, errors);
    checkField("frameCounter", in.frameCounter, out.frameCounter,
               m.frameCounter, errors);
    checkField("frameWidth", in.frameWidth, out.frameWidth,
               m.frameWidth, errors);
    checkField("frameHeight", in.frameHeight, out.frameHeight,
               m.frameHeight, errors);
    checkField("searchWindowWidth", in.searchWindowWidth,
               out.searchWindowWidth, m.searchWindowWidth, errors);
    checkField("searchWindowHeight", in.searchWindowHeight,
               out.searchWindowHeight, m.searchWindowHeight, errors);
    checkField("searchWindowX", in.searchWindowX, out.searchWindowX,
               m.searchWindowX, errors);
    checkField("searchWindowY", in.searchWindowY, out.searchWindowY,
               m.searchWindowY, errors);
    checkField("lostModeOption", in.lostModeOption, out.lostModeOption,
               m.lostModeOption, errors);
    checkField("frameBufferSize", in.frameBufferSize,
               out.frameBufferSize, m.frameBufferSize, errors);
    checkField("maxFramesInLostMode", in.maxFramesInLostMode,
               out.maxFramesInLostMode, m.maxFramesInLostMode, errors);
    checkField("processedFrameId", in.processedFrameId,
               out.processedFrameId, m.processedFrameId, errors);
    checkField("frameId", in.frameId, out.frameId, m.frameId, errors);
    checkField("velX", in.velX, out.velX, m.velX, errors);
    checkField("velY", in.velY, out.velY, m.velY, errors);
    checkField("detectionProbability", in.detectionProbability,
               out.detectionProbability, m.detectionProbability, errors);
    checkField("rectAutoSize", in.rectAutoSize, out.rectAutoSize,
               m.rectAutoSize, errors);
    checkField("rectAutoPosition", in.rectAutoPosition,
               out.rectAutoPosition, m.rectAutoPosition, errors);
    checkField("multipleThreads", in.multipleThreads,
               out.multipleThreads, m.multipleThreads, errors);
    checkField("numChannels", in.numChannels, out.numChannels,
               m.numChannels, errors);
    checkField("type", in.type, out.type, m.type, errors);
    checkField("processingTimeMks", in.processingTimeMks,
               out.processingTimeMks, m.processingTimeMks, errors);
    checkField("custom1", in.custom1, out.custom1, m.custom1, errors);
    checkField("custom2", in.custom2, out.custom2, m.custom2, errors);
    checkField("custom3", in.custom3, out.custom3, m.custom3, errors);
    return errors == 0;
}



/// Compare the fields which are stored in JSON files.
bool compareJsonFields(const cr::vtracker::VTrackerParams& in,
                       const cr::vtracker::VTrackerParams& out)
{
    int errors = 0;
    checkField("rectWidth", in.rectWidth, out.rectWidth, true, errors);
    checkField("rectHeight", in.rectHeight, out.rectHeight, true, errors);
    checkField("searchWindowWidth", in.searchWindowWidth,
               out.searchWindowWidth, true, errors);
    checkField("searchWindowHeight", in.searchWindowHeight,
               out.searchWindowHeight, true, errors);
    checkField("lostModeOption", in.lostModeOption, out.lostModeOption,
               true, errors);
    checkField("frameBufferSize", in.frameBufferSize,
               out.frameBufferSize, true, errors);
    checkField("maxFramesInLostMode", in.maxFramesInLostMode,
               out.maxFramesInLostMode, true, errors);
    checkField("rectAutoSize", in.rectAutoSize, out.rectAutoSize,
               true, errors);
    checkField("rectAutoPosition", in.rectAutoPosition,
               out.rectAutoPosition, true, errors);
    checkField("multipleThreads", in.multipleThreads,
               out.multipleThreads, true, errors);
    checkField("numChannels", in.numChannels, out.numChannels,
               true, errors);
    checkField("type", in.type, out.type, true, errors);
    checkField("custom1", in.custom1, out.custom1, true, errors);
    checkField("custom2", in.custom2, out.custom2, true, errors);
    checkField("custom3", in.custom3, out.custom3, true, errors);
    return errors == 0;
}



/// Print a failed check and return false.
bool fail(const char* message)
{
    std::cout << message << std::endl;
    return false;
}



/// Remove a file when the object is destroyed (JSON file test).
class FileRemover
{
public:
    explicit FileRemover(const char* fileName) : m_fileName(fileName) {}
    ~FileRemover()
    {
        // The file does not exist if the test failed before writing it.
        if (std::remove(m_fileName) != 0)
        {
            std::cerr << "File " << m_fileName << " was not removed"
                      << std::endl;
        }
    }
    FileRemover(const FileRemover&) = delete;
    FileRemover& operator= (const FileRemover&) = delete;

private:
    const char* const m_fileName;
};



/// Copy test.
bool copyTest()
{
    // Prepare random params.
    cr::vtracker::VTrackerParams in;
    randomize(in);
    const cr::vtracker::VTrackerParamsMask all;

    // Copy params (constructor and assignment).
    const cr::vtracker::VTrackerParams out = in;
    if (!compareParams(in, out, all))
    {
        return fail("Copy constructor error");
    }
    cr::vtracker::VTrackerParams assigned;
    assigned = in;
    if (!compareParams(in, assigned, all))
    {
        return fail("Assignment error");
    }

    // Self assignment must not change the object.
    const cr::vtracker::VTrackerParams& self = assigned;
    assigned = self;
    if (!compareParams(in, assigned, all))
    {
        return fail("Self assignment error");
    }

    return true;
}



/// Encode/decode test.
bool encodeDecodeTest()
{
    // Prepare random params.
    cr::vtracker::VTrackerParams in;
    randomize(in);

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    if (!in.encode(data, 1024, size))
    {
        return fail("Can't encode data");
    }
    std::cout << "Encoded data size: " << size << " bytes" << std::endl;
    if (size != PARAMS_MAX_SIZE)
    {
        return fail("Wrong size of encoded data");
    }

    // Decode data into params filled by other values: all fields must be
    // overwritten.
    cr::vtracker::VTrackerParams out;
    randomize(out);
    if (!out.decode(data, size))
    {
        return fail("Can't decode data");
    }

    // Compare params.
    const cr::vtracker::VTrackerParamsMask all;
    return compareParams(in, out, all);
}



/// Encode/decode test with params mask.
bool encodeDecodeWithMaskTest()
{
    // Prepare random params.
    cr::vtracker::VTrackerParams in;
    randomize(in);

    // Prepare mask (every second parameter).
    cr::vtracker::VTrackerParamsMask mask;
    setAll(mask, false);
    mask.mode = true;
    mask.rectY = true;
    mask.rectHeight = true;
    mask.objectY = true;
    mask.objectHeight = true;
    mask.frameCounter = true;
    mask.frameHeight = true;
    mask.searchWindowHeight = true;
    mask.searchWindowY = true;
    mask.frameBufferSize = true;
    mask.processedFrameId = true;
    mask.velX = true;
    mask.detectionProbability = true;
    mask.rectAutoPosition = true;
    mask.numChannels = true;
    mask.processingTimeMks = true;
    mask.custom2 = true;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    if (!in.encode(data, 1024, size, &mask))
    {
        return fail("Can't encode data");
    }
    std::cout << "Encoded data size: " << size << " bytes" << std::endl;
    if (size != 73 || size != expectedSize(mask))
    {
        return fail("Wrong size of encoded data");
    }

    // Decode data. Fields not selected by the mask must be zero.
    cr::vtracker::VTrackerParams out;
    if (!out.decode(data, size))
    {
        return fail("Can't decode data");
    }
    if (!compareParams(in, out, mask))
    {
        return false;
    }

    // Random masks.
    for (int i = 0; i < RANDOM_ITERATIONS; ++i)
    {
        randomize(in);
        randomize(mask);
        if (!in.encode(data, 1024, size, &mask) || size != expectedSize(mask))
        {
            return fail("Random mask: encode error");
        }
        randomize(out);
        if (!out.decode(data, size) || !compareParams(in, out, mask))
        {
            return fail("Random mask: decode error");
        }
    }

    return true;
}



/// Encode params arguments test (buffer size, null pointer, mask bits).
bool encodeArgumentsTest()
{
    cr::vtracker::VTrackerParams in;
    randomize(in);
    uint8_t data[PARAMS_MAX_SIZE + 8];
    std::memset(data, 0xA5, sizeof(data));
    int size = 777;

    // Null pointer.
    if (in.encode(nullptr, 1024, size) || size != 0)
    {
        return fail("Null pointer accepted");
    }

    // Buffer which is too small must be rejected and must not be touched.
    size = 777;
    if (in.encode(data, PARAMS_MAX_SIZE - 1, size) || size != 0)
    {
        return fail("Small buffer accepted");
    }
    if (in.encode(data, 0, size) || in.encode(data, -1, size) ||
        in.encode(data, std::numeric_limits<int>::min(), size))
    {
        return fail("Invalid buffer size accepted");
    }
    for (const uint8_t value : data)
    {
        if (value != 0xA5)
        {
            return fail("Buffer changed after rejected encode");
        }
    }

    // Buffer of exact size: nothing is written after the encoded data.
    if (!in.encode(data, PARAMS_MAX_SIZE, size) || size != PARAMS_MAX_SIZE)
    {
        return fail("Buffer of exact size rejected");
    }
    for (int i = PARAMS_MAX_SIZE; i < static_cast<int>(sizeof(data)); ++i)
    {
        if (data[i] != 0xA5)
        {
            return fail("Data written after the end of encoded data");
        }
    }

    // Header: data type and version, mask without mask pointer.
    if (data[0] != 0x02 || data[1] != VTRACKER_MAJOR_VERSION ||
        data[2] != VTRACKER_MINOR_VERSION)
    {
        return fail("Wrong header");
    }
    for (int i = 3; i < PARAMS_HEADER_SIZE; ++i)
    {
        if (data[i] != 0xFF)
        {
            return fail("Wrong mask without mask pointer");
        }
    }

    // All flags are set: the unused mask bits are zero.
    cr::vtracker::VTrackerParamsMask mask;
    if (!in.encode(data, PARAMS_MAX_SIZE, size, &mask) ||
        size != PARAMS_MAX_SIZE || data[3] != 0xFF || data[4] != 0xFF ||
        data[5] != 0xFF || data[6] != 0xFF || data[7] != 0xC0)
    {
        return fail("Wrong mask with all flags set");
    }

    // No flags: only the header.
    setAll(mask, false);
    if (!in.encode(data, PARAMS_MAX_SIZE, size, &mask) ||
        size != PARAMS_HEADER_SIZE)
    {
        return fail("Wrong size with no flags");
    }
    cr::vtracker::VTrackerParams out;
    randomize(out);
    if (!out.decode(data, size) || !compareParams(in, out, mask))
    {
        return fail("Wrong decoding of params with no flags");
    }

    return true;
}



/// Decode params with invalid data test: invalid data must be rejected and
/// the object must not be changed.
bool decodeInvalidDataTest()
{
    cr::vtracker::VTrackerParams in;
    randomize(in);
    uint8_t data[1024];
    int size = 0;
    if (!in.encode(data, 1024, size))
    {
        return fail("Can't encode data");
    }

    cr::vtracker::VTrackerParams sentinel;
    randomize(sentinel);
    const cr::vtracker::VTrackerParamsMask all;

    // Null pointer, invalid sizes.
    cr::vtracker::VTrackerParams out = sentinel;
    if (out.decode(nullptr, size) || out.decode(data, -1) ||
        out.decode(data, 0) || out.decode(data, PARAMS_HEADER_SIZE - 1) ||
        out.decode(data, std::numeric_limits<int>::min()))
    {
        return fail("Invalid arguments accepted");
    }
    if (!compareParams(sentinel, out, all))
    {
        return fail("Object changed after rejected decode (arguments)");
    }

    // Truncated data: every length shorter than the encoded data is invalid.
    for (int cut = 0; cut < size; ++cut)
    {
        if (out.decode(data, cut))
        {
            return fail("Truncated data accepted");
        }
        if (!compareParams(sentinel, out, all))
        {
            return fail("Object changed after rejected decode (truncated)");
        }
    }

    // Invalid header: data type, major and minor version.
    for (int index = 0; index < 3; ++index)
    {
        for (const int value : {0, 1, 3, 0x7F, 0xFF})
        {
            uint8_t copy[1024];
            std::memcpy(copy, data, static_cast<size_t>(size));
            if (copy[index] == value)
            {
                continue;
            }
            copy[index] = static_cast<uint8_t>(value);
            if (out.decode(copy, size))
            {
                return fail("Invalid header accepted");
            }
        }
    }
    if (!compareParams(sentinel, out, all))
    {
        return fail("Object changed after rejected decode (header)");
    }

    // Bytes after the encoded data are ignored.
    if (!out.decode(data, 1024) || !compareParams(in, out, all))
    {
        return fail("Data with trailing bytes rejected");
    }

    // Any non zero byte of a boolean field is true.
    in.rectAutoSize = false;
    in.rectAutoPosition = true;
    in.multipleThreads = true;
    if (!in.encode(data, 1024, size))
    {
        return fail("Can't encode data");
    }
    // Boolean fields are stored after 25 numeric fields of 4 bytes each.
    const int boolPos = PARAMS_HEADER_SIZE + 25 * 4;
    data[boolPos] = 0x02;
    data[boolPos + 1] = 0xFF;
    data[boolPos + 2] = 0x80;
    if (!out.decode(data, size) || !out.rectAutoSize || !out.rectAutoPosition ||
        !out.multipleThreads)
    {
        return fail("Wrong decoding of boolean fields");
    }

    return true;
}



/// Corruption test: random damaged data must never crash the decoder and
/// the result must be deterministic.
bool corruptionTest()
{
    cr::vtracker::VTrackerParams in;
    cr::vtracker::VTrackerParamsMask mask;
    uint8_t data[1024];
    int accepted = 0;
    int rejected = 0;
    for (int i = 0; i < CORRUPTION_ITERATIONS; ++i)
    {
        randomize(in);
        randomize(mask);
        int size = 0;
        if (!in.encode(data, 1024, size, &mask))
        {
            return fail("Can't encode data");
        }

        // Damage 1..4 bytes and use random data size.
        const int damaged = 1 + randomInt(4);
        for (int k = 0; k < damaged; ++k)
        {
            data[randomInt(size)] = static_cast<uint8_t>(randomInt(256));
        }
        const int dataSize = randomInt(PARAMS_MAX_SIZE + 10);

        cr::vtracker::VTrackerParams first;
        cr::vtracker::VTrackerParams second;
        const bool firstResult = first.decode(data, dataSize);
        const bool secondResult = second.decode(data, dataSize);
        if (firstResult != secondResult)
        {
            return fail("Not deterministic result");
        }
        if (firstResult)
        {
            const cr::vtracker::VTrackerParamsMask all;
            if (!compareParams(first, second, all))
            {
                return fail("Not deterministic params");
            }
            ++accepted;
        }
        else
        {
            ++rejected;
        }
    }
    std::cout << "Damaged data: " << accepted << " decoded, " << rejected
              << " rejected" << std::endl;

    return true;
}



/// Encode/decode commands test.
bool encodeDecodeCommandsTest()
{
    uint8_t data[1024];
    int size = 0;
    cr::vtracker::VTrackerCommand commandId =
            cr::vtracker::VTrackerCommand::RESET;
    cr::vtracker::VTrackerParam paramId =
            cr::vtracker::VTrackerParam::TYPE;

    // Commands.
    for (int id = FIRST_COMMAND_ID; id <= LAST_COMMAND_ID; ++id)
    {
        const float arg1 = randomFloat(20);
        const float arg2 = randomFloat(20);
        const float arg3 = randomFloat(20);
        cr::vtracker::VTracker::encodeCommand(
                    data, size, static_cast<cr::vtracker::VTrackerCommand>(id),
                    arg1, arg2, arg3);
        if (size != COMMAND_SIZE || data[0] != 0x00)
        {
            return fail("Wrong encoded command");
        }

        float in1 = -1.0f;
        float in2 = -1.0f;
        float in3 = -1.0f;
        if (cr::vtracker::VTracker::decodeCommand(
                    data, size, paramId, commandId, in1, in2, in3) != 0)
        {
            return fail("Command not decoded");
        }
        if (static_cast<int>(commandId) != id || in1 != arg1 || in2 != arg2 ||
            in3 != arg3)
        {
            return fail("Wrong command ID or arguments");
        }
    }

    // Set param commands.
    for (int id = FIRST_PARAM_ID; id <= LAST_PARAM_ID; ++id)
    {
        const float value = randomFloat(20);
        cr::vtracker::VTracker::encodeSetParamCommand(
                    data, size, static_cast<cr::vtracker::VTrackerParam>(id),
                    value);
        if (size != SET_PARAM_COMMAND_SIZE || data[0] != 0x01)
        {
            return fail("Wrong encoded set param command");
        }

        float in1 = -1.0f;
        float in2 = -1.0f;
        float in3 = -1.0f;
        if (cr::vtracker::VTracker::decodeCommand(
                    data, size, paramId, commandId, in1, in2, in3) != 1)
        {
            return fail("Set param command not decoded");
        }
        if (static_cast<int>(paramId) != id || in1 != value)
        {
            return fail("Wrong param ID or value");
        }
    }

    return true;
}



/// Decode command with invalid data test.
bool decodeCommandInvalidDataTest()
{
    uint8_t data[1024];
    int size = 0;
    cr::vtracker::VTrackerCommand commandId =
            cr::vtracker::VTrackerCommand::SET_LOST_MODE;
    cr::vtracker::VTrackerParam paramId =
            cr::vtracker::VTrackerParam::CUSTOM_1;
    float value1 = 0.0f;
    float value2 = 0.0f;
    float value3 = 0.0f;
    using cr::vtracker::VTracker;

    // Null pointers.
    size = 777;
    VTracker::encodeCommand(nullptr, size, cr::vtracker::VTrackerCommand::RESET);
    if (size != 0)
    {
        return fail("Size not reset by encodeCommand(nullptr)");
    }
    size = 777;
    VTracker::encodeSetParamCommand(
                nullptr, size, cr::vtracker::VTrackerParam::TYPE, 1.0f);
    if (size != 0)
    {
        return fail("Size not reset by encodeSetParamCommand(nullptr)");
    }
    if (VTracker::decodeCommand(nullptr, COMMAND_SIZE, paramId, commandId,
                                value1, value2, value3) != -1)
    {
        return fail("Null pointer accepted");
    }

    // Wrong sizes of a command.
    VTracker::encodeCommand(data, size, cr::vtracker::VTrackerCommand::CAPTURE,
                            1.0f, 2.0f, 3.0f);
    for (const int wrong : {std::numeric_limits<int>::min(), -1, 0, 1, 10, 11, 12,
                      18, 20, 100, std::numeric_limits<int>::max()})
    {
        if (VTracker::decodeCommand(data, wrong, paramId, commandId, value1,
                                    value2, value3) != -1)
        {
            return fail("Command with wrong size accepted");
        }
    }

    // Wrong sizes of a set param command.
    VTracker::encodeSetParamCommand(
                data, size, cr::vtracker::VTrackerParam::TYPE, 1.0f);
    for (const int wrong : {std::numeric_limits<int>::min(), -1, 0, 1, 10, 12, 18,
                      19, 100, std::numeric_limits<int>::max()})
    {
        if (VTracker::decodeCommand(data, wrong, paramId, commandId, value1,
                                    value2, value3) != -1)
        {
            return fail("Set param command with wrong size accepted");
        }
    }

    // Wrong version and data type.
    VTracker::encodeCommand(data, size, cr::vtracker::VTrackerCommand::CAPTURE,
                            1.0f, 2.0f, 3.0f);
    data[1] = static_cast<uint8_t>(data[1] + 1);
    if (VTracker::decodeCommand(data, size, paramId, commandId, value1,
                                value2, value3) != -1)
    {
        return fail("Wrong major version accepted");
    }
    data[1] = static_cast<uint8_t>(data[1] - 1);
    data[2] = static_cast<uint8_t>(data[2] + 1);
    if (VTracker::decodeCommand(data, size, paramId, commandId, value1,
                                value2, value3) != -1)
    {
        return fail("Wrong minor version accepted");
    }
    data[2] = static_cast<uint8_t>(data[2] - 1);
    for (const int type : {2, 3, 0x7F, 0xFF})
    {
        data[0] = static_cast<uint8_t>(type);
        if (VTracker::decodeCommand(data, size, paramId, commandId, value1,
                                    value2, value3) != -1)
        {
            return fail("Wrong data type accepted");
        }
    }

    // Unknown IDs: outputs for IDs must stay unchanged.
    commandId = cr::vtracker::VTrackerCommand::SET_LOST_MODE;
    paramId = cr::vtracker::VTrackerParam::CUSTOM_1;
    const int wrongIds[] = {std::numeric_limits<int>::min(), -1, 0,
                            LAST_COMMAND_ID + 1, 77, 0x7FFFFFFF};
    for (const int id : wrongIds)
    {
        VTracker::encodeCommand(
                    data, size, static_cast<cr::vtracker::VTrackerCommand>(id));
        if (VTracker::decodeCommand(data, size, paramId, commandId, value1,
                                    value2, value3) != -1)
        {
            return fail("Unknown command ID accepted");
        }
        VTracker::encodeSetParamCommand(
                    data, size, static_cast<cr::vtracker::VTrackerParam>(id),
                    1.0f);
        if (VTracker::decodeCommand(data, size, paramId, commandId, value1,
                                    value2, value3) != -1)
        {
            return fail("Unknown param ID accepted");
        }
    }
    if (commandId != cr::vtracker::VTrackerCommand::SET_LOST_MODE ||
        paramId != cr::vtracker::VTrackerParam::CUSTOM_1)
    {
        return fail("Output IDs changed after rejected decode");
    }

    return true;
}



/// Version test.
bool versionTest()
{
    const std::string expected = std::to_string(VTRACKER_MAJOR_VERSION) + "." +
                                 std::to_string(VTRACKER_MINOR_VERSION) + "." +
                                 std::to_string(VTRACKER_PATCH_VERSION);
    std::cout << "Version: " << cr::vtracker::VTracker::getVersion()
              << std::endl;
    return cr::vtracker::VTracker::getVersion() == expected;
}



/// JSON read/write test (file).
bool jsonReadWriteTest()
{
    // Prepare random params.
    cr::vtracker::VTrackerParams in;
    randomize(in);

    // Write params to file.
    const FileRemover remover(JSON_FILE_NAME);
    cr::utils::ConfigReader inConfig;
    if (!inConfig.set(in, "VTrackerParams"))
    {
        return fail("Can't set params to config");
    }
    if (!inConfig.writeToFile(JSON_FILE_NAME))
    {
        return fail("Can't write config file");
    }

    // Read params from file.
    cr::utils::ConfigReader outConfig;
    if (!outConfig.readFromFile(JSON_FILE_NAME))
    {
        return fail("Can't open config file");
    }
    cr::vtracker::VTrackerParams out;
    if (!outConfig.get(out, "VTrackerParams"))
    {
        return fail("Can't read params from file");
    }

    // Compare params.
    return compareJsonFields(in, out);
}



/// JSON read test with invalid data: invalid JSON must be rejected without
/// crash.
bool jsonInvalidDataTest()
{
    const char* const documents[] = {
        "",
        "{",
        "not json",
        "[]",
        "{\"VTrackerParams\": 5}",
        "{\"VTrackerParams\": []}",
        "{\"VTrackerParams\": {\"rectWidth\": \"text\"}}",
        "{\"VTrackerParams\": {\"rectWidth\": 1e999}}",
        "{\"VTrackerParams\": {\"rectWidth\": 99999999999999999999}}",
        "{\"VTrackerParams\": {\"rectAutoSize\": 7}}",
        "{\"VTrackerParams\": {\"custom1\": null}}",
        "{\"Other\": {}}"};
    int parsed = 0;
    int accepted = 0;
    for (const char* document : documents)
    {
        // The results depend on the document, the calls must be safe.
        cr::utils::ConfigReader config;
        cr::vtracker::VTrackerParams params;
        if (config.readFromString(document))
        {
            ++parsed;
            if (config.get(params, "VTrackerParams"))
            {
                ++accepted;
            }
        }
    }
    std::cout << "Invalid JSON documents: " << parsed << " parsed, "
              << accepted << " read as params" << std::endl;

    // A document with missing fields must be rejected and the params must not
    // be changed.
    cr::utils::ConfigReader config;
    if (!config.readFromString(
                "{\"VTrackerParams\": {\"rectWidth\": 33, \"rectHeight\": 44}}"))
    {
        return fail("Can't read valid JSON string");
    }
    cr::vtracker::VTrackerParams sentinel;
    randomize(sentinel);
    cr::vtracker::VTrackerParams params = sentinel;
    if (config.get(params, "VTrackerParams"))
    {
        return fail("Document with missing fields accepted");
    }
    if (!compareJsonFields(sentinel, params))
    {
        return fail("Params changed after rejected document");
    }

    // Round trip through JSON string.
    cr::utils::ConfigReader inConfig;
    std::string json;
    if (!inConfig.set(sentinel, "VTrackerParams") ||
        !inConfig.writeToString(json))
    {
        return fail("Can't write JSON string");
    }
    cr::utils::ConfigReader outConfig;
    cr::vtracker::VTrackerParams out;
    if (!outConfig.readFromString(json) ||
        !outConfig.get(out, "VTrackerParams"))
    {
        return fail("Can't read JSON string");
    }

    return compareJsonFields(sentinel, out);
}



/// Run one test and print the result.
bool runTest(const char* title, bool (*test)())
{
    std::cout << title << ":" << std::endl;
    const bool passed = test();
    std::cout << (passed ? "OK" : "ERROR") << std::endl << std::endl;
    return passed;
}
}



// Entry point.
int main()
{
    std::cout << "#####################################" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "# VTracker test                     #" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "#####################################" << std::endl;
    std::cout << std::endl;

    bool allPassed = true;
    allPassed = runTest("Copy test", copyTest) && allPassed;
    allPassed = runTest("Encode/Decode test", encodeDecodeTest) && allPassed;
    allPassed = runTest("Encode/Decode test with params mask",
                        encodeDecodeWithMaskTest) && allPassed;
    allPassed = runTest("Encode params arguments test",
                        encodeArgumentsTest) && allPassed;
    allPassed = runTest("Decode params invalid data test",
                        decodeInvalidDataTest) && allPassed;
    allPassed = runTest("Damaged params data test",
                        corruptionTest) && allPassed;
    allPassed = runTest("Encode/Decode commands test",
                        encodeDecodeCommandsTest) && allPassed;
    allPassed = runTest("Decode commands invalid data test",
                        decodeCommandInvalidDataTest) && allPassed;
    allPassed = runTest("Version test", versionTest) && allPassed;
    allPassed = runTest("JSON read/write test", jsonReadWriteTest) && allPassed;
    allPassed = runTest("JSON invalid data test",
                        jsonInvalidDataTest) && allPassed;

    std::cout << (allPassed ? "ALL TESTS PASSED" : "SOME TESTS FAILED")
              << std::endl;

    return allPassed ? 0 : 1;
}
