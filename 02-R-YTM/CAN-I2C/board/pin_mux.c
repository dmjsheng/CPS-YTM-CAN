/*
 * Copyright 2020-2025 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file pin_mux.c
 * @brief 
 * 
 */



#include "pin_mux.h"

/*! @brief User configuration cfg InitConfigArr0 array */
const pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] = {
    /* PTE_0-60-GPIO-SW1 */
    {
        .base = PCTRLE,
        .pinPortIdx = 0U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOE,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTC_8-36-UART1_RX-UART1_RX */
    {
        .base = PCTRLC,
        .pinPortIdx = 8U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTC_9-35-UART1_TX-UART1_TX */
    {
        .base = PCTRLC,
        .pinPortIdx = 9U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTC_6-52-CAN0_RX-CAN_RX */
    {
        .base = PCTRLC,
        .pinPortIdx = 6U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTC_7-51-CAN0_TX-CAN_TX */
    {
        .base = PCTRLC,
        .pinPortIdx = 7U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTE_6-53-GPIO-CAN_SLEEP_EN */
    {
        .base = PCTRLE,
        .pinPortIdx = 6U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOE,
        .direction = GPIO_OUTPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTD_1-1-I2C1_SCL- */
    {
        .base = PCTRLD,
        .pinPortIdx = 1U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOD,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTD_0-2-I2C1_SDA- */
    {
        .base = PCTRLD,
        .pinPortIdx = 0U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOD,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
};



/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

