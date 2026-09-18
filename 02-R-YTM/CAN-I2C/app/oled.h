#ifndef OLED_H
#define OLED_H

#include "status.h"
#include <stdint.h>

status_t OLED_Init(void);
status_t OLED_Clear(void);
status_t OLED_ShowTestPattern(void);
status_t OLED_ShowBuildDateTime(void);
status_t OLED_ShowFrame(const uint8_t *frame);
status_t OLED_ShowCanCounters(uint32_t tx_count, uint32_t rx_count);
status_t OLED_ShowTextAtPage(uint8_t page, const char *text);

#endif /* OLED_H */
