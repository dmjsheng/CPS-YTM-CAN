/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file i2c_irq.c
 * @version 1.4.1
 *
 * @brief I2C interrupt handler implementations.
 *
 * Provides the platform-specific ISR entry points for I2C peripherals.
 * Each handler delegates to the driver-level IRQ handler in i2c_driver.c.
 */

#include "device_registers.h"
#include "i2c_driver.h"
#include "i2c_irq.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined (YTM32B1L_SERIES)
/*! @brief I2C0 combined master/slave interrupt handler. */
void I2C0_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(0);
}
/*! @brief I2C1 combined master/slave interrupt handler. */
void I2C1_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(1);
}

#elif defined(YTM32B1M_SERIES)
#if (I2C_INSTANCE_COUNT > 0u)

/*! @brief I2C0 master interrupt handler. */
void I2C0_Master_IRQHandler(void) 
{
    I2C_DRV_MasterIRQHandler(0);
}

/*! @brief I2C0 slave interrupt handler. */
void I2C0_Slave_IRQHandler(void)
{
    I2C_DRV_SlaveIRQHandler(0);
}

#if(I2C_INSTANCE_COUNT > 1u)

/*! @brief I2C1 master interrupt handler. */
void I2C1_Master_IRQHandler(void)
{
    I2C_DRV_MasterIRQHandler(1);
}

/*! @brief I2C1 slave interrupt handler. */
void I2C1_Slave_IRQHandler(void)
{
    I2C_DRV_SlaveIRQHandler(1);
}

#endif

#if(I2C_INSTANCE_COUNT > 2u)

/*! @brief I2C2 master interrupt handler. */
void I2C2_Master_IRQHandler(void)
{
    I2C_DRV_MasterIRQHandler(2);
}

/*! @brief I2C2 slave interrupt handler. */
void I2C2_Slave_IRQHandler(void)
{
    I2C_DRV_SlaveIRQHandler(2);
}

#endif

#endif

#elif defined(YTM32B1H_SERIES)
#if (I2C_INSTANCE_COUNT > 0u)

/*! @brief I2C0 combined master/slave interrupt handler. */
void I2C0_Master_Slave_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(0);
}


#if(I2C_INSTANCE_COUNT > 1u)

/*! @brief I2C1 combined master/slave interrupt handler. */
void I2C1_Master_Slave_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(1);
}

#endif

#if(I2C_INSTANCE_COUNT > 2u)

/*! @brief I2C2 combined master/slave interrupt handler. */
void I2C2_Master_Slave_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(2);
}

#endif
#if(I2C_INSTANCE_COUNT > 3u)

/*! @brief I2C3 combined master/slave interrupt handler. */
void I2C3_Master_Slave_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(3);
}

#endif
#if(I2C_INSTANCE_COUNT > 4u)

/*! @brief I2C4 combined master/slave interrupt handler. */
void I2C4_Master_Slave_IRQHandler(void)
{
    I2C_DRV_ModuleIRQHandler(4);
}

#endif

#endif
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/
