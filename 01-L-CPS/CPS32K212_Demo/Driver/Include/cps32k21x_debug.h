/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_DEBUG_H__   
#define __CPS32K21X_DEBUG_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


#define DEBUG_TIM2_DBGSTOP      (BIT11)    /*<! Debug模式下TIM2停止工作 */
#define DEBUG_WWDG_DBGSTOP      (BIT10)    /*<! Debug模式下WWDG停止工作 */
#define DEBUG_IWDG_DBGSTOP      (BIT9)     /*<! Debug模式下IWDG停止工作 */
#define DEBUG_BEEP_DBGSTOP      (BIT8)     /*<! Debug模式下BEEP停止工作 */
#define DEBUG_AWK_DBGSTOP       (BIT7)     /*<! Debug模式下AWK停止工作 */
#define DEBUG_ETIMER_DBGSTOP    (BIT5)     /*<! Debug模式下ETIMER停止工作 */
#define DEBUG_LPTIM_DBGSTOP     (BIT2)     /*<! Debug模式下LPTIM停止工作 */
#define DEBUG_TIM11_DBGSTOP     (BIT1)     /*<! Debug模式下TIM11停止工作 */
#define DEBUG_TIM10_DBGSTOP     (BIT0)     /*<! Debug模式下TIM10停止工作 */

	 
/* Exported functions --------------------------------------------------------*/
void DEBUG_DeInit(void);
void DEBUG_TIM2_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_WWDG_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_IWDG_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_BEEP_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_ETIMER_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_LPTIM_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_TIM11_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);
void DEBUG_TIM10_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState);


#ifdef __cplusplus
}
#endif


#endif /*__CPS32K21X_DEBUG_H__ */


