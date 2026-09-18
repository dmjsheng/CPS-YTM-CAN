/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_timer.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: Select the TIM peripheral 
  * 	This parameter can be one of the following values: TMER10, TMER11.
  * @retval None
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx)); 

	if ((TIMx == TIM10) || (TIMx == TIM11))
	{
		/* Enable TIMX reset state */
		RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BASETIM_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

        /*Release TIMX from reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BASETIM_RST, DISABLE);
	}     
}

/**
  * @brief  Initializes the TIMx Timer Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: Select the TIM peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the 
  *         specified TIMx peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
	uint32_t tmpreg = 0;
	
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx)); 
	assert_param(IS_TIM_GATE_POLARITY_STATE(TIM_TimeBaseInitStruct->Gate_Polarity));
	assert_param(IS_GATE_STATE(TIM_TimeBaseInitStruct->GateState));
	assert_param(IS_TIM_CT_MODE(TIM_TimeBaseInitStruct->CounterMode));
	assert_param(IS_TIM_TMRMS(TIM_TimeBaseInitStruct->TmrModeSel));
	assert_param(IS_TIM_TMRSZ(TIM_TimeBaseInitStruct->TmrSize));
	assert_param(IS_TIM_TMROS(TIM_TimeBaseInitStruct->TmrOneShort));
	assert_param(IS_TIM_PRESCALE_DIV(TIM_TimeBaseInitStruct->ClockDivision));

	TIMx->CR &= ~(uint32_t)TMRxCR_MASK;   // TIMx Stop, TOG,TOGN同时输出0
	
	/* Control register value Initialization */
    tmpreg	= (TIM_TimeBaseInitStruct->Gate_Polarity) |\
	        	(TIM_TimeBaseInitStruct->GateState) |\
	        	(TIM_TimeBaseInitStruct->TmrSize) |\
	        	(TIM_TimeBaseInitStruct->TmrModeSel) |\
            	(TIM_TimeBaseInitStruct->CounterMode) |\
	        	(TIM_TimeBaseInitStruct->TmrOneShort) |\
            	(TIM_TimeBaseInitStruct->ClockDivision);

    TIMx->CR = tmpreg;           
}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TimeBaseInitStruct : pointer to a TIM_TimeBaseInitTypeDef structure which will be initialized.
  * @retval None
  */
void TIM_StructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
	TIM_TimeBaseInitStruct->Gate_Polarity = TIM_GATE_Polarity_High;  /*<! 门控极性为高电平 */
	TIM_TimeBaseInitStruct->GateState     = TIM_GATE_DISABLE;        /*<! 门控关闭 */
	TIM_TimeBaseInitStruct->CounterMode   = TIM_CT_TIMER;            /*<! 默认为定时模式 */
	TIM_TimeBaseInitStruct->TmrModeSel    = TIM_Mode1_FreeRun;       /*<! 自由运行模式 */
	TIM_TimeBaseInitStruct->TmrSize       = TIM_TMRSIZE_16BIT;       /*<! 定时器位数，默认16位 */
	TIM_TimeBaseInitStruct->TmrOneShort   = TIM_TMROS_REPEAT;        /*<! TIMx重复运行 */
	TIM_TimeBaseInitStruct->ClockDivision = TIM_Prescale_DIV1;       /*<! TIMx预分频，1分频 */
}

/**
  * @brief  Enables or disables the specified TIMx peripheral run function.
  * @param  TIMx: Select the TIM peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  NewState: new state of the TIMx peripheral.
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState)); 

	if (NewState != DISABLE)
	{
		/* Enable the TIM Counter */
		TIMx->CR |=  TIM_TR_ENABLE;
	}
	else
	{
		/* Disable the TIM Counter */
		TIMx->CR &= ~TIM_TR_ENABLE;
	}
}

/**
  * @brief  Enables or disables the specified TIMx peripheral TOG output function.
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  NewState: new state of the TIMx peripheral.
  * 	This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_TogCmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable the TIM TOG Function */
		TIMx->CR |=  TIM_TOG_EN;
	}
	else
	{
		/* Disable the TIM TOG Function */
		TIMx->CR &= ~TIM_TOG_EN;
	}
}

/**
  * @brief  Enables or disables the specified TIMx interrupts.
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  NewState: new state of the specifies the TIMx interrupts sources.
  * 	This parameter can be: ENABLE or DISABLE.
  */
void TIM_ITConfig(TIM_TypeDef* TIMx,  FunctionalState NewState)
{  
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable the Interrupt sources */
		TIMx->CR |=  TIM_IT_ENABLE;
	}
	else
	{
		/* Disable the Interrupt sources */
		TIMx->CR &= ~TIM_IT_ENABLE;
	}
}

/**
  * @brief  Config TIMx to the specified Mode/配置TIMx为定时模式还是计数模式  
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_CounterMode: specifies the Counter Mode or Timer Mode.
  * 	This parameter can be one of the following values:
  *		@arg TIM_CT_TIMER
  *		@arg TIM_CT_COUNTER
  * @retval None
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_CT_MODE(MODE));
	
	/* Clear function bit to zero */
	TIMx->CR &= ~TIM_CT_COUNTER; 

	/* Set the specifies the Mode */
	TIMx->CR |=  TIM_CounterMode; 
}

/**
  * @brief  Select TIMx Gate Polarity
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_GatePolarity: The Input Gate Polarity .
  * 	This parameter can be one of the following values:
  *     @arg TIM_GATE_Polarity_High
  *     @arg TIM_GATE_Polarity_Low         
  * @retval None 
  */
void TIM_SelectGatePolarity(TIM_TypeDef* TIMx, uint32_t TIM_GatePolarity)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_GATE_POLARITY_STATE(TIM_GatePolarity));
	
	/* Clear function bit to zero */
	TIMx->CR &= ~TIM_GATE_Polarity_Low; 

	/* Set the specifies the Gate polarity */
	TIMx->CR |=  TIM_GatePolarity;
}

/**
  * @brief  Sets the TIMx Clock Division value.
  * @param TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_Div: specifies the clock division value.
  * 	This parameter can be one of the following value:
  *     	@arg TIM_Prescale_DIV1
  *     	@arg TIM_Prescale_DIV2
  *     	@arg TIM_Prescale_DIV4
  *     	@arg TIM_Prescale_DIV8
  *     	@arg TIM_Prescale_DIV16
  *     	@arg TIM_Prescale_DIV32
  *     	@arg TIM_Prescale_DIV64
  *     	@arg TIM_Prescale_DIV128
  * @retval None
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_Div)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	assert_param(IS_TIM_PRESCALE_DIV(TIM_Div));
	
	/* Reset the TIMx DIV Bits */
	TIMx->CR &= ~(uint32_t)TIM_Prescale_DIV128;
	
	/* Set the TIMx Div value */
	TIMx->CR |=  TIM_Div;
}

/**
  * @brief Gets the TIMx Prescaler value.
  * @param TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @retval Prescaler Register value.
  */
uint8_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/* Get the Prescaler Register value */
	return (uint8_t)(TIMx->CR & ((uint32_t)(0x07)));
}

/**
  * @brief  Set Timer Load Register value, Load Register and BGLoad Register value
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_Value: Set to the LOAD/BGLOAD register of value
  * @retval None.
  */
void TIM_SetTimerLoadRegister(TIM_TypeDef* TIMx, uint32_t TIM_Value)
{
	/* Check the parameters */
    assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/* Set the value to the Load register */
	TIMx->LOAD = (uint32_t)TIM_Value; 
	
	/* Set the value to the BGLoad register */
	TIMx->BGLOAD = (uint32_t)TIM_Value; 
}

/**
  * @brief  Set Timer BGLoad Register value
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_Value: Set to the BGLOAD register of value
  * @retval None.
  */
void TIM_SetTimerAutoReload(TIM_TypeDef* TIMx, uint32_t reloadValue)
{
	/* Check the parameters */
    assert_param(IS_BASETIM_ALL_PERIPH(TIMx));
	
	/* Set the value to the BGLoad register */
	TIMx->BGLOAD = reloadValue; 
}

/**
  * @brief  Gets the Timer Load Register's value
  * @param  TIMx: Select the TIMx peripheral 
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @retval Counter Register value.
  */
uint32_t TIM_GetTimerLoadRegister(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));

	/* Get the Timer Load Register value */
	return (TIMx->LOAD);
}

/**
  * @brief  Gets the Timer count Register's value
  * @param  TIMx: Select the TIMx peripheral
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @retval Counter Register value.
  */
uint32_t TIM_GetCounterRegister(TIM_TypeDef* TIMx)
{
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));

	/* Get the Counter Register value */
	return (uint32_t)(TIMx->CNT); 
}

/**
  * @brief  获取原始中断状态，不论中断是否使能，均可读取
  * @param  TIMx: Select the TIMx peripheral
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_RawFlag: 中断原始状态
  * 	This parameter can be one of the following values: 
  *     	@arg TIM_IT_FLAG
  * @retval  The new state of TIM_ITFLAG (SET or RESET). 
  */
ITStatus TIM_Get_RawIT_Flag(TIM_TypeDef* TIMx, uint32_t TIM_RawFlag)
{ 
	ITStatus bitstatus = RESET;  

	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));

	if ((TIMx->RAWINTSR & TIM_RawFlag) != 0)
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
  * @brief  获取中断标志状态, 需要使能中断控才能读取中断标志
  * @param  TIMx: Select the TIMx peripheral
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_MskFlag: IT Flag Status.
  * 	This parameter can be one of the following values: 
  *     	@arg TIM_IT_FLAG
  * @retval The new state of TIM_ITFLAG (SET or RESET).
  */
ITStatus TIM_Get_MskIT_Flag(TIM_TypeDef* TIMx, uint32_t TIM_MskFlag)
{ 
	ITStatus bitstatus = RESET;  

	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));

	if ((TIMx->MSKINTSR & TIM_MskFlag) != 0)
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
  * @brief  Clear the IT Flag 
  * @param  TIMx: Select the TIMx peripheral
  * 	This parameter can be one of the following values: TIM10, TIM11.
  * @param  TIM_ITFLAG: The state of TIM_ITFLAG
  * This parameter can be one of the following values: 
  *     @arg TIM_IT_FLAG
  */
void TIM_ClearITFlag(TIM_TypeDef* TIMx, uint32_t TIM_IT_Flag)
{  
	/* Check the parameters */
	assert_param(IS_BASETIM_ALL_PERIPH(TIMx));

	/* Clear the flags */
	TIMx->INTCLR = TIM_IT_Flag;
}

