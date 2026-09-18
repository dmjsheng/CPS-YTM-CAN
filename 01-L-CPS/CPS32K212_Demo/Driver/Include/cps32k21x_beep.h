/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_BEEP_H__   
#define __CPS32K21X_BEEP_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"

	 
/* Exported types ------------------------------------------------------------*/
#define IS_BEEP_ALL_PERIPH(PERIPH) 		((PERIPH) == BEEP)

/**
  * @}BEEP MASK
  */
#define BEEP_DIV_MASK     				((uint32_t)0x00000FFF)
#define BEEP_Out_DIV_MASK  			    ((uint32_t)(0x03UL << 16))    /* 蜂鸣器输出分频 */
#define BEEP_CLKSEL_MASK   				((uint32_t)(0x03UL << 20))    /* 蜂鸣器时钟源选择：PCLK */
#define BEEP_ENABLE      				((uint32_t)(0x01UL << 18))    /* 蜂鸣器使能 */

#define IS_BEEP_PRESCALER(PRESCALER)    (((PRESCALER) <= 0xFFF) && ((PRESCALER) >>= 0)) 	 
	 
/**
  * @}BEEP_O_CLKSEL
  */	 
#define BEEP_O_CLKDIV_DIV8       ((uint32_t)0x00)             /* !< 蜂鸣器BEEP_O频率选择:     fbeep/8 */ 
#define BEEP_O_CLKDIV_DIV4       ((uint32_t)(0x01UL << 16))   /* !< 蜂鸣器BEEP_O频率选择:   fbeep/4 */
#define BEEP_O_CLKDIV_DIV2       ((uint32_t)(0x02UL << 16))   /* !< 蜂鸣器BEEP_O频率选择:  fbeep/2 */
#define BEEP_O_CLKDIV_DIV2P      ((uint32_t)(0x03UL << 16))   /* !< 蜂鸣器BEEP_O频率选择:  fbeep/2 */

#define IS_BEEP_O_CLKDIV(DIV)  	 (((DIV) == BEEP_O_CLKDIV_DIV8) ||\
                                  ((DIV) == BEEP_O_CLKDIV_DIV4) ||\
                                  ((DIV) == BEEP_O_CLKDIV_DIV2) ||\
                                  ((DIV) == BEEP_O_CLKDIV_DIV2P))

/**
  * @}BEEP CLK SELECTION
  */
#define BEEP_CLKSEL_STOP         ((uint32_t)0x00)	           /* !< Beep Clock Stop */ 
#define BEEP_CLKSEL_LIRC         ((uint32_t)(0x01UL << 20))	   /* !< Select LIRC Clock */ 
#define BEEP_CLKSEL_HXT          ((uint32_t)(0x02UL << 20))	   /* !< Select HXT Clock */ 
#define BEEP_CLKSEL_PCLK         ((uint32_t)(0x03UL << 20))	   /* !< Select PCLK Clock */ 

#define IS_BEEP_CLKSEL(CLK) 	 (((CLK) == BEEP_CLKSEL_STOP) ||\
                                  ((CLK) == BEEP_CLKSEL_LIRC) ||\
                                  ((CLK) == BEEP_CLKSEL_HXT) ||\
                                  ((CLK) == BEEP_CLKSEL_PCLK))

																							 																							 
/* Exported functions --------------------------------------------------------*/
void BEEP_DeInit(void);
void BEEP_SetPrescaler(BEEP_TypeDef* BEEPx, uint32_t BeepPrescaler);
void BEEP_OutputPrescalerConfig(BEEP_TypeDef* BEEPx, uint32_t ClkDiv);
void BEEP_Cmd(BEEP_TypeDef* BEEPx, FunctionalState NewState);
void BEEP_ClockSourceConfig(BEEP_TypeDef* BEEPx, uint32_t CLKSource);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_BEEP_H__*/



