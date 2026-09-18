/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_LPTIM_H__   
#define __CPS32K21X_LPTIM_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


/** 
  * @brief  LPTIM Initialize structure definition
  */ 
typedef struct
{
  	uint32_t worMode;       /*<! LPTIM工作模式 */        
	uint32_t ct_mode_sel;   /*<! 计数器/定时器功能选择 */
	uint32_t tck_sel;       /*<! LPTIM时钟选 */
	uint32_t gate_en;       /*<! 定时器门控Gate使能 */
	uint32_t gatePolarity;  /*<! Gate门控极性 */
	uint32_t tck_en;        /*<! LPTIM计数时钟使能 */                                  
} LPTIM_InitTypeDef;


/* Exported types ------------------------------------------------------------*/
#define IS_LPTIM_ALL_PERIPH(PERIPH)    (((PERIPH) == LPTIM) 

/* mask set */
#define LPTIM_Mode_MASK      		(BIT1)   		/*<! 工作模式设置掩码 */  
#define LPTIM_CT_MASK        		(BIT2)  		/*<! 计数器/定时器功能选择设置掩码 */
#define LPTIM_TCK_MASK      		(BIT5 | BIT4)   /*<! LPTIM时钟选择掩码 */
#define LPTIM_GATE_MASK      		(BIT6)   		/*<! 定时器门控使能 */
#define LPTIM_GATE_POLARITY_MASK  	(BIT7)          /*<! GATE门控极性 */
#define LPTIM_TCKEN_MASK   		    (BIT9)          /*<! LPTIM 计数时钟使能 */

/* work mode define */
#define LPTIM_MODE1          	(0)        /*<! 模式1无重载模式16位计数器/定时器 */ 
#define LPTIM_MODE2          	(BIT1)     /*<! 模式2自动重装载16位计数器/定时器 */ 
#define IS_LPTIM_MODE(MODE)  	(((MODE) == LPTIM_MODE1) ||\
                                 ((MODE) == LPTIM_MODE2))

/* Counter or Timer define */
#define LPTIM_COUNTER          	(BIT2)     /*<! 计数器功能 */
#define LPTIM_TIMER          	(0)        /*<! 定时器功能 */
#define IS_LPTIM_CT(CT_SEL)     (((CT_SEL) == LPTIM_COUNTER) ||\
                                 ((CT_SEL) == LPTIM_TIMER))

/* TCK Source Select */
#define TCK_SEL_PCLK      		((uint32_t)(0x00 << 4))   /*<! LPTIM时钟源为PCLK, 读取定时器计数值时经过同步 */
#define TCK_SEL_PCLK1      		((uint32_t)(0x01 << 4))   /*<! LPTIM时钟源为PCLK, 读取定时器计数值无同步 */
#define TCK_SEL_LXT       		((uint32_t)(0x02 << 4))   /*<! LPTIM时钟源为LXT */
#define TCK_SEL_LIRC      		((uint32_t)(0x03 << 4))   /*<! LPTIM时钟源为LIRC */
#define IS_TCK_SEL(TCK)  		(((TCK) == TCK_SEL_PCLK) ||\
                                 ((TCK) == TCK_SEL_PCLK1))||\
                                 ((TCK) == TCK_SEL_LXT))  ||\
                                 ((TCK) == TCK_SEL_LIRC))
																																				
/* GATE enable */
#define LPTIM_GATE_ENABLE       (BIT6)    /*<! LPTIM门控Gate使能 */
#define LPTIM_GATE_DISABLE      (0)		  /*<! LPTIM门控Gate禁止 */
#define IS_LPTIM_GATE(GATE)     (((GATE) == LPTIM_GATE_ENABLE) ||\
                                 ((GATE) == LPTIM_GATE_DISABLE))

/* GATE Polority define */
#define GATE_Polarity_High          (0)       /*<! 门控极性高有效 */
#define GATE_Polarity_Low           (BIT7)    /*<! 门控极性低有效 */
#define IS_GATE_POLARITY(GATE_P)    (((GATE_P) == GATE_Polarity_High) ||\
                                     ((GATE_P) == GATE_Polarity_Low))

/* TCK Enable/Disable define */
#define LPTIM_TCK_ENABLE            (BIT9)    /*<! TCK时钟使能 */
#define LPTIM_TCK_DISABLE           (0)       /*<! TCK时钟禁止 */
#define IS_LPTIM_TCK_EN(Status)     (((Status) == LPTIM_TCK_ENABLE) ||\
                                     ((Status) == LPTIM_TCK_DISABLE))

/* LPTIM RUN define */
#define LPTIM_RUN_ENABLE      	(BIT0)    /*<! LPTIM定时器运行 */
#define LPTIM_RUN_DISABLE     	 (0)      /*<! LPTIM定时器停止 */

/* LPTIM TOG_EN define */
#define LPTIM_TOG_ENABLE      	(BIT3)    /*<! TOG输出使能 */
#define LPTIM_TOG_DISABLE     	(0)       /*<! TOG输出禁止 */

/* LPTIM INT_EN define */
#define LPTIM_IT_ENABLE       	(BIT8)    /*<! LPTIM中断使能 */
#define LPTIM_IT_DISABLE      	(0)       /*<! LPTIM中断禁止 */

/* LPTIM WT_FLAG set */
#define LPTIM_WT_FLAG         	(BIT16)   

/* LPTIM IT FLAG */
#define LPTIM_IT_FLAG         	(BIT0) 
#define IS_LPTIM_IT(FLAG)     	((FLAG) == LPTIM_IT_FLAG)

#define IS_LPTIM_LOAD(VALUE)        (((VALUE) >= 0) && ((VALUE) <= (uint32_t)0xFFFF))                              
#define IS_LPTIM_BGLOAD(VALUE)      (((VALUE) >= 0) && ((VALUE) <= (uint32_t)0xFFFF))
                                     

/* Exported functions --------------------------------------------------------*/
void LPTIM_DeInit(LPTIM_TypeDef* LPTIMx);
uint32_t LPTIM_ReadCnt(LPTIM_TypeDef* LPTIMx);
void LPTIM_Init(LPTIM_TypeDef* LPTIMx, LPTIM_InitTypeDef * LPTIM_InitStruct);
void LPTIM_StructInit(LPTIM_InitTypeDef* LPTIM_InitStruct);
void LPTIM_Cmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState);
void LPTIM_TogCmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState);
void LPTIM_ITConfig(LPTIM_TypeDef* LPTIMx, FunctionalState NewState);
FlagStatus LPTIM_GetWTFlagStatus(LPTIM_TypeDef* LPTIMx);
void LPTIM_BGloadConfig(LPTIM_TypeDef* LPTIMx, uint32_t Value);
void LPTIM_LoadConfig(LPTIM_TypeDef* LPTIMx, uint32_t Value);
ITStatus LPTIM_GetITStatus(LPTIM_TypeDef* LPTIMx, uint32_t IntFlag);
void LPTIM_ClearITFlag(LPTIM_TypeDef* LPTIMx, uint32_t IntFlag);


#ifdef __cplusplus
}
#endif


#endif   /* __CPS32K21X_LPTIM_H__ */

