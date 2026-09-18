/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_debug.h"



/** 
  * @brief  Deinitializes the DEBUG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DEBUG_DeInit(void)
{
    /* Enable DEBUG reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_DEBUG_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release DEBUG from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_DEBUG_RST, DISABLE);
}

/** 
  * @brief  Enbale or disable TIM2 to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the TIM2 when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_TIM2_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_TIM2_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_TIM2_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable WWDG to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the WWDG when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_WWDG_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_WWDG_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_WWDG_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable IWDG to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the IWDG when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_IWDG_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_IWDG_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_IWDG_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable BEEP to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the BEEP when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_BEEP_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_BEEP_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_BEEP_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable ETIMER to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the ETIMER when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_ETIMER_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_ETIMER_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_ETIMER_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable LPTIM to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the LPTIM when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_LPTIM_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_LPTIM_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_LPTIM_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable TIM11 to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the TIM11 when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_TIM11_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_TIM11_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_TIM11_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}

/** 
  * @brief  Enbale or disable TIM11 to run when the chip enters debug mode
  * @param  DEBUGx: Select the DEBUG Peripheral.
  *   This parameters can be one of the following values: DEBUG
  * @param  NewState: new state of the TIM11 when the chip enters debug mode
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DEBUG_TIM10_Cmd(DEBUG_TypeDef* DEBUGx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(DEBUGx));
	assert_param(IS_FUNCTION_STATE(NewState));

	tmpreg = DEBUGx->APBFZ;

	if (NewState != DISABLE)
	{
	    tmpreg &= (uint32_t)(~DEBUG_TIM10_DBGSTOP);  
	}
	else
	{
	    tmpreg |= DEBUG_TIM10_DBGSTOP;
	}
	
    /* Set the value to the APBFZ register */
	DEBUGx->APBFZ = 0x5A690000 + tmpreg;
}



