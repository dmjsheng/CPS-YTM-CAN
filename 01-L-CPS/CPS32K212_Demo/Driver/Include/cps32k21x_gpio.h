/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_GPIO_H__  
#define __CPS32K21X_GPIO_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"

	 
/* Exported types ------------------------------------------------------------*/
#define IS_GPIO_ALL_PERIPH(PERIPH) 		(((PERIPH) == GPIOA) || \
                                    	 ((PERIPH) == GPIOB) || \
                                         ((PERIPH) == GPIOC) || \
                                         ((PERIPH) == GPIOD) || \
                                         ((PERIPH) == GPIOE))

/** 
  * @brief GPIO Configuration Mode enumeration 
  */   
typedef enum
{ 
    GPIO_Mode_IN   = 0x00,    /*!< GPIO Input Mode */
    GPIO_Mode_OUT  = 0x01,    /*!< GPIO Output Mode */
    GPIO_Mode_ANA  = 0x02     /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE)  	(((MODE) == GPIO_Mode_IN)  || \
                             	 ((MODE) == GPIO_Mode_OUT) || \
                             	 ((MODE) == GPIO_Mode_ANA))

/** 
  * @brief GPIO Output type enumeration 
  */  
typedef enum
{ 
    GPIO_OType_PP = 0x00,  // 推挽输出模式
    GPIO_OType_OD = 0x01   // 开漏输出模式
}GPIOOType_TypeDef;

#define IS_GPIO_OTYPE(OTYPE) 	(((OTYPE) == GPIO_OType_PP) || \
                              	 ((OTYPE) == GPIO_OType_OD))

/** 
  * @brief GPIO Output speed enumeration
  */  
typedef enum
{ 
	GPIO_Speed_High = 0x00,  /*!< High speed     */
	GPIO_Speed_Low  = 0x01   /*!< Low speed    */
}GPIOSpeed_TypeDef;

/* Add legacy definition */  
#define IS_GPIO_SPEED(SPEED) 	(((SPEED) == GPIO_Speed_High)  || \
                              	 ((SPEED) == GPIO_Speed_Low)) 

/** 
  * @brief GPIO端口驱动强度选择控制位
  */  
typedef enum
{ 
	GPIO_Drive_High = 0x00,  /*!< 高驱动强度     */
	GPIO_Drive_Low  = 0x01   /*!< 低驱动强度     */
}GPIODrive_TypeDef;

#define IS_GPIO_DRIVE(DRIVE)	(((DRIVE) == GPIO_Drive_High) ||\
                                 ((DRIVE) == GPIO_Drive_Low))


/** 
  * @brief GPIO Configuration PullUp PullDown enumeration 
  */ 
typedef enum
{ 
    GPIO_PuPd_NOPULL = 0x00,     /*!< 禁止上拉、下拉  */
    GPIO_PuPd_UP     = 0x01,     /*!< 上拉使能     */
    GPIO_PuPd_DOWN   = 0x02,     /*!< 下拉使能     */
}GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD) 		(((PUPD) == GPIO_PuPd_NOPULL)||\
                            	 ((PUPD) == GPIO_PuPd_UP)    ||\
                            	 ((PUPD) == GPIO_PuPd_DOWN)) 

/** 
  * @brief GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum
{ 
    Bit_RESET = 0,
    Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) 		(((ACTION) == Bit_RESET) ||\
                                    	 ((ACTION) == Bit_SET))

/** @defgroup EXIT_InitTypeDef
  * @{
  */ 
typedef struct
{
	uint8_t EXIT_Pin_En;        /*!< GPIO中断脚使能位， 0: 禁止/屏蔽中断   1：使能中断 */      
    
	uint8_t EXIT_Flag_Clr;      /*!< GPIO中断脚标志位清除， 0: 保留中断标志位  1：清除中断标志位 */
	                                      
	uint8_t EXIT_IT_Type;       /*!< 中断类型， 0 --> 边沿触发中断类型， 1 --> 电平触发中断类型 */
											
	uint8_t EXIT_IT_Polarity;   /*!< 中断极性， 0 --> 低电平或下降沿触发中断  1 --> 高电平或上升沿触发中断 */
											
	uint8_t EXIT_AnyEdge;       /*!< 端口任意边沿触发中断，0 --> 中断触发沿由 PxIVALn决定  1 --> 上升/下降沿都触发中断 */
											                                  
}EXIT_InitTypeDef;

/** @defgroup EXIT_Pin_En 
  * @{
  */ 
#define EXIT_Pin_Enable		      ((uint8_t)0x01)    /*!< GPIO中断脚使能 */  
#define EXIT_Pin_Disable          ((uint8_t)0x00)    /*!< GPIO中断脚禁止 */  

/** @defgroup EXIT_Flag_Clr 
  * @{
  */ 
#define EXIT_Flag_Clear		      ((uint8_t)0x01)    /*!< 清除中断标志 */   
#define EXIT_Flag_Keep            ((uint8_t)0x00)    /*!< 保留中断标志 */   

/** @defgroup EXIT_IT_Type 
  * @{
  */ 
#define EXIT_IT_Type_Level	      ((uint8_t)0x01)    /*!< 中断类型：电平触发 */    
#define EXIT_IT_Type_Edge      	  ((uint8_t)0x00)    /*!< 中断类型：边沿触发 */    

/** @defgroup EXIT_IT_Polarity 
  * @{
  */ 
#define EXIT_IT_Pol_HighRising	  ((uint8_t)0x01)    /*!< 中断极性：高电平或上升沿 */                       
#define EXIT_IT_Pol_LowFalling    ((uint8_t)0x00)    /*!< 中断极性：低电平或下降沿 */

/** @defgroup EXIT_AnyEdge 
  * @{
  */ 
#define EXIT_AnyEdge_Enable       ((uint8_t)0x01)    /*!< 双边沿触发使能 */ 
#define EXIT_AnyEdge_Disable      ((uint8_t)0x00)    /*!< 双边沿触发禁止 */ 

/** 
  * @brief GPIO Init structure definition  
  */ 
typedef struct
{
	uint16_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
	                                   This parameter can be any value of @ref GPIO_pins_define */

	GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
	                                   This parameter can be a value of @ref GPIOMode_TypeDef */

	GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
	                                   This parameter can be a value of @ref GPIOSpeed_TypeDef */
	                                   
	GPIODrive_TypeDef GPIO_Drive;   /*!< Specifies the drive for the selected pins.
	                                   This parameter can be a value of @ref GPIODrive_TypeDef */

	GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
	                                   This parameter can be a value of @ref GPIOOType_TypeDef */

	GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
	                                   This parameter can be a value of @ref GPIOPuPd_TypeDef */
}GPIO_InitTypeDef;


/** @defgroup GPIO_pins_define 
  * @{
  */ 
									
#define GPIO_Pin_None	       ((uint16_t)0x0000)  /* None pin selected */
#define GPIO_Pin_0             ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1             ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2             ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3             ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4             ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5             ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6             ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7             ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8             ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9             ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10            ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11            ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12            ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13            ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14            ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15            ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All           ((uint16_t)0xFFFF)  /* All pins selected */

#define IS_GPIO_PIN(PIN)        ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))
#define IS_GET_GPIO_PIN(PIN)    (((PIN) == GPIO_Pin_0) || \
                              	((PIN) == GPIO_Pin_1)  || \
                              	((PIN) == GPIO_Pin_2)  || \
                              	((PIN) == GPIO_Pin_3)  || \
                              	((PIN) == GPIO_Pin_4)  || \
                              	((PIN) == GPIO_Pin_5)  || \
                              	((PIN) == GPIO_Pin_6)  || \
                              	((PIN) == GPIO_Pin_7)  || \
                              	((PIN) == GPIO_Pin_8)  || \
                              	((PIN) == GPIO_Pin_9)  || \
                              	((PIN) == GPIO_Pin_10) || \
                              	((PIN) == GPIO_Pin_11) || \
                              	((PIN) == GPIO_Pin_12) || \
                              	((PIN) == GPIO_Pin_13) || \
                              	((PIN) == GPIO_Pin_14) || \
                              	((PIN) == GPIO_Pin_15))
                              
/** @defgroup GPIO_Pin_sources 
  * @{
  */ 
#define GPIO_PinSource0          ((uint8_t)0x00)
#define GPIO_PinSource1          ((uint8_t)0x01)
#define GPIO_PinSource2          ((uint8_t)0x02)
#define GPIO_PinSource3          ((uint8_t)0x03)
#define GPIO_PinSource4          ((uint8_t)0x04)
#define GPIO_PinSource5          ((uint8_t)0x05)
#define GPIO_PinSource6          ((uint8_t)0x06)
#define GPIO_PinSource7          ((uint8_t)0x07)
#define GPIO_PinSource8          ((uint8_t)0x08)
#define GPIO_PinSource9          ((uint8_t)0x09)
#define GPIO_PinSource10         ((uint8_t)0x0A)
#define GPIO_PinSource11         ((uint8_t)0x0B)
#define GPIO_PinSource12         ((uint8_t)0x0C)
#define GPIO_PinSource13         ((uint8_t)0x0D)
#define GPIO_PinSource14         ((uint8_t)0x0E)
#define GPIO_PinSource15         ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE)   (((PINSOURCE) == GPIO_PinSource0)  || \
                                         ((PINSOURCE) == GPIO_PinSource1)  || \
                                         ((PINSOURCE) == GPIO_PinSource2)  || \
                                         ((PINSOURCE) == GPIO_PinSource3)  || \
                                         ((PINSOURCE) == GPIO_PinSource4)  || \
                                         ((PINSOURCE) == GPIO_PinSource5)  || \
                                         ((PINSOURCE) == GPIO_PinSource6)  || \
                                         ((PINSOURCE) == GPIO_PinSource7)  || \
                                         ((PINSOURCE) == GPIO_PinSource8)  || \
                                         ((PINSOURCE) == GPIO_PinSource9)  || \
                                         ((PINSOURCE) == GPIO_PinSource10) || \
                                         ((PINSOURCE) == GPIO_PinSource11) || \
                                         ((PINSOURCE) == GPIO_PinSource12) || \
                                         ((PINSOURCE) == GPIO_PinSource13) || \
                                         ((PINSOURCE) == GPIO_PinSource14) || \
                                         ((PINSOURCE) == GPIO_PinSource15))
																			 																		 
/** @defgroup GPIO_Pin_direction_mode
  * @{
  */ 
#define GPIO_PIN_MODE_OUT    			 ((uint32_t)0x00000001) 
#define GPIO_PIN_MODE_IN     			 ((uint32_t)0x00000000)  
#define IS_GPIO_PIN_DIRECTION(PINMODE)   (((PINMODE) == GPIO_PIN_MODE_OUT)|| \
                                          ((PINMODE) == GPIO_PIN_MODE_IN))

/****************** Bits definition for GPIO_MODER register  *********************/
#define GPIO_MODE          		((uint32_t)0x0000000F)

/****************** Bits definition for GPIO_OTYPER register  ********************/
#define GPIO_OTYPER_OD          ((uint32_t)0x00000001)

/****************** Bits definition for GPIO_SLEWCR register  ********************/
#define GPIO_SLEWCR_MASK		((uint32_t)0x00000001)

/****************** Bits definition for GPIO_DRVCR register  ********************/
#define GPIO_DRVCR_MASK			((uint32_t)0x00000001)

/****************** Bits definition for GPIO_PUPDR register  *********************/
#define GPIO_PUPDR_PUPD         ((uint32_t)0x00000003)


/***************** Bits definition for Pxn(n=0~15)消抖使能配置位 *******************/
#define GPIO_DIDB_SYNC_EN               (BIT16)
#define GPIO_DIDB_PIN0_EN               (BIT0)
#define GPIO_DIDB_PIN1_EN               (BIT1)
#define GPIO_DIDB_PIN2_EN               (BIT2)
#define GPIO_DIDB_PIN3_EN               (BIT3)
#define GPIO_DIDB_PIN4_EN               (BIT4)
#define GPIO_DIDB_PIN5_EN               (BIT5)
#define GPIO_DIDB_PIN6_EN               (BIT6)
#define GPIO_DIDB_PIN7_EN               (BIT7)
#define GPIO_DIDB_PIN8_EN               (BIT8)
#define GPIO_DIDB_PIN9_EN               (BIT9)
#define GPIO_DIDB_PIN10_EN              (BIT10)
#define GPIO_DIDB_PIN11_EN              (BIT11)
#define GPIO_DIDB_PIN12_EN              (BIT12)
#define GPIO_DIDB_PIN13_EN              (BIT13)
#define GPIO_DIDB_PIN14_EN              (BIT14)
#define GPIO_DIDB_PIN15_EN              (BIT15)
#define GPIO_DIDB_PINALL_MASK           ((uint32_t)0xFFFF)

#define IS_GPIO_DIDB_PINxEN(PINx)    	(((PINx) == GPIO_DIDB_PIN0_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN1_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN2_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN3_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN4_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN5_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN6_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN7_EN)  || \
									   	 ((PINx) == GPIO_DIDB_PIN8_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN9_EN)  || \
                                       	 ((PINx) == GPIO_DIDB_PIN10_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PIN11_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PIN12_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PIN13_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PIN14_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PIN15_EN) || \
                                       	 ((PINx) == GPIO_DIDB_PINALL_MASK))


/***************** GPIO DBCLK set register ***************************************/
#define GPIO_DBCLK_EN                   ((uint32_t)0x00000010)  /*< 使能去抖动时钟 */
#define GPIO_DBCLK_1CYCLE               ((uint32_t)0x00000000)
#define GPIO_DBCLK_2CYCLE               ((uint32_t)0x00000001)
#define GPIO_DBCLK_4CYCLE               ((uint32_t)0x00000002)
#define GPIO_DBCLK_8CYCLE               ((uint32_t)0x00000003)
#define GPIO_DBCLK_16CYCLE              ((uint32_t)0x00000004)
#define GPIO_DBCLK_32CYCLE              ((uint32_t)0x00000005)
#define GPIO_DBCLK_64CYCLE              ((uint32_t)0x00000006)
#define GPIO_DBCLK_128CYCLE             ((uint32_t)0x00000007)
#define GPIO_DBCLK_256CYCLE             ((uint32_t)0x00000008)
#define GPIO_DBCLK_512CYCLE             ((uint32_t)0x00000009)
#define GPIO_DBCLK_1024CYCLE            ((uint32_t)0x0000000A)
#define GPIO_DBCLK_2048CYCLE            ((uint32_t)0x0000000B)
#define GPIO_DBCLK_4096CYCLE            ((uint32_t)0x0000000C)
#define GPIO_DBCLK_8192CYCLE            ((uint32_t)0x0000000D)
#define GPIO_DBCLK_16384CYCLE           ((uint32_t)0x0000000E)
#define GPIO_DBCLK_32768CYCLE           ((uint32_t)0x0000000F)
#define GPIO_DBCLK_CYCLEMASK            ((uint32_t)0x0000000F)

#define IS_GPIO_DBCLK_CYCLE(CYCLE)    	(((CYCLE) == GPIO_DBCLK_1CYCLE)    || \
                                       	 ((CYCLE) == GPIO_DBCLK_2CYCLE)    || \
                                       	 ((CYCLE) == GPIO_DBCLK_4CYCLE)    || \
                                       	 ((CYCLE) == GPIO_DBCLK_8CYCLE)    || \
                                       	 ((CYCLE) == GPIO_DBCLK_16CYCLE)   || \
                                       	 ((CYCLE) == GPIO_DBCLK_32CYCLE)   || \
                                       	 ((CYCLE) == GPIO_DBCLK_64CYCLE)   || \
                                       	 ((CYCLE) == GPIO_DBCLK_128CYCLE)  || \
									   	 ((CYCLE) == GPIO_DBCLK_256CYCLE)  || \
                                       	 ((CYCLE) == GPIO_DBCLK_1024CYCLE) || \
                                       	 ((CYCLE) == GPIO_DBCLK_2048CYCLE) || \
                                       	 ((CYCLE) == GPIO_DBCLK_4096CYCLE) || \
                                       	 ((CYCLE) == GPIO_DBCLK_8192CYCLE) || \
                                       	 ((CYCLE) == GPIO_DBCLK_16384CYCLE)|| \
                                       	 ((CYCLE) == GPIO_DBCLK_32768CYCLE))


/** @defgroup GPIO_Alternat_function_selection_define 
  * @{
  */ 
/** 
  * @brief AF 0 selection  
  */ 
#define GPIO_AF_NRST           ((uint8_t)0x00)  /* NRST Alternate Function mapping */
#define GPIO_AF_OSCIN          ((uint8_t)0x00)  /* OSCIN Alternate Function mapping */
#define GPIO_AF_OSCOUT         ((uint8_t)0x00)  /* OSCOUT Alternate Function mapping */
#define GPIO_AF_X32KOUT        ((uint8_t)0x00)  /* X32KOUT Alternate Function mapping */
#define GPIO_AF_X32KIN         ((uint8_t)0x00)  /* X32KIN Alternate Function mapping */
#define GPIO_AF_SWDIO          ((uint8_t)0x00)  /* SWDIO Alternate Function mapping */
#define GPIO_AF_SWDCLK         ((uint8_t)0x00)  /* SWDCLK Alternate Function mapping */


/** 
  * @brief PAx function selection  
  */ 
/*-------------------------- PA7 AFR function selection ok----------------------*/
#define GPIO_AF_ETIMER_CH4_PA7          ((uint8_t)0x01)  /* ETIMER_CH4 Alternate Function mapping */
#define GPIO_AF_CAN0_STDBY_PA7          ((uint8_t)0x03)  /* CAN0_STDBY Alternate Function mapping */
#define GPIO_AF_TIM10_TOG_PA7           ((uint8_t)0x04)  /* TIM10_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PA7              ((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */


/*-------------------------- PA4 AFR function selection ok----------------------*/
#define GPIO_AF_TIM2_CH1_PA4          	((uint8_t)0x01)  /* TIM2_CH1 Alternate Function mapping */
#define GPIO_AF_EUART0_RX_PA4          	((uint8_t)0x02)  /* EUART0_RX Alternate Function mapping */
#define GPIO_AF_CAN0_STDBY_PA4          ((uint8_t)0x03)  /* CAN0_STDBY Alternate Function mapping */
#define GPIO_AF_TIM10_TOGN_PA4          ((uint8_t)0x04)  /* TIM10_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PA4  			((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PA3 AFR function selection ok----------------------*/
#define GPIO_AF_ETIMER_CH1_PA3          ((uint8_t)0x01)  /* ETIMER_CH1 Alternate Function mapping */
#define GPIO_AF_EUART0_TX_PA3			((uint8_t)0x02)  /* EUART0_TX Alternate Function mapping */
#define GPIO_AF_CAN0_TX_PA3             ((uint8_t)0x03)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF_TIM11_EXT_PA3           ((uint8_t)0x04)  /* TIM11_EXT Alternate Function mapping */  	
#define GPIO_AF_ANALOG_PA3				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PA2 AFR function selection ok----------------------*/
#define GPIO_AF_TIM2_CH2_PA2 		  	((uint8_t)0x01)  /* TIM2_CH2 Alternate Function mapping */
#define GPIO_AF_EUART0_RX_PA2			((uint8_t)0x02)  /* EUART0_RX Alternate Function mapping */
#define GPIO_AF_CAN0_RX_PA2          	((uint8_t)0x03)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF_TIM11_GATE_PA2          ((uint8_t)0x04)  /* TIM11_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PA2     			((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PA1 AFR function selection ok----------------------*/
#define GPIO_AF_TIM2_CH1_PA1		 	((uint8_t)0x01)  /* TIM2_CH1 Alternate Function mapping */
#define GPIO_AF_I2C0_SCL_PA1			((uint8_t)0x02)  /* I2C0_SCL Alternate Function mapping */
#define GPIO_AF_EUART1_TX_PA1           ((uint8_t)0x03)  /* EUART1_TX Alternate Function mapping */
#define GPIO_AF_TIM11_TOGN_PA1          ((uint8_t)0x04)  /* TIM11_TOGN Alternate Function mapping */
#define GPIO_AF_VC_OUT_PA1              ((uint8_t)0x05)  /* SPI1_MOSI Alternate Function mapping */
#define GPIO_AF_ANALOG_PA1				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PA0 AFR function selection ok----------------------*/
#define GPIO_AF_TIM2_CH4_PA0		  	((uint8_t)0x01)  /* TIM2_CH4 Alternate Function mapping */
#define GPIO_AF_I2C0_SDA_PA0			((uint8_t)0x02)  /* I2C0_SDA Alternate Function mapping */
#define GPIO_AF_EUART1_RX_PA0           ((uint8_t)0x03)  /* EUART1_RX Alternate Function mapping */
#define GPIO_AF_TIM11_TOG_PA0      		((uint8_t)0x04)  /* TIM11_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PA0				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA15 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3_PA15         ((uint8_t)0x01)  /* ETIMER_CH3 Alternate Function mapping */
#define GPIO_AF_TIM10_GATE_PA15			((uint8_t)0x04)  /* TIM10_GATE Alternate Function mapping */
#define GPIO_AF_LVD_OUT_PA15            ((uint8_t)0x05)  /* LVD_OUT Alternate Function mapping */
#define GPIO_AF_ANALOG_PA15             ((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA14 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3N_PA14        ((uint8_t)0x01)  /* ETIMER_CH3N Alternate Function mapping */
#define GPIO_AF_HIRC_OUT_PA14           ((uint8_t)0x05)  /* HIRC_OUT Alternate Function mapping */
#define GPIO_AF_ANALOG_PA14				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA13 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3N_PA13        ((uint8_t)0x01)  /* ETIMER_CH3N Alternate Function mapping */
#define GPIO_AF_ASPI_MOSI_PA13			((uint8_t)0x02)  /* ASPI_MOSI Alternate Function mapping */
#define GPIO_AF_TIM11_TOGN_PA13         ((uint8_t)0x04)  /* TIM11_TOGN Alternate Function mapping */
#define GPIO_AF_LPTIM_GATE_PA13         ((uint8_t)0x05)  /* LPTIM_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PA13				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA12 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH2N_PA12        ((uint8_t)0x01)  /* ETIMER_CH2N Alternate Function mapping */
#define GPIO_AF_ASPI_SCK_PA12			((uint8_t)0x02)  /* ASPI_SCK Alternate Function mapping */
#define GPIO_AF_TIM11_TOG_PA12          ((uint8_t)0x04)  /* TIM11_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PA12				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA11 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1N_PA11        ((uint8_t)0x01)  /* ETIMER_CH1N Alternate Function mapping */
#define GPIO_AF_EUART1_TX_PA11			((uint8_t)0x02)  /* EUART1_TX Alternate Function mapping */
#define GPIO_AF_I2C0_SCL_PA11			((uint8_t)0x03)  /* I2C0_SCL Alternate Function mapping */
#define GPIO_AF_TIM11_EXT_PA11			((uint8_t)0x04)  /* TIM11_EXT Alternate Function mapping */
#define GPIO_AF_ANALOG_PA11				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA10 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3_PA10         ((uint8_t)0x01)  /* ETIMER_CH3 Alternate Function mapping */
#define GPIO_AF_EUART1_RX_PA10			((uint8_t)0x02)  /* EUART1_RX Alternate Function mapping */
#define GPIO_AF_I2C0_SDA_PA10         	((uint8_t)0x03)  /* I2C0_SDA Alternate Function mapping */
#define GPIO_AF_TIM11_GATE_PA10         ((uint8_t)0x04)  /* TIM11_GATE Alternate Function mapping */
#define GPIO_AF_LPTIM_TOG_PA10          ((uint8_t)0x05)  /* LPTIM_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PA10				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA9 AFR function selection OK-----------------------*/
#define GPIO_AF_TIM2_CH3_PA9          	((uint8_t)0x01)  /* TIM2_CH3 Alternate Function mapping */
#define GPIO_AF_TIM11_EXT_PA9           ((uint8_t)0x04)  /* TIM11_EXT Alternate Function mapping */
#define GPIO_AF_ANALOG_PA9				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PA8 AFR function selection OK-----------------------*/
#define GPIO_AF_ETIMER_CH1_PA8          ((uint8_t)0x01)  /* ETIMER_CH1 Alternate Function mapping */
#define GPIO_AF_TIM10_EXT_PA8           ((uint8_t)0x04)  /* TIM10_EXT Alternate Function mapping */
#define GPIO_AF_LIRC_OUT_PA8  			((uint8_t)0x05)  /* LIRC_OUT Alternate Function mapping */
#define GPIO_AF_ANALOG_PA8				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/** 
  * @brief PBx function selection  
  */ 
/*-------------------------- PB7 AFR function selection OK----------------------*/
#define GPIO_AF_I2C0_SCL_PB7			((uint8_t)0x02)  /* I2C0_SCL Alternate Function mapping */
#define GPIO_AF_ANALOG_PB7				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB6 AFR function selection OK----------------------*/
#define GPIO_AF_I2C0_SDA_PB6			((uint8_t)0x02)  /* I2C0_SDA Alternate Function mapping */
#define GPIO_AF_ANALOG_PB6				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB5 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1N_PB5		  	((uint8_t)0x01)  /* ETIMER_CH1N Alternate Function mapping */
#define GPIO_AF_ASPI_SSN_PB5			((uint8_t)0x02)  /* ASPI_SSN Alternate Function mapping */
#define GPIO_AF_CAN0_STDBY_PB5          ((uint8_t)0x03)  /* CAN0_STDBY Alternate Function mapping */
#define GPIO_AF_TIM10_TOGN_PB5			((uint8_t)0x04)  /* TIM10_TOGN Alternate Function mapping */
#define GPIO_AF_CLK_MCO_PB5             ((uint8_t)0x05)  /* CLK_MCO Alternate Function mapping */
#define GPIO_AF_ANALOG_PB5				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB4 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH2_PB4		  	((uint8_t)0x01)  /* ETIMER_CH2 Alternate Function mapping */
#define GPIO_AF_ASPI_MISO_PB4			((uint8_t)0x02)  /* ASPI_MISO Alternate Function mapping */
#define GPIO_AF_CAN0_RX_PB4             ((uint8_t)0x03)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF_TIM10_TOG_PB4          	((uint8_t)0x04)  /* TIM10_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PB4				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB3 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3_PB3		  	((uint8_t)0x01)  /* ETIMER_CH3 Alternate Function mapping */
#define GPIO_AF_ASPI_SCK_PB3			((uint8_t)0x02)  /* ASPI_SCK Alternate Function mapping */
#define GPIO_AF_EUART0_TX_PB3   		((uint8_t)0x03)  /* EUART0_TX Alternate Function mapping */
#define GPIO_AF_TIM10_EXT_PB3   		((uint8_t)0x04)  /* TIM10_EXT Alternate Function mapping */
#define GPIO_AF_LPTIM_TOG_PB3			((uint8_t)0x05)  /* LPTIM_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PB3				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB2 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3N_PB2		  	((uint8_t)0x01)  /* ETIMER_CH3N Alternate Function mapping */
#define GPIO_AF_EUART0_RX_PB2           ((uint8_t)0x03)  /* EUART0_RX Alternate Function mapping */
#define GPIO_AF_TIM10_GATE_PB2          ((uint8_t)0x04)  /* TIM10_GATE Alternate Function mapping */
#define GPIO_AF_LPTIM_TOGN_PB2          ((uint8_t)0x05)  /* LPTIM_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PB2				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB1 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1_PB1		  	((uint8_t)0x01)  /* ETIMER_CH1 Alternate Function mapping */
#define GPIO_AF_EUART1_TX_PB1			((uint8_t)0x02)  /* EUART1_TX Alternate Function mapping */
#define GPIO_AF_CAN0_TX_PB1				((uint8_t)0x03)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF_BEEP_OUT_PB1            ((uint8_t)0x05)  /* BEEP_OUT Alternate Function mapping */
#define GPIO_AF_ANALOG_PB1				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PB0 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1N_PB0         ((uint8_t)0x01)  /* ETIMER_CH1N Alternate Function mapping */
#define GPIO_AF_EUART1_RX_PB0			((uint8_t)0x02)  /* EUART1_RX Alternate Function mapping */
#define GPIO_AF_CAN0_RX_PB0  			((uint8_t)0x03)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF_NMI_b_PB0               ((uint8_t)0x05)  /* NMI_b Alternate Function mapping */
#define GPIO_AF_ANALOG_PB0				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PB14 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH4_PB14         	((uint8_t)0x01)  /* TIM2_CH4 Alternate Function mapping */
#define GPIO_AF_TIM10_GATE_PB14         ((uint8_t)0x04)  /* TIM10_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PB14				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PB13 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3N_PB13        ((uint8_t)0x01)  /* ETIMER_CH3N Alternate Function mapping */
#define GPIO_AF_I2C0_SDA_PB13           ((uint8_t)0x03)  /* I2C0_SDA Alternate Function mapping */
#define GPIO_AF_TIM11_EXT_PB13			((uint8_t)0x04)  /* TIM11_EXT Alternate Function mapping */
#define GPIO_AF_ANALOG_PB13				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */


/*------------------------- PB9 AFR function selection OK-----------------------*/
#define GPIO_AF_ETIMER_CH2N_PB9         ((uint8_t)0x01)  /* ETIMER_CH2N Alternate Function mapping */
#define GPIO_AF_SPI1_MISO_PB9			((uint8_t)0x02)  /* SPI1_MISO Alternate Function mapping */
#define GPIO_AF_CAN0_RX_PB9    			((uint8_t)0x03)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF_TIM10_TOGN_PB9			((uint8_t)0x04)  /* TIM10_TOGN Alternate Function mapping */
#define GPIO_AF_LPTIM_TOG_PB9           ((uint8_t)0x05)  /* LPTIM_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PB9				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PB8 AFR function selection OK-----------------------*/
#define GPIO_AF_ETIMER_CH2_PB8          ((uint8_t)0x01)  /* ETIMER_CH2 Alternate Function mapping */
#define GPIO_AF_SPI1_SSN_PB8			((uint8_t)0x02)  /* SPI1_SSN Alternate Function mapping */
#define GPIO_AF_CAN0_TX_PB8       		((uint8_t)0x03)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF_TIM10_GATE_PB8          ((uint8_t)0x04)  /* TIM10_GATE Alternate Function mapping */
#define GPIO_AF_LPTIM_GATE_PB8    		((uint8_t)0x05)  /* LPTIM_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PB8				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/** 
  * @brief PCx function selection  
  */ 
/*-------------------------- PC7 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH2_PC7          	((uint8_t)0x01)  /* TIM2_CH2 Alternate Function mapping */
#define GPIO_AF_ASPI_MISO_PC7			((uint8_t)0x02)  /* ASPI_MISO Alternate Function mapping */
#define GPIO_AF_CAN0_TX_PC7             ((uint8_t)0x03)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF_ANALOG_PC7				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC6 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH3_PC6          	((uint8_t)0x01)  /* TIM2_CH3 Alternate Function mapping */
#define GPIO_AF_ASPI_SSN_PC6			((uint8_t)0x02)  /* SPI1_SSN Alternate Function mapping */
#define GPIO_AF_CAN0_RX_PC6   			((uint8_t)0x03)  /* CAN0_RX Alternate Function mapping */
#define GPIO_AF_ANALOG_PC6				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC5 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_BKIN_PC5         ((uint8_t)0x01)  /* ETIMER_BKIN Alternate Function mapping */
#define GPIO_AF_SPI1_SSN_PC5			((uint8_t)0x02)  /* SPI1_SSN Alternate Function mapping */
#define GPIO_AF_TIM11_TOGN_PC5          ((uint8_t)0x04)  /* TIM11_TOGN Alternate Function mapping */
#define GPIO_AF_LPTIM_TOGN_PC5          ((uint8_t)0x05)  /* LPTIM_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PC5				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC4 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH3_PC4          	((uint8_t)0x01)  /* TIM2_CH3 Alternate Function mapping */
#define GPIO_AF_EUART0_TX_PC4			((uint8_t)0x02)  /* EUART0_TX Alternate Function mapping */
#define GPIO_AF_TIM10_GATE_PC4          ((uint8_t)0x04)  /* TIM10_GATE Alternate Function mapping */
#define GPIO_AF_BEEP_OUT_PC4            ((uint8_t)0x05)  /* BEEP_OUT Alternate Function mapping */
#define GPIO_AF_ANALOG_PC4				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC3 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH2N_PC3         ((uint8_t)0x01)  /* ETIMER_CH2N Alternate Function mapping */
#define GPIO_AF_ASPI_MOSI_PC3			((uint8_t)0x02)  /* ASPI_MOSI Alternate Function mapping */
#define GPIO_AF_CAN0_TX_PC3             ((uint8_t)0x03)  /* CAN0_TX Alternate Function mapping */
#define GPIO_AF_ANALOG_PC3				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC2 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH4_PC2          ((uint8_t)0x01)  /* ETIMER_CH4 Alternate Function mapping */
#define GPIO_AF_ASPI_SCK_PC2			((uint8_t)0x02)  /* ASPI_SCK Alternate Function mapping */	
#define GPIO_AF_ANALOG_PC2				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PC1 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3_PC1          ((uint8_t)0x01)  /* ETIMER_CH3 Alternate Function mapping */
#define GPIO_AF_TIM11_GATE_PC1        	((uint8_t)0x04)  /* TIM11_GATE Alternate Function mapping */
#define GPIO_AF_LPTIM_GATE_PC1          ((uint8_t)0x05)  /* LPTIM_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PC1				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PC15 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH2_PC15         	((uint8_t)0x01)  /* TIM2_CH2 Alternate Function mapping */
#define GPIO_AF_ASPI_SSN_PC15			((uint8_t)0x02)  /* ASPI_SSN Alternate Function mapping */
#define GPIO_AF_TIM11_TOG_PC15			((uint8_t)0x04)  /* TIM11_TOG Alternate Function mapping */
#define GPIO_AF_ANALOG_PC15				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PC14 AFR function selection OK----------------------*/
#define GPIO_AF_TIM2_CH1_PC14         	((uint8_t)0x01)  /* TIM2_CH1 Alternate Function mapping */
#define GPIO_AF_TIM11_TOGN_PC14         ((uint8_t)0x04)  /* TIM11_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PC14				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PC9 AFR function selection OK-----------------------*/
#define GPIO_AF_ETIMER_CH2N_PC9         ((uint8_t)0x01)  /* ETIMER_CH2N Alternate Function mapping */
#define GPIO_AF_TIM10_EXT_PC9   		((uint8_t)0x04)  /* TIM10_EXT Alternate Function mapping */
#define GPIO_AF_LPTIM_GATE_PC9			((uint8_t)0x05)  /* LPTIM_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PC9				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*------------------------- PC8 AFR function selection OK-----------------------*/
#define GPIO_AF_ETIMER_CH2_PC8         	((uint8_t)0x01)  /* ETIMER_CH2 Alternate Function mapping */
#define GPIO_AF_TIM10_TOGN_PC8          ((uint8_t)0x04)  /* TIM10_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PC8				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/** 
  * @brief PDx function selection  
  */ 
/*-------------------------- PD5 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3N_PD5         ((uint8_t)0x01)  /* ETIMER_CH3N Alternate Function mapping */
#define GPIO_AF_TIM10_TOGN_PD5			((uint8_t)0x04)  /* TIM10_TOGN Alternate Function mapping */
#define GPIO_AF_LPTIM_EXT_PD5           ((uint8_t)0x05)  /* LPTIM_EXT Alternate Function mapping */
#define GPIO_AF_ANALOG_PD5				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PD3 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH3_PD3          ((uint8_t)0x01)  /* ETIMER_CH3 Alternate Function mapping */
#define GPIO_AF_SPI1_SSN_PD3			((uint8_t)0x02)  /* SPI1_SSN Alternate Function mapping */
#define GPIO_AF_TIM11_TOG_PD3           ((uint8_t)0x04)  /* TIM11_TOG Alternate Function mapping */
#define GPIO_AF_NMI_b_PD3               ((uint8_t)0x05)  /* NMI_b Alternate Function mapping */
#define GPIO_AF_ANALOG_PD3				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PD2 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1N_PD2         ((uint8_t)0x01)  /* ETIMER_CH1N Alternate Function mapping */
#define GPIO_AF_TIM11_GATE_PD2          ((uint8_t)0x04)  /* TIM11_GATE Alternate Function mapping */
#define GPIO_AF_ANALOG_PD2				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PD1 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1_PD1          ((uint8_t)0x01)  /* ETIMER_CH1 Alternate Function mapping */
#define GPIO_AF_SPI1_MOSI_PD1			((uint8_t)0x02)  /* SPI1_MOSI Alternate Function mapping */
#define GPIO_AF_TIM10_EXT_PD1           ((uint8_t)0x04)  /* TIM10_EXT Alternate Function mapping */
#define GPIO_AF_LPTIM_EXT_PD1      		((uint8_t)0x05)  /* LPTIM_EXT Alternate Function mapping */
#define GPIO_AF_ANALOG_PD1				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/*-------------------------- PD0 AFR function selection OK----------------------*/
#define GPIO_AF_ETIMER_CH1N_PD0         ((uint8_t)0x01)  /* ETIMER_CH1N Alternate Function mapping */
#define GPIO_AF_SPI1_SCK_PD0			((uint8_t)0x02)  /* SPI1_SCK Alternate Function mapping */
#define GPIO_AF_TIM10_TOG_PD0           ((uint8_t)0x04)  /* TIM10_TOG Alternate Function mapping */
#define GPIO_AF_LPTIM_TOGN_PD0			((uint8_t)0x05)  /* LPTIM_TOGN Alternate Function mapping */
#define GPIO_AF_ANALOG_PD0				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */

/** 
  * @brief PEx function selection  
  */ 
/*-------------------------- PE6 AFR function selection OK----------------------*/
#define GPIO_AF_ANALOG_PE6				((uint8_t)0x0F)  /* ANALOG Alternate Function mapping */


#define IS_GPIO_AF(GPIO_AF)     	  	(((GPIO_AF) >= 0) && ((GPIO_AF) <= 0x0F))


/* Exported functions --------------------------------------------------------*/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);   
void GPIO_AFIODeInit(void);      
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);  
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);  
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);   
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);  
void GPIO_DBSyncCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState);  
void GPIO_DBPinSyncCmd(GPIO_TypeDef* GPIOx, uint32_t DB_Pin, FunctionalState NewState);  
void GPIO_DBClkCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState);  
void GPIO_SetDBClk(GPIO_TypeDef* GPIOx, uint32_t DBClk);  
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);  
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);   
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);  
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);  
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  
void GPIO_PinPuPdCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_PUPD);  
void GPIO_PortDriveCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, FunctionalState NewState);  
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint8_t GPIO_PinSource, uint8_t GPIO_AF);   
uint16_t GPIO_EXIT_ReadRawIntSR(GPIO_TypeDef* GPIOx);
BitAction GPIO_EXIT_Get_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
BitAction GPIO_EXIT_Get_IT_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EXIT_Clear_IT_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EXIT_StructInit(EXIT_InitTypeDef* EXIT_InitStruct);
void GPIO_EXTILineConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, EXIT_InitTypeDef* EXIT_InitStructure);


#ifdef __cplusplus
}
#endif

#endif   /*__CPS32K21X_GPIO_H__ */

