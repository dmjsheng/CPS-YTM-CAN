/* USER CODE BEGIN Header */
/*
 *  Copyright 2020-2023 Yuntu Microelectronics Co., Ltd.
 *  All rights reserved.
 * 
 *  SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file main.c
 * @brief YunTu YTM32B1LE0 右车灯节点控制器 (Right Lamp ECU)
 *        - SW1 (PTE0): 模拟右转向灯拨杆 (OFF -> 右转 -> 双闪 -> OFF)
 *        - PTD7 (LED4 蓝): 右转向灯 (1Hz 闪烁)
 *        - PTD6 (LED5 绿): 右位置灯 (常亮，转向灯激活时强制避让熄灭)
 *        - OLED: 动态车灯仪表 UI 实时刷新
 *        - 周期 100ms 上报 RightLamp_Status (0x202)
 */
/* USER CODE END Header */

#include "sdk_project_config.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can_demo_logic.h"
#include "oled.h"

/* ========== 硬件引脚与外设定 ========== */
#define CAN_INST                   (0U)

/* 板载按键 SW1 (PTE0) - 模拟右转向拨杆 */
#define SW1_GPIO_BASE              (GPIOE)
#define SW1_GPIO_PIN               (0U)

/* 板载 LED: PTD7 (LED4 蓝 - 右转向灯), PTD6 (LED5 绿 - 右位置灯)，低电平点亮 */
#define RIGHT_TURN_LED_PORT        (GPIOD)
#define RIGHT_TURN_LED_PIN         (7U)
#define RIGHT_POS_LED_PORT         (GPIOD)
#define RIGHT_POS_LED_PIN          (6U)

#define RIGHT_TURN_ON()            PINS_DRV_ClearPins(RIGHT_TURN_LED_PORT, (1UL << RIGHT_TURN_LED_PIN))
#define RIGHT_TURN_OFF()           PINS_DRV_SetPins(RIGHT_TURN_LED_PORT, (1UL << RIGHT_TURN_LED_PIN))
#define RIGHT_POS_ON()             PINS_DRV_ClearPins(RIGHT_POS_LED_PORT, (1UL << RIGHT_POS_LED_PIN))
#define RIGHT_POS_OFF()            PINS_DRV_SetPins(RIGHT_POS_LED_PORT, (1UL << RIGHT_POS_LED_PIN))

/* ========== DBC 报文 ID ========== */
#define RX_BCM_MSG_ID              (0x100UL) /* BCM 灯光控制总指令 */
#define TX_RIGHT_STATUS_ID         (0x202UL) /* 右车灯状态反馈报文 */
#define RX_STD_MAILBOX             (0x00UL)
#define TX_STD_MAILBOX             (0x01UL)

#define CAN_DATA_LENGTH            (8U)
#define SAMPLE_PERIOD_MS           (5U)

/* CAN 发送与接收缓冲 */
static flexcan_msgbuff_t rxStdMsg;
static uint8_t txData[CAN_DATA_LENGTH] = {0U};

static const flexcan_data_info_t txMbStdInfo = {
    .msg_id_type = FLEXCAN_MSG_ID_STD,
    .data_length = CAN_DATA_LENGTH,
    .fd_enable = false,
    .fd_padding = 0,
    .enable_brs = false,
    .is_remote = false,
};

static const flexcan_data_info_t rxMbStdInfo = {
    .msg_id_type = FLEXCAN_MSG_ID_STD,
    .data_length = CAN_DATA_LENGTH,
    .fd_enable = false,
    .fd_padding = 0,
    .enable_brs = false,
    .is_remote = false,
};

/* 统计计数 */
static uint32_t canTxFrameCount = 0U;
static uint32_t canRxFrameCount = 0U;

/* 车灯控制与仲裁状态 */
static uint8_t  s_turn_cmd = 0U;         /* 0-OFF, 1-Left, 2-Right, 3-Hazard */
static uint8_t  s_pos_cmd  = 0U;         /* 0-OFF, 1-ON */
static uint8_t  s_active_lamp = 0U;      /* 0-NONE, 1-POS_LIGHT, 2-TURN_LIGHT */
static uint8_t  s_turn_lamp_state = 0U;  /* 0-灭, 1-亮 */
static uint8_t  s_pos_lamp_state  = 0U;  /* 0-灭, 1-亮 */
static uint8_t  s_rolling_counter = 0U;  /* 0~15 滚动活度计数 */

static uint16_t s_blink_timer_ms = 0U;
static bool     s_blink_phase    = false;
static uint16_t s_tx_timer_ms    = 0U;
static uint16_t s_oled_timer_ms  = 0U;
static bool     s_need_oled_update = true;

static void Board_Init(void);
static void Init_Lamp_GPIO(void);
static void Update_OLED_Display(void);

int main(void)
{
    status_t status = STATUS_SUCCESS;
    can_demo_button_t sw1Button;

    Board_Init();
    Init_Lamp_GPIO();

    PRINTF("\r\n========================================\r\n");
    PRINTF("  YunTu YTM32B1LE0 Right Lamp ECU Started\r\n");
    PRINTF("  Listening BCM Cmd (0x100) @ 500 kbps\r\n");
    PRINTF("  Periodic Feedback RightLamp_Status (0x202)\r\n");
    PRINTF("========================================\r\n");

    /* 1. 初始化 FlexCAN 并配置接收邮箱 (0x100) 与发送邮箱 (0x202) */
    status |= FLEXCAN_DRV_Init(CAN_INST, &flexcanInitConfig0_State, &flexcanInitConfig0);
    status |= FLEXCAN_DRV_ConfigRxMb(CAN_INST, RX_STD_MAILBOX, &rxMbStdInfo, RX_BCM_MSG_ID);
    status |= FLEXCAN_DRV_ConfigTxMb(CAN_INST, TX_STD_MAILBOX, &txMbStdInfo, TX_RIGHT_STATUS_ID);
    status |= FLEXCAN_DRV_Receive(CAN_INST, RX_STD_MAILBOX, &rxStdMsg);

    if (status != STATUS_SUCCESS)
    {
        PRINTF("[ERROR] CAN Init Failed: 0x%x\r\n", status);
        while (1) {}
    }

    /* 2. 初始化 OLED */
    if (OLED_Init() == STATUS_SUCCESS)
    {
        (void)OLED_Clear();
        Update_OLED_Display();
        s_need_oled_update = false;
    }

    /* 3. 初始化板载按键 SW1 (PTE0) */
    CanDemoButton_Init(&sw1Button, true);

    while (1)
    {
        /* ================= 1. 本地按键 SW1 (模拟右转向拨杆) ================= */
        if (CanDemoButton_Update(&sw1Button, PINS_DRV_ReadPin(SW1_GPIO_BASE, SW1_GPIO_PIN) != 0U))
        {
            if (s_turn_cmd == 0U)
            {
                s_turn_cmd = 2U; /* 开启右转向 */
                PRINTF("[SW1 CLICK] Right Turn Light Activated!\r\n");
            }
            else if (s_turn_cmd == 2U)
            {
                s_turn_cmd = 3U; /* 开启双闪警报 */
                PRINTF("[SW1 CLICK] Hazard Warning Activated!\r\n");
            }
            else
            {
                s_turn_cmd = 0U; /* 关闭 */
                PRINTF("[SW1 CLICK] Turn Signal Turned OFF.\r\n");
            }
            s_need_oled_update = true;
        }

        /* ================= 2. CAN 报文接收处理 (BCM 0x100) ================= */
        status_t rxStatus = FLEXCAN_DRV_GetTransferStatus(CAN_INST, RX_STD_MAILBOX);
        if (rxStatus != STATUS_BUSY)
        {
            if (rxStatus == STATUS_SUCCESS)
            {
                canRxFrameCount++;
                if (rxStdMsg.msgId == RX_BCM_MSG_ID)
                {
                    uint8_t rx_turn = rxStdMsg.data[0] & 0x03U;
                    uint8_t rx_pos  = (rxStdMsg.data[0] >> 2U) & 0x01U;
                    uint8_t rx_roll = (rxStdMsg.data[0] >> 4U) & 0x0FU;

                    if ((rx_turn != s_turn_cmd) || (rx_pos != s_pos_cmd))
                    {
                        PRINTF("[BCM RX (0x100)] TurnCmd=%u, PosCmd=%u, RollCnt=%u\r\n",
                               rx_turn, rx_pos, rx_roll);
                        s_turn_cmd = rx_turn;
                        s_pos_cmd  = rx_pos;
                        s_need_oled_update = true;
                    }
                }
            }
            /* 重新挂起接收 */
            (void)FLEXCAN_DRV_Receive(CAN_INST, RX_STD_MAILBOX, &rxStdMsg);
        }

        /* ================= 3. 汽车级优先级仲裁与车灯控制 ================= */
        /* 右车灯激活条件: 右转向 (2) 或 双闪警报 (3) */
        bool is_right_turn_active = (s_turn_cmd == 2U) || (s_turn_cmd == 3U);

        if (is_right_turn_active)
        {
            /* 
             * 【最高优先级: 转向灯接管】
             * 1. 位置灯让位熄灭 (Suppression)
             * 2. PTD7 (LED4 蓝) 按 1Hz (500ms 亮 / 500ms 灭) 规律闪烁
             */
            s_active_lamp = 2U; /* TURN_LIGHT */
            s_pos_lamp_state = 0U;
            RIGHT_POS_OFF();

            s_blink_timer_ms += SAMPLE_PERIOD_MS;
            if (s_blink_timer_ms >= 500U)
            {
                s_blink_timer_ms = 0U;
                s_blink_phase = !s_blink_phase;
                s_need_oled_update = true;
            }

            if (s_blink_phase)
            {
                RIGHT_TURN_ON();
                s_turn_lamp_state = 1U;
            }
            else
            {
                RIGHT_TURN_OFF();
                s_turn_lamp_state = 0U;
            }
        }
        else
        {
            s_blink_timer_ms = 0U;
            s_blink_phase = false;
            s_turn_lamp_state = 0U;
            RIGHT_TURN_OFF();

            /* 次优先级: 位置灯 */
            if (s_pos_cmd == 1U)
            {
                s_active_lamp = 1U; /* POS_LIGHT */
                s_pos_lamp_state = 1U;
                RIGHT_POS_ON(); /* PTD6 (LED5 绿) 常亮 */
            }
            else
            {
                s_active_lamp = 0U; /* NONE */
                s_pos_lamp_state = 0U;
                RIGHT_POS_OFF(); /* 全灭 */
            }
        }

        /* 定期或状态改变时刷新 OLED */
        s_oled_timer_ms += SAMPLE_PERIOD_MS;
        if (s_oled_timer_ms >= 1000U)
        {
            s_oled_timer_ms = 0U;
            s_need_oled_update = true;
        }

        if (s_need_oled_update)
        {
            Update_OLED_Display();
            s_need_oled_update = false;
        }

        /* ================= 4. 100ms 周期向总线广播 RightLamp_Status (0x202) ================= */
        s_tx_timer_ms += SAMPLE_PERIOD_MS;
        if (s_tx_timer_ms >= 100U)
        {
            s_tx_timer_ms = 0U;

            if (FLEXCAN_DRV_GetTransferStatus(CAN_INST, TX_STD_MAILBOX) != STATUS_BUSY)
            {
                uint8_t turn_stat = 0U;
                if (s_active_lamp == 2U)
                {
                    turn_stat = s_turn_lamp_state ? 1U : 2U;
                }

                txData[0] = (turn_stat & 0x03U) | ((s_pos_lamp_state & 0x01U) << 2U) | ((s_active_lamp & 0x03U) << 3U);
                txData[1] = (s_rolling_counter & 0x0FU);
                s_rolling_counter = (s_rolling_counter + 1U) & 0x0FU;

                (void)FLEXCAN_DRV_Send(CAN_INST, TX_STD_MAILBOX, &txMbStdInfo, TX_RIGHT_STATUS_ID, txData);
                canTxFrameCount++;
            }
        }

        OSIF_TimeDelay(SAMPLE_PERIOD_MS);
    }
}

static void Update_OLED_Display(void)
{
    char buf[22];

    /* Page 0: Title */
    (void)OLED_ShowTextAtPage(0U, " [YTM RIGHT LAMP] ");

    /* Page 2: Command */
    const char *tStr = "OFF";
    if (s_turn_cmd == 1U) tStr = "LEFT";
    else if (s_turn_cmd == 2U) tStr = "RIGHT";
    else if (s_turn_cmd == 3U) tStr = "HAZARD";

    const char *pStr = (s_pos_cmd == 1U) ? "ON " : "OFF";
    snprintf(buf, sizeof(buf), "CMD: T:%-6s P:%s", tStr, pStr);
    (void)OLED_ShowTextAtPage(2U, buf);

    /* Page 4: Lamp Status / Priority Effect */
    if (s_active_lamp == 2U)
    {
        if (s_turn_cmd == 3U)
        {
            (void)OLED_ShowTextAtPage(4U, s_blink_phase ? ">>> HAZARD ON  <<<" : "   [PRIO: TURN]   ");
        }
        else
        {
            (void)OLED_ShowTextAtPage(4U, s_blink_phase ? ">>> RIGHT TURN <<<" : "   [PRIO: TURN]   ");
        }
    }
    else if (s_active_lamp == 1U)
    {
        (void)OLED_ShowTextAtPage(4U, "--- POS LIGHT ON -");
    }
    else
    {
        (void)OLED_ShowTextAtPage(4U, "--- ALL LAMPS OFF-");
    }

    /* Page 6: CAN Bus Counters */
    snprintf(buf, sizeof(buf), "TX:%04u  RX:%04u",
             (unsigned int)(canTxFrameCount % 10000U),
             (unsigned int)(canRxFrameCount % 10000U));
    (void)OLED_ShowTextAtPage(6U, buf);
}

static void Init_Lamp_GPIO(void)
{
    /* PTD7 (LED4 蓝 - 右转向灯) 配置为 GPIO 输出，默认高电平熄灭 */
    PINS_DRV_SetMuxModeSel(PCTRLD, RIGHT_TURN_LED_PIN, PCTRL_MUX_AS_GPIO);
    PINS_DRV_SetPinDirection(RIGHT_TURN_LED_PORT, RIGHT_TURN_LED_PIN, GPIO_OUTPUT_DIRECTION);
    RIGHT_TURN_OFF();

    /* PTD6 (LED5 绿 - 右位置灯) 配置为 GPIO 输出，默认高电平熄灭 */
    PINS_DRV_SetMuxModeSel(PCTRLD, RIGHT_POS_LED_PIN, PCTRL_MUX_AS_GPIO);
    PINS_DRV_SetPinDirection(RIGHT_POS_LED_PORT, RIGHT_POS_LED_PIN, GPIO_OUTPUT_DIRECTION);
    RIGHT_POS_OFF();
}

static void Board_Init(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    if (STATUS_SUCCESS != CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX, CLOCK_MANAGER_POLICY_AGREEMENT))
    {
        SystemSoftwareReset();
    }
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    I2C_DRV_MasterInit(1, &I2C_MasterConfig0, &I2C_MasterConfig0_State);
    UTILITY_PRINT_Init();
}
