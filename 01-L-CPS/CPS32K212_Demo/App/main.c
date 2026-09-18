#include "main.h"
#include "pro_os.h"
#include "cps32k21x_rcc.h"

static void Board_Init(void);

int main(void)
{
    /* 1. 板级时钟初始化 */
    Board_Init();

    /* 2. 启动系统任务调度 */
    Init_OS();

    /* 3. 调度循环不会退出 */
    while (1)
    {
        ;
    }
}

static void Board_Init(void)
{
    ErrorStatus status = ERROR;

    /* 系统时钟切换: 优先选用板载外部 8MHz 高精度晶振 (HXT) 倍频到 48MHz (CAN通信必须高精度时钟) */
    status = RCC_SysClk_SwitchTo_PLL(RCC, PLL_INPUT_SOURCE_HXT, SET_PLL_FREQ_48MHz);
    if (status != SUCCESS)
    {
        /* 若外部晶振未起振，降级使用内部 16MHz HIRC 倍频 */
        status = RCC_SysClk_SwitchTo_PLL(RCC, PLL_INPUT_SOURCE_HIRC, SET_PLL_FREQ_48MHz);
        while (status != SUCCESS)
        {
            status = RCC_SysClk_SwitchTo_PLL(RCC, PLL_INPUT_SOURCE_HIRC, SET_PLL_FREQ_48MHz);
        }
    }
}
