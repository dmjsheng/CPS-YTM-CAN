/* Includes ------------------------------------------------------------------*/
#include  "cps32k21x_clktrim.h"   


/** 
  * @brief  配置参考时钟和待校准时钟
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  Refclk: Reference clock source
  *    This parameters can be one of the following values:
  *    	@arg REFCLK_HIRC
  *    	@arg REFCLK_HXT
  *    	@arg REFCLK_LIRC
  *    	@arg REFCLK_EXT_CLK_IN
  *    	@arg REFCLK_PLL
  * @param  Calclk: Calibration clock source
  *    This parameters can be one of the following values:
  *    	@arg CALCLK_HIRC
  *    	@arg CALCLK_HXT
  *    	@arg CALCLK_LIRC
  *    	@arg CALCLK_PLL
  * @retval None
  */
void CLKTRIM_ClkConfig(CLKTRIM_TypeDef* CLKTRIMx, uint32_t Refclk, uint32_t Calclk)
{
    uint32_t tmpreg = 0;
	
	/* Check the parameters */
	assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
	assert_param(IS_REFCLK_SEL(Refclk));
	assert_param(IS_CALCLK_SEL(Calclk));
	
	tmpreg = CLKTRIMx->CR;  
	
	/* Set Reference clock */
	tmpreg &= (uint32_t)(~REFCLK_Mask);
	tmpreg |= (uint32_t)Refclk;
	
	/* Set Calibration clock */
	tmpreg &= (uint32_t)(~CALCLK_Mask);
	tmpreg |= (uint32_t)Calclk;
	
	/* Set value to CR register */
	CLKTRIMx->CR = tmpreg;
}

/** 
  * @brief  软监测开始使能/禁止
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  NewState: 软监测开始状态
  *    This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void CLKTRIM_Monitor_StartCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable software monitor start control */
        CLKTRIMx->CR |= CLKTRIM_TRIM_START;
    }
    else
    {
        /* Disable software monitor start control */
        CLKTRIMx->CR &= (uint32_t)(~CLKTRIM_TRIM_START);
    }
}

/** 
  * @brief  Enable or disable clock monitor function
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  NewState: new state of the clock monitor function. 
  *    This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
void CLKTRIM_MonitorCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the monitor function */
        CLKTRIMx->CR |= CLKTRIM_MON_ENABLE;
    }
    else
    {
        /* Disable the monitor function */
        CLKTRIMx->CR &= (uint32_t)(~CLKTRIM_MON_ENABLE);
    }
}

/** 
  * @brief  使能/禁止参考时钟及校准时钟
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  NewState: 参考时钟及校准时钟的使能状态
  *    This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */ 
void CLKTRIM_ClkCmd(CLKTRIM_TypeDef* CLKTRIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
    if (NewState != DISABLE)
    {
        CLKTRIMx->CR |= REFCALCLK_ENABLE;  // 参考时钟及校准时钟使能
    }
    else
    {
        CLKTRIMx->CR &= (uint32_t)(~REFCALCLK_ENABLE);  // 参考时钟及校准时钟禁止
    }
}

/** 
  * @brief  设置参考计数器初始值
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  Value: 参考计数器初始值
  * @retval None
  */ 
void CLKTRIM_SetRefconValue(CLKTRIM_TypeDef* CLKTRIMx, uint32_t Value)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_CLKTRIM_REFCON_VALUE(Value));

    /* Set value to REFCON register */
    CLKTRIMx->REFCON = Value;
}

/** 
  * @brief  读取参考计数器值 
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @retval 参考计数器的值
  */ 
uint32_t CLKTRIM_GetRefValue(CLKTRIM_TypeDef* CLKTRIMx)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));

    /* Return clktrim refcnt value */
    return (CLKTRIMx->REFCNT);
}

/** 
  * @brief  读取校准计数器值
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  * @param  NewState: new state of the CLKTRIM peripheral. 
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @retval 校准计数器的值
  */ 
uint32_t CLKTRIM_GetCalValue(CLKTRIM_TypeDef* CLKTRIMx)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));

    /* Return clktrim Calibration value */
    return (CLKTRIMx->CALCNT);
}

/** 
  * @brief  CLKTRIM模块复位及中断方式配置
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  rst_select: 发生停振检知时复位或中断方式选择 
  *    This parameter can be one of the following values:
  *		@arg CLKTRIM_SEL_INTERRUPT  
  *		@arg CLKTRIM_SEL_RESET      
  * @retval None
  */ 
void CLKTRIM_RST_IE_Config(CLKTRIM_TypeDef* CLKTRIMx, uint32_t rst_select)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));

	if (rst_select == CLKTRIM_SEL_RESET)
	{
		CLKTRIMx->CR |= CLKTRIM_SEL_RESET;   // 发生停振检知时产生复位
	}
	else if (rst_select == CLKTRIM_SEL_INTERRUPT)
	{
		CLKTRIMx->CR &= (uint32_t)(~CLKTRIM_SEL_RESET);  // 发生停振检知时产生中断
	}
}

/** 
  * @brief  Gets CLKTRIM interrupt flag status
  * @param  CLKTRIMx: Select the CLKTRIM peripheral.
  *    This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  CLKTRIM_FLAG: CLKTRIMx interruption of flag   
  *    This parameter can be one of the following values:
  *		 @arg CLKTRIM_FLAG_REFCNTSTOP       
  *		 @arg CLKTRIM_FLAG_CALCNTOVF   
  *		 @arg CLKTRIM_FLAG_HXTFAULT   
  *		 @arg CLKTRIM_FLAG_PLLFAULT    
  *		 @arg CLKTRIM_FLAG_LIRCFAULT   
  *		 @arg CLKTRIM_FLAG_HIRCFAULT   
  *		 @arg CLKTRIM_FLAG_DET_HXTFAULT   
  * @retval The new state of CLKTRIM_FLAG (SET or RESET).
  *    This parameter can be one of the following values:
  *      @arg SET
  *      @arg RESET
  */ 
FlagStatus CLKTRIM_GetFlagStatus(CLKTRIM_TypeDef* CLKTRIMx, uint16_t CLKTRIM_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_CLKTRIM_FLAG(CLKTRIM_FLAG));
	
    /* Get flag status */
    if ((CLKTRIMx->IFR & CLKTRIM_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/** 
  * @brief  Clear the interrupt flag
  * @param  CLKTRIMx: Set the CLKTRIM peripheral.
  *   This parameter can be one of the following values: 
  *       CLKTRIM
  * @param  CLKTRIM_FLAG: CLKTRIMx interruption of flag 
  *   This parameter can be one of the following values:
  *		@arg CLKTRIM_FLAG_HXTFAULT   
  *		@arg CLKTRIM_FLAG_PLLFAULT    
  *		@arg CLKTRIM_FLAG_LIRCFAULT   
  *		@arg CLKTRIM_FLAG_HIRCFAULT   
  *		@arg CLKTRIM_FLAG_DET_HXTFAULT 
  *		@arg CLKTRIM_FLAG_ALL 
  * @retval None
  */
void ClkTrim_ClearFlagStatus(CLKTRIM_TypeDef* CLKTRIMx, uint16_t CLKTRIM_FLAG)
{
    /* Check the parameters */
    assert_param(IS_CLKTRIM_ALL_PERIPH(CLKTRIMx));
    assert_param(IS_CLKTRIM_FLAG(CLKTRIM_FLAG));

    /* clear clktrim interrupt flag */
    CLKTRIMx->ICLR = CLKTRIM_FLAG;
}


