#include "gpio_drv.h"

void Init_GPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 开启 GPIOA, GPIOB, GPIOC 时钟 */
    RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOA_CKEN, ENABLE);
    RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOB_CKEN, ENABLE);
    RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOC_CKEN, ENABLE);

    /* 1. LED 初始化 (PC5, PC6) */
    LED_RUN_OFF();
    LED_CAN_OFF();

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* 2. CAN PHY 待机控制管脚 (PA7: 输出低电平使能收发器) */
    CAN_PHY_ENABLE();
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 3. 板载按键配置 (PC14: SW2, PC15: SW3，配置为上拉输入) */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* 5ms 周期按键消抖扫描函数 (20ms 连续确认) */
key_event_t KEY_Scan_5ms(void)
{
    static uint8_t k1_count = 0u;
    static uint8_t k2_count = 0u;
    static uint8_t k1_pressed = 0u;
    static uint8_t k2_pressed = 0u;
    key_event_t event = KEY_EVENT_NONE;

    /* SW2 (PC14) 消抖 */
    if (KEY1_READ_PIN() == 0u)
    {
        if (k1_count < 255u) { k1_count++; }
        if ((k1_count >= 4u) && (k1_pressed == 0u)) /* 4 * 5ms = 20ms */
        {
            k1_pressed = 1u;
            event = KEY1_CLICK;
        }
    }
    else
    {
        k1_count = 0u;
        k1_pressed = 0u;
    }

    /* SW3 (PC15) 消抖 */
    if (KEY2_READ_PIN() == 0u)
    {
        if (k2_count < 255u) { k2_count++; }
        if ((k2_count >= 4u) && (k2_pressed == 0u)) /* 4 * 5ms = 20ms */
        {
            k2_pressed = 1u;
            if (event == KEY_EVENT_NONE)
            {
                event = KEY2_CLICK;
            }
        }
    }
    else
    {
        k2_count = 0u;
        k2_pressed = 0u;
    }

    return event;
}
