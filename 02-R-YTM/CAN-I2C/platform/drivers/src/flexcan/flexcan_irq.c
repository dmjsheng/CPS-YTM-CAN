/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file flexcan_irq.c
 * @version 1.4.1
 *
 * @brief FlexCAN Interrupt Handler — per-instance vector entry points.
 *
 * This file implements the chip-level interrupt vector entry points for all
 * FlexCAN instances. Each entry point delegates to one of the generic
 * dispatch functions declared in flexcan_irq.h:
 *   - FLEXCAN_IRQHandler()        — message buffer Tx/Rx interrupts.
 *   - FLEXCAN_Error_IRQHandler()  — error and status interrupts.
 *   - FLEXCAN_ORed_IRQHandler()   — bus-off and Tx/Rx warning interrupts.
 *   - FLEXCAN_WakeUpHandler()     — Pretended Networking / Self Wake-Up.
 */

#include "flexcan_irq.h"
#if (FEATURE_CAN_HAS_SELF_WAKE_UP && FEATURE_CAN_HAS_WAKE_UP_IRQ)
#include "flexcan_hw_access.h"
#endif

#if defined (YTM32B1L_SERIES)

/*******************************************************************************
 * CAN0 Vector Entry Points — YTM32B1L
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 0U)

/*! @brief CAN0 combined error / wake-up IRQ entry point (YTM32B1L). */
void CAN0_ORed_Err_Wakeup_IRQHandler(void)
{
#if (FEATURE_CAN_HAS_SELF_WAKE_UP && FEATURE_CAN_HAS_WAKE_UP_IRQ)
    if(FLEXCAN_GetWAKINT(CAN0) != 0U)
    {
        FLEXCAN_WakeUpHandler(0U);
    }
    else
#endif
    {
        FLEXCAN_Error_IRQHandler(0U);
    }     
}

/*! @brief CAN0 MB 0–15 IRQ entry point (YTM32B1L). */
void CAN0_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0U, 0U, 15U);
}

/*! @brief CAN0 MB 16–31 IRQ entry point (YTM32B1L). */
void CAN0_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0U, 16U, 31U);
}
#endif /* (CAN_INSTANCE_COUNT > 0U) */

#elif (defined (YTM32B1M_SERIES) || defined (YTM32B1H_SERIES))

/*******************************************************************************
 * CAN0 Vector Entry Points — YTM32B1M / YTM32B1H
 ******************************************************************************/

/*! @brief CAN0 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN0_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(0);
}

/*! @brief CAN0 Error IRQ entry point. */
void CAN0_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(0);
}

/*! @brief CAN0 Wake-Up IRQ entry point. */
void CAN0_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(0);
}

/*! @brief CAN0 MB 0–15 IRQ entry point. */
void CAN0_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 0, 15);
}

/*! @brief CAN0 MB 16–31 IRQ entry point. */
void CAN0_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 16, 31);
}
#if defined(FEATURE_CAN0_MAX_MB_NUM) && (FEATURE_CAN0_MAX_MB_NUM > 32U)
/*! @brief CAN0 MB 32–47 IRQ entry point. */
void CAN0_ORed_32_47_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 32, 47);
}

/*! @brief CAN0 MB 48–63 IRQ entry point. */
void CAN0_ORed_48_63_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 48, 63);
}
#endif
#if defined(FEATURE_CAN0_MAX_MB_NUM) && (FEATURE_CAN0_MAX_MB_NUM > 64U)
/*! @brief CAN0 MB 64–79 IRQ entry point. */
void CAN0_ORed_64_79_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 64, 79);
}

/*! @brief CAN0 MB 80–95 IRQ entry point. */
void CAN0_ORed_80_95_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 80, 95);
}

/*! @brief CAN0 MB 96–111 IRQ entry point. */
void CAN0_ORed_96_111_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 96, 111);
}

/*! @brief CAN0 MB 112–127 IRQ entry point. */
void CAN0_ORed_112_127_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(0, 112, 127);
}
#endif 

/*******************************************************************************
 * CAN1 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 1U)

/*! @brief CAN1 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN1_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(1);
}

/*! @brief CAN1 Error IRQ entry point. */
void CAN1_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(1);
}

/*! @brief CAN1 Wake-Up IRQ entry point. */
void CAN1_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(1);
}

/*! @brief CAN1 MB 0–15 IRQ entry point. */
void CAN1_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 0, 15);
}

/*! @brief CAN1 MB 16–31 IRQ entry point. */
void CAN1_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 16, 31);
}
#if defined(FEATURE_CAN1_MAX_MB_NUM) && (FEATURE_CAN1_MAX_MB_NUM > 32U)
/*! @brief CAN1 MB 32–47 IRQ entry point. */
void CAN1_ORed_32_47_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 32, 47);
}

/*! @brief CAN1 MB 48–63 IRQ entry point. */
void CAN1_ORed_48_63_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 48, 63);
}
#endif
#if defined(FEATURE_CAN1_MAX_MB_NUM) && (FEATURE_CAN1_MAX_MB_NUM > 64U)
/*! @brief CAN1 MB 64–79 IRQ entry point. */
void CAN1_ORed_64_79_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 64, 79);
}

/*! @brief CAN1 MB 80–95 IRQ entry point. */
void CAN1_ORed_80_95_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 80, 95);
}

/*! @brief CAN1 MB 96–111 IRQ entry point. */
void CAN1_ORed_96_111_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 96, 111);
}

/*! @brief CAN1 MB 112–127 IRQ entry point. */
void CAN1_ORed_112_127_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(1, 112, 127);
}
#endif
#endif

/*******************************************************************************
 * CAN2 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 2U)  

/*! @brief CAN2 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN2_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(2);
}

/*! @brief CAN2 Error IRQ entry point. */
void CAN2_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(2);
}

/*! @brief CAN2 Wake-Up IRQ entry point. */
void CAN2_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(2);
}

/*! @brief CAN2 MB 0–15 IRQ entry point. */
void CAN2_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(2, 0, 15);
}

/*! @brief CAN2 MB 16–31 IRQ entry point. */
void CAN2_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(2, 16, 31);
}
#if defined(FEATURE_CAN2_MAX_MB_NUM) && (FEATURE_CAN2_MAX_MB_NUM > 32U)
/*! @brief CAN2 MB 32–47 IRQ entry point. */
void CAN2_ORed_32_47_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(2, 32, 47);
}

/*! @brief CAN2 MB 48–63 IRQ entry point. */
void CAN2_ORed_48_63_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(2, 48, 63);
}
#endif
#endif

/*******************************************************************************
 * CAN3 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 3U)  

/*! @brief CAN3 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN3_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(3);
}

/*! @brief CAN3 Error IRQ entry point. */
void CAN3_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(3);
}

/*! @brief CAN3 Wake-Up IRQ entry point. */
void CAN3_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(3);
}

/*! @brief CAN3 MB 0–15 IRQ entry point. */
void CAN3_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(3, 0, 15);
}

/*! @brief CAN3 MB 16–31 IRQ entry point. */
void CAN3_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(3, 16, 31);
}
#if defined(FEATURE_CAN3_MAX_MB_NUM) && (FEATURE_CAN3_MAX_MB_NUM > 32U)
/*! @brief CAN3 MB 32–47 IRQ entry point. */
void CAN3_ORed_32_47_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(3, 32, 47);
}

/*! @brief CAN3 MB 48–63 IRQ entry point. */
void CAN3_ORed_48_63_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(3, 48, 63);
}
#endif
#endif

/*******************************************************************************
 * CAN4 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 4U) 

/*! @brief CAN4 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN4_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(4);
}

/*! @brief CAN4 Error IRQ entry point. */
void CAN4_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(4);
}

/*! @brief CAN4 Wake-Up IRQ entry point. */
void CAN4_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(4);
}

/*! @brief CAN4 MB 0–15 IRQ entry point. */
void CAN4_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(4, 0, 15);
}

/*! @brief CAN4 MB 16–31 IRQ entry point. */
void CAN4_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(4, 16, 31);
}
#if defined(FEATURE_CAN4_MAX_MB_NUM) && (FEATURE_CAN4_MAX_MB_NUM > 32U)
/*! @brief CAN4 MB 32–47 IRQ entry point. */
void CAN4_ORed_32_47_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(4, 32, 47);
}

/*! @brief CAN4 MB 48–63 IRQ entry point. */
void CAN4_ORed_48_63_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(4, 48, 63);
}
#endif
#endif

/*******************************************************************************
 * CAN5 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 5U) 

/*! @brief CAN5 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN5_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(5);
}

/*! @brief CAN5 Error IRQ entry point. */
void CAN5_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(5);
}

/*! @brief CAN5 Wake-Up IRQ entry point. */
void CAN5_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(5);
}

/*! @brief CAN5 MB 0–15 IRQ entry point. */
void CAN5_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(5, 0, 15);
}

/*! @brief CAN5 MB 16–31 IRQ entry point. */
void CAN5_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(5, 16, 31);
}
#endif

/*******************************************************************************
 * CAN6 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 6U) 

/*! @brief CAN6 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN6_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(6);
}

/*! @brief CAN6 Error IRQ entry point. */
void CAN6_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(6);
}

/*! @brief CAN6 Wake-Up IRQ entry point. */
void CAN6_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(6);
}

/*! @brief CAN6 MB 0–15 IRQ entry point. */
void CAN6_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(6, 0, 15);
}

/*! @brief CAN6 MB 16–31 IRQ entry point. */
void CAN6_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(6, 16, 31);
}
#endif

/*******************************************************************************
 * CAN7 Vector Entry Points
 ******************************************************************************/
#if defined(CAN_INSTANCE_COUNT) && (CAN_INSTANCE_COUNT > 7U) 

/*! @brief CAN7 Bus-Off / Tx-Rx Warning IRQ entry point. */
void CAN7_ORed_IRQHandler(void)
{
    FLEXCAN_ORed_IRQHandler(7);
}

/*! @brief CAN7 Error IRQ entry point. */
void CAN7_Error_IRQHandler(void)
{
    FLEXCAN_Error_IRQHandler(7);
}

/*! @brief CAN7 Wake-Up IRQ entry point. */
void CAN7_Wake_Up_IRQHandler(void)
{
    FLEXCAN_WakeUpHandler(7);
}

/*! @brief CAN7 MB 0–15 IRQ entry point. */
void CAN7_ORed_0_15_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(7, 0, 15);
}

/*! @brief CAN7 MB 16–31 IRQ entry point. */
void CAN7_ORed_16_31_MB_IRQHandler(void)
{
    FLEXCAN_IRQHandler(7, 16, 31);
}
#endif
#else
    #error "No valid CPU defined!"
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
