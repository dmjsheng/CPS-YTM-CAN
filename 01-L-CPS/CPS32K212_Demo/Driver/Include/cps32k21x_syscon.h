/*Define to prevent recursive inclusion --------------------------------------*/
#ifndef __CPS32K21X_SYSCON_H__
#define __CPS32K21X_SYSCON_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_etimer.h" 
#include "cps32k21x_advtim.h" 


/** @addtogroup NMI_InitTypeDef
  * @{
  */
typedef struct
{
    uint32_t EnStatus;   /*!< NMI使能状态 */              
	
	uint32_t filterEn;   /*!< NMI滤波使能 */
	
	uint32_t clkSel;     /*!< NMI时钟选择 */
	
	uint32_t filterDiv;  /*!< NMI滤波分频 */
} NMI_InitTypeDef;


/** @addtogroup SYSCON
  * @{
  */ 	 
#define SYSCON_UNLOCK_KEY      ((uint32_t)0x55AA6699)   /*!< Unlock key */
#define SYSCON_LOCK_KEY        ((uint32_t)0x55AA6698)   /*!< Lock key */


/* Exported types ------------------------------------------------------------*/
#define IS_SYSCON_ALL_PERIPH(PERIPH)    	((PERIPH) == SYSCON)


/** @defgroup SYSCON_CFGR0 register  
  * @{
  */ 
#define FAST_IO_DIS             (BIT3)    /*!< GPIO Fast禁止 */	 
#define IWDT_DSLP_STOP          (BIT2)    /*!< IWDT在DeepSleep模式停止计数 */	 
#define DBGDLSP_DIS             (BIT1)    /*!< 不允许在Debug模式进入Deep Sleep */	 
#define LOCKUP_EN               (BIT0)    /*!< Cortex-M0 LookUp功能使能 */     


/** @defgroup SYSCON_PORTINTCR register  
  * @{
  */ 
#define PAD_DSLP_EN      		(BIT1)   /*!< 进入Deep Sleep模式，PAD中断模式不自动切换 */	
#define PAD_INTSEL_DSLP  		(BIT0)   /*!< Deep Sleep中断产生模式 */	
#define PAD_INTSEL_SLEEP  		(0)      /*!< Sleep中断产生模式 */

#define IS_PAD_INTSEL(SEL) 		(((SEL) == PAD_INTSEL_DSLP) ||\
								 ((SEL) == PAD_INTSEL_SLEEP))


/** @defgroup SYSCON_PORTCR register/管脚控制寄存器
  * @{
  */
/*------------------------ ASPI SSN从机选择输入信号选择-----------------------*/
#define ASPI_SSN_SEL_Mask       ((uint32_t)0x07 << 16)
#define ASPI_SSN_SEL_High       ((uint32_t)0x00 << 16)    /*!< ASPI SSN信号来源于：固定高电平 */	
#define ASPI_SSN_SEL_PB5        ((uint32_t)0x01 << 16)    /*!< ASPI SSN信号来源于：PB5 */	
#define ASPI_SSN_SEL_PC6        ((uint32_t)0x02 << 16)    /*!< ASPI SSN信号来源于：PC6    */	
#define ASPI_SSN_SEL_PC15       ((uint32_t)0x03 << 16)    /*!< ASPI SSN信号来源于：PC15   */	

#define IS_SPI0_SSN_SEL(SEL) 	(((SEL) == ASPI_SSN_SEL_High) ||\
                              	 ((SEL) == ASPI_SSN_SEL_PB5) ||\
                              	 ((SEL) == ASPI_SSN_SEL_PC6) ||\
								 ((SEL) == ASPI_SSN_SEL_PC15))


/*------------------------ LPTIM EXT输入信号选择------------------------------*/
#define LPTIM_EXT_SEL_Mask      ((uint32_t)0x07 << 13)
#define LPTIM_EXT_SEL_SELF      ((uint32_t)0x00 << 13)    /*!< LPTIM EXT信号来源于：LPTIM_EXT */	
#define LPTIM_EXT_SEL_VC        ((uint32_t)0x01 << 13)    /*!< LPTIM EXT信号来源于：VC */	

#define IS_LPTIM_EXT_SEL(SEL) 	(((SEL) == LPTIM_EXT_SEL_SELF) ||\
								 ((SEL) == LPTIM_EXT_SEL_VC))


/*------------------------ LPTIM门控输入信号选择------------------------------*/
#define LPTIM_GATE_SEL_Mask          ((uint32_t)0x07 << 10)
#define LPTIM_GATE_SEL_SELF          ((uint32_t)0x00 << 10)   /*!< LPTIM GATE信号来源于：LPTIM_GATE */	
#define LPTIM_GATE_SEL_EUART0_RXD    ((uint32_t)0x01 << 10)   /*!< LPTIM GATE信号来源于：EUART0_RXD */
#define LPTIM_GATE_SEL_EUART1_RXD    ((uint32_t)0x02 << 10)   /*!< LPTIM GATE信号来源于：EUART1_RXD */
#define LPTIM_GATE_SEL_VC            ((uint32_t)0x04 << 10)   /*!< LPTIM GATE信号来源于：VC之输出 */

#define IS_LPTIM_GATE_SEL(SEL) 		(((SEL) == LPTIM_GATE_SEL_SELF) ||\
                              	 	 ((SEL) == LPTIM_GATE_SEL_EUART0_RXD) ||\
                              		 ((SEL) == LPTIM_GATE_SEL_EUART1_RXD) ||\
								 	 ((SEL) == LPTIM_GATE_SEL_VC))


/*------------------------ TIM11门控输入信号选择------------------------------*/
#define TIM11_GATE_SEL_Mask          ((uint32_t)0x07 << 7)
#define TIM11_GATE_SEL_SELF          ((uint32_t)0x00 << 7)  /*!< TIM11 GATE信号来源于：TIM11_GATE */
#define TIM11_GATE_SEL_EUART0_RXD    ((uint32_t)0x01 << 7)  /*!< TIM11 GATE信号来源于：EUART0_RXD */
#define TIM11_GATE_SEL_EUART1_RXD    ((uint32_t)0x02 << 7)  /*!< TIM11 GATE信号来源于：EUART1_RXD */
#define TIM11_GATE_SEL_VC            ((uint32_t)0x04 << 7)  /*!< TIM11 GATE信号来源于：VC */

#define IS_TIM11_GATE_SEL(SEL) 		(((SEL) == TIM11_GATE_SEL_SELF) ||\
                              	 	 ((SEL) == TIM11_GATE_SEL_EUART0_RXD) ||\
                              		 ((SEL) == TIM11_GATE_SEL_EUART1_RXD) ||\
								 	 ((SEL) == TIM11_GATE_SEL_VC))


/*------------------------ TIM10门控输入信号选择------------------------------*/
#define TIM10_GATE_SEL_Mask          ((uint32_t)0x07 << 4)
#define TIM10_GATE_SEL_SELF          ((uint32_t)0x00 << 4)  /*!< TIM10 GATE信号来源于：TIM10_GATE */
#define TIM10_GATE_SEL_EUART0_RXD    ((uint32_t)0x01 << 4)  /*!< TIM10 GATE信号来源于：EUART0_RXD */
#define TIM10_GATE_SEL_EUART1_RXD    ((uint32_t)0x02 << 4)  /*!< TIM10 GATE信号来源于：EUART1_RXD */
#define TIM10_GATE_SEL_VC            ((uint32_t)0x04 << 4)  /*!< TIM10 GATE信号来源于：VC */

#define IS_TIM10_GATE_SEL(SEL) 		(((SEL) == TIM10_GATE_SEL_SELF) ||\
                              	 	 ((SEL) == TIM10_GATE_SEL_EUART0_RXD) ||\
                              		 ((SEL) == TIM10_GATE_SEL_EUART1_RXD) ||\
								 	 ((SEL) == TIM10_GATE_SEL_VC))


/*------------------------ SPI1 SSN从机选择输入信号选择-----------------------*/
#define SPI1_SSN_SEL_Mask       ((uint32_t)0x0F << 0)
#define SPI1_SSN_SEL_High       ((uint32_t)0x00 << 0)   /*!< SPI1 SSN信号来源于：固定高电平 */	
#define SPI1_SSN_SEL_PB8	    ((uint32_t)0x01 << 0)   /*!< SPI1 SSN信号来源于：PB8 */	
#define SPI1_SSN_SEL_PC5    	((uint32_t)0x02 << 0)   /*!< SPI1 SSN信号来源于：PC5 */	
#define SPI1_SSN_SEL_PD3		((uint32_t)0x03 << 0)   /*!< SPI1 SSN信号来源于：PD3 */	


#define IS_SPI1_SSN_SEL(SEL) 	(((SEL) == SPI1_SSN_SEL_High) ||\
                              	 ((SEL) == SPI1_SSN_SEL_PB8)  ||\
                              	 ((SEL) == SPI1_SSN_SEL_PC5)  ||\
								 ((SEL) == SPI1_SSN_SEL_PD3))


#define CLK_FAIL_BREAK_EN      (BIT22)    /*!< 系统时钟停止检出时，ETIMER Break使能 */	
#define DSLP_BREAK_EN          (BIT21)    /*!< Deep Sleep模式下，ETIMER Break使能 */	
#define BREAK_OUT_CFG          (BIT20)    /*!< OCx/OCxN在Break模式下同时输出0 */	


/*------------------------- ETIMER ETR信号来源选择 ------------------------*/
#define ETIMER_ETR_SEL_Mask     ((uint32_t)0x0F << 16)
#define ETIMER_ETR_SEL_Low      ((uint32_t)0x00 << 16)   /*!< ETIMER ETR信号来源：固定低电平 */	
#define ETIMER_ETR_SEL_PA1	    ((uint32_t)0x01 << 16)   /*!< ETIMER ETR信号来源：PA1 */	
#define ETIMER_ETR_SEL_PA2      ((uint32_t)0x02 << 16)   /*!< ETIMER ETR信号来源：PA2 */
#define ETIMER_ETR_SEL_PA3      ((uint32_t)0x03 << 16)   /*!< ETIMER ETR信号来源：PA3 */
#define ETIMER_ETR_SEL_PB4	   	((uint32_t)0x04 << 16)   /*!< ETIMER ETR信号来源：PB4 */
#define ETIMER_ETR_SEL_PB5	   	((uint32_t)0x05 << 16)   /*!< ETIMER ETR信号来源：PB5 */
#define ETIMER_ETR_SEL_PC3		((uint32_t)0x06 << 16)   /*!< ETIMER ETR信号来源：PC3 */
#define ETIMER_ETR_SEL_PC4		((uint32_t)0x07 << 16)   /*!< ETIMER ETR信号来源：PC4 */
#define ETIMER_ETR_SEL_PC5		((uint32_t)0x08 << 16)   /*!< ETIMER ETR信号来源：PC5 */
#define ETIMER_ETR_SEL_PC6		((uint32_t)0x09 << 16)   /*!< ETIMER ETR信号来源：PC6 */
#define ETIMER_ETR_SEL_PC7		((uint32_t)0x0A << 16)   /*!< ETIMER ETR信号来源：PC7 */
#define ETIMER_ETR_SEL_PD1		((uint32_t)0x0B << 16)   /*!< ETIMER ETR信号来源：PD1 */
#define ETIMER_ETR_SEL_PD2		((uint32_t)0x0C << 16)   /*!< ETIMER ETR信号来源：PD2 */
#define ETIMER_ETR_SEL_VCOUT	((uint32_t)0x0D << 16)   /*!< ETIMER ETR信号来源：VCOUT */
      
#define IS_TIM_ETR_SEL(SEL) 	(((SEL) == ETIMER_ETR_SEL_Low) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PA1) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PA2) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PA3) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PB4) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PB5) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PC3) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PC4) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PC5) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PC6) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PC7) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PD1) ||\
                              	 ((SEL) == ETIMER_ETR_SEL_PD2) ||\
								 ((SEL) == ETIMER_ETR_SEL_VCOUT))


/*------------------------ ETIMER输入通道信号来源选择 ------------------------*/
#define ETIMER_CH_SEL_Mask			((uint32_t)0x07)
#define ETIMER_CH_SEL_SELF         	((uint32_t)0x00)  	/*!< ETIMER_CH输入通道信号来源：ETIMER_CH */
#define ETIMER_CH_SEL_EUART0_RXD	((uint32_t)0x01)	/*!< ETIMER_CH输入通道信号来源：EUART0_RXD */
#define ETIMER_CH_SEL_EUART1_RXD	((uint32_t)0x02)	/*!< ETIMER_CH输入通道信号来源：EUART1_RXD */
#define ETIMER_CH_SEL_LIRC			((uint32_t)0x04)	/*!< ETIMER_CH输入通道信号来源：LIRC */
#define ETIMER_CH_SEL_VC			((uint32_t)0x05)	/*!< ETIMER_CH输入通道信号来源：VC的输出 */

#define IS_TIM_CH_SEL(SEL) 		    (((SEL) == ETIMER_CH_SEL_SELF) ||\
                              	 	 ((SEL) == ETIMER_CH_SEL_EUART0_RXD) ||\
                              	 	 ((SEL) == ETIMER_CH_SEL_EUART1_RXD) ||\
                              	 	 ((SEL) == ETIMER_CH_SEL_LIRC) ||\
								     ((SEL) == ETIMER_CH_SEL_VC))

/*------------------------- TIM2 ETR信号来源选择 ------------------------*/
#define TIM2_ETR_SEL_Mask     ((uint32_t)0x0F << 16)
#define TIM2_ETR_SEL_Low      ((uint32_t)0x00 << 16)   /*!< TIM2 ETR信号来源：固定低电平 */	
#define TIM2_ETR_SEL_PA1	  ((uint32_t)0x01 << 16)   /*!< TIM2 ETR信号来源：PA1 */	
#define TIM2_ETR_SEL_PA2      ((uint32_t)0x02 << 16)   /*!< TIM2 ETR信号来源：PA2 */
#define TIM2_ETR_SEL_PA3      ((uint32_t)0x03 << 16)   /*!< TIM2 ETR信号来源：PA3 */
#define TIM2_ETR_SEL_PB4	  ((uint32_t)0x04 << 16)   /*!< TIM2 ETR信号来源：PB4 */
#define TIM2_ETR_SEL_PB5	  ((uint32_t)0x05 << 16)   /*!< TIM2 ETR信号来源：PB5 */
#define TIM2_ETR_SEL_PC3      ((uint32_t)0x06 << 16)   /*!< TIM2 ETR信号来源：PC3 */
#define TIM2_ETR_SEL_PC4	  ((uint32_t)0x07 << 16)   /*!< TIM2 ETR信号来源：PC4 */
#define TIM2_ETR_SEL_PC5	  ((uint32_t)0x08 << 16)   /*!< TIM2 ETR信号来源：PC5 */
#define TIM2_ETR_SEL_PC6	  ((uint32_t)0x09 << 16)   /*!< TIM2 ETR信号来源：PC6 */
#define TIM2_ETR_SEL_PC7	  ((uint32_t)0x0A << 16)   /*!< TIM2 ETR信号来源：PC7 */
#define TIM2_ETR_SEL_PD1	  ((uint32_t)0x0B << 16)   /*!< TIM2 ETR信号来源：PD1 */
#define TIM2_ETR_SEL_PD2	  ((uint32_t)0x0C << 16)   /*!< TIM2 ETR信号来源：PD2 */
#define TIM2_ETR_SEL_VCOUT	  ((uint32_t)0x0D << 16)   /*!< TIM2 ETR信号来源：VCOUT */
      
#define IS_TIM2_ETR_SEL(SEL) 	(((SEL) == TIM2_ETR_SEL_Low) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PA1) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PA2) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PA3) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PB4) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PB5) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PC3) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PC4) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PC5) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PC6) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PC7) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PD1) ||\
                              	 ((SEL) == TIM2_ETR_SEL_PD2) ||\
								 ((SEL) == TIM2_ETR_SEL_VCOUT))

/*------------------------ ADVTIM(TIM2)输入通道信号来源选择 ------------------------*/
#define TIM2_CH_SEL_Mask	     ((uint32_t)0x07)
#define TIM2_CH_SEL_SELF         ((uint32_t)0x00)  	/*!< TIM2_CH输入通道信号来源：TIM2_CHx */
#define TIM2_CH_SEL_EUART0_RXD   ((uint32_t)0x01)	/*!< TIM2_CH输入通道信号来源：EUART0_RXD */
#define TIM2_CH_SEL_EUART1_RXD	 ((uint32_t)0x02)	/*!< TIM2_CH输入通道信号来源：EUART1_RXD */
#define TIM2_CH_SEL_LIRC		 ((uint32_t)0x04)	/*!< TIM2_CH输入通道信号来源：LIRC */
#define TIM2_CH_SEL_VC			 ((uint32_t)0x05)	/*!< TIM2_CH输入通道信号来源：VC的输出 */

#define IS_TIM2_CH_SEL(SEL) 		(((SEL) == TIM2_CH_SEL_SELF) ||\
                              	 	 ((SEL) == TIM2_CH_SEL_EUART0_RXD) ||\
                              	 	 ((SEL) == TIM2_CH_SEL_EUART1_RXD) ||\
                              	 	 ((SEL) == TIM2_CH_SEL_LIRC) ||\
								     ((SEL) == TIM2_CH_SEL_VC))


/** @defgroup SYSCON_RSTCTRL register/外部复位控制寄存器
  * @{
  */ 
#define RSTPAD_DISABLE     ((uint32_t)(0x5A690001))   /*!< 关闭PE6端口外部复位功能 */
#define RSTPAD_ENABLE      ((uint32_t)(0x5A690000))   /*!< 使能PE6端口外部复位功能 */


/** @defgroup NMI定义
  * @{
  */ 
#define NMI_ENABLE     		(BIT0)   /*!< NMI使能 */
#define NMI_DISABLE   		 (0)	 /*!< NMI禁止 */

#define NMI_CKSEL_LIRC  	(BIT1)   /*!< NMI滤波时钟选择LIRC */
#define NMI_CKSEL_PCLK  	 (0)     /*!< NMI滤波时钟选择PCLK */

#define NMI_FLT_ENABLE  	(BIT2)   /*!< NMI滤波使能 */
#define NMI_FLT_DISABLE 	 (0)	 /*!< NMI滤波禁止 */

#define NMI_FLT_DIV_Mask   	((uint32_t)0x03 << 4)
#define NMI_FLT_DIV1	   	((uint32_t)0x00 << 4)     /*!< 1分频 */
#define NMI_FLT_DIV2	   	((uint32_t)0x01 << 4)     /*!< 2分频 */
#define NMI_FLT_DIV4	   	((uint32_t)0x02 << 4)     /*!< 4分频 */
#define NMI_FLT_DIV8	   	((uint32_t)0x03 << 4)     /*!< 8分频 */

#define IS_NMI_FLT_DIV(DIV)	 	(((DIV) == NMI_FLT_DIV1) ||\
                              	 ((DIV) == NMI_FLT_DIV2) ||\
                              	 ((DIV) == NMI_FLT_DIV4) ||\
								 ((DIV) == NMI_FLT_DIV8))


#define NMI_INTF     (BIT0)    /*!< NMI信号中断标志 */

#define IS_NMI_INTF(FLAG)    ((FLAG) == NMI_INTF)


/* Exported functions --------------------------------------------------------*/
void SYSCON_DeInit(void);
void SYSCON_CortexM0LockUpCmd(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_DBG_DSLP_DisConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_IWDG_DSLP_StopConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_GPIO_Fast_Cmd(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_PadIT_Mode_Select(SYSCON_TypeDef* SYSCONx, uint32_t PadIntSel);
void SYSCON_ASPI_SSN_Config(SYSCON_TypeDef* SYSCONx, uint32_t ASPI_SSN_Sel);
void SYSCON_SPI1_SSN_Config(SYSCON_TypeDef* SYSCONx, uint32_t SP1_SSN_Sel);
void SYSCON_TIM10_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t TIM10_Gate_Sel);
void SYSCON_TIM11_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t TIM11_Gate_Sel);
void SYSCON_LPTIM_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t LPTIM_Gate_Sel);
void SYSCON_LPTIM_EXTConfig(SYSCON_TypeDef* SYSCONx, uint32_t LPTIM_EXT_Sel);
void SYSCON_ETIMER_ChannelConfig(SYSCON_TypeDef* SYSCONx, uint8_t ETIMER_Channel, uint32_t InputSignal_Sel);
void SYSCON_ETIMER_ETRSignalConfig(SYSCON_TypeDef* SYSCONx, uint32_t ETR_Signal_Sel);
void SYSCON_ETIMER_Break_OutCfg(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_ETIMER_SetBreakZero(SYSCON_TypeDef* SYSCONx);
void SYSCON_ClkFail_BreakConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void SYSCON_TIM2_ChannelConfig(SYSCON_TypeDef* SYSCONx, uint8_t TIMx_Channel, uint32_t InputSignal_Sel);
void SYSCON_TIM2_ETRSignalConfig(SYSCON_TypeDef* SYSCONx, uint32_t ETR_Signal_Sel);
void SYSCON_DSLP_BreakConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState);
void NMI_StructInit(NMI_InitTypeDef* NMI_InitStruct);
void SYSCON_NMI_Init(SYSCON_TypeDef* SYSCONx, NMI_InitTypeDef* NMI_InitStruct);
ITStatus SYSCON_NMI_GetITStatus(SYSCON_TypeDef* SYSCONx, uint32_t NMI_IT_Flag);
void SYSCON_NMI_ClearITFlag(SYSCON_TypeDef* SYSCONx, uint32_t NMI_IT_Flag);
void SYSCON_RSTPad_Config(SYSCON_TypeDef* SYSCONx, uint32_t RstPad_Set);


#ifdef __cplusplus
}
#endif

#endif   /*__CPS32K21X_SYSCON_H__ */


