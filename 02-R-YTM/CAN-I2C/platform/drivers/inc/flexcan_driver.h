/*
 * Copyright 2020-2022 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file flexcan_driver.h
 * @version 1.4.1
 *
 * @brief FlexCAN Driver — Public API for CAN / CAN-FD communication.
 *
 * This header defines the application-level interface for the FlexCAN
 * peripheral. It wraps the low-level hardware access layer and provides
 * a convenient, instance-based API for configuring the CAN engine, sending
 * and receiving CAN frames, and managing interrupts and callbacks.
 *
 * The APIs are organized into the following functional groups:
 *   - **Initialization & De-initialization** — Set up or tear down the module.
 *   - **Bit Rate Configuration** — Configure standard and FD bit timing.
 *   - **Rx Mask Configuration** — Set global, individual, and FIFO masks.
 *   - **Transmit Operations** — Configure Tx MBs and send frames.
 *   - **Receive Operations** — Configure Rx MBs/FIFO and receive frames.
 *   - **Transfer Status & Error** — Abort, query, and read error status.
 *   - **Callback & Interrupt** — Install event/error callbacks.
 *   - **Transceiver Delay Compensation** — TDC offset and measurement.
 *   - **Pretended Networking** — Low-power wake-up configuration.
 *
 * @note The FlexCAN peripheral clock must be enabled (via clock_manager)
 *       before calling any function in this module.
 */

/*!
 * @page misra_violations MISRA-C:2012 violations list
 *
 * PRQA S 0750 Rule 19.2: A union type specifier has been defined.
 *
 */ 

#ifndef FLEXCAN_DRIVER_H
#define FLEXCAN_DRIVER_H

#include "device_registers.h"
#include "osif.h"

#if FEATURE_CAN_HAS_DMA_ENABLE

#include "dma_driver.h"

#endif

/*!
 * @addtogroup flexcan
 * @brief FlexCAN Peripheral Driver — Public API.
 * @details Provides instance-based APIs for CAN / CAN-FD configuration,
 *          transmission, reception, and interrupt management. Supports
 *          message buffers, Rx FIFO, Enhanced Rx FIFO, DMA, Pretended
 *          Networking, and Transceiver Delay Compensation.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
#define FLEXCAN_MB_HANDLE_ENHANCE_RXFIFO    (128U)
#endif

/*!
 * @brief Rx FIFO transfer type (interrupt-driven or DMA-driven).
 */
typedef enum
{
    FLEXCAN_RXFIFO_USING_INTERRUPTS,    /*!< Use interrupts for RxFIFO. */
#if FEATURE_CAN_HAS_DMA_ENABLE
    FLEXCAN_RXFIFO_USING_DMA            /*!< Use DMA for RxFIFO. */
#endif
} flexcan_rxfifo_transfer_type_t;

/*!
 * @brief Event types reported to the user event callback.
 */
typedef enum
{
    FLEXCAN_EVENT_RX_COMPLETE,     /*!< A frame was received in the configured Rx MB. */
    FLEXCAN_EVENT_RXFIFO_COMPLETE, /*!< A frame was received in the Rx FIFO. */
    FLEXCAN_EVENT_RXFIFO_WARNING,  /*!< Rx FIFO is almost full (5 frames). */
    FLEXCAN_EVENT_RXFIFO_OVERFLOW, /*!< Rx FIFO is full (incoming message was lost). */
    FLEXCAN_EVENT_TX_COMPLETE,     /*!< A frame was sent from the configured Tx MB. */
#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
    FLEXCAN_EVENT_ENHANCE_RXFIFO_AVAILABLEDATA,
    FLEXCAN_EVENT_ENHANCE_RXFIFO_WATERMARK,
    FLEXCAN_EVENT_ENHANCE_RXFIFO_OVERFLOW,
#endif
#if FEATURE_CAN_HAS_WAKE_UP_IRQ
    FLEXCAN_EVENT_WAKEUP_TIMEOUT,  /*!< An wake up event occurred due to timeout. */
    FLEXCAN_EVENT_WAKEUP_MATCH,    /*!< An wake up event occurred due to matching. */
    FLEXCAN_EVENT_SELF_WAKEUP,     /*!< A self wake up event occurred. */
#endif /* FEATURE_CAN_HAS_WAKE_UP_IRQ */
#if FEATURE_CAN_HAS_DMA_ENABLE
    FLEXCAN_EVENT_DMA_COMPLETE,      /*!< A complete transfer occurred on DMA */
    FLEXCAN_EVENT_DMA_ERROR,      /*!< A DMA transfer fail, because of a DMA channel error */
#endif /* FEATURE_CAN_HAS_DMA_ENABLE */
    FLEXCAN_EVENT_ERROR
} flexcan_event_type_t;

/*!
 * @brief Error event types reported to the user error callback.
 */
typedef enum
{
    FLEXCAN_ERROR_OVERRUN_EVENT = CAN_ESR1_ERROVR_MASK,
#if FEATURE_CAN_HAS_FD
    FLEXCAN_FD_DATA_BIT_ERROR_EVENT = CAN_ESR1_ERRINT_FAST_MASK,
#endif
    FLEXCAN_BUS_OFF_DONE_EVENT = CAN_ESR1_BOFFDONEINT_MASK,
    FLEXCAN_TX_WARNING_EVENT = CAN_ESR1_TXWRN_MASK,
    FLEXCAN_RX_WARNING_EVENT = CAN_ESR1_RXWRN_MASK,
    FLEXCAN_BUS_OFF_ENTER_EVENT = CAN_ESR1_BOFFINT_MASK,
    FLEXCAN_BIT_ERROR_EVENT = CAN_ESR1_ERRINT_MASK,
    FLEXCAN_WAKEUP_EVENT = CAN_ESR1_WAKINT_MASK,
#if FEATURE_CAN_HAS_RAM_ECC
    FLEXCAN_RAM_ECC_ERROR_EVENT = CAN_ERRSR_FANCEIF_MASK | CAN_ERRSR_HANCEIF_MASK,
#endif
} flexcan_error_event_type_t;

/*!
 * @brief Runtime state of a message buffer (idle / Rx busy / Tx busy).
 */
typedef enum
{
    FLEXCAN_MB_IDLE,      /*!< The MB is not used by any transfer. */
    FLEXCAN_MB_RX_BUSY,   /*!< The MB is used for a reception. */
    FLEXCAN_MB_TX_BUSY,   /*!< The MB is used for a transmission. */
#if FEATURE_CAN_HAS_DMA_ENABLE
    FLEXCAN_MB_DMA_ERROR /*!< The MB is used as DMA source and fail to transfer */
#endif
} flexcan_mb_state_t;

/*!
 * @brief CAN message identifier type (standard 11-bit or extended 29-bit).
 */
typedef enum
{
    FLEXCAN_MSG_ID_STD,         /*!< Standard ID*/
    FLEXCAN_MSG_ID_EXT          /*!< Extended ID*/
} flexcan_msgbuff_id_type_t;

#if FEATURE_CAN_HAS_PE_CLKSRC_SELECT
/*!
 * @brief Protocol Engine (PE) clock source selection.
 */
typedef enum
{
    FLEXCAN_CLK_SOURCE_OSC = 0U,  /*!< The CAN engine clock source is the oscillator clock. */
    FLEXCAN_CLK_SOURCE_PERIPH = 1U   /*!< The CAN engine clock source is the peripheral clock. */
} flexcan_clk_source_t;
#endif

/*!
 * @brief FlexCAN message buffer data structure.
 *
 * Contains the Code/Status word, message ID, data payload, and data length.
 */
typedef struct
{
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msgId;                     /*!< Message Buffer ID*/
    uint8_t data[64];                   /*!< Data bytes of the FlexCAN message*/
    uint8_t dataLen;                    /*!< Length of data in bytes */
} flexcan_msgbuff_t;

/*!
 * @brief Internal handle for managing a single message buffer transfer.
 */
typedef struct
{
    flexcan_msgbuff_t *mb_message;       /*!< The FlexCAN MB structure */
    semaphore_t mbSema;                  /*!< Semaphore used for signaling completion of a blocking transfer */
    volatile flexcan_mb_state_t state;   /*!< The state of the current MB (idle/Rx busy/Tx busy) */
    bool isBlocking;                     /*!< True if the transfer is blocking */
    bool isRemote;                       /*!< True if the frame is a remote frame */
} flexcan_mb_handle_t;


/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should
 *       not be modified by users. Contents are subject to change in future
 *       releases.
 */
typedef struct FlexCANState
{
    flexcan_mb_handle_t mbs[FEATURE_CAN_MAX_MB_NUM];           /*!< Array containing information
                                                                    related to each MB */
    void (*callback)(uint8_t instance,
                     flexcan_event_type_t eventType,
                     uint32_t buffIdx,
                     struct FlexCANState *driverState);        /*!< IRQ handler callback function. */
    void *callbackParam;                                       /*!< Parameter used to pass user data
                                                                    when invoking the callback
                                                                    function. */
    void (*error_callback)(uint8_t instance,
                           flexcan_error_event_type_t eventType,
                           struct FlexCANState *driverState);  /*!< Error IRQ handler callback
                                                                    function. */
    void *errorCallbackParam;                                  /*!< Parameter used to pass user data
                                                                    when invoking the error callback
                                                                    function. */
#if FEATURE_CAN_HAS_DMA_ENABLE
    uint8_t rxFifoDMAChannel;                                  /*!< DMA channel number used for
                                                                    transfers. */
#endif
#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
    flexcan_mb_handle_t enhanceRxFifoState;   /*!< The state of the enhance rx fifo (idle/Rx busy) */
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */
    flexcan_rxfifo_transfer_type_t transferType;               /*!< Type of RxFIFO transfer. */
    uint32_t max_num_mb;                                       /*!< The maximum number of Message Buffers */
} flexcan_state_t;

/*!
 * @brief Data information structure provided by the user for Tx/Rx operations.
 */
typedef struct
{
    flexcan_msgbuff_id_type_t msg_id_type;  /*!< Type of message ID (standard or extended)*/
    uint32_t data_length;                   /*!< Length of Data in Bytes*/
#if FEATURE_CAN_HAS_FD
    bool fd_enable;                         /*!< Enable or disable FD*/
    uint8_t fd_padding;                     /*!< Set a value for padding. It will be used when the data length code (DLC)
                                                 specifies a bigger payload size than data_length to fill the MB */
    bool enable_brs;                        /*!< Enable bit rate switch inside a CAN FD format frame*/
#endif
    bool is_remote;                         /*!< Specifies if the frame is standard or remote */
} flexcan_data_info_t;

/*!
 * @brief Number of Rx FIFO ID filter elements.
 */
typedef enum
{
    FLEXCAN_RX_FIFO_ID_FILTERS_8 = 0x0,         /*!<   8 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_16 = 0x1,         /*!<  16 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_24 = 0x2,         /*!<  24 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_32 = 0x3,         /*!<  32 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_40 = 0x4,         /*!<  40 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_48 = 0x5,         /*!<  48 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_56 = 0x6,         /*!<  56 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_64 = 0x7,         /*!<  64 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_72 = 0x8,         /*!<  72 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_80 = 0x9,         /*!<  80 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_88 = 0xA,         /*!<  88 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_96 = 0xB,         /*!<  96 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_104 = 0xC,         /*!< 104 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_112 = 0xD,         /*!< 112 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_120 = 0xE,         /*!< 120 Rx FIFO Filters. */
    FLEXCAN_RX_FIFO_ID_FILTERS_128 = 0xF          /*!< 128 Rx FIFO Filters. */
} flexcan_rx_fifo_id_filter_num_t;

/*!
 * @brief Rx acceptance mask type (global or per-MB individual).
 */
typedef enum
{
    FLEXCAN_RX_MASK_GLOBAL,      /*!< Rx global mask*/
    FLEXCAN_RX_MASK_INDIVIDUAL   /*!< Rx individual mask*/
} flexcan_rx_mask_type_t;

/*!
 * @brief Rx FIFO ID filter table element format.
 */
typedef enum
{
    FLEXCAN_RX_FIFO_ID_FORMAT_A, /*!< One full ID (standard and extended) per ID Filter Table element.*/
    FLEXCAN_RX_FIFO_ID_FORMAT_B, /*!< Two full standard IDs or two partial 14-bit (standard and
                                      extended) IDs per ID Filter Table element.*/
    FLEXCAN_RX_FIFO_ID_FORMAT_C, /*!< Four partial 8-bit Standard IDs per ID Filter Table element.*/
    FLEXCAN_RX_FIFO_ID_FORMAT_D  /*!< All frames rejected.*/
} flexcan_rx_fifo_id_element_format_t;

/*!
 * @brief Rx FIFO ID filter table element.
 */
typedef struct
{
    bool isRemoteFrame;      /*!< Remote frame*/
    bool isExtendedFrame;    /*!< Extended frame*/
    uint32_t id;             /*!< Rx FIFO ID filter element*/
} flexcan_id_table_t;

/*!
 * @brief FlexCAN operation modes.
 */
typedef enum
{
    FLEXCAN_NORMAL_MODE,        /*!< Normal mode or user mode  */
    FLEXCAN_LISTEN_ONLY_MODE,   /*!< Listen-only mode  */
    FLEXCAN_LOOPBACK_MODE,      /*!< Loop-back mode  */
    FLEXCAN_FREEZE_MODE,        /*!< Freeze mode  */
    FLEXCAN_DISABLE_MODE        /*!< Module disable mode  */
} flexcan_operation_modes_t;

#if FEATURE_CAN_HAS_FD
/*!
 * @brief CAN FD payload sizes (8 / 16 / 32 / 64 bytes).
 */
typedef enum
{
    FLEXCAN_PAYLOAD_SIZE_8 = 0,  /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_16,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_32,    /*!< FlexCAN message buffer payload size in bytes*/
    FLEXCAN_PAYLOAD_SIZE_64      /*!< FlexCAN message buffer payload size in bytes*/
} flexcan_fd_payload_size_t;
#endif

/*!
 * @brief Bit timing segment structure for CAN / CAN FD.
 */
typedef struct
{
    uint32_t propSeg;         /*!< Propagation segment*/
    uint32_t phaseSeg1;       /*!< Phase segment 1*/
    uint32_t phaseSeg2;       /*!< Phase segment 2*/
    uint32_t preDivider;      /*!< Clock prescaler division factor*/
    uint32_t rJumpwidth;      /*!< Resync jump width*/
} flexcan_time_segment_t;


#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
/*!
 * @brief Enhanced Rx FIFO filter matching scheme.
 */
typedef enum{
    FLEXCAN_ENAHNCE_RXFIFO_FSCH_FILTER_MASK,
    FLEXCAN_ENAHNCE_RXFIFO_FSCH_RANGE,
    FLEXCAN_ENAHNCE_RXFIFO_FSCH_DOUBLE_FILTER,
}flexcan_enchance_rx_fifo_filter_scheme_t;

/*!
 * @brief Enhanced Rx FIFO filter table element.
 */
typedef struct {
    bool isRemoteFrame;      /*!< Remote frame*/
    bool isExtendedFrame;    /*!< Extended frame*/
    flexcan_enchance_rx_fifo_filter_scheme_t filterScheme; 
    union
    {  /*PRQA S 0750*/
        struct
        {
            uint32_t filter;
            uint32_t mask;
        }scheme_filter_mask;
        struct
        {
            uint32_t filterHigh;
            uint32_t filterLow;
        }scheme_range_filter;
        struct
        {
            uint32_t filter2;
            uint32_t filter1;
        }scheme_double_filter;
    }filter_table;
} flexcan_enhance_rx_fifo_filter_table_t;
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */

/*!
 * @brief FlexCAN user configuration structure.
 *
 * Passed to FLEXCAN_DRV_Init() to configure the FlexCAN instance.
 */
typedef struct
{
    uint32_t max_num_mb;                            /*!< The maximum number of Message Buffers
                                                          */
    flexcan_rx_fifo_id_filter_num_t num_id_filters; /*!< The number of RX FIFO ID filters needed
                                                          */
    bool is_rx_fifo_needed;                         /*!< 1 if needed; 0 if not. This controls whether the Rx FIFO feature is enabled or not.
                                                          */
    flexcan_operation_modes_t flexcanMode;          /*!< User configurable FlexCAN operation modes.
                                                         */
#if FEATURE_CAN_HAS_FD
    flexcan_fd_payload_size_t payload;              /*!< The payload size of the mailboxes specified in bytes. */
    bool fd_enable;                                 /*!< Enable/Disable the Flexible Data Rate feature. */
#endif
#if FEATURE_CAN_HAS_PE_CLKSRC_SELECT
    flexcan_clk_source_t pe_clock;                  /*!< The clock source of the CAN Protocol Engine (PE). */
#endif
    flexcan_time_segment_t bitrate;                 /*!< The bitrate used for standard frames or for the arbitration phase of FD frames. */
#if FEATURE_CAN_HAS_FD
    flexcan_time_segment_t bitrate_cbt;             /*!< The bitrate used for the data phase of FD frames. */
#endif
    flexcan_rxfifo_transfer_type_t transfer_type;   /*!< Specifies if the Rx FIFO uses interrupts or DMA. */
#if FEATURE_CAN_HAS_DMA_ENABLE
    uint8_t rxFifoDMAChannel;                       /*!< Specifies the DMA channel number to be used for DMA transfers. */
#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
    uint8_t rxFifoDMALastWord;
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */
#endif
#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
    bool is_enhance_rx_fifo_needed;                 /*!< 1 if needed; 0 if not. This controls whether the use legecy Rx FIFO or enhance Rx FIFO. */
    uint32_t num_enhance_rx_fifo_filters;           /*!< The number of enhance rx fifo filters needed */
    uint32_t num_enhance_rx_fifo_extid_filters;     /*!< The number of enhance rx fifo filters needed for extended id */
    uint32_t num_enhance_rx_fifo_min_messages;
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */
} flexcan_user_config_t;

#if FEATURE_CAN_HAS_PRETENDED_NETWORKING

/*! @brief Pretended Networking ID filter */
typedef struct {
    bool extendedId;    /*!< Specifies if the ID is standard or extended. */
    bool remoteFrame;   /*!< Specifies if the frame is standard or remote. */
    uint32_t id;        /*!< Specifies the ID value. */
} flexcan_pn_id_filter_t;

/*! @brief Pretended Networking payload filter */
typedef struct {
    uint8_t dlcLow;       /*!< Specifies the lower limit of the payload size. */
    uint8_t dlcHigh;      /*!< Specifies the upper limit of the payload size. */
    uint8_t payload1[8U]; /*!< Specifies the payload to be matched (for MATCH_EXACT), the lower limit
                              (for MATCH_GEQ and MATCH_RANGE) or the upper limit (for MATCH_LEQ). */
    uint8_t payload2[8U]; /*!< Specifies the mask (for MATCH_EXACT) or the upper limit (for MATCH_RANGE). */
} flexcan_pn_payload_filter_t;

/*! @brief Pretended Networking filtering combinations */
typedef enum {
    FLEXCAN_FILTER_ID,                  /*!< Message ID filtering only */
    FLEXCAN_FILTER_ID_PAYLOAD,          /*!< Message ID and payload filtering */
    FLEXCAN_FILTER_ID_NTIMES,           /*!< Message ID filtering occurring a specified number of times */
    FLEXCAN_FILTER_ID_PAYLOAD_NTIMES    /*!< Message ID and payload filtering  occurring a specified number of times */
} flexcan_pn_filter_combination_t;

/*! @brief Pretended Networking matching schemes */
typedef enum {
    FLEXCAN_FILTER_MATCH_EXACT,   /*!< Match an exact target value. */
    FLEXCAN_FILTER_MATCH_GEQ,     /*!< Match greater than or equal to a specified target value. */
    FLEXCAN_FILTER_MATCH_LEQ,     /*!< Match less than or equal to a specified target value. */
    FLEXCAN_FILTER_MATCH_RANGE    /*!< Match inside a range, greater than or equal to a specified lower limit and smaller than or
                                      equal to a specified upper limit. */
} flexcan_pn_filter_selection_t;

/*!
 * @brief Pretended Networking configuration structure.
 */
typedef struct {
    bool wakeUpTimeout;                               /*!< Specifies if an wake up event is triggered on timeout. */
    bool wakeUpMatch;                                 /*!< Specifies if an wake up event is triggered on match. */
    uint16_t numMatches;                              /*!< The number of matches needed before generating an wake up event. */
    uint16_t matchTimeout;                            /*!< Defines a timeout value that generates an wake up event if wakeUpTimeout is true. */
    flexcan_pn_filter_combination_t filterComb;       /*!< Defines the filtering scheme used. */
    flexcan_pn_id_filter_t idFilter1;                 /*!< The configuration of the first ID filter (match exact / lower limit / upper limit). */
    flexcan_pn_id_filter_t idFilter2;                 /*!< The configuration of the second ID filter (mask / upper limit). */
    flexcan_pn_filter_selection_t idFilterType;       /*!< Defines the ID filtering scheme. */
    flexcan_pn_filter_selection_t payloadFilterType;  /*!< Defines the payload filtering scheme. */
    flexcan_pn_payload_filter_t payloadFilter;        /*!< The configuration of the payload filter. */
} flexcan_pn_config_t;

#endif /* FEATURE_CAN_HAS_PRETENDED_NETWORKING */


/*!
 * @brief User event callback function type for Tx/Rx/FIFO completion events.
 */
typedef void (*flexcan_callback_t)(uint8_t instance, flexcan_event_type_t eventType,
                                   uint32_t buffIdx, flexcan_state_t *flexcanState);

/*!
 * @brief User error callback function type for error and status events.
 */
typedef void (*flexcan_error_callback_t)(uint8_t instance, flexcan_error_event_type_t eventType,
                                         flexcan_state_t *flexcanState);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization & De-initialization
 * @{
 */

/*!
 * @brief Get the default FlexCAN configuration.
 *
 * Fills the configuration structure with sensible defaults:
 * - 16 message buffers
 * - Flexible Data Rate disabled
 * - Rx FIFO disabled
 * - Normal operation mode
 * - 8-byte payload size
 * - PE clock = Oscillator clock
 * - Bit rate ≈ 500 Kbit/s (sample point ≈ 87.5 %)
 *
 * @param[out] config  Pointer to the configuration structure to populate.
 * @return Actual bit rate (Hz) computed for the PE clock frequency.
 */
uint32_t FLEXCAN_DRV_GetDefaultConfig(flexcan_user_config_t *config);

/*!
 * @brief Initialize a FlexCAN peripheral instance.
 *
 * Configures the FlexCAN module according to the user configuration,
 * enables interrupts, and stores the runtime state.
 *
 * @param[in]  instance  FlexCAN peripheral instance index (0-based).
 * @param[out] state     Pointer to the driver state structure (allocated by caller).
 * @param[in]  data      Pointer to the user configuration structure.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if a message buffer index is invalid;
 *         STATUS_ERROR if another error occurred.
 * @pre  The FlexCAN peripheral clock must be enabled.
 * @post The FlexCAN instance is ready for Tx/Rx operations.
 */
status_t FLEXCAN_DRV_Init(
    uint8_t instance,
    flexcan_state_t *state,
    const flexcan_user_config_t *data);

/*!
 * @brief Shut down a FlexCAN peripheral instance.
 *
 * Disables all FlexCAN interrupts, disables the module, and releases
 * internal resources.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @return STATUS_SUCCESS if successful;
 *         STATUS_ERROR if de-initialization failed.
 */
status_t FLEXCAN_DRV_Deinit(uint8_t instance);

/*@}*/

/*!
 * @name Bit Rate Configuration
 * @{
 */

/*!
 * @brief Set the bit timing for standard frames or the arbitration phase of FD frames.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] bitrate   Pointer to the bit timing segment structure.
 */
void FLEXCAN_DRV_SetBitrate(uint8_t instance, const flexcan_time_segment_t *bitrate);

#if FEATURE_CAN_HAS_FD

/*!
 * @brief Set the bit timing for the data phase of FD frames (BRS enabled).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] bitrate   Pointer to the bit timing segment structure.
 */
void FLEXCAN_DRV_SetBitrateCbt(uint8_t instance, const flexcan_time_segment_t *bitrate);

#endif

/*!
 * @brief Get the current bit timing for standard frames / arbitration phase.
 *
 * @param[in]  instance  FlexCAN peripheral instance index (0-based).
 * @param[out] bitrate   Pointer to store the current bit timing settings.
 */
void FLEXCAN_DRV_GetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate);

#if FEATURE_CAN_HAS_FD

/*!
 * @brief Get the current bit timing for FD data phase (BRS enabled).
 *
 * @param[in]  instance  FlexCAN peripheral instance index (0-based).
 * @param[out] bitrate   Pointer to store the current bit timing settings.
 */
void FLEXCAN_DRV_GetBitrateFD(uint8_t instance, flexcan_time_segment_t *bitrate);

#endif

/*@}*/

/*!
 * @name Rx Mask Configuration
 * @{
 */

/*!
 * @brief Set the Rx acceptance mask type (global or individual).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] type      Mask type: FLEXCAN_RX_MASK_GLOBAL or FLEXCAN_RX_MASK_INDIVIDUAL.
 */
void FLEXCAN_DRV_SetRxMaskType(uint8_t instance, flexcan_rx_mask_type_t type);

/*!
 * @brief Set the Rx FIFO global acceptance mask.
 *
 * This mask is applied to all Rx FIFO filter elements regardless of format.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] id_type   Standard or extended ID mask type.
 * @param[in] mask      Mask value. In FIFO mode with Format A or B, bit 31
 *                      encodes RTR check and bit 30 encodes IDE check.
 *                      For Format C, bits 31 and 30 are ignored.
 */
void FLEXCAN_DRV_SetRxFifoGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Set the Rx MB global acceptance mask (standard or extended).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] id_type   Standard or extended ID.
 * @param[in] mask      Mask value.
 */
void FLEXCAN_DRV_SetRxMbGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Set the Rx MB 14 acceptance mask (standard or extended).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] id_type   Standard or extended ID.
 * @param[in] mask      Mask value.
 */
void FLEXCAN_DRV_SetRxMb14Mask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Set the Rx MB 15 acceptance mask (standard or extended).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] id_type   Standard or extended ID.
 * @param[in] mask      Mask value.
 */
void FLEXCAN_DRV_SetRxMb15Mask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Set an individual Rx acceptance mask for a specific MB.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] id_type   Standard or extended ID.
 * @param[in] mb_idx    Message buffer index.
 * @param[in] mask      Mask value. In FIFO mode with Format A or B, bit 31
 *                      encodes RTR check and bit 30 encodes IDE check.
 *                      For Format C, bits 31 and 30 are ignored.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid.
 */
status_t FLEXCAN_DRV_SetRxIndividualMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint8_t mb_idx,
    uint32_t mask);

/*!
 * @brief Set the Rx FIFO global mask using a raw (pre-computed) value.
 *
 * The caller is responsible for computing the mask value according to the
 * reference manual format.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mask      Raw mask value.
 */
void FLEXCAN_DRV_SetRawRxFifoGlobalMask(
    uint8_t instance,
    uint32_t mask);

/*!
 * @brief Set an individual Rx mask using a raw (pre-computed) value.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @param[in] mask      Raw mask value.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid.
 */
status_t FLEXCAN_DRV_SetRawRxIndividualMask(
    uint8_t instance,
    uint8_t mb_idx,
    uint32_t mask);

/*@}*/

#if FEATURE_CAN_HAS_FD

/*!
 * @name Transceiver Delay Compensation (FD only)
 * @{
 */

/*!
 * @brief Enable/disable Transceiver Delay Compensation and set the TDC offset.
 *
 * The offset value is added to the measured transceiver loop delay to define
 * the position of the delayed comparison point when BRS is active.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] enable    true to enable TDC, false to disable.
 * @param[in] offset    TDC offset value (in CAN clock cycles).
 */
void FLEXCAN_DRV_SetTDCOffset(uint8_t instance, bool enable, uint8_t offset);

/*!
 * @brief Get the measured Transceiver Delay Compensation value.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @return Measured TDC value (transceiver loop delay + offset).
 */
uint8_t FLEXCAN_DRV_GetTDCValue(uint8_t instance);

/*!
 * @brief Check whether the TDC Fail flag is set.
 *
 * When true, the TDC mechanism is out of range and cannot compensate
 * the transceiver loop delay.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @retval true   TDC measurement failed (out of range).
 * @retval false  TDC operating normally.
 */
bool FLEXCAN_DRV_GetTDCFail(uint8_t instance);

/*!
 * @brief Clear the TDC Fail flag.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 */
void FLEXCAN_DRV_ClearTDCFail(uint8_t instance);

/*@}*/

#endif

/*!
 * @name Transmit Configuration & Data Transfer
 * @{
 */

/*!
 * @brief Configure a message buffer for transmission.
 *
 * Sets up the specified MB with the given data info and message ID,
 * and marks it as inactive (ready for a subsequent Send call).
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @param[in] tx_info   Pointer to the data information structure.
 * @param[in] msg_id    CAN message identifier.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid.
 */
status_t FLEXCAN_DRV_ConfigTxMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id);

/*!
 * @brief Configure a Tx message buffer for automatic remote frame response.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @param[in] tx_info   Pointer to the data information structure.
 * @param[in] msg_id    CAN message identifier.
 * @param[in] mb_data   Pointer to the response payload data.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid.
 */
status_t FLEXCAN_DRV_ConfigRemoteResponseMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data);

/*!
 * @brief Send a CAN frame (blocking with timeout).
 *
 * Transmits a CAN frame using the specified message buffer. The function
 * blocks until the frame is sent or the timeout expires.
 *
 * @param[in] instance    FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx      Message buffer index.
 * @param[in] tx_info     Pointer to the data information structure.
 * @param[in] msg_id      CAN message identifier.
 * @param[in] mb_data     Pointer to the payload data.
 * @param[in] timeout_ms  Timeout in milliseconds.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid;
 *         STATUS_BUSY if the MB is already in use;
 *         STATUS_TIMEOUT if the timeout expired.
 */
status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data,
    uint32_t timeout_ms);

/*!
 * @brief Send a CAN frame (non-blocking, callback-based).
 *
 * Transmits a CAN frame using the specified message buffer. The function
 * returns immediately. If an event callback is installed, it will be
 * invoked with FLEXCAN_EVENT_TX_COMPLETE upon successful transmission.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @param[in] tx_info   Pointer to the data information structure.
 * @param[in] msg_id    CAN message identifier.
 * @param[in] mb_data   Pointer to the payload data.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid;
 *         STATUS_BUSY if the MB is already in use.
 */
status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    const uint8_t *mb_data);

/*@}*/

/*!
 * @name Receive Configuration & Data Transfer
 * @{
 */

/*!
 * @brief Configure a message buffer for reception.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @param[in] rx_info   Pointer to the data information structure.
 * @param[in] msg_id    CAN message identifier to accept.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_CAN_BUFF_OUT_OF_RANGE if the MB index is invalid.
 */
status_t FLEXCAN_DRV_ConfigRxMb(
    uint8_t instance,
    uint8_t mb_idx,
    const flexcan_data_info_t *rx_info,
    uint32_t msg_id);

/*!
 * @brief FlexCAN Rx FIFO field configuration
 *
 * @note The number of elements in the ID filter table is defined by the
 *       following formula:
 *       - for format A: the number of Rx FIFO ID filters
 *       - for format B: twice the number of Rx FIFO ID filters
 *       - for format C: four times the number of Rx FIFO ID filters
 *       The user must provide the exact number of elements in order to avoid
 *       any misconfiguration.
 *
 *       Each element in the ID filter table specifies an ID to be used as
 *       acceptance criteria for the FIFO as follows:
 *       - for format A: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, bits
 *         28 to 0 are used.
 *       - for format B: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, only
 *         the 14 most significant bits (28 to 15) of the ID are compared to the
 *         14 most significant bits (28 to 15) of the received ID.
 *       - for format C: In both standard and extended frame formats, only the 8
 *         most significant bits (7 to 0 for standard, 28 to 21 for extended) of
 *         the ID are compared to the 8 most significant bits (7 to 0 for
 *         standard, 28 to 21 for extended) of the received ID.
 *
 * @param   instance           A FlexCAN instance number
 * @param   id_format          The format of the Rx FIFO ID Filter Table Elements
 * @param   id_filter_table    The ID filter table elements which contain RTR
 *                             bit, IDE bit, and Rx message ID
 */
void FLEXCAN_DRV_ConfigRxFifo(
    uint8_t instance,
    flexcan_rx_fifo_id_element_format_t id_format,
    const flexcan_id_table_t *id_filter_table);


#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
/*!
 * @brief Configure Enhanced Rx FIFO ID filter table elements.
 *
 * @param[in] instance               FlexCAN peripheral instance index (0-based).
 * @param[in] id_filter_table        Pointer to the Enhanced Rx FIFO filter table.
 * @param[in] id_filter_table_length Number of elements in the filter table.
 */
void FLEXCAN_DRV_ConfigEnhanceRxFifo(
    uint8_t instance,
    const flexcan_enhance_rx_fifo_filter_table_t *id_filter_table,
    uint8_t id_filter_table_length);
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */

/*!
 * @brief Receives a CAN frame using the specified message buffer, in a blocking manner.
 *
 * This function receives a CAN frame using a configured message buffer. The function
 * blocks until either a frame was received, or the specified timeout expired.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @param   timeout_ms A timeout for the transfer in milliseconds.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy;
 *          STATUS_TIMEOUT if the timeout is reached
 */
status_t FLEXCAN_DRV_ReceiveBlocking(
    uint8_t instance,
    uint8_t mb_idx,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

/*!
 * @brief Receives a CAN frame using the specified message buffer.
 *
 * This function receives a CAN frame using a configured message buffer. The function
 * returns immediately. If a callback is installed, it will be invoked after
 * the frame was received and read into the specified buffer.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_CAN_BUFF_OUT_OF_RANGE if the index of a message buffer is invalid;
 *          STATUS_BUSY if a resource is busy
 */
status_t FLEXCAN_DRV_Receive(
    uint8_t instance,
    uint8_t mb_idx,
    flexcan_msgbuff_t *data);

/*!
 * @brief Receives a CAN frame using the message FIFO, in a blocking manner.
 *
 * This function receives a CAN frame using the Rx FIFO. The function blocks until
 * either a frame was received, or the specified timeout expired.
 *
 * @param   instance    A FlexCAN instance number
 * @param   data        The FlexCAN receive message buffer data.
 * @param   timeout_ms  A timeout for the transfer in milliseconds.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_BUSY if a resource is busy;
 *          STATUS_TIMEOUT if the timeout is reached;
 *          STATUS_ERROR if other error occurred
 */
status_t FLEXCAN_DRV_RxFifoBlocking(
    uint8_t instance,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

/*!
 * @brief Receives a CAN frame using the message FIFO.
 *
 * This function receives a CAN frame using the Rx FIFO. The function returns
 * immediately. If a callback is installed, it will be invoked after the frame
 * was received and read into the specified buffer.
 *
 * @param   instance    A FlexCAN instance number
 * @param   data        The FlexCAN receive message buffer data.
 * @return  STATUS_SUCCESS if successful;
 *          STATUS_BUSY if a resource is busy;
 *          STATUS_ERROR if other error occurred
 */
status_t FLEXCAN_DRV_RxFifo(
    uint8_t instance,
    flexcan_msgbuff_t *data);


#if FEATURE_CAN_HAS_ENHANCE_RX_FIFO
/*!
 * @brief Receive a CAN frame via the Enhanced Rx FIFO (non-blocking).
 *
 * @param[in]  instance  FlexCAN peripheral instance index (0-based).
 * @param[out] data      Pointer to the message buffer to store the received frame.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_BUSY if a transfer is already in progress;
 *         STATUS_ERROR if Enhanced Rx FIFO is not enabled.
 */
status_t FLEXCAN_DRV_EnhanceRxFifo(
    uint8_t instance,
    flexcan_msgbuff_t *data);
#endif /* FEATURE_CAN_HAS_ENHANCE_RX_FIFO */

/*@}*/

/*!
 * @name Transfer Status & Error
 * @{
 */

/*!
 * @brief Abort an ongoing transfer on the specified message buffer.
 *
 * @param[in] instance  FlexCAN peripheral instance index (0-based).
 * @param[in] mb_idx    Message buffer index.
 * @return STATUS_SUCCESS if the transfer was aborted;
 *         STATUS_CAN_NO_TRANSFER_IN_PROGRESS if no transfer was active.
 */
status_t FLEXCAN_DRV_AbortTransfer(uint8_t instance, uint8_t mb_idx);

/*!
 * @brief Returns whether the previous FlexCAN transfer has finished.
 *
 * When performing an async transfer, call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success).
 *
 * @param instance The FlexCAN instance number.
 * @param mb_idx The index of the message buffer.
 * @return STATUS_SUCCESS if successful;
 *         STATUS_BUSY if a resource is busy;
 *         STATUS_ERROR in case of a DMA error transfer;
 */
status_t FLEXCAN_DRV_GetTransferStatus(uint8_t instance, uint8_t mb_idx);

/*!
 * @brief Returns reported error conditions.
 *
 * Reports various error conditions detected in the reception and transmission of a CAN frame
 * and some general status of the device.
 *
 * @param instance The FlexCAN instance number.
 * @return value of the Error and Status 1 register;
 */
uint32_t FLEXCAN_DRV_GetErrorStatus(uint8_t instance);

/*@}*/

/*!
 * @name Callback & Interrupt Management
 * @{
 */

/*!
 * @brief Installs a callback function for the IRQ handler.
 *
 * @param instance The FlexCAN instance number.
 * @param callback The callback function.
 * @param callbackParam User parameter passed to the callback function through the state parameter.
 */
void FLEXCAN_DRV_InstallEventCallback(uint8_t instance,
                                      flexcan_callback_t callback,
                                      void *callbackParam);

/*!
 * @brief Installs an error callback function for the IRQ handler and enables error interrupts.
 *
 * @param instance The FlexCAN instance number.
 * @param callback The error callback function.
 * @param callbackParam User parameter passed to the error callback function through the state
 *                      parameter.
 */
void FLEXCAN_DRV_InstallErrorCallback(uint8_t instance,
                                      flexcan_error_callback_t callback,
                                      void *callbackParam);

#if FEATURE_CAN_HAS_WAKE_UP_IRQ
#if FEATURE_CAN_HAS_SELF_WAKE_UP
/*!
 * @brief Enable self wake up.
 *
 * @param   instance    The FlexCAN instance number.
 */
void FLEXCAN_DRV_EnableSelfWakeUp(uint8_t instance);

/*!
 * @brief Disable self wake up.
 *
 * @param   instance    The FlexCAN instance number.
 */
void FLEXCAN_DRV_DisableSelfWakeUp(uint8_t instance);
#endif
#endif

/*@}*/

#if FEATURE_CAN_HAS_PRETENDED_NETWORKING

/*!
 * @name Pretended Networking
 * @{
 */

/*!
 * @brief Configures Pretended Networking settings.
 *
 * @param instance The FlexCAN instance number.
 * @param enable Enable/Disable Pretended Networking mode.
 * @param pnConfig Pointer to the Pretended Networking configuration structure.
 */
void FLEXCAN_DRV_ConfigPN(uint8_t instance, bool enable, const flexcan_pn_config_t *pnConfig);

/*!
 * @brief Extracts one of the frames which triggered the wake up event.
 *
 * @param   instance    The FlexCAN instance number.
 * @param   wmbIndex  The index of the message buffer to be extracted.
 * @param   wmb  Pointer to the message buffer structure where the frame will be saved.
 */
void FLEXCAN_DRV_GetWMB(uint8_t instance, uint8_t wmbIndex, flexcan_msgbuff_t *wmb);

/*@}*/

#endif /* FEATURE_CAN_HAS_PRETENDED_NETWORKING */

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* FLEXCAN_DRIVER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
