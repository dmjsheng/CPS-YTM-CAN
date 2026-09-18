#ifndef OLED_DATETIME_H
#define OLED_DATETIME_H

#include <stdbool.h>
#include <stddef.h>

bool OLED_FormatBuildDateTime(const char *buildDate,
                              const char *buildTime,
                              char *dateText,
                              size_t dateTextCapacity,
                              char *timeText,
                              size_t timeTextCapacity);

#endif


