/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_rcc.h"


/** 
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
	/* Close AHB Clock */
	RCC->HCLKEN &= ~RCC_AHB_CLKMASK;
	
	/* Close APB Clock */
	RCC->PCLKEN &= ~RCC_APB_CLKMASK;
}

/** 
  * @brief  Waits for HIRC Stable.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HIRC oscillator is stable and ready to use
  * - ERROR: HIRC oscillator not yet ready
  */
ErrorStatus RCC_WaitForHIRCStable(RCC_TypeDef *RCCx)
{
    __IO uint32_t StartUpCounter = 0;
    uint32_t HIRCStatus = 0;
    ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));

    /* Wait till HIRC Ready or timeout */
    do
    {
        HIRCStatus = RCCx->HIRCCR & RCC_FLAG_HIRCRDY;
        StartUpCounter++;  
    } while ((StartUpCounter < 0xFFFFFFFFUL) && (HIRCStatus != RCC_FLAG_HIRCRDY));
  
    if (HIRCStatus == RCC_FLAG_HIRCRDY)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }  
    return (status);
}

/** 
  * @brief  Waits for HXT Stable.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  PERIOD: the time of HXT stable   
  *   This parameter can be one of the following values:
  *     @arg RCC_HXT_STARTUP_PERIOD_1024
  *     @arg RCC_HXT_STARTUP_PERIOD_2048
  *     @arg RCC_HXT_STARTUP_PERIOD_4096
  *     @arg RCC_HXT_STARTUP_PERIOD_16384
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HXT oscillator is stable and ready to use
  * - ERROR: HXT oscillator not yet ready
  */
ErrorStatus RCC_WaitForHXTStable(RCC_TypeDef *RCCx, uint32_t PERIOD)
{
    __IO uint32_t StartUpCounter = 0;
    uint32_t HXTStatus = 0;
    uint32_t tempreg = 0;
    ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_HXT_STARTUP_PERIOD(PERIOD));
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
	/* Set HXT STARTUP period value */
	tempreg  =  RCCx->HXTCR;
	tempreg &= ~(uint32_t)RCC_HXT_STARTUP_MASK;
	tempreg |=  (uint32_t)(PERIOD << 4);
	RCCx->HXTCR = 0x5A690000 + tempreg;
	
    /* Wait till HXT STABLE or timeout */
    do
    {
        HXTStatus = RCCx->HXTCR & RCC_FLAG_HXTRDY;
        StartUpCounter++;  
    } while ((StartUpCounter < 0xFFFFFFFFUL) && (HXTStatus != RCC_FLAG_HXTRDY));
  
    if (HXTStatus == RCC_FLAG_HXTRDY)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }  
	
    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;
    
    return (status);
}

/** 
  * @brief  Waits for LIRC Stable.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  PERIOD: the time of LIRC stable    
  *   This parameter can be one of the following values:
  *     @arg RCC_LIRC_STARTUP_PERIOD_4
  *     @arg RCC_LIRC_STARTUP_PERIOD_16
  *     @arg RCC_LIRC_STARTUP_PERIOD_64
  *     @arg RCC_LIRC_STARTUP_PERIOD_256
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: LIRC oscillator is stable and ready to use
  * - ERROR: LIRC oscillator not yet ready
  */
ErrorStatus RCC_WaitForLIRCStable(RCC_TypeDef *RCCx, uint32_t PERIOD)
{
    __IO uint32_t StartUpCounter = 0;
    uint32_t LIRCStatus = 0;
    uint32_t tempreg = 0;
    ErrorStatus status = ERROR;
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_LIRC_STARTUP_PERIOD(PERIOD));
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
	/* Set LIRC STARTUP */
	tempreg  =  RCCx->LIRCCR;
	tempreg &= ~(uint32_t)RCC_LIRC_STARTUP_MASK;
	tempreg |=  (uint32_t)(PERIOD << 10);
	RCCx->LIRCCR = 0x5A690000 + tempreg;
	
    /* Wait till LIRC STABLE or timeout*/
    do
    {
        LIRCStatus = RCCx->LIRCCR & RCC_FLAG_LIRCRDY;
        StartUpCounter++;  
    } while ((StartUpCounter < HXT_STABLE_TIMEOUT) && (LIRCStatus != RCC_FLAG_LIRCRDY));
  
    if (LIRCStatus == RCC_FLAG_LIRCRDY)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }  
	
    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;
    
    return (status);
}

/** 
  * @brief  Fills each HXT_InitTypeDef member with its default value.
  * @param  HXT_InitStruct : pointer to a HXT_InitTypeDef structure which will be initialized.
  * @retval None
  */
void RCC_HXT_InitStruct(HXT_InitTypeDef * HXT_InitStruct)
{
	HXT_InitStruct->HXTBYP = DISABLE;
	HXT_InitStruct->HXTEN  = DISABLE;
	HXT_InitStruct->HXTPORT = 0;
	HXT_InitStruct->HXTSTARTUP = RCC_HXT_STARTUP_PERIOD_4096;
}

/** 
  * @brief  Initialize HXT module
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  HXT_InitStruct: pointer to a HXT_InitTypeDef structure which will be used.
  * @retval None
  */
void RCC_HXT_Init(RCC_TypeDef *RCCx, HXT_InitTypeDef *HXT_InitStruct)
{
	uint32_t tempreg = 0;

    /* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));

	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

	tempreg  =  RCCx->HXTCR;
	tempreg &= ~(uint32_t)RCC_HXT_STARTUP_MASK;
	tempreg |=  (uint32_t)(HXT_InitStruct->HXTSTARTUP << 4);
	RCCx->HXTCR = 0x5A690000 + tempreg;   // Write RCC_HXTCR register
	
	tempreg = RCCx->SYSCLKCR;
	
	if (HXT_InitStruct->HXTBYP == ENABLE)   // HXT振荡器内部是否旁路？
	{
		tempreg |=  RCC_HXT_BYP_ENABLE;
	}
	else
	{
		tempreg &= ~(uint32_t)RCC_HXT_BYP_ENABLE;
	}

	if (HXT_InitStruct->HXTPORT == RCC_HXT_PORT_OSC)
	{
		tempreg |=  RCC_HXT_PORT_OSC;  // HXT端口
	}
	else
	{
		tempreg &= ~(uint32_t)RCC_HXT_PORT_OSC;  // GPIO口
	}

	if (HXT_InitStruct->HXTEN == ENABLE)
	{
		tempreg |=  RCC_HXT_ENABLE;
	}
	else
	{
		tempreg &= ~(uint32_t)RCC_HXT_ENABLE;
	}

	RCCx->SYSCLKCR = 0x5A690000 + tempreg;
	
	/* Open the lock of register */
    RCCx->UNLOCK = 0x5A690000 + tempreg;
}

/** 
  * @brief  Set the port of HXT 
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  NewState: new state of the HXT port. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_SetHXTPort(RCC_TypeDef *RCCx, FunctionalState NewState)
{
	uint32_t tempreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

	tempreg = RCCx->SYSCLKCR;
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
	if (NewState != DISABLE)
    {
		/* HXT Port Configure to Analog function */
		tempreg |=  RCC_HXT_PORT_OSC;   

		/* HXT内部振荡模块未被旁路， 与OSC_IN/OSC_OUT相连 */
		tempreg &= ~(uint32_t)RCC_HXT_BYP_ENABLE;
    }
	else
    {
		/* Config to the GPIO port */
		tempreg &= ~(uint32_t)RCC_HXT_PORT_OSC;
    }

	RCCx->SYSCLKCR = 0x5A690000 + tempreg;
	
	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}


/** 
  * @brief  Set M0 IRQ Latency/设置中断延时控制
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  IRQLATENCY: The value of IRQ LATENCY
  * @retval None
  */
void RCC_SetM0IRQLatency(RCC_TypeDef *RCCx, uint32_t IRQLATENCY)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));

    /* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

    /* Set value to IRQ latency register */
    RCCx->IRQLATENCY = IRQLATENCY;

    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  config system tick timer
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  SKEW: This parameter can be: 0 or 1.
  * @param  TICKTIMERSTCALIB: 
  * @retval None
  */
void RCC_SystemTickTimerConfig(RCC_TypeDef *RCCx, uint8_t SKEW, uint32_t TICKTIMERSTCALIB)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));

    /* Set the value to STCALIB register */
    RCCx->STICKCR &= ~(uint32_t)RCC_SYSTEMTICKTIMER_STCALIB_MASK;
    RCCx->STICKCR |=  (uint32_t)(SKEW << 24);
    RCCx->STICKCR |=  TICKTIMERSTCALIB;
}

/** 
  * @brief  Enables system tick timer core ref clock 
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  NewState: new state of core ref clock. 
  *   This parameter can be: ENABLE or DISABLE.
  *     ENABLE : 使用内核时钟
  *     DISABLE ：使用HCLK/4时钟
  * @retval None
  */
void RCC_SetSysTickRefClockCmd(RCC_TypeDef *RCCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    RCCx->STICKCR &= ~RCC_SYSTEMTICKTIMER_REFCORE_CLOCK;
	
    if (NewState != DISABLE)
    {
        /* Use core clock */
        RCCx->STICKCR |=  RCC_SYSTEMTICKTIMER_REFCORE_CLOCK; 
    }
    else
    {
        /* Use HCLK/4 clock */
        RCCx->STICKCR &= ~(uint32_t)RCC_SYSTEMTICKTIMER_REFCORE_CLOCK; 
    }
}

/** 
  * @brief  Enables/Disable the clock .
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_CLKType: specifies the clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLKType_HIRC
  *     @arg RCC_CLKType_HXT
  *     @arg RCC_CLKType_LIRC
  *     @arg RCC_CLKType_PLL
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClkCmd(RCC_TypeDef *RCCx, uint32_t RCC_CLKType, FunctionalState NewState)
{
    uint32_t tmpSYSCLKCR = 0;
    uint32_t tmpPLLCR = 0;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_CLK_TYPE(RCC_CLKType));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    tmpSYSCLKCR = RCCx->SYSCLKCR;   
    tmpPLLCR = RCCx->PLLCR;     

	if (RCC_CLKType == RCC_CLKType_HIRC)  
	{
		if (NewState != DISABLE)
        {
            tmpSYSCLKCR |=  RCC_CLKType_HIRC_EN;   
        }
		else
        {
            tmpSYSCLKCR &= ~(uint32_t)RCC_CLKType_HIRC_EN;
        }
	}
	else if (RCC_CLKType == RCC_CLKType_HXT)
	{
        if (NewState != DISABLE)
        {
            tmpSYSCLKCR |=  RCC_CLKType_HXT_EN;   
        }
        else
        {
            tmpSYSCLKCR &= ~(uint32_t)RCC_CLKType_HXT_EN;
        }
	}
    else if (RCC_CLKType == RCC_CLKType_LIRC)
    {
		if (NewState != DISABLE)
        {
            tmpSYSCLKCR |=  RCC_CLKType_LIRC_EN; 
        }
		else
        {
            tmpSYSCLKCR &= ~(uint32_t)RCC_CLKType_LIRC_EN;
        }
	}
	else if (RCC_CLKType == RCC_CLKType_PLL)
	{
        if (NewState != DISABLE)
        {
            tmpPLLCR &= ~(uint32_t)RCC_CLKType_PLL_EN;  // PLL工作
        }
        else
        {
            tmpPLLCR |=  RCC_CLKType_PLL_EN;  // PLL睡眠
        }
	} 
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
	/* set register */
	RCCx->SYSCLKCR = 0x5A690000 + tmpSYSCLKCR;
	RCCx->PLLCR = tmpPLLCR;
	
	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Selects the system clock (SYSCLK).
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *  This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSource_HIRC
  *     @arg RCC_SYSCLKSource_HXT
  *     @arg RCC_SYSCLKSource_PLL
  *     @arg RCC_SYSCLKSource_LIRC
  * @retval None
  */
void RCC_SelSysclk(RCC_TypeDef *RCCx, uint32_t RCC_SYSCLKSource)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

    /* RCC_SYSCLKSource value */
    tmpreg = RCC_SYSCLKSource;
    
    /* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
    /* set clock source */
    RCCx->SYSCLKSEL = 0x5A690000 + tmpreg;
    
    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Configures the clock output source function
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *  This parameter can be one of the following values:
  *     @arg RCC_MCO_SOURCE_SEL_HIRC
  *     @arg RCC_MCO_SOURCE_SEL_HXT
  *     @arg RCC_MCO_SOURCE_SEL_LIRC
  *     @arg RCC_MCO_SOURCE_SEL_SYSCLK
  *     @arg RCC_MCO_SOURCE_SEL_FCLK
  *     @arg RCC_MCO_SOURCE_SEL_PLL
  * @retval None
  */
void RCC_ClkOutputSourceConfig(RCC_TypeDef *RCCx, uint32_t RCC_SYSCLKOutSource)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_MCO_SOURCE_SEL(RCC_SYSCLKOutSource));
    
    tmpreg = RCCx->MCOCR;
    
    /* RCC_SYSCLKSource value */
    tmpreg &= ~(uint32_t)RCC_MCO_SOURCE_SEL_MASK;
    tmpreg |=  (uint32_t)(RCC_SYSCLKOutSource << 8);
    
    /* set clock source */
    RCCx->MCOCR |= tmpreg;
}

/** 
  * @brief  Enable or Disable the function of mco clock output 
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  NewState: new state of the mco clock output. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClkOutputCmd(RCC_TypeDef *RCCx, FunctionalState NewState)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    /* read MCOCR */
    tmpreg = RCCx->MCOCR;
    
    if (NewState != DISABLE)
    {
        tmpreg |=  RCC_MCO_OUTPUT_ENABLE;
    } 
    else 
    {
        tmpreg &= ~(uint32_t)RCC_MCO_OUTPUT_ENABLE;
    }
    
	/* set clock source */
	RCCx->MCOCR |= tmpreg;
}

/** 
  * @brief  Configures the FCLK output clock division frequery
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_SYSCLKSource_DIV: Set clock division parameters
  *  This parameter can be one of the following values:
  *     @arg RCC_FCLK_O_CLK_DIV1:    FCLK_O clock = FCLK clock
        @arg RCC_FCLK_O_CLK_DIV2:    FCLK / 2
        @arg RCC_FCLK_O_CLK_DIV4:    FCLK / 4
        @arg RCC_FCLK_O_CLK_DIV6:    FCLK / 6
        @arg RCC_FCLK_O_CLK_DIV8:    FCLK / 8
        @arg RCC_FCLK_O_CLK_DIV10:   FCLK / 10
        @arg RCC_FCLK_O_CLK_DIV12:   FCLK / 12
        @arg RCC_FCLK_O_CLK_DIV14:   FCLK / 14
        @arg RCC_FCLK_O_CLK_DIV16:   FCLK / 16
        @arg RCC_FCLK_O_CLK_DIV18:   FCLK / 18
        @arg RCC_FCLK_O_CLK_DIV20:   FCLK / 20
        @arg RCC_FCLK_O_CLK_DIV22:   FCLK / 22
        @arg RCC_FCLK_O_CLK_DIV24:   FCLK / 24
        @arg RCC_FCLK_O_CLK_DIV26:   FCLK / 26
        @arg RCC_FCLK_O_CLK_DIV28:   FCLK / 28
        @arg RCC_FCLK_O_CLK_DIV30:   FCLK / 30
		@arg RCC_FCLK_O_CLK_DIV32:   FCLK / 32
  * @retval None
  */
void RCC_ClkFclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_FCLK_O_CLK_DIV)
{
    uint32_t tmpreg = 0;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_FCLK_DIV(RCC_FCLK_O_CLK_DIV));
    
    /* read MCOCR */
    tmpreg = RCCx->MCOCR;
    
    /* set fclk div */
    tmpreg &= ~(uint32_t)RCC_FCLK_DIV_MASK;
    tmpreg |=  RCC_FCLK_O_CLK_DIV;
    
    /* set fclk value */
    RCCx->MCOCR = tmpreg;
}

/** 
  * @brief  Returns the clock source used as system clock.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @retval the value of SYSCLKSEL register
  */
uint8_t RCC_GetSysclkSource(RCC_TypeDef *RCCx)
{
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	
    return ((uint8_t)(RCCx->SYSCLKSEL & ((uint32_t)0x0F)));
}

/** 
  * @brief  Configures the AHB clock Div (HCLK).
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_HCLK_DIV: defines the AHB clock divider. This clock is derived from 
  *   the system clock (SYSCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLK_Div1~255: HCLK clock = SYSCLK/(2*HCLKDIV)
        @arg RCC_HCLK_DIV1:  HCLK = SYSCLK
        @arg RCC_HCLK_DIV2:  HCLK = SYSCLK / 2
        @arg RCC_HCLK_DIV4:  HCLK = SYSCLK / 4
        @arg RCC_HCLK_DIV6:  HCLK = SYSCLK / 6
        @arg RCC_HCLK_DIV8:  HCLK = SYSCLK / 8
        @arg RCC_HCLK_DIV10: HCLK = SYSCLK / 10
        @arg RCC_HCLK_DIV12: HCLK = SYSCLK / 12
        @arg RCC_HCLK_DIV14: HCLK = SYSCLK / 14
        @arg RCC_HCLK_DIV16: HCLK = SYSCLK / 16
        @arg RCC_HCLK_DIV18: HCLK = SYSCLK / 18
        @arg RCC_HCLK_DIV20: HCLK = SYSCLK / 20
        @arg RCC_HCLK_DIV22: HCLK = SYSCLK / 22
        @arg RCC_HCLK_DIV24: HCLK = SYSCLK / 24
        @arg RCC_HCLK_DIV26: HCLK = SYSCLK / 26
        @arg RCC_HCLK_DIV28: HCLK = SYSCLK / 28
        @arg RCC_HCLK_DIV30: HCLK = SYSCLK / 30
        @arg RCC_HCLK_DIV32: HCLK = SYSCLK / 32
  *
  * @retval None
  */
void RCC_SetHclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_HCLK_DIV)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_HCLK_DIV(RCC_HCLK_DIV));

    /* Store the new value */
    RCCx->HCLKDIV = (uint32_t)RCC_HCLK_DIV;
}

/** 
  * @brief  Configures the Low Speed APB clock div (PCLK).
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_PCLK_DIV: defines the APB clock divider. This clock is derived from 
  *   the APB clock (PCLK).
  *   This parameter can be one of the following values:
        @arg RCC_APB_Div1~255: APB clock = HCLK/(2*DIV)
        @arg RCC_PCLK_DIV1:  PCLK = HCLK
        @arg RCC_PCLK_DIV2:  PCLK = HCLK / 2
        @arg RCC_PCLK_DIV4:  PCLK = HCLK / 4
        @arg RCC_PCLK_DIV6:  PCLK = HCLK / 6
        @arg RCC_PCLK_DIV8:  PCLK = HCLK / 8
        @arg RCC_PCLK_DIV10: PCLK = HCLK / 10
        @arg RCC_PCLK_DIV12: PCLK = HCLK / 12
        @arg RCC_PCLK_DIV14: PCLK = HCLK / 14
        @arg RCC_PCLK_DIV16: PCLK = HCLK / 16
        @arg RCC_PCLK_DIV18: PCLK = HCLK / 18
        @arg RCC_PCLK_DIV20: PCLK = HCLK / 20
        @arg RCC_PCLK_DIV22: PCLK = HCLK / 22
        @arg RCC_PCLK_DIV24: PCLK = HCLK / 24
        @arg RCC_PCLK_DIV26: PCLK = HCLK / 26
        @arg RCC_PCLK_DIV28: PCLK = HCLK / 28
        @arg RCC_PCLK_DIV30: PCLK = HCLK / 30
        @arg RCC_PCLK_DIV32: PCLK = HCLK / 32
  * @retval None
  */
void RCC_SetPclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_PCLK_DIV)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_PCLK_DIV(RCC_PCLK_DIV));
    
    /* Store the new value */
    RCCx->PCLKDIV = (uint32_t)RCC_PCLK_DIV;
}

/** 
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates it's clock.   
  * this parameter can be any combination of the following values:        
  		@arg RCC_AHBPeriph_GPIOA_CKEN :     Enables GPIOA         
		@arg RCC_AHBPeriph_GPIOB_CKEN :     Enables GPIOB  
		@arg RCC_AHBPeriph_GPIOC_CKEN :     Enables GPIOC        
		@arg RCC_AHBPeriph_GPIOD_CKEN :     Enables GPIOD         
		@arg RCC_AHBPeriph_CRC_CKEN   :     Enables CRC  
		@arg RCC_AHBPeriph_GPIOE_CKEN :     Enables GPIOE 
		@arg RCC_AHBPeriph_FLASH_CKEN :     Enables FLASH 
  * @param  NewState: new state of the AHB Periph clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCCx->HCLKEN |=  RCC_AHBPeriph;
    }
    else
    {
        RCCx->HCLKEN &= ~(uint32_t)RCC_AHBPeriph;
    }
}

/** 
  * @brief  Enables or disables the Low Speed APB peripheral clock.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_APBPeriph: specifies the APB peripheral to gates it's clock.
  *   This parameter can be any combination of the following values:
  *      @arg RCC_APBPeriph_EUART0_CKEN      
  *      @arg RCC_APBPeriph_EUART1_CKEN      
  *      @arg RCC_APBPeriph_I2C0_CKEN           
  *      @arg RCC_APBPeriph_ASPI_CKEN       
  *      @arg RCC_APBPeriph_LPTIM_CKEN      
  *      @arg RCC_APBPeriph_BASETIM_CKEN    
  *      @arg RCC_APBPeriph_SYSCON_CKEN          
  *      @arg RCC_APBPeriph_SPI1_CKEN       
  *      @arg RCC_APBPeriph_ETIMER_CKEN       
  *      @arg RCC_APBPeriph_TIM2_CKEN       
  *      @arg RCC_APBPeriph_WWDG_CKEN       
  *      @arg RCC_APBPeriph_ADC_CKEN        
  *      @arg RCC_APBPeriph_AWK_CKEN              
  *      @arg RCC_APBPeriph_CLKTRIM_CKEN    
  *      @arg RCC_APBPeriph_IWDG_CKEN       
  *      @arg RCC_APBPeriph_LVD_VC_OPA_CKEN 
  *      @arg RCC_APBPeriph_BEEP_CKEN       
  *      @arg RCC_APBPeriph_DEBUG_CKEN      
  *      @arg RCC_APBPeriph_CAN0_CKEN            
  *
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_APBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCCx->PCLKEN |=  RCC_APBPeriph;
    }
    else
    {
        RCCx->PCLKEN &= ~(uint32_t)RCC_APBPeriph;
    }
}

/** 
  * @brief  Forces or releases peripheral reset.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_PeriphRst: specifies the peripheral to reset.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_APBPeriph_EUART0_RST      
  *   @arg RCC_APBPeriph_EUART1_RST      
  *   @arg RCC_APBPeriph_I2C0_RST         
  *   @arg RCC_APBPeriph_ASPI_RST       
  *   @arg RCC_APBPeriph_LPTIM_RST      
  *   @arg RCC_APBPeriph_BASETIM_RST    
  *   @arg RCC_APBPeriph_SYSCON_RST          
  *   @arg RCC_APBPeriph_SPI1_RST       
  *   @arg RCC_APBPeriph_ETIMER_RST       
  *   @arg RCC_APBPeriph_TIM2_RST       
  *   @arg RCC_APBPeriph_WWDG_RST       
  *   @arg RCC_APBPeriph_ADC_RST        
  *   @arg RCC_APBPeriph_AWK_RST            
  *   @arg RCC_APBPeriph_CLKTRIM_RST          
  *   @arg RCC_APBPeriph_LVD_VC_OPA_RST 
  *   @arg RCC_APBPeriph_BEEP_RST       
  *   @arg RCC_APBPeriph_DEBUG_RST      
  *   @arg RCC_APBPeriph_CAN0_RST             
  *   @arg RCC_AHBPeriph_GPIOA_RST      
  *   @arg RCC_AHBPeriph_GPIOB_RST      
  *   @arg RCC_AHBPeriph_GPIOC_RST      
  *   @arg RCC_AHBPeriph_GPIOD_RST      
  *   @arg RCC_AHBPeriph_CRC_RST            
  *   @arg RCC_AHBPeriph_GPIOE_RST      
  *
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PeriphResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_PERIPHRST(RCC_PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

    if (NewState != DISABLE)
    {
        RCCx->PERIPRST |=  RCC_PeriphRst;
    }
    else
    {
        RCCx->PERIPRST &= ~(uint32_t)RCC_PeriphRst;
    }
	
    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Enable or disable MCU/CPU reset.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_RSTMode: Chip reset mode
  *   This parameter can be the following values:
       @arg RCC_MCU_RESET        
       @arg RCC_CPU_RESET      
  * @param  NewState: new state of chip reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_RSTMode, FunctionalState NewState)
{
	uint32_t rcc_reset_mode = 0;
	
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_RST(RCC_RSTMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (RCC_RSTMode == RCC_MCU_RESET)
    {
    	rcc_reset_mode = 0x55AA6699;
    }
    else if (RCC_RSTMode == RCC_CPU_RESET)
    {
    	rcc_reset_mode = 0x55AA669A;
    } 
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

    if (NewState != DISABLE)
    {
        RCCx->RSTCR |=  rcc_reset_mode;
    }
    else
    {
        RCCx->RSTCR &= ~(uint32_t)rcc_reset_mode;
    }
	
	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Checks whether the specified reset source is set or not.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  RCC_RST_FLAG: specifies the flag to check. 
			@arg RCC_FLAG_MCU_RST      
			@arg RCC_FLAG_CPU_RST      
			@arg RCC_FLAG_WWDG_RST     
			@arg RCC_FLAG_IWDG_RST     
			@arg RCC_FLAG_LVD_RST      
			@arg RCC_FLAG_POR_RST      
			@arg RCC_FLAG_LOCKUP_RST   
			@arg RCC_FLAG_PAD_RST 
			@arg RCC_FLAG_SOFT_RST 
			@arg RCC_FLAG_CMU_LOC_RST 
			@arg RCC_FLAG_LOL_RST 
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetResetFlag(RCC_TypeDef *RCCx, uint32_t RCC_RST_FLAG)
{
    uint32_t tmpreg = 0;
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_FLAG_RST(RCC_RST_FLAG));

    /* Get the RCC Reset Value */
    tmpreg = RCCx->RSTSR;  // RCCx->RSTSR只受POR控制

    if ((tmpreg & RCC_RST_FLAG) != (uint32_t)RESET)
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
  * @brief  Config SWD port to gpio function
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  NewState: new state of the SWD port
  *   This parameter can be: ENABLE or DISABLE. 
        ENABLE  : 周边模块功能模式
        DISABLE : PA4和PC4的端口功能模式为SWD端口功能
  * @retval None
  */
void RCC_Config_Swd_GPIO(RCC_TypeDef *RCCx, FunctionalState NewState)
{
	uint32_t tmpreg = 0; 
	
	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		tmpreg = 0x5A690000;  // 周边模块功能
	}
	else
	{
		tmpreg = 0x5A690001;  // SWD管脚功能
	}
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
	/*set the value to the SWDIOCR register*/
	RCCx->SWDIOCR = tmpreg;
	
	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Set PLL Stable time value.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  PLL_Stable_Value: PLL stable time value
  *   This parameter can be the following values:
		@arg RCC_PLL_STARTUP_PERIOD_128
		@arg RCC_PLL_STARTUP_PERIOD_256
		@arg RCC_PLL_STARTUP_PERIOD_512
		@arg RCC_PLL_STARTUP_PERIOD_1024
		@arg RCC_PLL_STARTUP_PERIOD_2048
		@arg RCC_PLL_STARTUP_PERIOD_4096
		@arg RCC_PLL_STARTUP_PERIOD_8192
		@arg RCC_PLL_STARTUP_PERIOD_16384

  * @retval None
  */
void RCC_PLL_Set_Stable_Value(RCC_TypeDef *RCCx, uint16_t PLL_Stable_Value)
{	
	uint32_t tmpreg = 0;

	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
    assert_param(IS_RCC_PLL_STARTUP_PERIOD(PLL_Stable_Value));
	
	/* Read PLLCR */
	tmpreg = RCCx->PLLCR;

	/* Set PLL STARTUP period value */
	tmpreg &= ~(uint32_t)(RCC_PLL_STARTUP_PERIOD_MSK << 19);
	tmpreg |=  (uint32_t)(PLL_Stable_Value << 19);
	
	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

	RCCx->PLLCR = tmpreg;
	
	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
}

/** 
  * @brief  Enable or disable HXT clock.
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC   
  * @param  NewState: new state of HXT clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval An Error Status enumuration value:
  * - SUCCESS: HXT oscillator is stable and ready to use
  * - ERROR: HXT oscillator startup failed
  */
ErrorStatus RCC_HXT_Cmd(RCC_TypeDef *RCCx, FunctionalState NewState) 
{
    __IO uint32_t StartUpCounter = 0;
    uint32_t tempreg = 0;
    uint32_t HXTStatus = 0;
    ErrorStatus status = ERROR;

	/* Check the parameters */
	assert_param(IS_RCC_ALL_PERIPH(RCCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

	if (NewState != DISABLE)
	{
		tempreg  =  RCCx->HXTCR;
		tempreg &= ~(uint32_t)RCC_HXT_STARTUP_MASK;
		tempreg |=  (uint32_t)(RCC_HXT_STARTUP_PERIOD_16384 << 4);
        tempreg &= ~(uint32_t)(HXT_XSEL_STRONG << 2);    // 振幅控制位：00
        tempreg |=  (uint32_t)(HXT_XSEL_STRONGER << 2);  // 振幅控制位：10
        tempreg &= ~(uint32_t)(HXT_IBSEL_STRONG << 0);   // 偏置电流控制位：00
        tempreg |=  (uint32_t)(HXT_IBSEL_STRONGER << 0); // 偏置电流控制位：10
		RCCx->HXTCR = 0x5A690000 + tempreg;   // Set HXT Stable time
		
		tempreg = RCCx->SYSCLKCR;

	#if 1  // for test
		tempreg &= ~(uint32_t)RCC_HXT_BYP_ENABLE;   // HXT时钟与OSC_IN/OSC_OUT管脚相连接
	#else
		tempreg |=  (uint32_t)RCC_HXT_BYP_ENABLE;   // HXT 内部振荡模块旁路模式， HXT 从管脚 OSCIN 直接输入
    #endif

		tempreg |= RCC_HXT_PORT_OSC;      // OSCIN/OSCOUT管脚配置-->HXT管脚模式(模拟功能)
		tempreg |= RCC_HXT_ENABLE;        // HXT Enable
		RCCx->SYSCLKCR = 0x5A690000 + tempreg;

		/* Wait till HXT STABLE or timeout */
	    do
	    {
	        HXTStatus = (RCCx->HXTCR & RCC_FLAG_HXTRDY);
	        StartUpCounter++;  
	    } while ((StartUpCounter < 0xFFFFFFFFUL) && (HXTStatus != RCC_FLAG_HXTRDY));

	    if (HXTStatus == RCC_FLAG_HXTRDY)
	    {
	    	status = SUCCESS;
	    }
	    else
	    {
	    	status = ERROR;
	    }
	}
	else    // Disable
	{
		tempreg  =  RCCx->SYSCLKCR;
		tempreg &= ~(uint32_t)RCC_HXT_PORT_OSC;  // OSCIN/OSCOUT管脚配置GPIO功能模式(数字功能)
		tempreg &= ~(uint32_t)RCC_HXT_ENABLE;    // HXT Disable
		RCCx->SYSCLKCR = 0x5A690000 + tempreg;
		status = SUCCESS;
	}

	/* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
    
	return (status);
}

/** 
  * @brief  System clock source switch to pll
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  PLLCLK_Source: input clock source of pll
  *   This parameter can be the following values:
		@arg PLL_INPUT_SOURCE_HIRC
		@arg PLL_INPUT_SOURCE_HXT
  * @param  PLLCLK_Freq: specifies pll Freq. value.
  *   This parameter can be the following values:
  		@arg SET_PLL_FREQ_48MHz
  		@arg SET_PLL_FREQ_40MHz
  		@arg SET_PLL_FREQ_32MHz
  		@arg SET_PLL_FREQ_24MHz
  		@arg SET_PLL_FREQ_16MHz
  * @retval ERROR (0), SUCESS(1)
  * @remark Fin x (M / N) * (1 / OD), Fin=8MHz(HIRC=8MHz or HXT=8MHz)
  */
ErrorStatus RCC_SysClk_SwitchTo_PLL(RCC_TypeDef *RCCx, uint8_t PLL_Source_Sel, uint8_t PLL_Freq)
{
    uint32_t tmpreg = 0;
    uint32_t PLLCR_Status = 0;
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    
	/* Set PLL STARTUP period value */
//    tmpreg |= (uint32_t)(RCC_PLL_STARTUP_PERIOD_2048 << 19);  // Startup time --> 2048个PLL周期 
//    tmpreg |= (uint32_t)(RCC_PLL_STARTUP_PERIOD_4096 << 19);  // Startup time --> 4096个PLL周期
    tmpreg |= (uint32_t)(RCC_PLL_STARTUP_PERIOD_8192 << 19);  // Startup time --> 8192个PLL周期

    /* Select PLL input clock source */
    if (PLL_Source_Sel == PLL_INPUT_SOURCE_HXT)
    {
    	tmpreg |= (uint32_t)(0x01UL << 3);   // PLL input clock source : HXT clock
    	/* Enable HXT clock */
    	status = RCC_HXT_Cmd(RCCx, ENABLE);
    	if (status == ERROR)
    	{
    		return (status);
    	}
    }
    
    tmpreg |= (uint32_t)(0x01UL << 2);   // 输出使能控制OEN=1, 即PLL正常输出
    
    switch (PLL_Freq)
    {
		case SET_PLL_FREQ_48MHz:                   
            tmpreg |= (uint32_t)((0x06UL << 12) | (0x01UL << 6));   // M=6  N=1
            break;
		case SET_PLL_FREQ_40MHz:	               
            tmpreg |= (uint32_t)((0x05UL << 12) | (0x01UL << 6));   // M=5  N=1
            break;			
		case SET_PLL_FREQ_32MHz:	               
            tmpreg |= (uint32_t)((0x04UL << 12) | (0x01UL << 6));   // M=4  N=1
            break;		
		case SET_PLL_FREQ_24MHz:	               
            tmpreg |= (uint32_t)((0x03UL << 12) | (0x01UL << 6));   // M=3  N=1
            break;			
		case SET_PLL_FREQ_16MHz:	               
            tmpreg |= (uint32_t)((0x02UL << 12) | (0x01UL << 6));   // M=2  N=1
            break;	
        default:   // default pll=48MHz
            tmpreg |= (uint32_t)((0x06UL << 12) | (0x01UL << 6));   // M=6  N=1
            break;    
    }

    /* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;
	
    RCCx->PLLCR = tmpreg;   // 配置PLLCR寄存器

	tmpreg  = FLASH->ACR;
    tmpreg |=  (uint32_t)(0x01UL << 8);   // 启用预取缓冲区
	tmpreg &= ~(uint32_t)(0x07UL << 0);   // 0个等待位
    
    /* 根据系统时钟频率配置等待位 */
    if (PLL_Freq > 36u)
    {
        tmpreg |= (uint32_t)(0x02 << 0);  // 两个等待位，当SYSCLK > 36MHz
    }
    else if ((PLL_Freq > 18u) && (PLL_Freq <= 36u))
    {
        tmpreg |= (uint32_t)(0x01 << 0);  // 一个等待位，当18MHz < SYSCLK ≤ 36MHz
    }
    
    __disable_irq();   // 关闭总中断
    FLASH->ACR = tmpreg;   // 对FLASH_ACR.LATENCY连续两次写同样的值才有效
    FLASH->ACR = tmpreg; 
    __enable_irq();    // 开启总中断    

	/* Wait till PLL STABLE or timeout */
    do
    {
        PLLCR_Status = RCCx->PLLCR & RCC_FLAG_PLL;
        StartUpCounter++;  
    } while ((StartUpCounter < 0xFFFFFFFFUL) && (PLLCR_Status != RCC_FLAG_PLL));

	if (PLLCR_Status == RCC_FLAG_PLL)  // 判断PLL是否已经稳定？
	{
		status = SUCCESS;
		RCCx->SYSCLKSEL &= (uint32_t)0xFFFFFFF0;      // CLKSW[3:0] = 4'b0000
    	RCCx->SYSCLKSEL  = 0x5A690004;   // 系统时钟源选择：PLL
	}
    else
    {
    	status = ERROR;
    }
    
    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	

    return (status);
}

/** 
  * @brief  System clock source switch to HXT Clock
  * @param  RCCx: Selects the RCCx peripheral
  *    This parameter can be one of the following values: 
  *         RCC
  * @param  HXT_Freq: specifies hxt Freq. value(uint: MHz).
  *   This parameter can be the following values:
  		@arg RCC_SEL_HXT_FREQ_8MHz
  		@arg RCC_SEL_HXT_FREQ_12MHz
  		@arg RCC_SEL_HXT_FREQ_16MHz
  		@arg RCC_SEL_HXT_FREQ_24MHz
  		@arg RCC_SEL_HXT_FREQ_32MHz
  * @retval ERROR (0), SUCESS (1)
  */
ErrorStatus RCC_SysClk_SwitchTo_HXT(RCC_TypeDef *RCCx, uint8_t HXT_Freq)
{
     __IO uint32_t StartUpCounter = 0;
    uint32_t tempreg = 0;
    uint32_t HXTStatus = 0;
    ErrorStatus status = ERROR;
    
    /* Close the lock of register */
	RCCx->UNLOCK = RCC_UNLOCK_KEY;

    tempreg  =  RCCx->HXTCR;
    tempreg &= ~(uint32_t)RCC_HXT_STARTUP_MASK;
    tempreg |=  (uint32_t)(RCC_HXT_STARTUP_PERIOD_16384 << 4);
    tempreg &= ~(uint32_t)(HXT_XSEL_STRONG << 2);    // 振幅控制位：2'b00
    tempreg &= ~(uint32_t)(HXT_IBSEL_STRONG << 0);   // 偏置电流控制位：2'b00
    
    if (HXT_Freq > RCC_SEL_HXT_FREQ_24MHz)  // HXT晶振时钟大于24MHz时
    {
        tempreg |=  (uint32_t)(HXT_XSEL_STRONG << 2);    // 振幅控制位：2'b11
        tempreg |=  (uint32_t)(HXT_IBSEL_STRONG << 0);   // 偏置电流控制位：2'b11
    }
    else
    {
        tempreg |=  (uint32_t)(HXT_XSEL_STRONGER << 2);  // 振幅控制位：2'b10
        tempreg |=  (uint32_t)(HXT_IBSEL_STRONGER << 0); // 偏置电流控制位：2'b10
    }
        
    RCCx->HXTCR = 0x5A690000 + tempreg;   // Set RCC_HXTCR Register
    
    tempreg = RCCx->SYSCLKCR;
    tempreg &= ~(uint32_t)RCC_HXT_BYP_ENABLE;   // HXT时钟与OSC_IN/OSC_OUT管脚相连接
    tempreg |=  RCC_HXT_PORT_OSC;   // OSCIN/OSCOUT管脚配置-->HXT管脚模式(模拟功能)
    tempreg |=  RCC_HXT_ENABLE;     // HXT Enable
    RCCx->SYSCLKCR = 0x5A690000 + tempreg;

    /* Wait till HXT STABLE or timeout */
    do
    {
        HXTStatus = (RCCx->HXTCR & RCC_FLAG_HXTRDY);
        StartUpCounter++;  
    } while ((StartUpCounter < 0xFFFFFFFFUL) && (HXTStatus != RCC_FLAG_HXTRDY));

    if (HXTStatus == RCC_FLAG_HXTRDY)   // 判断HXT是否Ready?
    {
        status = SUCCESS;
        RCCx->SYSCLKSEL &= (uint32_t)0xFFFFFFF0;      // CLKSW[3:0] = 4'b0000
    	RCCx->SYSCLKSEL  = 0x5A690002;   // 系统时钟源选择：HXT
    }
    else
    {
        status = ERROR;
    }

    /* Open the lock of register */
    RCCx->UNLOCK = RCC_LOCK_KEY;	
    
    return (status);
}


