/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_ADC_H__
#define __CPS32K21X_ADC_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


/** @defgroup ADC_Exported_Constants
  * @{
  */ 
#define IS_ADC_ALL_PERIPH(PERIPH)    (((PERIPH) == ADC))   


/** 
  * @brief ADC Initialize structure definition  
  */ 
typedef struct
{
    uint32_t ConvMode_Sel;      /*!< ADC转换模式选择 */ 
    
    uint32_t Internal_Vref_En;  /*!< ADC内部参考电压使能 */   
    
	uint32_t SampleCycleSel;    /*!< ADC采样周期选择 */    
	
    uint32_t Ref_Voltage_Sel;   /*!< ADC参考电压选择 */  
    
	uint32_t Buffer_Dis;        /*!< ADC输入信号放大关闭 */  

	uint32_t ClockDiv;          /*!< ADC时钟分频设定 */  
	
	uint32_t Result_Align;      /*!< ADC转换结果对齐 */                                                                                                                                                                                                                                         
}ADC_InitTypeDef;


/* ADC转换模式选择 -----------------------------------------------------------*/
#define ADC_ConvMode_Scan        (BIT8)             /* 扫描转换模式 */
#define ADC_ConvMode_Single      ((uint32_t)0x00)   /* 单次转换模式 */

#define IS_ADC_ConvMode(SEL)     (((SEL) == ADC_ConvMode_Scan) ||\
                                  ((SEL) == ADC_ConvMode_Single))

  
/* 内部参考电压使能 ----------------------------------------------------------*/
#define ADC_Internal_VREF_ENABLE      (BIT16)            /*!< ADC内部参考电压使能 */   
#define ADC_Internal_VREF_DISABLE     ((uint32_t)0x00)   /*!< ADC内部参考电压禁止 */ 

#define ADC_Internal_VREF_En(STATUS)  (((STATUS) == ADC_Internal_VREF_ENABLE) || \
								       ((STATUS) == ADC_Internal_VREF_DISABLE))


/* 采样周期选择定义 ----------------------------------------------------------*/
#define ADC_SampleCycle_Mask      ((uint32_t)(0x03UL << 14))
#define ADC_SampleCycle_4Cycle    ((uint32_t)0x00)            /*!< 4个转换周期 */ 
#define ADC_SampleCycle_6Cycle    ((uint32_t)(0x01UL << 14))  /*!< 6个转换周期 */ 
#define ADC_SampleCycle_8Cycle    ((uint32_t)(0x02UL << 14))  /*!< 8个转换周期 */ 
#define ADC_SampleCycle_11Cycle   ((uint32_t)(0x03UL << 14))  /*!< 11个转换周期 */

#define IS_ADCSampleCycle(SEL)    (((SEL) == ADC_SampleCycle_4Cycle) || \
                                   ((SEL) == ADC_SampleCycle_6Cycle) || \
                                   ((SEL) == ADC_SampleCycle_8Cycle) || \
								   ((SEL) == ADC_SampleCycle_11Cycle))


/* 参考电压选择 --------------------------------------------------------------*/
#define ADC_VREF_SEL_Mask         ((uint32_t)(0x03UL << 12))
#define ADC_VREF_Internal_2V      ((uint32_t)0x00)            /*!< 内部2V参考电压 */ 
#define ADC_VREF_Internal_4V      ((uint32_t)(0x01UL << 12))  /*!< 内部4V参考电压 */ 
#define ADC_VREF_EXT_VREF         ((uint32_t)(0x02UL << 12))  /*!< 外部参考电压EXT_VREF(PB5) */ 
#define ADC_VREF_AVDD             ((uint32_t)(0x03UL << 12))  /*!< AVDD参考电压(默认参考) */ 

#define IS_ADC_VREF(SEL)          (((SEL) == ADC_VREF_Internal_2V) || \
                                   ((SEL) == ADC_VREF_Internal_4V) || \
                                   ((SEL) == ADC_VREF_EXT_VREF) || \
								   ((SEL) == ADC_VREF_AVDD))


/* ADC输入信号放大关闭 -------------------------------------------------------*/
#define ADC_Buffer_DISABLE         (BIT11)            /*!< ADC输入buffer关闭，即输入信号放大关闭 */ 
#define ADC_Buffer_ENABLE          ((uint32_t)0x00)   /*!< ADC输入buffer开启，即输入信号放大开启 */
  
#define IS_ADC_BUFFER_DIS(STATUS)  (((STATUS) == ADC_Buffer_DISABLE) || \
								    ((STATUS) == ADC_Buffer_ENABLE))

/* ADC时钟分频设定 -----------------------------------------------------------*/
#define ADC_CLOCK_DIV_Mask     ((uint32_t)(0x03UL << 2))
#define ADC_CLOCK_DIV1         ((uint32_t)0x00)            /*!< fADC = PCLK   */ 
#define ADC_CLOCK_DIV2         ((uint32_t)(0x01UL << 2))   /*!< fADC = PCLK/2 */ 
#define ADC_CLOCK_DIV4         ((uint32_t)(0x02UL << 2))   /*!< fADC = PCLK/4 */ 
#define ADC_CLOCK_DIV8         ((uint32_t)(0x03UL << 2))   /*!< fADC = PCLK/8 */ 

#define IS_ADC_CLOCK_DIV(SEL)  (((SEL) == ADC_CLOCK_DIV1) || \
                                ((SEL) == ADC_CLOCK_DIV2) || \
                                ((SEL) == ADC_CLOCK_DIV4) || \
								((SEL) == ADC_CLOCK_DIV8))


/* ADC转换结果对齐 -----------------------------------------------------------*/
#define ADC_RESULT_Align_Left      (BIT0)             /*!< ADC转换结果左对齐 */ 
#define ADC_RESULT_Align_Right     ((uint32_t)0x00)   /*!< ADC转换结果右对齐 */

#define IS_ADC_RESULT_Align(SEL)   (((SEL) == ADC_RESULT_Align_Left) || \
								    ((SEL) == ADC_RESULT_Align_Right))


/* ADC模块使能 ---------------------------------------------------------------*/
#define ADC_ENABLE       (BIT0)            /*!< ADC模块使能 */ 
#define ADC_DISABLE      ((uint32_t)0x00)  /*!< ADC模块禁止 */ 
                           

/* ADC转换通道定义 -----------------------------------------------------------*/
#define ADC_CHANNEL_Mask       ((uint32_t)0x1F)
#define ADC_CHANNEL_AIN0       ((uint32_t)0x00)   /*!< ADC通道：AIN0(PC4) */ 
#define ADC_CHANNEL_AIN1       ((uint32_t)0x01)   /*!< ADC通道：AIN1(PA8) */ 																 
#define ADC_CHANNEL_AIN2       ((uint32_t)0x02)   /*!< ADC通道：AIN2(PC3) */
#define ADC_CHANNEL_AIN3       ((uint32_t)0x03)   /*!< ADC通道：AIN3(PC2) */
#define ADC_CHANNEL_AIN4       ((uint32_t)0x04)   /*!< ADC通道：AIN4(PD5) */
#define ADC_CHANNEL_AIN5       ((uint32_t)0x05)   /*!< ADC通道：AIN5(PC1) */
#define ADC_CHANNEL_AIN6       ((uint32_t)0x06)   /*!< ADC通道：AIN6(PA9) */
#define ADC_CHANNEL_AIN7       ((uint32_t)0x07)   /*!< ADC通道：AIN7(PC15)   */
#define ADC_CHANNEL_AIN8       ((uint32_t)0x08)   /*!< ADC通道：AIN8(PC14) */
#define ADC_CHANNEL_AIN9       ((uint32_t)0x09)   /*!< ADC通道：AIN9(PB3) */
#define ADC_CHANNEL_AIN10      ((uint32_t)0x0A)   /*!< ADC通道：AIN10(PB2) */
#define ADC_CHANNEL_AIN11      ((uint32_t)0x0B)   /*!< ADC通道：AIN11(PB1) */
#define ADC_CHANNEL_AIN12      ((uint32_t)0x0C)   /*!< ADC通道：AIN12(PB0) */
#define ADC_CHANNEL_AIN13      ((uint32_t)0x0D)   /*!< ADC通道：AIN13(PC9) */
#define ADC_CHANNEL_AIN14      ((uint32_t)0x0E)   /*!< ADC通道：AIN14(PC8) */
#define ADC_CHANNEL_AIN15      ((uint32_t)0x0F)   /*!< ADC通道：AIN15(PA7) */
#define ADC_CHANNEL_AIN16      ((uint32_t)0x10)   /*!< ADC通道：AIN16(PA1) */
#define ADC_CHANNEL_1P5V       ((uint32_t)0x11)   /*!< ADC通道：内部电源电压1P5V */
#define ADC_CHANNEL_AVDD_DIV3  ((uint32_t)0x12)   /*!< ADC通道：1/3 AVDD */
#define ADC_CHANNEL_1V_AVREF   ((uint32_t)0x13)   /*!< ADC通道：1V AVREF */
#define ADC_CHANNEL_TS         ((uint32_t)0x14)   /*!< ADC通道：TS温度传感器输出 */
#define ADC_CHANNEL_PGA_OUT    ((uint32_t)0x15)   /*!< ADC通道：PGA_OUT */

#define IS_ADC_CHANNEL_SEL(CH)  (((CH) == ADC_CHANNEL_AIN0) || \
                                 ((CH) == ADC_CHANNEL_AIN1) || \
                                 ((CH) == ADC_CHANNEL_AIN2) || \
                                 ((CH) == ADC_CHANNEL_AIN3) || \
                                 ((CH) == ADC_CHANNEL_AIN4) || \
                                 ((CH) == ADC_CHANNEL_AIN5) || \
                                 ((CH) == ADC_CHANNEL_AIN6) || \
                                 ((CH) == ADC_CHANNEL_AIN7) || \
                                 ((CH) == ADC_CHANNEL_AIN8) || \
                                 ((CH) == ADC_CHANNEL_AIN9) || \
                                 ((CH) == ADC_CHANNEL_AIN10) || \
                                 ((CH) == ADC_CHANNEL_AIN11) || \
                                 ((CH) == ADC_CHANNEL_AIN12) || \
                                 ((CH) == ADC_CHANNEL_AIN13) || \
                                 ((CH) == ADC_CHANNEL_AIN14) || \
                                 ((CH) == ADC_CHANNEL_AIN15) || \
                                 ((CH) == ADC_CHANNEL_AIN16) || \
                                 ((CH) == ADC_CHANNEL_1P5V) || \
                                 ((CH) == ADC_CHANNEL_AVDD_DIV3) || \
                                 ((CH) == ADC_CHANNEL_1V_AVREF) || \
                                 ((CH) == ADC_CHANNEL_TS) || \
								 ((CH) == ADC_CHANNEL_PGA_OUT))


#define ADC_SINGLE_START     (BIT0)    /*!< ADC单次转换启动 */
#define ADC_SQR_SCAN_START   (BIT0)    /*!< ADC顺序扫描转换启动 */
#define ADC_JQR_SCAN_START   (BIT0)    /*!< ADC插队扫描转换启动 */


#define IS_ADC_HT_COMPARE_VALUE(Value)     (((Value) >= 0) && ((Value) <<= 0xFFF))
#define IS_ADC_LT_COMPARE_VALUE(Value)     (((Value) >= 0) && ((Value) <<= 0xFFF))


/* ADC阈值比较定义 -----------------------------------------------------------*/
#define ADC_REG_CMP_ENABLE      (BIT14)  /*!< 使能区间比较 */
#define ADC_HT_CMP_ENABLE       (BIT13)  /*!< 使能高阈值比较 */
#define ADC_LT_CMP_ENABLE       (BIT12)  /*!< 使能低阈值比较 */

/* ADC阈值通道定义 -----------------------------------------------------------*/
#define ADC_THRESHOLD_CH_Mask   ((uint32_t)(0x1FUL << 1))
#define ADC_SQR_SCAN_CH0        ((uint32_t)0x00)            /*!< 顺序扫描转换通道0 */
#define ADC_SQR_SCAN_CH1        ((uint32_t)(0x01UL << 1))   /*!< 顺序扫描转换通道1 */
#define ADC_SQR_SCAN_CH2        ((uint32_t)(0x02UL << 1))   /*!< 顺序扫描转换通道2 */
#define ADC_SQR_SCAN_CH3        ((uint32_t)(0x03UL << 1))   /*!< 顺序扫描转换通道3 */
#define ADC_SQR_SCAN_CH4        ((uint32_t)(0x04UL << 1))   /*!< 顺序扫描转换通道4 */
#define ADC_SQR_SCAN_CH5        ((uint32_t)(0x05UL << 1))   /*!< 顺序扫描转换通道5 */
#define ADC_SQR_SCAN_CH6        ((uint32_t)(0x06UL << 1))   /*!< 顺序扫描转换通道6 */
#define ADC_SQR_SCAN_CH7        ((uint32_t)(0x07UL << 1))   /*!< 顺序扫描转换通道7 */
#define ADC_SQR_SCAN_CH8        ((uint32_t)(0x08UL << 1))   /*!< 顺序扫描转换通道8 */
#define ADC_SQR_SCAN_CH9        ((uint32_t)(0x09UL << 1))   /*!< 顺序扫描转换通道9 */
#define ADC_JQR_SCAN_CH0        ((uint32_t)(0x0EUL << 1))   /*!< 插队扫描转换通道0 */
#define ADC_JQR_SCAN_CH1        ((uint32_t)(0x0FUL << 1))   /*!< 插队扫描转换通道1 */
#define ADC_JQR_SCAN_CH2        ((uint32_t)(0x10UL << 1))   /*!< 插队扫描转换通道2 */
#define ADC_JQR_SCAN_CH3        ((uint32_t)(0x11UL << 1))   /*!< 插队扫描转换通道3 */
#define ADC_RESULT              ((uint32_t)(0x12UL << 1))   /*!< 选择ADC_RESULT进行阈值比较 */

#define IS_ADC_TH_CHANNEL(CH)   (((CH) == ADC_SQR_SCAN_CH0) || \
                                 ((CH) == ADC_SQR_SCAN_CH1) || \
                                 ((CH) == ADC_SQR_SCAN_CH2) || \
                                 ((CH) == ADC_SQR_SCAN_CH3) || \
                                 ((CH) == ADC_SQR_SCAN_CH4) || \
                                 ((CH) == ADC_SQR_SCAN_CH5) || \
                                 ((CH) == ADC_SQR_SCAN_CH6) || \
                                 ((CH) == ADC_SQR_SCAN_CH7) || \
                                 ((CH) == ADC_SQR_SCAN_CH8) || \
                                 ((CH) == ADC_SQR_SCAN_CH9) || \
                                 ((CH) == ADC_JQR_SCAN_CH0) || \
                                 ((CH) == ADC_JQR_SCAN_CH1) || \
                                 ((CH) == ADC_JQR_SCAN_CH2) || \
                                 ((CH) == ADC_JQR_SCAN_CH3) || \
								 ((CH) == ADC_RESULT))


#define ADC_SQR_ConvNum_Mask        ((uint32_t)(0x0FUL << 20))
#define IS_ADC_SQR_ConvNum(Value)   (((Value) >= 0) && ((Value) <<= 10))

#define ADC_JQR_ConvNum_Mask        ((uint32_t)(0x07UL << 20))
#define IS_ADC_JQR_ConvNum(Value)   (((Value) >= 0) && ((Value) <<= 4))


/* ADC中断使能定义 -----------------------------------------------------------*/
#define ADC_JQR_IE       (BIT5)   /*!< 插队扫描转换完成中断使能 */
#define ADC_SQR_IE       (BIT4)   /*!< 顺序扫描转换完成中断使能 */
#define ADC_REG_IE       (BIT3)   /*!< 区间中断使能 */												 
#define ADC_HT_IE        (BIT2)   /*!< 上阈值中断使能 */
#define ADC_LT_IE        (BIT1)   /*!< 下阈值中断使能 */
#define ADC_SGL_IE       (BIT0)   /*!< 单次转换完成中断使能 */

#define IS_ADC_IE(SEL)   (((SEL) == ADC_JQR_IE)|| \
                          ((SEL) == ADC_SQR_IE)|| \
                          ((SEL) == ADC_REG_IE)|| \
                          ((SEL) == ADC_HT_IE) || \
                          ((SEL) == ADC_LT_IE) || \
                          ((SEL) == ADC_SGL_IE))

/* ADC中断标志定义 -----------------------------------------------------------*/
#define ADC_JQR_IF       (BIT5)   /*!< 插队扫描转换完成中断标志 */
#define ADC_SQR_IF       (BIT4)   /*!< 顺序扫描转换完成中断标志 */
#define ADC_REG_IF       (BIT3)   /*!< 区间中断标志 */												 
#define ADC_HT_IF        (BIT2)   /*!< 上阈值中断标志 */
#define ADC_LT_IF        (BIT1)   /*!< 下阈值中断标志 */
#define ADC_SGL_IF       (BIT0)   /*!< 单次转换完成中断标志 */
#define ADC_ALL_IF       (ADC_JQR_IF | ADC_SQR_IF | ADC_REG_IF | ADC_HT_IF | ADC_LT_IF | ADC_SGL_IF)

#define IS_ADC_IT_FLAG(IF)   (((IF) == ADC_JQR_IF)|| \
                              ((IF) == ADC_SQR_IF)|| \
                              ((IF) == ADC_REG_IF)|| \
                              ((IF) == ADC_HT_IF) || \
                              ((IF) == ADC_LT_IF) || \
                              ((IF) == ADC_SGL_IF)|| \
						      ((IF) == ADC_ALL_IF))

/* ADC外部触发源定义 ---------------------------------------------------------*/
#define ADC_TRIG_SOURCE_Mask     ((uint8_t)(0x1F))
#define ADC_AUTO_TRIG_DISABLE    ((uint8_t)(0x00))    /*!< 禁止自动触发 */
#define ADC_TRIG_TIM10_IT        ((uint8_t)(0x01))    /*!< TIM10中断触发 */
#define ADC_TRIG_TIM11_IT        ((uint8_t)(0x02))    /*!< TIM11中断触发 */
#define ADC_TRIG_ETIMER_IT       ((uint8_t)(0x03))    /*!< ETIMER中断触发 */
#define ADC_TRIG_LPTIM_IT        ((uint8_t)(0x04))    /*!< LPTIM中断触发 */
#define ADC_TRIG_ETIMER_TRGO     ((uint8_t)(0x05))    /*!< ETIMER TRGO触发 */
#define ADC_TRIG_TIM2_TRGO       ((uint8_t)(0x06))    /*!< TIM2 TRGO触发 */
#define ADC_TRIG_TIM2_IT         ((uint8_t)(0x07))    /*!< TIM2中断触发 */
#define ADC_TRIG_EUART0_RX_IT    ((uint8_t)(0x08))    /*!< EUART0接收完成中断触发 */
#define ADC_TRIG_EUART1_RX_IT    ((uint8_t)(0x09))    /*!< EUART1接收完成中断触发 */
#define ADC_TRIG_ASPI_RX_IT      ((uint8_t)(0x0A))    /*!< ASPI接收完成中断触发 */
#define ADC_TRIG_VC_IT           ((uint8_t)(0x0B))    /*!< VC中断触发 */
#define ADC_TRIG_SPI1_IT         ((uint8_t)(0x0C))    /*!< SPI1中断触发 */
#define ADC_TRIG_ASPI_TX_IT      ((uint8_t)(0x0F))    /*!< ASPI发送完成中断触发 */
#define ADC_TRIG_PA1_IT          ((uint8_t)(0x10))    /*!< PA1中断触发 */
#define ADC_TRIG_PA2_IT          ((uint8_t)(0x11))    /*!< PA2中断触发 */
#define ADC_TRIG_PA3_IT          ((uint8_t)(0x12))    /*!< PA3中断触发 */
#define ADC_TRIG_PB4_IT          ((uint8_t)(0x13))    /*!< PB4中断触发 */
#define ADC_TRIG_PB5_IT          ((uint8_t)(0x14))    /*!< PB5中断触发 */
#define ADC_TRIG_PC3_IT          ((uint8_t)(0x15))    /*!< PC3中断触发 */
#define ADC_TRIG_PC4_IT          ((uint8_t)(0x16))    /*!< PC4中断触发 */
#define ADC_TRIG_PC5_IT          ((uint8_t)(0x17))    /*!< PC5中断触发 */
#define ADC_TRIG_PC6_IT          ((uint8_t)(0x18))    /*!< PC6中断触发 */
#define ADC_TRIG_PC7_IT          ((uint8_t)(0x19))    /*!< PC7中断触发 */
#define ADC_TRIG_PD1_IT          ((uint8_t)(0x1A))    /*!< PD1中断触发 */
#define ADC_TRIG_PD2_IT          ((uint8_t)(0x1B))    /*!< PD2中断触发 */
#define ADC_TRIG_PD3_IT          ((uint8_t)(0x1C))    /*!< PD3中断触发 */
#define ADC_TRIG_EUART0_TX_IT    ((uint8_t)(0x1E))    /*!< EUART0发送完成中断触发 */
#define ADC_TRIG_EUART1_TX_IT    ((uint8_t)(0x1F))    /*!< EUART1发送完成中断触发 */

#define IS_ADC_TRIG_SOURCE(SEL)   (((SEL) >= 0) && ((SEL) <= 0x1F))


/* Exported functions --------------------------------------------------------*/  
void ADC_DeInit(void);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_Single_Channel_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_Single_Conv_Start(ADC_TypeDef* ADCx);
uint16_t ADC_Get_Single_Result(ADC_TypeDef* ADCx);
void ADC_REG_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_HT_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_LT_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_Threshold_CH_Config(ADC_TypeDef* ADCx, uint32_t CmpChannel);
void ADC_Set_HT_CompareValue(ADC_TypeDef* ADCx, uint32_t HtValue);
void ADC_Set_LT_CompareValue(ADC_TypeDef* ADCx, uint32_t LtValue);
void ADC_SQR_CH0_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH1_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH2_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH3_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH4_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH5_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH6_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH7_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH8_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_SQR_CH9_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_Set_SQR_ConvNum(ADC_TypeDef* ADCx, uint32_t ConvNum);
void ADC_SQR_Conv_Start(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result0(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result1(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result2(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result3(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result4(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result5(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result6(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result7(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result8(ADC_TypeDef* ADCx);
uint16_t ADC_Get_SQR_Result9(ADC_TypeDef* ADCx);
void ADC_JQR_CH0_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_JQR_CH1_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_JQR_CH2_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_JQR_CH3_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx);
void ADC_Set_JQR_ConvNum(ADC_TypeDef* ADCx, uint32_t ConvNum);
void ADC_JQR_Conv_Start(ADC_TypeDef* ADCx);
uint16_t ADC_Get_JQR_Result0(ADC_TypeDef* ADCx);
uint16_t ADC_Get_JQR_Result1(ADC_TypeDef* ADCx);
uint16_t ADC_Get_JQR_Result2(ADC_TypeDef* ADCx);
uint16_t ADC_Get_JQR_Result3(ADC_TypeDef* ADCx);
void ADC_SGL_SQR_Trig_Select(ADC_TypeDef* ADCx, uint8_t TriggerSource);
void ADC_JQR_Trig_Select(ADC_TypeDef* ADCx, uint8_t TriggerSource);
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT_FLAG);
void ADC_ClearITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT_FLAG);


#ifdef __cplusplus
}
#endif

#endif /*__CPS32K21X_ADC_H__ */


