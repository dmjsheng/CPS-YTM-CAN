/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_wwdg.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
	/*Enable CRC reset state */
	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_WWDG_RST, ENABLE);
	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
	
	/*Release CRC from reset state */
	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_WWDG_RST, DISABLE);  
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  Prescaler: specifies the WWDG Prescaler. 
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t Prescaler)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_WWDG_PRSC(Prescaler));
    
    /* Read WWDG_CR register */
    tmpreg  = WWDG->CR;

    tmpreg &= (uint32_t)(~(WWDG_PRSC_Mask << 8));
    
    /* Set WWWDG Prescaler value */
    tmpreg |= (uint32_t)(Prescaler << 8);
    
    /* Store the new value */
    WWDG->CR = tmpreg;
}

/**
  * @brief  Sets the WWDG window compare value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
    uint32_t tmpreg = 0;

    /* Read WWDG_CR register */
    tmpreg  = WWDG->CR;
    
    tmpreg &= (uint32_t)(~WWDG_WINCMP_Mask);

    /* Set Window compare Value value */
    tmpreg |= (uint32_t)WindowValue;

    /* Store the new value */
    WWDG->CR = tmpreg;
}

/**
  * @brief  Enable or disable the WWDG interrupt.
  * @param  NewState: new state of the WWDG interrupt. 
  * 	This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_ITConfig(FunctionalState NewStatus)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewStatus));
	
	if (NewStatus != DISABLE)
    {
		/* Enables the WWDG interrupt */
		WWDG->INTEN |=  WWDG_IE_ENABLE;
    }
	else
    {
		/* Disable the WWDG interrupt */
		WWDG->INTEN &= (uint32_t)(~WWDG_IE_ENABLE);
    }
}

/**
  * @brief  Sets the WWDG reload counter value.
  * @param  ReloadValue: specifies the WWDG reload counter value.
  * @retval None
  */
void WWDG_SetReLoad(uint8_t ReloadValue)
{
    /* Check the parameters */
	assert_param(IS_WWDG_RLOAD(ReloadValue));
    
    /* set the vlaue to the RLDCNT*/
    WWDG->RLOAD = ((uint32_t)ReloadValue) & ((uint32_t)0xFF);
}

/**
  * @brief  Enable or disable WWDG counter function.                  
  * @param  NewState: new state of the WWDG peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_Cmd(FunctionalState NewStatus)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewStatus));
    
    if (NewStatus != DISABLE)
    {
        WWDG->CR |= WWDG_EN;   // WWDG使能
    }
    else
    {
        WWDG->CR &= (uint32_t)(~WWDG_EN);  // WWDG禁止
    }
}

/**
  * @brief  Checks whether the specified WWDG interrupt has occurred or not.
  * @param  WWDG_FLAG: specifies the WWDG FLAG to check. 
  * This parameter can be one of the following values:
  *     @arg  WWDG_IT_FLAG
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
ITStatus WWDG_GetITStatus(uint16_t WWDG_FLAG)
{
    ITStatus bitstatus = RESET;

	/* Check the parameters */
	assert_param(IS_WWDG_IT_FLAG(WWDG_FLAG));
	
    if (((WWDG->SR) & WWDG_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the WWDG's interrupt pending bits.
  * @param  None
  * @retval None
  */
void WWDG_ClearITFlag(void)
{
    /* Clear the interrupt flag */
    WWDG->INTCLR = WWDG_IT_FLAG;
}

/**
  * @brief  读取WWDG看门狗计数器当前值
  * @param  None
  * @retval None
  */
uint8_t WWDG_ReadCounter(void)
{
	return ((uint8_t)WWDG->CNTVAL);
}

/**
  * @brief  读取WWDG看门狗窗口比较值
  * @param  None
  * @retval None
  */
uint8_t WWDG_ReadWindowCmpValue(void)
{
	return ((uint8_t)(WWDG->CR & ((uint32_t)0xFF)));
}


