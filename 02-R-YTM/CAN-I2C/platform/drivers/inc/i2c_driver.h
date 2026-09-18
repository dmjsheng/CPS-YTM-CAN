/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file i2c_driver.h
 * @version 1.4.1
 *
 * @brief I2C Driver API – public interface.
 *
 * Provides the application-level API for configuring and using the I2C
 * peripheral in both master and slave modes. APIs are organized as follows:
 *
 * - **Master Initialization**  – Init / Deinit
 * - **Master Configuration**   – baud rate, slave address
 * - **Master Transfer**        – blocking & non-blocking send/receive, abort
 * - **Master Status**          – transfer status query
 * - **Slave Initialization**   – Init / Deinit
 * - **Slave Buffer Management**– set Tx/Rx buffers
 * - **Slave Transfer**         – blocking & non-blocking send/receive, abort
 * - **Slave Status**           – transfer status query
 * - **Default Configuration**  – get default master/slave config
 * - **IRQ Handlers**           – master, slave, and a combined master/slave handler
 */

#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "status.h"
#include "dma_driver.h"
#include "osif.h"
#include "callbacks.h"

/*!
 * @addtogroup i2c
 * @brief Application-level I2C master/slave driver.
 * @{
 */

/*******************************************************************************
 * Enumerations
 ******************************************************************************/

/*! @cond DRIVER_INTERNAL_USE_ONLY */
/*! Size of the master command queue.
 *  Worst case: 5 commands in High-Speed receive with 10-bit address:
 *  START + master code, REP START + addr_1 + tx, addr_2,
 *  REP START + addr_1 + rx, receive command */
#define I2C_MASTER_CMD_QUEUE_SIZE   5U
/*! @endcond */

/*! @brief I2C operating modes.
 *
 * Selects the bus speed and protocol mode for the I2C peripheral.
 */
typedef enum
{
    I2C_STANDARD_MODE = 0x0U,   /*!< Standard-mode (Sm), up to 100 kbit/s */
    I2C_FAST_MODE = 0x1U,   /*!< Fast-mode (Fm), up to 400 kbit/s */
#if(I2C_HAS_FAST_PLUS_MODE)
    I2C_FASTPLUS_MODE = 0x2U,   /*!< Fast-mode Plus (Fm+), up to 1 Mbit/s */
#endif
#if(I2C_HAS_HIGH_SPEED_MODE)
    I2C_HIGHSPEED_MODE = 0x3U,   /*!< High-speed Mode (Hs), up to 3.4 Mbit/s */
#endif
#if(I2C_HAS_ULTRA_FAST_MODE)
    I2C_ULTRAFAST_MODE = 0x4U    /*!< Ultra Fast Mode (UFm), up to 5 Mbit/s */
#endif
} i2c_mode_t;

/*! @brief Type of I2C transfer mechanism.
 *
 * Selects whether the driver uses DMA or interrupt-driven transfers.
 */
typedef enum
{
    I2C_USING_DMA = 0,    /*!< DMA-based transfer */
    I2C_USING_INTERRUPTS = 1,    /*!< Interrupt-based transfer */
} i2c_transfer_type_t;

/*******************************************************************************
 * Configuration Structures
 ******************************************************************************/

/*!
 * @brief Master configuration structure.
 *
 * Passed to I2C_DRV_MasterInit() to configure the I2C master.
 * The application may free this structure after init returns.
 */
typedef struct
{
    uint16_t slaveAddress;                      /*!< Target slave address (7-bit or 10-bit). */
    bool is10bitAddr;                           /*!< true = 10-bit address, false = 7-bit. */
    i2c_mode_t operatingMode;                   /*!< Bus speed / protocol mode. */
    uint32_t baudRate;                          /*!< SCL frequency in Hz for the selected mode. */
#if(I2C_HAS_HIGH_SPEED_MODE)
    uint32_t baudRateHS;                        /*!< SCL frequency in Hz for Hs-mode (ignored otherwise). */
    uint8_t masterCode;                         /*!< Hs-mode master code (0–7, ignored otherwise). */
#endif
    i2c_transfer_type_t transferType;           /*!< DMA or interrupt transfer mechanism. */
    uint8_t dmaChannel;                         /*!< DMA channel number (ignored when using interrupts). */
    i2c_master_callback_t masterCallback;       /*!< End-of-transfer callback (called from ISR context).
                                                     May be NULL for polling usage. */
    void *callbackParam;                        /*!< User parameter forwarded to masterCallback. */
} i2c_master_user_config_t;

/*!
 * @brief Slave configuration structure.
 *
 * Passed to I2C_DRV_SlaveInit() to configure the I2C slave.
 * The application may free this structure after init returns.
 */
typedef struct
{
    uint16_t slaveAddress;                    /*!< Own slave address (7-bit or 10-bit). */
    bool is10bitAddr;                         /*!< true = 10-bit address, false = 7-bit. */
    i2c_mode_t operatingMode;                 /*!< Bus speed / protocol mode. */
    bool slaveListening;                      /*!< true = always listening, false = on-demand. */
    i2c_transfer_type_t transferType;         /*!< DMA or interrupt transfer mechanism. */
    uint8_t dmaChannel;                       /*!< DMA channel number (ignored when using interrupts). */
    i2c_slave_callback_t slaveCallback;       /*!< Event callback (called from ISR context).
                                                  Required when slaveListening = true. */
    void *callbackParam;                      /*!< User parameter forwarded to slaveCallback. */
} i2c_slave_user_config_t;

/*!
 * @brief Baud rate parameter structure.
 *
 * Used with I2C_DRV_MasterGetBaudRate() and I2C_DRV_MasterSetBaudRate().
 */
typedef struct
{
    uint32_t baudRate;                        /*!< SCL frequency in Hz. */
#if(I2C_HAS_HIGH_SPEED_MODE)
    uint32_t baudRateHS;                      /*!< Hs-mode SCL frequency in Hz. */
#endif
} i2c_baud_rate_params_t;

/*! @cond DRIVER_INTERNAL_USE_ONLY */
/* I2C master commands */
typedef enum
{
    I2C_MASTER_COMMAND_TRANSMIT = 0x0U,              /*!< Transmit DATA[7:0] */
    I2C_MASTER_COMMAND_RECEIVE = 0x4U,               /*!< Receive (DATA[7:0] + 1) bytes */
    I2C_MASTER_COMMAND_STOP = 0x2U,                  /*!< Generate STOP condition */
    I2C_MASTER_COMMAND_RECEIVE_DISCARD = 0x6U,       /*!< Receive and discard (DATA[7:0] + 1) bytes */
    I2C_MASTER_COMMAND_START = 0x1U,                 /*!< Generate START and transmit address in DATA[7:0] */
    I2C_MASTER_COMMAND_START_NACK = 0x3U,            /*!< Generate START and transmit address in DATA[7:0],
                                                          expect a NACK to be returned */
    I2C_MASTER_COMMAND_START_HS = 0x9U,              /*!< Generate START and transmit address in DATA[7:0]
                                                          in high speed mode */
    I2C_MASTER_COMMAND_START_NACK_HS = 0xBU,         /*!< Generate START and transmit address in DATA[7:0]
                                                          in high speed mode, expect a NACK to be returned */
} i2c_master_command_t;
/*! @endcond */

/*! @cond DRIVER_INTERNAL_USE_ONLY */
/* Master software command queue */
typedef struct
{
    i2c_master_command_t cmd[I2C_MASTER_CMD_QUEUE_SIZE];
    uint8_t data[I2C_MASTER_CMD_QUEUE_SIZE];
    uint8_t writeIdx;
    uint8_t readIdx;
} i2c_master_cmd_queue_t;
/*! @endcond */

/*!
 * @brief Master internal context structure
 *
 * This structure is used by the master-mode driver for its internal logic. It must
 * be provided by the application through the I2C_DRV_MasterInit() function, then
 * it cannot be freed until the driver is de-initialized using I2C_DRV_MasterDeinit().
 * The application should make no assumptions about the content of this structure.
 */
typedef struct
{
/*! @cond DRIVER_INTERNAL_USE_ONLY */
    i2c_master_cmd_queue_t cmdQueue;        /* Software queue for commands, when I2C FIFO is not big enough */
    uint8_t *rxBuff;                        /* Pointer to receive data buffer */
    uint32_t rxSize;                        /* Size of receive data buffer */
    const uint8_t *txBuff;                  /* Pointer to transmit data buffer */
    uint32_t txSize;                        /* Size of transmit data buffer */
    volatile status_t status;               /* Status of last driver operation */
    i2c_mode_t operatingMode;               /* I2C Operating mode */
    uint16_t slaveAddress;                  /* Slave address */
    volatile bool i2cIdle;                  /* Idle/busy state of the driver */
#if(I2C_HAS_HIGH_SPEED_MODE)
    uint8_t masterCode;                     /* Master code for High-speed mode */
    bool highSpeedInProgress;               /* High-speed communication is in progress */
    uint32_t baudRateHS;                    /*!< Baud rate for High-speed mode. Unused in other operating modes */
#endif
    bool sendStop;                          /* Specifies if STOP condition must be generated after current transfer */
    bool is10bitAddr;                       /* Selects 7-bit or 10-bit slave address */
    semaphore_t idleSemaphore;              /* Semaphore used by blocking functions */
    bool blocking;                          /* Specifies if the current transfer is blocking */
    i2c_transfer_type_t transferType;       /* Type of I2C transfer */
    uint8_t dmaChannel;                     /* Channel number for DMA rx channel */
    i2c_master_callback_t masterCallback;   /* Master callback function */
    void *callbackParam;                    /* Parameter for the master callback function */
    bool abortedTransfer;                   /* Specifies if master has aborted transfer */
    uint32_t baudrate;                      /* Baud rate in Hz*/
/*! @endcond */
} i2c_master_state_t;

/*!
 * @brief Slave internal context structure
 *
 * This structure is used by the slave-mode driver for its internal logic. It must
 * be provided by the application through the I2C_DRV_SlaveInit() function, then
 * it cannot be freed until the driver is de-initialized using I2C_DRV_SlaveDeinit().
 * The application should make no assumptions about the content of this structure.
 */
typedef struct
{
/*! @cond DRIVER_INTERNAL_USE_ONLY */
    status_t status;                        /* The I2C slave status */
    volatile bool isTransferInProgress;     /* Slave is busy because of an ongoing transfer */
    uint32_t txSize;                        /* Size of the TX buffer*/
    uint32_t rxSize;                        /* Size of the RX buffer*/
    const uint8_t *txBuff;                  /* Pointer to Tx Buffer*/
    uint8_t *rxBuff;                        /* Pointer to Rx Buffer*/
    i2c_mode_t operatingMode;               /* I2C Operating mode */
    bool slaveListening;                    /* Slave mode (always listening or on demand only) */
    bool is10bitAddress;                    /* Specifies if 10-bit or 7-bit address */
    uint8_t repeatedStarts;                 /* Specifies the number of repeated starts */
    bool txUnderrunWarning;                 /* Possible slave tx under run */
    semaphore_t idleSemaphore;              /* Semaphore used by blocking functions */
    bool blocking;                          /* Specifies if the current transfer is blocking */
    i2c_transfer_type_t transferType;       /* Type of I2C transfer */
    uint8_t dmaChannel;                     /* Channel number for DMA channel */
    i2c_slave_callback_t slaveCallback;     /* Slave callback function */
    void *callbackParam;                    /* Parameter for the slave callback function */
/*! @endcond */
} i2c_slave_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * Master Initialization
 ******************************************************************************/
/*!
 * @name Master Initialization
 * @brief Functions for initializing and de-initializing the I2C master driver.
 * @{
 */

/*!
 * @brief Initialize the I2C master mode driver.
 *
 * Configures the I2C peripheral for master operation according to the
 * provided configuration structure.
 *
 * @param[in]  instance       I2C peripheral instance number.
 * @param[in]  userConfigPtr  Pointer to master configuration. May be freed
 *                            after this call returns.
 * @param[out] master         Pointer to master driver state. Must remain
 *                            allocated until I2C_DRV_MasterDeinit() is called.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterInit(uint32_t instance,
                            const i2c_master_user_config_t *userConfigPtr,
                            i2c_master_state_t *master);

/*!
 * @brief De-initialize the I2C master mode driver.
 *
 * Releases all master-mode resources. The driver cannot be used again
 * until re-initialized.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterDeinit(uint32_t instance);

/*! @} */ /* End of Master Initialization */

/*******************************************************************************
 * Master Configuration
 ******************************************************************************/
/*!
 * @name Master Configuration
 * @brief Functions for configuring baud rate and slave address at run-time.
 * @{
 */

/*!
 * @brief Get the currently configured baud rate.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] baudRate  Receives the current baud rate parameters.
 */
void I2C_DRV_MasterGetBaudRate(uint32_t instance, i2c_baud_rate_params_t *baudRate);

/*!
 * @brief Set the baud rate for subsequent I2C communication.
 *
 * Sets the SCL frequency and optionally changes the operating mode.
 * Due to hardware limitations the actual baud rate may differ from the
 * requested value. Call I2C_DRV_MasterGetBaudRate() afterwards to read
 * the actual rate that was achieved.
 *
 * @param[in] instance       I2C peripheral instance number.
 * @param[in] operatingMode  Desired operating mode.
 * @param[in] baudRate       Desired baud rate parameters.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterSetBaudRate(uint32_t instance,
                                   const i2c_mode_t operatingMode,
                                   const i2c_baud_rate_params_t baudRate);

/*!
 * @brief Set the target slave address.
 *
 * Updates the slave address used by all subsequent master transfers.
 *
 * @param[in] instance    I2C peripheral instance number.
 * @param[in] address     Slave address (7-bit or 10-bit).
 * @param[in] is10bitAddr true = 10-bit address, false = 7-bit.
 */
void I2C_DRV_MasterSetSlaveAddr(uint32_t instance, const uint16_t address, const bool is10bitAddr);

/*! @} */ /* End of Master Configuration */

/*******************************************************************************
 * Master Transfer
 ******************************************************************************/
/*!
 * @name Master Transfer
 * @brief Blocking and non-blocking send/receive functions for master mode,
 *        plus transfer abort.
 * @{
 */

/*!
 * @brief Start a non-blocking send transaction (master).
 *
 * Initiates transmission to the currently configured slave address and
 * returns immediately. Use I2C_DRV_MasterGetTransferStatus() to poll
 * completion, or register a callback.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @param[in] txBuff    Pointer to transmit data buffer.
 * @param[in] txSize    Number of bytes to transmit.
 * @param[in] sendStop  true = generate STOP after transmission.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterSendData(uint32_t instance,
                                const uint8_t *txBuff,
                                uint32_t txSize,
                                bool sendStop);

/*!
 * @brief Perform a blocking send transaction (master).
 *
 * Sends data and blocks until the transfer completes or the timeout
 * expires.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @param[in] txBuff    Pointer to transmit data buffer.
 * @param[in] txSize    Number of bytes to transmit.
 * @param[in] sendStop  true = generate STOP after transmission.
 * @param[in] timeout   Timeout in milliseconds.
 * @return  STATUS_SUCCESS, STATUS_TIMEOUT, or error code.
 */
status_t I2C_DRV_MasterSendDataBlocking(uint32_t instance,
                                        const uint8_t *txBuff,
                                        uint32_t txSize,
                                        bool sendStop,
                                        uint32_t timeout);

/*!
 * @brief Start a non-blocking receive transaction (master).
 *
 * Initiates reception from the currently configured slave address and
 * returns immediately.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] rxBuff    Pointer to receive data buffer.
 * @param[in]  rxSize    Number of bytes to receive.
 * @param[in]  sendStop  true = generate STOP after reception.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterReceiveData(uint32_t instance,
                                   uint8_t *rxBuff,
                                   uint32_t rxSize,
                                   bool sendStop);

/*!
 * @brief Perform a blocking receive transaction (master).
 *
 * Receives data and blocks until the transfer completes or the timeout
 * expires.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] rxBuff    Pointer to receive data buffer.
 * @param[in]  rxSize    Number of bytes to receive.
 * @param[in]  sendStop  true = generate STOP after reception.
 * @param[in]  timeout   Timeout in milliseconds.
 * @return  STATUS_SUCCESS, STATUS_TIMEOUT, or error code.
 */
status_t I2C_DRV_MasterReceiveDataBlocking(uint32_t instance,
                                           uint8_t *rxBuff,
                                           uint32_t rxSize,
                                           bool sendStop,
                                           uint32_t timeout);

/*!
 * @brief Abort a non-blocking master transfer.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_MasterAbortTransferData(uint32_t instance);

/*! @} */ /* End of Master Transfer */

/*******************************************************************************
 * Master Status
 ******************************************************************************/
/*!
 * @name Master Status
 * @brief Functions for querying the progress of an active master transfer.
 * @{
 */

/*!
 * @brief Get the current master transfer status.
 *
 * Can be called during a non-blocking transfer to check progress.
 *
 * @param[in]  instance        I2C peripheral instance number.
 * @param[out] bytesRemaining  Remaining bytes in the active transfer
 *                             (may be NULL if not needed).
 * @return  STATUS_SUCCESS (transfer complete), STATUS_BUSY (in progress),
 *          or error code.
 */
status_t I2C_DRV_MasterGetTransferStatus(uint32_t instance, uint32_t *bytesRemaining);

/*! @} */ /* End of Master Status */

/*******************************************************************************
 * Slave Initialization
 ******************************************************************************/
/*!
 * @name Slave Initialization
 * @brief Functions for initializing and de-initializing the I2C slave driver.
 * @{
 */

/*!
 * @brief Initialize the I2C slave mode driver.
 *
 * @param[in]  instance       I2C peripheral instance number.
 * @param[in]  userConfigPtr  Pointer to slave configuration. May be freed
 *                            after this call returns.
 * @param[out] slave          Pointer to slave driver state. Must remain
 *                            allocated until I2C_DRV_SlaveDeinit() is called.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveInit(uint32_t instance,
                           const i2c_slave_user_config_t *userConfigPtr,
                           i2c_slave_state_t *slave);

/*!
 * @brief De-initialize the I2C slave mode driver.
 *
 * Releases all slave-mode resources. The driver cannot be used again
 * until re-initialized.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveDeinit(uint32_t instance);

/*! @} */ /* End of Slave Initialization */

/*******************************************************************************
 * Slave Buffer Management
 ******************************************************************************/
/*!
 * @name Slave Buffer Management
 * @brief Functions for providing Tx/Rx buffers to the slave driver
 *        (typically called from the slave callback).
 * @{
 */

/*!
 * @brief Provide a transmit data buffer for the slave.
 *
 * Typically called from the slave callback when the driver reports
 * I2C_SLAVE_EVENT_TX_REQ or I2C_SLAVE_EVENT_TX_EMPTY.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @param[in] txBuff    Pointer to transmit data.
 * @param[in] txSize    Number of bytes available.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveSetTxBuffer(uint32_t instance,
                                  const uint8_t *txBuff,
                                  uint32_t txSize);

/*!
 * @brief Provide a receive data buffer for the slave.
 *
 * Typically called from the slave callback when the driver reports
 * I2C_SLAVE_EVENT_RX_REQ or I2C_SLAVE_EVENT_RX_FULL.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] rxBuff    Pointer to receive buffer.
 * @param[in]  rxSize    Buffer capacity in bytes.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveSetRxBuffer(uint32_t instance,
                                  uint8_t *rxBuff,
                                  uint32_t rxSize);

/*! @} */ /* End of Slave Buffer Management */

/*******************************************************************************
 * Slave Transfer
 ******************************************************************************/
/*!
 * @name Slave Transfer
 * @brief Blocking and non-blocking send/receive functions for slave mode
 *        (only available when slaveListening = false), plus transfer abort.
 * @{
 */

/*!
 * @brief Start a non-blocking send transaction (slave).
 *
 * Only available when the slave was initialized with slaveListening = false.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @param[in] txBuff    Pointer to transmit data buffer.
 * @param[in] txSize    Number of bytes to transmit.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveSendData(uint32_t instance,
                               const uint8_t *txBuff,
                               uint32_t txSize);

/*!
 * @brief Perform a blocking send transaction (slave).
 *
 * Only available when the slave was initialized with slaveListening = false.
 * Blocks until the transfer completes or the timeout expires.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @param[in] txBuff    Pointer to transmit data buffer.
 * @param[in] txSize    Number of bytes to transmit.
 * @param[in] timeout   Timeout in milliseconds.
 * @return  STATUS_SUCCESS, STATUS_TIMEOUT, or error code.
 */
status_t I2C_DRV_SlaveSendDataBlocking(uint32_t instance,
                                       const uint8_t *txBuff,
                                       uint32_t txSize,
                                       uint32_t timeout);

/*!
 * @brief Start a non-blocking receive transaction (slave).
 *
 * Only available when the slave was initialized with slaveListening = false.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] rxBuff    Pointer to receive data buffer.
 * @param[in]  rxSize    Number of bytes to receive.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveReceiveData(uint32_t instance,
                                  uint8_t *rxBuff,
                                  uint32_t rxSize);

/*!
 * @brief Perform a blocking receive transaction (slave).
 *
 * Only available when the slave was initialized with slaveListening = false.
 * Blocks until the transfer completes or the timeout expires.
 *
 * @param[in]  instance  I2C peripheral instance number.
 * @param[out] rxBuff    Pointer to receive data buffer.
 * @param[in]  rxSize    Number of bytes to receive.
 * @param[in]  timeout   Timeout in milliseconds.
 * @return  STATUS_SUCCESS, STATUS_TIMEOUT, or error code.
 */
status_t I2C_DRV_SlaveReceiveDataBlocking(uint32_t instance,
                                          uint8_t *rxBuff,
                                          uint32_t rxSize,
                                          uint32_t timeout);

/*!
 * @brief Abort a non-blocking slave transfer.
 *
 * @param[in] instance  I2C peripheral instance number.
 * @return  STATUS_SUCCESS or error code.
 */
status_t I2C_DRV_SlaveAbortTransferData(uint32_t instance);

/*! @} */ /* End of Slave Transfer */

/*******************************************************************************
 * Slave Status
 ******************************************************************************/
/*!
 * @name Slave Status
 * @brief Functions for querying the progress of an active slave transfer.
 * @{
 */

/*!
 * @brief Get the current slave transfer status.
 *
 * Can be called during a non-blocking transfer to check progress.
 *
 * @param[in]  instance        I2C peripheral instance number.
 * @param[out] bytesRemaining  Remaining bytes in the active transfer
 *                             (may be NULL if not needed).
 * @return  STATUS_SUCCESS (transfer complete), STATUS_BUSY (in progress),
 *          or error code.
 */
status_t I2C_DRV_SlaveGetTransferStatus(uint32_t instance,
                                        uint32_t *bytesRemaining);

/*! @} */ /* End of Slave Status */

/*******************************************************************************
 * Default Configuration
 ******************************************************************************/
/*!
 * @name Default Configuration
 * @brief Functions for obtaining default configuration structures.
 * @{
 */

/*!
 * @brief Get the default master configuration.
 *
 * Fills the provided structure with safe default values.
 *
 * @param[out] config  Pointer to configuration structure to fill.
 */
void I2C_DRV_MasterGetDefaultConfig(i2c_master_user_config_t *config);

/*!
 * @brief Get the default slave configuration.
 *
 * Fills the provided structure with safe default values.
 *
 * @param[out] config  Pointer to configuration structure to fill.
 */
void I2C_DRV_SlaveGetDefaultConfig(i2c_slave_user_config_t *config);

/*! @} */ /* End of Default Configuration */

/*******************************************************************************
 * IRQ Handlers
 ******************************************************************************/
/*!
 * @name IRQ Handlers
 * @brief Interrupt service routines for master, slave modes.
 * @{
 */

/*!
 * @brief Master IRQ handler.
 *
 * Handles the continuation of a master transfer started by one of the
 * send/receive functions. Called from the hardware interrupt vector.
 *
 * @param[in] instance  I2C peripheral instance number.
 */
void I2C_DRV_MasterIRQHandler(uint32_t instance);

/*!
 * @brief Slave IRQ handler.
 *
 * Handles slave-side bus events and notifies the application via the
 * registered callback. Called from the hardware interrupt vector.
 *
 * @param[in] instance  I2C peripheral instance number.
 */
void I2C_DRV_SlaveIRQHandler(uint32_t instance);

#if defined(YTM32B1L_SERIES) || defined(YTM32B1H_SERIES)
/*!
 * @brief Combined master/slave IRQ handler.
 *
 * Used on devices that share a single interrupt vector for both master
 * and slave events. A single I2C instance can only operate as either
 * master or slave at a time.
 *
 * @param[in] instance  I2C peripheral instance number.
 */
void I2C_DRV_ModuleIRQHandler(uint32_t instance);
#endif

/*! @} */ /* End of IRQ Handlers */

/*! @} */ /* End of i2c group */

#if defined(__cplusplus)
}
#endif

#endif /* I2C_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
