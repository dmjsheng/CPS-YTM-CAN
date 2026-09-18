#include <stddef.h>
#include <stdint.h>

#include "i2c_driver.h"
#include "oled.h"
#include "oled_datetime.h"
#include "oled_protocol.h"
#include "osif.h"

#define OLED_I2C_INSTANCE       (1U)
#define OLED_I2C_TIMEOUT_MS     (100U)
#define OLED_WIDTH              (128U)
#define OLED_PAGE_COUNT         (8U)

/* Standard 5x7 ASCII Font Table (0x20 to 0x7E, 95 characters) */
static const uint8_t OLED_ASCII_5x7[95U][5U] = {
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* 0x20 ' ' */
    {0x00U, 0x00U, 0x5FU, 0x00U, 0x00U}, /* 0x21 '!' */
    {0x00U, 0x07U, 0x00U, 0x07U, 0x00U}, /* 0x22 '"' */
    {0x14U, 0x7FU, 0x14U, 0x7FU, 0x14U}, /* 0x23 '#' */
    {0x24U, 0x2AU, 0x7FU, 0x2AU, 0x12U}, /* 0x24 '$' */
    {0x23U, 0x13U, 0x08U, 0x64U, 0x62U}, /* 0x25 '%' */
    {0x36U, 0x49U, 0x55U, 0x22U, 0x50U}, /* 0x26 '&' */
    {0x00U, 0x05U, 0x03U, 0x00U, 0x00U}, /* 0x27 ''' */
    {0x00U, 0x1CU, 0x22U, 0x41U, 0x00U}, /* 0x28 '(' */
    {0x00U, 0x41U, 0x22U, 0x1CU, 0x00U}, /* 0x29 ')' */
    {0x14U, 0x08U, 0x3EU, 0x08U, 0x14U}, /* 0x2A '*' */
    {0x08U, 0x08U, 0x3EU, 0x08U, 0x08U}, /* 0x2B '+' */
    {0x00U, 0x50U, 0x30U, 0x00U, 0x00U}, /* 0x2C ',' */
    {0x08U, 0x08U, 0x08U, 0x08U, 0x08U}, /* 0x2D '-' */
    {0x00U, 0x60U, 0x60U, 0x00U, 0x00U}, /* 0x2E '.' */
    {0x20U, 0x10U, 0x08U, 0x04U, 0x02U}, /* 0x2F '/' */
    {0x3EU, 0x51U, 0x49U, 0x45U, 0x3EU}, /* 0x30 '0' */
    {0x00U, 0x42U, 0x7FU, 0x40U, 0x00U}, /* 0x31 '1' */
    {0x42U, 0x61U, 0x51U, 0x49U, 0x46U}, /* 0x32 '2' */
    {0x21U, 0x41U, 0x45U, 0x4BU, 0x31U}, /* 0x33 '3' */
    {0x18U, 0x14U, 0x12U, 0x7FU, 0x10U}, /* 0x34 '4' */
    {0x27U, 0x45U, 0x45U, 0x45U, 0x39U}, /* 0x35 '5' */
    {0x3CU, 0x4AU, 0x49U, 0x49U, 0x30U}, /* 0x36 '6' */
    {0x01U, 0x71U, 0x09U, 0x05U, 0x03U}, /* 0x37 '7' */
    {0x36U, 0x49U, 0x49U, 0x49U, 0x36U}, /* 0x38 '8' */
    {0x06U, 0x49U, 0x49U, 0x29U, 0x1EU}, /* 0x39 '9' */
    {0x00U, 0x36U, 0x36U, 0x00U, 0x00U}, /* 0x3A ':' */
    {0x00U, 0x56U, 0x36U, 0x00U, 0x00U}, /* 0x3B ';' */
    {0x08U, 0x14U, 0x22U, 0x41U, 0x80U}, /* 0x3C '<' */
    {0x14U, 0x14U, 0x14U, 0x14U, 0x14U}, /* 0x3D '=' */
    {0x80U, 0x41U, 0x22U, 0x14U, 0x08U}, /* 0x3E '>' */
    {0x02U, 0x01U, 0x51U, 0x09U, 0x06U}, /* 0x3F '?' */
    {0x32U, 0x49U, 0x79U, 0x41U, 0x3EU}, /* 0x40 '@' */
    {0x7EU, 0x11U, 0x11U, 0x11U, 0x7EU}, /* 0x41 'A' */
    {0x7FU, 0x49U, 0x49U, 0x49U, 0x36U}, /* 0x42 'B' */
    {0x3EU, 0x41U, 0x41U, 0x41U, 0x22U}, /* 0x43 'C' */
    {0x7FU, 0x41U, 0x41U, 0x22U, 0x1CU}, /* 0x44 'D' */
    {0x7FU, 0x49U, 0x49U, 0x49U, 0x41U}, /* 0x45 'E' */
    {0x7FU, 0x09U, 0x09U, 0x09U, 0x01U}, /* 0x46 'F' */
    {0x3EU, 0x41U, 0x49U, 0x49U, 0x7AU}, /* 0x47 'G' */
    {0x7FU, 0x08U, 0x08U, 0x08U, 0x7FU}, /* 0x48 'H' */
    {0x00U, 0x41U, 0x7FU, 0x41U, 0x00U}, /* 0x49 'I' */
    {0x20U, 0x40U, 0x41U, 0x3FU, 0x01U}, /* 0x4A 'J' */
    {0x7FU, 0x08U, 0x14U, 0x22U, 0x41U}, /* 0x4B 'K' */
    {0x7FU, 0x40U, 0x40U, 0x40U, 0x40U}, /* 0x4C 'L' */
    {0x7FU, 0x02U, 0x0CU, 0x02U, 0x7FU}, /* 0x4D 'M' */
    {0x7FU, 0x04U, 0x08U, 0x10U, 0x7FU}, /* 0x4E 'N' */
    {0x3EU, 0x41U, 0x41U, 0x41U, 0x3EU}, /* 0x4F 'O' */
    {0x7FU, 0x09U, 0x09U, 0x09U, 0x06U}, /* 0x50 'P' */
    {0x3EU, 0x41U, 0x51U, 0x21U, 0x5EU}, /* 0x51 'Q' */
    {0x7FU, 0x09U, 0x19U, 0x29U, 0x46U}, /* 0x52 'R' */
    {0x46U, 0x49U, 0x49U, 0x49U, 0x31U}, /* 0x53 'S' */
    {0x01U, 0x01U, 0x7FU, 0x01U, 0x01U}, /* 0x54 'T' */
    {0x3FU, 0x40U, 0x40U, 0x40U, 0x3FU}, /* 0x55 'U' */
    {0x1FU, 0x20U, 0x40U, 0x20U, 0x1FU}, /* 0x56 'V' */
    {0x3FU, 0x40U, 0x38U, 0x40U, 0x3FU}, /* 0x57 'W' */
    {0x63U, 0x14U, 0x08U, 0x14U, 0x63U}, /* 0x58 'X' */
    {0x07U, 0x08U, 0x70U, 0x08U, 0x07U}, /* 0x59 'Y' */
    {0x61U, 0x51U, 0x49U, 0x45U, 0x43U}, /* 0x5A 'Z' */
    {0x00U, 0x7FU, 0x41U, 0x41U, 0x00U}, /* 0x5B '[' */
    {0x02U, 0x04U, 0x08U, 0x10U, 0x20U}, /* 0x5C '\' */
    {0x00U, 0x41U, 0x41U, 0x7FU, 0x00U}, /* 0x5D ']' */
    {0x04U, 0x02U, 0x01U, 0x02U, 0x04U}, /* 0x5E '^' */
    {0x40U, 0x40U, 0x40U, 0x40U, 0x40U}, /* 0x5F '_' */
    {0x00U, 0x01U, 0x02U, 0x04U, 0x00U}, /* 0x60 '`' */
    {0x20U, 0x54U, 0x54U, 0x54U, 0x78U}, /* 0x61 'a' */
    {0x7FU, 0x48U, 0x44U, 0x44U, 0x38U}, /* 0x62 'b' */
    {0x38U, 0x44U, 0x44U, 0x44U, 0x20U}, /* 0x63 'c' */
    {0x38U, 0x44U, 0x44U, 0x48U, 0x7FU}, /* 0x64 'd' */
    {0x38U, 0x54U, 0x54U, 0x54U, 0x18U}, /* 0x65 'e' */
    {0x08U, 0x7EU, 0x09U, 0x01U, 0x02U}, /* 0x66 'f' */
    {0x0CU, 0x52U, 0x52U, 0x52U, 0x3EU}, /* 0x67 'g' */
    {0x7FU, 0x08U, 0x04U, 0x04U, 0x78U}, /* 0x68 'h' */
    {0x00U, 0x44U, 0x7DU, 0x40U, 0x00U}, /* 0x69 'i' */
    {0x20U, 0x40U, 0x44U, 0x3DU, 0x00U}, /* 0x6A 'j' */
    {0x7FU, 0x10U, 0x28U, 0x44U, 0x00U}, /* 0x6B 'k' */
    {0x00U, 0x41U, 0x7FU, 0x40U, 0x00U}, /* 0x6C 'l' */
    {0x7CU, 0x04U, 0x18U, 0x04U, 0x78U}, /* 0x6D 'm' */
    {0x7CU, 0x08U, 0x04U, 0x04U, 0x78U}, /* 0x6E 'n' */
    {0x38U, 0x44U, 0x44U, 0x44U, 0x38U}, /* 0x6F 'o' */
    {0x7CU, 0x14U, 0x14U, 0x14U, 0x08U}, /* 0x70 'p' */
    {0x08U, 0x14U, 0x14U, 0x18U, 0x7CU}, /* 0x71 'q' */
    {0x7CU, 0x08U, 0x04U, 0x04U, 0x08U}, /* 0x72 'r' */
    {0x48U, 0x54U, 0x54U, 0x54U, 0x20U}, /* 0x73 's' */
    {0x04U, 0x3FU, 0x44U, 0x40U, 0x20U}, /* 0x74 't' */
    {0x3CU, 0x40U, 0x40U, 0x20U, 0x7CU}, /* 0x75 'u' */
    {0x1CU, 0x20U, 0x40U, 0x20U, 0x1CU}, /* 0x76 'v' */
    {0x3CU, 0x40U, 0x30U, 0x40U, 0x3CU}, /* 0x77 'w' */
    {0x44U, 0x28U, 0x10U, 0x28U, 0x44U}, /* 0x78 'x' */
    {0x0CU, 0x50U, 0x50U, 0x50U, 0x3CU}, /* 0x79 'y' */
    {0x44U, 0x64U, 0x54U, 0x4CU, 0x44U}, /* 0x7A 'z' */
    {0x00U, 0x08U, 0x36U, 0x41U, 0x00U}, /* 0x7B '{' */
    {0x00U, 0x00U, 0x7FU, 0x00U, 0x00U}, /* 0x7C '|' */
    {0x00U, 0x41U, 0x36U, 0x08U, 0x00U}, /* 0x7D '}' */
    {0x10U, 0x08U, 0x08U, 0x10U, 0x08U}  /* 0x7E '~' */
};

static status_t OLED_SendCommand(uint8_t command)
{
    uint8_t packet[2U];
    size_t packetLength;

    packetLength = OLED_BuildCommandPacket(packet, sizeof(packet), command);
    if (packetLength == 0U)
    {
        return STATUS_ERROR;
    }

    return I2C_DRV_MasterSendDataBlocking(OLED_I2C_INSTANCE,
                                          packet,
                                          (uint32_t)packetLength,
                                          true,
                                          OLED_I2C_TIMEOUT_MS);
}

static status_t OLED_SendData(const uint8_t *data, size_t dataLength)
{
    uint8_t packet[OLED_WIDTH + 1U];
    size_t packetLength;

    packetLength = OLED_BuildDataPacket(packet,
                                        sizeof(packet),
                                        data,
                                        dataLength);
    if (packetLength == 0U)
    {
        return STATUS_ERROR;
    }

    return I2C_DRV_MasterSendDataBlocking(OLED_I2C_INSTANCE,
                                          packet,
                                          (uint32_t)packetLength,
                                          true,
                                          OLED_I2C_TIMEOUT_MS);
}

static status_t OLED_SelectPage(uint8_t page)
{
    status_t status;

    status = OLED_SendCommand((uint8_t)(0xB0U | page));
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    status = OLED_SendCommand(0x00U);
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    return OLED_SendCommand(0x10U);
}

static void OLED_GetGlyph(char character, uint8_t glyph[5U])
{
    if ((character >= ' ') && (character <= '~'))
    {
        for (size_t index = 0U; index < 5U; index++)
        {
            glyph[index] = OLED_ASCII_5x7[(uint8_t)character - 0x20U][index];
        }
    }
    else
    {
        for (size_t index = 0U; index < 5U; index++)
        {
            glyph[index] = 0U;
        }
    }
}

status_t OLED_ShowTextAtPage(uint8_t page, const char *text)
{
    uint8_t data[OLED_WIDTH] = {0U};
    uint8_t glyph[5U];
    size_t dataLength = 0U;

    if (text != NULL)
    {
        for (size_t textIndex = 0U;
             (text[textIndex] != '\0') && ((dataLength + 6U) <= OLED_WIDTH);
             textIndex++)
        {
            OLED_GetGlyph(text[textIndex], glyph);
            for (size_t glyphIndex = 0U; glyphIndex < 5U; glyphIndex++)
            {
                data[dataLength++] = glyph[glyphIndex];
            }
            data[dataLength++] = 0U; /* 1-column inter-character spacing */
        }
    }

    if (OLED_SelectPage(page) != STATUS_SUCCESS)
    {
        return STATUS_ERROR;
    }

    /* Send entire 128-byte row to overwrite and clear any old residues */
    return OLED_SendData(data, OLED_WIDTH);
}

status_t OLED_Init(void)
{
    static const uint8_t initCommands[] = {
        0xAEU, /* Display OFF */
        0xD5U, 0x80U, /* Display clock divide ratio */
        0xA8U, 0x3FU, /* Multiplex ratio: 1/64 */
        0xD3U, 0x00U, /* Display offset */
        0x40U, /* Display start line */
        0x8DU, 0x14U, /* Charge pump ON */
        0x20U, 0x00U, /* Page addressing mode */
        0xA1U, /* Segment remap */
        0xC8U, /* COM scan direction remapped */
        0xDAU, 0x12U, /* COM pins for 128x64 */
        0x81U, 0x7FU, /* Contrast */
        0xD9U, 0xF1U, /* Pre-charge */
        0xDBU, 0x40U, /* VCOMH deselect level */
        0xA4U, /* Resume RAM display */
        0xA6U, /* Normal display */
        0xAFU  /* Display ON */
    };
    status_t status;

    OSIF_TimeDelay(100U);

    for (size_t index = 0U; index < sizeof(initCommands); index++)
    {
        status = OLED_SendCommand(initCommands[index]);
        if (status != STATUS_SUCCESS)
        {
            return status;
        }
    }

    return STATUS_SUCCESS;
}

status_t OLED_Clear(void)
{
    uint8_t zeroData[OLED_WIDTH] = {0U};
    status_t status;

    for (uint8_t page = 0U; page < OLED_PAGE_COUNT; page++)
    {
        status = OLED_SelectPage(page);
        if (status != STATUS_SUCCESS)
        {
            return status;
        }

        status = OLED_SendData(zeroData, sizeof(zeroData));
        if (status != STATUS_SUCCESS)
        {
            return status;
        }
    }

    return STATUS_SUCCESS;
}

status_t OLED_ShowTestPattern(void)
{
    uint8_t patternData[OLED_WIDTH];
    status_t status;

    for (size_t index = 0U; index < sizeof(patternData); index++)
    {
        patternData[index] = 0xAAU;
    }

    for (uint8_t page = 0U; page < OLED_PAGE_COUNT; page++)
    {
        status = OLED_SelectPage(page);
        if (status != STATUS_SUCCESS)
        {
            return status;
        }

        status = OLED_SendData(patternData, sizeof(patternData));
        if (status != STATUS_SUCCESS)
        {
            return status;
        }
    }

    return STATUS_SUCCESS;
}

status_t OLED_ShowFrame(const uint8_t *frame)
{
    if (frame == NULL)
    {
        return STATUS_ERROR;
    }

    for (uint8_t page = 0U; page < OLED_PAGE_COUNT; page++)
    {
        if (OLED_SelectPage(page) != STATUS_SUCCESS)
        {
            return STATUS_ERROR;
        }

        if (OLED_SendData(&frame[(size_t)page * OLED_WIDTH], OLED_WIDTH) != STATUS_SUCCESS)
        {
            return STATUS_ERROR;
        }
    }

    return STATUS_SUCCESS;
}

status_t OLED_ShowBuildDateTime(void)
{
    char dateText[11U];
    char timeText[9U];
    status_t status;

    if (!OLED_FormatBuildDateTime(__DATE__,
                                  __TIME__,
                                  dateText,
                                  sizeof(dateText),
                                  timeText,
                                  sizeof(timeText)))
    {
        return STATUS_ERROR;
    }

    status = OLED_Clear();
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    status = OLED_ShowTextAtPage(1U, dateText);
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    return OLED_ShowTextAtPage(3U, timeText);
}

static void OLED_FormatCounterText(char prefix,
                                   uint32_t counter,
                                   char text[7U])
{
    text[0] = prefix;
    text[1] = ':';
    text[2] = (char)('0' + ((counter / 1000U) % 10U));
    text[3] = (char)('0' + ((counter / 100U) % 10U));
    text[4] = (char)('0' + ((counter / 10U) % 10U));
    text[5] = (char)('0' + (counter % 10U));
    text[6] = '\0';
}

status_t OLED_ShowCanCounters(uint32_t tx_count, uint32_t rx_count)
{
    char txText[7U];
    char rxText[7U];
    status_t status;

    OLED_FormatCounterText('1', tx_count, txText);
    OLED_FormatCounterText('2', rx_count, rxText);

    status = OLED_ShowTextAtPage(1U, txText);
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    return OLED_ShowTextAtPage(3U, rxText);
}
