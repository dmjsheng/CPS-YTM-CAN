/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_adc.h"  


/** 
  * @brief  Deinitializes the ADC peripherals registers to their default reset 
  *         values.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
    /* Enable ADC reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ADC_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release ADC from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ADC_RST, DISABLE);
}

/** 
  * @brief  Initializes the ADCx peripheral according to the specified parameters 
  *         in the ADC_InitStruct. 
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t tmpcr0 = 0;
    uint32_t tmpcr1 = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_ConvMode(ADC_InitStruct->ConvMode_Sel)); 
    assert_param(ADC_Internal_VREF_En(ADC_InitStruct->Internal_Vref_En)); 
    assert_param(IS_ADCSampleCycle(ADC_InitStruct->SampleCycleSel)); 
    assert_param(IS_ADC_VREF(ADC_InitStruct->Ref_Voltage_Sel)); 
	assert_param(IS_ADC_BUFFER_DIS(ADC_InitStruct->Buffer_Dis)); 
	assert_param(IS_ADC_CLOCK_DIV(ADC_InitStruct->ClockDiv)); 
    assert_param(IS_ADC_RESULT_Align(ADC_InitStruct->Result_Align)); 

    /* Read ADC_CR0 register */
    tmpcr0 = ADCx->CR0;

    /* Read ADC_CR1 register */
    tmpcr1 = ADCx->CR1;
    
    tmpcr0 &= (uint32_t)(~ADC_Internal_VREF_ENABLE);  // ADC_CR0.VREF_EN=0
    tmpcr0 &= (uint32_t)(~ADC_SampleCycle_Mask);  // ADC_CR0.SH_CTR[1:0]=2'b00
    tmpcr0 &= (uint32_t)(~ADC_VREF_SEL_Mask);     // ADC_CR0.VREF_SEL[1:0]=2'b00
    tmpcr0 &= (uint32_t)(~ADC_Buffer_DISABLE);    // ADC_CR0.BUF_DIS=0, Open input buffer
    tmpcr0 &= (uint32_t)(~ADC_CLOCK_DIV_Mask);    // ADC_CR0.CkDiv[1:0] = 2'b00
    tmpcr1 &= (uint32_t)(~ADC_ConvMode_Scan);     // ADC_CR1.Mode=0, Single conv. mode
    tmpcr1 &= (uint32_t)(~ADC_RESULT_Align_Left); // ADC_CR1.Align=0, Align=right
    
    tmpcr0 |= ADC_InitStruct->Internal_Vref_En;
    tmpcr0 |= ADC_InitStruct->SampleCycleSel;
    tmpcr0 |= ADC_InitStruct->Ref_Voltage_Sel;
    tmpcr0 |= ADC_InitStruct->Buffer_Dis;
    tmpcr0 |= ADC_InitStruct->ClockDiv;

    tmpcr1 |= ADC_InitStruct->ConvMode_Sel;
    tmpcr1 |= ADC_InitStruct->Result_Align;

    /* write ADC_CR0 register */
    ADCx->CR0 = tmpcr0;
    
    /* write ADC_CR1 register */
    ADCx->CR1 = tmpcr1;
}

/** 
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
    ADC_InitStruct->ConvMode_Sel = ADC_ConvMode_Single;   // 单次转换模式
    ADC_InitStruct->Internal_Vref_En = ADC_Internal_VREF_DISABLE;   // 内部参考电压禁止
    ADC_InitStruct->SampleCycleSel = ADC_SampleCycle_11Cycle;   // 采样周期为11个采样时钟
    ADC_InitStruct->Ref_Voltage_Sel = ADC_VREF_AVDD;  // 参考电压为AVDD
    ADC_InitStruct->Buffer_Dis = ADC_Buffer_ENABLE;   // ADC输入信号放大使能
    ADC_InitStruct->ClockDiv = ADC_CLOCK_DIV1;        // PCLK/Div1
    ADC_InitStruct->Result_Align = ADC_RESULT_Align_Right;   // 右对齐方式
}

/**
  * @brief  Enables or disables the specified ADCx peripheral.
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  NewState: new state of the ADCx peripheral. 
  *       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		ADCx->CR0 |= ADC_ENABLE;   // 使能ADC模块
	}
	else
	{
		ADCx->CR0 &= (uint32_t)(~ADC_ENABLE);  // 禁止ADC模块
	}
}

/** 
  * @brief  ADC单次转换通道配置
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 选择单次转换的AD通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_Single_Channel_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	ADCx->CR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 4));
	ADCx->CR0 |= (uint32_t)(ADC_Channelx << 4);
}

/** 
  * @brief  ADC单次转换启动
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval None
  */
void ADC_Single_Conv_Start(ADC_TypeDef* ADCx)
{
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));

	ADCx->SGLSTART = ADC_SINGLE_START;   // 启动ADC单次转换
}

/** 
  * @brief  获取ADC单次转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC单次转换结果
  */
uint16_t ADC_Get_Single_Result(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->RESULT;
}

/** 
  * @brief  Enable or Disable REG Compare
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  NewState: new state of the REG Compare. 
  *       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_REG_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
	    ADCx->CR1 |= ADC_REG_CMP_ENABLE;
	}
	else
	{
	    ADCx->CR1 &= (uint32_t)(~ADC_REG_CMP_ENABLE);
	}
}

/** 
  * @brief  Enable or Disable HT Compare
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  NewState: new state of the HT Compare. 
  *       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_HT_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
	    ADCx->CR1 |= ADC_HT_CMP_ENABLE;
	}
	else
	{
	    ADCx->CR1 &= (uint32_t)(~ADC_HT_CMP_ENABLE);
	}
}

/** 
  * @brief  Enable or Disable LT Compare
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  NewState: new state of the LT Compare. 
  *       This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_LT_Compare_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
	    ADCx->CR1 |= ADC_LT_CMP_ENABLE;
	}
	else
	{
	    ADCx->CR1 &= (uint32_t)(~ADC_LT_CMP_ENABLE);
	}
}

/** 
  * @brief  设置ADC阈值比较通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  CmpChannel: 阈值比较通道
  *    This parameters can be one of the following values:
  *    @arg ADC_SQR_SCAN_CH0
  *    @arg ADC_SQR_SCAN_CH1
  *    @arg ADC_SQR_SCAN_CH2
  *    @arg ADC_SQR_SCAN_CH3
  *    @arg ADC_SQR_SCAN_CH4
  *    @arg ADC_SQR_SCAN_CH5
  *    @arg ADC_SQR_SCAN_CH6
  *    @arg ADC_SQR_SCAN_CH7
  *    @arg ADC_SQR_SCAN_CH8
  *    @arg ADC_SQR_SCAN_CH9
  *    @arg ADC_JQR_SCAN_CH0
  *    @arg ADC_JQR_SCAN_CH1
  *    @arg ADC_JQR_SCAN_CH2
  *    @arg ADC_JQR_SCAN_CH3
  *    @arg ADC_RESULT
  * @retval None
  */
void ADC_Threshold_CH_Config(ADC_TypeDef* ADCx, uint32_t CmpChannel)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_TH_CHANNEL(CmpChannel));

    ADCx->CR1 &= (uint32_t)(~ADC_THRESHOLD_CH_Mask);
    ADCx->CR1 |= CmpChannel;
}

/** 
  * @brief  set compare ht value
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  HtValue: the value of ht.
  * @retval None
  */
void ADC_Set_HT_CompareValue(ADC_TypeDef* ADCx, uint32_t HtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_HT_COMPARE_VALUE(HtValue));
  
    /* set ADC HT value */
    ADCx->HT = HtValue;
}

/** 
  * @brief  set compare lt value
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  LtValue: the value of lt.
  * @retval None
  */
void ADC_Set_LT_CompareValue(ADC_TypeDef* ADCx, uint32_t LtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_LT_COMPARE_VALUE(LtValue));

    /* set ADC LT value */
    ADCx->LT = LtValue;
}

/** 
  * @brief  顺序扫描通道0配置待转换的ADC通道
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH0_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 0));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 0);
}

/** 
  * @brief  顺序扫描通道1配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH1_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 5));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 5);
}

/** 
  * @brief  顺序扫描通道2配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH2_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 10));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 10);
}

/** 
  * @brief  顺序扫描通道3配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH3_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 15));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 15);
}

/** 
  * @brief  顺序扫描通道3配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH4_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 20));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 20);
}

/** 
  * @brief  顺序扫描通道5配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH5_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR0 &= (uint32_t)(~(ADC_CHANNEL_Mask << 25));
    ADCx->SQR0 |= (uint32_t)(ADC_Channelx << 25);
}

/** 
  * @brief  顺序扫描通道6配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH6_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR1 &= (uint32_t)(~(ADC_CHANNEL_Mask << 0));
    ADCx->SQR1 |= (uint32_t)(ADC_Channelx << 0);
}

/** 
  * @brief  顺序扫描通道7配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH7_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR1 &= (uint32_t)(~(ADC_CHANNEL_Mask << 5));
    ADCx->SQR1 |= (uint32_t)(ADC_Channelx << 5);
}

/** 
  * @brief  顺序扫描通道8配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH8_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR1 &= (uint32_t)(~(ADC_CHANNEL_Mask << 10));
    ADCx->SQR1 |= (uint32_t)(ADC_Channelx << 10);
}

/** 
  * @brief  顺序扫描通道9配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_SQR_CH9_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->SQR1 &= (uint32_t)(~(ADC_CHANNEL_Mask << 15));
    ADCx->SQR1 |= (uint32_t)(ADC_Channelx << 15);
}

/** 
  * @brief  设置ADC顺序扫描转换次数
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ConvNum: 转换次数，范围0~10                                        
  * @retval None
  */
void ADC_Set_SQR_ConvNum(ADC_TypeDef* ADCx, uint32_t ConvNum)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_SQR_ConvNum(ConvNum));

    ADCx->SQR1 &= (uint32_t)(~ADC_SQR_ConvNum_Mask);
    ADCx->SQR1 |= (uint32_t)(ConvNum << 20);
}

/** 
  * @brief  启动ADC顺序扫描换转
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval None
  */
void ADC_SQR_Conv_Start(ADC_TypeDef* ADCx)
{
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));

	ADCx->SQRSTART = ADC_SQR_SCAN_START;   // 启动ADC顺序扫描转换
}

/** 
  * @brief  获取ADC顺序扫描转换通道0的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道0之转换结果
  */
uint16_t ADC_Get_SQR_Result0(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT0;
}

/** 
  * @brief  获取ADC顺序扫描转换通道1的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道1之转换结果
  */
uint16_t ADC_Get_SQR_Result1(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT1;
}

/** 
  * @brief  获取ADC顺序扫描转换通道2的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道2之转换结果
  */
uint16_t ADC_Get_SQR_Result2(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT2;
}

/** 
  * @brief  获取ADC顺序扫描转换通道3的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道3之转换结果
  */
uint16_t ADC_Get_SQR_Result3(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT3;
}

/** 
  * @brief  获取ADC顺序扫描转换通道4的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道4之转换结果
  */
uint16_t ADC_Get_SQR_Result4(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT4;
}

/** 
  * @brief  获取ADC顺序扫描转换通道5的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道5之转换结果
  */
uint16_t ADC_Get_SQR_Result5(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT5;
}

/** 
  * @brief  获取ADC顺序扫描转换通道6的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道6之转换结果
  */
uint16_t ADC_Get_SQR_Result6(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT6;
}

/** 
  * @brief  获取ADC顺序扫描转换通道7的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道7之转换结果
  */
uint16_t ADC_Get_SQR_Result7(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT7;
}

/** 
  * @brief  获取ADC顺序扫描转换通道8的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道8之转换结果
  */
uint16_t ADC_Get_SQR_Result8(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT8;
}

/** 
  * @brief  获取ADC顺序扫描转换通道9的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC顺序扫描转换通道9之转换结果
  */
uint16_t ADC_Get_SQR_Result9(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->SQRRESULT9;
}

/** 
  * @brief  插队扫描通道0配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_JQR_CH0_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->JQR &= (uint32_t)(~(ADC_CHANNEL_Mask << 0));
    ADCx->JQR |= (uint32_t)(ADC_Channelx << 0);
}

/** 
  * @brief  插队扫描通道1配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_JQR_CH1_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->JQR &= (uint32_t)(~(ADC_CHANNEL_Mask << 5));
    ADCx->JQR |= (uint32_t)(ADC_Channelx << 5);
}

/** 
  * @brief  插队扫描通道2配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_JQR_CH2_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->JQR &= (uint32_t)(~(ADC_CHANNEL_Mask << 10));
    ADCx->JQR |= (uint32_t)(ADC_Channelx << 10);
}

/** 
  * @brief  插队扫描通道3配置待转换的ADC通道
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_Channelx: 待转换的ADC通道
  *    This parameters can be one of the following values:
  *    @arg ADC_CHANNEL_AIN0
  *    @arg ADC_CHANNEL_AIN1
  *    @arg ADC_CHANNEL_AIN2
  *    @arg ADC_CHANNEL_AIN3
  *    @arg ADC_CHANNEL_AIN4
  *    @arg ADC_CHANNEL_AIN5
  *    @arg ADC_CHANNEL_AIN6
  *    @arg ADC_CHANNEL_AIN7
  *    @arg ADC_CHANNEL_AIN8
  *    @arg ADC_CHANNEL_AIN9
  *    @arg ADC_CHANNEL_AIN10
  *    @arg ADC_CHANNEL_AIN11
  *    @arg ADC_CHANNEL_AIN12
  *    @arg ADC_CHANNEL_AIN13
  *    @arg ADC_CHANNEL_AIN14
  *    @arg ADC_CHANNEL_AIN15
  *    @arg ADC_CHANNEL_AIN16
  *    @arg ADC_CHANNEL_AIN17
  *    @arg ADC_CHANNEL_AVDD_DIV3
  *    @arg ADC_CHANNEL_1V_AVREF
  *    @arg ADC_CHANNEL_TS
  *    @arg ADC_CHANNEL_PGA_OUT
  * @retval None
  */
void ADC_JQR_CH3_Config(ADC_TypeDef* ADCx, uint32_t ADC_Channelx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL_SEL(ADC_Channelx));

    ADCx->JQR &= (uint32_t)(~(ADC_CHANNEL_Mask << 15));
    ADCx->JQR |= (uint32_t)(ADC_Channelx << 15);
}

/** 
  * @brief  设置ADC插队扫描转换次数
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ConvNum: 转换次数，范围0~4                                        
  * @retval None
  */
void ADC_Set_JQR_ConvNum(ADC_TypeDef* ADCx, uint32_t ConvNum)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_JQR_ConvNum(ConvNum));

    ADCx->JQR &= (uint32_t)(~ADC_JQR_ConvNum_Mask);
    ADCx->JQR |= (uint32_t)(ConvNum << 20);
}

/** 
  * @brief  启动ADC插队扫描换转
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval None
  */
void ADC_JQR_Conv_Start(ADC_TypeDef* ADCx)
{
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));

	ADCx->JQRSTART = ADC_JQR_SCAN_START;   // 启动ADC插队扫描转换
}

/** 
  * @brief  获取ADC插队扫描转换通道0的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC插队扫描转换通道0之转换结果
  */
uint16_t ADC_Get_JQR_Result0(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->JQRRESULT0;
}

/** 
  * @brief  获取ADC插队扫描转换通道1的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC插队扫描转换通道1之转换结果
  */
uint16_t ADC_Get_JQR_Result1(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->JQRRESULT1;
}

/** 
  * @brief  获取ADC插队扫描转换通道2的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC插队扫描转换通道2之转换结果
  */
uint16_t ADC_Get_JQR_Result2(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->JQRRESULT2;
}

/** 
  * @brief  获取ADC插队扫描转换通道3的转换结果
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @retval 返回ADC插队扫描转换通道3之转换结果
  */
uint16_t ADC_Get_JQR_Result3(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	
    return ADCx->JQRRESULT3;
}

/**
  * @brief  单次转换/顺序扫描转换外部触发源选择
  * @param  ADCx: Select the ADCx peripheral. 
  *   This parameter can be one of the following values: ADC
  * @param  TriggerSource: 指定的外部触发源
  *   This parameter can be one of the following values:
  *     @arg ADC_AUTO_TRIG_DISABLE
  *     @arg ADC_TRIG_TIM10_IT
  *     @arg ADC_TRIG_TIM11_IT
  *     @arg ADC_TRIG_ETIMER_IT
  *     @arg ADC_TRIG_LPTIM_IT
  *     @arg ADC_TRIG_ETIMER_TRGO
  *     @arg ADC_TRIG_TIM2_TRGO
  *     @arg ADC_TRIG_TIM2_IT
  *     @arg ADC_TRIG_EUART0_RX_IT
  *     @arg ADC_TRIG_EUART1_RX_IT
  *     @arg ADC_TRIG_ASPI_RX_IT
  *     @arg ADC_TRIG_VC_IT
  *     @arg ADC_TRIG_SPI1_IT
  *     @arg ADC_TRIG_ASPI_TX_IT
  *     @arg ADC_TRIG_PA1_IT
  *     @arg ADC_TRIG_PA2_IT
  *     @arg ADC_TRIG_PA3_IT
  *     @arg ADC_TRIG_PB4_IT
  *     @arg ADC_TRIG_PB5_IT
  *     @arg ADC_TRIG_PC3_IT
  *     @arg ADC_TRIG_PC4_IT
  *     @arg ADC_TRIG_PC5_IT
  *     @arg ADC_TRIG_PC6_IT
  *     @arg ADC_TRIG_PC7_IT
  *     @arg ADC_TRIG_PD1_IT
  *     @arg ADC_TRIG_PD2_IT
  *     @arg ADC_TRIG_PD3_IT
  *     @arg ADC_TRIG_EUART0_TX_IT
  *     @agr ADC_TRIG_EUART1_TX_IT
  * @retval None
  */
void ADC_SGL_SQR_Trig_Select(ADC_TypeDef* ADCx, uint8_t TriggerSource)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_TRIG_SOURCE(TriggerSource));

	ADCx->EXTTRIGGER0 &= (uint32_t)(~ADC_TRIG_SOURCE_Mask);
	ADCx->EXTTRIGGER0 |= (uint32_t)TriggerSource;
}

/**
  * @brief  插队扫描转换外部触发源选择
  * @param  ADCx: Select the ADCx peripheral. 
  *   This parameter can be one of the following values: ADC
  * @param  TriggerSource: 指定的外部触发源
  *   This parameter can be one of the following values:
  *     @arg ADC_AUTO_TRIG_DISABLE
  *     @arg ADC_TRIG_TIM10_IT
  *     @arg ADC_TRIG_TIM11_IT
  *     @arg ADC_TRIG_ETIMER_IT
  *     @arg ADC_TRIG_LPTIM_IT
  *     @arg ADC_TRIG_ETIMER_TRGO
  *     @arg ADC_TRIG_TIM2_TRGO
  *     @arg ADC_TRIG_TIM2_IT
  *     @arg ADC_TRIG_EUART0_RX_IT
  *     @arg ADC_TRIG_EUART1_RX_IT
  *     @arg ADC_TRIG_ASPI_RX_IT
  *     @arg ADC_TRIG_VC_IT
  *     @arg ADC_TRIG_SPI1_IT
  *     @arg ADC_TRIG_ASPI_TX_IT
  *     @arg ADC_TRIG_PA1_IT
  *     @arg ADC_TRIG_PA2_IT
  *     @arg ADC_TRIG_PA3_IT
  *     @arg ADC_TRIG_PB4_IT
  *     @arg ADC_TRIG_PB5_IT
  *     @arg ADC_TRIG_PC3_IT
  *     @arg ADC_TRIG_PC4_IT
  *     @arg ADC_TRIG_PC5_IT
  *     @arg ADC_TRIG_PC6_IT
  *     @arg ADC_TRIG_PC7_IT
  *     @arg ADC_TRIG_PD1_IT
  *     @arg ADC_TRIG_PD2_IT
  *     @arg ADC_TRIG_PD3_IT
  *     @arg ADC_TRIG_EUART0_TX_IT
  *     @agr ADC_TRIG_EUART1_TX_IT
  * @retval None
  */
void ADC_JQR_Trig_Select(ADC_TypeDef* ADCx, uint8_t TriggerSource)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_TRIG_SOURCE(TriggerSource));

    ADCx->EXTTRIGGER1 &= (uint32_t)(~ADC_TRIG_SOURCE_Mask);
	ADCx->EXTTRIGGER1 |= (uint32_t)TriggerSource;
}

/**
  * @brief  Enables or disables the specified ADCx interrupts.
  * @param  ADCx: Select the ADCx peripheral. 
  *   	This parameter can be one of the following values: ADC
  * @param  ADC_IT: specifies the ADCx interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg ADC_JQR_IE
  *     @arg ADC_SQR_IE
  *     @arg ADC_REG_IE
  *     @arg ADC_HT_IE
  *     @arg ADC_LT_IE
  *     @arg ADC_SGL_IE
  * @param  NewState: new state of the specified ADCx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
	assert_param(IS_ADC_IE(ADC_IT));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        ADCx->IER |= ADC_IT;
    }
    else
    {
        ADCx->IER &= (uint32_t)(~ADC_IT);
    }
}

/**
  * @brief  Checks whether the specified ADCx interrupt has occurred or not.
  * @param  ADCx: Select the ADCx peripheral. 
  *   This parameter can be one of the following values: ADC
  * @param  ADC_IT_FLAG: specifies the ADCx interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg ADC_JQR_IF
  *     @arg ADC_SQR_IF
  *     @arg ADC_REG_IF
  *     @arg ADC_HT_IF
  *	    @arg ADC_LT_IF
  *	    @arg ADC_SGL_IF
  * @retval The new state of ADC_IT_FLAG (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT_FLAG)
{
	ITStatus bitstatus = RESET;
	
	/* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT_FLAG(ADC_IT_FLAG));
	
	if ((ADCx->IFR & ADC_IT_FLAG) != (uint32_t)RESET)
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
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: Select the ADCx peripheral.
  *   This parameter can be one of the following values: ADC
  * @param  ADC_IT_FLAG: specifies the ADCx interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg ADC_JQR_IF
  *     @arg ADC_SQR_IF
  *     @arg ADC_REG_IF
  *     @arg ADC_HT_IF
  *	    @arg ADC_LT_IF
  *	    @arg ADC_SGL_IF
  *     @arg ADC_ALL_IF
  * @retval None
  */
void ADC_ClearITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT_FLAG)
{
    uint32_t temp = 0;
    
    /* Check the parameters */
	assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT_FLAG(ADC_IT_FLAG));

    temp = (uint32_t)(~ADC_IT_FLAG);
    
    ADCx->ICR = temp;
}


