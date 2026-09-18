/* Define to prevent recursive inclusion -----------*/
#ifndef __CPS32K21X_WWDG_H__
#define __CPS32K21X_WWDG_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


#define IS_WWDG_RLOAD(VALUE)    (((VALUE) >= 0x01) && ((VALUE) <= 0xFF))


/* ---------------------- WWDG_CR registers bit mask ------------------------ */
#define WWDG_EN          		(BIT28)      		   /*!< WWDG使能 */
#define WWDG_PRSC_Mask   		((uint32_t)0xFFFFF)    /*!< WWD预分频掩码 */
#define WWDG_WINCMP_Mask    	((uint32_t)0xFF)       /*!< WWD窗口比较值掩码 */


/* --------------------- WWDG_INTEN registers bit mask ---------------------- */
#define WWDG_IE_ENABLE      	(BIT0)    /*!< WWDG中断使能 */


/* --------------------- WWDG_SR registers bit mask ------------------------- */
#define WWDG_IT_FLAG        	(BIT0)    /*!< WWDG中断标志位 */
#define IS_WWDG_IT_FLAG(FLAG)   ((FLAG) == WWDG_IT_FLAG)   


/* --------------------- WWDG_INTCLR registers bit mask --------------------- */
#define WWDG_ICLR_EN            (BIT0)    /*!< WWDG中断标志清除使能 */


/** @defgroup WWDG_Prescaler 
  * @{
  */
#define IS_WWDG_PRSC(PRSC)    (((PRSC) >= 0) && ((PRSC) <= 0xFFFFF))
                                    																		
																			
/* Exported functions --------------------------------------------------------*/ 																			
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_ITConfig(FunctionalState NewStatus);
void WWDG_SetReLoad(uint8_t ReloadValue);
void WWDG_Cmd(FunctionalState NewStatus);
ITStatus WWDG_GetITStatus(uint16_t WWDG_FLAG);
void WWDG_ClearITFlag(void);
uint8_t WWDG_ReadCounter(void);
uint8_t WWDG_ReadWindowCmpValue(void);


#ifdef __cplusplus
}
#endif


#endif  /*__CPS32K21X_WWDG_H__ */

