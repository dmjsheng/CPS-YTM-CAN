/*
 * Copyright 2020-2025 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file vector.S
 * @brief 
 * 
 */


    .section .isr_vector, "a"
    .align 2
    .thumb
    .long   STACK_end                                      /* Top of Stack */
    .long   Reset_Handler                                                /* Reset Handler */
    .long   NMI_Handler
    .long   HardFault_Handler
    .long   DefaultISR
    .long   DefaultISR
    .long   DefaultISR
    .long   DefaultISR
    .long   DefaultISR
    .long   DefaultISR
    .long   DefaultISR
    .long   SVC_Handler
    .long   DefaultISR
    .long   DefaultISR
    .long   PendSV_Handler
    .long   SysTick_Handler
    .long   DMA0_IRQHandler
    .long   DMA1_IRQHandler
    .long   DMA2_IRQHandler
    .long   DMA3_IRQHandler
    .long   DMA_Error_IRQHandler
    .long   EMU0_IRQHandler
    .long   RTC_IRQHandler
    .long   SPI2_IRQHandler
    .long   lpTMR0_IRQHandler
    .long   GPIO_IRQHandler
    .long   CAN0_ORed_Err_Wakeup_IRQHandler
    .long   CAN0_ORed_0_15_MB_IRQHandler
    .long   eTMR0_CH_0_7_IRQHandler
    .long   eTMR0_Fault_IRQHandler
    .long   eTMR0_Ovf_IRQHandler
    .long   eTMR1_IRQHandler
    .long   eTMR2_IRQHandler
    .long   CAN0_ORed_16_31_MB_IRQHandler
    .long   EFM_IRQHandler
    .long   DefaultISR
    .long   pTMR0_IRQHandler
    .long   PCU_CMU_IRQHandler
    .long   WDG0_IRQHandler
    .long   UART2_IRQHandler
    .long   I2C0_IRQHandler
    .long   I2C1_IRQHandler
    .long   SPI0_IRQHandler
    .long   SPI1_IRQHandler
    .long   ADC0_IRQHandler
    .long   ACMP0_IRQHandler
    .long   UART1_IRQHandler
    .long   UART0_IRQHandler
