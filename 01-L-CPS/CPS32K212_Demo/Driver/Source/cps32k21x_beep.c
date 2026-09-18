/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_beep.h"  
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the BEEP peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void BEEP_DeInit(void)
{
	/* Enable BEEP reset state */
	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BEEP_RST, ENABLE);
	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
	
	/* Release BEEP from reset state */
	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BEEP_RST, DISABLE);  
}

/** 
  * @brief  Set BEEP Clock Prescaler
  * @param  BEEPx: Selects the BEEPx peripheral
  *   This parameter can be one of the following values:
  *       BEEP
  * @param  BeepPrescaler: Selects the BEEP Prescaler
  * @retval None
  */
void BEEP_SetPrescaler(BEEP_TypeDef* BEEPx, uint32_t BeepPrescaler)
{
    /* Check the parameters */
	assert_param(IS_BEEP_ALL_PERIPH(BEEPx));
	assert_param(IS_BEEP_PRESCALER(BeepPrescaler));
	
	/* Set the value to the CSR register */
    BEEPx->CSR &= (uint32_t)(~BEEP_DIV_MASK); 
    
    if (BeepPrescaler > 0xFFFUL)
    {
        BeepPrescaler = 0xFFFUL;
    }
    
	BEEPx->CSR |= BeepPrescaler;
}

/** 
  * @brief  BEEP select prescaler/蜂鸣器输出BEEP_O频率分频选择
  * @param  BEEPx: Selects the BEEPx peripheral
  *   This parameter can be one of the following values:
  *       BEEP
  * @param  ClkDiv:  Selects the BEEPx peripheral output frequency div
  *   This parameter can be one of the following values:
  *     @arg BEEP_O_CLKDIV_DIV8 
  *     @arg BEEP_O_CLKDIV_DIV4  
  *     @arg BEEP_O_CLKDIV_DIV2   
  *     @arg BEEP_O_CLKDIV_DIV2P  
  * @retval None
  */
void BEEP_OutputPrescalerConfig(BEEP_TypeDef* BEEPx, uint32_t ClkDiv)
{
    /* Check the parameters */
	assert_param(IS_BEEP_ALL_PERIPH(BEEPx));
	assert_param(IS_BEEP_O_CLKDIV(ClkDiv));
	
	/* Set the output frequency of BEEP */
    BEEPx->CSR &= (uint32_t)(~BEEP_Out_DIV_MASK); 
	BEEPx->CSR |= ClkDiv;
}

/** 
  * @brief  Enables BEEPx peripheral
  * @param  BEEPx: Selects the BEEPx peripheral
  *   This parameter can be one of the following values:
  *       BEEP
  * @param  NewState: new state of the BEEPx peripheral. 
  *     This parameter can be: ENABLE or DISABLE.
  */
void BEEP_Cmd(BEEP_TypeDef* BEEPx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_BEEP_ALL_PERIPH(BEEPx)); 
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable BEEP function */
		BEEPx->CSR |= BEEP_ENABLE;
	} 
	else 
	{
		/* Disable BEEP function */
		BEEPx->CSR &= (uint32_t)(~BEEP_ENABLE);
	}
}

/** 
  * @brief  BEEP模块时钟源配置
  * @param  BEEPx: Selects the BEEPx peripheral
  *   This parameter can be one of the following values:
  *       BEEP
  * @param  CLKSource: Selects the Clock source of peripheral
  *   This parameter can be one of the following values:
  *     @arg BEEP_CLKSEL_STOP 
  *     @arg BEEP_CLKSEL_LIRC 
  *     @arg BEEP_CLKSEL_HXT   
  *     @arg BEEP_CLKSEL_PCLK  
  * @retval None
  */
void BEEP_ClockSourceConfig(BEEP_TypeDef* BEEPx, uint32_t CLKSource)
{
    /* Check the parameters */
    assert_param(IS_BEEP_ALL_PERIPH(BEEPx)); 
	assert_param(IS_BEEP_CLKSEL(CLKSource));
	
	/* Set Clock  parameters to the CSR register */
	BEEPx->CSR &= (uint32_t)(~BEEP_CLKSEL_MASK);
	BEEPx->CSR |= CLKSource;
}


