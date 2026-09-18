/* Define to prevent recursive inclusion -------------------------------------*/	
#ifndef __CPS32K21X_I2C_H__	
#define __CPS32K21X_I2C_H__	

	
/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include <stdio.h>


#define MY_SYSTEM_CORE_CLOCK   (30000000UL)


//#define NULL      (0)      

#define HAL_IS_BIT_SET(REG, BIT)      (((REG) & (BIT)) != 0U)
#define HAL_IS_BIT_CLR(REG, BIT)      (((REG) & (BIT)) == 0U)

#define SET_BIT(REG, BIT)       ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(BIT))

//#define READ_BIT(REG, BIT)    ((REG) & (BIT))

//#define CLEAR_REG(REG)        ((REG) = (0x0))

//#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

//#define READ_REG(REG)         ((REG))

//#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

//#define CLEAR_WPBIT(REG, CLEARMASK, WPKEY)   WRITE_REG((REG), ((READ_REG(REG)) & (~(CLEARMASK))) | WPKEY)

//#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 

//#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
    
/* ========================================================================================= */
/* ========================                    I2C                          ================ */
/* ========================================================================================= */

/* ==========================================  CR  ========================================= */
#define I2C_CR_H1M_Pos          (0UL)               /*!< I2C CR: H1M (Bit 0)                 */
#define I2C_CR_H1M_Msk          (0x1UL)             /*!< I2C CR: H1M (Bitfield-Mask: 0x01)   */
#define I2C_CR_H1M               I2C_CR_H1M_Msk 
#define I2C_CR_AA_Pos           (2UL)               /*!< I2C CR: AA (Bit 2)                  */
#define I2C_CR_AA_Msk           (0x4UL)             /*!< I2C CR: AA (Bitfield-Mask: 0x01)    */
#define I2C_CR_AA                I2C_CR_AA_Msk   
#define I2C_CR_SI_Pos           (3UL)               /*!< I2C CR: SI (Bit 3)                  */
#define I2C_CR_SI_Msk           (0x8UL)             /*!< I2C CR: SI (Bitfield-Mask: 0x01)    */
#define I2C_CR_SI                I2C_CR_SI_Msk  
#define I2C_CR_STO_Pos          (4UL)               /*!< I2C CR: STO (Bit 4)                 */
#define I2C_CR_STO_Msk          (0x10UL)            /*!< I2C CR: STO (Bitfield-Mask: 0x01)   */
#define I2C_CR_STO              I2C_CR_STO_Msk
#define I2C_CR_STA_Pos          (5UL)               /*!< I2C CR: STA (Bit 5)                 */
#define I2C_CR_STA_Msk          (0x20UL)            /*!< I2C CR: STA (Bitfield-Mask: 0x01)   */
#define I2C_CR_STA              I2C_CR_STA_Msk
#define I2C_CR_ENS_Pos          (6UL)               /*!< I2C CR: ENS (Bit 6)                 */
#define I2C_CR_ENS_Msk          (0x40UL)            /*!< I2C CR: ENS (Bitfield-Mask: 0x01)   */
#define I2C_CR_ENS              I2C_CR_ENS_Msk 
/* ==========================================  DATA  ======================================= */
#define I2C_DATA_DAT_Pos        (0UL)               /*!< I2C DATA: DAT (Bit 0)               */
#define I2C_DATA_DAT_Msk        (0xffUL)            /*!< I2C DATA: DAT (Bitfield-Mask: 0xff) */

/* ==========================================  ADDR  ======================================= */
#define I2C_ADDR_GC_Pos         (0UL)               /*!< I2C ADDR: GC (Bit 0)                */
#define I2C_ADDR_GC_Msk         (0x1UL)             /*!< I2C ADDR: GC (Bitfield-Mask: 0x01)  */
#define I2C_ADDR_GC             I2C_ADDR_GC_Msk
#define I2C_ADDR_I2CADR_Pos     (1UL)               /*!< I2C ADDR: I2CADR (Bit 1)            */
#define I2C_ADDR_I2CADR_Msk     (0xfeUL)            /*!< I2C ADDR: I2CADR (Bitfield-Mask: 0x7f)  */

/* ==========================================  SR  ============================================= */
#define I2C_SR_I2CSTA_Pos       (0UL)               /*!< I2C SR: I2CSTA (Bit 0)                  */
#define I2C_SR_I2CSTA_Msk       (0xffUL)            /*!< I2C SR: I2CSTA (Bitfield-Mask: 0xff)    */

/* =========================================  TIMRUN  ========================================== */
#define I2C_TIMRUN_TME_Pos      (0UL)               /*!< I2C TIMRUN: TME (Bit 0)                 */
#define I2C_TIMRUN_TME_Msk      (0x1UL)             /*!< I2C TIMRUN: TME (Bitfield-Mask: 0x01)   */
#define I2C_TIMRUN_TME          I2C_TIMRUN_TME_Msk

/* =========================================  BAUDCR  ========================================== */
#define I2C_BAUDCR_TM_Pos       (0UL)               /*!< I2C BAUDCR: TM (Bit 0)                  */
#define I2C_BAUDCR_TM_Msk       (0xffUL)            /*!< I2C BAUDCR: TM (Bitfield-Mask: 0xff)    */
#define I2C_BAUDCR_TM           I2C_BAUDCR_TM_Msk 
    

/**
  * @brief  Status structures definition
  */
typedef enum
{
    STATUS_OK       = 0x00U,
    STATUS_ERROR    = 0x01U,
    STATUS_BUSY     = 0x02U,
    STATUS_TIMEOUT  = 0x03U
} StatusTypeDef;


/**
  * @brief  HAL State structure definition
  *
  */
typedef enum
{
    I2C_STATE_RESET = 0x00U,   /*!< Peripheral is not yet Initialized         */	
    I2C_STATE_NONE,            /*!< I2C not do anything        	              */	
    I2C_STATE_READY,           /*!< Peripheral Initialized and ready for use  */
    I2C_STATE_BUSY,            /*!< An internal process is ongoing            */
    I2C_STATE_BUSY_TX,         /*!< Data Transmission process is ongoing      */
    I2C_STATE_BUSY_RX,         /*!< Data Reception process is ongoing         */
    I2C_STATE_ABORT,           /*!< Abort user request ongoing                */
    I2C_STATE_TIMEOUT,         /*!< Timeout state                             */
    I2C_STATE_ERROR            /*!< Error                                     */
}I2C_StateTypeDef;


/** 
  * @brief  I2C Initial Configuration Structure definition  
  */
typedef struct 
{
	uint32_t master;	    /*!< master mode enable/disable.
						         This parameter can be a value of @ref I2C_Master_Mode */
	                          
	uint32_t slave; 	    /*!< slave mode enable/disable.
                                 This parameter can be a value of @ref I2C_Slave_Mode */
	                          
	uint32_t slaveAddr;	    /*!< slave address */
	                          
    uint32_t speedclock;    /*!< i2c speed clock set, speed=Pclk / (8 * (baudcr + 1)), uint: KHz */
	                          
	uint32_t broadack;	    /*!< ack enable or disable when as slave.
						         This parameter can be a value of @ref I2C BROAD */
	
}I2C_InitTypeDef; 


/**
  * @brief  HAL Mode structure definition
 */
typedef enum
{
    I2C_MODE_NONE   = 0x00U,   /*!< No I2C communication on going        */
    I2C_MODE_MASTER = 0x10U,   /*!< I2C communication is in Master Mode  */
    I2C_MODE_SLAVE  = 0x20U    /*!< I2C communication is in Slave Mode   */
}I2C_ModeTypeDef;

/**
  * @brief  I2CStatus enum definition
 */

typedef enum 
{
    I2C_ERROR   = 0u,   /*!< No i2c status flag      */
    I2C_SUCCESS = 1u,   /*!< Waited i2c status flag  */
    I2C_WAITING = 2u    /*!< Waiting i2c status flag */
} I2CStatus;


/** 
  * @brief  I2C handle Structure definition  
  */ 
typedef struct 
{
    I2C_TypeDef*            Instance;
    I2C_InitTypeDef         Init;                             
    __IO uint32_t           PreviousState;  /*!< I2C communication Previous state and mode
                                                 context for internal usage */
    __IO I2C_StateTypeDef   State;          /*!< I2C communication state  */                             
    __IO I2C_ModeTypeDef    Mode;           /*!< I2C communication mode   */                                  
    __IO uint32_t           ErrorCode;      /*!< I2C Error code           */
 }I2C_HandleTypeDef;


/** @defgroup I2C_Error_Code I2C Error Code
  * @brief    I2C Error Code 
  * @{
  */ 
#define I2C_ERROR_NONE       (0x00000000U)    /*!< No error      */
#define I2C_ERROR_TIMEOUT    (0x00000020U)    /*!< Timeout Error */


/** @defgroup I2C_Master_Mode I2C master mode enable/disable
  * @{
  */
#define I2C_MASTER_MODE_DISABLE     ((uint32_t)0x00000000)
#define I2C_MASTER_MODE_ENABLE      ((uint32_t)0x00000001)


/** @defgroup I2C_Slave_Mode I2C slave mode enable/disable
  * @{
  */
#define I2C_SLAVE_MODE_ENABLE       ((uint32_t)0x00000000)
#define I2C_SLAVE_MODE_DISABLE      ((uint32_t)0x00000001)

  
/** @defgroup I2C_BROAD  I2C broad ack enable/disable
  * @{
  */
#define I2C_BROAD_ACK_ENABLE        ((uint32_t)0x00000000)
#define I2C_BROAD_ACK_DISABLE       ((uint32_t)0x00000001)

  
/** @defgroup I2C_HIGH_RATE  I2C high rate enable/disable
  * @{
  */
#define I2C_HIGH_RATE_ENABLE        ((uint32_t)0x00000000)
#define I2C_HIGH_RATE_DISABLE       I2C_CR_H1M


/** @defgroup I2C_Flag_definition I2C Flag definition
  * @{
  */
#define I2C_FLAG_ERROR_UNDER        ((uint32_t)0x00000000)
#define I2C_FLAG_USELESS            ((uint32_t)0x000000F8)

/************************* Master发送状态 *************************************/
#define I2C_FLAG_MASTER_TX_START            ((uint32_t)0x00000008)
#define I2C_FLAG_MASTER_TX_RESTART          ((uint32_t)0x00000010)
#define I2C_FLAG_MASTER_TX_SLAW_ACK         ((uint32_t)0x00000018)
#define I2C_FLAG_MASTER_TX_SLAW_NOACK       ((uint32_t)0x00000020)
#define I2C_FLAG_MASTER_TX_DATA_ACK         ((uint32_t)0x00000028)
#define I2C_FLAG_MASTER_TX_DATA_NOACK       ((uint32_t)0x00000030)
#define I2C_FLAG_MASTER_TX_LOST_SCL         ((uint32_t)0x00000038)

/************************* Master接收状态 *************************************/
#define I2C_FLAG_MASTER_RX_START            ((uint32_t)0x00000008)
#define I2C_FLAG_MASTER_RX_RESTART          ((uint32_t)0x00000010)
#define I2C_FLAG_MASTER_RX_SLAW_ACK         ((uint32_t)0x00000040)
#define I2C_FLAG_MASTER_RX_SLAW_NOACK       ((uint32_t)0x00000048)
#define I2C_FLAG_MASTER_RX_DATA_ACK         ((uint32_t)0x00000050)
#define I2C_FLAG_MASTER_RX_DATA_NOACK       ((uint32_t)0x00000058)
#define I2C_FLAG_MASTER_RX_LOST_SCL         ((uint32_t)0x00000038)

/************************* Slave发送状态 **************************************/
#define I2C_FLAG_SLAVE_TX_SLAW_ACK          ((uint32_t)0x000000A8)
#define I2C_FLAG_SLAVE_TX_DATA_ACK          ((uint32_t)0x000000B8)
#define I2C_FLAG_SLAVE_TX_DATA_NOACK        ((uint32_t)0x000000C0)
#define I2C_FLAG_SLAVE_TX_DATA_LAST         ((uint32_t)0x000000C8)
#define I2C_FLAG_SLAVE_TX_LOST_SCL          ((uint32_t)0x000000B0)

/************************* Slave接收状态 **************************************/
#define I2C_FLAG_SLAVE_RX_SLAW_ACK          ((uint32_t)0x00000060)   
#define I2C_FLAG_SLAVE_RX_BROAD_ACK         ((uint32_t)0x00000070)   
#define I2C_FLAG_SLAVE_RX_SDATA_ACK         ((uint32_t)0x00000080)
#define I2C_FLAG_SLAVE_RX_SDATA_NOACK       ((uint32_t)0x00000088)
#define I2C_FLAG_SLAVE_RX_BDATA_ACK         ((uint32_t)0x00000090)
#define I2C_FLAG_SLAVE_RX_BDATA_NOACK       ((uint32_t)0x00000098)
#define I2C_FLAG_SLAVE_RX_SA_LOST_SCL       ((uint32_t)0x00000068)
#define I2C_FLAG_SLAVE_RX_BA_LOST_SCL       ((uint32_t)0x00000078)
#define I2C_FLAG_SLAVE_STOP_RESTART         ((uint32_t)0x000000A0)

  
 /** @defgroup I2C_transfer_direction I2C transfer direction selection
  * @{
  */
#define I2C_Direction_Transmitter      ((uint8_t)0x00)
#define I2C_Direction_Receiver         ((uint8_t)0x01)
#define IS_I2C_DIRECTION(DIRECTION)    (((DIRECTION) == I2C_Direction_Transmitter) || \
                                        ((DIRECTION) == I2C_Direction_Receiver))


/* Exported macro ------------------------------------------------------------*/
	
/**
  * @brief  Enable/Disable the I2C peripheral.
  * @param  __HANDLE__: I2C handle
  * @retval None
  */
#define __HAL_I2C_ENABLE(__HANDLE__)   		(SET_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS))
#define __HAL_I2C_DISABLE(__HANDLE__)  		(CLEAR_BIT((__HANDLE__)->Instance->CR, I2C_CR_ENS))


/** @brief  Check whether the I2C interrupt SI is enabled or not.
  * @param  __HANDLE__ specifies the I2C Handle.
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_I2C_GET_INT_SI_FLAG(__HANDLE__)      	((((__HANDLE__)->Instance->CR & (I2C_CR_SI)) == (I2C_CR_SI)) ? SET : RESET)

/** @brief  Clear the I2C interrupt set flags which are cleared by write 0 to specific bit.
  * @param  __HANDLE__ specifies the I2C Handle.
  * @retval None
  */
#define __HAL_I2C_CLEAR_INT_SI_FLAG(__HANDLE__) 	CLEAR_BIT((__HANDLE__)->Instance->CR,I2C_CR_SI)

 
/** @brief  CHECK the parameter used init
  * @param  
  * @retval None
  */
#define IS_I2C_ALL_INSTANCE(INSTANCE)   ((INSTANCE) == I2C0)
#define IS_I2C_SLAVE_MODE(MODE)         (((MODE) == I2C_SLAVE_MODE_ENABLE) || ((MODE) == I2C_SLAVE_MODE_DISABLE)) 
#define IS_I2C_MASTER_MODE(MODE)        (((MODE) == I2C_MASTER_MODE_ENABLE) || ((MODE) == I2C_MASTER_MODE_DISABLE)) 
#define IS_I2C_BROAD_ACK(ACK)           (((ACK) == I2C_BROAD_ACK_ENABLE) || ((ACK) == I2C_BROAD_ACK_DISABLE))
#define IS_I2C_SPEED_CLOCK(CLOCK)       ((CLOCK) < 1000 ) 


#define I2C_TIMEOUT_FLAG          (10U)     /*!< Timeout 10 ms  */
#define I2C_TIMEOUT_BUSY_FLAG     (20U)     /*!< Timeout 20 ms  */


extern I2C_HandleTypeDef i2c_ins;
extern uint32_t HAL_GetTick(void);

/* Exported functions --------------------------------------------------------*/
StatusTypeDef I2C_Init(I2C_HandleTypeDef *hi2c);
StatusTypeDef I2C_DeInit(I2C_HandleTypeDef *hi2c);
void I2C_Start_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
void I2C_Stop_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
void I2C_ACK_Config(I2C_HandleTypeDef *hi2c,FunctionalState NewState);
FlagStatus HAL_I2C_Get_Interrupt_Flag(I2C_HandleTypeDef *hi2c);
void I2C_Clear_Interrupt_Flag(I2C_HandleTypeDef *hi2c);
void I2C_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t Data);
void I2C_Receive_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData);
void I2C_Send_Address(I2C_HandleTypeDef *hi2c, uint8_t Address, uint8_t I2C_Direction);
I2CStatus I2C_Check_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag);
ErrorStatus I2C_Wait_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag);
StatusTypeDef I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
StatusTypeDef I2C_Master_Transmit_NOStop(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
StatusTypeDef I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
StatusTypeDef I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
StatusTypeDef I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *Size);
void I2C_IRQHandler(I2C_HandleTypeDef *hi2c);
__WEAK void I2C_MasterCallback(I2C_HandleTypeDef *hi2c);
__WEAK void I2C_SlaveCallback(I2C_HandleTypeDef *hi2c);


#endif   /* __CPS32K21X_I2C_H__ */


