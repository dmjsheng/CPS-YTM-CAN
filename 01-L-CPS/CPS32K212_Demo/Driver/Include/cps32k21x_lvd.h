/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_LVD_H__   
#define __CPS32K21X_LVD_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"
     

/**
  * @} LVD_InitTypeDef
  */
typedef struct
{
    uint32_t Th_Volage_sel;      /*!< LVD阈值电压选择 */   
                                  
    uint32_t LVD_Act_sel;        /*!< LVD复位、中断方式选择 */

    uint32_t filterClk_sel;      /*!< LVD滤波时钟选择 */

    uint32_t filter_EnStatus;    /*!< LVD滤波使能状态 */

    uint32_t LVD_trigger_sel;    /*!< LVD触发方式选择 */
                                  
}LVD_InitTypeDef;
	 
	 
/* Exported types ------------------------------------------------------------*/
#define IS_LVD_ALL_PERIPH(PERIPH)    (((PERIPH) == LVD) 


/* LVD阈值电压选择定义 -------------------------------------------------------*/	 
#define TH_Voltage_SEL_Mask         ((uint32_t)0x0F)
#define TH_Voltage_SEL_2P7V         ((uint32_t)0x05)   /*!< LVD阈值电压2.7V */
#define TH_Voltage_SEL_3P3V         ((uint32_t)0x08)   /*!< LVD阈值电压3.3V */
#define TH_Voltage_SEL_3P7V         ((uint32_t)0x0A)   /*!< LVD阈值电压3.7V */
#define TH_Voltage_SEL_4P1V         ((uint32_t)0x0C)   /*!< LVD阈值电压4.1V */

#define IS_TH_VOLTAGE_SEL(VOLT)     (((VOLT) == TH_Voltage_SEL_2P7V) ||\
                                     ((VOLT) == TH_Voltage_SEL_3P3V) ||\
                                     ((VOLT) == TH_Voltage_SEL_3P7V) ||\
                                     ((VOLT) == TH_Voltage_SEL_4P1V)) 


/* LVD复位/中断功能定义 ------------------------------------------------------*/  
#define LVD_ACT_MASK        	 ((uint32_t)0x00000040)
#define LVD_ACT_RESET       	 ((uint32_t)0x00000040)  /*!< LVD产生复位 */
#define LVD_ACT_INTERRUPT        ((uint32_t)0x00000000)  /*!< LVD产生中断 */

#define IS_LVD_ACT(ACT)     	 (((ACT) == LVD_ACT_RESET) ||\
                            	  ((ACT) == LVD_ACT_INTERRUPT))


/* LVD滤波时钟定义 -----------------------------------------------------------*/
#define LVD_FLTCLK_SEL_MASK      ((uint32_t)0x00000300)
#define LVD_FLTCLK_SEL_Invalid   ((uint32_t)0x00)        /*!< LVD滤波时钟无效 */
#define LVD_FLTCLK_SEL_PCLK      ((uint32_t)0x00000100)  /*!< LVD滤波时钟为PCLK(选此时钟时LVD只能配置成中断方式) */
#define LVD_FLTCLK_SEL_LIRC      ((uint32_t)0x00000200)  /*!< LVD滤波时钟为LIRC */
  
#define IS_LVD_FLTCLK_SEL(CLK)   (((CLK) == LVD_FLTCLK_SEL_Invalid) ||\
                                  ((CLK) == LVD_FLTCLK_SEL_PCLK) ||\
                                  ((CLK) == LVD_FLTCLK_SEL_LIRC))                            	  


/* LVD数字滤波使能 -----------------------------------------------------------*/ 
#define LVD_FLT_ENABLE      	 ((uint32_t)0x00000080)  /*!< LVD使能数字滤波 */
#define LVD_FLT_DISABLE     	 ((uint32_t)0x00000000)  /*!< LVD禁止数字滤波 */

#define IS_LVD_FLT_EN(Status)    (((Status) == LVD_FLT_ENABLE) ||\
                            	  ((Status) == LVD_FLT_DISABLE))


/* LVD触发方式定义 -----------------------------------------------------------*/
#define LVD_TRIG_SEL_Mask        ((uint32_t)(0x07UL << 12))
#define LVD_TRIG_Disable         ((uint32_t)0x00)             /*!< LVD禁止触发 */
#define LVD_TRIG_FallingEdge     ((uint32_t)(0x01UL << 12))   /*!< LVD下降沿触发 */
#define LVD_TRIG_RisingEdge      ((uint32_t)(0x02UL << 12))   /*!< LVD上升沿触发 */
#define LVD_TRIG_BothEge         ((uint32_t)(0x03UL << 12))   /*!< LVD上升沿、下降沿均触发 */
#define LVD_TRIG_HighLevel       ((uint32_t)(0x04UL << 12))   /*!< LVD高电平触发 */
 
#define IS_LVD_TRIG(SEL)         (((SEL) == LVD_TRIG_Disable) ||\
                                  ((SEL) == LVD_TRIG_FallingEdge)||\
                                  ((SEL) == LVD_TRIG_RisingEdge) ||\
                                  ((SEL) == LVD_TRIG_BothEge) ||\
                                  ((SEL) == LVD_TRIG_HighLevel)) 

                                  
/* LVD中断使能定义 -----------------------------------------------------------*/		 
#define LVD_IT_ENABLE      ((uint32_t)0x00008000)  /*!< LVD中断使能 */
#define LVD_IT_DISABLE     ((uint32_t)0x00000000)  /*!< LVD中断禁止 */


/* LVD模块使能定义 -----------------------------------------------------------*/		 
#define LVD_ENABLE         ((uint32_t)0x00000020)  /*!< LVD模块使能 */
#define LVD_DISABLE        ((uint32_t)0x00000000)  /*!< LVD模块禁止 */


/* LVD采样滤波次数 -----------------------------------------------------------*/
#define LVD_FLT_NUM_Mask   ((uint32_t)0xFFFF0000)
#define IS_FLT_NUM(NUM)    (((NUM) >= 0) && ((NUM) <= 0xFFFF))


/* LVD中断标志位定义 ----------------------------------------------------------*/
#define LVD_IT_INTF        ((uint32_t)0x00000001)   /*!< LVD中断标志 */


/* Exported functions --------------------------------------------------------*/
void LVD_DeInit(void);
void LVD_Init(LVD_TypeDef* LVDx, LVD_InitTypeDef* LVD_InitStruct);
void LVD_StructInit(LVD_InitTypeDef* LVD_InitStruct);
void LVD_Set_Th_Voltage(LVD_TypeDef* LVDx, uint32_t  SelVoltge);
void LVD_Cmd(LVD_TypeDef* LVDx, FunctionalState NewState);
void LVD_Act_Config(LVD_TypeDef* LVDx, uint32_t SelAct);
void LVD_Filter_Cmd(LVD_TypeDef* LVDx, FunctionalState NewState);
void LVD_Set_FilterClk(LVD_TypeDef* LVDx, uint32_t FltClk);
void LVD_Set_FilterNum(LVD_TypeDef* LVDx, uint32_t FltNum);
void LVD_Trigger_Config(LVD_TypeDef* LVDx, uint32_t TriggerSel);
void LVD_ITConfig(LVD_TypeDef* LVDx, FunctionalState NewState);
FlagStatus LVD_GetFlagStatus(LVD_TypeDef* LVDx, uint32_t LVD_FLAG);
void LVD_ClearITFlag(LVD_TypeDef* LVDx);
FlagStatus LVD_Read_Result(LVD_TypeDef* LVDx);


#ifdef __cplusplus
}
#endif


#endif    /* __CPS32K21X_LVD_H__ */

