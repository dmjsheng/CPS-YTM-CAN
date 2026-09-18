#include "wdg_drv.h"

void WDG_DRV_Init(uint32_t timeout_ms)
{
    RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_IWDG_CKEN, ENABLE);
    RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_DEBUG_CKEN, ENABLE);

    DEBUG_IWDG_Cmd(DEBUG, DISABLE);
    IWDG_Mode_Config(IWDG, IWDG_MODE_RESET);

    /*
     * LIRC 实测约 38.4 kHz (周期约 26.04 us)
     * reloadValue = timeout_ms * 38.4
     * 例: 500ms -> 500 * 38.4 ≈ 19200 (在此取 16384 ~ 19200)
     */
    uint32_t reload = (uint32_t)(timeout_ms * 38400u / 1000u);
    if (reload > 0xFFFFFUL)
    {
        reload = 0xFFFFFUL;
    }

    IWDG_SetReload(IWDG, reload);
    IWDG_Cmd(IWDG, ENABLE);
    IWDG_Refresh_Cmd(IWDG, ENABLE);
}

void WDG_DRV_Trigger(void)
{
    IWDG_Refresh_Cmd(IWDG, ENABLE);
}
