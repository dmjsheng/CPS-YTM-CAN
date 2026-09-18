#ifndef OLED_PROTOCOL_H
#define OLED_PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

size_t OLED_BuildCommandPacket(uint8_t *packet,
                               size_t packetCapacity,
                               uint8_t command);

size_t OLED_BuildDataPacket(uint8_t *packet,
                            size_t packetCapacity,
                            const uint8_t *data,
                            size_t dataLength);

#endif


