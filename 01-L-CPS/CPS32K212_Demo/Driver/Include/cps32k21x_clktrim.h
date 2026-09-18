/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_CLKTRIM_H__
#define __CPS32K21X_CLKTRIM_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"



#define IS_CLKTRIM_ALL_PERIPH(PERIPH)       ((PERIPH) == CLKTRIM)



/*--------------------- CLKTRIM_CR Register define  --------------------------*/
#define CLKTRIM_DET_ENABLE      (BIT10)  /*!< HXT硬件监测使能 */
#define CLKTRIM_DET_DISABLE      (0)     /*!< HXT硬件监测禁止 */


#define REFCALCLK_ENABLE        (BIT9)   /*!< 参考时钟和待监测时钟使能 */
#define REFCALCLK_DISABLE        (0)     /*!< 参考时钟和待监测时钟禁止 */


#define CLKTRIM_SEL_RESET       (BIT8)   /*!< 中断及复位选择：复位 */
#define CLKTRIM_SEL_INTERRUPT    (0)     /*!< 中断及复位选择：中断 */


#define CLKTRIM_MON_ENABLE      (BIT7)   /*!< 监测模式使能 */
#define CLKTRIM_MON_DISABLE      (0)     /*!< 监测模式禁止 */


/**
  * @} 待监测时钟源选择
  */
#define CALCLK_Mask     	   ((uint32_t)(0x07UL << 4))
#define CALCLK_HIRC      	   ((uint32_t)0x00UL)           /*!< 内部高速8MHz时钟 */
#define CALCLK_HXT      	   ((uint32_t)(0x01UL << 4))    /*!< 外部高速晶振时钟 */
#define CALCLK_LIRC      	   ((uint32_t)(0x02UL << 4))    /*!< 内部低频时钟 */
#define CALCLK_PLL      	   ((uint32_t)(0x04UL << 4))    /*!< PLL时钟 */

#define IS_CALCLK_SEL(CLK)     (((CLK) == CALCLK_HIRC) ||\
								((CLK) == CALCLK_HXT)  ||\
							    ((CLK) == CALCLK_LIRC) ||\
								((CLK) == CALCLK_PLL))


#define IS_CLKTRIM_REFCON_VALUE(VALUE)    (((VALUE) >= 0) && ((VALUE) <= 0xFFFFFFFFUL))


/**
  * @} 参考时钟源选择
  */
#define REFCLK_Mask             ((uint32_t)(0x07UL << 1))
#define REFCLK_HIRC      		((uint32_t)0x00UL)           /*!< 内部高速8MHz时钟 */
#define REFCLK_HXT      		((uint32_t)(0x01UL << 1))    /*!< 外部高速晶振时钟 */
#define REFCLK_LIRC      		((uint32_t)(0x02UL << 1))    /*!< 内部低频时钟 */
#define REFCLK_EXT_CLK_IN      	((uint32_t)(0x04UL << 1))    /*!< 外部输入时钟 */
#define REFCLK_PLL     			((uint32_t)(0x05UL << 1))    /*!< PLL时钟 */

#define IS_REFCLK_SEL(CLK)      (((CLK) == REFCLK_HIRC) ||\
                                 ((CLK) == REFCLK_HXT) ||\
                                 ((CLK) == REFCLK_LIRC) ||\
                                 ((CLK) == REFCLK_EXT_CLK_IN) ||\
                                 ((CLK) == REFCLK_PLL))


#define CLKTRIM_TRIM_START      ((uint32_t)0x01)   /*!< 软监测开始 */
#define CLKTRIM_TRIM_STOP       ((uint32_t)0x00)   /*!< 软监测停止 */																


/**
  * @} 中断标志位
  */
#define CLKTRIM_FLAG_REFCNTSTOP    ((uint32_t)0x01)   /*!< 参考计数器停止标志 */
#define CLKTRIM_FLAG_CALCNTOVF     ((uint32_t)0x02)   /*!< 校准计数器溢出标志 */
#define CLKTRIM_FLAG_HXTFAULT      ((uint32_t)0x08)   /*!< HXT失效标志 */
#define CLKTRIM_FLAG_PLLFAULT      ((uint32_t)0x10)   /*!< PLL失效标志 */
#define CLKTRIM_FLAG_LIRCFAULT     ((uint32_t)0x20)   /*!< LIRC失效标志 */
#define CLKTRIM_FLAG_HIRCFAULT     ((uint32_t)0x40)   /*!< HIRC失效标志 */
#define CLKTRIM_FLAG_DET_HXTFAULT  ((uint32_t)0x80)   /*!< HXT硬件监测停振检知标志 */
#define CLKTRIM_FLAG_ALL           ((uint32_t)0xF8)   

#define IS_CLKTRIM_FLAG(FLAG)      (((FLAG) == CLKTRIM_FLAG_REFCNTSTOP) ||\
							        ((FLAG) == CLKTRIM_FLAG_CALCNTOVF) ||\
								    ((FLAG) == CLKTRIM_FLAG_HXTFAULT) ||\
								    ((FLAG) == CLKTRIM_FLAG_PLLFAULT) ||\
								    ((FLAG) == CLKTRIM_FLAG_LIRCFAULT) ||\
								    ((FLAG) == CLKTRIM_FLAG_HIRCFAULT) ||\
								    ((FLAG) == CLKTRIM_FLAG_DET_HXTFAULT))
																	
																	
/* Exported functions --------------------------------------------------------*/ 																
void CLKTRIM_ClkConfig(CLKTRIM_TypeDef* CLKTRIMx, uint32_t Refclk, uint32_t Calclk);
void CLKTRIM_Monitor_StartCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState);
void CLKTRIM_MonitorCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState);
void CLKTRIM_ClkCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState);
void CLKTRIM_SetRefconValue(CLKTRIM_TypeDef* CLKTRIMx, uint32_t Value);
uint32_t CLKTRIM_GetRefValue(CLKTRIM_TypeDef* CLKTRIMx);
uint32_t CLKTRIM_GetCalValue(CLKTRIM_TypeDef* CLKTRIMx);
void CLKTRIM_RST_IE_Config(CLKTRIM_TypeDef* CLKTRIMx, uint32_t rst_select);
FlagStatus CLKTRIM_GetFlagStatus(CLKTRIM_TypeDef* CLKTRIMx, uint16_t CLKTRIM_FLAG);
void ClkTrim_ClearFlagStatus(CLKTRIM_TypeDef* CLKTRIMx, uint16_t CLKTRIM_FLAG);


#ifdef __cplusplus
}
#endif


#endif /* __CPS32K21X_CLKTRIM_H__ */

