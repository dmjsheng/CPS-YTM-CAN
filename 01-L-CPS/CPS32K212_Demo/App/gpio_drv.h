#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include "cps32k21x_gpio.h"
#include "cps32k21x_rcc.h"
#include "baselib_types.h"

/* ========== 底层 GPIO 宏 ========== */
static inline uint8_t GET(GPIO_TypeDef *const port, uint16_t pin)
{
    return (uint8_t)GPIO_ReadInputDataBit(port, pin);
}

static inline uint8_t GET_PINOUT(GPIO_TypeDef *const port, uint16_t pin)
{
    return (uint8_t)GPIO_ReadOutputDataBit(port, pin);
}

#define HIGH(port, pin) GPIO_SetBits(port, pin)
#define LOW(port, pin)  GPIO_ResetBits(port, pin)

/* ========== 车灯与 LED 状态指示 (低电平点亮) ========== */
/* PC5 - 左位置灯 / 示宽灯 (兼作运行指示) */
#define LAMP_LEFT_POS_ON()        LOW(GPIOC, GPIO_Pin_5)
#define LAMP_LEFT_POS_OFF()       HIGH(GPIOC, GPIO_Pin_5)
#define LAMP_LEFT_POS_TOGGLE()    GPIO_ToggleBits(GPIOC, GPIO_Pin_5)
#define LAMP_LEFT_POS_STATE()     (GET_PINOUT(GPIOC, GPIO_Pin_5) == 0u)

/* PC6 - 左转向灯 (兼作通信指示) */
#define LAMP_LEFT_TURN_ON()       LOW(GPIOC, GPIO_Pin_6)
#define LAMP_LEFT_TURN_OFF()      HIGH(GPIOC, GPIO_Pin_6)
#define LAMP_LEFT_TURN_TOGGLE()   GPIO_ToggleBits(GPIOC, GPIO_Pin_6)
#define LAMP_LEFT_TURN_STATE()    (GET_PINOUT(GPIOC, GPIO_Pin_6) == 0u)

/* 兼容旧别名 */
#define LED_RUN_ON()              LAMP_LEFT_POS_ON()
#define LED_RUN_OFF()             LAMP_LEFT_POS_OFF()
#define LED_RUN_TOGGLE()          LAMP_LEFT_POS_TOGGLE()
#define LED_CAN_ON()              LAMP_LEFT_TURN_ON()
#define LED_CAN_OFF()             LAMP_LEFT_TURN_OFF()
#define LED_CAN_TOGGLE()          LAMP_LEFT_TURN_TOGGLE()

/* ========== CAN 收发器使能控制 ========== */
/* PA7 - CAN0_STDBY 控制 (低电平为正常工作模式，高电平为待机) */
#define CAN_PHY_ENABLE()   LOW(GPIOA, GPIO_Pin_7)
#define CAN_PHY_DISABLE()  HIGH(GPIOA, GPIO_Pin_7)

/* ========== 板载按键输入 (低电平有效) ========== */
/* PC14 - SW2 (KEY1), PC15 - SW3 (KEY2) */
#define KEY1_READ_PIN()    GET(GPIOC, GPIO_Pin_14)
#define KEY2_READ_PIN()    GET(GPIOC, GPIO_Pin_15)

typedef enum
{
    KEY_EVENT_NONE = 0u,
    KEY1_CLICK     = 1u,
    KEY2_CLICK     = 2u
} key_event_t;

void Init_GPIO(void);
key_event_t KEY_Scan_5ms(void);

#endif /* GPIO_DRV_H */
