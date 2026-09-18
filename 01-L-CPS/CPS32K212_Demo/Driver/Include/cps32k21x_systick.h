/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_SYSTICK_H__   
#define __CPS32K21X_SYSTICK_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


#define PRIORITY_HIGHEST	 (0U)
#define PRIORITY_HIGH		 (1U)
#define PRIORITY_LOW	     (2U)
#define PRIORITY_LOWEST		 (3U)
#define TICK_INT_PRIORITY    ((uint32_t)PRIORITY_LOWEST)    /*!< tick interrupt priority (lowest by default)  */

	 																						 																							 
/* Exported functions --------------------------------------------------------*/
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
void HAL_Delay(uint32_t Delay);
ErrorStatus SysTick_Initialize(uint32_t My_SystemCoreClock, uint32_t TickPriority);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_SYSTICK_H__*/

