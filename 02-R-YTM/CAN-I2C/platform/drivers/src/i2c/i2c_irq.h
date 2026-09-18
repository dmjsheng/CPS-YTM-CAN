/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file i2c_irq.h
 * @version 1.4.1
 *
 * @brief I2C interrupt handler declarations.
 *
 * Declares the platform-specific I2C IRQ entry points that are referenced
 * by the startup vector table. Each handler delegates to
 * I2C_DRV_MasterIRQHandler(), I2C_DRV_SlaveIRQHandler(), or
 * I2C_DRV_ModuleIRQHandler() as appropriate.
 */

#ifndef I2C_IRQ_H__
#define I2C_IRQ_H__

#include "device_registers.h"

/*******************************************************************************
 * Declarations
 ******************************************************************************/

#if defined (YTM32B1L_SERIES)

/*! @brief I2C0 combined master/slave interrupt handler. */
void I2C0_IRQHandler(void);

/*! @brief I2C1 combined master/slave interrupt handler. */
void I2C1_IRQHandler(void);

#elif defined(YTM32B1M_SERIES)

#if (I2C_INSTANCE_COUNT > 0u)

/*! @brief I2C0 master interrupt handler. */
void I2C0_Master_IRQHandler(void);

/*! @brief I2C0 slave interrupt handler. */
void I2C0_Slave_IRQHandler(void);

#if(I2C_INSTANCE_COUNT > 1u)

/*! @brief I2C1 master interrupt handler. */
void I2C1_Master_IRQHandler(void);

/*! @brief I2C1 slave interrupt handler. */
void I2C1_Slave_IRQHandler(void);

#if(I2C_INSTANCE_COUNT > 2u)

/*! @brief I2C2 master interrupt handler. */
void I2C2_Master_IRQHandler(void);

/*! @brief I2C2 slave interrupt handler. */
void I2C2_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT == 3u */

#endif /* I2C_INSTANCE_COUNT == 2u */

#endif /* I2C_INSTANCE_COUNT > 0u */

#elif defined(YTM32B1H_SERIES)

#if (I2C_INSTANCE_COUNT > 0u)

/*! @brief I2C0 combined master/slave interrupt handler. */
void I2C0_Master_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT > 0u */

#if (I2C_INSTANCE_COUNT > 1u)

/*! @brief I2C1 combined master/slave interrupt handler. */
void I2C1_Master_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT > 1u */

#if (I2C_INSTANCE_COUNT > 2u)

/*! @brief I2C2 combined master/slave interrupt handler. */
void I2C2_Master_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT > 2u */

#if (I2C_INSTANCE_COUNT > 3u)

/*! @brief I2C3 combined master/slave interrupt handler. */
void I2C3_Master_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT > 3u */

#if (I2C_INSTANCE_COUNT > 4u)

/*! @brief I2C4 combined master/slave interrupt handler. */
void I2C4_Master_Slave_IRQHandler(void);

#endif /* I2C_INSTANCE_COUNT > 4u */

#endif

#endif /* I2C_IRQ_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

