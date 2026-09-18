#ifndef LAMP_APP_H
#define LAMP_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio_drv.h"

/* ========== 车载 CAN DBC 报文 ID ========== */
#define CAN_ID_BCM_LAMP_CMD       (0x100u)  /* BCM 下发灯光控制指令 */
#define CAN_ID_LEFT_LAMP_STATUS   (0x201u)  /* CPS32K 左车灯节点状态反馈 */
#define CAN_ID_RIGHT_LAMP_STATUS  (0x202u)  /* 云途 YTM32 右车灯节点状态反馈 */

/* 转向灯指令枚举 (DBC TurnLight_Cmd) */
typedef enum
{
    TURN_CMD_OFF             = 0u,  /* 关闭 */
    TURN_CMD_LEFT            = 1u,  /* 左转向灯 */
    TURN_CMD_RIGHT           = 2u,  /* 右转向灯 (右车灯响应) */
    TURN_CMD_HAZARD          = 3u   /* 双闪危险警报灯 (左右车灯同步响应) */
} turn_cmd_t;

/* 位置灯指令枚举 (DBC PosLight_Cmd) */
typedef enum
{
    POS_CMD_OFF              = 0u,  /* 关闭 */
    POS_CMD_ON               = 1u   /* 开启 */
} pos_cmd_t;

/* 当前主导生效灯具枚举 (优先级仲裁结果) */
typedef enum
{
    ACTIVE_LAMP_NONE         = 0u,  /* 全灭 */
    ACTIVE_LAMP_POS          = 1u,  /* 位置灯主导 (常亮) */
    ACTIVE_LAMP_TURN         = 2u   /* 转向灯优先接管 (闪烁，位置灯让位熄灭) */
} active_lamp_t;

/* 车灯控制与状态管理结构体 */
typedef struct
{
    /* 来自 BCM / 本地按键的控制命令 */
    turn_cmd_t      turn_cmd;
    pos_cmd_t       pos_cmd;

    /* 仲裁与实际输出物理状态 */
    active_lamp_t   active_lamp;
    uint8_t         turn_lamp_phy_state;  /* 0: 灭, 1: 亮 */
    uint8_t         pos_lamp_phy_state;   /* 0: 灭, 1: 亮 */

    /* 闪烁定时器 (20ms 基准时钟) */
    uint16_t        blink_timer_20ms;
    uint8_t         blink_phase;          /* 0: 灭周期, 1: 亮周期 */

    /* 总线统计与计数 */
    uint8_t         rolling_counter;
    uint32_t        tx_status_count;
    uint32_t        rx_bcm_count;

    /* 标志位 */
    bool            need_refresh_oled;
} lamp_mgr_t;

void Lamp_App_Init(void);
void Lamp_App_Key_Handler(key_event_t key);
void Lamp_App_Process_Rx(uint32_t id, const uint8_t *data, uint8_t dlc);
void Lamp_App_20ms_Task(void);
void Lamp_App_100ms_Task(void);
void Lamp_App_Update_OLED(void);

#endif /* LAMP_APP_H */
