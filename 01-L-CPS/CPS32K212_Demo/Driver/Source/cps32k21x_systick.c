/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_systick.h"  
#include "cps32k21x_rcc.h"


__IO uint32_t uwTick = 0;


/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
void HAL_IncTick(void)
{
    uwTick += 1u;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note  This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
uint32_t HAL_GetTick(void)
{
    return uwTick;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(uint32_t Delay)
{
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = Delay;
    
    while ((HAL_GetTick() - tickstart) < wait)
    {
    }
}

/**
  * @brief  Initialize SysTick timer
  * @param  My_SystemCoreClock: system clock frequency
  * @param  TickPriority: Set SysTick timer interrupt priority
  *   This parameter can be one of the following values:
  *     @arg PRIORITY_HIGHEST 
  *     @arg PRIORITY_HIGH  
  *     @arg PRIORITY_LOW   
  *     @arg PRIORITY_LOWEST  
  * @retval The initialize result of the SysTick timer(SUCCESS or ERROR).
  */
ErrorStatus SysTick_Initialize(uint32_t My_SystemCoreClock, uint32_t TickPriority)
{
    /* Configure the SysTick to have interrupt in 1ms time basis*/
    //if (SysTick_Config(My_SystemCoreClock / 1000U / 2) > 0U)    // 0.5ms中断间隔
    if (SysTick_Config(My_SystemCoreClock / 1000U) > 0U)  // 1ms中断间隔
    {
        return ERROR;  
    }
    
    /* Configure the SysTick IRQ priority */
    if (TickPriority < (1UL << __NVIC_PRIO_BITS))
    {
        NVIC_SetPriority(SysTick_IRQn, TickPriority);
    }
    else
    {
        return ERROR;  
    }
    
    return SUCCESS;   // 返回成功
}

