#ifndef __CPS32K21X_CAN_H__
#define __CPS32K21X_CAN_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "cps32k21x.h"
#include "cps32k21x_rcc.h"


/* @brief CAN interrupt enable all interrupt macro */
#define CAN_IE_ALL_ENABLE_Mask      (CAN_CTRL1_EIE_Mask  | CAN_CTRL1_TSIE_Mask | CAN_CTRL1_TPIE_Mask |\
                                    CAN_CTRL1_RAFIE_Mask | CAN_CTRL1_RFIE_Mask | CAN_CTRL1_ROIE_Mask |\
                                    CAN_CTRL1_RIE_Mask   | CAN_CTRL1_EPIE_Mask | CAN_CTRL1_ALIE_Mask | CAN_CTRL1_BEIE_Mask)

/*!
* @brief CAN instance index macro
*/
//#define CAN_INDEX(CANx)        ((uint8_t)(((uint32_t)(CANx) - CAN0_BASE) >> 10))

#define CAN_INDEX(CANx)        (((CANx) == (CAN0)) ? (0) : (1))

#define CAN_MAX_FILTER_NUM     (16U)    /*<! CAN最大滤波器数量 */


/* @brief CAN transmit buffer full macro */
#define CAN_TRANSMIT_BUFFER_FULL   (0x03UL)

#define CAN_INSTANCE_MAX           (1UL)       /*!< Number of instances of the CAN module  */

#define RCC_CAN0_TIMCLK_DIV_Pos    (0UL)       /*!< CAN0_TIMCLK_DIV (Bit 0)                */
#define RCC_CAN0_TIMCLK_DIV_Mask   (0x03UL)    /*!< CAN0_TIMCLK_DIV (Bitfield-Mask: 0x03)  */
    

/* ==================================  TBUF/RBUF  ========================================= */
#define CAN_INFO_ID_Pos       (0UL)                  /*!< ID (Bit 0)                        */
#define CAN_INFO_ID_Mask      (0x1FFFFFFFUL)         /*!< ID (Bitfield-Mask: 0x1FFFFFFF)    */
#define CAN_INFO_ESI_Pos      (31UL)                 /*!< ESI (Bit 31)，即错误状态指示       */
#define CAN_INFO_ESI_Mask     (0x80000000UL)         /*!< ESI (Bitfield-Mask: 0x01)         */
#define CAN_INFO_DLC_Pos      (0UL)                  /*!< DLC (Bit 0)                       */
#define CAN_INFO_DLC_Mask     (0x0FUL)               /*!< DLC (Bitfield-Mask: 0x0F)         */
#define CAN_INFO_BRS_Pos      (4UL)                  /*!< BRS (Bit 4)                       */
#define CAN_INFO_BRS_Mask     (0x10UL)               /*!< BRS (Bitfield-Mask: 0x01)         */
#define CAN_INFO_FDF_Pos      (5UL)                  /*!< FDF (Bit 5)                       */
#define CAN_INFO_FDF_Mask     (0x20UL)               /*!< FDF (Bitfield-Mask: 0x01)         */
#define CAN_INFO_RTR_Pos      (6UL)                  /*!< RTR (Bit 6)                       */
#define CAN_INFO_RTR_Mask     (0x40UL)               /*!< RTR (Bitfield-Mask: 0x01)         */
#define CAN_INFO_IDE_Pos      (7UL)                  /*!< IDE (Bit 7)                       */
#define CAN_INFO_IDE_Mask     (0x80UL)               /*!< IDE (Bitfield-Mask: 0x01)         */

/* ====================================  CTRL0  ===========-----------===================== */
#define CAN_CTRL0_BUSOFF_Pos      (0UL)              /*!< BUSOFF (Bit 0)                    */
#define CAN_CTRL0_BUSOFF_Mask     (0x1UL)            /*!< BUSOFF (Bitfield-Mask: 0x01)      */
#define CAN_CTRL0_TACTIVE_Pos     (1UL)              /*!< TACTIVE (Bit 1)                   */
#define CAN_CTRL0_TACTIVE_Mask    (0x2UL)            /*!< TACTIVE (Bitfield-Mask: 0x01)     */
#define CAN_CTRL0_RACTIVE_Pos     (2UL)              /*!< RACTIVE (Bit 2)                   */
#define CAN_CTRL0_RACTIVE_Mask    (0x4UL)            /*!< RACTIVE (Bitfield-Mask: 0x01)     */
#define CAN_CTRL0_TSSS_Pos        (3UL)              /*!< TSSS (Bit 3)                      */
#define CAN_CTRL0_TSSS_Mask       (0x8UL)            /*!< TSSS (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_TPSS_Pos        (4UL)              /*!< TPSS (Bit 4)                      */
#define CAN_CTRL0_TPSS_Mask       (0x10UL)           /*!< TPSS (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_LBMI_Pos        (5UL)              /*!< LBMI (Bit 5)                      */
#define CAN_CTRL0_LBMI_Mask       (0x20UL)           /*!< LBMI (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_LBME_Pos        (6UL)              /*!< LBME (Bit 6)                      */
#define CAN_CTRL0_LBME_Mask       (0x40UL)           /*!< LBME (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_RESET_Pos       (7UL)              /*!< RESET (Bit 7)                     */
#define CAN_CTRL0_RESET_Mask      (0x80UL)           /*!< RESET (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_TSA_Pos         (8UL)              /*!< TSA (Bit 8)                       */
#define CAN_CTRL0_TSA_Mask        (0x100UL)          /*!< TSA (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_TSALL_Pos       (9UL)              /*!< TSALL (Bit 9)                     */
#define CAN_CTRL0_TSALL_Mask      (0x200UL)          /*!< TSALL (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_TSONE_Pos       (10UL)             /*!< TSONE (Bit 10)                    */
#define CAN_CTRL0_TSONE_Mask      (0x400UL)          /*!< TSONE (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_TPA_Pos         (11UL)             /*!< TPA (Bit 11)                      */
#define CAN_CTRL0_TPA_Mask        (0x800UL)          /*!< TPA (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_TPE_Pos         (12UL)             /*!< TPE (Bit 12)                      */
#define CAN_CTRL0_TPE_Mask        (0x1000UL)         /*!< TPE (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_STBY_Pos        (13UL)             /*!< STBY (Bit 13)                     */
#define CAN_CTRL0_STBY_Mask       (0x2000UL)         /*!< STBY (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_LOM_Pos         (14UL)             /*!< LOM (Bit 14)                      */
#define CAN_CTRL0_LOM_Mask        (0x4000UL)         /*!< LOM (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_TBSEL_Pos       (15UL)             /*!< TBSEL (Bit 15)                    */
#define CAN_CTRL0_TBSEL_Mask      (0x8000UL)         /*!< TBSEL (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_TSSTAT_Pos      (16UL)             /*!< TSSTAT (Bit 16)                   */
#define CAN_CTRL0_TSSTAT_Mask     (0x30000UL)        /*!< TSSTAT (Bitfield-Mask: 0x03)      */
#define CAN_CTRL0_TSMODE_Pos      (21UL)             /*!< TSMODE (Bit 21)                   */
#define CAN_CTRL0_TSMODE_Mask     (0x200000UL)       /*!< TSMODE (Bitfield-Mask: 0x01)      */
#define CAN_CTRL0_TSNEXT_Pos      (22UL)             /*!< TSNEXT (Bit 22)                   */
#define CAN_CTRL0_TSNEXT_Mask     (0x400000UL)       /*!< TSNEXT (Bitfield-Mask: 0x01)      */
#define CAN_CTRL0_FDISO_Pos       (23UL)             /*!< FDISO (Bit 23)                    */
#define CAN_CTRL0_FDISO_Mask      (0x800000UL)       /*!< FDISO (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_RSTAT_Pos       (24UL)             /*!< RSTAT (Bit 24)                    */
#define CAN_CTRL0_RSTAT_Mask      (0x3000000UL)      /*!< RSTAT (Bitfield-Mask: 0x03)       */
#define CAN_CTRL0_RBALL_Pos       (27UL)             /*!< RBALL (Bit 27)                    */
#define CAN_CTRL0_RBALL_Mask      (0x8000000UL)      /*!< RBALL (Bitfield-Mask: 0x01)       */
#define CAN_CTRL0_RREL_Pos        (28UL)             /*!< RREL (Bit 28)                     */
#define CAN_CTRL0_RREL_Mask       (0x10000000UL)     /*!< RREL (Bitfield-Mask: 0x01)        */
#define CAN_CTRL0_ROV_Pos         (29UL)             /*!< ROV (Bit 29)                      */
#define CAN_CTRL0_ROV_Mask        (0x20000000UL)     /*!< ROV (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_ROM_Pos         (30UL)             /*!< ROM (Bit 30)                      */
#define CAN_CTRL0_ROM_Mask        (0x40000000UL)     /*!< ROM (Bitfield-Mask: 0x01)         */
#define CAN_CTRL0_SACK_Pos        (31UL)             /*!< SACK (Bit 31)                     */
#define CAN_CTRL0_SACK_Mask       (0x80000000UL)     /*!< SACK (Bitfield-Mask: 0x01)        */

/* =====================================  CTRL1  ========================================== */
#define CAN_CTRL1_TSFF_Pos        (0UL)              /*!< TSFF (Bit 0)                      */
#define CAN_CTRL1_TSFF_Mask       (0x1UL)            /*!< TSFF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_EIE_Pos         (1UL)              /*!< EIE (Bit 1)                       */
#define CAN_CTRL1_EIE_Mask        (0x2UL)            /*!< EIE (Bitfield-Mask: 0x01)         */
#define CAN_CTRL1_TSIE_Pos        (2UL)              /*!< TSIE (Bit 2)                      */
#define CAN_CTRL1_TSIE_Mask       (0x4UL)            /*!< TSIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_TPIE_Pos        (3UL)              /*!< TPIE (Bit 3)                      */
#define CAN_CTRL1_TPIE_Mask       (0x8UL)            /*!< TPIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_RAFIE_Pos       (4UL)              /*!< RAFIE (Bit 4)                     */
#define CAN_CTRL1_RAFIE_Mask      (0x10UL)           /*!< RAFIE (Bitfield-Mask: 0x01)       */
#define CAN_CTRL1_RFIE_Pos        (5UL)              /*!< RFIE (Bit 5)                      */
#define CAN_CTRL1_RFIE_Mask       (0x20UL)           /*!< RFIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_ROIE_Pos        (6UL)              /*!< ROIE (Bit 6)                      */
#define CAN_CTRL1_ROIE_Mask       (0x40UL)           /*!< ROIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_RIE_Pos         (7UL)              /*!< RIE (Bit 7)                       */
#define CAN_CTRL1_RIE_Mask        (0x80UL)           /*!< RIE (Bitfield-Mask: 0x01)         */
#define CAN_CTRL1_AIF_Pos         (8UL)              /*!< AIF (Bit 8)                       */
#define CAN_CTRL1_AIF_Mask        (0x100UL)          /*!< AIF (Bitfield-Mask: 0x01)         */
#define CAN_CTRL1_EIF_Pos         (9UL)              /*!< EIF (Bit 9)                       */
#define CAN_CTRL1_EIF_Mask        (0x200UL)          /*!< EIF (Bitfield-Mask: 0x01)         */
#define CAN_CTRL1_TSIF_Pos        (10UL)             /*!< TSIF (Bit 10)                     */
#define CAN_CTRL1_TSIF_Mask       (0x400UL)          /*!< TSIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_TPIF_Pos        (11UL)             /*!< TPIF (Bit 11)                     */
#define CAN_CTRL1_TPIF_Mask       (0x800UL)          /*!< TPIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_RAFIF_Pos       (12UL)             /*!< RAFIF (Bit 12)                    */
#define CAN_CTRL1_RAFIF_Mask      (0x1000UL)         /*!< RAFIF (Bitfield-Mask: 0x01)       */
#define CAN_CTRL1_RFIF_Pos        (13UL)             /*!< RFIF (Bit 13)                     */
#define CAN_CTRL1_RFIF_Mask       (0x2000UL)         /*!< RFIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_ROIF_Pos        (14UL)             /*!< ROIF (Bit 14)                     */
#define CAN_CTRL1_ROIF_Mask       (0x4000UL)         /*!< ROIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_RIF_Pos         (15UL)             /*!< RIF (Bit 15)                      */
#define CAN_CTRL1_RIF_Mask        (0x8000UL)         /*!< RIF (Bitfield-Mask: 0x01)         */
#define CAN_CTRL1_BEIF_Pos        (16UL)             /*!< BEIF (Bit 16)                     */
#define CAN_CTRL1_BEIF_Mask       (0x10000UL)        /*!< BEIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_BEIE_Pos        (17UL)             /*!< BEIE (Bit 17)                     */
#define CAN_CTRL1_BEIE_Mask       (0x20000UL)        /*!< BEIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_ALIF_Pos        (18UL)             /*!< ALIF (Bit 18)                     */
#define CAN_CTRL1_ALIF_Mask       (0x40000UL)        /*!< ALIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_ALIE_Pos        (19UL)             /*!< ALIE (Bit 19)                     */
#define CAN_CTRL1_ALIE_Mask       (0x80000UL)        /*!< ALIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_EPIF_Pos        (20UL)             /*!< EPIF (Bit 20)                     */
#define CAN_CTRL1_EPIF_Mask       (0x100000UL)       /*!< EPIF (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_EPIE_Pos        (21UL)             /*!< EPIE (Bit 21)                     */
#define CAN_CTRL1_EPIE_Mask       (0x200000UL)       /*!< EPIE (Bitfield-Mask: 0x01)        */
#define CAN_CTRL1_EPASS_Pos       (22UL)             /*!< EPASS (Bit 22)                    */
#define CAN_CTRL1_EPASS_Mask      (0x400000UL)       /*!< EPASS (Bitfield-Mask: 0x01)       */
#define CAN_CTRL1_EWARN_Pos       (23UL)             /*!< EWARN (Bit 23)                    */
#define CAN_CTRL1_EWARN_Mask      (0x800000UL)       /*!< EWARN (Bitfield-Mask: 0x01)       */
#define CAN_CTRL1_EWL_Pos         (24UL)             /*!< EWL (Bit 24)                      */
#define CAN_CTRL1_EWL_Mask        (0xf000000UL)      /*!< EWL (Bitfield-Mask: 0x0f)         */
#define CAN_CTRL1_AFWL_Pos        (28UL)             /*!< AFWL (Bit 28)                     */
#define CAN_CTRL1_AFWL_Mask       (0xf0000000UL)     /*!< AFWL (Bitfield-Mask: 0x0f)        */

/* ==================================  SBITRATE  ========================================== */
#define CAN_BITRATE_SEG_1_Pos     (0UL)              /*!< SEG_1 (Bit 0)                     */
#define CAN_BITRATE_SEG_1_Mask    (0xffUL)           /*!< SEG_1 (Bitfield-Mask: 0xff)       */
#define CAN_BITRATE_SEG_2_Pos     (8UL)              /*!< SEG_2 (Bit 8)                     */
#define CAN_BITRATE_SEG_2_Mask    (0x7f00UL)         /*!< SEG_2 (Bitfield-Mask: 0x7f)       */
#define CAN_BITRATE_SJW_Pos       (16UL)             /*!< SJW (Bit 16)                      */
#define CAN_BITRATE_SJW_Mask      (0x7f0000UL)       /*!< SJW (Bitfield-Mask: 0x7f)         */
#define CAN_BITRATE_PRESC_Pos     (24UL)             /*!< PRESC (Bit 24)                    */
#define CAN_BITRATE_PRESC_Mask    (0xff000000UL)     /*!< PRESC (Bitfield-Mask: 0xff)       */
                                    
/* ==================================  ERRINFO  =========================================== */
#define CAN_ERRINFO_ALC_Pos       (0UL)              /*!< ALC (Bit 0)                       */
#define CAN_ERRINFO_ALC_Mask      (0x1fUL)           /*!< ALC (Bitfield-Mask: 0x1f)         */
#define CAN_ERRINFO_KOER_Pos      (5UL)              /*!< KOER (Bit 5)                      */
#define CAN_ERRINFO_KOER_Mask     (0xe0UL)           /*!< KOER (Bitfield-Mask: 0x07)        */
#define CAN_ERRINFO_SSPOFF_Pos    (8UL)              /*!< SSPOFF (Bit 8)                    */
#define CAN_ERRINFO_SSPOFF_Mask   (0x7f00UL)         /*!< SSPOFF (Bitfield-Mask: 0x7f)      */
#define CAN_ERRINFO_TDCEN_Pos     (15UL)             /*!< TDCEN (Bit 15)                    */
#define CAN_ERRINFO_TDCEN_Mask    (0x8000UL)         /*!< TDCEN (Bitfield-Mask: 0x01)       */
#define CAN_ERRINFO_RECNT_Pos     (16UL)             /*!< RECNT (Bit 16)                    */
#define CAN_ERRINFO_RECNT_Mask    (0xff0000UL)       /*!< RECNT (Bitfield-Mask: 0xff)       */
#define CAN_ERRINFO_TECNT_Pos     (24UL)             /*!< TECNT (Bit 24)                    */
#define CAN_ERRINFO_TECNT_Mask    (0xff000000UL)     /*!< TECNT (Bitfield-Mask: 0xff)       */

/* ==================================  ACFCTRL  =========================================== */
#define CAN_ACFCTRL_ACFADR_Pos      (0UL)            /*!< ACFADR (Bit 0)                    */
#define CAN_ACFCTRL_ACFADR_Mask     (0xfUL)          /*!< ACFADR (Bitfield-Mask: 0x0f)      */
#define CAN_ACFCTRL_SELMASK_Pos     (5UL)            /*!< SELMASK (Bit 5)                   */
#define CAN_ACFCTRL_SELMASK_Mask    (0x20UL)         /*!< SELMASK (Bitfield-Mask: 0x01)     */
#define CAN_ACFCTRL_TIMEEN_Pos      (8UL)            /*!< TIMEEN (Bit 8)                    */
#define CAN_ACFCTRL_TIMEEN_Mask     (0x100UL)        /*!< TIMEEN (Bitfield-Mask: 0x01)      */
#define CAN_ACFCTRL_TIMEPOS_Pos     (9UL)            /*!< TIMEPOS (Bit 9)                   */
#define CAN_ACFCTRL_TIMEPOS_Mask    (0x200UL)        /*!< TIMEPOS (Bitfield-Mask: 0x01)     */
#define CAN_ACFCTRL_ACFEN_Pos       (16UL)           /*!< ACFEN (Bit 16)                    */
#define CAN_ACFCTRL_ACFEN_Mask      (0xffff0000UL)   /*!< ACFEN (Bitfield-Mask: 0xffff)     */

/* ====================================  ACF  ============================================= */
#define CAN_ACF_ACODE_Pos      (0UL)                 /*!< ACODE (Bit 0)                     */
#define CAN_ACF_ACODE_Mask     (0x1fffffffUL)        /*!< ACODE (Bitfield-Mask: 0x1fffffff) */
#define CAN_ACF_AIDE_Pos       (29UL)                /*!< AIDE (Bit 29)                     */
#define CAN_ACF_AIDE_Mask      (0x20000000UL)        /*!< AIDE (Bitfield-Mask: 0x01)        */
#define CAN_ACF_AIDEE_Pos      (30UL)                /*!< AIDEE (Bit 30)                    */
#define CAN_ACF_AIDEE_Mask     (0x40000000UL)        /*!< AIDEE (Bitfield-Mask: 0x01)       */

/* ===================================  VERTION  ========================================== */
#define CAN_VERSION_VERSION_Pos     (0UL)            /*!< VERSION (Bit 0)                   */
#define CAN_VERSION_VERSION_Mask    (0xffffUL)       /*!< VERSION (Bitfield-Mask: 0xffff)   */

/* ============================================  Define  ============================================ */
#define MAX_CAN_WAIT_TIMES         (100000UL)       /* default wait times, or user define */
#define CAN_RECEIVE_FIFO_COUNT     (7UL)            /* CAN receive fifo count */
#define CAN_TRANSMIT_FIFO_COUNT    (4UL)            /* CAN transmit fifo count (1 PTB + 3 STB) */
#define CAN_IRQ_FLAG_Mask          (0x00D5FF00UL)   /* CAN interrupt flag mask macro */


typedef struct 
{
    uint32_t  ID;        /*!< CAN identifier */
    uint32_t  RTS;       /*!< Receive time stamps */
    uint8_t   ESI;       /*!< Transmit time-stamp enable or error state indicator */
    uint8_t   DLC;       /*!< Data length code */
    uint8_t   BRS;       /*!< Bit rate switch */
    uint8_t   FDF;       /*!< FD format indicator */
    uint8_t   RTR;       /*!< Remote transmission request */
    uint8_t   IDE;       /*!< Identifier extension */
    uint8_t*  DATA;      /*!< Data pointer */
} CAN_MsgInfoType;


/*!< Bitrate = CAN_CLOCK / ((S_PRESC + 1) * (1 + (S_SEG_1 + 1) + (S_SEG_2 + 1))) */
typedef struct
{
    uint8_t  PRESC;      /*!< Prescaler */
    uint8_t  SEG_1;      /*!< Bit Timing Segment 1 */
    uint8_t  SEG_2;      /*!< Bit Timing Segment 2 */
    uint8_t  SJW;        /*!< Synchronization Jump Width */
} CAN_BitRateConfigType;


typedef struct
{
    uint8_t         index;    /*!< Filter index */
    FunctionalState enable;   /*!< Enable or disable */
    uint32_t        code;     /*!< Code data */
    uint32_t        mask;     /*!< Mask data */
} CAN_FilterControlType;



typedef enum
{
    CAN_TRANSMIT_ALL = 0,        /*!< 发送所有报文 */
    CAN_TRANSMIT_ONE,            /*!< 只发送一帧报文 */
    CAN_TRANSMIT_AMOUNT_MAX      /*!< Invalid transmit amount */
} CAN_TransmitAmountType;


/*!< CANx外设时钟控制位索引号定义，即在RCC_PCLKEN中CANx的位偏移量 */
typedef enum
{
    PCLKEN_CAN0 = 21
}RCC_PCLKEN_Type_t;


/*!< CANx外设复位控制位索引号定义，即在RCC_PERIPRST中CANx的位偏移量 */
typedef enum
{
    PERIPRST_CAN0 = 21
} RCC_PERIPRST_Type_t;


/**
  * @} CAN_DeviceType_t
  */
typedef struct
{
    uint32_t                interruptFlag;   /* CAN interrupt flag */
    FunctionalState         interruptEn;     /* CAN interrupt enable */
    FunctionalState         timeStampEn;     /* Time stamp enable */
    CAN_TransmitAmountType  tsAmount;        /* Transmit secondary all frames or one frame */
    DeviceCallback_Type     callback;        /* CAN callback funciton pointer */
} CAN_DeviceType_t;


typedef struct
{
    IRQn_Type               irq;       /* CAN interrupt number */
    RCC_PCLKEN_Type_t       clock;     /* module clock enable  */
    RCC_PERIPRST_Type_t     reset;     /* module reset */
} CAN_InfoType_t;



/*!< CAN通信波特率类型 */
typedef enum
{
    CAN_BITRATE_1M = 0,
    CAN_BITRATE_800K,
    CAN_BITRATE_500K,
    CAN_BITRATE_250K,
    CAN_BITRATE_125K,
    CAN_BITRATE_100K,
    CAN_BITRATE_50K,
    CAN_BITRATE_20K,
    CAN_BITRATE_10K,
    CAN_BITRATE_5K,
    CAN_BITRATE_NUM
} CAN_BitRateType;      /*!< CAN normal BitRate */


/*!< CAN-FD数据波特率类型 */
typedef enum
{
    CAN_DBITRATE_50K = 0,
    CAN_DBITRATE_100K,
    CAN_DBITRATE_1M,
    CAN_DBITRATE_2M,
    CAN_DBITRATE_4M,
    CAN_DBITRATE_6M,
    CAN_DBITRATE_8M,
    CAN_DBITRATE_NUM
} CAN_DBitRateType;     /*!< CAN FD data BitRate */


typedef enum
{
    CAN_MODE_NORMAL,              /*!< 正常模式 */
    CAN_MODE_MONITOR,             /*!< 监听模式 */
    CAN_MODE_LOOPBACK_INTERNAL,   /*!< 内部环回模式 */
    CAN_MODE_LOOPBACK_EXTERNAL    /*!< 外部环回模式 */
} CAN_ModeType;


typedef enum
{
    CAN_CLKSRC_AHB,               /*!< Clcok source from AHB bus */
    CAN_CLKSRC_EXTERNAL_OSC,      /*!< Clcok source from external OSC */
} CAN_ClkSrcType;


/*!< 数据长度类型 */
typedef enum
{
    CAN_DLC_12_BYTES = 9UL,
    CAN_DLC_16_BYTES,
    CAN_DLC_20_BYTES,
    CAN_DLC_24_BYTES,
    CAN_DLC_32_BYTES,
    CAN_DLC_48_BYTES,
    CAN_DLC_64_BYTES
} CAN_DlcType;


/*!< 发送缓冲区类型 */
typedef enum
{
    CAN_TRANSMIT_PRIMARY = 0,    /*!< 主发送缓冲区PTB */
    CAN_TRANSMIT_SECONDARY       /*!< 次发送缓冲区STB */
} CAN_TransmitBufferType;





/*!< 发送缓冲区模式 */
typedef enum
{
    CAN_TSMODE_FIFO = 0,         /*!< Transmit fifo mode */
    CAN_TSMODE_PRIORITY          /*!< Transmit priority mode */
} CAN_TransmitModeType;


/*!< 接收缓冲区溢出模式 */
typedef enum
{
    CAN_RECV_OVER_WRITE = 0,     /*!< Oldest message will be overwrite */
    CAN_RECV_DISCARD             /*!< New message will not be store */
} CAN_OverflowModeType;


/*!< 时间戳标志位置类型 */
typedef enum
{
    CAN_TIME_STAMP_SOF = 0,      /*!< TIME-STAMPing position SOF */
    CAN_TIME_STAMP_EOF           /*!< TIME-STAMPing position EOF */
}CAN_TimeStampPosType;


/*!< CAN报文帧类型 */
typedef enum
{
    CAN_CTRL_DATA_FRAME = 0,     /*!< Data frame */
    CAN_CTRL_REMOTE_FRAME        /*!< Remote frame */
}CAN_CtrlFrameType;


/*!< CAN时钟源类型选择 */
typedef enum
{
    CAN_CLK_SEL_EXTERNAL_OSC = 0,
    CAN_CLK_SEL_AHB
} CAN_ClockSelectType;


/*!< CAN CiA603时间戳时钟分频选择 */
typedef enum
{
    CAN_TIME_CLK_DIVIDER_8 = 0,
    CAN_TIME_CLK_DIVIDER_16,
    CAN_TIME_CLK_DIVIDER_24,
    CAN_TIME_CLK_DIVIDER_48
} CAN_TimeClockDividerType;





typedef struct
{
    uint8_t                     filterNum;             /*!< Set filter number */
    uint8_t                     errorWarningLimit;     /*!< programmable error warning limit*/
    CAN_ModeType                canMode;               /*!< CAN mode  */
    CAN_ClkSrcType              clockSrc;              /*!< CAN clock source */
    CAN_TransmitModeType        tsMode;                /*!< Transmit buffer secondary operation mode */
    CAN_TransmitAmountType      tsAmount;              /*!< Transmit secondary: CAN_TRANSMIT_ALL->all frames; CAN_TRANSMIT_ONE->one frame */
    FunctionalState             interruptEn;           /*!< Interrupt enable */
    FunctionalState             tpss;                  /*!< Transmission primary single shot mode for PTB */
    FunctionalState             tsss;                  /*!< Transmission secondary single shot mode for STB */
    FunctionalState             timeStampEn;           /*!< Time stamp enable */
    CAN_TimeClockDividerType    timeStampClk;          /*!< Time stamp clock  */
    CAN_TimeStampPosType        timeStampPos;          /*!< Time stamp position  */
    CAN_OverflowModeType        rom;                   /*!< Receive buffer overflow mode */
    FunctionalState             selfAckEn;             /*!< Self-Acknowledge enable(when LBME=1) */
    FunctionalState             fdModeEn;              /*!< FD enable   */
    FunctionalState             fdIsoEn;               /*!< FD ISO mode */
    FunctionalState             tdcEnable;             /*!< TDC enable (when data BitRate >= 1Mbps) */
    uint8_t                     sspOffset;             /*!< SSP offset  */
    uint32_t                    interruptMask;         /*!< Interrupt enable mask  */
    CAN_BitRateConfigType*      normalBitrate;         /*!< Normal BitRate setting */
    CAN_BitRateConfigType*      dataBitrate;           /*!< Data BitRate setting   */
    CAN_FilterControlType*      filterList;            /*!< Filter controller list */
    DeviceCallback_Type         callback;              /*!< CAN callback pointer   */
} CAN_ConfigType;


/* ====================================  Functions declaration  ===================================== */
void CAN_SetReset(CAN_TypeDef* CANx, FunctionalState NewState);
uint8_t CAN_SetStandby(CAN_TypeDef* CANx, FunctionalState state);
int32_t CAN_IsMsgInReceiveBuf(CAN_TypeDef* CANx);
uint8_t CAN_StartTransmission(CAN_TypeDef* CANx, CAN_TransmitBufferType type, CAN_TransmitAmountType amount);
void CAN_AbortTransmission(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
uint8_t CAN_IsTransmitBusy(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
uint8_t CAN_IsTransmitting(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
uint8_t CAN_IsTransmitIdle(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
int32_t CAN_IsBusoff(CAN_TypeDef* CANx);
void CAN_SetIntEnable(CAN_TypeDef* CANx, uint32_t intEn);
void CAN_SetEwl(CAN_TypeDef* CANx, uint8_t ewl);
void CAN_SetAfwl(CAN_TypeDef* CANx, uint8_t afwl);
uint32_t CAN_GetTts(CAN_TypeDef* CANx);
void CAN_SetTpss(CAN_TypeDef* CANx, FunctionalState state);
void CAN_SetTsss(CAN_TypeDef* CANx, FunctionalState state);
uint32_t CAN_GetTSStat(CAN_TypeDef* CANx);
uint32_t CAN_GetRStat(CAN_TypeDef* CANx);
uint32_t CAN_GetRov(CAN_TypeDef* CANx);
uint32_t CAN_GetKoer(CAN_TypeDef* CANx);
void CAN_SetFdIso(CAN_TypeDef* CANx, FunctionalState state);
void CAN_SetTSMode(CAN_TypeDef* CANx, CAN_TransmitModeType tsMode);
void CAN_SetRom(CAN_TypeDef* CANx, CAN_OverflowModeType rom);
void CAN_SetSack(CAN_TypeDef* CANx, FunctionalState state);
void CAN_SetTdc(CAN_TypeDef* CANx, FunctionalState state);
void CAN_SetSspOffet(CAN_TypeDef* CANx, uint8_t offset);
void CAN_SetTimePosition(CAN_TypeDef* CANx, CAN_TimeStampPosType pos);
void CAN_EnableTime(CAN_TypeDef* CANx, FunctionalState state);
void CAN_SetAcfEn(CAN_TypeDef* CANx, uint8_t index, FunctionalState state);
void CAN_SetAcfIndex(CAN_TypeDef* CANx, uint8_t index);
void CAN_SetAcfCode(CAN_TypeDef* CANx, uint32_t code);
void CAN_SetAcfMask(CAN_TypeDef* CANx, uint32_t mask);
uint16_t CAN_GetVersion(CAN_TypeDef* CANx);
uint8_t CAN_GetRECnt(CAN_TypeDef* CANx);
uint8_t CAN_GetTECnt(CAN_TypeDef* CANx);
void CAN_SetCallBack(CAN_TypeDef* CANx, DeviceCallback_Type callbackFunc);
void CAN_HandleEvent(CAN_TypeDef* CANx);
static void CAN_SetBitrate(CAN_TypeDef* CANx, const CAN_BitRateConfigType *config, uint8_t dataBitrate);
int32_t CAN_GetError(CAN_TypeDef* CANx);
void CAN_SetTimeStampDivider(uint8_t canIndex, CAN_TimeClockDividerType divider);
void CAN_Init(CAN_TypeDef* CANx, CAN_ConfigType *config);
void CAN_DeInit(CAN_TypeDef* CANx);
int32_t WaitTransmitPrimaryDone(CAN_TypeDef* CANx);
int32_t WaitTransmitSecondaryDone(CAN_TypeDef* CANx);
int32_t CAN_WaitTransmissionDone(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
uint8_t CAN_WaitTransmissionIdle(CAN_TypeDef* CANx, CAN_TransmitBufferType type);
uint8_t CAN_GetPayloadSize(uint8_t dlcValue);
void CAN_SetMsgInfo(CAN_TypeDef* CANx, const CAN_MsgInfoType *info, CAN_TransmitBufferType type);
void CAN_SetTransmitAmount(CAN_TypeDef* CANx, CAN_TransmitAmountType amount);
int32_t CAN_TransmitMessage(CAN_TypeDef* CANx, const CAN_MsgInfoType *info, CAN_TransmitBufferType type);
uint8_t CAN_ReceiveMessage(CAN_TypeDef* CANx, CAN_MsgInfoType *info);
int32_t CAN_SetFilter(CAN_TypeDef* CANx, uint8_t index, uint32_t code, uint32_t mask, FunctionalState state);


#endif     /* __CPS32K21X_CAN_H__  */

