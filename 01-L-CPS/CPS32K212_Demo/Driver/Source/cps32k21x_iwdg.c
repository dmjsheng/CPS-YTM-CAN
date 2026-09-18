/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_iwdg.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  IWDG计数器重装载寄存器设置
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  reloadValue: specifies the IWDG Reload value.
  *          This parameter must be a number between 0 and 0x0FFFFF.
  * @retval None
  */
void IWDG_SetReload(IWDG_TypeDef* IWDGx, uint32_t reloadValue)
{
    /* Check the parameters */
    assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
    assert_param(IS_IWDG_RELOAD(reloadValue));
    
    /* IWDG unlock */
    IWDGx->UNLOCK = IWDG_UNLOCK_CMD;
    
    /* Set the value to the RLOAD Register */
    IWDGx->RLOAD = reloadValue;
    
    /* IWDG Lock */
    IWDGx->UNLOCK = IWDG_LOCK_CMD;
}

/**
  * @brief  配置IWDG工作模式
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  Mode: specifies the IWDG Mode.
  *   This parameter can be one of the following values:
  *     @arg IWDG_MODE_INTERRUPT
  *     @arg IWDG_MODE_RESET
  * @retval None
  */
void IWDG_Mode_Config(IWDG_TypeDef* IWDGx, uint32_t Mode)
{
  	/* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_IWDG_MODE(Mode));
  	
    /* IWDG unlock */
    IWDGx->UNLOCK = IWDG_UNLOCK_CMD;
    
	if (Mode == IWDG_MODE_INTERRUPT)
    {
		IWDGx->CFGR |= IWDG_MODE_INTERRUPT;  // 中断模式
    }
	else if (Mode == IWDG_MODE_RESET)
    {
        IWDGx->CFGR &= (uint32_t)(~IWDG_MODE_INTERRUPT);   // 复位模式
    }
    
    /* IWDG Lock */
    IWDGx->UNLOCK = IWDG_LOCK_CMD;
}

/**
  * @brief  获取IWDG计数器值 
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @retval 返回当前IWDG计数器值
  */
uint32_t IWDG_GetReload(IWDG_TypeDef* IWDGx)
{
    /* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
    
    return (uint32_t)(IWDGx->CNTVAL);
}

/**
  * @brief  IWDG启动命令
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  NewState: IWDG启动状态
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IWDG_Cmd(IWDG_TypeDef* IWDGx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
    	IWDGx->CMDCR = IWDG_RUN_CMD;   // 启动IWDG运行
    }
}

/**
  * @brief  IWDG重装载刷新命令
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  NewState: IWDG重装载刷新状态
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IWDG_Refresh_Cmd(IWDG_TypeDef* IWDGx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
    if (NewState != DISABLE)
    {
    	IWDGx->CMDCR = IWDG_RELOAD_CMD;   // IWDG重装载刷新命令
    }
}

/**
  * @brief  Enables or disables the IWDG interrupt.
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  NewState: new state of the IWDG interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IWDG_ITConfig(IWDG_TypeDef* IWDGx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
    /* IWDG unlock */
    IWDGx->UNLOCK = IWDG_UNLOCK_CMD;
    
    /* Enables the flag of iwdt interrupt */
    if (NewState != DISABLE)
    {
        IWDGx->CFGR &= (uint32_t)(~IWDG_IE_DISABLE);   // 中断使能
    }
    else
    {
        IWDGx->CFGR |= IWDG_IE_DISABLE;  // 中断禁止
    }
    
    /* IWDG Lock */
    IWDGx->UNLOCK = IWDG_LOCK_CMD;
}

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  IWDG_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *    @arg IWDG_IT_FLAG: IWDG Interrupt Flags
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus IWDG_GetFlagStatus(IWDG_TypeDef* IWDGx, uint32_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_IWDG_IT_FLAG(IWDG_FLAG));
	
    if ((IWDGx->SR & IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    
    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Clears the interrupt flag of IWDG
  * @param  IWDGx: Select the IWDGx peripheral. 
  *   This parameter can be one of the following values:
  *   	IWDG
  * @param  IT_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg IWDG_IT_FLAG: IWDG Interrupt Flags
  * @retval None
  */
void IWDG_ClearITFlag(IWDG_TypeDef* IWDGx, uint32_t IT_FLAG)
{
	/* Check the parameters */
	assert_param(IS_IWDG_ALL_PERIPH(IWDGx));
	assert_param(IS_IWDG_IT_FLAG(IT_FLAG));
	
    /* IWDG unlock */
    IWDGx->UNLOCK = IWDG_UNLOCK_CMD;
    
	/* Clears the flag of IWDG */
	IWDGx->INTCLR = IT_FLAG;   // 清中断标志位
    
    /* IWDG Lock */
    IWDGx->UNLOCK = IWDG_LOCK_CMD;
}

