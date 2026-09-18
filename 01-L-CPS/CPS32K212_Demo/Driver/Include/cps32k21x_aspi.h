/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_ASPI_H__
#define __CPS32K21X_ASPI_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"

	 
	 
/** @defgroup ASPI_Exported_Constants
  * @{
  */  
#define IS_ASPI_ALL_PERIPH(PERIPH)    (((PERIPH) == ASPI1))

#define ASPI_WAIT_TIMEOUT       (10)    /* 10ms */  


typedef enum {ASPI_SPDR_RECEIVE, ASPI_SPDR_SEND}ASPI_SPDR_t;
typedef enum {ASPI_SPMS_4LINE, ASPI_SPMS_3LINE}ASPI_SPMS_t;
typedef enum {ASPI_SPOM_CMOS, ASPI_SPMS_OPENDRAIN}ASPI_SPOM_t;
typedef enum {ASPI_SPLP2_NORMAL, ASPI_SPLP2_LOOPBACK}ASPI_SPLP2_t;
typedef enum {ASPI_SPLP1_NORMAL, ASPI_SPLP1_LOOPBACK}ASPI_SPLP1_t;

typedef enum
{
   ASPI_OVRFC_FLAG = 0,
   ASPI_MODFC_FLAG, 
   ASPI_UDRFC_FLAG,   
   ASPI_SPIEFC_FLAG,  
   ASPI_SPRFC_FLAG,          
}ASPI_INTTERUPT_FLAG_t;


/** 
  * @brief  ASPI Init structure definition  
  */

typedef struct
{
	uint32_t ASPI_Mode;                /*!< Specifies the ASPI operating mode.
	                                     This parameter can be a value of @ref ASPI_mode */

	uint32_t ASPI_CPOL;                /*!< Specifies the serial clock steady state.
	                                     This parameter can be a value of @ref ASPI_Clock_Polarity */

	uint32_t ASPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
	                                     This parameter can be a value of @ref ASPI_Clock_Phase */

	uint32_t ASPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
	                                     used to configure the transmit and receive SCK clock.
	                                     This parameter can be a value of @ref ASPI_BaudRate_Prescaler.
	                                     @note The communication clock is derived from the master
	                                     clock. The slave clock does not need to be set. */
}ASPI_InitTypeDef;


/** @defgroup ASPI_mode 
  * @{
  */
#define ASPI_Mode_Master         ((uint32_t)0x40000000)    /*<! ASPI主机模式 */
#define ASPI_Mode_Slave          ((uint32_t)0x00000000)    /*<! ASPI从机模式 */
#define IS_ASPI_MODE(MODE) 	    (((MODE) == ASPI_Mode_Master) ||\
                           		 ((MODE) == ASPI_Mode_Slave))


/** @defgroup ASPI_Clock_Polarity 
  * @{
  */
#define ASPI_CPOL_Low            ((uint32_t)0x00000000)   /*<! ASPI时钟极性Low */
#define ASPI_CPOL_High           ((uint32_t)0x00000002)   /*<! ASPI时钟极性High */
#define IS_ASPI_CPOL(CPOL) 	    (((CPOL) == ASPI_CPOL_Low) ||\
                                 ((CPOL) == ASPI_CPOL_High))

/** @defgroup ASPI_Clock_Phase 
  * @{
  */
#define ASPI_CPHA_1Edge          ((uint32_t)0x00000000)   /*<! ASPI时钟相位：第一边沿 */
#define ASPI_CPHA_2Edge          ((uint32_t)0x00000001)   /*<! ASPI时钟相位：第二边沿 */
#define IS_ASPI_CPHA(CPHA)       (((CPHA) == ASPI_CPHA_1Edge) ||\
                                 ((CPHA) == ASPI_CPHA_2Edge))

/**
  * @}ASPI_SPEN_Enable
  */
#define ASPI_SPEN_ENABLE         ((uint32_t)0x00000001)   /*<! ASPI模块Enable */
#define ASPI_SPEN_DISABLE        ((uint32_t)0x00000000)   /*<! ASPI模块Disable */


/** @defgroup ASPI_BaudRate_Prescaler 
  * @{
  */
#define IS_ASPI_BAUDRATE_PRESCALER(PRESCALER)    ((PRESCALER)>=0 ||((PRESCALER)<= 255)) 
#define IS_ASPI_SSL_DELAY(SSL_Delay_Cycle)       ((SSL_Delay_Cycle)>=0 ||((SSL_Delay_Cycle)<= 8)) 
#define IS_ASPI_SPN_DELAY(SPN_Delay_Cycle)       ((SPN_Delay_Cycle)>=0 ||((SPN_Delay_Cycle)<= 8)) 
#define IS_ASPI_TTRG(Depth)       ((Depth)>=0 ||((Depth)<= 3)) 
#define IS_ASPI_RTRG(Depth)       ((Depth)>=0 ||((Depth)<= 3)) 
#define  ASPI_SSL_DELAY_MASK     (uint32_t)(7<<8)
#define  ASPI_SPN_DELAY_MASK     (uint32_t)(7<<16)
#define  ASPI_SCK_DELAY_MASK     (uint32_t)(7)
                                        

/**
  * @}ASPI SSN STATUS
  */
#define ASPI_SSN_Low    		((uint32_t)0x00000000)   /*<! ASPI_SSN管脚输出低电平 */
#define ASPI_SSN_High   		((uint32_t)0x00000001)   /*<! ASPI_SSN管脚输出高电平 */

/**
  * @}ASPI Flag define 
  */
#define ASPI_FLAG_ASPIF    	((uint32_t)0x00000080)   /* End of transmission interrupt flag */
#define ASPI_FLAG_WCOL    	((uint32_t)0x00000040)   /* Write Conflict Interruption flag */
#define ASPI_FLAG_SSERR   	((uint32_t)0x00000020)   /* Slave SSN error flag */
#define ASPI_FLAG_MDF     	((uint32_t)0x00000010)   /* Slave mode error flag */
#define IS_ASPI_FLAG(FLAG)   (((FLAG) == ASPI_FLAG_ASPIF) ||\
                             ((FLAG) == ASPI_FLAG_WCOL) ||\
                             ((FLAG) == ASPI_FLAG_SSERR)||\
							 ((FLAG) == ASPI_FLAG_MDF)) 
                                                       
/**************************************/
#define  ASPI_SLNDEN_ENABLE     (uint32_t)(0x01UL << 14)
#define  ASPI_SLNDEN_DISABLE   ~(uint32_t)(0x01UL << 14)

#define  ASPI_SPNDL_ENABLE     (uint32_t)(0x01UL << 13)
#define  ASPI_SPNDL_DISABLE   ~(uint32_t)(0x01UL << 13)

#define  ASPI_SCKDEN_ENABLE     (uint32_t)(0x01UL << 15)
#define  ASPI_SCKDEN_DISABLE   ~(uint32_t)(0x01UL << 15)


#define  ASPI_SPTEF_FLAG     (uint32_t)(0x01UL << 29)
#define  ASPI_SPRF_FLAG      (uint32_t)(0x01UL << 31)

#define  ASPI_SPRDTD_READ_RECEIVE_BUFFER  (uint32_t)0
#define  ASPI_SPRDTD_READ_SEND_BUFFER     (uint32_t)(0x01UL << 3)


#define  ASPI_SPMS_MASK       (uint32_t)(0x01UL << 24)
#define  ASPI_SPTIE_MASK      (uint32_t)(0x01UL << 20)
#define  ASPI_SPIIE_MASK      (uint32_t)(0x01UL << 18)
#define  ASPI_SPRIE_MASK      (uint32_t)(0x01UL << 17)
#define  ASPI_SPEIE_MASK      (uint32_t)(0x01UL << 16)
#define  ASPI_MODFEN_MASK     (uint32_t)(0x01UL << 14)
#define  ASPI_BFDS_MASK       (uint32_t)(0x01UL << 13)
#define  ASPI_SCKAES_MASK     (uint32_t)(0x01UL << 12)
#define  ASPI_SPE_MASK        (uint32_t)(0x01UL << 0)
#define  ASPI_SPOM_MASK       (uint32_t)(0x01UL << 18)
#define  ASPI_SPLP2_MASK      (uint32_t)(0x01UL << 17)
#define  ASPI_SPLP1_MASK      (uint32_t)(0x01UL << 16)
#define  ASPI_SPDCR1_MASK     (uint32_t)(0x01UL << 3)
#define  ASPI_TTRG_MASK       (uint32_t)(0x03UL << 8)
#define  ASPI_RTRG_MASK       (uint32_t)(0x03UL << 0)
													
/** @defgroup CR_CLEAR_Mask
  * @{
  */
#define CR_CLEAR_Mask  		((uint32_t)0x00000040)


/* Exported functions --------------------------------------------------------*/
void ASPI_DeInit(ASPI_TypeDef* ASPIx);
void ASPI_StructInit(ASPI_InitTypeDef* ASPI_InitStruct);
void ASPI_Init(ASPI_TypeDef * ASPIx, ASPI_InitTypeDef *ASPI_InitStruct);
void ASPI_SPE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SPMS_Select(ASPI_TypeDef * ASPIx, ASPI_SPMS_t mode);
void ASPI_SPOM_Select(ASPI_TypeDef * ASPIx, ASPI_SPOM_t mode);
void ASPI_SPLP2_Select(ASPI_TypeDef * ASPIx, ASPI_SPLP2_t mode);
void ASPI_SPLP1_Select(ASPI_TypeDef * ASPIx, ASPI_SPLP1_t mode);
void ASPI_SPRDTD_Select(ASPI_TypeDef * ASPIx,  ASPI_SPDR_t mode);
void ASPI_FIFO_TTRG_Set(ASPI_TypeDef * ASPIx,uint32_t Depth);
void ASPI_FIFO_RTRG_Set(ASPI_TypeDef * ASPIx,uint32_t Depth);
void ASPI_SPTIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SPIIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SPRIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SPEIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_MODFEN_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_BFDS_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SCKASE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState);
void ASPI_SPNDL_Cmd(ASPI_TypeDef* ASPIx, FunctionalState NewState,uint16_t SPN_Delay_Cycle);
void ASPI_SCKDL_Cmd(ASPI_TypeDef* ASPIx, FunctionalState NewState,uint16_t SCK_Delay_Cycle);
uint8_t ASPI_Master_TransmitReceive(ASPI_TypeDef* ASPIx, uint8_t TxData);
void ASPI_MasterSend(ASPI_TypeDef * ASPIx, uint32_t TxData);
uint32_t ASPI_MasterReceive(ASPI_TypeDef * ASPIx);
void ASPI_SlaveSend(ASPI_TypeDef * ASPIx, uint32_t txData);
void ASPI_ResetFIFO(ASPI_TypeDef * ASPIx);
uint32_t ASPI_SlaveReceive(ASPI_TypeDef * ASPIx);
void  ASPI_ClearFlag(ASPI_TypeDef * ASPIx,ASPI_INTTERUPT_FLAG_t Flag);
uint32_t ASPI_GetSPTFSRFlag(ASPI_TypeDef * ASPIx);
uint32_t ASPI_GetSPRFSRFlag(ASPI_TypeDef * ASPIx);
uint32_t ASPI_GetSPSRFlag(ASPI_TypeDef * ASPIx);

#ifdef __cplusplus
}
#endif

#endif   /*__CPS32K21X_ASPI_H__ */


