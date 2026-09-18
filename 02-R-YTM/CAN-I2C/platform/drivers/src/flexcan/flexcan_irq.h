/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file flexcan_irq.h
 * @version 1.4.1
 *
 * @brief FlexCAN Interrupt Handler — internal declarations.
 *
 * This header declares the low-level interrupt service routines and
 * dispatch functions for all FlexCAN instances. It is used internally
 * by the FlexCAN driver and should not be included directly by
 * application code.
 *
 * Three kinds of handlers are declared:
 *   - **MB IRQ handler** — dispatches message buffer Tx/Rx interrupts.
 *   - **Error IRQ handler** — dispatches error and status interrupts.
 *   - **Wake-Up handler** — dispatches Pretended Networking and
 *     Self Wake-Up events.
 *
 * Per-instance vector entry points (e.g. CAN0_ORed_0_15_MB_IRQHandler)
 * are also declared and route to the generic handlers above.
 */

#ifndef FLEXCAN_IRQ_H
#define FLEXCAN_IRQ_H

#include "device_registers.h"

/*******************************************************************************
 * Internal IRQ Dispatch Functions
 ******************************************************************************/

/*!
 * @brief Message buffer interrupt handler for a FlexCAN instance.
 *
 * Scans the specified range of message buffer interrupt flags and dispatches
 * to the appropriate Rx or Tx completion logic.
 *
 * @param[in] instance      FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx_start  First MB index in the scan range.
 * @param[in] mb_idx_end    Last MB index in the scan range (inclusive).
 */
void FLEXCAN_IRQHandler(uint8_t instance, uint8_t mb_idx_start, uint8_t mb_idx_end);

/*!
 * @brief Error interrupt handler for a FlexCAN instance.
 *
 * Invoked on error interrupts (bit error, overrun, FD data error, wake-up
 * interrupt). Reads ESR1, invokes the user error callback, and clears flags.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 */
void FLEXCAN_Error_IRQHandler(uint8_t instance);

/*!
 * @brief Bus-Off and Tx/Rx Warning interrupt handler for a FlexCAN instance.
 *
 * Invoked on bus-off, bus-off-done, Tx warning, and Rx warning events.
 * Reads ESR1, invokes the user error callback, and clears flags.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 */
void FLEXCAN_ORed_IRQHandler(uint8_t instance);

#if FEATURE_CAN_HAS_WAKE_UP_IRQ

/*!
 * @brief Wake-up handler for a FlexCAN instance.
 *
 * Handles Pretended Networking wake-up timeout (WTOF), wake-up match (WUMF),
 * and Self Wake-Up (WAKINT) events. Invokes the user callback after clearing
 * the corresponding flag.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 */
void FLEXCAN_WakeUpHandler(uint8_t instance);

#endif /* FEATURE_CAN_HAS_WAKE_UP_IRQ */

/*******************************************************************************
 * Per-Instance Vector Entry Points
 ******************************************************************************/

#if defined (YTM32B1L_SERIES)

/*! @brief CAN0 combined error/wake-up IRQ handler (YTM32B1L). */
void CAN0_ORed_Err_Wakeup_IRQHandler(void);
/*! @brief CAN0 MB 0–15 IRQ handler (YTM32B1L). */
void CAN0_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN0 MB 16–31 IRQ handler (YTM32B1L). */
void CAN0_ORed_16_31_MB_IRQHandler(void);

#elif (defined (YTM32B1M_SERIES) || defined (YTM32B1H_SERIES))

/*! @brief CAN0 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN0_ORed_IRQHandler(void);
/*! @brief CAN0 Error IRQ handler. */
void CAN0_Error_IRQHandler(void);
/*! @brief CAN0 Wake-Up IRQ handler. */
void CAN0_Wake_Up_IRQHandler(void);
/*! @brief CAN0 MB 0–15 IRQ handler. */
void CAN0_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN0 MB 16–31 IRQ handler. */
void CAN0_ORed_16_31_MB_IRQHandler(void);
#if defined (FEATURE_CAN0_MAX_MB_NUM)&&(FEATURE_CAN0_MAX_MB_NUM > 32U)
/*! @brief CAN0 MB 32–47 IRQ handler. */
void CAN0_ORed_32_47_MB_IRQHandler(void);
/*! @brief CAN0 MB 48–63 IRQ handler. */
void CAN0_ORed_48_63_MB_IRQHandler(void);
#endif
#if defined (FEATURE_CAN0_MAX_MB_NUM)&&(FEATURE_CAN0_MAX_MB_NUM > 64U)
/*! @brief CAN0 MB 64–79 IRQ handler. */
void CAN0_ORed_64_79_MB_IRQHandler(void);
/*! @brief CAN0 MB 80–95 IRQ handler. */
void CAN0_ORed_80_95_MB_IRQHandler(void);
/*! @brief CAN0 MB 96–111 IRQ handler. */
void CAN0_ORed_96_111_MB_IRQHandler(void);
/*! @brief CAN0 MB 112–127 IRQ handler. */
void CAN0_ORed_112_127_MB_IRQHandler(void);
#endif 
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 1U)
/*! @brief CAN1 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN1_ORed_IRQHandler(void);
/*! @brief CAN1 Error IRQ handler. */
void CAN1_Error_IRQHandler(void);
/*! @brief CAN1 Wake-Up IRQ handler. */
void CAN1_Wake_Up_IRQHandler(void);
/*! @brief CAN1 MB 0–15 IRQ handler. */
void CAN1_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN1 MB 16–31 IRQ handler. */
void CAN1_ORed_16_31_MB_IRQHandler(void);
#if defined (FEATURE_CAN1_MAX_MB_NUM)&&(FEATURE_CAN1_MAX_MB_NUM > 32U)
/*! @brief CAN1 MB 32–47 IRQ handler. */
void CAN1_ORed_32_47_MB_IRQHandler(void);
/*! @brief CAN1 MB 48–63 IRQ handler. */
void CAN1_ORed_48_63_MB_IRQHandler(void);
#endif
#if defined (FEATURE_CAN1_MAX_MB_NUM)&&(FEATURE_CAN1_MAX_MB_NUM > 64U)
/*! @brief CAN1 MB 64–79 IRQ handler. */
void CAN1_ORed_64_79_MB_IRQHandler(void);
/*! @brief CAN1 MB 80–95 IRQ handler. */
void CAN1_ORed_80_95_MB_IRQHandler(void);
/*! @brief CAN1 MB 96–111 IRQ handler. */
void CAN1_ORed_96_111_MB_IRQHandler(void);
/*! @brief CAN1 MB 112–127 IRQ handler. */
void CAN1_ORed_112_127_MB_IRQHandler(void);
#endif
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 2U)  
/*! @brief CAN2 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN2_ORed_IRQHandler(void);
/*! @brief CAN2 Error IRQ handler. */
void CAN2_Error_IRQHandler(void);
/*! @brief CAN2 Wake-Up IRQ handler. */
void CAN2_Wake_Up_IRQHandler(void);
/*! @brief CAN2 MB 0–15 IRQ handler. */
void CAN2_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN2 MB 16–31 IRQ handler. */
void CAN2_ORed_16_31_MB_IRQHandler(void);
#if defined (FEATURE_CAN2_MAX_MB_NUM)&&(FEATURE_CAN2_MAX_MB_NUM > 32U)
/*! @brief CAN2 MB 32–47 IRQ handler. */
void CAN2_ORed_32_47_MB_IRQHandler(void);
/*! @brief CAN2 MB 48–63 IRQ handler. */
void CAN2_ORed_48_63_MB_IRQHandler(void);
#endif
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 3U)  
/*! @brief CAN3 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN3_ORed_IRQHandler(void);
/*! @brief CAN3 Error IRQ handler. */
void CAN3_Error_IRQHandler(void);
/*! @brief CAN3 Wake-Up IRQ handler. */
void CAN3_Wake_Up_IRQHandler(void);
/*! @brief CAN3 MB 0–15 IRQ handler. */
void CAN3_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN3 MB 16–31 IRQ handler. */
void CAN3_ORed_16_31_MB_IRQHandler(void);
#if defined (FEATURE_CAN3_MAX_MB_NUM)&&(FEATURE_CAN3_MAX_MB_NUM > 32U)
/*! @brief CAN3 MB 32–47 IRQ handler. */
void CAN3_ORed_32_47_MB_IRQHandler(void);
/*! @brief CAN3 MB 48–63 IRQ handler. */
void CAN3_ORed_48_63_MB_IRQHandler(void);
#endif
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 4U) 
/*! @brief CAN4 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN4_ORed_IRQHandler(void);
/*! @brief CAN4 Error IRQ handler. */
void CAN4_Error_IRQHandler(void);
/*! @brief CAN4 Wake-Up IRQ handler. */
void CAN4_Wake_Up_IRQHandler(void);
/*! @brief CAN4 MB 0–15 IRQ handler. */
void CAN4_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN4 MB 16–31 IRQ handler. */
void CAN4_ORed_16_31_MB_IRQHandler(void);
#if defined (FEATURE_CAN4_MAX_MB_NUM)&&(FEATURE_CAN4_MAX_MB_NUM > 32U)
/*! @brief CAN4 MB 32–47 IRQ handler. */
void CAN4_ORed_32_47_MB_IRQHandler(void);
/*! @brief CAN4 MB 48–63 IRQ handler. */
void CAN4_ORed_48_63_MB_IRQHandler(void);
#endif
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 5U) 
/*! @brief CAN5 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN5_ORed_IRQHandler(void);
/*! @brief CAN5 Error IRQ handler. */
void CAN5_Error_IRQHandler(void);
/*! @brief CAN5 Wake-Up IRQ handler. */
void CAN5_Wake_Up_IRQHandler(void);
/*! @brief CAN5 MB 0–15 IRQ handler. */
void CAN5_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN5 MB 16–31 IRQ handler. */
void CAN5_ORed_16_31_MB_IRQHandler(void);
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 6U) 
/*! @brief CAN6 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN6_ORed_IRQHandler(void);
/*! @brief CAN6 Error IRQ handler. */
void CAN6_Error_IRQHandler(void);
/*! @brief CAN6 Wake-Up IRQ handler. */
void CAN6_Wake_Up_IRQHandler(void);
/*! @brief CAN6 MB 0–15 IRQ handler. */
void CAN6_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN6 MB 16–31 IRQ handler. */
void CAN6_ORed_16_31_MB_IRQHandler(void);
#endif
#if defined (CAN_INSTANCE_COUNT)&&(CAN_INSTANCE_COUNT > 7U) 
/*! @brief CAN7 Bus-Off / Tx-Rx Warning IRQ handler. */
void CAN7_ORed_IRQHandler(void);
/*! @brief CAN7 Error IRQ handler. */
void CAN7_Error_IRQHandler(void);
/*! @brief CAN7 Wake-Up IRQ handler. */
void CAN7_Wake_Up_IRQHandler(void);
/*! @brief CAN7 MB 0–15 IRQ handler. */
void CAN7_ORed_0_15_MB_IRQHandler(void);
/*! @brief CAN7 MB 16–31 IRQ handler. */
void CAN7_ORed_16_31_MB_IRQHandler(void);
#endif
#else
    #error "No valid CPU defined!"
#endif

#endif /* FLEXCAN_IRQ_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
