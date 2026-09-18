/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_syscon.h"
#include "cps32k21x_rcc.h"
#include "cps32k21x_advtim.h"  


/** 
  * @brief  Deinitializes the SYSCON Functions 
  *   registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCON_DeInit(void)
{
	/* Enable SYSCON reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SYSCON_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    
    /* Release SYSCON from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SYSCON_RST, DISABLE);
}

/** 
  * @brief  Enable or disable Cortex-M0 Lockup function
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: new state of the SYSCONx.
  *    This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void SYSCON_CortexM0LockUpCmd(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
    uint32_t tempreg = 0;
    
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
    tempreg = SYSCONx->CFGR0;
    
    /* Close lock */
    SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;
	
	if (NewState != DISABLE)
	{
        tempreg |=  LOCKUP_EN;
	}
	else
	{
		tempreg &=  (uint32_t)(~LOCKUP_EN);
	}
	
    SYSCONx->CFGR0 = 0x5A690000 + tempreg;
    
	/* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

/** 
  * @brief  Debug模式下，禁止Deep Sleep模式进入配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: Debug模式下，Deep Sleep模式禁止进入状态
  *    This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void SYSCON_DBG_DSLP_DisConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	uint32_t tempreg = 0;
		
	/* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    tempreg = SYSCONx->CFGR0;

	/* Close lock */
    SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;
    
    if (NewState != DISABLE)   // 在Debug模式下禁止进入Deep Sleep模式
    {
    	tempreg |= BIT1;
    }
    else  // 在Debug模式下允许进入Deep Sleep模式
    {
    	tempreg &= (uint32_t)(~BIT1);
    }

	SYSCONx->CFGR0 = 0x5A690000 + tempreg;
	
    /* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

/** 
  * @brief  IWDG在Deep Sleep模式下停止计数配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: IWDG在Deep Sleep模式下停止计数状态配置.
  *    This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void SYSCON_IWDG_DSLP_StopConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	uint32_t tempreg = 0;
	
	/* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    tempreg = RCC->PCLKEN;
    if (0 == (tempreg & ((uint32_t)(0x01UL << 7))))
    {
        RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_SYSCON_CKEN, ENABLE);  // 开启SYSCON模块时钟
    }

	tempreg = SYSCONx->CFGR0;
	
    /* Close lock */
    SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;

	if (NewState != DISABLE)   // IWDG在Deep Sleep模式下停止计数
	{
		tempreg |= IWDT_DSLP_STOP;
	}
	else  // IWDG在Deep Sleep模式下保持计数
	{
		tempreg &= (uint32_t)(~IWDT_DSLP_STOP);
	}

	SYSCONx->CFGR0 = 0x5A690000 + tempreg;
	
    /* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

/** 
  * @brief  GPIO端口FAST配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: GPIO端口的Fast使能及禁止
  *    This parameter can be: ENABLE or DISABLE.    
  * @retval None
  */
void SYSCON_GPIO_Fast_Cmd(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	uint32_t tempreg = 0;
	
	/* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

	tempreg = SYSCONx->CFGR0;
	
    /* Close lock */
    SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;

	if (NewState != DISABLE)   
	{
		tempreg &= (uint32_t)(~FAST_IO_DIS);  // 使能GPIO Fast功能
	}
	else  
	{
		tempreg |= FAST_IO_DIS;   // 关闭GPIO Fast功能
	}

	SYSCONx->CFGR0 = 0x5A690000 + tempreg;
	
    /* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;

}

/** 
  * @brief  端口中断模式选择.
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  PadIntSel: 端口中断模式选择
  *    This parameter can be one of the following values: 
  *       @arg  PAD_INTSEL_DSLP
  *       @arg  PAD_INTSEL_SLEEP
  * @retval None
  */
void SYSCON_PadIT_Mode_Select(SYSCON_TypeDef* SYSCONx, uint32_t PadIntSel)
{
	uint32_t tempreg = 0;
	
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_PAD_INTSEL(PadIntSel));

	if (PadIntSel == PAD_INTSEL_DSLP)   // 若端口中断模式选择DeepSleep中断产生模式
	{
    	tempreg |= (BIT1 | BIT0);
    }
    else if (PadIntSel == PAD_INTSEL_SLEEP)
    {
    	tempreg |= BIT1;
    }

	SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;
    SYSCONx->PORTINTCR = 0x5A690000 + tempreg;
    SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

/** 
  * @brief  配置ASPI从机模式时ASPI_SSN信号来源
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  ASPI_SSN_Sel : selects the GPIO port pin to be used as 
            ASPI peripheral nss signal
  *    This parameter can be one of the following values: 
  *		  @arg ASPI_SSN_SEL_High
  *		  @arg ASPI_SSN_SEL_PB5
  *		  @arg ASPI_SSN_SEL_PC6
  *		  @arg ASPI_SSN_SEL_PC15
  * @retval None
  */
void SYSCON_ASPI_SSN_Config(SYSCON_TypeDef* SYSCONx, uint32_t ASPI_SSN_Sel)
{
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_SPI0_SSN_SEL(ASPI_SSN_Sel));
    
    /* ASPI SSN */
    SYSCONx->PORTCR &= (uint32_t)(~ASPI_SSN_SEL_Mask);
    SYSCONx->PORTCR |= ASPI_SSN_Sel;
}

/** 
  * @brief  配置SPI1从机模式时SPI1_SSN信号来源
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  SP1_SSN_Sel : selects the GPIO port pin to be used as 
  *         SPI1 peripheral nss signal
  *    This parameter can be one of the following values: 
  *		 @arg SPI1_SSN_SEL_High
  *		 @arg SPI1_SSN_SEL_PB8
  *		 @arg SPI1_SSN_SEL_PC5
  *		 @arg SPI1_SSN_SEL_PD3
  * @retval None
  */
void SYSCON_SPI1_SSN_Config(SYSCON_TypeDef* SYSCONx, uint32_t SP1_SSN_Sel)
{
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_SPI1_SSN_SEL(SP1_SSN_Sel));
    
    /* SPI1 SSN */
    SYSCONx->PORTCR &= (uint32_t)(~SPI1_SSN_SEL_Mask);
    SYSCONx->PORTCR |= SP1_SSN_Sel;
}

/** 
  * @brief  Config TIM10 GATE singnal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  TIM10_Gate_Sel: Select TIM10 GATE signal
  *    This parameter can be one of the following values: 
  *		  @arg TIM10_GATE_SEL_SELF
  *		  @arg TIM10_GATE_SEL_EUART0_RXD
  *		  @arg TIM10_GATE_SEL_EUART1_RXD
  *		  @arg TIM10_GATE_SEL_VC
  * @retval None 
  */
void SYSCON_TIM10_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t TIM10_Gate_Sel) 
{ 
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_TIM10_GATE_SEL(TIM10_Gate_Sel)); 
	
    /* Configure TIM0 GATE selection PIN */ 
    SYSCONx->PORTCR &= (uint32_t)(~TIM10_GATE_SEL_Mask);
    SYSCONx->PORTCR |= TIM10_Gate_Sel;
}

/** 
  * @brief  Config TIM11 GATE singnal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  TIM11_Gate_Sel: Select TIM11 GATE signal
  *    This parameter can be one of the following values: 
  *		 @arg TIM11_GATE_SEL_SELF
  *		 @arg TIM11_GATE_SEL_EUART0_RXD
  *		 @arg TIM11_GATE_SEL_EUART1_RXD
  *		 @arg TIM11_GATE_SEL_VC
  * @retval None 
  */
void SYSCON_TIM11_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t TIM11_Gate_Sel) 
{ 
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_TIM11_GATE_SEL(TIM11_Gate_Sel)); 
	
    /* Configure TIM0 GATE selection PIN */ 
    SYSCONx->PORTCR &= (uint32_t)(~TIM11_GATE_SEL_Mask);
    SYSCONx->PORTCR |= TIM11_Gate_Sel;
}

/** 
  * @brief  Config LPTIM GATE singnal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  LPTIM_Gate_Sel: Select LPTIM GATE signal
  *    This parameter can be one of the following values: 
  *		  @arg LPTIM_GATE_SEL_SELF
  *		  @arg LPTIM_GATE_SEL_EUART0_RXD
  *		  @arg LPTIM_GATE_SEL_EUART1_RXD
  *		  @arg LPTIM_GATE_SEL_VC
  * @retval None 
  */
void SYSCON_LPTIM_GateConfig(SYSCON_TypeDef* SYSCONx, uint32_t LPTIM_Gate_Sel) 
{ 
    /* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_LPTIM_GATE_SEL(LPTIM_Gate_Sel)); 

    /* Configure IPTIM GATE selection PIN */ 
    SYSCONx->PORTCR &= (uint32_t)(~LPTIM_GATE_SEL_Mask);
    SYSCONx->PORTCR |= LPTIM_Gate_Sel;
}

/**  
  * @brief  Config LPTIM EXT singnal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  LPTIM_EXT_Sel: Select LPTIM EXT signal
  *    This parameter can be one of the following values: 
  *		  @arg LPTIM_EXT_SEL_SELF
  *		  @arg LPTIM_EXT_SEL_VC
  * @retval None 
  */
void SYSCON_LPTIM_EXTConfig(SYSCON_TypeDef* SYSCONx, uint32_t LPTIM_EXT_Sel) 
{
	/* Check the parameters */
    assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_LPTIM_EXT_SEL(LPTIM_EXT_Sel)); 

    /* Configure IPTIM GATE selection PIN */ 
    SYSCONx->PORTCR &= (uint32_t)(~LPTIM_EXT_SEL_Mask);
    SYSCONx->PORTCR |= LPTIM_EXT_Sel;
}

/** 
  * @brief  Config ETIMER input signal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  ETIMERx_Channel: Select ETIMERx Channel 
  *    This parameter can be one of the following values:
  *       @arg ETIMER_Channel_1
  *       @arg ETIMER_Channel_2
  *       @arg ETIMER_Channel_3
  *       @arg ETIMER_Channel_4
  * @param  InputSignal_Sel: Select input signal
  *    This parameter can be one of the following values:
  *       @arg ETIMER_CH_SEL_SELF
  *       @arg ETIMER_CH_SEL_EUART0_RXD
  *       @arg ETIMER_CH_SEL_EUART1_RXD
  *       @arg ETIMER_CH_SEL_LIRC
  *       @arg ETIMER_CH_SEL_VC
  * @retval None 
  */
void SYSCON_ETIMER_ChannelConfig(SYSCON_TypeDef* SYSCONx, uint8_t ETIMER_Channel, uint32_t InputSignal_Sel)
{
    /* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_TIM_CHANNEL(ETIMER_Channel)); 
	assert_param(IS_TIM_CH_SEL(InputSignal_Sel)); 
	
	switch (ETIMER_Channel)
	{
		case ETIMER_Channel_1:
			SYSCONx->ETIMERCR &= (uint32_t)(~(ETIMER_CH_SEL_Mask << 0));
			SYSCONx->ETIMERCR |= (uint32_t)(InputSignal_Sel << 0);
			break;
		case ETIMER_Channel_2:
			SYSCONx->ETIMERCR &= (uint32_t)(~(ETIMER_CH_SEL_Mask << 4));
			SYSCONx->ETIMERCR |= (uint32_t)(InputSignal_Sel << 4);
			break;
		case ETIMER_Channel_3:
			SYSCONx->ETIMERCR &= (uint32_t)(~(ETIMER_CH_SEL_Mask << 8));
			SYSCONx->ETIMERCR |= (uint32_t)(InputSignal_Sel << 8);
			break;
		case ETIMER_Channel_4:
			SYSCONx->ETIMERCR &= (uint32_t)(~(ETIMER_CH_SEL_Mask << 12));
			SYSCONx->ETIMERCR |= (uint32_t)(InputSignal_Sel << 12);
			break;
		default : break;
	}
}

/** 
  * @brief  Config tim1 ETR signal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  ETR_Signal_Sel: Select ETR signal
  *	   This parameter can be one of the following values: 
  *       @arg ETIMER_ETR_SEL_Low
  *       @arg ETIMER_ETR_SEL_PA1
  *       @arg ETIMER_ETR_SEL_PA2
  *       @arg ETIMER_ETR_SEL_PA3
  *       @arg ETIMER_ETR_SEL_PB4
  *       @arg ETIMER_ETR_SEL_PB5
  *       @arg ETIMER_ETR_SEL_PC3
  *       @arg ETIMER_ETR_SEL_PC4
  *       @arg ETIMER_ETR_SEL_PC5
  *       @arg ETIMER_ETR_SEL_PC6
  *       @arg ETIMER_ETR_SEL_PC7
  *       @arg ETIMER_ETR_SEL_PD1
  *       @arg ETIMER_ETR_SEL_PD2
  *       @arg ETIMER_ETR_SEL_VCOUT
  * @retval None 
  */
void SYSCON_ETIMER_ETRSignalConfig(SYSCON_TypeDef* SYSCONx, uint32_t ETR_Signal_Sel)
{
    /* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_TIM_ETR_SEL(ETR_Signal_Sel));
	
	SYSCONx->ETIMERCR &= (uint32_t)(~ETIMER_ETR_SEL_Mask);
	SYSCONx->ETIMERCR |= ETR_Signal_Sel;
}

/** 
  * @brief  Config ETIMER Break 模式下OCx/OCxN输出配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: 在Break刹车有效模式下，OCx/OCxN输出状态配置
  *    This parameter can be: ENABLE or DISABLE.  
  *    ENABLE : OCx/OCxN在break模式符合STM协议
  *    DISABLE: OCx/OCxN在break模式同时输出0
  * @retval None 
  */
void SYSCON_ETIMER_Break_OutCfg(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));

	if (NewState != DISABLE)
	{
	    SYSCONx->ETIMERCR &= (uint32_t)(~BREAK_OUT_CFG);
	}
	else
	{
	    SYSCONx->ETIMERCR |= (uint32_t)(BREAK_OUT_CFG);  // OCx/OCxN在Break模式下同时输出0
	}
}

/** 
  * @brief  ETIMER在Break模式下OCx/OCxN输出设置为0
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *     This parameter can be one of the following values: 
  *         SYSCON
  * @retval None 
  */
void SYSCON_ETIMER_SetBreakZero(SYSCON_TypeDef* SYSCONx)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));

	SYSCONx->ETIMERCR |= BREAK_OUT_CFG;
}

/** 
  * @brief  系统时钟停止检出时，ETIMER Break使能状态配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *     This parameter can be one of the following values: 
  *         SYSCON.
  * @param  NewState: 系统时钟停止检出时，ETIMER Break使能状态
  *   	This parameter can be: ENABLE or DISABLE. 
  * @retval None 
  */
void SYSCON_ClkFail_BreakConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		SYSCONx->ETIMERCR |= CLK_FAIL_BREAK_EN;
	}
	else
	{
		SYSCONx->ETIMERCR &= (uint32_t)(~CLK_FAIL_BREAK_EN);
	}
}

/** 
  * @brief  Config TIM2 Channel input signal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  TIMx_Channel: Select ETIMERx Channel 
  *    This parameter can be one of the following values:
  *       @arg TIM_Channel_1
  *       @arg TIM_Channel_2
  *       @arg TIM_Channel_3
  *       @arg TIM_Channel_4
  * @param  InputSignal_Sel: Select input signal
  *    This parameter can be one of the following values:
  *       @arg TIM2_CH_SEL_SELF
  *       @arg TIM2_CH_SEL_EUART0_RXD
  *       @arg TIM2_CH_SEL_EUART1_RXD
  *       @arg TIM2_CH_SEL_LIRC
  *       @arg TIM2_CH_SEL_VC
  * @retval None 
  */
void SYSCON_TIM2_ChannelConfig(SYSCON_TypeDef* SYSCONx, uint8_t TIMx_Channel, uint32_t InputSignal_Sel)
{
    /* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_TIM_CHANNEL(TIMx_Channel)); 
	assert_param(IS_TIM2_CH_SEL(InputSignal_Sel)); 
	
	switch (TIMx_Channel)
	{
		case TIM_Channel_1:
			SYSCONx->TIM2CR &= (uint32_t)(~(TIM2_CH_SEL_Mask << 0));
			SYSCONx->TIM2CR |= (uint32_t)(InputSignal_Sel << 0);
			break;
		case TIM_Channel_2:
			SYSCONx->TIM2CR &= (uint32_t)(~(TIM2_CH_SEL_Mask << 4));
			SYSCONx->TIM2CR |= (uint32_t)(InputSignal_Sel << 4);
			break;
		case TIM_Channel_3:
			SYSCONx->TIM2CR &= (uint32_t)(~(TIM2_CH_SEL_Mask << 8));
			SYSCONx->TIM2CR |= (uint32_t)(InputSignal_Sel << 8);
			break;
		case TIM_Channel_4:
			SYSCONx->TIM2CR &= (uint32_t)(~(TIM2_CH_SEL_Mask << 12));
			SYSCONx->TIM2CR |= (uint32_t)(InputSignal_Sel << 12);
			break;
		default : break;
	}
}

/** 
  * @brief  Config TIM2 ETR signal
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  ETR_Signal_Sel: Select ETR signal
  *	   This parameter can be one of the following values: 
  *       @arg TIM2_ETR_SEL_Low
  *       @arg TIM2_ETR_SEL_PA1
  *       @arg TIM2_ETR_SEL_PA2
  *       @arg TIM2_ETR_SEL_PA3
  *       @arg TIM2_ETR_SEL_PB4
  *       @arg TIM2_ETR_SEL_PB5
  *       @arg TIM2_ETR_SEL_PC3
  *       @arg TIM2_ETR_SEL_PC4
  *       @arg TIM2_ETR_SEL_PC5
  *       @arg TIM2_ETR_SEL_PC6
  *       @arg TIM2_ETR_SEL_PC7
  *       @arg TIM2_ETR_SEL_PD1
  *       @arg TIM2_ETR_SEL_PD2
  *       @arg TIM2_ETR_SEL_VCOUT
  * @retval None 
  */
void SYSCON_TIM2_ETRSignalConfig(SYSCON_TypeDef* SYSCONx, uint32_t ETR_Signal_Sel)
{
    /* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_TIM2_ETR_SEL(ETR_Signal_Sel));
	
	SYSCONx->TIM2CR &= (uint32_t)(~TIM2_ETR_SEL_Mask);
	SYSCONx->TIM2CR |= ETR_Signal_Sel;
}

/** 
  * @brief  Deep Sleep模式下，ETIMER Break使能状态配置
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *     This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: Deep Sleep下ETIMER Break使能状态
  *   	This parameter can be: ENABLE or DISABLE. 
  * @retval None 
  */
void SYSCON_DSLP_BreakConfig(SYSCON_TypeDef* SYSCONx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		SYSCONx->ETIMERCR |= DSLP_BREAK_EN;
	}
	else
	{
		SYSCONx->ETIMERCR &= (uint32_t)(~DSLP_BREAK_EN);
	}
}

/**
  * @brief  Fills each NMI_InitStruct member with its default value.
  * @param  NMI_InitStruct: pointer to a NMI_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void NMI_StructInit(NMI_InitTypeDef* NMI_InitStruct)
{
	NMI_InitStruct->clkSel    = NMI_CKSEL_PCLK;  // NMI时钟选择PCLK
	NMI_InitStruct->EnStatus  = NMI_DISABLE;     // NMI禁止
	NMI_InitStruct->filterEn  = NMI_FLT_DISABLE; // NMI滤波禁止
	NMI_InitStruct->filterDiv = NMI_FLT_DIV1;    // NMI滤波1分频
}

/**
  * @brief  Initializes the NMI according to the specified
  *         parameters in the NMI_InitStruct .
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *     This parameter can be one of the following values: 
  *         SYSCON
  * @param  NMI_InitStruct: pointer to a NMI_InitTypeDef structure
  *         that contains the configuration information for the NMI
  * @retval None
  */
void SYSCON_NMI_Init(SYSCON_TypeDef* SYSCONx, NMI_InitTypeDef* NMI_InitStruct)
{
	uint32_t tempreg = 0;
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));

	tempreg = SYSCONx->NMICR;
	
	/* Close lock */
    SYSCONx->UNLOCK = SYSCON_UNLOCK_KEY;
    
	tempreg &= (uint32_t)(~NMI_ENABLE);
	tempreg |= NMI_InitStruct->EnStatus;

	tempreg &= (uint32_t)(~NMI_FLT_ENABLE);
	tempreg |= NMI_InitStruct->filterEn;

	tempreg &= (uint32_t)(~NMI_CKSEL_LIRC);
	tempreg |= NMI_InitStruct->clkSel;
	
	tempreg &= (uint32_t)(~NMI_FLT_DIV_Mask);
	tempreg |= NMI_InitStruct->filterDiv;

	SYSCONx->NMICR = 0x5A690000 + tempreg;

	/* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

/**
  * @brief  Checks whether NMI interrupt has occurred or not.
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NMI_IT_Flag: specifies the NMI interrupt source to check.
  *    This parameter can be one of the following values:
  *		  @arg NMI_INTF          
  * @retval The new state of NMI interrupt (SET or RESET).
  */
ITStatus SYSCON_NMI_GetITStatus(SYSCON_TypeDef* SYSCONx, uint32_t NMI_IT_Flag)
{
	ITStatus bitstatus = RESET;
	
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_NMI_INTF(NMI_IT_Flag));

	if ((SYSCONx->NMISR & NMI_IT_Flag) != (uint16_t)RESET)
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
  * @brief  Clears the NMI interrupt pending bit.
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *    This parameter can be one of the following values: 
  *         SYSCON
  * @param  NMI_IT_Flag: NMI Interrupt flag. 
  *    This parameter can be one of the following values:
  *		@arg NMI_INTF          
  * @retval None
  */
void SYSCON_NMI_ClearITFlag(SYSCON_TypeDef* SYSCONx, uint32_t NMI_IT_Flag)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
	assert_param(IS_NMI_INTF(NMI_IT_Flag));

	SYSCONx->NMISR &= (uint32_t)(~NMI_IT_Flag);
}

/** 
  * @brief  外部复位脚RST功能开启/关闭
  * @param  SYSCONx: Select the SYSCONx peripheral.
  *     This parameter can be one of the following values: 
  *         SYSCON
  * @param  NewState: PE6脚的外部复位功能开启/关闭状态
  *     This parameter can be one of the following values: 
  *     @arg RSTPAD_ENABLE
  *     @arg RSTPAD_DISABLE
  * @retval None 
  */
void SYSCON_RSTPad_Config(SYSCON_TypeDef* SYSCONx, uint32_t RstPad_Set)
{
	/* Check the parameters */
	assert_param(IS_SYSCON_ALL_PERIPH(SYSCONx));
    assert_param(IS_RSTPAD_Config(RstPad_Set));
    
	/* Close lock */
    SYSCONx->UNLOCK  = SYSCON_UNLOCK_KEY;
    
    SYSCONx->RSTCTRL = RstPad_Set;

	/* Open lock */
	SYSCONx->UNLOCK = SYSCON_LOCK_KEY;
}

