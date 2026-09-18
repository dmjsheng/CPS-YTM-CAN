/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file i2c_hw_access.h
 * @version 1.4.1
 *
 * @brief I2C Hardware Access Layer.
 *
 * This header provides low-level inline accessor functions for the I2C
 * peripheral registers. Functions are organized into the following categories:
 *
 * **Master side:**
 *   - Master Enable & FIFO Reset
 *   - Master Clock Configuration (prescaler, SCL high/low, setup/hold, Hs-mode)
 *   - Master Pin & NACK Configuration
 *   - Master FIFO Management (size, watermark, count)
 *   - Master Data I/O (command transmit, data receive)
 *   - Master Status Events (Rx ready, Tx request, errors, bus busy)
 *   - Master Status Clear
 *   - Master Interrupt Control
 *   - Master DMA Control
 *   - Master Timeout Configuration
 *
 * **Slave side:**
 *   - Slave Enable
 *   - Slave Address Configuration
 *   - Slave Status Events (bit error, STOP, repeated START, address valid, Rx/Tx)
 *   - Slave Status Clear
 *   - Slave ACK/NACK & Clock Stretching Control
 *   - Slave Data I/O
 *   - Slave Interrupt Control
 *   - Slave DMA Control
 *   - Slave High-Speed Mode Detection
 *
 * @note This is an internal layer used by the I2C Driver (i2c_driver.h/c).
 *       Application code should use the I2C_DRV_* APIs from i2c_driver.h.
 */

/*!
 * @page misra_violations MISRA-C:2012 violations list
 *
 * PRQA S 0779 Rule 5.2: dentifier does not differ from other identifier(s)
 *
 */

#ifndef I2C_HW_ACCESS_H
#define I2C_HW_ACCESS_H

#include <stdbool.h>
#include "i2c_driver.h"
#include "device_registers.h"

/*!
 * @addtogroup i2c_hw_access I2C Hardware Access
 * @ingroup i2c
 * @brief Low-level register access functions for the I2C peripheral.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name Master Interrupt Mask Definitions
 * @brief Bit masks for enabling/disabling individual master interrupt sources.
 * @{
 */
#define   I2C_MASTER_DATA_MATCH_INT             (I2C_MIE_MATIE_MASK)    /*!< Data Match Interrupt       */
#define   I2C_MASTER_PIN_LOW_TIMEOUT_INT        (I2C_MIE_TOIE_MASK)     /*!< Pin Low Timeout Interrupt  */
#define   I2C_MASTER_FIFO_ERROR_INT             (I2C_MIE_OPERRIE_MASK)  /*!< FIFO Error Interrupt       */
#define   I2C_MASTER_ARBITRATION_LOST_INT       (I2C_MIE_ARBIE_MASK)    /*!< Arbitration Lost Interrupt */
#define   I2C_MASTER_NACK_DETECT_INT            (I2C_MIE_NACKIE_MASK)   /*!< NACK Detect Interrupt      */
#define   I2C_MASTER_STOP_DETECT_INT            (I2C_MIE_STOPIE_MASK)   /*!< STOP Detect Interrupt      */
#define   I2C_MASTER_END_PACKET_INT             (I2C_MIE_EPIE_MASK)     /*!< End Packet Interrupt       */
#define   I2C_MASTER_RECEIVE_DATA_INT           (I2C_MIE_RXIE_MASK)     /*!< Receive Data Interrupt     */
#define   I2C_MASTER_TRANSMIT_DATA_INT          (I2C_MIE_TXIE_MASK)     /*!< Transmit Data Interrupt    */
/*! @} */

/*!
 * @name Slave Interrupt Mask Definitions
 * @brief Bit masks for enabling/disabling individual slave interrupt sources.
 * @{
 */
#define   I2C_SLAVE_SMBUS_ALERT_RESPONSE_INT    (I2C_SIE_ALERTIE_MASK)  /*!< SMBus Alert Response Interrupt */
#define   I2C_SLAVE_GENERAL_CALL_INT            (I2C_SIE_GCIE_MASK)     /*!< General Call Interrupt         */
#define   I2C_SLAVE_ADDRESS_MATCH_1_INT         (I2C_SIE_MAT1IE_MASK)   /*!< Address Match 1 Interrupt      */
#define   I2C_SLAVE_ADDRESS_MATCH_0_INT         (I2C_SIE_MAT0IE_MASK)   /*!< Address Match 0 Interrupt      */
#define   I2C_SLAVE_FIFO_ERROR_INT              (I2C_SIE_OPERRIE_MASK)  /*!< FIFO Error Interrupt           */
#define   I2C_SLAVE_BIT_ERROR_INT               (I2C_SIE_ARBIE_MASK)    /*!< Bit Error Interrupt            */
#define   I2C_SLAVE_STOP_DETECT_INT             (I2C_SIE_STOPIE_MASK)   /*!< STOP Detect Interrupt          */
#define   I2C_SLAVE_REPEATED_START_INT          (I2C_SIE_RSIE_MASK)     /*!< Repeated Start Interrupt       */
#define   I2C_SLAVE_TRANSMIT_ACK_INT            (I2C_SIE_ACKIE_MASK)    /*!< Transmit ACK Interrupt         */
#define   I2C_SLAVE_ADDRESS_VALID_INT           (I2C_SIE_ADDRIE_MASK)   /*!< Address Valid Interrupt        */
#define   I2C_SLAVE_RECEIVE_DATA_INT            (I2C_SIE_RXIE_MASK)     /*!< Receive Data Interrupt         */
#define   I2C_SLAVE_TRANSMIT_DATA_INT           (I2C_SIE_TXIE_MASK)     /*!< Transmit Data Interrupt        */
/*! @} */

/*! @brief Pin configuration selection.
 *
 * Selects the electrical drive mode for the I2C SDA/SCL pins.
 */
typedef enum
{
    I2C_CFG_2PIN_OPEN_DRAIN = 0U,  /*!< 2-pin open drain mode */
    I2C_CFG_2PIN_PUSH_PULL = 1U,  /*!< 2-pin push-pull mode */
    I2C_CFG_2PIN_OUTPUT_ONLY = 3U,  /*!< 2-pin output only mode (ultra-fast mode) */
} i2c_pin_config_t;

/*! @brief Master NACK reaction configuration.
 *
 * Controls how the I2C master responds to a NACK from the slave.
 */
typedef enum
{
    I2C_NACK_RECEIVE = 0U,  /*!< Receive ACK and NACK normally */
    I2C_NACK_IGNORE = 1U,  /*!< Treat a received NACK as if it was an ACK */
} i2c_nack_config_t;

/*! @brief I2C master prescaler options.
 *
 * Clock divider applied to the I2C functional clock for baud rate generation.
 */
typedef enum
{
    I2C_MASTER_PRESC_DIV_1 = 0U,  /*!< Divide by 1   */
    I2C_MASTER_PRESC_DIV_2 = 1U,  /*!< Divide by 2   */
    I2C_MASTER_PRESC_DIV_4 = 2U,  /*!< Divide by 4   */
    I2C_MASTER_PRESC_DIV_8 = 3U,  /*!< Divide by 8   */
    I2C_MASTER_PRESC_DIV_16 = 4U,  /*!< Divide by 16  */
    I2C_MASTER_PRESC_DIV_32 = 5U,  /*!< Divide by 32  */
    I2C_MASTER_PRESC_DIV_64 = 6U,  /*!< Divide by 64  */
    I2C_MASTER_PRESC_DIV_128 = 7U,  /*!< Divide by 128 */
} i2c_master_prescaler_t;

/*! @brief Slave address matching configuration.
 *
 * Selects the address match formula used by the I2C slave to validate
 * received addresses against ADDR0 and ADDR1 register values.
 */
typedef enum
{
    I2C_SLAVE_ADDR_MATCH_0_7BIT = 0U,  /*!< Address match 0 (7-bit) */
    I2C_SLAVE_ADDR_MATCH_0_10BIT = 1U,  /*!< Address match 0 (10-bit) */
    I2C_SLAVE_ADDR_MATCH_0_7BIT_OR_1_7BIT = 2U,  /*!< Address match 0 (7-bit) or Address match 1 (7-bit) */
    I2C_SLAVE_ADDR_MATCH_0_10BIT_OR_1_10BIT = 3U,  /*!< Address match 0 (10-bit) or Address match 1 (10-bit) */
    I2C_SLAVE_ADDR_MATCH_0_7BIT_OR_1_10BIT = 4U,  /*!< Address match 0 (7-bit) or Address match 1 (10-bit) */     /* PRQA S 0779 */
    I2C_SLAVE_ADDR_MATCH_0_10BIT_OR_1_7BIT = 5U,  /*!< Address match 0 (10-bit) or Address match 1 (7-bit) */     /* PRQA S 0779 */
    I2C_SLAVE_ADDR_MATCH_RANGE_7BIT = 6U,  /*!< From Address match 0 (7-bit) to Address match 1 (7-bit) */
    I2C_SLAVE_ADDR_MATCH_RANGE_10BIT = 7U,  /*!< From Address match 0 (10-bit) to Address match 1 (10-bit) */
} i2c_slave_addr_config_t;

/*! @brief Slave NACK reaction configuration.
 *
 * Controls whether the slave ends the current transfer upon detecting a NACK.
 */
typedef enum
{
    I2C_SLAVE_NACK_END_TRANSFER = 0U,  /*!< Slave will end transfer when NACK detected */
    I2C_SLAVE_NACK_CONTINUE_TRANSFER = 1U,  /*!< Slave will not end transfer when NACK detected */
} i2c_slave_nack_config_t;

/*! @brief Slave ACK/NACK transmission options.
 *
 * Instructs the slave to transmit ACK or NACK after receiving a data byte.
 */
typedef enum
{
    I2C_SLAVE_TRANSMIT_ACK = 0U,  /*!< Transmit ACK for received word  */
    I2C_SLAVE_TRANSMIT_NACK = 1U,  /*!< Transmit NACK for received word */
} i2c_slave_nack_transmit_t;

/*******************************************************************************
 * Master FIFO Management
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Master FIFO Management
 * @brief Functions for querying FIFO size, resetting FIFOs, and configuring
 *        FIFO watermarks for the I2C master.
 * @{
 */

/*!
 * @brief Get the size of the Master Receive FIFO
 * 
 * This function returns the size of the Master Receive FIFO, always a power of 2.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  Master Receive FIFO Size
 */
static inline uint16_t I2C_Get_MasterRxFIFOSize(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->RXFIFO;
    tmp = (tmp & I2C_RXFIFO_SIZE_MASK) >> I2C_RXFIFO_SIZE_SHIFT;
    tmp = 1UL << tmp;     /* RX FIFO size = 2^MRXFIFO */
    return (uint16_t) tmp;
}


/*!
 * @brief Get the size of the Master Transmit FIFO
 * 
 * This function returns the size of the Master Transmit FIFO, always a power of 2.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  Master Transmit FIFO Size
 */
static inline uint16_t I2C_Get_MasterTxFIFOSize(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->TXFIFO;
    tmp = (tmp & I2C_TXFIFO_SIZE_MASK) >> I2C_TXFIFO_SIZE_SHIFT;
    tmp = 1UL << tmp;      /* TX FIFO size = 2^MTXFIFO */
    return (uint16_t) tmp;
}


/*!
 * @brief Reset the master receive FIFO
 * 
 * This function empties the receive FIFO of the I2C master.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Reset_MasterRxFIFOCmd(I2C_Type *baseAddr)
{
    baseAddr->RXFIFO |= I2C_RXFIFO_RESET_MASK;
}


/*!
 * @brief Reset the master transmit FIFO
 * 
 * This function empties the transmit FIFO of the I2C master. 
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Reset_MasterTxFIFOCmd(I2C_Type *baseAddr)
{
    baseAddr->TXFIFO |= I2C_TXFIFO_RESET_MASK;
}

/*! @} */ /* End of Master FIFO Management */

/*******************************************************************************
 * Master Enable & Reset
 ******************************************************************************/
/*!
 * @name Master Enable & Reset
 * @brief Functions for enabling/disabling the I2C master module.
 * @{
 */

/*!
 * @brief Enable or disable the I2C master.
 *
 * If the module is enabled, the transmit FIFO is not empty and the I2C bus
 * is idle, the I2C master will immediately initiate a transfer on the bus.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] enable    true = enable master, false = disable master.
 */
static inline void I2C_Set_MasterEnable(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->MCTRL;
    regValue &= (uint32_t) (~(I2C_MCTRL_MEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_MCTRL_MEN_SHIFT;
    baseAddr->MCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Master Enable & Reset */

/*******************************************************************************
 * Master Status Events
 ******************************************************************************/
/*!
 * @name Master Status Events
 * @brief Functions for querying I2C master event flags (Rx ready, Tx request,
 *        FIFO error, arbitration lost, NACK, bus busy, line-low timeout).
 * @{
 */

/*!
 * @brief Check if receive data is available.
 *
 * Returns true when the number of words in the receive FIFO is greater
 * than the receive FIFO watermark.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @return  true if receive data is ready, false otherwise.
 */
static inline bool I2C_Get_MasterReceiveDataReadyEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    return (((regValue & I2C_MSTS_RXIF_MASK) >> I2C_MSTS_RXIF_SHIFT) != 0U);
}

/*!
 * @brief Indicate if the I2C master requests more data
 * 
 * This function returns true when the number of words in the transmit FIFO is equal 
 * or less than the transmit FIFO watermark. See function I2C_Set_MasterTxFIFOWatermark()
 * for configuring the transmit FIFO watermark.
 *
 * @param baseAddr  base address of the I2C module
 * @return  transmit data requested/not requested
 */
static inline bool I2C_Get_MasterTransmitDataRequestEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    return (((regValue & I2C_MSTS_TXIF_MASK) >> I2C_MSTS_TXIF_SHIFT) != 0U);
}

/*!
 * @brief Check the occurrence of a FIFO error event
 * 
 * This function returns true if the I2C master detects an attempt to send or 
 * receive data without first generating a (repeated) START condition. This can 
 * occur if the transmit FIFO underflows when the AUTOSTOP bit is set. When this 
 * flag is set, the I2C master will send a STOP condition (if busy) and will 
 * not initiate a new START condition until this flag has been cleared.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a FIFO error event
 */
static inline bool I2C_Get_MasterFIFOErrorEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    regValue = (regValue & I2C_MSTS_OPERRIF_MASK) >> I2C_MSTS_OPERRIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Get line low detection event.
 *
 * @param baseAddr  base address of the I2C module
 */
static inline bool I2C_Get_MasterLineLowTimeoutEvent(I2C_Type *baseAddr)
{
    return (bool) ((((baseAddr->MSTS & I2C_MSTS_TOIF_MASK) >> I2C_MSTS_TOIF_SHIFT) != 0U) ? true : false);
}

/*!
 * @brief Check the occurrence of an arbitration lost event
 * 
 * This function returns true if the I2C master detects an arbitration lost
 * condition, as defined by the I2C standard. When this flag sets, the I2C 
 * master will release the bus (go idle) and will not initiate a new START 
 * condition until this flag has been cleared.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of an arbitration lost event
 */
static inline bool I2C_Get_MasterArbitrationLostEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    regValue = (regValue & I2C_MSTS_ARBIF_MASK) >> I2C_MSTS_ARBIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the occurrence of an unexpected NACK event
 * 
 * This function returns true if the I2C master detects a NACK when 
 * transmitting an address or data. If a NACK is expected for a given address 
 * (as configured by the command word) then the flag will set if a NACK is not
 * generated. When set, the master will transmit a STOP condition and will not 
 * initiate a new START condition until this flag has been cleared.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of an unexpected NACK event
 */
static inline bool I2C_Get_MasterNACKDetectEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    regValue = (regValue & I2C_MSTS_NACKIF_MASK) >> I2C_MSTS_NACKIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the bus busy condition event
 * 
 * This function returns true if the I2C bus is busy.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a bus busy event
 */
static inline bool I2C_Get_MasterBusBusyEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = baseAddr->MSTS;
    regValue = (regValue & I2C_MSTS_BUSY_MASK) >> I2C_MSTS_BUSY_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*! @} */ /* End of Master Status Events */

/*******************************************************************************
 * Master Status Clear
 ******************************************************************************/
/*!
 * @name Master Status Clear
 * @brief Functions for clearing I2C master event flags.
 * @{
 */

/*!
 * @brief Clear the FIFO error event flag.
 *
 * This event must be cleared before the I2C master can initiate a
 * new START condition.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 */
static inline void I2C_Clear_MasterFIFOErrorEvent(I2C_Type *baseAddr)
{
    baseAddr->MSTS = ((uint32_t) 1U << I2C_MSTS_OPERRIF_SHIFT);
}

/*!
 * @brief Clear the line low event flag
 * 
 * This function clears the line low event. This event must be cleared 
 * before the I2C master can initiate a START condition.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_MasterLineLowTimeoutEvent(I2C_Type *baseAddr)
{
    baseAddr->MSTS = ((uint32_t) 1U << I2C_MSTS_TOIF_SHIFT);
}

/*!
 * @brief Clear the arbitration lost event flag
 * 
 * This function clears the arbitration lost event. This event must be cleared 
 * before the I2C master can initiate a START condition.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_MasterArbitrationLostEvent(I2C_Type *baseAddr)
{
    baseAddr->MSTS = ((uint32_t) 1U << I2C_MSTS_ARBIF_SHIFT);
}

/*!
 * @brief Clear the unexpected NACK event flag
 * 
 * This function clears the unexpected NACK event. This event must be cleared 
 * before the I2C master can initiate a START condition.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_MasterNACKDetectEvent(I2C_Type *baseAddr)
{
    baseAddr->MSTS = ((uint32_t) 1U << I2C_MSTS_NACKIF_SHIFT);
}

/*! @} */ /* End of Master Status Clear */

/*******************************************************************************
 * Master DMA Control
 ******************************************************************************/
/*!
 * @name Master DMA Control
 * @brief Functions for enabling/disabling DMA requests on master Rx/Tx paths.
 * @{
 */

/*!
 * @brief Enable or disable receive data DMA requests.
 *
 * When enabled, the I2C master generates Rx DMA requests whenever the
 * number of words in the receive FIFO exceeds the watermark.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] enable    true = enable Rx DMA, false = disable Rx DMA.
 */
static inline void I2C_Set_MasterRxDMA(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->MCTRL;
    regValue &= (uint32_t) (~(I2C_MCTRL_RXDMAEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_MCTRL_RXDMAEN_SHIFT;
    baseAddr->MCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable/disable transmit data DMA requests
 * 
 * This function enables or disables generation of Tx DMA requests when data
 * can be written to the transmit FIFO, as configured by the transmit FIFO watermark.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  specifies whether to enable or disable DMA requests
 */
static inline void I2C_Set_MasterTxDMA(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->MCTRL;
    regValue &= (uint32_t) (~(I2C_MCTRL_TXDMAEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_MCTRL_TXDMAEN_SHIFT;
    baseAddr->MCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Master DMA Control */

/*******************************************************************************
 * Master Interrupt Control
 ******************************************************************************/
/*!
 * @name Master Interrupt Control
 * @brief Functions for enabling/disabling I2C master interrupt sources.
 * @{
 */

/*!
 * @brief Enable or disable specified I2C master interrupts.
 *
 * @param[in] baseAddr    Pointer to the I2C peripheral base address.
 * @param[in] interrupts  Bitmask of interrupts (OR of I2C_MASTER_*_INT defines).
 * @param[in] enable      true = enable, false = disable.
 */
static inline void I2C_Set_MasterInt(I2C_Type *baseAddr, uint32_t interrupts, bool enable)
{
    uint32_t tmp = baseAddr->MIE;

    if (enable == true)
    {
        tmp |= interrupts;
    } else
    {
        tmp &= ~interrupts;
    }
    baseAddr->MIE = tmp;
}

/*! @} */ /* End of Master Interrupt Control */

/*******************************************************************************
 * Master Pin & NACK Configuration
 ******************************************************************************/
/*!
 * @name Master Pin & NACK Configuration
 * @brief Functions for configuring I2C pin drive mode and NACK reaction.
 * @{
 */

/*!
 * @brief Set the pin mode of the I2C module.
 *
 * Configures the electrical drive mode for the I2C SDA/SCL pins.
 *
 * @param[in] baseAddr       Pointer to the I2C peripheral base address.
 * @param[in] configuration  Desired pin mode (see #i2c_pin_config_t).
 */
static inline void I2C_Set_MasterPinConfig(I2C_Type *baseAddr, i2c_pin_config_t configuration)
{
    uint32_t tmp = baseAddr->MCTRL;
    tmp &= ~(I2C_MCTRL_PPEN_MASK | I2C_MCTRL_HSMOD_MASK);
    tmp |= ((uint32_t)configuration) << I2C_MCTRL_PPEN_SHIFT;
    baseAddr->MCTRL = tmp;
}

/*!
 * @brief Configure the reaction of the module on NACK reception
 * 
 * This function configures how the I2C master reacts when receiving a NACK. NACK responses can 
 * be treated normally or ignored. In Ultra-Fast mode it is necessary to configure the module to 
 * ignore NACK responses.
 * 
 * @param baseAddr  base address of the I2C module
 * @param configuration  set reaction of the module on NACK reception
 */
static inline void I2C_Set_MasterNACKConfig(I2C_Type *baseAddr, i2c_nack_config_t configuration)
{
    uint32_t regValue = (uint32_t) baseAddr->MCTRL;
    regValue &= (uint32_t) (~(I2C_MCTRL_IGACK_MASK));
    regValue |= I2C_MCTRL_IGACK(configuration);
    baseAddr->MCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Master Pin & NACK Configuration */

/*******************************************************************************
 * Master Clock Configuration
 ******************************************************************************/
/*!
 * @name Master Clock Configuration
 * @brief Functions for configuring prescaler, SCL high/low periods,
 *        data valid delay, and setup/hold timing.
 * @{
 */

/*!
 * @brief Set the I2C master clock prescaler.
 *
 * The prescaler divides the I2C functional clock for all master timing
 * except the digital glitch filters.
 *
 * @param[in] baseAddr   Pointer to the I2C peripheral base address.
 * @param[in] prescaler  Desired prescaler value (see #i2c_master_prescaler_t).
 */
static inline void I2C_Set_MasterPrescaler(I2C_Type *baseAddr, i2c_master_prescaler_t prescaler)
{
    uint32_t tmp = baseAddr->MFLTCFG;
    tmp &= ~(I2C_MFLTCFG_DIV_MASK);
    tmp |= I2C_MFLTCFG_DIV(prescaler);
    baseAddr->MFLTCFG = tmp;
}

/*!
 * @brief Return the I2C master prescaler
 * 
 * This function returns the currently configured clock prescaler.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  I2C master prescaler
 */
static inline i2c_master_prescaler_t I2C_Get_MasterPrescaler(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MFLTCFG;
    tmp = (tmp & I2C_MFLTCFG_DIV_MASK) >> I2C_MFLTCFG_DIV_SHIFT;
    return (i2c_master_prescaler_t) tmp;
}

/*!
 * @brief Return the configured minimum clock high period
 * 
 * This function returns the currently configured value for clock high period.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  minimum clock high period
 */
static inline uint8_t I2C_Get_MasterClockHighPeriod(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp = (tmp & I2C_MCLKCFG_HIGH_MASK) >> I2C_MCLKCFG_HIGH_SHIFT;
    return (uint8_t) tmp;
}

/*!
 * @brief Set the minimum clock high period
 * 
 * This function configures the minimum number of cycles (minus one) that the 
 * SCL clock is driven high by the master. The SCL high time is extended by the 
 * time it takes to detect a rising edge on the external SCL pin. Ignoring any 
 * additional board delay due to external loading, this is equal to 
 * (2 + FILTSCL) / 2^PRESCALE cycles.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  minimum clock high period
 */
static inline void I2C_Set_MasterClockHighPeriod(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp &= ~(I2C_MCLKCFG_HIGH_MASK);
    tmp |= I2C_MCLKCFG_HIGH(value);
    baseAddr->MCLKCFG = tmp;
}

/*!
 * @brief Set the data hold time for SDA
 * 
 * This function sets the minimum number of cycles (minus one) that is used as the 
 * data hold time for SDA. Must be configured less than the minimum SCL low period.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  value of the data hold time for SDA
 */
static inline void I2C_Set_MasterDataValidDelay(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp &= ~(I2C_MCLKCFG_VALID_MASK);
    tmp |= I2C_MCLKCFG_VALID(value);
    baseAddr->MCLKCFG = tmp;
}

/*!
 * @brief Set the setup and hold delay for a START / STOP condition
 * 
 * This function configures the Minimum number of cycles (minus one) that is used 
 * by the master as the setup and hold time for a (repeated) START condition and setup 
 * time for a STOP condition. The setup time is extended by the time it takes to detect 
 * a rising edge on the external SCL pin. Ignoring any additional board delay due to 
 * external loading, this is equal to (2 + FILTSCL) / 2^PRESCALE cycles.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  setup and hold time for a START / STOP condition
 */
static inline void I2C_Set_MasterSetupHoldDelay(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp &= ~(I2C_MCLKCFG_STHD_MASK);
    tmp |= I2C_MCLKCFG_STHD(value);
    baseAddr->MCLKCFG = tmp;
}

/*!
 * @brief Set the minimum clock low period
 * 
 * This function configures the minimum number of cycles (minus one) that the 
 * SCL clock is driven low by the master. This value is also used for the 
 * minimum bus free time between a STOP and a START condition.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  minimum clock low period
 */
static inline void I2C_Set_MasterClockLowPeriod(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp &= ~(I2C_MCLKCFG_LOW_MASK);
    tmp |= I2C_MCLKCFG_LOW(value);
    baseAddr->MCLKCFG = tmp;
}

/*!
 * @brief Return the configured minimum clock low period
 * 
 * This function returns the currently configured value for clock low period.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  minimum clock low period
 */
static inline uint8_t I2C_Get_MasterClockLowPeriod(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MCLKCFG;
    tmp = (tmp & I2C_MCLKCFG_LOW_MASK) >> I2C_MCLKCFG_LOW_SHIFT;
    return (uint8_t) tmp;
}

/*! @} */ /* End of Master Clock Configuration */

/*******************************************************************************
 * Master High-Speed Clock Configuration
 ******************************************************************************/
/*!
 * @name Master High-Speed Clock Configuration
 * @brief Functions for configuring SCL timing in High-Speed (Hs) mode.
 *
 * These settings only take effect during High-Speed mode transfers.
 * Available only when `I2C_HAS_HIGH_SPEED_MODE` is defined.
 * @{
 */

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Set the SDA data valid delay in High-Speed mode.
 *
 * Must be configured less than the minimum SCL low period.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] value     Data valid delay value (cycles minus one).
 */
static inline void I2C_Set_MasterDataValidDelayHS(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp &= ~(I2C_HSCLK_VALID_MASK);
    tmp |= I2C_HSCLK_VALID(value);
    baseAddr->HSCLK = tmp;
}

#endif

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Set the setup and hold time for a START / STOP condition in high-speed mode
 * 
 * This function configures the Minimum number of cycles (minus one) that is used 
 * by the master as the setup and hold time for a (repeated) START condition and setup 
 * time for a STOP condition. The setup time is extended by the time it takes to detect 
 * a rising edge on the external SCL pin. Ignoring any additional board delay due to 
 * external loading, this is equal to (2 + FILTSCL) / 2^PRESCALE cycles.
 * This setting only has effect during High-Speed mode transfers.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  setup and hold time for a START / STOP condition
 */
static inline void I2C_Set_MasterSetupHoldDelayHS(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp &= ~(I2C_HSCLK_STHD_MASK);
    tmp |= I2C_HSCLK_STHD(value);
    baseAddr->HSCLK = tmp;
}

#endif

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Set the minimum clock high period in high-speed mode
 * 
 * This function configures the minimum number of cycles (minus one) that the 
 * SCL clock is driven high by the master. The SCL high time is extended by the 
 * time it takes to detect a rising edge on the external SCL pin. Ignoring any 
 * additional board delay due to external loading, this is equal to 
 * (2 + FILTSCL) / 2^PRESCALE cycles.
 * This setting only has effect during High-Speed mode transfers.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  minimum clock high period
 */
static inline void I2C_Set_MasterClockHighPeriodHS(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp &= ~(I2C_HSCLK_HIGH_MASK);
    tmp |= I2C_HSCLK_HIGH(value);
    baseAddr->HSCLK = tmp;
}

#endif

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Return the configured minimum clock high period in high-speed mode
 * 
 * This function returns the currently configured value for clock high period
 * in high-speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  minimum clock high period
 */
static inline uint8_t I2C_Get_MasterClockHighPeriodHS(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp = (tmp & I2C_HSCLK_HIGH_MASK) >> I2C_HSCLK_HIGH_SHIFT;
    return (uint8_t) tmp;
}

#endif

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Set the minimum clock low period in high-speed mode
 * 
 * This function configures the minimum number of cycles (minus one) that the 
 * SCL clock is driven low by the master. This value is also used for the 
 * minimum bus free time between a STOP and a START condition.
 * This setting only has effect during High-Speed mode transfers.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  minimum clock low period
 */
static inline void I2C_Set_MasterClockLowPeriodHS(I2C_Type *baseAddr, uint8_t value)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp &= ~(I2C_HSCLK_LOW_MASK);
    tmp |= I2C_HSCLK_LOW(value);
    baseAddr->HSCLK = tmp;
}

#endif

#if(I2C_HAS_HIGH_SPEED_MODE)

/*!
 * @brief Return the configured minimum clock low period in high-speed mode
 * 
 * This function returns the currently configured value for clock low period
 * in high-speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  minimum clock low period
 */
static inline uint8_t I2C_Get_MasterClockLowPeriodHS(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->HSCLK;
    tmp = (tmp & I2C_HSCLK_LOW_MASK) >> I2C_HSCLK_LOW_SHIFT;
    return (uint8_t) tmp;
}

#endif

/*! @} */ /* End of Master High-Speed Clock Configuration */

/*******************************************************************************
 * Master FIFO Watermark & Count
 ******************************************************************************/
/*!
 * @name Master FIFO Watermark & Count
 * @brief Functions for configuring FIFO watermarks and reading FIFO counts.
 * @{
 */

/*!
 * @brief Set the receive FIFO watermark.
 *
 * When the number of words in the receive FIFO exceeds this value, a receive
 * data ready event is generated. Values >= FIFO size are truncated.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] value     Watermark threshold (0 to FIFO_SIZE - 1).
 */
static inline void I2C_Set_MasterRxFIFOWatermark(I2C_Type *baseAddr, uint16_t value)
{
    uint32_t tmp = baseAddr->RXFIFO;
    tmp &= ~(I2C_RXFIFO_WATER_MASK);
    tmp |= I2C_RXFIFO_WATER(value);
    baseAddr->RXFIFO = tmp;
}

/*!
 * @brief Return the configured receive FIFO watermark
 * 
 * This function returns the currently configured value for receive FIFO watermark
 * 
 * @param baseAddr  base address of the I2C module
 * @return  number of words in the receive FIFO that will cause the receive data flag to be set
 */
static inline uint16_t I2C_Get_MasterRxFIFOWatermark(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->RXFIFO;
    tmp = (tmp & I2C_RXFIFO_WATER_MASK) >> I2C_RXFIFO_WATER_SHIFT;
    return (uint16_t) tmp;
}

/*!
 * @brief Set the transmit FIFO watermark
 * 
 * This function configures the transmit FIFO watermark. Whenever the number of words in the transmit 
 * FIFO is greater than the transmit FIFO watermark, a transmit data request event is generated.
 * Writing a value equal or greater than the FIFO size will be truncated.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  number of words in the transmit FIFO that will cause the transmit data flag to be set
 */
static inline void I2C_Set_MasterTxFIFOWatermark(I2C_Type *baseAddr, uint16_t value)
{
    uint32_t tmp = baseAddr->TXFIFO;
    tmp &= ~(I2C_TXFIFO_WATER_MASK);
    tmp |= I2C_TXFIFO_WATER(value);
    baseAddr->TXFIFO = tmp;
}

/*!
 * @brief Return the number of words in the receive FIFO
 * 
 * This function returns the number of words currently available in the receive FIFO.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  the number of words in the receive FIFO
 */
static inline uint16_t I2C_Get_MasterRxFIFOCount(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->RXFIFO;
    tmp = (tmp & I2C_RXFIFO_COUNT_MASK) >> I2C_RXFIFO_COUNT_SHIFT;
    return (uint16_t) tmp;
}

/*!
 * @brief Return the number of words in the transmit FIFO
 * 
 * This function returns the number of words currently available in the transmit FIFO.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  the number of words in the transmit FIFO
 */
static inline uint16_t I2C_Get_MasterTxFIFOCount(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->TXFIFO;
    tmp = (tmp & I2C_TXFIFO_COUNT_MASK) >> I2C_TXFIFO_COUNT_SHIFT;
    return (uint16_t) tmp;
}

/*! @} */ /* End of Master FIFO Watermark & Count */

/*******************************************************************************
 * Master Data I/O
 ******************************************************************************/
/*!
 * @name Master Data I/O
 * @brief Functions for writing commands/data to the transmit FIFO and
 *        reading received data from the receive FIFO.
 * @{
 */

/*!
 * @brief Write a command and data byte to the master transmit FIFO.
 *
 * The command selects the I2C bus operation (transmit, receive, START, STOP)
 * and the data byte is sent on the bus.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] cmd       Master command (see #i2c_master_command_t).
 * @param[in] data      Data byte to transmit.
 */
static inline void I2C_Cmd_MasterTransmit(I2C_Type *baseAddr, i2c_master_command_t cmd, uint8_t data)
{
    baseAddr->MDATA = ((uint32_t) cmd << 8U) + (uint32_t) data;
}

/*!
 * @brief Return the received data
 * 
 * This function returns data received by the I2C master that has not been discarded 
 * due to data match settings or active command, and increments the FIFO read pointer.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  data received by the I2C master
 */
static inline uint8_t I2C_Get_MasterRxData(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->MDATA;
    tmp = (tmp & I2C_MDATA_DATA_MASK) >> I2C_MDATA_DATA_SHIFT;
    return (uint8_t) tmp;
}

/*! @} */ /* End of Master Data I/O */

/*******************************************************************************
 * Slave Enable
 ******************************************************************************/
/*!
 * @name Slave Enable
 * @brief Functions for enabling/disabling the I2C slave module.
 * @{
 */

/*!
 * @brief Enable or disable the I2C slave.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] enable    true = enable slave, false = disable slave.
 */
static inline void I2C_Set_SlaveEnable(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_SEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_SEN_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Slave Enable */

/*******************************************************************************
 * Slave Status Events
 ******************************************************************************/
/*!
 * @name Slave Status Events
 * @brief Functions for querying I2C slave event flags (bit error, STOP,
 *        repeated START, address valid, Rx/Tx data, FIFO error).
 * @{
 */

#if(I2C_HAS_ULTRA_FAST_MODE)

/*!
 * @brief Check for slave FIFO overflow or underflow.
 *
 * This event can only occur if clock stretching is disabled.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @return  true if FIFO overflow/underflow detected, false otherwise.
 */
static inline bool I2C_Get_SlaveFIFOErrorEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_OPERRIF_MASK) >> I2C_SSTS_OPERRIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

#endif

/*!
 * @brief Check the detection of a bit error
 * 
 * This function checks for the occurrence of a bit error event. This event occurs
 * if the I2C slave transmits a logic one and detects a logic zero on the I2C bus. The
 * slave will ignore the rest of the transfer until the next (repeated) START condition.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a bit error
 */
static inline bool I2C_Get_SlaveBitErrorEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_ARBIF_MASK) >> I2C_SSTS_ARBIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the detection of a STOP condition
 * 
 * This function checks for the detection of a STOP condition, after the I2C slave 
 * matched the last address byte.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a STOP condition
 */
static inline bool I2C_Get_SlaveSTOPDetectEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_STOPIF_MASK) >> I2C_SSTS_STOPIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the detection of a repeated START condition
 * 
 * This function checks for the detection of a repeated START condition, after 
 * the I2C slave matched the last address byte. This event does not occur
 * when the slave first detects a START condition.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a repeated START condition
 */
static inline bool I2C_Get_SlaveRepeatedStartEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_RSIF_MASK) >> I2C_SSTS_RSIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the validity of the Address Status Register
 * 
 * This function checks for the detection of a valid address. The event is 
 * cleared by reading the address - see function I2C_Get_SlaveReceivedAddr().
 * It can also be cleared by reading the data register, when data register has 
 * been configured to allow address reads.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of the validity of the Address Status Register
 */
static inline bool I2C_Get_SlaveAddressValidEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_ADDRIF_MASK) >> I2C_SSTS_ADDRIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check the availability of receive data
 * 
 * This function checks for the availability of data received by the I2C slave.
 * The event is cleared by reading the received data - see function 
 * I2C_Get_SlaveData(). The event is not cleared by calling
 * I2C_Get_SlaveData() if the data register is configured to allow address
 * reads and an address valid event is active.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of receive data availability
 */
static inline bool I2C_Get_SlaveReceiveDataEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_RXIF_MASK) >> I2C_SSTS_RXIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*!
 * @brief Check if transmit data is requested
 * 
 * This function checks if the I2C slave requests data to transmit. The
 * event is cleared by providing transmit data - see function 
 * I2C_Transmit_SlaveData(). The event can also be automatically cleared
 * if the I2C module detects a NACK or a repeated START or STOP condition
 * 
 * @param baseAddr  base address of the I2C module
 * @return  indication of a transmit data request
 */
static inline bool I2C_Get_SlaveTransmitDataEvent(const I2C_Type *baseAddr)
{
    uint32_t regValue = (uint32_t) baseAddr->SSTS;
    regValue = (regValue & I2C_SSTS_TXIF_MASK) >> I2C_SSTS_TXIF_SHIFT;
    return (bool) ((regValue != 0U) ? true : false);
}

/*! @} */ /* End of Slave Status Events */

/*******************************************************************************
 * Slave Status Clear
 ******************************************************************************/
/*!
 * @name Slave Status Clear
 * @brief Functions for clearing I2C slave event flags.
 * @{
 */

#if(I2C_HAS_ULTRA_FAST_MODE)

/*!
 * @brief Clear the slave FIFO overflow/underflow flag.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 */
static inline void I2C_Clear_SlaveFIFOErrorEvent(I2C_Type *baseAddr)
{
    baseAddr->SSTS = ((uint32_t) 1U << I2C_SSTS_OPERRIF_SHIFT);
}

#endif

/*!
 * @brief Clear bit error flag
 * 
 * This function clears the bit error event.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_SlaveBitErrorEvent(I2C_Type *baseAddr)
{
    baseAddr->SSTS = ((uint32_t) 1U << I2C_SSTS_ARBIF_SHIFT);
}

/*!
 * @brief Clear the STOP detect flag
 * 
 * This function clears the STOP detect event.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_SlaveSTOPDetectEvent(I2C_Type *baseAddr)
{
    baseAddr->SSTS = ((uint32_t) 1U << I2C_SSTS_STOPIF_SHIFT);
}

/*!
 * @brief Clear the repeated START detect flag
 * 
 * This function clears the repeated START detect event.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Clear_SlaveRepeatedStartEvent(I2C_Type *baseAddr)
{
    baseAddr->SSTS = ((uint32_t) 1U << I2C_SSTS_RSIF_SHIFT);
}

/*! @} */ /* End of Slave Status Clear */

/*******************************************************************************
 * Slave Interrupt Control
 ******************************************************************************/
/*!
 * @name Slave Interrupt Control
 * @brief Functions for enabling/disabling I2C slave interrupt sources.
 * @{
 */

/*!
 * @brief Enable or disable specified I2C slave interrupts.
 *
 * @param[in] baseAddr    Pointer to the I2C peripheral base address.
 * @param[in] interrupts  Bitmask of interrupts (OR of I2C_SLAVE_*_INT defines).
 * @param[in] enable      true = enable, false = disable.
 */
static inline void I2C_Set_SlaveInt(I2C_Type *baseAddr, uint32_t interrupts, bool enable)
{
    uint32_t tmp = baseAddr->SIE;

    if (enable == true)
    {
        tmp |= interrupts;
    } else
    {
        tmp &= ~interrupts;
    }
    baseAddr->SIE = tmp;
}

/*!
 * @brief Return the state of the specified I2C slave interrupt
 * 
 * This function returns the enabled/disabled state of the slave interrupt 
 * source specified by the interrupt parameter.
 * 
 * @param baseAddr  base address of the I2C module
 * @param interrupts  interrupt for which the check is made; 
 *  must be one of the following constants:
 *  - I2C_SLAVE_SMBUS_ALERT_RESPONSE  - SMBus Alert Response Interrupt
 *  - I2C_SLAVE_GENERAL_CALL          - General Call Interrupt
 *  - I2C_SLAVE_ADDRESS_MATCH_1       - Address Match 1 Interrupt
 *  - I2C_SLAVE_ADDRESS_MATCH_0       - Address Match 0 Interrupt
 *  - I2C_SLAVE_FIFO_ERROR            - FIFO Error Interrupt
 *  - I2C_SLAVE_BIT_ERROR             - Bit Error Interrupt
 *  - I2C_SLAVE_STOP_DETECT           - STOP Detect Interrupt
 *  - I2C_SLAVE_REPEATED_START        - Repeated Start Interrupt
 *  - I2C_SLAVE_TRANSMIT_ACK          - Transmit ACK Interrupt
 *  - I2C_SLAVE_ADDRESS_VALID         - Address Valid Interrupt
 *  - I2C_SLAVE_RECEIVE_DATA          - Receive Data Interrupt
 *  - I2C_SLAVE_TRANSMIT_DATA         - Transmit Data Interrupt
 * @return  enable/disable state of specified interrupt
 */
static inline bool I2C_Get_SlaveInt(const I2C_Type *baseAddr, uint32_t interrupts)
{
    uint32_t tmp = baseAddr->SIE;
    bool hasInterrupts = false;

    if ((tmp & interrupts) != (uint32_t) 0U)
    {
        hasInterrupts = true;
    }

    return hasInterrupts;
}

/*! @} */ /* End of Slave Interrupt Control */

/*******************************************************************************
 * Slave DMA Control
 ******************************************************************************/
/*!
 * @name Slave DMA Control
 * @brief Functions for enabling/disabling DMA requests on slave Rx/Tx paths.
 * @{
 */

/*!
 * @brief Enable or disable slave receive data DMA requests.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] enable    true = enable Rx DMA, false = disable Rx DMA.
 */
static inline void I2C_Set_SlaveRxDMA(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_RXDMAEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_RXDMAEN_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable/disable slave transmit data DMA requests
 * 
 * This function enables or disables generation of Tx DMA requests when the module
 * requires more data to transmit.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  specifies whether to enable or disable transmit data DMA requests
 */
static inline void I2C_Set_SlaveTxDMA(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_TXDMAEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_TXDMAEN_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Slave DMA Control */

/*******************************************************************************
 * Slave Address Configuration
 ******************************************************************************/
/*!
 * @name Slave Address Configuration
 * @brief Functions for configuring slave address matching, ADDR0 register,
 *        received address readback, and High-Speed mode detection.
 * @{
 */

/*!
 * @brief Set the address match configuration.
 *
 * Configures the condition that triggers a slave address match.
 *
 * @param[in] baseAddr       Pointer to the I2C peripheral base address.
 * @param[in] configuration  Address match mode (see #i2c_slave_addr_config_t).
 */
static inline void I2C_Set_SlaveAddrConfig(I2C_Type *baseAddr, i2c_slave_addr_config_t configuration)
{
    uint32_t tmp = baseAddr->SCTRL;
    tmp &= ~(I2C_SCTRL_ADDRCFG_MASK);
    tmp |= I2C_SCTRL_ADDRCFG(configuration);
    baseAddr->SCTRL = tmp;
}

/*!
 * @brief Control detection of the High-speed Mode master code
 * 
 * This function enables or disables the detection of the High-speed Mode 
 * master code of slave address 0000_1XX, but does not cause an address match 
 * on this code. When set and any Hs-mode master code is detected, the slave 
 * filter and ACK stalls are disabled until the next STOP condition is detected.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  enable/disable the detection of the High-speed Mode master code
 */
static inline void I2C_Set_SlaveHighSpeedModeDetect(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_HSEN_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_HSEN_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Slave Address Configuration */

/*******************************************************************************
 * Slave ACK/NACK & Clock Stretching
 ******************************************************************************/
/*!
 * @name Slave ACK/NACK & Clock Stretching
 * @brief Functions for controlling slave NACK handling, ACK transmission,
 *        and SCL clock stretching on various bus events.
 * @{
 */

/*!
 * @brief Configure slave behaviour when NACK is detected.
 *
 * When enabled, the slave continues transfers after a NACK.
 * Required for Ultra-Fast mode operation.
 *
 * @param[in] baseAddr     Pointer to the I2C peripheral base address.
 * @param[in] nack_config  NACK reaction mode (see #i2c_slave_nack_config_t).
 */
static inline void I2C_Set_SlaveIgnoreNACK(I2C_Type *baseAddr, i2c_slave_nack_config_t nack_config)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_IGACK_MASK));
    regValue |= ((uint32_t)nack_config) << I2C_SCTRL_IGACK_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable or disable clock stretching for the sending of the ACK bit
 * 
 * This function enables or disables SCL clock stretching during slave-transmit address 
 * byte(s) and slave-receiver address and data byte(s) to allow software to write the 
 * Transmit ACK Register before the ACK or NACK is transmitted. Clock stretching occurs 
 * when transmitting the 9th bit and is therefore not compatible with high speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  enable or disable clock stretching
 */
static inline void I2C_Set_SlaveACKStall(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_ACKSTALL_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_ACKSTALL_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable or disable clock stretching for data transmission
 * 
 * This function enables or disables SCL clock stretching when the transmit data 
 * flag is set during a slave-transmit transfer. Clock stretching occurs following 
 * the 9th bit and is therefore compatible with high speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  enable or disable clock stretching
 */
static inline void I2C_Set_SlaveTXDStall(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_TXSTALL_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_TXSTALL_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable or disable clock stretching for data reception
 * 
 * This function enables or disables SCL clock stretching when receive data flag 
 * is set during a slave-receive transfer. Clock stretching occurs following the 9th
 * bit and is therefore compatible with high speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  enable or disable clock stretching
 */
static inline void I2C_Set_SlaveRXStall(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_RXSTALL_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_RXSTALL_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*!
 * @brief Enable or disable clock stretching for valid address reception
 * 
 * This function enables or disables SCL clock stretching when the address valid 
 * flag is asserted. Clock stretching only occurs following the 9th bit and is 
 * therefore compatible with high speed mode.
 * 
 * @param baseAddr  base address of the I2C module
 * @param enable  enable or disable clock stretching
 */
static inline void I2C_Set_SlaveAddrStall(I2C_Type *baseAddr, bool enable)
{
    uint32_t regValue = (uint32_t) baseAddr->SCTRL;
    regValue &= (uint32_t) (~(I2C_SCTRL_ADRSTALL_MASK));
    regValue |= (uint32_t)(enable ? 1U : 0U) << I2C_SCTRL_ADRSTALL_SHIFT;
    baseAddr->SCTRL = (uint32_t) regValue;
}

/*! @} */ /* End of Slave ACK/NACK & Clock Stretching */

/*******************************************************************************
 * Slave Address & Data I/O
 ******************************************************************************/
/*!
 * @name Slave Address & Data I/O
 * @brief Functions for configuring the slave address register (ADDR0),
 *        reading the received address, and transmitting/receiving data.
 * @{
 */

/*!
 * @brief Set the ADDR0 register for slave address matching.
 *
 * In 7-bit mode the address is compared to ADDR0[7:1]. In 10-bit mode,
 * the first byte is compared to {11110, ADDR0[10:9]} and the second
 * byte to ADDR0[8:1].
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] addr      Address value to write to ADDR0.
 */
static inline void I2C_Set_SlaveAddr0(I2C_Type *baseAddr, uint16_t addr)
{
    uint32_t tmp = baseAddr->SADDR;
    tmp &= ~(I2C_SADDR_ADDRA_MASK);
    tmp |= I2C_SADDR_ADDRA(addr);
    baseAddr->SADDR = tmp;
}

/*!
 * @brief Return the received slave address
 * 
 * This function returns the received slave address. Reading the address clears 
 * the address valid event. The address can be 7-bit or 10-bit (10-bit addresses 
 * are prefixed by 11110) and includes the R/W bit in the least significant position.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  received address
 */
static inline uint16_t I2C_Get_SlaveReceivedAddr(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->SRADDR;
    tmp = (tmp & I2C_SRADDR_ADDR_MASK) >> I2C_SRADDR_ADDR_SHIFT;
    return (uint16_t) tmp;
}

/*!
 * @brief Configure the ACK/NACK transmission after a received byte
 * 
 * This function can be used to instruct the I2C slave whether to send an ACK or 
 * a NACK after receiving a byte. When ACK stall is enabled this function must be 
 * called after each matching address and after each received data byte. It can also 
 * be called when I2C Slave is disabled or idle to configure the default ACK/NACK.
 * 
 * @param baseAddr  base address of the I2C module
 * @param nack  specifies whether to transmit ACK or NACK
 */
static inline void I2C_Set_SlaveTransmitNACK(I2C_Type *baseAddr, i2c_slave_nack_transmit_t nack)
{
    uint32_t regValue = (uint32_t) baseAddr->SACK;
    regValue &= (uint32_t) (~(I2C_SACK_NACK_MASK));
    regValue |= ((uint32_t)nack) << I2C_SACK_NACK_SHIFT;
    baseAddr->SACK = (uint32_t) regValue;
}

/*!
 * @brief Provide data for the I2C slave transmitter
 * 
 * This function provides one byte of data for the I2C slave to transmit. 
 * Calling this function clears the transmit data event.
 * 
 * @param baseAddr  base address of the I2C module
 * @param data  data for the I2C slave transmitter
 */
static inline void I2C_Transmit_SlaveData(I2C_Type *baseAddr, uint8_t data)
{
    baseAddr->SDATA = (uint32_t) data;
}

/*!
 * @brief Return the data received by the I2C slave receiver
 * 
 * This function returns the data received by the I2C slave.
 * Calling this function clears the receive data event.
 * 
 * @param baseAddr  base address of the I2C module
 * @return  data received by the I2C slave receiver
 */
static inline uint8_t I2C_Get_SlaveData(const I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->SDATA;
    tmp = (tmp & I2C_SDATA_DATA_MASK) >> I2C_SDATA_DATA_SHIFT;
    return (uint8_t) tmp;
}

/*! @} */ /* End of Slave Address & Data I/O */

/*******************************************************************************
 * Master Timeout Configuration
 ******************************************************************************/
/*!
 * @name Master Timeout Configuration
 * @brief Functions for configuring idle timeout and line-low timeout
 *        detection for bus error recovery.
 * @{
 */

/*!
 * @brief Set the idle timeout period.
 *
 * Configures the number of prescaled cycles after SDA and SCL are both
 * high before the bus is considered idle.
 *
 * @param[in] baseAddr  Pointer to the I2C peripheral base address.
 * @param[in] value     Timeout period value.
 */
static inline void I2C_Set_MasterTimeoutPeriod(I2C_Type *baseAddr, uint16_t value)
{
    uint32_t tmp = baseAddr->TOCFG;
    tmp &= ~(I2C_TOCFG_IDLE_MASK);
    tmp |= I2C_TOCFG_IDLE(value);
    baseAddr->TOCFG = tmp;
}

/*!
 * @brief Get the idle timeout period
 * 
 * This function is to Get the number of cycles that the line idle flag is 
 * set after detecting that SDA and SCL are high.
 * 
 * @param baseAddr  base address of the I2C module
 */
static inline uint32_t I2C_Get_MasterTimeoutPeriod(I2C_Type *baseAddr)
{
    uint32_t tmp = baseAddr->TOCFG;
    tmp &= (I2C_TOCFG_IDLE_MASK);
    tmp >>= I2C_TOCFG_IDLE_SHIFT;
    return tmp;
}

/*!
 * @brief Set the pin low timeout period
 * 
 * This function is to configure the cycles of line low timeout.
 * 
 * @param baseAddr  base address of the I2C module
 * @param value  timeout period
 */
static inline void I2C_Set_MasterLineLowTimeoutPeriod(I2C_Type *baseAddr, uint16_t value)
{
    baseAddr->TOCFG &= ~(I2C_TOCFG_LOW_MASK);
    baseAddr->TOCFG |= I2C_TOCFG_LOW(value);
}

/*!
 * @brief Set SDA and SCL line low detection.
 *
 * @param baseAddr  base address of the I2C module
 */
static inline void I2C_Set_MasterLineLowDetect(I2C_Type *baseAddr)
{
    baseAddr->TOCFG &= ~(I2C_TOCFG_SDA_MASK);
    baseAddr->TOCFG |= I2C_TOCFG_SDA_MASK;
}

/*! @} */ /* End of Master Timeout Configuration */

#if defined(__cplusplus)
}
#endif

/*! @} */ /* End of i2c_hw_access group */

#endif /* I2C_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
