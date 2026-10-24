#include "VTracker.h"
#include "VTrackerVersion.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>



namespace
{
// Encoded data stores int and float fields as raw 4 bytes values.
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(float) == 4, "float must be 4 bytes");
// Library version is stored in the encoded data as two bytes.
static_assert(VTRACKER_MAJOR_VERSION >= 0 &&
              VTRACKER_MAJOR_VERSION <= std::numeric_limits<uint8_t>::max(),
              "major version must fit in one byte");
static_assert(VTRACKER_MINOR_VERSION >= 0 &&
              VTRACKER_MINOR_VERSION <= std::numeric_limits<uint8_t>::max(),
              "minor version must fit in one byte");

/// Number of bits in a byte.
constexpr int BITS_IN_BYTE{8};
/// Size of an int or float field in the encoded data, bytes.
constexpr int VALUE_SIZE{4};
/// Size of a bool field in the encoded data, bytes.
constexpr int FLAG_SIZE{1};
/// Number of bool fields of VTrackerParams.
constexpr int FLAGS_NUMBER{3};
/// Number of int and float fields of VTrackerParams.
constexpr int VALUES_NUMBER{31};
/// Total number of fields of VTrackerParams (and of flags in the mask).
constexpr int FIELDS_NUMBER{FLAGS_NUMBER + VALUES_NUMBER};

/// Data type byte of encoded params.
constexpr uint8_t PARAMS_DATA_TYPE{0x02};
/// Position of the fields mask in the encoded params: after the data type
/// byte and two version bytes.
constexpr int PARAMS_MASK_POS{3};
/// Size of the fields mask, bytes (one bit per field, first field is the most
/// significant bit of the first byte).
constexpr int PARAMS_MASK_SIZE{5};
/// Size of the encoded params header: data type, version and mask.
constexpr int PARAMS_HEADER_SIZE{PARAMS_MASK_POS + PARAMS_MASK_SIZE};
/// Maximum size of the encoded params (all fields encoded).
constexpr int PARAMS_MAX_SIZE{PARAMS_HEADER_SIZE + VALUES_NUMBER * VALUE_SIZE +
                              FLAGS_NUMBER * FLAG_SIZE};
static_assert(PARAMS_MAX_SIZE == 135, "wrong size of encoded params");
static_assert(FIELDS_NUMBER <= PARAMS_MASK_SIZE * BITS_IN_BYTE,
              "mask is too small");

/// Data type byte of an encoded command.
constexpr uint8_t COMMAND_DATA_TYPE{0x00};
/// Data type byte of an encoded set param command.
constexpr uint8_t SET_PARAM_DATA_TYPE{0x01};
/// Size of an encoded command, bytes: header (3), ID (4), three arguments.
constexpr int COMMAND_SIZE{19};
/// Size of an encoded set param command, bytes: header (3), ID (4), value (4).
constexpr int SET_PARAM_COMMAND_SIZE{11};
/// Position of the command ID in an encoded command and in an encoded set
/// param command: after the data type byte and two version bytes.
constexpr int COMMAND_ID_POS{3};
/// Position of the first command argument (or of the param value in a set
/// param command) and of the next two arguments.
constexpr int COMMAND_ARG1_POS{COMMAND_ID_POS + VALUE_SIZE};
constexpr int COMMAND_ARG2_POS{COMMAND_ARG1_POS + VALUE_SIZE};
constexpr int COMMAND_ARG3_POS{COMMAND_ARG2_POS + VALUE_SIZE};
static_assert(COMMAND_ARG3_POS + VALUE_SIZE == COMMAND_SIZE,
              "wrong size of encoded command");
static_assert(COMMAND_ARG1_POS + VALUE_SIZE == SET_PARAM_COMMAND_SIZE,
              "wrong size of encoded set param command");
/// Value of a mask byte with all bits set and of the most significant bit.
constexpr uint8_t FULL_MASK_BYTE{0xFF};
constexpr int FIRST_MASK_BIT{0x80};



/// Location of a VTrackerParams field in the encoded data.
struct FieldRef
{
    /// Pointer to the field of a VTrackerParams object.
    void* value{nullptr};
    /// Size of the field in the encoded data: VALUE_SIZE or FLAG_SIZE.
    int size{0};
};



/// Get the table of VTrackerParams fields in the order they are stored in the
/// encoded data (the same order as the bits of the mask).
std::array<FieldRef, FIELDS_NUMBER> makeFieldTable(
        rapidpixel::VTrackerParams& p)
{
    return {{
        {&p.mode, VALUE_SIZE},
        {&p.rectX, VALUE_SIZE},
        {&p.rectY, VALUE_SIZE},
        {&p.rectWidth, VALUE_SIZE},
        {&p.rectHeight, VALUE_SIZE},
        {&p.objectX, VALUE_SIZE},
        {&p.objectY, VALUE_SIZE},
        {&p.objectWidth, VALUE_SIZE},
        {&p.objectHeight, VALUE_SIZE},
        {&p.lostModeFrameCounter, VALUE_SIZE},
        {&p.frameCounter, VALUE_SIZE},
        {&p.frameWidth, VALUE_SIZE},
        {&p.frameHeight, VALUE_SIZE},
        {&p.searchWindowWidth, VALUE_SIZE},
        {&p.searchWindowHeight, VALUE_SIZE},
        {&p.searchWindowX, VALUE_SIZE},
        {&p.searchWindowY, VALUE_SIZE},
        {&p.lostModeOption, VALUE_SIZE},
        {&p.frameBufferSize, VALUE_SIZE},
        {&p.maxFramesInLostMode, VALUE_SIZE},
        {&p.processedFrameId, VALUE_SIZE},
        {&p.frameId, VALUE_SIZE},
        {&p.velX, VALUE_SIZE},
        {&p.velY, VALUE_SIZE},
        {&p.detectionProbability, VALUE_SIZE},
        {&p.rectAutoSize, FLAG_SIZE},
        {&p.rectAutoPosition, FLAG_SIZE},
        {&p.multipleThreads, FLAG_SIZE},
        {&p.numChannels, VALUE_SIZE},
        {&p.type, VALUE_SIZE},
        {&p.processingTimeMks, VALUE_SIZE},
        {&p.custom1, VALUE_SIZE},
        {&p.custom2, VALUE_SIZE},
        {&p.custom3, VALUE_SIZE}
    }};
}



/// Get the table of mask flags in the same order as makeFieldTable(...).
std::array<const bool*, FIELDS_NUMBER> makeFlagTable(
        const rapidpixel::VTrackerParamsMask& m)
{
    return {{
        &m.mode,
        &m.rectX,
        &m.rectY,
        &m.rectWidth,
        &m.rectHeight,
        &m.objectX,
        &m.objectY,
        &m.objectWidth,
        &m.objectHeight,
        &m.lostModeFrameCounter,
        &m.frameCounter,
        &m.frameWidth,
        &m.frameHeight,
        &m.searchWindowWidth,
        &m.searchWindowHeight,
        &m.searchWindowX,
        &m.searchWindowY,
        &m.lostModeOption,
        &m.frameBufferSize,
        &m.maxFramesInLostMode,
        &m.processedFrameId,
        &m.frameId,
        &m.velX,
        &m.velY,
        &m.detectionProbability,
        &m.rectAutoSize,
        &m.rectAutoPosition,
        &m.multipleThreads,
        &m.numChannels,
        &m.type,
        &m.processingTimeMks,
        &m.custom1,
        &m.custom2,
        &m.custom3
    }};
}



/// Get the byte of the mask and the bit inside the byte for a field index.
/// The first field is the most significant bit of the first byte.
constexpr int maskByteIndex(int fieldIndex)
{
    return fieldIndex / BITS_IN_BYTE;
}



constexpr int maskBit(int fieldIndex)
{
    return FIRST_MASK_BIT >> (fieldIndex % BITS_IN_BYTE);
}
}



rapidpixel::VTracker::~VTracker()
{

}



std::string rapidpixel::VTracker::getVersion()
{
    return VTRACKER_VERSION;
}



bool rapidpixel::VTrackerParams::encode(
        uint8_t* data, int bufferSize,
        int& size, rapidpixel::VTrackerParamsMask* mask)
{
    // Check the buffer: it must be able to hold all fields, so the output
    // never depends on the mask and cannot overflow the buffer.
    size = 0;
    if (data == nullptr || bufferSize < PARAMS_MAX_SIZE)
    {
        return false;
    }

    // Encode data type and version.
    data[0] = PARAMS_DATA_TYPE;
    data[1] = static_cast<uint8_t>(VTRACKER_MAJOR_VERSION);
    data[2] = static_cast<uint8_t>(VTRACKER_MINOR_VERSION);

    // Prepare mask. Without the mask all bits (including unused) are set.
    const rapidpixel::VTrackerParamsMask allFields;
    const auto flags = makeFlagTable(mask != nullptr ? *mask : allFields);
    for (int i = 0; i < PARAMS_MASK_SIZE; ++i)
    {
        data[PARAMS_MASK_POS + i] =
                mask == nullptr ? FULL_MASK_BYTE : uint8_t{0x00};
    }
    if (mask != nullptr)
    {
        for (int i = 0; i < FIELDS_NUMBER; ++i)
        {
            if (*flags[static_cast<size_t>(i)])
            {
                uint8_t& maskByte = data[PARAMS_MASK_POS + maskByteIndex(i)];
                maskByte = static_cast<uint8_t>(maskByte | maskBit(i));
            }
        }
    }

    // Encode fields selected by the mask.
    const auto fields = makeFieldTable(*this);
    int pos = PARAMS_HEADER_SIZE;
    for (size_t i = 0; i < fields.size(); ++i)
    {
        if (!*flags[i])
        {
            continue;
        }
        if (fields[i].size == FLAG_SIZE)
        {
            const bool flag = *static_cast<const bool*>(fields[i].value);
            data[pos] = flag ? uint8_t{0x01} : uint8_t{0x00};
        }
        else
        {
            std::memcpy(&data[pos], fields[i].value, VALUE_SIZE);
        }
        pos += fields[i].size;
    }

    size = pos;

    return true;
}



bool rapidpixel::VTrackerParams::decode(uint8_t* data, int dataSize)
{
    // Check data size (header must be complete) and header.
    if (data == nullptr || dataSize < PARAMS_HEADER_SIZE)
    {
        return false;
    }
    if (data[0] != PARAMS_DATA_TYPE)
    {
        return false;
    }
    if (data[1] != VTRACKER_MAJOR_VERSION || data[2] != VTRACKER_MINOR_VERSION)
    {
        return false;
    }

    // Decode into a temporary object: this object is changed only if the
    // whole data is valid. Fields not selected by the mask are set to zero.
    VTrackerParams result;
    const auto fields = makeFieldTable(result);
    int pos = PARAMS_HEADER_SIZE;
    for (int i = 0; i < FIELDS_NUMBER; ++i)
    {
        const FieldRef& field = fields[static_cast<size_t>(i)];
        const bool encoded =
                (data[PARAMS_MASK_POS + maskByteIndex(i)] & maskBit(i)) != 0;
        if (!encoded)
        {
            std::memset(field.value, 0, static_cast<size_t>(field.size));
            continue;
        }

        // Check that the field is inside the data (an attack on the size is
        // prevented here: the position never exceeds PARAMS_MAX_SIZE).
        if (dataSize - pos < field.size)
        {
            return false;
        }
        if (field.size == FLAG_SIZE)
        {
            *static_cast<bool*>(field.value) = data[pos] != 0x00;
        }
        else
        {
            std::memcpy(field.value, &data[pos], VALUE_SIZE);
        }
        pos += field.size;
    }

    *this = result;

    return true;
}



void rapidpixel::VTracker::encodeSetParamCommand(
        uint8_t* data, int& size, rapidpixel::VTrackerParam id, float value)
{
    // Check the buffer pointer.
    size = 0;
    if (data == nullptr)
    {
        return;
    }

    // Fill header.
    data[0] = SET_PARAM_DATA_TYPE;
    data[1] = static_cast<uint8_t>(VTRACKER_MAJOR_VERSION);
    data[2] = static_cast<uint8_t>(VTRACKER_MINOR_VERSION);

    // Fill data.
    const int paramId = static_cast<int>(id);
    std::memcpy(&data[COMMAND_ID_POS], &paramId, VALUE_SIZE);
    std::memcpy(&data[COMMAND_ARG1_POS], &value, VALUE_SIZE);
    size = SET_PARAM_COMMAND_SIZE;
}



void rapidpixel::VTracker::encodeCommand(
        uint8_t* data, int& size, VTrackerCommand id,
        float arg1, float arg2, float arg3)
{
    // Check the buffer pointer.
    size = 0;
    if (data == nullptr)
    {
        return;
    }

    // Fill header.
    data[0] = COMMAND_DATA_TYPE;
    data[1] = static_cast<uint8_t>(VTRACKER_MAJOR_VERSION);
    data[2] = static_cast<uint8_t>(VTRACKER_MINOR_VERSION);

    // Fill data.
    const int commandId = static_cast<int>(id);
    std::memcpy(&data[COMMAND_ID_POS], &commandId, VALUE_SIZE);
    std::memcpy(&data[COMMAND_ARG1_POS], &arg1, VALUE_SIZE);
    std::memcpy(&data[COMMAND_ARG2_POS], &arg2, VALUE_SIZE);
    std::memcpy(&data[COMMAND_ARG3_POS], &arg3, VALUE_SIZE);
    size = COMMAND_SIZE;
}



int rapidpixel::VTracker::decodeCommand(
                            uint8_t* data,
                            int size,
                            VTrackerParam& paramId,
                            VTrackerCommand& commandId,
                            float& value1,
                            float& value2,
                            float& value3)
{
    // Check pointer and size (the shortest command is set param command).
    if (data == nullptr || size < SET_PARAM_COMMAND_SIZE)
    {
        return -1;
    }

    // Check version.
    if (data[1] != VTRACKER_MAJOR_VERSION ||
        data[2] != VTRACKER_MINOR_VERSION)
    {
        return -1;
    }

    // Extract data.
    int id = 0;
    std::memcpy(&id, &data[COMMAND_ID_POS], VALUE_SIZE);
    value1 = 0.0f;
    value2 = 0.0f;
    value3 = 0.0f;

    // Check command type.
    if (data[0] == COMMAND_DATA_TYPE)
    {
        // Check size. A command has exactly one valid size.
        if (size != COMMAND_SIZE)
        {
            return -1;
        }

        // Check command ID: unknown IDs are not passed to the implementation.
        if (id < static_cast<int>(VTrackerCommand::CAPTURE) ||
            id > static_cast<int>(VTrackerCommand::CHANGE_RECT_SIZE))
        {
            return -1;
        }

        // Decode command ID and arguments.
        commandId = static_cast<VTrackerCommand>(id);
        std::memcpy(&value1, &data[COMMAND_ARG1_POS], VALUE_SIZE);
        std::memcpy(&value2, &data[COMMAND_ARG2_POS], VALUE_SIZE);
        std::memcpy(&value3, &data[COMMAND_ARG3_POS], VALUE_SIZE);
        return 0;
    }
    if (data[0] == SET_PARAM_DATA_TYPE)
    {
        // Check size. A set param command has exactly one valid size.
        if (size != SET_PARAM_COMMAND_SIZE)
        {
            return -1;
        }

        // Check param ID: unknown IDs are not passed to the implementation.
        if (id < static_cast<int>(VTrackerParam::SEARCH_WINDOW_WIDTH) ||
            id > static_cast<int>(VTrackerParam::CUSTOM_3))
        {
            return -1;
        }

        paramId = static_cast<VTrackerParam>(id);
        std::memcpy(&value1, &data[COMMAND_ARG1_POS], VALUE_SIZE);
        return 1;
    }

    return -1;
}
