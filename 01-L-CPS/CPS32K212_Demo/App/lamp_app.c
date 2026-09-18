#include "lamp_app.h"
#include "can_drv.h"
#include "oled_drv.h"
#include "uart_drv.h"
#include <stdio.h>
#include <string.h>

static lamp_mgr_t s_lamp;

void Lamp_App_Init(void)
{
    memset(&s_lamp, 0, sizeof(s_lamp));
    s_lamp.turn_cmd = TURN_CMD_OFF;
    s_lamp.pos_cmd  = POS_CMD_OFF;
    s_lamp.active_lamp = ACTIVE_LAMP_NONE;
    s_lamp.need_refresh_oled = true;

    /* 默认关闭所有车灯输出 */
    LAMP_LEFT_TURN_OFF();
    LAMP_LEFT_POS_OFF();

    /* 绘制 OLED 初始框架 */
    OLED_ShowString(0, 0, "[CPS LEFT LAMP ]");
    OLED_ShowString(0, 2, "CMD: T:OFF P:OFF");
    OLED_ShowString(0, 4, "[ALL LAMPS OFF] ");
    OLED_ShowString(0, 6, "TX:0x201 C:000  ");
}

/* 本地按键模拟车内灯光开关/拨杆 */
void Lamp_App_Key_Handler(key_event_t key)
{
    if (key == KEY1_CLICK)
    {
        /* SW2: 模拟转向拨杆 (关闭 -> 左转向 -> 双闪 -> 关闭 循环) */
        if (s_lamp.turn_cmd == TURN_CMD_OFF)
        {
            s_lamp.turn_cmd = TURN_CMD_LEFT;
            printf("\r\n[DRIVER STALK] Left Turn Selected!\r\n");
        }
        else if (s_lamp.turn_cmd == TURN_CMD_LEFT)
        {
            s_lamp.turn_cmd = TURN_CMD_HAZARD;
            printf("\r\n[DRIVER STALK] Hazard Warning (Double Flash) Selected!\r\n");
        }
        else
        {
            s_lamp.turn_cmd = TURN_CMD_OFF;
            printf("\r\n[DRIVER STALK] Turn Signal Turned OFF.\r\n");
        }
        s_lamp.need_refresh_oled = true;
    }
    else if (key == KEY2_CLICK)
    {
        /* SW3: 模拟车灯旋钮 (位置灯 ON / OFF 切换) */
        if (s_lamp.pos_cmd == POS_CMD_OFF)
        {
            s_lamp.pos_cmd = POS_CMD_ON;
            printf("\r\n[DRIVER KNOB] Position Light Turned ON!\r\n");
        }
        else
        {
            s_lamp.pos_cmd = POS_CMD_OFF;
            printf("\r\n[DRIVER KNOB] Position Light Turned OFF.\r\n");
        }
        s_lamp.need_refresh_oled = true;
    }
}

/* 接收并解析 DBC 报文 (消除单帧阻塞 printf 泛滥) */
void Lamp_App_Process_Rx(uint32_t id, const uint8_t *data, uint8_t dlc)
{
    (void)dlc;

    /* 匹配 BCM 灯光控制总指令 (0x100) */
    if (id == CAN_ID_BCM_LAMP_CMD)
    {
        s_lamp.rx_bcm_count++;

        turn_cmd_t rx_turn = (turn_cmd_t)(data[0] & 0x03u);
        pos_cmd_t  rx_pos  = (pos_cmd_t)((data[0] >> 2u) & 0x01u);
        uint8_t    rolling = (data[0] >> 4u) & 0x0Fu;

        static uint8_t s_last_bcm_turn = 0xFFu;
        static uint8_t s_last_bcm_pos  = 0xFFu;

        if ((rx_turn != s_last_bcm_turn) || (rx_pos != s_last_bcm_pos))
        {
            s_last_bcm_turn = (uint8_t)rx_turn;
            s_last_bcm_pos  = (uint8_t)rx_pos;
            s_lamp.turn_cmd = rx_turn;
            s_lamp.pos_cmd  = rx_pos;
            s_lamp.need_refresh_oled = true;
            printf("[BCM NEW CMD] TurnCmd=%u, PosCmd=%u, RollCnt=%u\r\n",
                   (unsigned int)rx_turn, (unsigned int)rx_pos, (unsigned int)rolling);
        }
    }
}

/* 
 * 20ms 车灯控制与优先级仲裁任务
 * 汽车级规范: 转向灯(安全指引) 优先级高于 位置灯(基础照明)
 */
void Lamp_App_20ms_Task(void)
{
    bool is_left_turn_active = (s_lamp.turn_cmd == TURN_CMD_LEFT) || 
                              (s_lamp.turn_cmd == TURN_CMD_HAZARD);

    if (is_left_turn_active)
    {
        s_lamp.active_lamp = ACTIVE_LAMP_TURN;

        /* 位置灯让位熄灭 */
        s_lamp.pos_lamp_phy_state = 0u;
        LAMP_LEFT_POS_OFF();

        /* 500ms 闪烁时基维护 */
        s_lamp.blink_timer_20ms++;
        if (s_lamp.blink_timer_20ms >= 25u) /* 25 * 20ms = 500ms */
        {
            s_lamp.blink_timer_20ms = 0u;
            s_lamp.blink_phase = !s_lamp.blink_phase;
            s_lamp.need_refresh_oled = true;
        }

        if (s_lamp.blink_phase)
        {
            LAMP_LEFT_TURN_ON();
            s_lamp.turn_lamp_phy_state = 1u;
        }
        else
        {
            LAMP_LEFT_TURN_OFF();
            s_lamp.turn_lamp_phy_state = 0u;
        }
    }
    else
    {
        /* 转向灯未激活或为右转向 */
        s_lamp.blink_timer_20ms = 0u;
        s_lamp.blink_phase = 0u;
        s_lamp.turn_lamp_phy_state = 0u;
        LAMP_LEFT_TURN_OFF();

        /* 检查次优先级: 位置灯 */
        if (s_lamp.pos_cmd == POS_CMD_ON)
        {
            s_lamp.active_lamp = ACTIVE_LAMP_POS;
            s_lamp.pos_lamp_phy_state = 1u;
            LAMP_LEFT_POS_ON(); /* 位置灯常亮 */
        }
        else
        {
            s_lamp.active_lamp = ACTIVE_LAMP_NONE;
            s_lamp.pos_lamp_phy_state = 0u;
            LAMP_LEFT_POS_OFF(); /* 全灭 */
        }
    }

    /* 刷新 OLED 状态 */
    if (s_lamp.need_refresh_oled)
    {
        Lamp_App_Update_OLED();
        s_lamp.need_refresh_oled = false;
    }
}

/* 100ms 周期任务: 向总线反馈 LeftLamp_Status (ID: 0x201) */
void Lamp_App_100ms_Task(void)
{
    uint8_t tx_data[8] = {0};

    uint8_t turn_stat = 0u;
    if (s_lamp.active_lamp == ACTIVE_LAMP_TURN)
    {
        turn_stat = s_lamp.turn_lamp_phy_state ? 1u : 2u;
    }

    uint8_t pos_stat    = s_lamp.pos_lamp_phy_state & 0x01u;
    uint8_t active_lamp = (uint8_t)s_lamp.active_lamp & 0x03u;

    tx_data[0] = (turn_stat & 0x03u) | (pos_stat << 2u) | (active_lamp << 3u);
    tx_data[1] = (s_lamp.rolling_counter & 0x0Fu);
    s_lamp.rolling_counter = (s_lamp.rolling_counter + 1u) & 0x0Fu;

    CAN_Send_Msg(CAN_ID_LEFT_LAMP_STATUS, tx_data, 8);
    s_lamp.tx_status_count++;

    /* 每 500ms (5 次 100ms 任务) 刷新一次 OLED 底部计数器，彻底解决频繁刷新导致的 I2C 总线争用 */
    static uint8_t s_cnt_div = 0u;
    s_cnt_div++;
    if (s_cnt_div >= 5u)
    {
        s_cnt_div = 0u;
        char tx_buf[17];
        snprintf(tx_buf, sizeof(tx_buf), "TX:0x201 C:%03u  ",
                 (unsigned int)(s_lamp.tx_status_count % 1000u));
        OLED_ShowString(0, 6, tx_buf);
    }
}

/* OLED 专属车灯仪表 UI 刷新 */
void Lamp_App_Update_OLED(void)
{
    /* 第 2 行: 显示当前接收指令 */
    char cmd_buf[17];
    const char *turn_str = "OFF";
    if (s_lamp.turn_cmd == TURN_CMD_LEFT)        turn_str = "LT ";
    else if (s_lamp.turn_cmd == TURN_CMD_RIGHT)  turn_str = "RT ";
    else if (s_lamp.turn_cmd == TURN_CMD_HAZARD) turn_str = "HZ ";

    snprintf(cmd_buf, sizeof(cmd_buf), "CMD: T:%s P:%s ",
             turn_str, (s_lamp.pos_cmd == POS_CMD_ON) ? "ON " : "OFF");
    OLED_ShowString(0, 2, cmd_buf);

    /* 第 3 行: 动态显示主导生效的灯光效果 */
    if (s_lamp.active_lamp == ACTIVE_LAMP_TURN)
    {
        if (s_lamp.turn_cmd == TURN_CMD_HAZARD)
        {
            if (s_lamp.blink_phase)
            {
                OLED_ShowString(0, 4, "<<<  HAZARD  >>>");
            }
            else
            {
                OLED_ShowString(0, 4, "   [PRIO:TURN]  ");
            }
        }
        else
        {
            if (s_lamp.blink_phase)
            {
                OLED_ShowString(0, 4, "<<< LEFT TURN   ");
            }
            else
            {
                OLED_ShowString(0, 4, "   [PRIO:TURN]  ");
            }
        }
    }
    else if (s_lamp.active_lamp == ACTIVE_LAMP_POS)
    {
        OLED_ShowString(0, 4, "[ POS LIGHT ON ]");
    }
    else
    {
        OLED_ShowString(0, 4, "[ ALL LAMPS OFF]");
    }
}
