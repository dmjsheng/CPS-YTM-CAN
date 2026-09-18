/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_awk.h"   
#include "cps32k21x_rcc.h"


/** 
  * @brief  Deinitializes the AWK peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void AWK_DeInit(void)
{
    /* Enable AWK reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_AWK_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /*Release AWK from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_AWK_RST, DISABLE);
}

/**
  * @brief  Initializes the AWKx peripheral according to the specified
  *         parameters in the AWK_InitStruct.
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK.
  * @param  AWK_InitStruct: pointer to a AWK_InitTypeDef structure which will
  *         be initialized.       
  * @retval None
  */
void AWK_Init(AWK_TypeDef *AWKx, AWK_InitTypeDef* AWK_InitStruct)
{
	uint32_t tmpawkcr = 0;
	
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
    assert_param(IS_AWK_SELCLK(AWK_InitStruct->ClkSourceSel));
	assert_param(IS_AWK_DIVSEL(AWK_InitStruct->ClkDiv));
	
	/* read the value of CR */
	tmpawkcr = AWKx->CR;
	
	/* Clear the function bits to zero */
	tmpawkcr &= (uint32_t)(~AWK_ENABLE);
	tmpawkcr &= (uint32_t)(~AWK_CLK_MASK);
    tmpawkcr &= (uint32_t)(~AWK_DIVSEL_Mask);
	tmpawkcr &= (uint32_t)(~HXTPRSC_SET_Mask);
	
	/*-------------------------- AWK CR Configuration ------------------------*/
	tmpawkcr |= (uint32_t)(((AWK_InitStruct->HxtPrsc) << 8) |\
	                       (AWK_InitStruct->ClkSourceSel) |\
	                       (AWK_InitStruct->ClkDiv));
	
	/* set the value to CR register */
	AWKx->CR = tmpawkcr;
}

/** 
  * @brief  Fills each AWK_InitTypeDef member with its default value.
  * @param  AWK_InitStruct : pointer to a AWK_InitTypeDef structure which will be initialized.
  * @retval None
  */
void AWK_StructInit(AWK_InitTypeDef* AWK_InitStruct)
{
    AWK_InitStruct->ClkDiv = AWK_DIVSEL_DIV2;   // 默认2分频
    AWK_InitStruct->ClkSourceSel = AWK_CLK_STOP;   // AWK时钟源停止
    AWK_InitStruct->HxtPrsc = (uint32_t)0xBC00;
}


/**
  * @brief  Enables or disables the specified AWKx peripheral function.
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK.
  * @param  NewState: new state of the AWKx peripheral.
  *     This parameter can be: ENABLE or DISABLE.     
  * @retval None
  */
void AWK_Cmd(AWK_TypeDef *AWKx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
        /* Enable the AWK peripheral */
        AWKx->CR |= AWK_ENABLE;
    }
	else
    {
        /* Disalbe the AWK peripheral */
        AWKx->CR &= (uint32_t)(~AWK_ENABLE);
    }
}

/**
  * @brief  Set the clock source of the AWKx
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK.
  * @param  AWKClkSource: specifies the clock source used as AWKx clock.
  *   This parameter can be one of the following values:
  *     @arg AWK_CLK_STOP
  *     @arg AWK_CLK_LIRC
  *     @arg AWK_CLK_HXT
  *     @arg AWK_CLK_LXT 
  * @retval None
  */
void AWK_SelClkSource(AWK_TypeDef *AWKx, uint8_t AWKClkSource)
{
	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
	assert_param(IS_AWK_SELCLK(AWKClkSource));
	
	/* Select the AWK clock source */
	AWKx->CR &= (uint32_t)(~AWK_CLK_MASK);
	AWKx->CR |=  AWKClkSource;
}

/**
  * @brief  设置AWK自动唤醒重装载寄存器值
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK.
  * @param  value: 自动唤醒重装载寄存器设定值       
  * @retval None
  */
void AWK_SetReLoadValue(AWK_TypeDef *AWKx, uint8_t value)
{
    /* Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));
    
    /* Set the value to the register of RLDVAL */
    AWKx->RLOAD = value;
}

/**
  * @brief  Clear the AWKx interrupt Flag 
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK.     
  * @retval None
  */
void AWK_ClearITFlag(AWK_TypeDef *AWKx)
{
    /* Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));
    
    /* Clear the AWK interrupt Flag */
    AWKx->INTCLR = AWK_IT_CLEAR;
}

/**
  * @brief  获取AWKx自动唤醒中断标志位状态
  * @param  AWKx: selects the AWKx peripheral
  * 	This parameter can be one of the following values: AWK. 
  * @param  AWK_IT_Flag: AWKx自动唤醒中断标志
  * 	This parameter can be one of the following values: 
  *     	@arg AWK_IT_AWUF
  * @retval  The new state of AWK_IT_AWUF (SET or RESET). 
  */
ITStatus AWK_GetITStatus(AWK_TypeDef *AWKx, uint32_t AWK_IT_Flag)
{
    ITStatus bitstatus = RESET;  

	/* Check the parameters */
	assert_param(IS_AWK_ALL_PERIPH(AWKx));
    assert_param(IS_AWK_IT(AWK_IT_Flag));
	

	if ((AWKx->SR & AWK_IT_Flag) != 0)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	
	return bitstatus;
}



