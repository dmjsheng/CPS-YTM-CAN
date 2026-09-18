/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_ETIMER_H__
#define __CPS32K21X_ETIMER_H__


#ifdef __cplusplus
 extern "C" {
#endif
		
/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"   
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


/** 
  * @brief  Time Base Init structure definition
  * @note   This structure is used with all ETIMERx, where x can be 1 
  */
typedef struct
{
	uint16_t ETIMER_Prescaler;         /*!< Specifies the prescaler value used to divide the ETIMER clock.
	                                   This parameter can be a number between 0x0000 and 0xFFFF */

	uint16_t ETIMER_CounterMode;       /*!< Specifies the counter mode.
	                                   This parameter can be a value of @ref ETIMER_Counter_Mode */

	uint16_t ETIMER_Period;            /*!< Specifies the period value to be loaded into the active
	                                   Auto-Reload Register at the next update event.
	                                   This parameter must be a number between 0x0000 and 0xFFFF. */ 

	uint16_t ETIMER_ClockDivision;     /*!< Specifies the clock division.
	                                  This parameter can be a value of @ref ETIMER_Clock_Division_CKD */

	uint8_t ETIMER_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
	                                   reaches zero, an update event is generated and counting restarts
	                                   from the RCR value (N).
	                                   This means in PWM mode that (N+1) corresponds to:
	                                      - the number of PWM periods in edge-aligned mode
	                                      - the number of half PWM period in center-aligned mode
	                                   This parameter must be a number between 0x00 and 0xFF. */
} ETIMER_TimeBaseInitTypeDef;       

/** 
  * @brief  ETIMER Output Compare Init structure definition  
  */
typedef struct
{
	uint16_t ETIMER_OCMode;        /*!< Specifies the ETIMER mode.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_and_PWM_modes */

	uint16_t ETIMER_OutputState;   /*!< Specifies the ETIMER Output Compare state.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_state */

	uint16_t ETIMER_OutputNState;  /*!< Specifies the ETIMER complementary Output Compare state.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_N_state */

	uint16_t ETIMER_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
	                               This parameter can be a number between 0x0000 and 0xFFFF */

	uint16_t ETIMER_OCPolarity;    /*!< Specifies the output polarity.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_Polarity */

	uint16_t ETIMER_OCNPolarity;   /*!< Specifies the complementary output polarity.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_N_Polarity */

	uint16_t ETIMER_OCIdleState;   /*!< Specifies the ETIMER Output Compare pin state during Idle state.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_Idle_State */

	uint16_t ETIMER_OCNIdleState;  /*!< Specifies the ETIMER Output Compare pin state during Idle state.
	                               This parameter can be a value of @ref ETIMER_Output_Compare_N_Idle_State */
} ETIMER_OCInitTypeDef;

/** 
  * @brief  ETIMER Input Capture Init structure definition  
  */

typedef struct
{
	uint16_t ETIMER_Channel;      /*!< Specifies the ETIMER channel.
	                              This parameter can be a value of @ref ETIMER_Channel */

	uint16_t ETIMER_ICPolarity;   /*!< Specifies the active edge of the input signal.
	                              This parameter can be a value of @ref ETIMER_Input_Capture_Polarity */

	uint16_t ETIMER_ICSelection;  /*!< Specifies the input.
	                              This parameter can be a value of @ref ETIMER_Input_Capture_Selection */

	uint16_t ETIMER_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
	                              This parameter can be a value of @ref ETIMER_Input_Capture_Prescaler */

	uint16_t ETIMER_ICFilter;     /*!< Specifies the input capture filter.
	                              This parameter can be a number between 0x0 and 0xF */
} ETIMER_ICInitTypeDef;

/** 
  * @brief  BDTR structure definition    
  */
typedef struct
{
	uint16_t ETIMER_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
	                                  This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */

	uint16_t ETIMER_OSSIState;        /*!< Specifies the Off-State used in Idle state.
	                                  This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */

	uint16_t ETIMER_LOCKLevel;        /*!< Specifies the LOCK level parameters.
	                                  This parameter can be a value of @ref Lock_level */ 

	uint16_t ETIMER_DeadTime;         /*!< Specifies the delay time between the switching-off and the
	                                  switching-on of the outputs.
	                                  This parameter can be a number between 0x00 and 0xFF  */

	uint16_t ETIMER_Break;            /*!< Specifies whether the ETIMER Break input is enabled or not. 
	                                  This parameter can be a value of @ref Break_Input_enable_disable */

	uint16_t ETIMER_BreakPolarity;    /*!< Specifies the ETIMER Break Input pin polarity.
	                                  This parameter can be a value of @ref Break_Polarity */

	uint16_t ETIMER_AutomaticOutput;  /*!< Specifies whether the ETIMER Automatic Output feature is enabled or not. 
	                                  This parameter can be a value of @ref ETIMER_AOE_Bit_Set_Reset */
} ETIMER_BDTRInitTypeDef;


/** @defgroup ETIMER_Exported_constants 
  * @{
  */
#define IS_ETIMER_ALL_PERIPH(PERIPH)   ((PERIPH) == ETIMER) 


/* ---------------------- ETIMER registers bit mask ------------------------ */
#define SMCR_ETR_Mask       ((uint16_t)0x00FF) 
#define CCMR_Offset         ((uint16_t)0x0018)
#define CCER_CCE_Set        ((uint16_t)0x0001)  
#define	CCER_CCNE_Set       ((uint16_t)0x0004) 


/*******************  Bit definition for ETIMER_CR1 register  ********************/
#define  ETIMER_CR1_CEN            ((uint16_t)0x0001)     /*!< Counter enable */
#define  ETIMER_CR1_UDIS           ((uint16_t)0x0002)     /*!< Update disable */
#define  ETIMER_CR1_URS            ((uint16_t)0x0004)     /*!< Update request source */
#define  ETIMER_CR1_OPM            ((uint16_t)0x0008)     /*!< One pulse mode */
#define  ETIMER_CR1_DIR            ((uint16_t)0x0010)     /*!< Direction */

#define  ETIMER_CR1_CMS            ((uint16_t)0x0060)     /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  ETIMER_CR1_CMS_0          ((uint16_t)0x0020)     /*!< Bit 0 */
#define  ETIMER_CR1_CMS_1          ((uint16_t)0x0040)     /*!< Bit 1 */

#define  ETIMER_CR1_ARPE           ((uint16_t)0x0080)     /*!< Auto-reload preload enable */

#define  ETIMER_CR1_CKD            ((uint16_t)0x0300)     /*!< CKD[1:0] bits (clock division) */
#define  ETIMER_CR1_CKD_0          ((uint16_t)0x0100)     /*!< Bit 0 */
#define  ETIMER_CR1_CKD_1          ((uint16_t)0x0200)     /*!< Bit 1 */

/*******************  Bit definition for ETIMER_CR2 register  ********************/
#define  ETIMER_CR2_CCPC           ((uint16_t)0x0001)     /*!< Capture/Compare Preloaded Control */
#define  ETIMER_CR2_CCUS           ((uint16_t)0x0004)     /*!< Capture/Compare Control Update Selection */
#define  ETIMER_CR2_CCDS           ((uint16_t)0x0008)     /*!< Capture/Compare DMA Selection */

#define  ETIMER_CR2_MMS            ((uint16_t)0x0070)     /*!< MMS[2:0] bits (Master Mode Selection) */
#define  ETIMER_CR2_MMS_0          ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_CR2_MMS_1          ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_CR2_MMS_2          ((uint16_t)0x0040)     /*!< Bit 2 */

#define  ETIMER_CR2_TI1S           ((uint16_t)0x0080)     /*!< TI1 Selection */
#define  ETIMER_CR2_OIS1           ((uint16_t)0x0100)     /*!< Output Idle state 1 (OC1 output) */
#define  ETIMER_CR2_OIS1N          ((uint16_t)0x0200)     /*!< Output Idle state 1 (OC1N output) */
#define  ETIMER_CR2_OIS2           ((uint16_t)0x0400)     /*!< Output Idle state 2 (OC2 output) */
#define  ETIMER_CR2_OIS2N          ((uint16_t)0x0800)     /*!< Output Idle state 2 (OC2N output) */
#define  ETIMER_CR2_OIS3           ((uint16_t)0x1000)     /*!< Output Idle state 3 (OC3 output) */
#define  ETIMER_CR2_OIS3N          ((uint16_t)0x2000)     /*!< Output Idle state 3 (OC3N output) */
#define  ETIMER_CR2_OIS4           ((uint16_t)0x4000)     /*!< Output Idle state 4 (OC4 output) */

/*******************  Bit definition for ETIMER_SMCR register  *******************/
#define  ETIMER_SMCR_SMS           ((uint16_t)0x0007)     /*!< SMS[2:0] bits (Slave mode selection) */
#define  ETIMER_SMCR_SMS_0         ((uint16_t)0x0001)     /*!< Bit 0 */
#define  ETIMER_SMCR_SMS_1         ((uint16_t)0x0002)     /*!< Bit 1 */
#define  ETIMER_SMCR_SMS_2         ((uint16_t)0x0004)     /*!< Bit 2 */

#define  ETIMER_SMCR_TS            ((uint16_t)0x0070)     /*!< TS[2:0] bits (Trigger selection) */
#define  ETIMER_SMCR_TS_0          ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_SMCR_TS_1          ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_SMCR_TS_2          ((uint16_t)0x0040)     /*!< Bit 2 */

#define  ETIMER_SMCR_MSM           ((uint16_t)0x0080)     /*!< Master/slave mode */

#define  ETIMER_SMCR_ETF           ((uint16_t)0x0F00)     /*!< ETF[3:0] bits (External trigger filter) */
#define  ETIMER_SMCR_ETF_0         ((uint16_t)0x0100)     /*!< Bit 0 */
#define  ETIMER_SMCR_ETF_1         ((uint16_t)0x0200)     /*!< Bit 1 */
#define  ETIMER_SMCR_ETF_2         ((uint16_t)0x0400)     /*!< Bit 2 */
#define  ETIMER_SMCR_ETF_3         ((uint16_t)0x0800)     /*!< Bit 3 */

#define  ETIMER_SMCR_ETPS          ((uint16_t)0x3000)     /*!< ETPS[1:0] bits (External trigger prescaler) */
#define  ETIMER_SMCR_ETPS_0        ((uint16_t)0x1000)     /*!< Bit 0 */
#define  ETIMER_SMCR_ETPS_1        ((uint16_t)0x2000)     /*!< Bit 1 */

#define  ETIMER_SMCR_ECE           ((uint16_t)0x4000)     /*!< External clock enable */
#define  ETIMER_SMCR_ETP           ((uint16_t)0x8000)     /*!< External trigger polarity */

/*******************  Bit definition for ETIMER_DIER register  *******************/
#define  ETIMER_DIER_UIE           ((uint16_t)0x0001)     /*!< Update interrupt enable */
#define  ETIMER_DIER_CC1IE         ((uint16_t)0x0002)     /*!< Capture/Compare 1 interrupt enable */
#define  ETIMER_DIER_CC2IE         ((uint16_t)0x0004)     /*!< Capture/Compare 2 interrupt enable */
#define  ETIMER_DIER_CC3IE         ((uint16_t)0x0008)     /*!< Capture/Compare 3 interrupt enable */
#define  ETIMER_DIER_CC4IE         ((uint16_t)0x0010)     /*!< Capture/Compare 4 interrupt enable */
#define  ETIMER_DIER_COMIE         ((uint16_t)0x0020)     /*!< COM interrupt enable */
#define  ETIMER_DIER_TIE           ((uint16_t)0x0040)     /*!< Trigger interrupt enable */
#define  ETIMER_DIER_BIE           ((uint16_t)0x0080)     /*!< Break interrupt enable */
#define  ETIMER_DIER_UDE           ((uint16_t)0x0100)     /*!< Update DMA request enable */
#define  ETIMER_DIER_CC1DE         ((uint16_t)0x0200)     /*!< Capture/Compare 1 DMA request enable */
#define  ETIMER_DIER_CC2DE         ((uint16_t)0x0400)     /*!< Capture/Compare 2 DMA request enable */
#define  ETIMER_DIER_CC3DE         ((uint16_t)0x0800)     /*!< Capture/Compare 3 DMA request enable */
#define  ETIMER_DIER_CC4DE         ((uint16_t)0x1000)     /*!< Capture/Compare 4 DMA request enable */
#define  ETIMER_DIER_COMDE         ((uint16_t)0x2000)     /*!< COM DMA request enable */
#define  ETIMER_DIER_TDE           ((uint16_t)0x4000)     /*!< Trigger DMA request enable */

/********************  Bit definition for ETIMER_SR register  ********************/
#define  ETIMER_SR_UIF             ((uint16_t)0x0001)     /*!< Update interrupt Flag */
#define  ETIMER_SR_CC1IF           ((uint16_t)0x0002)     /*!< Capture/Compare 1 interrupt Flag */
#define  ETIMER_SR_CC2IF           ((uint16_t)0x0004)     /*!< Capture/Compare 2 interrupt Flag */
#define  ETIMER_SR_CC3IF           ((uint16_t)0x0008)     /*!< Capture/Compare 3 interrupt Flag */
#define  ETIMER_SR_CC4IF           ((uint16_t)0x0010)     /*!< Capture/Compare 4 interrupt Flag */
#define  ETIMER_SR_COMIF           ((uint16_t)0x0020)     /*!< COM interrupt Flag */
#define  ETIMER_SR_TIF             ((uint16_t)0x0040)     /*!< Trigger interrupt Flag */
#define  ETIMER_SR_BIF             ((uint16_t)0x0080)     /*!< Break interrupt Flag */
#define  ETIMER_SR_CC1OF           ((uint16_t)0x0200)     /*!< Capture/Compare 1 Overcapture Flag */
#define  ETIMER_SR_CC2OF           ((uint16_t)0x0400)     /*!< Capture/Compare 2 Overcapture Flag */
#define  ETIMER_SR_CC3OF           ((uint16_t)0x0800)     /*!< Capture/Compare 3 Overcapture Flag */
#define  ETIMER_SR_CC4OF           ((uint16_t)0x1000)     /*!< Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for ETIMER_EGR register  ********************/
#define  ETIMER_EGR_UG             ((uint8_t)0x01)        /*!< Update Generation */
#define  ETIMER_EGR_CC1G           ((uint8_t)0x02)        /*!< Capture/Compare 1 Generation */
#define  ETIMER_EGR_CC2G           ((uint8_t)0x04)        /*!< Capture/Compare 2 Generation */
#define  ETIMER_EGR_CC3G           ((uint8_t)0x08)        /*!< Capture/Compare 3 Generation */
#define  ETIMER_EGR_CC4G           ((uint8_t)0x10)        /*!< Capture/Compare 4 Generation */
#define  ETIMER_EGR_COMG           ((uint8_t)0x20)        /*!< Capture/Compare Control Update Generation */
#define  ETIMER_EGR_TG             ((uint8_t)0x40)        /*!< Trigger Generation */
#define  ETIMER_EGR_BG             ((uint8_t)0x80)        /*!< Break Generation */

/******************  Bit definition for ETIMER_CCMR1 register  *******************/
#define  ETIMER_CCMR1_CC1S         ((uint16_t)0x0003)     /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  ETIMER_CCMR1_CC1S_0       ((uint16_t)0x0001)     /*!< Bit 0 */
#define  ETIMER_CCMR1_CC1S_1       ((uint16_t)0x0002)     /*!< Bit 1 */

#define  ETIMER_CCMR1_OC1FE        ((uint16_t)0x0004)     /*!< Output Compare 1 Fast enable */
#define  ETIMER_CCMR1_OC1PE        ((uint16_t)0x0008)     /*!< Output Compare 1 Preload enable */

#define  ETIMER_CCMR1_OC1M         ((uint16_t)0x0070)     /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define  ETIMER_CCMR1_OC1M_0       ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_CCMR1_OC1M_1       ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_CCMR1_OC1M_2       ((uint16_t)0x0040)     /*!< Bit 2 */

#define  ETIMER_CCMR1_OC1CE        ((uint16_t)0x0080)     /*!< Output Compare 1Clear Enable */

#define  ETIMER_CCMR1_CC2S         ((uint16_t)0x0300)     /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  ETIMER_CCMR1_CC2S_0       ((uint16_t)0x0100)     /*!< Bit 0 */
#define  ETIMER_CCMR1_CC2S_1       ((uint16_t)0x0200)     /*!< Bit 1 */

#define  ETIMER_CCMR1_OC2FE        ((uint16_t)0x0400)     /*!< Output Compare 2 Fast enable */
#define  ETIMER_CCMR1_OC2PE        ((uint16_t)0x0800)     /*!< Output Compare 2 Preload enable */

#define  ETIMER_CCMR1_OC2M         ((uint16_t)0x7000)     /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define  ETIMER_CCMR1_OC2M_0       ((uint16_t)0x1000)     /*!< Bit 0 */
#define  ETIMER_CCMR1_OC2M_1       ((uint16_t)0x2000)     /*!< Bit 1 */
#define  ETIMER_CCMR1_OC2M_2       ((uint16_t)0x4000)     /*!< Bit 2 */

#define  ETIMER_CCMR1_OC2CE        ((uint16_t)0x8000)     /*!< Output Compare 2 Clear Enable */


#define  ETIMER_CCMR1_IC1PSC       ((uint16_t)0x000C)     /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  ETIMER_CCMR1_IC1PSC_0     ((uint16_t)0x0004)     /*!< Bit 0 */
#define  ETIMER_CCMR1_IC1PSC_1     ((uint16_t)0x0008)     /*!< Bit 1 */

#define  ETIMER_CCMR1_IC1F         ((uint16_t)0x00F0)     /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define  ETIMER_CCMR1_IC1F_0       ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_CCMR1_IC1F_1       ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_CCMR1_IC1F_2       ((uint16_t)0x0040)     /*!< Bit 2 */
#define  ETIMER_CCMR1_IC1F_3       ((uint16_t)0x0080)     /*!< Bit 3 */

#define  ETIMER_CCMR1_IC2PSC       ((uint16_t)0x0C00)     /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  ETIMER_CCMR1_IC2PSC_0     ((uint16_t)0x0400)     /*!< Bit 0 */
#define  ETIMER_CCMR1_IC2PSC_1     ((uint16_t)0x0800)     /*!< Bit 1 */

#define  ETIMER_CCMR1_IC2F         ((uint16_t)0xF000)     /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define  ETIMER_CCMR1_IC2F_0       ((uint16_t)0x1000)     /*!< Bit 0 */
#define  ETIMER_CCMR1_IC2F_1       ((uint16_t)0x2000)     /*!< Bit 1 */
#define  ETIMER_CCMR1_IC2F_2       ((uint16_t)0x4000)     /*!< Bit 2 */
#define  ETIMER_CCMR1_IC2F_3       ((uint16_t)0x8000)     /*!< Bit 3 */

/******************  Bit definition for ETIMER_CCMR2 register  *******************/
#define  ETIMER_CCMR2_CC3S         ((uint16_t)0x0003)     /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  ETIMER_CCMR2_CC3S_0       ((uint16_t)0x0001)     /*!< Bit 0 */
#define  ETIMER_CCMR2_CC3S_1       ((uint16_t)0x0002)     /*!< Bit 1 */

#define  ETIMER_CCMR2_OC3FE        ((uint16_t)0x0004)     /*!< Output Compare 3 Fast enable */
#define  ETIMER_CCMR2_OC3PE        ((uint16_t)0x0008)     /*!< Output Compare 3 Preload enable */

#define  ETIMER_CCMR2_OC3M         ((uint16_t)0x0070)     /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define  ETIMER_CCMR2_OC3M_0       ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_CCMR2_OC3M_1       ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_CCMR2_OC3M_2       ((uint16_t)0x0040)     /*!< Bit 2 */

#define  ETIMER_CCMR2_OC3CE        ((uint16_t)0x0080)     /*!< Output Compare 3 Clear Enable */

#define  ETIMER_CCMR2_CC4S         ((uint16_t)0x0300)     /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  ETIMER_CCMR2_CC4S_0       ((uint16_t)0x0100)     /*!< Bit 0 */
#define  ETIMER_CCMR2_CC4S_1       ((uint16_t)0x0200)     /*!< Bit 1 */

#define  ETIMER_CCMR2_OC4FE        ((uint16_t)0x0400)     /*!< Output Compare 4 Fast enable */
#define  ETIMER_CCMR2_OC4PE        ((uint16_t)0x0800)     /*!< Output Compare 4 Preload enable */

#define  ETIMER_CCMR2_OC4M         ((uint16_t)0x7000)     /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define  ETIMER_CCMR2_OC4M_0       ((uint16_t)0x1000)     /*!< Bit 0 */
#define  ETIMER_CCMR2_OC4M_1       ((uint16_t)0x2000)     /*!< Bit 1 */
#define  ETIMER_CCMR2_OC4M_2       ((uint16_t)0x4000)     /*!< Bit 2 */

#define  ETIMER_CCMR2_OC4CE        ((uint16_t)0x8000)     /*!< Output Compare 4 Clear Enable */


#define  ETIMER_CCMR2_IC3PSC       ((uint16_t)0x000C)     /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  ETIMER_CCMR2_IC3PSC_0     ((uint16_t)0x0004)     /*!< Bit 0 */
#define  ETIMER_CCMR2_IC3PSC_1     ((uint16_t)0x0008)     /*!< Bit 1 */

#define  ETIMER_CCMR2_IC3F         ((uint16_t)0x00F0)     /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define  ETIMER_CCMR2_IC3F_0       ((uint16_t)0x0010)     /*!< Bit 0 */
#define  ETIMER_CCMR2_IC3F_1       ((uint16_t)0x0020)     /*!< Bit 1 */
#define  ETIMER_CCMR2_IC3F_2       ((uint16_t)0x0040)     /*!< Bit 2 */
#define  ETIMER_CCMR2_IC3F_3       ((uint16_t)0x0080)     /*!< Bit 3 */

#define  ETIMER_CCMR2_IC4PSC       ((uint16_t)0x0C00)     /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  ETIMER_CCMR2_IC4PSC_0     ((uint16_t)0x0400)     /*!< Bit 0 */
#define  ETIMER_CCMR2_IC4PSC_1     ((uint16_t)0x0800)     /*!< Bit 1 */

#define  ETIMER_CCMR2_IC4F         ((uint16_t)0xF000)     /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define  ETIMER_CCMR2_IC4F_0       ((uint16_t)0x1000)     /*!< Bit 0 */
#define  ETIMER_CCMR2_IC4F_1       ((uint16_t)0x2000)     /*!< Bit 1 */
#define  ETIMER_CCMR2_IC4F_2       ((uint16_t)0x4000)     /*!< Bit 2 */
#define  ETIMER_CCMR2_IC4F_3       ((uint16_t)0x8000)     /*!< Bit 3 */

/*******************  Bit definition for ETIMER_CCER register  *******************/
#define  ETIMER_CCER_CC1E          ((uint16_t)0x0001)     /*!< Capture/Compare 1 output enable */
#define  ETIMER_CCER_CC1P          ((uint16_t)0x0002)     /*!< Capture/Compare 1 output Polarity */
#define  ETIMER_CCER_CC1NE         ((uint16_t)0x0004)     /*!< Capture/Compare 1 Complementary output enable */
#define  ETIMER_CCER_CC1NP         ((uint16_t)0x0008)     /*!< Capture/Compare 1 Complementary output Polarity */
#define  ETIMER_CCER_CC2E          ((uint16_t)0x0010)     /*!< Capture/Compare 2 output enable */
#define  ETIMER_CCER_CC2P          ((uint16_t)0x0020)     /*!< Capture/Compare 2 output Polarity */
#define  ETIMER_CCER_CC2NE         ((uint16_t)0x0040)     /*!< Capture/Compare 2 Complementary output enable */
#define  ETIMER_CCER_CC2NP         ((uint16_t)0x0080)     /*!< Capture/Compare 2 Complementary output Polarity */
#define  ETIMER_CCER_CC3E          ((uint16_t)0x0100)     /*!< Capture/Compare 3 output enable */
#define  ETIMER_CCER_CC3P          ((uint16_t)0x0200)     /*!< Capture/Compare 3 output Polarity */
#define  ETIMER_CCER_CC3NE         ((uint16_t)0x0400)     /*!< Capture/Compare 3 Complementary output enable */
#define  ETIMER_CCER_CC3NP         ((uint16_t)0x0800)     /*!< Capture/Compare 3 Complementary output Polarity */
#define  ETIMER_CCER_CC4E          ((uint16_t)0x1000)     /*!< Capture/Compare 4 output enable */
#define  ETIMER_CCER_CC4P          ((uint16_t)0x2000)     /*!< Capture/Compare 4 output Polarity */
#define  ETIMER_CCER_CC4NP         ((uint16_t)0x8000)     /*!< Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for ETIMER_CNT register  ********************/
#define  ETIMER_CNT_CNT            ((uint16_t)0xFFFF)     /*!< Counter Value */

/*******************  Bit definition for ETIMER_PSC register  ********************/
#define  ETIMER_PSC_PSC            ((uint16_t)0xFFFF)     /*!< Prescaler Value */

/*******************  Bit definition for ETIMER_ARR register  ********************/
#define  ETIMER_ARR_ARR            ((uint16_t)0xFFFF)     /*!< actual auto-reload Value */

/*******************  Bit definition for ETIMER_RCR register  ********************/
#define  ETIMER_RCR_REP            ((uint8_t)0xFF)        /*!< Repetition Counter Value */

/*******************  Bit definition for ETIMER_CCR1 register  *******************/
#define  ETIMER_CCR1_CCR1          ((uint16_t)0xFFFF)     /*!< Capture/Compare 1 Value */

/*******************  Bit definition for ETIMER_CCR2 register  *******************/
#define  ETIMER_CCR2_CCR2          ((uint16_t)0xFFFF)     /*!< Capture/Compare 2 Value */

/*******************  Bit definition for ETIMER_CCR3 register  *******************/
#define  ETIMER_CCR3_CCR3          ((uint16_t)0xFFFF)     /*!< Capture/Compare 3 Value */

/*******************  Bit definition for ETIMER_CCR4 register  *******************/
#define  ETIMER_CCR4_CCR4          ((uint16_t)0xFFFF)     /*!< Capture/Compare 4 Value */

/*******************  Bit definition for ETIMER_BDTR register  *******************/
#define  ETIMER_BDTR_DTG           ((uint16_t)0x00FF)     /*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define  ETIMER_BDTR_DTG_0         ((uint16_t)0x0001)     /*!< Bit 0 */
#define  ETIMER_BDTR_DTG_1         ((uint16_t)0x0002)     /*!< Bit 1 */
#define  ETIMER_BDTR_DTG_2         ((uint16_t)0x0004)     /*!< Bit 2 */
#define  ETIMER_BDTR_DTG_3         ((uint16_t)0x0008)     /*!< Bit 3 */
#define  ETIMER_BDTR_DTG_4         ((uint16_t)0x0010)     /*!< Bit 4 */
#define  ETIMER_BDTR_DTG_5         ((uint16_t)0x0020)     /*!< Bit 5 */
#define  ETIMER_BDTR_DTG_6         ((uint16_t)0x0040)     /*!< Bit 6 */
#define  ETIMER_BDTR_DTG_7         ((uint16_t)0x0080)     /*!< Bit 7 */

#define  ETIMER_BDTR_LOCK          ((uint16_t)0x0300)     /*!< LOCK[1:0] bits (Lock Configuration) */
#define  ETIMER_BDTR_LOCK_0        ((uint16_t)0x0100)     /*!< Bit 0 */
#define  ETIMER_BDTR_LOCK_1        ((uint16_t)0x0200)     /*!< Bit 1 */

#define  ETIMER_BDTR_OSSI          ((uint16_t)0x0400)     /*!< Off-State Selection for Idle mode */
#define  ETIMER_BDTR_OSSR          ((uint16_t)0x0800)     /*!< Off-State Selection for Run mode */
#define  ETIMER_BDTR_BKE           ((uint16_t)0x1000)     /*!< Break enable */
#define  ETIMER_BDTR_BKP           ((uint16_t)0x2000)     /*!< Break Polarity */
#define  ETIMER_BDTR_AOE           ((uint16_t)0x4000)     /*!< Automatic Output enable */
#define  ETIMER_BDTR_MOE           ((uint16_t)0x8000)     /*!< Main Output enable */

                                                                                                                                                                                                                       
/** @defgroup ETIMER_Output_Compare_and_PWM_modes 
  * @{
  */
#define ETIMER_OCMode_Timing       ((uint16_t)0x0000)        /*!< 冻结*/
#define ETIMER_OCMode_Active       ((uint16_t)(0x01 << 4))   /*!< 匹配时设置通道为有效电平 */
#define ETIMER_OCMode_Inactive     ((uint16_t)(0x02 << 4))   /*!< 匹配时设置通道为无效电平 */
#define ETIMER_OCMode_Toggle       ((uint16_t)(0x03 << 4))   /*!< 翻转 */
#define ETIMER_OCMode_PWM1         ((uint16_t)(0x06 << 4))   /*!< PWM1 */
#define ETIMER_OCMode_PWM2         ((uint16_t)(0x07 << 4))   /*!< PWM2 */

#define IS_ETIMER_OC_MODE(MODE)    (((MODE) == ETIMER_OCMode_Timing) || \
                              	    ((MODE) == ETIMER_OCMode_Active) || \
                              	    ((MODE) == ETIMER_OCMode_Inactive) || \
                              	    ((MODE) == ETIMER_OCMode_Toggle)|| \
                              	    ((MODE) == ETIMER_OCMode_PWM1) || \
                              	    ((MODE) == ETIMER_OCMode_PWM2))
                              	
#define IS_ETIMER_OCM(MODE) 	 (((MODE) == ETIMER_OCMode_Timing) || \
                          	      ((MODE) == ETIMER_OCMode_Active) || \
                          	      ((MODE) == ETIMER_OCMode_Inactive) || \
                          	      ((MODE) == ETIMER_OCMode_Toggle)|| \
                          	      ((MODE) == ETIMER_OCMode_PWM1) || \
                          	      ((MODE) == ETIMER_OCMode_PWM2) || \
                          	      ((MODE) == ETIMER_ForcedAction_Active) || \
                          	      ((MODE) == ETIMER_ForcedAction_InActive))

/** @defgroup ETIMER_Output_Compare_state 
  * @{
  */
#define ETIMER_OutputState_Disable        (0)
#define ETIMER_OutputState_Enable         (BIT0)
#define IS_ETIMER_OUTPUT_STATE(STATE)     (((STATE) == ETIMER_OutputState_Disable) || \
                                           ((STATE) == ETIMER_OutputState_Enable))

/** @defgroup ETIMER_Output_Compare_N_state 
  * @{
  */
#define ETIMER_OutputNState_Disable        (0)
#define ETIMER_OutputNState_Enable         (BIT2)
#define IS_ETIMER_OUTPUTN_STATE(STATE)     (((STATE) == ETIMER_OutputNState_Disable) || \
                                            ((STATE) == ETIMER_OutputNState_Enable))

/** @defgroup ETIMER_Output_Compare_Polarity 
  * @{
  */
#define ETIMER_OCPolarity_High             (0)
#define ETIMER_OCPolarity_Low              (BIT1)
#define IS_ETIMER_OC_POLARITY(POLARITY)    (((POLARITY) == ETIMER_OCPolarity_High) || \
                                            ((POLARITY) == ETIMER_OCPolarity_Low))

/** @defgroup ETIMER_Output_Compare_N_Polarity 
  * @{
  */
#define ETIMER_OCNPolarity_High            (0)
#define ETIMER_OCNPolarity_Low             (BIT3)
#define IS_ETIMER_OCN_POLARITY(POLARITY)   (((POLARITY) == ETIMER_OCNPolarity_High) || \
                                            ((POLARITY) == ETIMER_OCNPolarity_Low))                                            

/** @defgroup ETIMER_Output_Compare_Idle_State 
  * @{
  */
#define ETIMER_OCIdleState_Set          (BIT8)
#define ETIMER_OCIdleState_Reset        (0)
#define IS_ETIMER_OCIDLE_STATE(STATE)   (((STATE) == ETIMER_OCIdleState_Set) || \
                                         ((STATE) == ETIMER_OCIdleState_Reset))

/** @defgroup ETIMER_Output_Compare_N_Idle_State 
  * @{
  */
#define ETIMER_OCNIdleState_Set           (BIT9)
#define ETIMER_OCNIdleState_Reset         (0)
#define IS_ETIMER_OCNIDLE_STATE(STATE)    (((STATE) == ETIMER_OCNIdleState_Set) || \
                                           ((STATE) == ETIMER_OCNIdleState_Reset))

/** @defgroup ETIMER_One_Pulse_Mode 
  * @{
  */
#define ETIMER_OPMode_Single        ((uint16_t)0x0008)
#define ETIMER_OPMode_Repetitive    ((uint16_t)0x0000)
#define IS_ETIMER_OPM_MODE(MODE) 	(((MODE) == ETIMER_OPMode_Single) || \
                               	     ((MODE) == ETIMER_OPMode_Repetitive))

/** @defgroup ETIMER_Channel 
  * @{
  */
#define ETIMER_Channel_1            ((uint16_t)0x0001)   /*!<  ETIMER通道1 */ 
#define ETIMER_Channel_2            ((uint16_t)0x0002)   /*!<  ETIMER通道2 */
#define ETIMER_Channel_3            ((uint16_t)0x0003)   /*!<  ETIMER通道3 */
#define ETIMER_Channel_4            ((uint16_t)0x0004)   /*!<  ETIMER通道4 */

#define IS_ETIMER_CHANNEL(CHANNEL)  (((CHANNEL) == ETIMER_Channel_1) || \
                                     ((CHANNEL) == ETIMER_Channel_2) || \
                                     ((CHANNEL) == ETIMER_Channel_3) || \
                                     ((CHANNEL) == ETIMER_Channel_4))
                                    	 
#define IS_ETIMER_PWMI_CHANNEL(CHANNEL)    (((CHANNEL) == ETIMER_Channel_1) || \
                                            ((CHANNEL) == ETIMER_Channel_2))
                                         
#define IS_ETIMER_COMPLEMENTARY_CHANNEL(CHANNEL)   (((CHANNEL) == ETIMER_Channel_1) || \
                                                    ((CHANNEL) == ETIMER_Channel_2) || \
                                                    ((CHANNEL) == ETIMER_Channel_3))

/** @defgroup ETIMER_Clock_Division_CKD 
  * @{
  */
#define ETIMER_CKD_Mask            ((uint16_t)(0x03 << 8))
#define ETIMER_CKD_DIV1            ((uint16_t)(0x00 << 8))     /*!<  tDTS = tCK_INT */
#define ETIMER_CKD_DIV2            ((uint16_t)(0x01 << 8))     /*!<  tDTS = 2tCK_INT */
#define ETIMER_CKD_DIV4            ((uint16_t)(0x02 << 8))     /*!<  tDTS = 4tCK_INT */

#define IS_ETIMER_CKD_DIV(DIV)     (((DIV) == ETIMER_CKD_DIV1) || \
                                    ((DIV) == ETIMER_CKD_DIV2) || \
                                    ((DIV) == ETIMER_CKD_DIV4))


#define ETIMER_CR1_DIR_Mask     (BIT4) 
#define ETIMER_CR1_CMS_Mask     ((uint16_t)(0x03 << 5))
   

/** @defgroup ETIMER_Counter_Mode 计数模式
  * @{
  */
#define ETIMER_CounterMode_Up                 (0)      				   /*!< 计数器向上计数 */
#define ETIMER_CounterMode_Down               (BIT4)                    /*!< 计数器向下计数 */
#define ETIMER_CounterMode_CenterAligned1     ((uint16_t)(0x01 << 5))   /*!< 中央对齐模式1 */
#define ETIMER_CounterMode_CenterAligned2     ((uint16_t)(0x02 << 5))   /*!< 中央对齐模式2 */
#define ETIMER_CounterMode_CenterAligned3     ((uint16_t)(0x03 << 5))   /*!< 中央对齐模式3 */

#define IS_ETIMER_COUNTER_MODE(MODE)          (((MODE) == ETIMER_CounterMode_Up) ||  \
                                               ((MODE) == ETIMER_CounterMode_Down) || \
                                               ((MODE) == ETIMER_CounterMode_CenterAligned1) || \
                                               ((MODE) == ETIMER_CounterMode_CenterAligned2) || \
                                               ((MODE) == ETIMER_CounterMode_CenterAligned3))

/** @defgroup ETIMER_Capture_Compare_state 
  * @{
  */
#define ETIMER_CCx_Enable     ((uint16_t)0x0001)
#define ETIMER_CCx_Disable    ((uint16_t)0x0000)
#define IS_ETIMER_CCX(CCX)    (((CCX) == ETIMER_CCx_Enable) || \
                               ((CCX) == ETIMER_CCx_Disable))

/** @defgroup ETIMER_Capture_Compare_N_state 
  * @{
  */
#define ETIMER_CCxN_Enable      ((uint16_t)0x0004)
#define ETIMER_CCxN_Disable     ((uint16_t)0x0000)
#define IS_ETIMER_CCXN(CCXN)    (((CCXN) == ETIMER_CCxN_Enable) || \
                                 ((CCXN) == ETIMER_CCxN_Disable))

/** @defgroup Break_Input_enable_disable 
  * @{
  */
#define ETIMER_Break_Enable             ((uint16_t)0x1000)
#define ETIMER_Break_Disable            ((uint16_t)0x0000)
#define IS_ETIMER_BREAK_STATE(STATE)    (((STATE) == ETIMER_Break_Enable) || \
                                         ((STATE) == ETIMER_Break_Disable))

/** @defgroup Break_Polarity 
  * @{
  */
#define ETIMER_BreakPolarity_Low              ((uint16_t)0x0000)
#define ETIMER_BreakPolarity_High             ((uint16_t)0x2000)
#define IS_ETIMER_BREAK_POLARITY(POLARITY)    (((POLARITY) == ETIMER_BreakPolarity_Low) || \
                                               ((POLARITY) == ETIMER_BreakPolarity_High))

/** @defgroup ETIMER_AOE_Bit_Set_Reset 
  * @{
  */
#define ETIMER_AutomaticOutput_Enable            ((uint16_t)0x4000)
#define ETIMER_AutomaticOutput_Disable           ((uint16_t)0x0000)
#define IS_ETIMER_AUTOMATIC_OUTPUT_STATE(STATE)  (((STATE) == ETIMER_AutomaticOutput_Enable) || \
                                                  ((STATE) == ETIMER_AutomaticOutput_Disable))

/** @defgroup Lock_level 
  * @{
  */
#define ETIMER_LOCKLevel_OFF            ((uint16_t)0x0000)
#define ETIMER_LOCKLevel_1              ((uint16_t)0x0100)
#define ETIMER_LOCKLevel_2              ((uint16_t)0x0200)
#define ETIMER_LOCKLevel_3              ((uint16_t)0x0300)
#define IS_ETIMER_LOCK_LEVEL(LEVEL)     (((LEVEL) == ETIMER_LOCKLevel_OFF) || \
                                         ((LEVEL) == ETIMER_LOCKLevel_1) || \
                                         ((LEVEL) == ETIMER_LOCKLevel_2) || \
                                         ((LEVEL) == ETIMER_LOCKLevel_3))

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */
#define ETIMER_OSSIState_Enable         ((uint16_t)0x0400)
#define ETIMER_OSSIState_Disable        ((uint16_t)0x0000)
#define IS_ETIMER_OSSI_STATE(STATE)     (((STATE) == ETIMER_OSSIState_Enable) || \
                                         ((STATE) == ETIMER_OSSIState_Disable))

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */
#define ETIMER_OSSRState_Enable         ((uint16_t)0x0800)
#define ETIMER_OSSRState_Disable        ((uint16_t)0x0000)
#define IS_ETIMER_OSSR_STATE(STATE)     (((STATE) == ETIMER_OSSRState_Enable) || \
                                         ((STATE) == ETIMER_OSSRState_Disable))

/** @defgroup ETIMER_Input_Capture_Polarity 
  * @{
  */
#define  ETIMER_ICPolarity_Rising         		((uint16_t)0x0000)  /*<! 捕获发生在IC的上升沿 */ 
#define  ETIMER_ICPolarity_Falling        		((uint16_t)0x0002)  /*<! 捕获发生在IC的下降沿 */ 
#define  ETIMER_ICPolarity_BothEdge       		((uint16_t)0x000A)
#define  IS_ETIMER_IC_POLARITY(POLARITY)   		(((POLARITY) == ETIMER_ICPolarity_Rising) || \
                                       		     ((POLARITY) == ETIMER_ICPolarity_Falling))
                                       		 
#define IS_ETIMER_IC_POLARITY_LITE(POLARITY)   (((POLARITY) == ETIMER_ICPolarity_Rising) || \
                                                ((POLARITY) == ETIMER_ICPolarity_Falling) || \
                                                ((POLARITY) == ETIMER_ICPolarity_BothEdge))                                      

/** @defgroup ETIMER_Input_Capture_Selection 
  * @{
  */
#define ETIMER_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< ETIMER Input 1, 2, 3 or 4 is selected to be connected to TI1 */                                                                 
#define ETIMER_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< ETIMER Input 1, 2, 3 or 4 is selected to be connected to TI2 */                                                              
#define ETIMER_ICSelection_TRC                ((uint16_t)0x0003) /*!< ETIMER Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_ETIMER_IC_SELECTION(SELECTION)     (((SELECTION) == ETIMER_ICSelection_DirectTI) || \
                                               ((SELECTION) == ETIMER_ICSelection_IndirectTI) || \
                                               ((SELECTION) == ETIMER_ICSelection_TRC))

/** @defgroup ETIMER_Input_Capture_Prescaler 
  * @{
  */
#define ETIMER_ICPSC_DIV1                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define ETIMER_ICPSC_DIV2                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define ETIMER_ICPSC_DIV4                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define ETIMER_ICPSC_DIV8                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_ETIMER_IC_PRESCALER(PRESCALER)     (((PRESCALER) == ETIMER_ICPSC_DIV1) || \
                                               ((PRESCALER) == ETIMER_ICPSC_DIV2) || \
                                               ((PRESCALER) == ETIMER_ICPSC_DIV4) || \
                                               ((PRESCALER) == ETIMER_ICPSC_DIV8))

/** @defgroup ETIMER_interrupt_sources 
  * @{
  */
#define ETIMER_IT_Update         ((uint16_t)0x0001)   /*!< 允许更新中断 */ 
#define ETIMER_IT_CC1            ((uint16_t)0x0002)   /*!< 允许捕获/比较 1 中断 */ 
#define ETIMER_IT_CC2            ((uint16_t)0x0004)   /*!< 允许捕获/比较 2 中断 */ 
#define ETIMER_IT_CC3            ((uint16_t)0x0008)   /*!< 允许捕获/比较 3 中断 */ 
#define ETIMER_IT_CC4            ((uint16_t)0x0010)   /*!< 允许捕获/比较 4 中断 */ 
#define ETIMER_IT_COM            ((uint16_t)0x0020)   /*!< 允许 COM 中断 */ 
#define ETIMER_IT_Trigger        ((uint16_t)0x0040)   /*!< 触发中断使能 */ 
#define ETIMER_IT_Break          ((uint16_t)0x0080)   /*!< 允许刹车中断 */ 
#define IS_ETIMER_IT(IT)         ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_ETIMER_GET_IT(IT)     (((IT) == ETIMER_IT_Update) || \
                                  ((IT) == ETIMER_IT_CC1) || \
                                  ((IT) == ETIMER_IT_CC2) || \
                                  ((IT) == ETIMER_IT_CC3) || \
                                  ((IT) == ETIMER_IT_CC4) || \
                                  ((IT) == ETIMER_IT_COM) || \
                                  ((IT) == ETIMER_IT_Trigger) || \
                                  ((IT) == ETIMER_IT_Break))

/** @defgroup ETIMER_External_Trigger_Prescaler 
  * @{
  */
#define ETIMER_ExtTRGPSC_OFF                  ((uint16_t)0x0000)  
#define ETIMER_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define ETIMER_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define ETIMER_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)
#define IS_ETIMER_EXT_PRESCALER(PRESCALER)    (((PRESCALER) == ETIMER_ExtTRGPSC_OFF) || \
                                               ((PRESCALER) == ETIMER_ExtTRGPSC_DIV2) || \
                                               ((PRESCALER) == ETIMER_ExtTRGPSC_DIV4) || \
                                               ((PRESCALER) == ETIMER_ExtTRGPSC_DIV8))

/** @defgroup ETIMER_Internal_Trigger_Selection/触发选择
  * @{
  */
#define ETIMER_TS_ITR0                       ((uint16_t)0x0000)     /*!< 内部触发 */ 
#define ETIMER_TS_ITR1                       ((uint16_t)0x0010)     /*!< 内部触发1 */ 
#define ETIMER_TS_ITR2                       ((uint16_t)0x0020)     /*!< 内部触发2 */ 
#define ETIMER_TS_ITR3                       ((uint16_t)0x0030)     /*!< 内部触发3 */ 
#define ETIMER_TS_TI1F_ED                    ((uint16_t)0x0040)     /*!< TI1的边沿检测器 */ 
#define ETIMER_TS_TI1FP1                     ((uint16_t)0x0050)     /*!< 滤波后的定时器输入1 */ 
#define ETIMER_TS_TI2FP2                     ((uint16_t)0x0060)     /*!< 滤波后的定时器输入2 */ 
#define ETIMER_TS_ETRF                       ((uint16_t)0x0070)     /*!< 外部触发输入 */ 
#define IS_ETIMER_TRIGGER_SELECTION(SELECTION)  (((SELECTION) == ETIMER_TS_ITR0) || \
                                              	 ((SELECTION) == ETIMER_TS_ITR1) || \
                                              	 ((SELECTION) == ETIMER_TS_ITR2) || \
                                              	 ((SELECTION) == ETIMER_TS_ITR3) || \
                                              	 ((SELECTION) == ETIMER_TS_TI1F_ED) || \
                                              	 ((SELECTION) == ETIMER_TS_TI1FP1) || \
                                              	 ((SELECTION) == ETIMER_TS_TI2FP2) || \
                                              	 ((SELECTION) == ETIMER_TS_ETRF))
                                              	 
#define IS_ETIMER_INTERNAL_TRIGGER_SELECTION(SELECTION)  (((SELECTION) == ETIMER_TS_ITR0) || \
                                                      	  ((SELECTION) == ETIMER_TS_ITR1) || \
                                                      	  ((SELECTION) == ETIMER_TS_ITR2) || \
                                                      	  ((SELECTION) == ETIMER_TS_ITR3))

/** @defgroup ETIMER_TIx_External_Clock_Source 
  * @{
  */
#define ETIMER_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)  
#define ETIMER_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define ETIMER_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define IS_ETIMER_TIXCLK_SOURCE(SOURCE) 	  (((SOURCE) == ETIMER_TIxExternalCLK1Source_TI1ED) || \
                                      	       ((SOURCE) == ETIMER_TIxExternalCLK1Source_TI1) || \
                                               ((SOURCE) == ETIMER_TIxExternalCLK1Source_TI2))

/** @defgroup ETIMER_External_Trigger_Polarity 
  * @{
  */ 
#define ETIMER_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define ETIMER_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_ETIMER_EXT_POLARITY(POLARITY)      (((POLARITY) == ETIMER_ExtTRGPolarity_Inverted) || \
                                               ((POLARITY) == ETIMER_ExtTRGPolarity_NonInverted))

/** @defgroup ETIMER_Prescaler_Reload_Mode 
  * @{
  */
#define ETIMER_PSCReloadMode_Update           (0)
#define ETIMER_PSCReloadMode_Immediate        (BIT0)   /*<! PSC and Reload立即更新 */  
#define IS_ETIMER_PRESCALER_RELOAD(RELOAD)    (((RELOAD) == ETIMER_PSCReloadMode_Update) || \
                                               ((RELOAD) == ETIMER_PSCReloadMode_Immediate))

/** @defgroup ETIMER_Forced_Action 
  * @{
  */
#define ETIMER_ForcedAction_Active         ((uint16_t)0x0050)
#define ETIMER_ForcedAction_InActive       ((uint16_t)0x0040)
#define IS_ETIMER_FORCED_ACTION(ACTION)    (((ACTION) == ETIMER_ForcedAction_Active) || \
                                            ((ACTION) == ETIMER_ForcedAction_InActive))

/** @defgroup ETIMER_Encoder_Mode 
  * @{
  */
#define ETIMER_EncoderMode_TI1            ((uint16_t)0x0001)
#define ETIMER_EncoderMode_TI2            ((uint16_t)0x0002)
#define ETIMER_EncoderMode_TI12           ((uint16_t)0x0003)
#define IS_ETIMER_ENCODER_MODE(MODE)      (((MODE) == ETIMER_EncoderMode_TI1) || \
                                           ((MODE) == ETIMER_EncoderMode_TI2) || \
                                           ((MODE) == ETIMER_EncoderMode_TI12))

/** @defgroup ETIMER_Event_Source 
  * @{
  */
#define ETIMER_EventSource_Update         ((uint16_t)0x0001)  /*!< 产生更新事件 */
#define ETIMER_EventSource_CC1            ((uint16_t)0x0002)  /*!< 产生捕获/比较 1 事件 */
#define ETIMER_EventSource_CC2            ((uint16_t)0x0004)  /*!< 产生捕获/比较 2 事件 */
#define ETIMER_EventSource_CC3            ((uint16_t)0x0008)  /*!< 产生捕获/比较 3 事件 */
#define ETIMER_EventSource_CC4            ((uint16_t)0x0010)  /*!< 产生捕获/比较 4 事件 */
#define ETIMER_EventSource_COM            ((uint16_t)0x0020)  /*!< 捕获/比较事件，产生控制更新 */
#define ETIMER_EventSource_Trigger        ((uint16_t)0x0040)  /*!< 产生触发事件 */
#define ETIMER_EventSource_Break          ((uint16_t)0x0080)  /*!< 产生刹车事件 */
#define IS_ETIMER_EVENT_SOURCE(SOURCE)    ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/** @defgroup ETIMER_Update_Source 
  * @{
  */
#define ETIMER_UpdateSource_Global        ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define ETIMER_UpdateSource_Regular       ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_ETIMER_UPDATE_SOURCE(SOURCE)   (((SOURCE) == ETIMER_UpdateSource_Global) || \
                                           ((SOURCE) == ETIMER_UpdateSource_Regular))

/** @defgroup ETIMER_Output_Compare_Preload_State 
  * @{
  */
#define ETIMER_OCPreload_Enable            ((uint16_t)0x0008)
#define ETIMER_OCPreload_Disable           ((uint16_t)0x0000)
#define IS_ETIMER_OCPRELOAD_STATE(STATE)   (((STATE) == ETIMER_OCPreload_Enable) || \
                                            ((STATE) == ETIMER_OCPreload_Disable))

/** @defgroup ETIMER_Output_Compare_Fast_State 
  * @{
  */
#define ETIMER_OCFast_Enable               ((uint16_t)0x0004)
#define ETIMER_OCFast_Disable              ((uint16_t)0x0000)
#define IS_ETIMER_OCFAST_STATE(STATE)      (((STATE) == ETIMER_OCFast_Enable) || \
                                            ((STATE) == ETIMER_OCFast_Disable))
                                     
/** @defgroup ETIMER_Output_Compare_Clear_State 
  * @{
  */
#define ETIMER_OCClear_Enable              ((uint16_t)0x0080)
#define ETIMER_OCClear_Disable             ((uint16_t)0x0000)
#define IS_ETIMER_OCCLEAR_STATE(STATE)     (((STATE) == ETIMER_OCClear_Enable) || \
                                            ((STATE) == ETIMER_OCClear_Disable))

/** @defgroup ETIMER_Trigger_Output_Source 
  * @{
  */
#define ETIMER_TRGOSource_Reset          ((uint16_t)0x0000)
#define ETIMER_TRGOSource_Enable         ((uint16_t)0x0010)
#define ETIMER_TRGOSource_Update         ((uint16_t)0x0020)
#define ETIMER_TRGOSource_OC1            ((uint16_t)0x0030)
#define ETIMER_TRGOSource_OC1Ref         ((uint16_t)0x0040)
#define ETIMER_TRGOSource_OC2Ref         ((uint16_t)0x0050)
#define ETIMER_TRGOSource_OC3Ref         ((uint16_t)0x0060)
#define ETIMER_TRGOSource_OC4Ref         ((uint16_t)0x0070)
#define IS_ETIMER_TRGO_SOURCE(SOURCE)    (((SOURCE) == ETIMER_TRGOSource_Reset) || \
                                         ((SOURCE) == ETIMER_TRGOSource_Enable) || \
                                         ((SOURCE) == ETIMER_TRGOSource_Update) || \
                                         ((SOURCE) == ETIMER_TRGOSource_OC1) || \
                                         ((SOURCE) == ETIMER_TRGOSource_OC1Ref) || \
                                         ((SOURCE) == ETIMER_TRGOSource_OC2Ref) || \
                                         ((SOURCE) == ETIMER_TRGOSource_OC3Ref) || \
                                         ((SOURCE) == ETIMER_TRGOSource_OC4Ref))

/** @defgroup ETIMER_Slave_Mode 
  * @{
  */
#define ETIMER_SlaveMode_Reset           ((uint16_t)0x0004)
#define ETIMER_SlaveMode_Gated           ((uint16_t)0x0005)
#define ETIMER_SlaveMode_Trigger         ((uint16_t)0x0006)
#define ETIMER_SlaveMode_External1       ((uint16_t)0x0007)
#define IS_ETIMER_SLAVE_MODE(MODE)       (((MODE) == ETIMER_SlaveMode_Reset) || \
                                          ((MODE) == ETIMER_SlaveMode_Gated) || \
                                          ((MODE) == ETIMER_SlaveMode_Trigger) || \
                                          ((MODE) == ETIMER_SlaveMode_External1))

/** @defgroup ETIMER_Master_Slave_Mode 
  * @{
  */
#define ETIMER_MasterSlaveMode_Enable      ((uint16_t)0x0080)
#define ETIMER_MasterSlaveMode_Disable     ((uint16_t)0x0000)
#define IS_ETIMER_MSM_STATE(STATE)         (((STATE) == ETIMER_MasterSlaveMode_Enable) || \
                                            ((STATE) == ETIMER_MasterSlaveMode_Disable))

/** @defgroup ETIMER_Flags 
  * @{
  */
#define ETIMER_FLAG_Update         ((uint16_t)0x0001)    /*!< 更新中断标志 */
#define ETIMER_FLAG_CC1            ((uint16_t)0x0002)    /*!< 捕获/比较 1 中断标记 */
#define ETIMER_FLAG_CC2            ((uint16_t)0x0004)    /*!< 捕获/比较 2 中断标记 */
#define ETIMER_FLAG_CC3            ((uint16_t)0x0008)    /*!< 捕获/比较 3 中断标记 */
#define ETIMER_FLAG_CC4            ((uint16_t)0x0010)    /*!< 捕获/比较 4 中断标记 */
#define ETIMER_FLAG_COM            ((uint16_t)0x0020)    /*!< COM 中断标记 */
#define ETIMER_FLAG_Trigger        ((uint16_t)0x0040)    /*!< 触发器中断标记 */
#define ETIMER_FLAG_Break          ((uint16_t)0x0080)    /*!< 刹车中断标记 */
#define ETIMER_FLAG_CC1OF          ((uint16_t)0x0200)    /*!< 捕获/比较 1 重复捕获标记 */
#define ETIMER_FLAG_CC2OF          ((uint16_t)0x0400)    /*!< 捕获/比较 2 重复捕获标记 */
#define ETIMER_FLAG_CC3OF          ((uint16_t)0x0800)    /*!< 捕获/比较 3 重复捕获标记 */
#define ETIMER_FLAG_CC4OF          ((uint16_t)0x1000)    /*!< 捕获/比较 4 重复捕获标记 */
#define IS_ETIMER_GET_FLAG(FLAG)   (((FLAG) == ETIMER_FLAG_Update) || \
                                    ((FLAG) == ETIMER_FLAG_CC1) || \
                                    ((FLAG) == ETIMER_FLAG_CC2) || \
                                    ((FLAG) == ETIMER_FLAG_CC3) || \
                                    ((FLAG) == ETIMER_FLAG_CC4) || \
                                    ((FLAG) == ETIMER_FLAG_COM) || \
                                    ((FLAG) == ETIMER_FLAG_Trigger) || \
                                    ((FLAG) == ETIMER_FLAG_Break) || \
                                    ((FLAG) == ETIMER_FLAG_CC1OF) || \
                                    ((FLAG) == ETIMER_FLAG_CC2OF) || \
                                    ((FLAG) == ETIMER_FLAG_CC3OF) || \
                                    ((FLAG) == ETIMER_FLAG_CC4OF))
                                                             
#define IS_ETIMER_CLEAR_FLAG(ETIMER_FLAG)    ((((ETIMER_FLAG) & (uint16_t)0xE100) == 0x0000) && ((ETIMER_FLAG) != 0x0000))


/** @defgroup ETIMER_Input_Capture_Filer_Value 
  * @{
  */
#define IS_ETIMER_IC_FILTER(ICFILTER)     ((ICFILTER) <= 0xF) 


/** @defgroup ETIMER_External_Trigger_Filter 
  * @{
  */
#define IS_ETIMER_EXT_FILTER(EXTFILTER)   ((EXTFILTER) <= 0xF)


/* Exported functions --------------------------------------------------------*/
void ETIMER_DeInit(ETIMER_TypeDef* ETIMERx);
void ETIMER_TimeBaseInit(ETIMER_TypeDef* ETIMERx, ETIMER_TimeBaseInitTypeDef* ETIMER_TimeBaseInitStruct);
void ETIMER_OC1Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct);
void ETIMER_OC2Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct);
void ETIMER_OC3Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct);
void ETIMER_OC4Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct);
void ETIMER_ICInit(ETIMER_TypeDef* ETIMERx, ETIMER_ICInitTypeDef* ETIMER_ICInitStruct);
void ETIMER_PWMIConfig(ETIMER_TypeDef* ETIMERx, ETIMER_ICInitTypeDef* ETIMER_ICInitStruct);
void ETIMER_BDTRConfig(ETIMER_TypeDef* ETIMERx, ETIMER_BDTRInitTypeDef *ETIMER_BDTRInitStruct);
void ETIMER_TimeBaseStructInit(ETIMER_TimeBaseInitTypeDef* ETIMER_TimeBaseInitStruct);
void ETIMER_OCStructInit(ETIMER_OCInitTypeDef* ETIMER_OCInitStruct);	
void ETIMER_ICStructInit(ETIMER_ICInitTypeDef* ETIMER_ICInitStruct);
void ETIMER_BDTRStructInit(ETIMER_BDTRInitTypeDef* ETIMER_BDTRInitStruct);
void ETIMER_Cmd(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_CtrlPWMOutputs(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_ITConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT, FunctionalState NewState);
void ETIMER_GenerateEvent(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_EventSource);
void ETIMER_InternalClockConfig(ETIMER_TypeDef* ETIMERx);
void ETIMER_ITRxExternalClockConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_InputTriggerSource);
void ETIMER_TIxExternalClockConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_TIxExternalCLKSource, uint16_t ETIMER_ICPolarity, uint16_t ICFilter);
void ETIMER_ETRClockMode1Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, uint16_t ETIMER_ExtTRGPolarity, uint16_t ExtTRGFilter);
void ETIMER_ETRClockMode2Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, uint16_t ETIMER_ExtTRGPolarity, uint16_t ExtTRGFilter);
void ETIMER_ETRConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, uint16_t ETIMER_ExtTRGPolarity, uint16_t ExtTRGFilter);
void ETIMER_PrescalerConfig(ETIMER_TypeDef* ETIMERx, uint16_t Prescaler, uint16_t ETIMER_PSCReloadMode);
void ETIMER_CounterModeConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_CounterMode);
void ETIMER_SelectInputTrigger(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_InputTriggerSource);
void ETIMER_EncoderInterfaceConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_EncoderMode, uint16_t ETIMER_IC1Polarity, uint16_t ETIMER_IC2Polarity);
void ETIMER_ForcedOC1Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction);
void ETIMER_ForcedOC2Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction);
void ETIMER_ForcedOC3Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction);
void ETIMER_ForcedOC4Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction);
void ETIMER_ARRPreloadConfig(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_SelectCOM(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_CCPreloadControl(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_OC1PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload);
void ETIMER_OC2PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload);
void ETIMER_OC3PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload);
void ETIMER_OC4PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload);
void ETIMER_OC1FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast);
void ETIMER_OC2FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast);
void ETIMER_OC3FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast);
void ETIMER_OC4FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast);
void ETIMER_ClearOC1Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear);
void ETIMER_ClearOC2Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear);
void ETIMER_ClearOC3Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear);
void ETIMER_ClearOC4Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear);
void ETIMER_OC1PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity);
void ETIMER_OC1NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity);
void ETIMER_OC2PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity);
void ETIMER_OC2NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity);
void ETIMER_OC3PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity);
void ETIMER_OC3NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity);
void ETIMER_OC4PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity);
void ETIMER_CCxCmd(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_CCx);
void ETIMER_CCxNCmd(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_CCxN);
void ETIMER_SelectOCxM(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_OCMode);
void ETIMER_UpdateDisableConfig(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_UpdateRequestConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_UpdateSource);
void ETIMER_SelectHallSensor(ETIMER_TypeDef* ETIMERx, FunctionalState NewState);
void ETIMER_SelectOnePulseMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OPMode);
void ETIMER_SelectOutputTrigger(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_TRGOSource);
void ETIMER_SelectSlaveMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_SlaveMode);
void ETIMER_SelectMasterSlaveMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_MasterSlaveMode);
void ETIMER_SetCounter(ETIMER_TypeDef* ETIMERx, uint16_t Counter);
void ETIMER_SetAutoreload(ETIMER_TypeDef* ETIMERx, uint16_t Autoreload);
void ETIMER_SetCompare1A(ETIMER_TypeDef* ETIMERx, uint16_t Compare1A);
void ETIMER_SetCompare2A(ETIMER_TypeDef* ETIMERx, uint16_t Compare2A);
void ETIMER_SetCompare3A(ETIMER_TypeDef* ETIMERx, uint16_t Compare3A);
void ETIMER_SetCompare4A(ETIMER_TypeDef* ETIMERx, uint16_t Compare4A);
void ETIMER_SetCompare1B(ETIMER_TypeDef* ETIMERx, uint16_t Compare1B);
void ETIMER_SetCompare2B(ETIMER_TypeDef* ETIMERx, uint16_t Compare2B);
void ETIMER_SetCompare3B(ETIMER_TypeDef* ETIMERx, uint16_t Compare3B);
void ETIMER_SetCompare4B(ETIMER_TypeDef* ETIMERx, uint16_t Compare4B);
void ETIMER_SetIC1Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC);
void ETIMER_SetIC2Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC);
void ETIMER_SetIC3Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC);
void ETIMER_SetIC4Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC);
void ETIMER_SetClockDivision(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_CKD);
uint16_t ETIMER_GetCapture1A(ETIMER_TypeDef* ETIMERx);
uint16_t ETIMER_GetCapture2A(ETIMER_TypeDef* ETIMERx);
uint16_t ETIMER_GetCapture3A(ETIMER_TypeDef* ETIMERx);
uint16_t ETIMER_GetCapture4A(ETIMER_TypeDef* ETIMERx);
uint16_t ETIMER_GetCounter(ETIMER_TypeDef* ETIMERx);
uint16_t ETIMER_GetPrescaler(ETIMER_TypeDef* ETIMERx);
FlagStatus ETIMER_GetFlagStatus(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_FLAG);
void ETIMER_ClearFlag(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_FLAG);
ITStatus ETIMER_GetITStatus(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT);
void ETIMER_ClearITPendingBit(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT);
void ETIMER_TI1_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter);
void ETIMER_TI2_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter);
void ETIMER_TI3_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter);
void ETIMER_TI4_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_ETIMER_H__ */

