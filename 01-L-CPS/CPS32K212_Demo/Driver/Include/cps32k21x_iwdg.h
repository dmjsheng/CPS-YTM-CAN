/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_IWDG_H__   
#define __CPS32K21X_IWDG_H__


#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


/** @defgroup IWDG_Exported_Constants
  * @{
  */ 
#define IS_IWDG_ALL_PERIPH(PERIPH)    ((PERIPH) == IWDG)


/** @defgroup IWDG Access Command define 
  * @{
  */
#define IWDG_UNLOCK_CMD           ((uint32_t)0x55AA6699)  /*!< 解锁命令 */	
#define IWDG_LOCK_CMD             ((uint32_t)0x55AA6698)  /*!< 加锁命令 */	

#define IWDG_RELOAD_CMD           ((uint8_t)0xAA)    /*!< IWDG重装载刷新命令 */	
#define IWDG_RUN_CMD              ((uint8_t)0x55)    /*!< IWDG启动运行命令 */	

#define IWDG_IE_DISABLE           (BIT1)    /*!< 中断禁止 */	
#define IWDG_IE_ENABLE            (0)       /*!< 中断使能 */	

#define IWDG_IT_FLAG              (BIT0)	/*!< 中断溢出标志 */	

#define IS_IWDG_IT_FLAG(FLAG)     ((FLAG) == IWDG_IT_FLAG)

#define IS_IWDG_RELOAD(RELOAD)    ((RELOAD) <= ((uint32_t)0x000FFFFF))

#define IWDG_MODE_INTERRUPT       (BIT0)    /*!< 中断模式 */	
#define IWDG_MODE_RESET           (0)       /*!< 复位模式 */	
#define IS_IWDG_MODE(MODE)        (((MODE) == IWDG_MODE_INTERRUPT) ||\
                                   ((MODE) == IWDG_MODE_RESET))


/* Exported functions --------------------------------------------------------*/
void IWDG_SetReload(IWDG_TypeDef* IWDGx, uint32_t reloadValue);
void IWDG_Mode_Config(IWDG_TypeDef* IWDGx, uint32_t Mode);
uint32_t IWDG_GetReload(IWDG_TypeDef* IWDGx);
void IWDG_Cmd(IWDG_TypeDef* IWDGx, FunctionalState NewState);
void IWDG_Refresh_Cmd(IWDG_TypeDef* IWDGx, FunctionalState NewState);
void IWDG_ITConfig(IWDG_TypeDef* IWDGx, FunctionalState NewState);
FlagStatus IWDG_GetFlagStatus(IWDG_TypeDef* IWDGx, uint32_t IWDG_FLAG);
void IWDG_ClearITFlag(IWDG_TypeDef* IWDGx, uint32_t IT_FLAG);


#ifdef __cplusplus
}
#endif


#endif /* __CPS32K21X_IWDG_H__ */

