/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_TIMER_H__
#define __CPS32K21X_TIMER_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


/** 
  * @brief  Timer Base Init structure definition
  * @note   This structure is used with TIM10/TIM11 
  */
typedef struct
{
    uint32_t Gate_Polarity;    /*!<Gate门控极性控制，@ref TIM_GATE_Polarity */

    uint32_t GateState;        /*!<定时器门控 0：无门控，TR=1时定时器工作  ，1：只有端口GATE有效并且TR=1时才工作 */

    uint32_t CounterMode;      /*!<计数器工作模式:计数模式 or 定时模式*/

    uint32_t TmrModeSel;       /*!<定时器模式选择:free-running/reload */ 

    uint32_t TmrSize;          /*!<定时器计数位数:16bits/32bits*/ 

    uint32_t TmrOneShort;      /*!<Counting mode:wrapping/one_shot 计数器运行一次使能 0：重复运行;   1：运行一次*/ 

    uint32_t ClockDivision;    /*!< Specifies the clock division.
                                 This parameter can be a value of @ref TIM_Clock_Division_CKD */
} TIM_TimeBaseInitTypeDef;       

/* Control register Mask */
#define TMRxCR_MASK       (BIT9 | BIT7)

/** @defgroup TIM_Exported_constants 
  * @{
  */
#define IS_BASETIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM10) ||\
                                       ((PERIPH) == TIM11))
                                                                                                                                                                                                                                                            
/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */
#define TIM_Prescale_DIV1           ((uint32_t)0x00000000)    /*!< TIM 预除频选择: 1分频 */
#define TIM_Prescale_DIV2           ((uint32_t)0x00000001)    /*!< TIM 预除频选择: 2分频 */
#define TIM_Prescale_DIV4           ((uint32_t)0x00000002)    /*!< TIM 预除频选择: 4分频 */
#define TIM_Prescale_DIV8           ((uint32_t)0x00000003)    /*!< TIM 预除频选择: 8分频 */
#define TIM_Prescale_DIV16          ((uint32_t)0x00000004)    /*!< TIM 预除频选择: 16分频 */
#define TIM_Prescale_DIV32          ((uint32_t)0x00000005)    /*!< TIM 预除频选择: 32分频 */
#define TIM_Prescale_DIV64          ((uint32_t)0x00000006)    /*!< TIM 预除频选择: 64分频 */
#define TIM_Prescale_DIV128         ((uint32_t)0x00000007)    /*!< TIM 预除频选择: 128分频 */

#define IS_TIM_PRESCALE_DIV(DIV)    (((DIV) == TIM_Prescale_DIV1) ||\
									 ((DIV) == TIM_Prescale_DIV2) ||\
									 ((DIV) == TIM_Prescale_DIV4) ||\
									 ((DIV) == TIM_Prescale_DIV8) ||\
									 ((DIV) == TIM_Prescale_DIV16) ||\
									 ((DIV) == TIM_Prescale_DIV32) ||\
									 ((DIV) == TIM_Prescale_DIV64) ||\
									 ((DIV) == TIM_Prescale_DIV128))														


/* set free_runing/periodic 定时器模式 */
#define TIM_Mode1_FreeRun       (0)        /*!< 0：模式1自由计数模式 */
#define TIM_Mode2_ReLoad        (BIT6)     /*!< 1：模式2自动重装载计数模式 */

#define IS_TIM_TMRMS(MS) 		(((MS) == TIM_TMRMS_FreeRun) ||\
								 ((MS) == TIM_TMRMS_ReLoad))


/* set TIM interrupt enable 中断使能控制 */
#define TIM_TMRIE_DISABLE       (0)      /*!< 定时器禁止中断 */
#define TIM_TMRIE_ENABLE        (BIT5)   /*!< 定时器使能中断 */

#define IS_TIM_TMRIE(IE_EN) 	(((IE_EN) == TIM_TMRIE_DISABLE) ||\
								 ((IE_EN) == TIM_TMRIE_ENABLE))


/* set 16bits/32bits's counting/设置定时器最大计数值 */
#define TIM_TMRSIZE_16BIT       (0)      /*!< 16位计数器 */
#define TIM_TMRSIZE_32BIT       (BIT4)   /*!< 32位计数器 */ 

#define IS_TIM_TMRSZ(SIZE_SEL) 	(((SIZE_SEL) == TIM_TMRSIZE_16BIT) ||\
								 ((SIZE_SEL) == TIM_TMRSIZE_32BIT))

/* set Repeat(重复模式)/one_shot */
#define TIM_TMROS_REPEAT        (0)        /*!< 0: 重复模式 */
#define TIM_TMR0S_ONESHOT       (BIT3)     /*!< 1：oneshot 模式 */

#define IS_TIM_TMROS(OS_SEL) 	(((OS_SEL) == TIM_TMROS_REPEAT) ||\
								 ((OS_SEL) == TIM_TMR0S_ONESHOT))

																	 
/** @defgroup TIM_CT_MODE计数模式/定时模式选择
  * @{
  */
#define TIM_CT_TIMER          	(0)        /*!< 定时模式 */
#define TIM_CT_COUNTER        	(BIT8)     /*!< 计数器模式 */

#define IS_TIM_CT_MODE(MODE)    (((MODE) == TIM_CT_TIMER) ||\
                                 ((MODE) == TIM_CT_COUNTER))


/** @defgroup TIM_TOG_Output/TIM反转输出
  * @{
  */
/* TOG and TOGN Output the same value "0" */
#define TIM_TOG_Out_Zero         (0) 

/* TOG and TOGN Output the contrary value */
#define TIM_TOG_EN               (BIT9) 

#define IS_TIM_TOG_EN(TOGEN)     (((TOGEN) == TIM_TOG_Out_Zero) ||\
                                  ((TOGEN) == TIM_TOG_EN))

/** @defgroup TIM_Gate_Control/TIM门控制位选择
  * @{
  */
#define TIM_GATE_DISABLE        (0)       /*!< Gate门控禁止 */
#define TIM_GATE_ENABLE         (BIT10)   /*!< Gate门控使能 */

#define IS_GATE_STATE(STATE)    (((STATE) == TIM_GATE_DISABLE) ||\
                                 ((STATE) == TIM_GATE_ENABLE))
/**
  * @}TIM_TR_ENABLE
  */
#define TIM_TR_DISABLE        (0)        /*!< 定时器停止 */
#define TIM_TR_ENABLE         (BIT7)     /*!< 定时器运行 */

#define IS_TR_STATE(STATE)    (((STATE) == TIM_TR_DISABLE) ||\
                               ((STATE) == TIM_TR_ENABLE))	
																																										
/**
  * @}TIM_IT_Enable
  */
#define TIM_IT_DISABLE        (0)  		 /*!< 禁止定时器中断 */
#define TIM_IT_ENABLE         (BIT5)     /*!< 使能定时器中断 */

#define IS_IT_STATE(STATE)    (((STATE) == TIM_TR_DISABLE) ||\
                               ((STATE) == TIM_TR_ENABLE))	
																							
/**
  * @}TIM_IT_FLAG
  */
#define TIM_IT_FLAG        ((uint32_t)0x000000001)  


/** @defgroup TIM_GATE_Polarity 
  * @{
  */
#define TIM_GATE_Polarity_High       (0)       /*!< 门控极性高电平有效 */ 
#define TIM_GATE_Polarity_Low       (BIT11)    /*!< 门控极性低电平有效 */ 

#define IS_TIM_GATE_POLARITY_STATE(STATE)  (((STATE) == TIM_GATE_Polarity_High) ||\
                                         	((STATE) == TIM_GATE_Polarity_Low))


/* Exported functions --------------------------------------------------------*/
void TIM_DeInit(TIM_TypeDef* TIMx);  
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);  
void TIM_StructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);  
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);  
void TIM_TogCmd(TIM_TypeDef* TIMx, FunctionalState NewState);  
void TIM_ITConfig(TIM_TypeDef* TIMx, FunctionalState NewState);  
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode);  
void TIM_SelectGatePolarity(TIM_TypeDef* TIMx, uint32_t TIM_GatePolarity); 
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_Div);  
uint8_t TIM_GetPrescaler(TIM_TypeDef* TIMx);  
void TIM_SetTimerLoadRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value);  
void TIM_SetTimerAutoReload(TIM_TypeDef* TIMx, uint32_t reloadValue);  
uint32_t TIM_GetTimerLoadRegister(TIM_TypeDef* TIMx);   
uint32_t TIM_GetCounterRegister(TIM_TypeDef* TIMx);  
ITStatus TIM_Get_RawIT_Flag(TIM_TypeDef* TIMx, uint32_t TIM_RawFlag);  
ITStatus TIM_Get_MskIT_Flag(TIM_TypeDef* TIMx, uint32_t TIM_MskFlag);  
void TIM_ClearITFlag(TIM_TypeDef* TIMx, uint32_t TIM_IT_Flag); 


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_TIMER_H__ */

