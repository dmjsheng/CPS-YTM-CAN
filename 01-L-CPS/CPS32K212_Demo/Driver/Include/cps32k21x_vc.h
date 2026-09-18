/*Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_VC_H__
#define __CPS32K21X_VC_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


/**
  * @} VC_InitTypeDef
  */
typedef struct
{
    uint32_t dac_vref_sel;       /*!< DAC参考电压选择 */ 

    uint32_t dac_div_sel;        /*!< 6位DAC分频选择 */
    
    uint32_t dac_EnStatus;       /*!< 6位DAC使能状态 */

    uint32_t hyst_voltage_sel;   /*!< VC迟滞电压选择 */ 

    uint32_t NinSel;             /*!< VC比较器反向端输入选择 */ 

    uint32_t PinSel;             /*!< VC比较器同向端输入选择 */ 

    uint32_t filterClk_sel;      /*!< VC滤波时钟选择 */

    uint32_t filter_EnStatus;    /*!< VC滤波使能状态 */

    uint32_t trigger_sel;        /*!< VC触发方式选择 */
                                  
}VC_InitTypeDef;

	 	 
/* Exported types ------------------------------------------------------------*/
#define IS_VC_ALL_PERIPH(PERIPH) 	((PERIPH) == VC) 


/*-------------------------- VC_CSR Register define --------------------------*/

/* VC参考电压定义 ------------------------------------------------------------*/
#define VC_DAC_VREF_SEL_2V4V        (BIT15)           /*!< 内部参考电压2V/4V */ 
#define VC_DAC_VREF_SEL_AVDD        ((uint32_t)0x00)  /*!< AVDD参考电压 */ 

#define IS_VC_DAC_VREF(SEL)         (((SEL) == VC_DAC_VREF_SEL_2V4V) ||\
						             ((SEL) == VC_DAC_VREF_SEL_AVDD)) 

/* 6位DAC使能定义 ------------------------------------------------------------*/
#define VC_DAC_ENABLE           (BIT14)           /*!< DAC使能 */ 
#define VC_DAC_DISABLE          ((uint32_t)0x00)  /*!< DAC禁止 */ 
 
#define IS_VC_DAC_EN(STATUS)    (((STATUS) == VC_DAC_ENABLE) ||\
						         ((STATUS) == VC_DAC_DISABLE)) 

/* DAC分压分频比定义 ---------------------------------------------------------*/
#define VC_DAC_DIV_Mask        ((uint32_t)(0x3FUL << 8))
#define IS_VC_DAC_DIV(SEL)     (((SEL) >= 0) && ((SEL) <= 0x3F))


/* VC迟滞电压定义 --------------------------------------------------------------*/
#define VC_HYST_VOLT_Mask       ((uint32_t)(0x03UL << 5))
#define VC_HYST_VOLT_0MV        ((uint32_t)0x00)           /*!< VC迟滞电压0mv */ 
#define VC_HYST_VOLT_10MV       ((uint32_t)(0x01UL << 5))  /*!< VC迟滞电压10mv */ 
#define VC_HYST_VOLT_20MV       ((uint32_t)(0x02UL << 5))  /*!< VC迟滞电压20mv */
#define VC_HYST_VOLT_30MV       ((uint32_t)(0x03UL << 5))  /*!< VC迟滞电压30mv */
   
#define IS_VC_HYST_VOLT(VOLT)   (((VOLT) == VC_HYST_VOLT_0MV) ||\
                                 ((VOLT) == VC_HYST_VOLT_10MV) ||\
							     ((VOLT) == VC_HYST_VOLT_20MV) ||\
						         ((VOLT) == VC_HYST_VOLT_30MV)) 


/* VC反相输入端电压选择定义 --------------------------------------------------*/
#define VC_INNSEL_Mask          ((uint32_t)(0x07UL << 2))
#define VC_INNSEL_VC_INN0       ((uint32_t)0x00)             /*!< VC_INN0 端子输入 */
#define VC_INNSEL_VC_INN1       ((uint32_t)(0x01UL << 2))    /*!< VC_INN1 端子输入 */
#define VC_INNSEL_VC_INN2       ((uint32_t)(0x02UL << 2))    /*!< VC_INN2 端子输入 */
#define VC_INNSEL_VC_INN3       ((uint32_t)(0x03UL << 2))    /*!< VC_INN3 端子输入 */
#define VC_INNSEL_2V4V          ((uint32_t)(0x04UL << 2))    /*!< 内部基准电压 2V/4V */
#define VC_INNSEL_1V            ((uint32_t)(0x05UL << 2))    /*!< 内部基准电压 1V */
#define VC_INNSEL_DAC_OUT       ((uint32_t)(0x07UL << 2))    /*!< 内部 DAC 的分压输出 */
  
#define IS_VC_NinSEL(SEL)      (((SEL) == VC_INNSEL_VC_INN0) ||\
                                ((SEL) == VC_INNSEL_VC_INN1) ||\
                                ((SEL) == VC_INNSEL_VC_INN2) ||\
                                ((SEL) == VC_INNSEL_VC_INN3) ||\
                                ((SEL) == VC_INNSEL_2V4V) ||\
                                ((SEL) == VC_INNSEL_1V) ||\
                                ((SEL) == VC_INNSEL_DAC_OUT)) 


/* VC同相输入端电压选择定义 --------------------------------------------------*/
#define VC_INPSEL_Mask          ((uint32_t)0x03)
#define VC_INPSEL_VC_INP0       ((uint32_t)0x00)   /*!< VC_INP0 端子输入 */
#define VC_INPSEL_VC_INP1       ((uint32_t)0x01)   /*!< VC_INP1 端子输入 */
#define VC_INPSEL_VC_INP2       ((uint32_t)0x02)   /*!< VC_INP2 端子输入 */
#define VC_INPSEL_PGA_OUT       ((uint32_t)0x03)   /*!< VC_PGA的输出 */

#define IS_VC_PinSEL(SEL)      (((SEL) == VC_INPSEL_VC_INP0) ||\
                                ((SEL) == VC_INPSEL_VC_INP1) ||\
                                ((SEL) == VC_INPSEL_VC_INP2) ||\
                                ((SEL) == VC_INPSEL_PGA_OUT)) 

						      
/*--------------------------- VC_CR Register define --------------------------*/
/* 滤波使能定义 --------------------------------------------------------------*/
#define VC_FILTER_ENABLE        (BIT23)            /*!< 数字滤波使能 */ 
#define VC_FILTER_DISABLE       ((uint32_t)0x00)   /*!< 数字滤波禁止 */ 
  
#define IS_VC_FILTER_EN(Status) (((Status) == VC_FILTER_ENABLE) ||\
                                 ((Status) == VC_FILTER_DISABLE)) 


/* 滤波时钟定义 --------------------------------------------------------------*/
#define VC_FLTCLK_Mask          ((uint32_t)(0x03UL << 21))
#define VC_FLTCLK_SEL_Invalid   ((uint32_t)0x00)            /*!< 滤波时钟选择：无效 */ 
#define VC_FLTCLK_SEL_PCLK      ((uint32_t)(0x01UL << 21))  /*!< 滤波时钟选择：PCLK */ 
#define VC_FLTCLK_SEL_LIRC      ((uint32_t)(0x02UL << 21))  /*!< 滤波时钟选择：LIRC */ 

#define IS_VC_FLTCLK(SEL)       (((SEL) == VC_FLTCLK_SEL_Invalid) ||\
                                 ((SEL) == VC_FLTCLK_SEL_PCLK) ||\
                                 ((SEL) == VC_FLTCLK_SEL_LIRC)) 

/* 采样滤波次数 --------------------------------------------------------------*/
#define VC_FLTNUM_Mask          ((uint32_t)(0x07UL << 16))
#define VC_FLTNUM_1_FLTCLK      ((uint32_t)0x00)              /*!< 滤波采样为 1 个滤波时钟周期 */
#define VC_FLTNUM_2_FLTCLK      ((uint32_t)(0x01UL << 16))    /*!< 滤波采样为 2 个滤波时钟周期 */
#define VC_FLTNUM_4_FLTCLK      ((uint32_t)(0x02UL << 16))    /*!< 滤波采样为 4 个滤波时钟周期 */
#define VC_FLTNUM_8_FLTCLK      ((uint32_t)(0x03UL << 16))    /*!< 滤波采样为 8 个滤波时钟周期 */
#define VC_FLTNUM_16_FLTCLK     ((uint32_t)(0x04UL << 16))    /*!< 滤波采样为 16 个滤波时钟周期 */
#define VC_FLTNUM_32_FLTCLK     ((uint32_t)(0x05UL << 16))    /*!< 滤波采样为 32 个滤波时钟周期 */
#define VC_FLTNUM_64_FLTCLK     ((uint32_t)(0x06UL << 16))    /*!< 滤波采样为 64 个滤波时钟周期 */
#define VC_FLTNUM_128_FLTCLK    ((uint32_t)(0x07UL << 16))    /*!< 滤波采样为 128 个滤波时钟周期 */

#define IS_VC_FLTNUM(SEL)       (((SEL) == VC_FLTNUM_1_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_2_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_4_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_8_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_16_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_32_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_64_FLTCLK) || \
                                 ((SEL) == VC_FLTNUM_128_FLTCLK)) 


/* VC中断使能定义-------------------------------------------------------------*/
#define VC_IT_ENABLE       (BIT7)              /*!< VC中断使能 */
#define VC_IT_DISABLE      ((uint32_t)0x00)    /*!< VC中断禁止 */


/* 触发方式定义 --------------------------------------------------------------*/	
#define VC_TRIG_SEL_Mask          ((uint32_t)(0x07UL << 4))
#define VC_TRIG_SEL_DISABLE       ((uint32_t)0x00)             /*!< VC禁止触发 */
#define VC_TRIG_SEL_FallingEdge   ((uint32_t)(0x01UL << 4))    /*!< VC下降沿触发 */
#define VC_TRIG_SEL_RisingEdge    ((uint32_t)(0x02UL << 4))    /*!< VC上升沿触发 */
#define VC_TRIG_SEL_HighLevel     ((uint32_t)(0x04UL << 4))    /*!< VC高电平触发 */

#define IS_VC_TRIG(SEL)           (((SEL) == VC_TRIG_SEL_DISABLE) ||\
                                   ((SEL) == VC_TRIG_SEL_FallingEdge) ||\
                                   ((SEL) == VC_TRIG_SEL_RisingEdge) ||\
                                   ((SEL) == VC_TRIG_SEL_HighLevel)) 	

/* VC模块使能定义-------------------------------------------------------------*/
#define VC_ENABLE       (BIT0)             /*!< VC模块使能 */
#define VC_DISABLE      ((uint32_t)0x00)   /*!< VC模块禁止 */


/*------------------------ VC_OUTCFG Register define -------------------------*/

/* VC比较输出配置定义---------------------------------------------------------*/
#define VC_INVPAD_EN                 (BIT14)   /*!< VC输出到PAD反向使能 */
#define VC_INT_ETIME_TIM2_BKE_EN     (BIT13)   /*!< VC 中断作为 ETIMER/TIM2 刹车控制 */
#define VC_ETIMER_TIM2_CH4_EN        (BIT12)   /*!< VC输出到ETIMER_CH4,TIM2_CH4捕获输入使能 */
#define VC_ETIMER_CH4_INV_EN         (BIT11)   /*!< VC输出到ETIMER_CH4反向捕获输入使能 */
#define VC_ETIMER_TIM2_CH3_EN        (BIT10)   /*!< VC输出到ETIMER_CH3,TIM2_CH3捕获输入使能 */
#define VC_ETIMER_CH3_INV_EN         (BIT9)    /*!< VC输出到ETIMER_CH3反向捕获输入使能  */
#define VC_ETIMER_TIM2_CH2_EN        (BIT8)    /*!< VC输出到ETIMER_CH2,TIM2_CH2捕获输入使能  */
#define VC_ETIMER_CH2_INV_EN         (BIT7)    /*!< VC输出到ETIMER_CH2反向捕获输入使能  */
#define VC_ETIMER_TIM2_CH1_EN        (BIT6)    /*!< VC输出到ETIMER_CH1,TIM2_CH1捕获输入使能  */
#define VC_ETIMER_CH1_INV_EN         (BIT5)    /*!< VC输出到ETIMER_CH1反向捕获输入使能  */
#define VC_LPTIMEXT_EN               (BIT4)    /*!< VC输出到LPTIM外部时钟使能 */
#define VC_LPTIM_GATE_EN             (BIT3)    /*!< VC输出到LPTIM门控使能 */
#define VC_TIM11_GATE_EN             (BIT2)    /*!< VC输出到TIM11门控使能 */
#define VC_TIM10_GATE_EN             (BIT1)    /*!< VC输出到TIM10门控使能 */
#define VC_BTIM_LPTIM_GATE_INV_EN    (BIT0)    /*!< VC输出到TIM10, TIM11, LPTIM门控反向使能 */


/*------------------------- VC_SR Register define ----------------------------*/

/* VC中断标志位定义 ----------------------------------------------------------*/
#define VC_IT_INTF     ((uint32_t)0x00000001)   /*!< VC中断标志 */


/*------------------------ VC_PGACR Register define --------------------------*/

/* PGA Offset电压定义---------------------------------------------------------*/
#define VC_PGA_OffsetVolt_Mask       ((uint32_t)(0x07UL << 5))
#define VC_PGA_OffsetVolt_None1      ((uint32_t)0x00)            /*!< No offset */
#define VC_PGA_OffsetVolt_ADD_3mV    ((uint32_t)(0x01UL << 5))   /*!< offset +3mV */
#define VC_PGA_OffsetVolt_ADD_6mV    ((uint32_t)(0x02UL << 5))   /*!< offset +6mV */
#define VC_PGA_OffsetVolt_ADD_9mV    ((uint32_t)(0x03UL << 5))   /*!< offset +9mV */
#define VC_PGA_OffsetVolt_None2      ((uint32_t)(0x04UL << 5))   /*!< No offset */
#define VC_PGA_OffsetVolt_DEC_9mV    ((uint32_t)(0x05UL << 5))   /*!< offset -9mV */
#define VC_PGA_OffsetVolt_DEC_6mV    ((uint32_t)(0x06UL << 5))   /*!< offset -6mV */
#define VC_PGA_OffsetVolt_DEC_3mV    ((uint32_t)(0x07UL << 5))   /*!< offset -3mV */

#define IS_VC_PGA_OffsetVolt(VOLT)   (((VOLT) == VC_PGA_OffsetVolt_None1) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_ADD_3mV) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_ADD_6mV) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_ADD_9mV) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_None2) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_DEC_9mV) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_DEC_6mV) || \
                                      ((VOLT) == VC_PGA_OffsetVolt_DEC_3mV)) 

/* PGA使能定义----------------------------------------------------------------*/
#define VC_PGA_ENABLE    (BIT1)    /*!< PGA使能 */
#define VC_PGA_DISABLE    (0)      /*!< PGA禁止 */


/* PGA_LOOP使能定义-----------------------------------------------------------*/
#define VC_PGA_LOOP_ENABLE   (BIT0)    /*!< PGA内部LOOP电路有效 */
#define VC_PGA_LOOP_DISABLE   (0)      /*!< PGA内部LOOP电路无效 */


/* Exported functions --------------------------------------------------------*/
void VC_DeInit(void);
void VC_StructInit(VC_InitTypeDef* VC_InitStruct);
void VC_Init(VC_TypeDef* VCx, VC_InitTypeDef* VC_InitStruct);
void VC_PinSel_Config(VC_TypeDef* VCx, uint32_t PinSel);
void VC_NinSel_Config(VC_TypeDef* VCx, uint32_t NinSel);
void VC_Set_DAC_Div(VC_TypeDef* VCx, uint32_t DAC_Div);
void VC_DAC_Cmd(VC_TypeDef* VCx, FunctionalState NewState);
void VC_DAC_Vref_Config(VC_TypeDef* VCx, uint32_t Vref);
void VC_Hyst_Voltage_Config(VC_TypeDef* VCx, uint32_t HystVolt);
void VC_Cmd(VC_TypeDef* VCx, FunctionalState NewState);
void VC_SetFilterClk(VC_TypeDef* VCx, uint32_t FltClk);
void VC_Filter_Cmd(VC_TypeDef* VCx, FunctionalState NewState);
void VC_SetFltNum(VC_TypeDef* VCx, uint32_t FltNum);
void VC_Trigger_Config(VC_TypeDef* VCx, uint32_t TriggerSel);
void VC_ITConfig(VC_TypeDef* VCx, FunctionalState NewState);
FlagStatus VC_GetFlagStatus(VC_TypeDef* VCx, uint32_t VC_FLAG);
void VC_ClearITFlag(VC_TypeDef* VCx);
FlagStatus VC_Read_Result(VC_TypeDef* VCx);
void VC_OutConfig_Cmd(VC_TypeDef* VCx, uint32_t OutCfgType, FunctionalState NewState);
void VC_PGA_OffsetVolt_Set(VC_TypeDef* VCx, uint32_t OffsetVolt);
void VC_PGA_Cmd(VC_TypeDef* VCx, FunctionalState NewState);
void VC_PGA_Loop_Cmd(VC_TypeDef* VCx, FunctionalState NewState);


#ifdef __cplusplus
}
#endif


#endif   /* __CPS32K21X_VC_H__ */



