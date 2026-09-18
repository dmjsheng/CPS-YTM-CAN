#ifndef WDG_DRV_H
#define WDG_DRV_H

#include "cps32k21x_iwdg.h"
#include "cps32k21x_rcc.h"
#include "cps32k21x_debug.h"
#include "baselib_types.h"

void WDG_DRV_Init(uint32_t timeout_ms);
void WDG_DRV_Trigger(void);

#endif /* WDG_DRV_H */
