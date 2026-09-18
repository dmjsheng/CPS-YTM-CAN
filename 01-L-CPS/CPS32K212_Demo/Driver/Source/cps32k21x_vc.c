/*Includes -------------------------------------------------------------------*/
#include "cps32k21x_vc.h"


/**
  * @brief  Deinitializes the VC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void VC_DeInit(void)
{
    /* Enable VC reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LVD_VC_OPA_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release VC from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_LVD_VC_OPA_RST, DISABLE);
}

/**
  * @brief  Fills each VC_InitStruct member with its default value.
  * @param  VC_InitStruct : pointer to a VC_InitTypeDef
  *         structure which will be initialized.
  * @retval None
  */	
void VC_StructInit(VC_InitTypeDef* VC_InitStruct)	
{	
    /* Set the default configuration */
    VC_InitStruct->dac_vref_sel     = VC_DAC_VREF_SEL_AVDD;   /* DAC参考电压源 */
    VC_InitStruct->dac_div_sel      = 0;                      /* DAC分频选择：1/64 Vref */
    VC_InitStruct->dac_EnStatus     = VC_DAC_DISABLE;         /* DAC使能状态 */
    VC_InitStruct->hyst_voltage_sel = VC_HYST_VOLT_0MV;       /* VC迟滞电压 */
    VC_InitStruct->NinSel           = VC_INNSEL_VC_INN0;      /* VC反相端输入信号源 */
    VC_InitStruct->PinSel           = VC_INPSEL_VC_INP0;      /* VC同相端输入信号源 */
    VC_InitStruct->filterClk_sel    = VC_FLTCLK_SEL_Invalid;  /* VC滤波时钟源选择 */
    VC_InitStruct->filter_EnStatus  = VC_FILTER_DISABLE;      /* VC数字滤波使能状态 */
    VC_InitStruct->trigger_sel      = VC_TRIG_SEL_DISABLE;    /* VC触发方式选择 */
}

/** 
  * @brief  Initializes the VCx peripheral according to the specified
  *         parameters in the VC_InitStruct.
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  VC_InitStruct: pointer to a VC_InitTypeDef structure which will
  *         be initialized.       
  * @retval None
  */
void VC_Init(VC_TypeDef* VCx, VC_InitTypeDef* VC_InitStruct)
{
    uint32_t tmpvccsr = 0;
    uint32_t tmpvccr = 0;
    
    /* Check the parameters */
    assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_DAC_VREF(VC_InitStruct->dac_vref_sel));
    assert_param(IS_VC_DAC_EN(VC_InitStruct->dac_EnStatus));
    assert_param(IS_VC_HYST_VOLT(VC_InitStruct->hyst_voltage_sel));
    assert_param(IS_VC_NinSEL(VC_InitStruct->NinSel));
    assert_param(IS_VC_PinSEL(VC_InitStruct->PinSel));
    assert_param(IS_VC_FLTCLK(VC_InitStruct->filterClk_sel));
    assert_param(IS_VC_FILTER_EN(VC_InitStruct->filter_EnStatus));
    assert_param(IS_VC_TRIG(VC_InitStruct->trigger_sel));

    /* read the value of VC_CSR register */
    tmpvccsr = VCx->CSR;

    tmpvccsr &= (uint32_t)(~VC_DAC_VREF_SEL_2V4V); // DAC Vref: AVDD
    tmpvccsr &= (uint32_t)(~VC_DAC_ENABLE);        // DAC Disable
    tmpvccsr &= (uint32_t)(~VC_DAC_DIV_Mask);      // 6'b000000： 1/64 Vref
    tmpvccsr &= (uint32_t)(~VC_HYST_VOLT_Mask);    // HTST Volt: 0mV

    tmpvccsr |= VC_InitStruct->dac_vref_sel;   // 设置DAC参考电压
    tmpvccsr |= VC_InitStruct->dac_EnStatus;   // 设置DAC使能状态
    
    if (VC_InitStruct->dac_div_sel > 0x3FUL)
    {
        tmpvccsr |= (uint32_t)(0x3FUL << 8);  // 防止溢出
    }
    else
    {
        tmpvccsr |= (uint32_t)(VC_InitStruct->dac_div_sel << 8);
    }
    
    tmpvccsr |= VC_InitStruct->hyst_voltage_sel; // 迟滞电压选择
    
    /* VC反相端输入选择 */
    tmpvccsr &= (uint32_t)(~VC_INNSEL_Mask);
    tmpvccsr |= VC_InitStruct->NinSel;

    /* VC同相端输入选择 */
    tmpvccsr &= (uint32_t)(~VC_INPSEL_Mask);
    tmpvccsr |= VC_InitStruct->PinSel;
    
    VCx->CSR = tmpvccsr;  // write VC_CSR register
    
    /* read the value of VC_CR register */
    tmpvccr = VCx->CR;

    tmpvccr &= (uint32_t)(~VC_FLTCLK_Mask);    // 滤波时钟Invalid
    tmpvccr &= (uint32_t)(~VC_FILTER_ENABLE);  // 禁止数字滤波
    tmpvccr &= (uint32_t)(~VC_TRIG_SEL_Mask);  // 触发Disable
    
    tmpvccr |= VC_InitStruct->filterClk_sel;   // 滤波时钟选择
    tmpvccr |= VC_InitStruct->filter_EnStatus; // 设置滤波使能状态
    tmpvccr |= VC_InitStruct->trigger_sel;     // 触发选择
    VCx->CR = tmpvccr;  // write VC_CR register
}

/** 
  * @brief  VC比较器同相端输入源配置
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  PinSel: VC比较器同相端输入源
  *   This parameter can be one of the following values: 
  *    @arg VC_INPSEL_VC_INP0
  *    @arg VC_INPSEL_VC_INP1
  *    @arg VC_INPSEL_VC_INP2
  *    @arg VC_INPSEL_PGA_OUT
  * @retval None
  */
void VC_PinSel_Config(VC_TypeDef* VCx, uint32_t PinSel)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_PinSEL(PinSel));
	
	/* Set Pin Mask */
	VCx->CSR &= (uint32_t)(~VC_INPSEL_Mask);
	
	/* Set Pin */
	VCx->CSR |= PinSel;	
}

/** 
  * @brief  VC比较器反相端输入源配置
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NinSel: VC比较器反相端输入源
  *   This parameter can be one of the following values: 
  *    @arg VC_INNSEL_VC_INN0
  *    @arg VC_INNSEL_VC_INN1
  *    @arg VC_INNSEL_VC_INN2
  *    @arg VC_INNSEL_VC_INN3
  *    @arg VC_INNSEL_2V4V
  *    @arg VC_INNSEL_1V
  *    @arg VC_INNSEL_DAC_OUT
  * @retval None
  */
void VC_NinSel_Config(VC_TypeDef* VCx, uint32_t NinSel)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_NinSEL(NinSel));
	
	/* Set Nin Mask */
	VCx->CSR &= (uint32_t)(~VC_INNSEL_Mask);
	
	/* Set Nin */
	VCx->CSR |= NinSel;	
}

/** 
  * @brief  设置DAC输出电压分压值
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  DAC_Div: config parameters, <=0x3F
  * @retval None
  */
void VC_Set_DAC_Div(VC_TypeDef* VCx, uint32_t DAC_Div)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_DAC_DIV(DAC_Div));
	
	VCx->CSR &= (uint32_t)(~VC_DAC_DIV_Mask);
	if (DAC_Div > 0x3FUL)
	{
	    VCx->CSR |= (uint32_t)(0x3FUL << 8);	
	}
	else
	{
	    VCx->CSR |= (uint32_t)(DAC_Div << 8);	
	}
}

/** 
  * @brief  使能/禁止6 bit DAC功能
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: new state of the DAC 
  *   This parameter can be: ENABLE or DISABLE.
  *   ENABLE  : 使能6 bit DAC
  *   DISABLE : 禁止6 bit DAC
  * @retval None
  */
void VC_DAC_Cmd(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable DAC */
		VCx->CSR |= VC_DAC_ENABLE;
    }
	else
    {
		/* Disable DAC */
		VCx->CSR &= (uint32_t)(~VC_DAC_ENABLE);  
    }
}

/** 
  * @brief  DAC参考电压源选择设置
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  Vref: DAC参考电压源选择值
  *   This parameter can be one of the following values:
  *    @arg VC_DAC_VREF_SEL_2V4V
  *    @arg VC_DAC_VREF_SEL_AVDD
  * @retval None
  */
void VC_DAC_Vref_Config(VC_TypeDef* VCx, uint32_t Vref)
{
    /* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_DAC_VREF(Vref));

    VCx->CSR &= (uint32_t)(~VC_DAC_VREF_SEL_2V4V);  // AVDD
    VCx->CSR |= Vref;
}

/** 
  * @brief  VC比较器迟滞电压配置
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  HystVolt: VC比较器的迟滞电压设定值
  *   This parameter can be one of the following values:
  *    @arg VC_HYST_VOLT_0MV
  *    @arg VC_HYST_VOLT_10MV
  *    @arg VC_HYST_VOLT_20MV
  *    @arg VC_HYST_VOLT_30MV
  * @retval None
  */
void VC_Hyst_Voltage_Config(VC_TypeDef* VCx, uint32_t HystVolt)
{
    /* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_HYST_VOLT(HystVolt));

    VCx->CSR &= (uint32_t)(~VC_HYST_VOLT_Mask);
    VCx->CSR |= HystVolt;
}

/** 
  * @brief  使能/禁止比较器模块
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: new state of the VCx.
  *   This parameter can be: ENABLE or DISABLE.
  *     ENABLE  : 使能VC比较器模块
  *     DISABLE : 禁止VC比较器模块
  * @retval None
  */
void VC_Cmd(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable VC function */
		VCx->CR |= VC_ENABLE;
    }
	else
    {
		/* Disable VC function */
		VCx->CR &= (uint32_t)(~VC_ENABLE);   
    }
}

/** 
  * @brief  配置VC数字滤波时钟源
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  FltClk: the clock source of filter
  *   This parameter can be one of the following values:
  *     @arg VC_FLTCLK_SEL_Invalid
  *     @arg VC_FLTCLK_SEL_PCLK
  *     @arg VC_FLTCLK_SEL_LIRC
  * @retval None
  */
void VC_SetFilterClk(VC_TypeDef* VCx, uint32_t FltClk)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_FLTCLK(FltClk));
	
	/* Set filter clock source */
	VCx->CR &= (uint32_t)(~VC_FLTCLK_Mask);
	VCx->CR |= FltClk;
}

/** 
  * @brief  使能/禁止VC数字滤波功能
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: VC数字滤波使能状态
  *   This parameter can be: ENABLE or DISABLE.
  *       ENABLE  : 使能数字滤波
  *       DISABLE : 禁止数字滤波
  * @retval None
  */
void VC_Filter_Cmd(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable digital filter function */
		VCx->CR |= VC_FILTER_ENABLE;
    }
	else
    {
		/* Disable digital filter function */
		VCx->CR &= (uint32_t)(~VC_FILTER_ENABLE); 
    }
}

/** 
  * @brief  设置VC采样滤波次数
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  FltNum: 要设置的采样滤滤次数 
  *   This parameter can be one of the following values:
  *     @arg VC_FLTNUM_1_FLTCLK
  *     @arg VC_FLTNUM_2_FLTCLK
  *     @arg VC_FLTNUM_4_FLTCLK
  *     @arg VC_FLTNUM_8_FLTCLK
  *     @arg VC_FLTNUM_16_FLTCLK
  *     @arg VC_FLTNUM_32_FLTCLK
  *     @arg VC_FLTNUM_64_FLTCLK
  *     @arg VC_FLTNUM_128_FLTCLK
  * @retval None
  */
void VC_SetFltNum(VC_TypeDef* VCx, uint32_t FltNum)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_FLTNUM(FltNum));
	
	/* Set the flt parameters */
	VCx->CR &= (uint32_t)(~VC_FLTNUM_Mask);
	VCx->CR |= FltNum;
}

/** 
  * @brief 配置VC触发方式
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param TriggerSel: VC触发方式  
  *    This parameter can be one of the following values:
  *     @arg VC_TRIG_SEL_DISABLE
  *     @arg VC_TRIG_SEL_FallingEdge
  *     @arg VC_TRIG_SEL_RisingEdge
  *     @arg VC_TRIG_SEL_HighLevel
  * @retval None
  */
void VC_Trigger_Config(VC_TypeDef* VCx, uint32_t TriggerSel)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_VC_TRIG(TriggerSel));

	VCx->CR &= (uint32_t)(~VC_TRIG_SEL_Mask);
	VCx->CR |= TriggerSel;
}

/** 
  * @brief  Enable or disable VCx interrupt function
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: new state of the VCx interrupt. 
  *   This parameter can be: ENABLE or DISABLE.
  *       ENABLE  : VC中断使能
  *       DISABLE : VC中断禁止
  * @retval None
  */
void VC_ITConfig(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable VC interrupt */
		VCx->CR |= VC_IT_ENABLE;
    }
	else
    {
		/* Disable VC interrupt */
	    VCx->CR &= (uint32_t)(~VC_IT_ENABLE);
    }
}

/**
  * @brief  Checks whether the interrupt flag is set or not.
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  VC_FLAG: VCx interrupt flag
  *   This paramter can be one of the following vlaues:
  *     @arg VC_IT_INTF
  * @retval The new state of the VCx interrupt flag (SET or RESET)
  */
FlagStatus VC_GetFlagStatus(VC_TypeDef* VCx, uint32_t VC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_VC_ALL_PERIPH(VCx));
    
    if (((VCx->SR) & VC_FLAG) != (uint32_t)RESET)
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
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @retval None
  */
void VC_ClearITFlag(VC_TypeDef* VCx)
{
    /* Check the parameters */
    assert_param(IS_VC_ALL_PERIPH(VCx));
    
    /* Clear the VCx interrupt flag */
    VCx->SR &= ((uint32_t)0xFE);
}

/**
  * @brief  读取VC模块输出值
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @retval 返回VC模块输出值 (SET or RESET)
  */
FlagStatus VC_Read_Result(VC_TypeDef* VCx)
{
    FlagStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_VC_ALL_PERIPH(VCx));

    if (((VCx->SR) & ((uint32_t)0x02)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }

    return bitstatus;
}

/** 
  * @brief  Enable or disable output config function
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  OutCfgType: VCx输出到其他外设控制
  *   This parameter can be one of the following values:
  *     @arg VC_INVPAD_EN            
  *     @arg VC_INT_ETIME_TIM2_BKE_EN  
  *     @arg VC_ETIMER_TIM2_CH4_EN          
  *     @arg VC_ETIMER_CH4_INV_EN      
  *     @arg VC_ETIMER_TIM2_CH3_EN        
  *     @arg VC_ETIMER_CH3_INV_EN     
  *     @arg VC_ETIMER_TIM2_CH2_EN         
  *     @arg VC_ETIMER_CH2_INV_EN   
  *     @arg VC_ETIMER_TIM2_CH1_EN    
  *     @arg VC_ETIMER_CH1_INV_EN  
  *     @arg VC_LPTIMEXT_EN          
  *     @arg VC_LPTIM_GATE_EN         
  *     @arg VC_TIM11_GATE_EN           
  *     @arg VC_TIM10_GATE_EN          
  *     @arg VC_BTIM_LPTIM_GATE_INV_EN         
  * @param  NewState: VCx输出到其他外设控制状态 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void VC_OutConfig_Cmd(VC_TypeDef* VCx, uint32_t OutCfgType, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        switch (OutCfgType)
        {
            case VC_INVPAD_EN:               VCx->OUTCFG |= VC_INVPAD_EN;              break; 
            case VC_INT_ETIME_TIM2_BKE_EN:   VCx->OUTCFG |= VC_INT_ETIME_TIM2_BKE_EN;  break;
            case VC_ETIMER_TIM2_CH4_EN:      VCx->OUTCFG |= VC_ETIMER_TIM2_CH4_EN;     break; 
            case VC_ETIMER_CH4_INV_EN:       VCx->OUTCFG |= VC_ETIMER_CH4_INV_EN;      break;
            case VC_ETIMER_TIM2_CH3_EN:      VCx->OUTCFG |= VC_ETIMER_TIM2_CH3_EN;     break;
            case VC_ETIMER_CH3_INV_EN:       VCx->OUTCFG |= VC_ETIMER_CH3_INV_EN;      break;
            case VC_ETIMER_TIM2_CH2_EN:      VCx->OUTCFG |= VC_ETIMER_TIM2_CH2_EN;     break;
            case VC_ETIMER_CH2_INV_EN:       VCx->OUTCFG |= VC_ETIMER_CH2_INV_EN;      break;
            case VC_ETIMER_TIM2_CH1_EN:      VCx->OUTCFG |= VC_ETIMER_TIM2_CH1_EN;     break;
            case VC_ETIMER_CH1_INV_EN:       VCx->OUTCFG |= VC_ETIMER_CH1_INV_EN;      break;
            case VC_LPTIMEXT_EN:             VCx->OUTCFG |= VC_LPTIMEXT_EN;            break;
            case VC_LPTIM_GATE_EN:           VCx->OUTCFG |= VC_LPTIM_GATE_EN;          break;
            case VC_TIM11_GATE_EN:           VCx->OUTCFG |= VC_TIM11_GATE_EN;          break;
            case VC_TIM10_GATE_EN:           VCx->OUTCFG |= VC_TIM10_GATE_EN;          break;
            case VC_BTIM_LPTIM_GATE_INV_EN:  VCx->OUTCFG |= VC_BTIM_LPTIM_GATE_INV_EN; break;
            default: break;
        }
    }
    else
    {
        switch (OutCfgType)
        {
            case VC_INVPAD_EN:               VCx->OUTCFG &= (uint32_t)(~VC_INVPAD_EN);              break; 
            case VC_INT_ETIME_TIM2_BKE_EN:   VCx->OUTCFG &= (uint32_t)(~VC_INT_ETIME_TIM2_BKE_EN);  break;
            case VC_ETIMER_TIM2_CH4_EN:      VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_TIM2_CH4_EN);     break; 
            case VC_ETIMER_CH4_INV_EN:       VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_CH4_INV_EN);      break;
            case VC_ETIMER_TIM2_CH3_EN:      VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_TIM2_CH3_EN);     break;
            case VC_ETIMER_CH3_INV_EN:       VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_CH3_INV_EN);      break;
            case VC_ETIMER_TIM2_CH2_EN:      VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_TIM2_CH2_EN);     break;
            case VC_ETIMER_CH2_INV_EN:       VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_CH2_INV_EN);      break;
            case VC_ETIMER_TIM2_CH1_EN:      VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_TIM2_CH1_EN);     break;
            case VC_ETIMER_CH1_INV_EN:       VCx->OUTCFG &= (uint32_t)(~VC_ETIMER_CH1_INV_EN);      break;
            case VC_LPTIMEXT_EN:             VCx->OUTCFG &= (uint32_t)(~VC_LPTIMEXT_EN);            break;
            case VC_LPTIM_GATE_EN:           VCx->OUTCFG &= (uint32_t)(~VC_LPTIM_GATE_EN);          break;
            case VC_TIM11_GATE_EN:           VCx->OUTCFG &= (uint32_t)(~VC_TIM11_GATE_EN);          break;
            case VC_TIM10_GATE_EN:           VCx->OUTCFG &= (uint32_t)(~VC_TIM10_GATE_EN);          break;
            case VC_BTIM_LPTIM_GATE_INV_EN:  VCx->OUTCFG &= (uint32_t)(~VC_BTIM_LPTIM_GATE_INV_EN); break;
            default: break;
        }
    }
}

/** 
  * @brief  设置PGA偏置电压Offset
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  OffsetVolt: Offset voltage
  *   This parameter can be one of the following values:
  *     @arg VC_PGA_OffsetVolt_None1
  *     @arg VC_PGA_OffsetVolt_ADD_3mV
  *     @arg VC_PGA_OffsetVolt_ADD_6mV
  *     @arg VC_PGA_OffsetVolt_ADD_9mV
  *     @arg VC_PGA_OffsetVolt_None2
  *     @arg VC_PGA_OffsetVolt_DEC_9mV
  *     @arg VC_PGA_OffsetVolt_DEC_6mV
  *     @arg VC_PGA_OffsetVolt_DEC_3mV
  * @retval None
  */
void VC_PGA_OffsetVolt_Set(VC_TypeDef* VCx, uint32_t OffsetVolt)
{
    /* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
	assert_param(IS_VC_PGA_OffsetVolt(OffsetVolt));

	VCx->PGACR &= (uint32_t)(~VC_PGA_OffsetVolt_Mask);
	VCx->PGACR |= OffsetVolt;
}

/** 
  * @brief  使能/禁止VC模块之PGA功能
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: new state of the VCx.
  *   This parameter can be: ENABLE or DISABLE.
  *     ENABLE  : VC模块之PGA使能
  *     DISABLE : VC模块之PGA禁止
  * @retval None
  */
void VC_PGA_Cmd(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable VC function */
		VCx->PGACR |= VC_PGA_ENABLE;
    }
	else
    {
		/* Disable VC function */
		VCx->PGACR &= (uint32_t)(~VC_PGA_ENABLE);   
    }
}

/** 
  * @brief  使能/禁止VC模块之PGA内部LOOP电路功能
  * @param  VCx: selects the VCx peripheral
  *   This parameter can be one of the following values: 
  *       VC
  * @param  NewState: new state of the VCx.
  *   This parameter can be: ENABLE or DISABLE.
  *     ENABLE  : VC模块之PGA内部LOOP使能
  *     DISABLE : VC模块之PGA内部LOOP禁止
  * @retval None
  */
void VC_PGA_Loop_Cmd(VC_TypeDef* VCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_VC_ALL_PERIPH(VCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
    {
		/* Enable VC function */
		VCx->PGACR |= VC_PGA_LOOP_ENABLE;
    }
	else
    {
		/* Disable VC function */
		VCx->PGACR &= (uint32_t)(~VC_PGA_LOOP_ENABLE);   
    }
}



