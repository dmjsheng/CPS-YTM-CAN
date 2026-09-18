/*Includes -------------------------------------------------------------------*/
#include "cps32k21x_lvd.h"


/**
  * @brief  Deinitializes the LVD peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void LVD_DeInit(void)
{
    /* Enable LVD reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LVD_VC_OPA_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release LVD from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LVD_VC_OPA_RST, DISABLE);
}

/**
  * @brief  Initializes the LVDx peripheral according to the specified
  *         parameters in the LVD_InitStruct.
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  LVD_InitStruct: pointer to a LVD_InitTypeDef structure which will be initialized.       
  * @retval None
  */
void LVD_Init(LVD_TypeDef* LVDx, LVD_InitTypeDef* LVD_InitStruct)
{
    uint32_t tempreg = 0;
    
    /* Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
	assert_param(IS_TH_VOLTAGE_SEL(LVD_InitStruct->Th_Volage_sel));
    assert_param(IS_LVD_ACT(LVD_InitStruct->LVD_Act_sel));
    assert_param(IS_LVD_FLTCLK_SEL(LVD_InitStruct->filterClk_sel));
    assert_param(IS_LVD_FLT_EN(LVD_InitStruct->filter_EnStatus));
    assert_param(IS_LVD_TRIG(LVD_InitStruct->LVD_trigger_sel));

    /* read the value of LVD_CR register */
    tempreg = LVDx->CR;

    tempreg &= (uint32_t)(~TH_Voltage_SEL_Mask);  // threhold voltage 1.7v
    tempreg &= (uint32_t)(~LVD_ACT_MASK);         // interrupt
    tempreg &= (uint32_t)(~LVD_FLTCLK_SEL_MASK);  // filter clock invalid
    tempreg &= (uint32_t)(~LVD_FLT_ENABLE);       // filter disable
    tempreg &= (uint32_t)(~LVD_TRIG_SEL_Mask);    // trigger disable

    /*-------------------------- LVD_CR Configuration ------------------------*/
    tempreg |= (uint32_t)((LVD_InitStruct->Th_Volage_sel) |\
                          (LVD_InitStruct->LVD_Act_sel) |\
                          (LVD_InitStruct->filterClk_sel) |\
                          (LVD_InitStruct->filter_EnStatus) |\
                          (LVD_InitStruct->LVD_trigger_sel));
    
	/* set the value to LVD_CR register */
	LVDx->CR = tempreg;
}

/**
  * @brief  Fills each LVD_InitTypeDef member with its default value.
  * @param  LVD_InitStruct : pointer to a LVD_InitTypeDef structure which will be initialized.
  * @retval None
  */
void LVD_StructInit(LVD_InitTypeDef* LVD_InitStruct)
{
    LVD_InitStruct->filterClk_sel   = LVD_FLTCLK_SEL_Invalid;  // 滤波时钟无效
    LVD_InitStruct->filter_EnStatus = LVD_FLT_DISABLE;         // 滤波禁止
    LVD_InitStruct->LVD_Act_sel     = LVD_ACT_INTERRUPT;       // LVD Act为中断
    LVD_InitStruct->LVD_trigger_sel = LVD_TRIG_Disable;        // 禁止触发
    LVD_InitStruct->Th_Volage_sel   = TH_Voltage_SEL_2P7V;     // 默认阈值电压2.7V
}

/** 
  * @brief  Set LVDx threshold voltage level
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  SelVoltge: LVD threshold voltage
  *   This parameter can be one of the following values:
  *    @arg TH_Voltage_SEL_2P7V
  *    @arg TH_Voltage_SEL_3P3V
  *    @arg TH_Voltage_SEL_3P7V
  *    @arg TH_Voltage_SEL_4P1V
  * @retval None
  */
void LVD_Set_Th_Voltage(LVD_TypeDef* LVDx, uint32_t  SelVoltge)
{
	uint32_t tmgreg = 0;
	
	/* Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
	assert_param(IS_TH_VOLTAGE_SEL(SelVoltge));
	
	/* Read the value of lvd CR register */
	tmgreg = LVDx->CR;
	
    /* Reset the lvd voltage level bit to zero */
	tmgreg &= (uint32_t)(~TH_Voltage_SEL_Mask);
	
	/* Set the value of voltage level */
	tmgreg |= SelVoltge;
	
	/* set the value to LVD_CR register */
	LVDx->CR = tmgreg;
}

/** 
  * @brief  Enables or disable LVD function
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  NewState: new state of the LVDx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Cmd(LVD_TypeDef* LVDx, FunctionalState NewState)
{	
	/* Check the parameters */
	assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable the LVD function*/
		LVDx->CR &= (uint32_t)(~LVD_ENABLE);
	}
	else
	{  
		/* Disable the LVD function*/
		LVDx->CR |= LVD_ENABLE;
	} 
}

/** 
  * @brief  配置LVD中断/复位功能 
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  SelAct: LVD配置成中断方式还是复位方式
  *   This parameter can be one of the following values:
  *     @arg LVD_ACT_RESET
  *     @arg LVD_ACT_INTERRUPT
  * @retval None
  */
void LVD_Act_Config(LVD_TypeDef* LVDx, uint32_t SelAct)
{
    /*Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_LVD_ACT(SelAct));

	LVDx->CR &= (uint32_t)(~LVD_ACT_MASK);   // Act config to interrupt function
    LVDx->CR |= SelAct;
}

/** 
  * @brief  Enable the LVD Filter Function
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  NewState: new state of the filter enable. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Filter_Cmd(LVD_TypeDef* LVDx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Open the filter function */
		LVDx->CR |= LVD_FLT_ENABLE;
    }
	else
    {
		/* Close the filter function */
		LVDx->CR &= (uint32_t)(~LVD_FLT_ENABLE);
    }
}

/** 
  * @brief  Set the filter clock function
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  FltClk: the clock source of filter
  *   This parameter can be one of the following values: 
  *     @arg LVD_FLTCLK_SEL_Invalid
  *     @arg LVD_FLTCLK_SEL_PCLK
  *     @arg LVD_FLTCLK_SEL_LIRC
  * @retval None
  */
void LVD_Set_FilterClk(LVD_TypeDef* LVDx, uint32_t FltClk)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_LVD_FLTCLK_SEL(FltClk));
	
	LVDx->CR &= (uint32_t)(~LVD_FLTCLK_SEL_MASK);
	
	/* Select filter clock source */
	LVDx->CR |= FltClk;
}

/** 
  * @brief  Set filter number 
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  FltNum: Selects the LVD filter parameter
  * @retval None
  */
void LVD_Set_FilterNum(LVD_TypeDef* LVDx, uint32_t FltNum)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_FLT_NUM(FltNum));
    
    LVDx->CR &= (uint32_t)(~LVD_FLT_NUM_Mask);
    LVDx->CR |= (uint32_t)(FltNum << 16);
}

/** 
  * @brief  配置LVD触发方式
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  TriggerSel: 选择LVD触发方工
  *   This parameter can be one of the following values:
  *     @arg LVD_TRIG_Disable
  *     @arg LVD_TRIG_FallingEdge
  *     @arg LVD_TRIG_RisingEdge
  *     @arg LVD_TRIG_BothEge
  *     @arg LVD_TRIG_HighLevel
  * @retval None
  */
void LVD_Trigger_Config(LVD_TypeDef* LVDx, uint32_t TriggerSel)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_LVD_TRIG(TriggerSel));

	LVDx->CR &= (uint32_t)(~LVD_TRIG_SEL_Mask);
	LVDx->CR |= TriggerSel;
}

/** 
  * @brief  Enable or disable LVDx interrupt function.
  * @param  LVDx: selects the LVDx peripheral
  *    This parameter can be one of the following values: 
  *       LVD
  * @param  NewState: new state of the LVDx interrupt function. 
  *    This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ITConfig(LVD_TypeDef* LVDx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable LVD interrupt function */
		LVDx->CR |= LVD_IT_ENABLE;
    }
	else
    {
        /* Disable LVD interrupt function */
        LVDx->CR &= (uint32_t)(~LVD_IT_ENABLE);
    }
}

/**
  * @brief  Checks whether the interrupt flag is set or not.
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @param  LVD_FLAG: LVD interrupt flag
  *   This paramter can be one of the following vlaues:
  *     @arg LVD_IT_INTF
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus LVD_GetFlagStatus(LVD_TypeDef* LVDx, uint32_t LVD_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    
    if (((LVDx->SR) & LVD_FLAG) != (uint32_t)RESET)
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
  * @param  LVDx: selects the LVDx peripheral
  *   This parameter can be one of the following values: 
  *       LVD
  * @retval None
  */
void LVD_ClearITFlag(LVD_TypeDef* LVDx)
{
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));
    
    /* Clear the LVD interrupt flag */
    LVDx->SR &= ((uint32_t)0xFE);
}

/**
  * @brief  读取LVD的输出状态
  * @param  LVDx: selects the LVDx peripheral
  * This parameter can be one of the following values: 
  *       LVD
  * @retval 返回LVD的输出状态 (SET or RESET)
  */
FlagStatus LVD_Read_Result(LVD_TypeDef* LVDx)
{
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_LVD_ALL_PERIPH(LVDx));  

    if (((LVDx->SR) & ((uint32_t)0x02)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }

    return bitstatus;
}

