/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_AWK_H__    
#define __CPS32K21X_AWK_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
	 
	 
/**
  * @} AWK_InitTypeDef
  */
typedef struct
{
    uint32_t HxtPrsc;        /*!< AWK HXT clock frequency division */   
                                  
    uint32_t ClkSourceSel;   /*!< AWK clock source Selection */

    uint32_t ClkDiv;         /*!< AWK counter clock frequency division Selection */
                                  
}AWK_InitTypeDef;


/** @defgroup TIM_Exported_constants 
  * @{
  */
#define IS_AWK_ALL_PERIPH(PERIPH)   ((PERIPH) == AWK)

#define HXTPRSC_SET_Mask       ((uint32_t)0x0000FF00)
                                      

/** @defgroup AWK clock source Selection
  * @{
  */
#define AWK_CLK_MASK           ((uint32_t)0x00000060)
#define AWK_CLK_STOP           ((uint32_t)0x00000000)   /*!<  AWK时钟停止 */
#define AWK_CLK_LIRC           ((uint32_t)0x00000020)   /*!<  LIRC时钟 */
#define AWK_CLK_HXT            ((uint32_t)0x00000040)   /*!<  HXT分频后的时钟 */
#define AWK_CLK_LXT            ((uint32_t)0x00000060)   /*!<  LXT的时钟 */
#define IS_AWK_SELCLK(CLK)     (((CLK) == AWK_CLK_STOP)||\
                                ((CLK) == AWK_CLK_LIRC)||\
							    ((CLK) == AWK_CLK_HXT) ||\
						        ((CLK) == AWK_CLK_LXT)) 

/** @defgroup AWK_Enable
  * @{
  */
#define AWK_ENABLE          ((uint32_t)0x10)   /*!< AWK模块使能 */
#define AWK_DISABLE         ((uint32_t)0x00)   /*!< AWK模块禁止 */
#define AWK_IT_CLEAR        ((uint32_t)0x01)   /*!< 清除AWK自动唤醒中断 */

#define AWK_IT_AWUF         ((uint32_t)0x01)   /*!< AWK自动唤醒中断标志 */
#define IS_AWK_IT(FLAG)     ((FLAG) == AWK_IT_AWUF)


/** @defgroup AWK counter clock frequency division Selection
  * @{
  */
#define AWK_DIVSEL_Mask        ((uint32_t)0x0000000F) 
#define AWK_DIVSEL_DIV2    	   ((uint32_t)0x00000000)   
#define AWK_DIVSEL_DIV4        ((uint32_t)0x00000001) 
#define AWK_DIVSEL_DIV8        ((uint32_t)0x00000002) 
#define AWK_DIVSEL_DIV16       ((uint32_t)0x00000003) 
#define AWK_DIVSEL_DIV32       ((uint32_t)0x00000004) 
#define AWK_DIVSEL_DIV64       ((uint32_t)0x00000005) 
#define AWK_DIVSEL_DIV128      ((uint32_t)0x00000006) 
#define AWK_DIVSEL_DIV256      ((uint32_t)0x00000007) 
#define AWK_DIVSEL_DIV512      ((uint32_t)0x00000008) 
#define AWK_DIVSEL_DIV1024     ((uint32_t)0x00000009) 
#define AWK_DIVSEL_DIV2048     ((uint32_t)0x0000000A) 
#define AWK_DIVSEL_DIV4096     ((uint32_t)0x0000000B) 
#define AWK_DIVSEL_DIV8192     ((uint32_t)0x0000000C) 
#define AWK_DIVSEL_DIV16384    ((uint32_t)0x0000000D) 
#define AWK_DIVSEL_DIV32768    ((uint32_t)0x0000000E) 
#define AWK_DIVSEL_DIV65536    ((uint32_t)0x0000000F) 

#define IS_AWK_DIVSEL(DIV)     (((DIV) == AWK_DIVSEL_DIV2) ||\
							    ((DIV) == AWK_DIVSEL_DIV4) ||\
                                ((DIV) == AWK_DIVSEL_DIV8) ||\
                                ((DIV) == AWK_DIVSEL_DIV16) ||\
                                ((DIV) == AWK_DIVSEL_DIV32) ||\
                                ((DIV) == AWK_DIVSEL_DIV64) ||\
                                ((DIV) == AWK_DIVSEL_DIV128) ||\
                                ((DIV) == AWK_DIVSEL_DIV256) ||\
                                ((DIV) == AWK_DIVSEL_DIV512) ||\
                                ((DIV) == AWK_DIVSEL_DIV1024) ||\
                                ((DIV) == AWK_DIVSEL_DIV2048) ||\
                                ((DIV) == AWK_DIVSEL_DIV4096) ||\
                                ((DIV) == AWK_DIVSEL_DIV8192) ||\
                                ((DIV) == AWK_DIVSEL_DIV16384) ||\
                                ((DIV) == AWK_DIVSEL_DIV32768) ||\
						        ((DIV) == AWK_DIVSEL_DIV65536)) 
                                

																	
/* Exported functions --------------------------------------------------------*/
void AWK_DeInit(void);
void AWK_Init(AWK_TypeDef *AWKx, AWK_InitTypeDef* AWK_InitStruct);
void AWK_StructInit(AWK_InitTypeDef* AWK_InitStruct);
void AWK_Cmd(AWK_TypeDef *AWKx, FunctionalState NewState);
void AWK_SelClkSource(AWK_TypeDef *AWKx, uint8_t AWKClkSource);
void AWK_SetReLoadValue(AWK_TypeDef *AWKx, uint8_t value);
void AWK_ClearITFlag(AWK_TypeDef *AWKx);
ITStatus AWK_GetITStatus(AWK_TypeDef *AWKx, uint32_t AWK_IT_Flag);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_AWK_H__ */

