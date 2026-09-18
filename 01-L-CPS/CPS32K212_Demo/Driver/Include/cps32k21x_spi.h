/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_SPI_H__
#define __CPS32K21X_SPI_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"

	 
	 
/** @defgroup SPI_Exported_Constants
  * @{
  */   
#define IS_SPI_ALL_PERIPH(PERIPH)    (((PERIPH) == SPI1))

#define SPI_WAIT_TIMEOUT       (10)    /* 10ms */  


/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
	uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
	                                     This parameter can be a value of @ref SPI_mode */

	uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
	                                     This parameter can be a value of @ref SPI_Clock_Polarity */

	uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
	                                     This parameter can be a value of @ref SPI_Clock_Phase */

	uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
	                                     used to configure the transmit and receive SCK clock.
	                                     This parameter can be a value of @ref SPI_BaudRate_Prescaler.
	                                     @note The communication clock is derived from the master
	                                     clock. The slave clock does not need to be set. */
}SPI_InitTypeDef;


/** @defgroup SPI_mode 
  * @{
  */
#define SPI_Mode_Master         ((uint32_t)0x00000010)    /*<! SPI主机模式 */
#define SPI_Mode_Slave          ((uint32_t)0x00000000)    /*<! SPI从机模式 */
#define IS_SPI_MODE(MODE) 	    (((MODE) == SPI_Mode_Master) ||\
                           		 ((MODE) == SPI_Mode_Slave))


/** @defgroup SPI_Clock_Polarity 
  * @{
  */
#define SPI_CPOL_Low            ((uint32_t)0x00000000)   /*<! SPI时钟极性Low */
#define SPI_CPOL_High           ((uint32_t)0x00000008)   /*<! SPI时钟极性High */
#define IS_SPI_CPOL(CPOL) 	    (((CPOL) == SPI_CPOL_Low) ||\
                                 ((CPOL) == SPI_CPOL_High))

/** @defgroup SPI_Clock_Phase 
  * @{
  */
#define SPI_CPHA_1Edge          ((uint32_t)0x00000000)   /*<! SPI时钟相位：第一边沿 */
#define SPI_CPHA_2Edge          ((uint32_t)0x00000004)   /*<! SPI时钟相位：第二边沿 */
#define IS_SPI_CPHA(CPHA)       (((CPHA) == SPI_CPHA_1Edge) ||\
                                 ((CPHA) == SPI_CPHA_2Edge))

/**
  * @}SPI_SPEN_Enable
  */
#define SPI_SPEN_ENABLE         ((uint32_t)0x00000040)   /*<! SPI模块Enable */
#define SPI_SPEN_DISABLE        ((uint32_t)0x00000000)   /*<! SPI模块Disable */


/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */
#define SPI_BaudRatePrescaler_2                 ((uint32_t)0x00000000)
#define SPI_BaudRatePrescaler_4         		((uint32_t)0x00000001)
#define SPI_BaudRatePrescaler_8         		((uint32_t)0x00000002)
#define SPI_BaudRatePrescaler_16        		((uint32_t)0x00000003)
#define SPI_BaudRatePrescaler_32        		((uint32_t)0x00000080)
#define SPI_BaudRatePrescaler_64        		((uint32_t)0x00000081)
#define SPI_BaudRatePrescaler_128       		((uint32_t)0x00000082)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER)    (((PRESCALER) == SPI_BaudRatePrescaler_2)  ||\
                                              	 ((PRESCALER) == SPI_BaudRatePrescaler_4)  ||\
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_8)  ||\
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_16) ||\
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_32) ||\
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_64) ||\
                                                 ((PRESCALER) == SPI_BaudRatePrescaler_128)) 
                                        
/**
  * @}SPI SSN STATUS
  */
#define SPI_SSN_Low    		((uint32_t)0x00000000)   /*<! SPI_SSN管脚输出低电平 */
#define SPI_SSN_High   		((uint32_t)0x00000001)   /*<! SPI_SSN管脚输出高电平 */

/**
  * @}SPI Flag define 
  */
#define SPI_FLAG_SPIF    	((uint32_t)0x00000080)   /* End of transmission interrupt flag */
#define SPI_FLAG_WCOL    	((uint32_t)0x00000040)   /* Write Conflict Interruption flag */
#define SPI_FLAG_SSERR   	((uint32_t)0x00000020)   /* Slave SSN error flag */
#define SPI_FLAG_MDF     	((uint32_t)0x00000010)   /* Slave mode error flag */
#define IS_SPI_FLAG(FLAG)   (((FLAG) == SPI_FLAG_SPIF) ||\
                             ((FLAG) == SPI_FLAG_WCOL) ||\
                             ((FLAG) == SPI_FLAG_SSERR)||\
							 ((FLAG) == SPI_FLAG_MDF)) 
														
/** @defgroup CR_CLEAR_Mask
  * @{
  */
#define CR_CLEAR_Mask  		((uint32_t)0x00000040)


/* Exported functions --------------------------------------------------------*/
void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
uint8_t SPI_Master_TransmitReceive(SPI_TypeDef* SPIx, uint8_t TxData);
void SPI_Slave_SendData(SPI_TypeDef* SPIx, uint8_t TxData);
uint8_t SPI_Slave_ReceiveData(SPI_TypeDef* SPIx);
void SPI_SSNOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_SPI_H__ */


