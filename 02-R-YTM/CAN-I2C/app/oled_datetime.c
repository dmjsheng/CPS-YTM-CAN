#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "oled_datetime.h"

static bool OLED_IsDigit(char character)
{
    return (character >= '0') && (character <= '9');
}

static bool OLED_MatchesMonth(const char *buildDate,
                              char first,
                              char second,
                              char third)
{
    return (buildDate[0] == first) &&
           (buildDate[1] == second) &&
           (buildDate[2] == third);
}

static uint8_t OLED_ParseMonth(const char *buildDate)
{
    static const char *const monthNames[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    for (uint8_t month = 0U; month < 12U; month++)
    {
        if (OLED_MatchesMonth(buildDate,
                              monthNames[month][0],
                              monthNames[month][1],
                              monthNames[month][2]))
        {
            return (uint8_t)(month + 1U);
        }
    }

    return 0U;
}

bool OLED_FormatBuildDateTime(const char *buildDate,
                              const char *buildTime,
                              char *dateText,
                              size_t dateTextCapacity,
                              char *timeText,
                              size_t timeTextCapacity)
{
    uint8_t month;
    uint8_t day;
    uint16_t year;

    if ((buildDate == NULL) || (buildTime == NULL) ||
        (dateText == NULL) || (timeText == NULL) ||
        (dateTextCapacity < 11U) || (timeTextCapacity < 9U))
    {
        return false;
    }

    month = OLED_ParseMonth(buildDate);
    if ((month == 0U) || (buildDate[3] != ' ') ||
        (buildDate[6] != ' ') ||
        (!OLED_IsDigit(buildDate[7])) ||
        (!OLED_IsDigit(buildDate[8])) ||
        (!OLED_IsDigit(buildDate[9])) ||
        (!OLED_IsDigit(buildDate[10])))
    {
        return false;
    }

    if (buildDate[4] == ' ')
    {
        if (!OLED_IsDigit(buildDate[5]))
        {
            return false;
        }
        day = (uint8_t)(buildDate[5] - '0');
    }
    else
    {
        if (!OLED_IsDigit(buildDate[4]) || !OLED_IsDigit(buildDate[5]))
        {
            return false;
        }
        day = (uint8_t)(((buildDate[4] - '0') * 10) +
                        (buildDate[5] - '0'));
    }

    year = (uint16_t)(((buildDate[7] - '0') * 1000U) +
                      ((buildDate[8] - '0') * 100U) +
                      ((buildDate[9] - '0') * 10U) +
                      (buildDate[10] - '0'));

    if ((day == 0U) || (day > 31U) ||
        (!OLED_IsDigit(buildTime[0])) ||
        (!OLED_IsDigit(buildTime[1])) ||
        (buildTime[2] != ':') ||
        (!OLED_IsDigit(buildTime[3])) ||
        (!OLED_IsDigit(buildTime[4])) ||
        (buildTime[5] != ':') ||
        (!OLED_IsDigit(buildTime[6])) ||
        (!OLED_IsDigit(buildTime[7])) ||
        (buildTime[8] != '\0'))
    {
        return false;
    }

    dateText[0] = (char)('0' + ((year / 1000U) % 10U));
    dateText[1] = (char)('0' + ((year / 100U) % 10U));
    dateText[2] = (char)('0' + ((year / 10U) % 10U));
    dateText[3] = (char)('0' + (year % 10U));
    dateText[4] = '-';
    dateText[5] = (char)('0' + (month / 10U));
    dateText[6] = (char)('0' + (month % 10U));
    dateText[7] = '-';
    dateText[8] = (char)('0' + (day / 10U));
    dateText[9] = (char)('0' + (day % 10U));
    dateText[10] = '\0';

    for (size_t index = 0U; index < 9U; index++)
    {
        timeText[index] = buildTime[index];
    }

    return true;
}


