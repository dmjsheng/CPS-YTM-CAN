#include "pro_os.h"
#include "QuarkTS.h"
#include "gpio_drv.h"
#include "uart_drv.h"
#include "oled_drv.h"
#include "can_drv.h"
#include "lamp_app.h"
#include <stdio.h>

void SystickConfig(void);
void IdleTask_Callback(qEvent_t e);

/* 5ms 周期任务: 按键扫描与车内灯光开关/拨杆模拟 */
qTask_t OS_5ms_task;
void OS_5ms_Task_Callback(qEvent_t e);

/* 20ms 周期任务: CAN 报文处理、优先级仲裁、闪烁控制与 100ms 反馈上报 */
qTask_t OS_20ms_task;
void OS_20ms_Task_Callback(qEvent_t e);

/* 500ms 周期任务: 系统运行监控日志 */
qTask_t OS_500ms_task;
void OS_500ms_Task_Callback(qEvent_t e);

void Init_OS(void)
{
    /* 1. 外设硬件底层初始化 */
    Init_GPIO();
    Init_UART();
    Init_OLED();
    Init_CAN();

    /* 2. 车载灯光应用层初始化 */
    Lamp_App_Init();

    /* 3. QuarkTS 内核时基 1ms */
    qOS_Setup(NULL, 0.001f, IdleTask_Callback);

    /* 4. 添加时间片调度任务 */
    qOS_Add_Task(&OS_5ms_task, OS_5ms_Task_Callback, qHigh_Priority,
                 0.005f, qPeriodic, qEnabled, NULL);

    qOS_Add_Task(&OS_20ms_task, OS_20ms_Task_Callback, qMedium_Priority,
                 0.020f, qPeriodic, qEnabled, NULL);

    qOS_Add_Task(&OS_500ms_task, OS_500ms_Task_Callback, qLowest_Priority,
                 0.500f, qPeriodic, qEnabled, NULL);

    /* 5. 启动 SysTick 1ms 中断 */
    SystickConfig();

    /* 6. 开启 OS 事件调度 */
    qOS_Run();
}

void SystickConfig(void)
{
    SysTick_Config(48000000UL / 1000U);
}

void IdleTask_Callback(qEvent_t e)
{
    (void)e;
}

/* 5ms 任务: 按键消抖扫描与事件分发 */
void OS_5ms_Task_Callback(qEvent_t e)
{
    (void)e;
    key_event_t key = KEY_Scan_5ms();

    if (key != KEY_EVENT_NONE)
    {
        Lamp_App_Key_Handler(key);
    }
}

/* 20ms 任务: 核心控制与总线调度 */
void OS_20ms_Task_Callback(qEvent_t e)
{
    (void)e;
    can_frame_t rx_msg;

    /* 1. 提取所有总线接收报文，送入灯光应用层解包 */
    while (CAN_Get_Rx_Msg(&rx_msg))
    {
        Lamp_App_Process_Rx(rx_msg.id, rx_msg.data, rx_msg.dlc);
    }

    /* 2. 执行 20ms 优先级仲裁、输出状态刷新与 OLED 更新 */
    Lamp_App_20ms_Task();

    /* 3. 5 个 20ms 周期执行一次 100ms DBC 状态反馈上报 */
    static uint8_t s_div_100ms = 0u;
    s_div_100ms++;
    if (s_div_100ms >= 5u)
    {
        s_div_100ms = 0u;
        Lamp_App_100ms_Task();
    }
}

/* 500ms 任务: 系统监控日志输出 */
void OS_500ms_Task_Callback(qEvent_t e)
{
    (void)e;
    /* 保持 PC5 / PC6 专用于车灯控制，不在此处随意翻转 */
}
