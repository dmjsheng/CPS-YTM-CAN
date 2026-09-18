#include "oled_protocol.h"

size_t OLED_BuildCommandPacket(uint8_t *packet,
                               size_t packetCapacity,
                               uint8_t command)
{
    if ((packet == NULL) || (packetCapacity < 2U))
    {
        return 0U;
    }

    packet[0] = 0x00U;
    packet[1] = command;
    return 2U;
}

size_t OLED_BuildDataPacket(uint8_t *packet,
                            size_t packetCapacity,
                            const uint8_t *data,
                            size_t dataLength)
{
    if ((packet == NULL) || (data == NULL) || (dataLength == 0U) ||
        (packetCapacity < (dataLength + 1U)))
    {
        return 0U;
    }

    packet[0] = 0x40U;
    for (size_t index = 0U; index < dataLength; index++)
    {
        packet[index + 1U] = data[index];
    }

    return dataLength + 1U;
}


