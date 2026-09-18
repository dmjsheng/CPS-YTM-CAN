/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_lptim.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the LPTIMx peripheral registers to their default reset values.
  * @param  LPTIMx: Select the LPTIMx peripheral. 
  *         This parameter can be one of the following values: 
  *         LPTIM.
  * @retval None
  */
void LPTIM_DeInit(LPTIM_TypeDef* LPTIMx)
{
    /* Check the parameters */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    if (LPTIMx == LPTIM)
    {
        /* Enable LPTIMx reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LPTIM_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        
        /* Release LPTIMx from reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LPTIM_RST, DISABLE);
    }
}

/**
  * @brief  Read LPTIMx_CNTVA Lregister
  * @param  LPTIMx: Select the LPTIMx peripheral. 
  *         This parameter can be one of the following values: 
  *         LPTIM.
  * @retval the LPTIMx_CNTVAL register value
  */
uint32_t LPTIM_ReadCnt(LPTIM_TypeDef* LPTIMx)
{
	return ((uint32_t)(LPTIMx->CNTVAL));
}

/**
  * @brief  Initializes the LPTIMx Time Base Unit peripheral according to 
  *         the specified parameters in the LPTIM_InitStruct.
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  LPTIM_InitStruct: pointer to a LPTIM_InitTypeDef structure that contains 
  *         the configuration information for the LPTIMx peripheral.
  * @retval None
  */
void LPTIM_Init(LPTIM_TypeDef* LPTIMx, LPTIM_InitTypeDef * LPTIM_InitStruct)
{
    uint32_t tmpreg = 0;
    
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_MODE(LPTIM_InitStruct->worMode));
	assert_param(IS_LPTIM_CT(LPTIM_InitStruct->ct_mode_sel));
	assert_param(IS_TCK_SEL(LPTIM_InitStruct->tck_sel));
	assert_param(IS_LPTIM_GATE(LPTIM_InitStruct->gate_en));
	assert_param(IS_GATE_POLARITY(LPTIM_InitStruct->gatePolarity));
	assert_param(IS_LPTIM_TCK_EN(LPTIM_InitStruct->tck_en));
	
	/* read cr register */
	tmpreg = LPTIMx->CR;
	
    /* set mode1 or mode2 */
	tmpreg &= ~(uint32_t)LPTIM_Mode_MASK;    // mode1
	tmpreg |=  LPTIM_InitStruct->worMode;
	
	/* set Counter or Timer */
	tmpreg &= ~(uint32_t)LPTIM_CT_MASK;    // Timer  
	tmpreg |=  LPTIM_InitStruct->ct_mode_sel;
	
	/* set TCK */
	tmpreg &= ~(uint32_t)LPTIM_TCK_MASK;   // PCLK
	tmpreg |=  LPTIM_InitStruct->tck_sel;
	
	/* set GATE enable */
	tmpreg &= ~(uint32_t)LPTIM_GATE_MASK;  // Gate disable
	tmpreg |=  LPTIM_InitStruct->gate_en;
	
	/* set GATE Polarity */
	tmpreg &= ~(uint32_t)LPTIM_GATE_POLARITY_MASK;  // Gate Polarity is high
	tmpreg |=  LPTIM_InitStruct->gatePolarity;
	
	/* set TCLKEN */
	tmpreg &= ~(uint32_t)LPTIM_TCKEN_MASK;
	tmpreg |=  LPTIM_InitStruct->tck_en;
	
	LPTIMx->CR = tmpreg;
}

/**
  * @brief  Fills each LPTIM_InitStruct member with its default value.
  * @param  LPTIM_InitStruct: pointer to a LPTIM_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void LPTIM_StructInit(LPTIM_InitTypeDef* LPTIM_InitStruct)
{
    /* LPTIM_InitStruct members default value */
    LPTIM_InitStruct->worMode = LPTIM_MODE1;    // 无重载16位计数器/定时器
    LPTIM_InitStruct->ct_mode_sel = LPTIM_TIMER;  // 定时器模式
    LPTIM_InitStruct->tck_sel = TCK_SEL_PCLK;     // 时钟源PCLK
    LPTIM_InitStruct->gate_en = LPTIM_GATE_DISABLE;   // 禁止门控
    LPTIM_InitStruct->gatePolarity = GATE_Polarity_High;  // 门控高电平有效
    LPTIM_InitStruct->tck_en = LPTIM_TCK_DISABLE;    // 计数时钟禁止
}	

/**
  * @brief  Enable LPTIMx function
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  NewState: new state of the LPTIMx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_Cmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* set lptim run enable */
		LPTIMx->CR |= LPTIM_RUN_ENABLE;   // 定时器运行
	}
	else
	{
		/* set lptimer run disable */
		LPTIMx->CR &= ~(uint32_t)LPTIM_RUN_ENABLE;  // 定时器禁止
	}
}

/**
  * @brief  Enable LPTIMx TOG output function
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  NewState: new state of the LPTIMx peripheral. 
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_TogCmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* set lptimer run enable */
		LPTIMx->CR |= LPTIM_TOG_ENABLE;   // TOG,TOGN输出相位相反的信号
	}
	else
	{
		/* set lptimer run disable */
		LPTIMx->CR &= ~(uint32_t)LPTIM_TOG_ENABLE;  // TOG,TOGN同时输出0
	}
}

/**
  * @brief  Config LPTIMx Interrupt
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  NewState: new state of the LPTIMx peripheral. 
  * 	This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_ITConfig(LPTIM_TypeDef* LPTIMx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* set lptimer run enable */
		LPTIMx->CR |= LPTIM_IT_ENABLE;
	}
	else
	{
		/* set lptimer run disable */
		LPTIMx->CR &= ~(uint32_t)LPTIM_IT_ENABLE;
	}
}

/**
  * @brief  Gets the WT Flags of LPTIMx
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @retval The new state of FlagStatus (SET or RESET).
  */
FlagStatus LPTIM_GetWTFlagStatus(LPTIM_TypeDef* LPTIMx)
{
	FlagStatus bitstatus = RESET;
	
	/* Check the parameters*/
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	
	if ((LPTIMx->CR & LPTIM_WT_FLAG) != (uint16_t)RESET)
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
  * @brief  Config LPTIMx BGLOAD register
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  Value: Set value to BGLOAD register
  * @retval None
  */
void LPTIM_BGloadConfig(LPTIM_TypeDef* LPTIMx, uint32_t Value)
{
	__IO uint32_t counter = 0x00;
	uint32_t status = 0x00;
	
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_LPTIM_BGLOAD(Value));
	
	/* Wait till LPTIMx_CR.WT FLAG  be cleared zero */
	do
	{
		counter++;
		status = LPTIMx->CR & LPTIM_WT_FLAG;
	} while ((counter < 0xFFFFFFFFUL) && (status == LPTIM_WT_FLAG));
	
	/* set LPTIMx VALUE */
	LPTIMx->BGLOAD = Value;
}

/**
  * @brief  Config LPTIMx LOAD register
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  Value: Set value to LOAD register
  * @retval None
  */
void LPTIM_LoadConfig(LPTIM_TypeDef* LPTIMx, uint32_t Value)
{
	__IO uint32_t counter = 0x00;
	uint32_t status = 0x00;
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_LPTIM_LOAD(Value));

	/* Wait till LPTIMx WT FLAG  be cleared zero */
	do
	{
		counter++;
		status = LPTIMx->CR & LPTIM_WT_FLAG;
	} while ((counter < 0xFFFFFFFFUL) && (status == LPTIM_WT_FLAG));
	
	/* set LPTIMx VALUE */
	LPTIMx->LOAD = Value;
}

/**
  * @brief  Get LPTIMx ITStatus
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  IntFlag: LPTIMx interruption of flag   
  * 	This parameter can be: LPTIM_IT_FLAG.
  * @retval None
  */
ITStatus LPTIM_GetITStatus(LPTIM_TypeDef* LPTIMx, uint32_t IntFlag)
{
	ITStatus bitstatus = RESET;
	
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_LPTIM_IT(IntFlag));

	/* get the it flag */
	if ((LPTIMx->INTSR) & IntFlag)
	{
		bitstatus = SET;
	}
	else
	{
		bitstatus = RESET;
	}
	
	/* return the it flag */
	return bitstatus;
}

/**
  * @brief  Clear LPTIMx ITStatus flag
  * @param  LPTIMx: Selects the LPTIMx peripheral
  *         This parameter can be one of the following values: LPTIM
  * @param  IntFlag: LPTIMx interruption of flag
  * 	This parameter can be: LPTIM_IT_FLAG.
  * @retval None
  */
void LPTIM_ClearITFlag(LPTIM_TypeDef* LPTIMx, uint32_t IntFlag)
{
	/* Check the parameters */
	assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
	assert_param(IS_LPTIM_IT(IntFlag));

	/* Clear IT Flag */
	LPTIMx->INTCLR = IntFlag;
}

