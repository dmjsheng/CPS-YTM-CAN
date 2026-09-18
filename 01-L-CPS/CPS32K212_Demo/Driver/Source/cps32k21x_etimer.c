/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_etimer.h"   


/**
  * @brief  Deinitializes the ETIMERx peripheral registers to their default reset values.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval None
  */
void ETIMER_DeInit(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 

    if (ETIMERx == ETIMER)
    {
    	/* Enable ETIMER reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ETIMER_RST, ENABLE);
    	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    	/* Release ETIMER from reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ETIMER_RST, DISABLE);
    }     
}

/**
  * @brief  Initializes the ETIMERx Time Base Unit peripheral according to 
  *         the specified parameters in the ETIMER_TimeBaseInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_TimeBaseInitStruct: pointer to a ETIMER_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the 
  *         specified ETIMER peripheral.
  * @retval None	
  */	
void ETIMER_TimeBaseInit(ETIMER_TypeDef* ETIMERx, ETIMER_TimeBaseInitTypeDef* ETIMER_TimeBaseInitStruct)
{
    uint16_t tmpcr1 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_COUNTER_MODE(ETIMER_TimeBaseInitStruct->ETIMER_CounterMode));
    assert_param(IS_ETIMER_CKD_DIV(ETIMER_TimeBaseInitStruct->ETIMER_ClockDivision));
	
    tmpcr1 = ETIMERx->CR1;  
	
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~((uint16_t)(ETIMER_CR1_DIR_Mask | ETIMER_CR1_CMS_Mask)));
    tmpcr1 |= (uint16_t)ETIMER_TimeBaseInitStruct->ETIMER_CounterMode;

    /* Set the clock division */
    tmpcr1 &= (uint16_t)(~ETIMER_CKD_Mask);
    tmpcr1 |= (uint16_t)ETIMER_TimeBaseInitStruct->ETIMER_ClockDivision;

    ETIMERx->CR1 = tmpcr1;

    /* Set the Autoreload value */
    ETIMERx->ARR = ETIMER_TimeBaseInitStruct->ETIMER_Period;   // 加载自动重装载寄存器

    /* Set the Prescaler value */
    ETIMERx->PSC = ETIMER_TimeBaseInitStruct->ETIMER_Prescaler;
			 
    /* Set the Repetition Counter value */
    ETIMERx->RCR = ETIMER_TimeBaseInitStruct->ETIMER_RepetitionCounter;

    /* Generate an update event to reload the Prescaler and the Repetition counter
    values immediately */
    ETIMERx->EGR = ETIMER_PSCReloadMode_Immediate;    
}
	
/**
  * @brief  Initializes the ETIMERx Channel1 according to the specified
  *         parameters in the ETIMER_OCInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCInitStruct: pointer to a ETIMER_OCInitTypeDef structure
  *         that contains the configuration information for the specified ETIMER peripheral.
  * @retval None	
  */
void ETIMER_OC1Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_MODE(ETIMER_OCInitStruct->ETIMER_OCMode));
    assert_param(IS_ETIMER_OUTPUT_STATE(ETIMER_OCInitStruct->ETIMER_OutputState));
    assert_param(IS_ETIMER_OUTPUTN_STATE(ETIMER_OCInitStruct->ETIMER_OutputNState));
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCInitStruct->ETIMER_OCPolarity)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCInitStruct->ETIMER_OCNPolarity));
    assert_param(IS_ETIMER_OCNIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCNIdleState));
    assert_param(IS_ETIMER_OCIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCIdleState));
    
    /* Disable the Channel 1: Reset the CC1E Bit */
    ETIMERx->CCER &= (uint16_t)(~(uint16_t)ETIMER_CCER_CC1E);  // Output disable
    
    /* Get the ETIMERx CCER register value */
    tmpccer = ETIMERx->CCER;
    
    /* Get the ETIMERx CR2 register value */
    tmpcr2 =  ETIMERx->CR2;

    /* Get the ETIMERx CCMR1 register value */
    tmpccmrx = ETIMERx->CCMR1;

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR1_OC1M));
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR1_CC1S));

    /* Select the Output Compare Mode */
    tmpccmrx |= ETIMER_OCInitStruct->ETIMER_OCMode;

    /* Reset the Output Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC1P));
    /* Set the Output Compare Polarity */
    tmpccer |= ETIMER_OCInitStruct->ETIMER_OCPolarity;

     /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC1NP));
    /* Set the Output N Polarity */
    tmpccer |= ETIMER_OCInitStruct->ETIMER_OCNPolarity;
    
    /* Set the Output State */
    tmpccer |= ETIMER_OCInitStruct->ETIMER_OutputState;
    
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC1NE));    
    /* Set the Output N State */
    tmpccer |= ETIMER_OCInitStruct->ETIMER_OutputNState;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS1));
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS1N));

    /* Set the Output Idle state */
    tmpcr2 |= ETIMER_OCInitStruct->ETIMER_OCIdleState;
    /* Set the Output N Idle state */
    tmpcr2 |= ETIMER_OCInitStruct->ETIMER_OCNIdleState;
   
    /* Write to ETIMERx CR2 */
    ETIMERx->CR2 = tmpcr2;

    /* Write to ETIMERx CCMR1 */
    ETIMERx->CCMR1 = tmpccmrx;

    /* Set the Capture Compare Register value */
    ETIMERx->CCR1A = ETIMER_OCInitStruct->ETIMER_Pulse; 

    /* Write to ETIMERx CCER */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Initializes the ETIMERx Channel2 according to the specified
  *         parameters in the ETIMER_OCInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCInitStruct: pointer to a ETIMER_OCInitTypeDef structure
  *         that contains the configuration information for the specified ETIMERx peripheral.
  * @retval None
  */
void ETIMER_OC2Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_MODE(ETIMER_OCInitStruct->ETIMER_OCMode));
    assert_param(IS_ETIMER_OUTPUT_STATE(ETIMER_OCInitStruct->ETIMER_OutputState));
    assert_param(IS_ETIMER_OUTPUTN_STATE(ETIMER_OCInitStruct->ETIMER_OutputNState));
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCInitStruct->ETIMER_OCPolarity)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCInitStruct->ETIMER_OCNPolarity));
    assert_param(IS_ETIMER_OCNIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCNIdleState));
    assert_param(IS_ETIMER_OCIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCIdleState));
    
    /* Disable the Channel 2: Reset the CC2E Bit */
    ETIMERx->CCER &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC2E));   // Output disable

    /* Get the ETIMERx CCER register value */  
    tmpccer = ETIMERx->CCER;
    
    /* Get the ETIMERx CR2 register value */
    tmpcr2 =  ETIMERx->CR2;

    /* Get the ETIMERx CCMR1 register value */
    tmpccmrx = ETIMERx->CCMR1;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR1_OC2M));
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR1_CC2S));

    /* Select the Output Compare Mode */
    tmpccmrx |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC2P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCPolarity << 4);

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC2NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCNPolarity << 4);

    /* Set the Output State */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OutputState << 4);

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC2NE));    
    /* Set the Output N State */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OutputNState << 4);

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS2));
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS2N));

    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCIdleState << 2);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCNIdleState << 2);
    
    /* Write to ETIMERx CR2 */
    ETIMERx->CR2 = tmpcr2;

    /* Write to ETIMERx CCMR1 */
    ETIMERx->CCMR1 = tmpccmrx;

    /* Set the Capture Compare Register value */
    ETIMERx->CCR2A = ETIMER_OCInitStruct->ETIMER_Pulse;

    /* Write to ETIMERx CCER */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Initializes the ETIMERx Channel3 according to the specified
  *         parameters in the ETIMER_OCInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCInitStruct: pointer to a ETIMER_OCInitTypeDef structure
  *         that contains the configuration information for the specified ETIMERx peripheral.
  * @retval None
  */
void ETIMER_OC3Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_MODE(ETIMER_OCInitStruct->ETIMER_OCMode));
    assert_param(IS_ETIMER_OUTPUT_STATE(ETIMER_OCInitStruct->ETIMER_OutputState));
    assert_param(IS_ETIMER_OUTPUTN_STATE(ETIMER_OCInitStruct->ETIMER_OutputNState));
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCInitStruct->ETIMER_OCPolarity)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCInitStruct->ETIMER_OCNPolarity));
    assert_param(IS_ETIMER_OCNIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCNIdleState));
    assert_param(IS_ETIMER_OCIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCIdleState));
    
    /* Disable the Channel 2: Reset the CC2E Bit */
    ETIMERx->CCER &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC3E));   // Output disable

    /* Get the ETIMERx CCER register value */
    tmpccer = ETIMERx->CCER;
    
    /* Get the ETIMERx CR2 register value */
    tmpcr2 =  ETIMERx->CR2;

    /* Get the ETIMERx CCMR2 register value */
    tmpccmrx = ETIMERx->CCMR2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR2_OC3M));
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR2_CC3S));  
    /* Select the Output Compare Mode */
    tmpccmrx |= ETIMER_OCInitStruct->ETIMER_OCMode;

    /* Reset the Output Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC3P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCPolarity << 8);

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC3NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCNPolarity << 8);
  
    /* Set the Output State */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OutputState << 8);
    
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC3NE));
    /* Set the Output N State */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OutputNState << 8);
    
    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS3));
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS3N));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCIdleState << 4);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCNIdleState << 4);
    
    /* Write to ETIMERx CR2 */
    ETIMERx->CR2 = tmpcr2;

    /* Write to ETIMERx CCMR2 */
    ETIMERx->CCMR2 = tmpccmrx;

    /* Set the Capture Compare Register value */
    ETIMERx->CCR3A = ETIMER_OCInitStruct->ETIMER_Pulse;

    /* Write to ETIMERx CCER */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Initializes the ETIMERx Channel4 according to the specified
  *         parameters in the ETIMER_OCInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCInitStruct: pointer to a ETIMER_OCInitTypeDef structure
  *         that contains the configuration information for the specified ETIMERx peripheral.
  * @retval None
  */
void ETIMER_OC4Init(ETIMER_TypeDef* ETIMERx, ETIMER_OCInitTypeDef* ETIMER_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_MODE(ETIMER_OCInitStruct->ETIMER_OCMode));
    assert_param(IS_ETIMER_OUTPUT_STATE(ETIMER_OCInitStruct->ETIMER_OutputState));
    assert_param(IS_ETIMER_OUTPUTN_STATE(ETIMER_OCInitStruct->ETIMER_OutputNState));
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCInitStruct->ETIMER_OCPolarity)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCInitStruct->ETIMER_OCNPolarity));
    assert_param(IS_ETIMER_OCNIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCNIdleState));
    assert_param(IS_ETIMER_OCIDLE_STATE(ETIMER_OCInitStruct->ETIMER_OCIdleState));
    
    /* Disable the Channel 2: Reset the CC4E Bit */
    ETIMERx->CCER &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC4E));

    /* Get the ETIMERx CCER register value */
    tmpccer = ETIMERx->CCER;
    
    /* Get the ETIMERx CR2 register value */
    tmpcr2 =  ETIMERx->CR2;

    /* Get the ETIMERx CCMR2 register value */
    tmpccmrx = ETIMERx->CCMR2;
    
    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR2_OC4M));
    tmpccmrx &= (uint16_t)(~((uint16_t)ETIMER_CCMR2_CC4S));

    /* Select the Output Compare Mode */
    tmpccmrx |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)ETIMER_CCER_CC4P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCPolarity << 12);

    /* Set the Output State */
    tmpccer |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OutputState << 12);

    /* Reset the Output Compare IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)ETIMER_CR2_OIS4));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(ETIMER_OCInitStruct->ETIMER_OCIdleState << 6);

    /* Write to ETIMERx CR2 */
    ETIMERx->CR2 = tmpcr2;

    /* Write to ETIMERx CCMR2 */  
    ETIMERx->CCMR2 = tmpccmrx;

    /* Set the Capture Compare Register value */
    ETIMERx->CCR4A = ETIMER_OCInitStruct->ETIMER_Pulse;

    /* Write to ETIMERx CCER */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Initializes the ETIMERx peripheral according to the specified
  *         parameters in the ETIMER_ICInitStruct.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICInitStruct: pointer to a ETIMER_ICInitTypeDef structure
  *         that contains the configuration information for the specified ETIMERx peripheral.
  * @retval None
  */
void ETIMER_ICInit(ETIMER_TypeDef* ETIMERx, ETIMER_ICInitTypeDef* ETIMER_ICInitStruct)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_CHANNEL(ETIMER_ICInitStruct->ETIMER_Channel));  
    assert_param(IS_ETIMER_IC_SELECTION(ETIMER_ICInitStruct->ETIMER_ICSelection));
    assert_param(IS_ETIMER_IC_PRESCALER(ETIMER_ICInitStruct->ETIMER_ICPrescaler));
    assert_param(IS_ETIMER_IC_FILTER(ETIMER_ICInitStruct->ETIMER_ICFilter));
    assert_param(IS_ETIMER_IC_POLARITY(ETIMER_ICInitStruct->ETIMER_ICPolarity));

    if (ETIMER_ICInitStruct->ETIMER_Channel == ETIMER_Channel_1)
    {
        /* TI1 Configuration */
        ETIMER_TI1_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC1Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
    }
    else if (ETIMER_ICInitStruct->ETIMER_Channel == ETIMER_Channel_2)
    {
        /* TI2 Configuration */
        ETIMER_TI2_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC2Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
    }
    else if (ETIMER_ICInitStruct->ETIMER_Channel == ETIMER_Channel_3)
    {
        /* TI3 Configuration */
        ETIMER_TI3_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC3Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
    }
    else if (ETIMER_ICInitStruct->ETIMER_Channel == ETIMER_Channel_4)
    {
        /* TI4 Configuration */
        ETIMER_TI4_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC4Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
    } 
}
	
/**
  * @brief  Configures the ETIMER peripheral according to the specified
  *         parameters in the ETIMER_ICInitStruct to measure an external PWM signal.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICInitStruct: pointer to a ETIMER_ICInitTypeDef structure
  *         that contains the configuration information for the specified ETIMER peripheral.
  * @retval None
  */
void ETIMER_PWMIConfig(ETIMER_TypeDef* ETIMERx, ETIMER_ICInitTypeDef* ETIMER_ICInitStruct)
{
    uint16_t icoppositepolarity = ETIMER_ICPolarity_Rising;
    uint16_t icoppositeselection = ETIMER_ICSelection_DirectTI;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Select the Opposite Input Polarity */
    if (ETIMER_ICInitStruct->ETIMER_ICPolarity == ETIMER_ICPolarity_Rising)
    {
        icoppositepolarity = ETIMER_ICPolarity_Falling;
    }
    else
    {
        icoppositepolarity = ETIMER_ICPolarity_Rising;
    }
    /* Select the Opposite Input */
    if (ETIMER_ICInitStruct->ETIMER_ICSelection == ETIMER_ICSelection_DirectTI)
    {
        icoppositeselection = ETIMER_ICSelection_IndirectTI;
    }
    else
    {
        icoppositeselection = ETIMER_ICSelection_DirectTI;
    }
    
    if (ETIMER_ICInitStruct->ETIMER_Channel == ETIMER_Channel_1)
    {
        /* TI1 Configuration */
        ETIMER_TI1_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC1Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
        
        /* TI2 Configuration */
        ETIMER_TI2_Config(ETIMERx, icoppositepolarity, icoppositeselection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC2Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);	
    }	
    else
    { 
        /* TI2 Configuration */
        ETIMER_TI2_Config(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPolarity, ETIMER_ICInitStruct->ETIMER_ICSelection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC2Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
        
        /* TI1 Configuration */
        ETIMER_TI1_Config(ETIMERx, icoppositepolarity, icoppositeselection, ETIMER_ICInitStruct->ETIMER_ICFilter);
        /* Set the Input Capture Prescaler value */
        ETIMER_SetIC1Prescaler(ETIMERx, ETIMER_ICInitStruct->ETIMER_ICPrescaler);
    }
}

/**
  * @brief  Configures the: Break feature, dead time, Lock level, the OSSI,
  *         the OSSR State and the AOE(automatic output enable).
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_BDTRInitStruct: pointer to a ETIMER_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration  information for the ETIMER peripheral.
  * @retval None
  */
void ETIMER_BDTRConfig(ETIMER_TypeDef* ETIMERx, ETIMER_BDTRInitTypeDef *ETIMER_BDTRInitStruct)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OSSR_STATE(ETIMER_BDTRInitStruct->ETIMER_OSSRState));
    assert_param(IS_ETIMER_OSSI_STATE(ETIMER_BDTRInitStruct->ETIMER_OSSIState));
    assert_param(IS_ETIMER_LOCK_LEVEL(ETIMER_BDTRInitStruct->ETIMER_LOCKLevel));
    assert_param(IS_ETIMER_BREAK_STATE(ETIMER_BDTRInitStruct->ETIMER_Break));
    assert_param(IS_ETIMER_BREAK_POLARITY(ETIMER_BDTRInitStruct->ETIMER_BreakPolarity));
    assert_param(IS_ETIMER_AUTOMATIC_OUTPUT_STATE(ETIMER_BDTRInitStruct->ETIMER_AutomaticOutput));
    
    /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
    ETIMERx->BDTR = (uint32_t)ETIMER_BDTRInitStruct->ETIMER_OSSRState | ETIMER_BDTRInitStruct->ETIMER_OSSIState |
             ETIMER_BDTRInitStruct->ETIMER_LOCKLevel | ETIMER_BDTRInitStruct->ETIMER_DeadTime |
             ETIMER_BDTRInitStruct->ETIMER_Break | ETIMER_BDTRInitStruct->ETIMER_BreakPolarity |
             ETIMER_BDTRInitStruct->ETIMER_AutomaticOutput;
}

/**
  * @brief  Fills each ETIMER_TimeBaseInitStruct member with its default value.
  * @param  ETIMER_TimeBaseInitStruct : pointer to a ETIMER_TimeBaseInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */	
void ETIMER_TimeBaseStructInit(ETIMER_TimeBaseInitTypeDef* ETIMER_TimeBaseInitStruct)	
{	
    /* Set the default configuration */
    ETIMER_TimeBaseInitStruct->ETIMER_Period = 0xFFFF;
    ETIMER_TimeBaseInitStruct->ETIMER_Prescaler = 0x0000;   // 预分频器默认值
    ETIMER_TimeBaseInitStruct->ETIMER_ClockDivision = ETIMER_CKD_DIV1;
    ETIMER_TimeBaseInitStruct->ETIMER_CounterMode = ETIMER_CounterMode_Up;
    ETIMER_TimeBaseInitStruct->ETIMER_RepetitionCounter = 0x0000;
}

/**
  * @brief  Fills each ETIMER_OCInitStruct member with its default value.
  * @param  ETIMER_OCInitStruct : pointer to a ETIMER_OCInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void ETIMER_OCStructInit(ETIMER_OCInitTypeDef* ETIMER_OCInitStruct)
{
    /* Set the default configuration */
    ETIMER_OCInitStruct->ETIMER_OCMode = ETIMER_OCMode_Timing;   
    ETIMER_OCInitStruct->ETIMER_OutputState = ETIMER_OutputState_Disable; 
    ETIMER_OCInitStruct->ETIMER_OutputNState = ETIMER_OutputNState_Disable;
    ETIMER_OCInitStruct->ETIMER_Pulse = 0x0000;
    ETIMER_OCInitStruct->ETIMER_OCPolarity = ETIMER_OCPolarity_High;   
    ETIMER_OCInitStruct->ETIMER_OCNPolarity = ETIMER_OCPolarity_High;  
    ETIMER_OCInitStruct->ETIMER_OCIdleState = ETIMER_OCIdleState_Reset;
    ETIMER_OCInitStruct->ETIMER_OCNIdleState = ETIMER_OCNIdleState_Reset;
}

/**
  * @brief  Fills each ETIMER_ICInitStruct member with its default value.
  * @param  ETIMER_ICInitStruct: pointer to a ETIMER_ICInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void ETIMER_ICStructInit(ETIMER_ICInitTypeDef* ETIMER_ICInitStruct)
{
    /* Set the default configuration */
    ETIMER_ICInitStruct->ETIMER_Channel = ETIMER_Channel_1;
    ETIMER_ICInitStruct->ETIMER_ICPolarity = ETIMER_ICPolarity_Rising;
    ETIMER_ICInitStruct->ETIMER_ICSelection = ETIMER_ICSelection_DirectTI;
    ETIMER_ICInitStruct->ETIMER_ICPrescaler = ETIMER_ICPSC_DIV1;
    ETIMER_ICInitStruct->ETIMER_ICFilter = 0x00;
}

/**
  * @brief  Fills each ETIMER_BDTRInitStruct member with its default value.
  * @param  ETIMER_BDTRInitStruct: pointer to a ETIMER_BDTRInitTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void ETIMER_BDTRStructInit(ETIMER_BDTRInitTypeDef* ETIMER_BDTRInitStruct)
{
    /* Set the default configuration */
    ETIMER_BDTRInitStruct->ETIMER_OSSRState = ETIMER_OSSRState_Disable;  // Off-State Selection for Run Mode
    ETIMER_BDTRInitStruct->ETIMER_OSSIState = ETIMER_OSSIState_Disable;
    ETIMER_BDTRInitStruct->ETIMER_LOCKLevel = ETIMER_LOCKLevel_OFF;
    ETIMER_BDTRInitStruct->ETIMER_DeadTime = 0x00;
    ETIMER_BDTRInitStruct->ETIMER_Break = ETIMER_Break_Disable;
    ETIMER_BDTRInitStruct->ETIMER_BreakPolarity = ETIMER_BreakPolarity_Low;
    ETIMER_BDTRInitStruct->ETIMER_AutomaticOutput = ETIMER_AutomaticOutput_Disable;
}

/**
  * @brief  Enables or disables the specified ETIMERx peripheral.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the ETIMERx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_Cmd(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the ETIMER Counter */
        ETIMERx->CR1 |= ETIMER_CR1_CEN;
    }
    else
    {
        /* Disable the ETIMER Counter */
        ETIMERx->CR1 &= (uint16_t)(~((uint16_t)ETIMER_CR1_CEN));
    }
}

/**
  * @brief  Enables or disables the ETIMERx peripheral Main Outputs.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the ETIMER peripheral Main Outputs.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_CtrlPWMOutputs(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Enable the ETIMER Main Output */
        ETIMERx->BDTR |= ETIMER_BDTR_MOE;   // 主输出使能
    }
    else
    {
        /* Disable the ETIMER Main Output */
        ETIMERx->BDTR &= (uint16_t)(~((uint16_t)ETIMER_BDTR_MOE));  // 主输出关闭
    }  
}

/**
  * @brief  Enables or disables the specified ETIMERx interrupts.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_IT: specifies the ETIMERx interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg ETIMER_IT_Update: ETIMER update Interrupt source
  *     @arg ETIMER_IT_CC1: ETIMER Capture Compare 1 Interrupt source
  *     @arg ETIMER_IT_CC2: ETIMER Capture Compare 2 Interrupt source
  *     @arg ETIMER_IT_CC3: ETIMER Capture Compare 3 Interrupt source
  *     @arg ETIMER_IT_CC4: ETIMER Capture Compare 4 Interrupt source
  *     @arg ETIMER_IT_COM: ETIMER Commutation Interrupt source
  *     @arg ETIMER_IT_Trigger: ETIMER Trigger Interrupt source
  *     @arg ETIMER_IT_Break: ETIMER Break Interrupt source   
  * @param  NewState: new state of the ETIMERx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_ITConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT, FunctionalState NewState)
{  
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_IT(ETIMER_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        ETIMERx->DIER |= ETIMER_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        ETIMERx->DIER &= (uint16_t)~ETIMER_IT;
    }
}

/**
  * @brief  Configures the ETIMERx event to be generate by software.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_EventSource: specifies the event source.
  *   This parameter can be one or more of the following values:	   
  *     @arg ETIMER_EventSource_Update: Timer update Event source
  *     @arg ETIMER_EventSource_CC1: Timer Capture Compare 1 Event source
  *     @arg ETIMER_EventSource_CC2: Timer Capture Compare 2 Event source
  *     @arg ETIMER_EventSource_CC3: Timer Capture Compare 3 Event source
  *     @arg ETIMER_EventSource_CC4: Timer Capture Compare 4 Event source
  *     @arg ETIMER_EventSource_COM: Timer COM event source  
  *     @arg ETIMER_EventSource_Trigger: Timer Trigger Event source
  *     @arg ETIMER_EventSource_Break: Timer Break event source    
  * @retval None
  */
void ETIMER_GenerateEvent(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_EventSource)
{ 
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_EVENT_SOURCE(ETIMER_EventSource));

    /* Set the event sources */
    ETIMERx->EGR = ETIMER_EventSource;
}

/**
  * @brief  Configures the ETIMERx internal Clock
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER      
  * @retval None
  */
void ETIMER_InternalClockConfig(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Disable slave mode, the prescaler directly with the internal clock */
    ETIMERx->SMCR &=  (uint16_t)(~((uint16_t)ETIMER_SMCR_SMS));  // 预分频器直接从内部时钟驱动
}

/**
  * @brief  Configures the ETIMERx Internal Trigger as External Clock
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ITRSource: Trigger source.
  *   This parameter can be one of the following values:
  *     @arg  ETIMER_TS_ITR0: Internal Trigger 0
  *     @arg  ETIMER_TS_ITR1: Internal Trigger 1
  *     @arg  ETIMER_TS_ITR2: Internal Trigger 2
  *     @arg  ETIMER_TS_ITR3: Internal Trigger 3
  * @retval None
  */
void ETIMER_ITRxExternalClockConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_InputTriggerSource)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_INTERNAL_TRIGGER_SELECTION(ETIMER_InputTriggerSource));
    
    /* Select the Internal Trigger */
    ETIMER_SelectInputTrigger(ETIMERx, ETIMER_InputTriggerSource);
    
    /* Select the External clock mode1 */
    ETIMERx->SMCR |= ETIMER_SlaveMode_External1;	
}
	
/**
  * @brief  Configures the ETIMERx Trigger as External Clock
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_TIxExternalCLKSource: Trigger source.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *     @arg ETIMER_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
  *     @arg ETIMER_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
  * @param  ETIMER_ICPolarity: specifies the TIx Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Rising
  *     @arg ETIMER_ICPolarity_Falling
  * @param  ICFilter : specifies the filter value.
  *   This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void ETIMER_TIxExternalClockConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_TIxExternalCLKSource,	uint16_t ETIMER_ICPolarity, uint16_t ICFilter)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_TIXCLK_SOURCE(ETIMER_TIxExternalCLKSource));
    assert_param(IS_ETIMER_IC_POLARITY(ETIMER_ICPolarity));
    assert_param(IS_ETIMER_IC_FILTER(ICFilter));
    
    /* Configure the Timer Input Clock Source */
    if (ETIMER_TIxExternalCLKSource == ETIMER_TIxExternalCLK1Source_TI2)
    {
        ETIMER_TI2_Config(ETIMERx, ETIMER_ICPolarity, ETIMER_ICSelection_DirectTI, ICFilter);
    }
    else
    {
        ETIMER_TI1_Config(ETIMERx, ETIMER_ICPolarity, ETIMER_ICSelection_DirectTI, ICFilter);
    }
    
    /* Select the Trigger source */
    ETIMER_SelectInputTrigger(ETIMERx, ETIMER_TIxExternalCLKSource);
    
    /* Select the External clock mode1 */
    ETIMERx->SMCR |= ETIMER_SlaveMode_External1;
}

/**
  * @brief  Configures the External clock Mode1
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *     @arg ETIMER_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *     @arg ETIMER_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *     @arg ETIMER_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  ETIMER_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg ETIMER_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void ETIMER_ETRClockMode1Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, uint16_t ETIMER_ExtTRGPolarity,	uint16_t ExtTRGFilter)
{
    uint16_t tmpsmcr = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_EXT_PRESCALER(ETIMER_ExtTRGPrescaler));
    assert_param(IS_ETIMER_EXT_POLARITY(ETIMER_ExtTRGPolarity));
    assert_param(IS_ETIMER_EXT_FILTER(ExtTRGFilter));
    
    /* Configure the ETR Clock source */
    ETIMER_ETRConfig(ETIMERx, ETIMER_ExtTRGPrescaler, ETIMER_ExtTRGPolarity, ExtTRGFilter);

    /* Get the ETIMERx SMCR register value */
    tmpsmcr = ETIMERx->SMCR;
    
    /* Reset the SMS Bits */
    tmpsmcr &= (uint16_t)(~((uint16_t)ETIMER_SMCR_SMS));
    
    /* Select the External clock mode1 */
    tmpsmcr |= ETIMER_SlaveMode_External1;
    
    /* Select the Trigger selection : ETRF */
    tmpsmcr &= (uint16_t)(~((uint16_t)ETIMER_SMCR_TS));
    tmpsmcr |= ETIMER_TS_ETRF;
    
    /* Write to ETIMERx SMCR */
    ETIMERx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the External clock Mode2
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *     @arg ETIMER_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *     @arg ETIMER_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *     @arg ETIMER_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  ETIMER_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg ETIMER_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void ETIMER_ETRClockMode2Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, 	uint16_t ETIMER_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_EXT_PRESCALER(ETIMER_ExtTRGPrescaler));
    assert_param(IS_ETIMER_EXT_POLARITY(ETIMER_ExtTRGPolarity));
    assert_param(IS_ETIMER_EXT_FILTER(ExtTRGFilter));
    
    /* Configure the ETR Clock source */
    ETIMER_ETRConfig(ETIMERx, ETIMER_ExtTRGPrescaler, ETIMER_ExtTRGPolarity, ExtTRGFilter);
    /* Enable the External clock mode2 */
    ETIMERx->SMCR |= ETIMER_SMCR_ECE; 
}

/**
  * @brief  Configures the ETIMERx External Trigger (ETR).
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPSC_OFF: ETRP Prescaler OFF.
  *     @arg ETIMER_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *     @arg ETIMER_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *     @arg ETIMER_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  ETIMER_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg ETIMER_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void ETIMER_ETRConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ExtTRGPrescaler, uint16_t ETIMER_ExtTRGPolarity,	uint16_t ExtTRGFilter)
{
    uint16_t tmpsmcr = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_EXT_PRESCALER(ETIMER_ExtTRGPrescaler));
    assert_param(IS_ETIMER_EXT_POLARITY(ETIMER_ExtTRGPolarity));
    assert_param(IS_ETIMER_EXT_FILTER(ExtTRGFilter));
    
    tmpsmcr = ETIMERx->SMCR;
    
    /* Reset the ETR Bits */
    tmpsmcr &= SMCR_ETR_Mask;
    
    /* Set the Prescaler, the Filter value and the Polarity */
    tmpsmcr |= (uint16_t)(ETIMER_ExtTRGPrescaler | (uint16_t)(ETIMER_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
    
    /* Write to ETIMERx SMCR */
    ETIMERx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the ETIMERx Prescaler.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  ETIMER_PSCReloadMode: specifies the ETIMER Prescaler Reload mode
  *   This parameter can be one of the following values:
  *     @arg ETIMER_PSCReloadMode_Update: The Prescaler is loaded at the update event.
  *     @arg ETIMER_PSCReloadMode_Immediate: The Prescaler is loaded immediately.
  * @retval None
  */
void ETIMER_PrescalerConfig(ETIMER_TypeDef* ETIMERx, uint16_t Prescaler, uint16_t ETIMER_PSCReloadMode)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_PRESCALER_RELOAD(ETIMER_PSCReloadMode));
    
    /* Set the Prescaler value */
    ETIMERx->PSC = Prescaler;
    
    /* Set or reset the UG Bit */
    ETIMERx->EGR = ETIMER_PSCReloadMode;
}

/**
  * @brief  Specifies the ETIMERx Counter Mode to be used.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_CounterMode: specifies the Counter Mode to be used
  *   This parameter can be one of the following values:
  *     @arg ETIMER_CounterMode_Up: ETIMER Up Counting Mode
  *     @arg ETIMER_CounterMode_Down: ETIMER Down Counting Mode
  *     @arg ETIMER_CounterMode_CenterAligned1: ETIMER Center Aligned Mode1
  *     @arg ETIMER_CounterMode_CenterAligned2: ETIMER Center Aligned Mode2
  *     @arg ETIMER_CounterMode_CenterAligned3: ETIMER Center Aligned Mode3
  * @retval None
  */
void ETIMER_CounterModeConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_CounterMode)
{
    uint16_t tmpcr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_COUNTER_MODE(ETIMER_CounterMode));
    
    tmpcr1 = ETIMERx->CR1;
    
    /* Reset the CMS and DIR Bits */
    tmpcr1 &= (uint16_t)(~((uint16_t)(ETIMER_CR1_DIR | ETIMER_CR1_CMS)));
    
    /* Set the Counter Mode */
    tmpcr1 |= ETIMER_CounterMode;
    
    /* Write to ETIMERx CR1 register */
    ETIMERx->CR1 = tmpcr1;
}

/**
  * @brief  Selects the Input Trigger source
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_InputTriggerSource: The Input Trigger source.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_TS_ITR0: Internal Trigger 0
  *     @arg ETIMER_TS_ITR1: Internal Trigger 1
  *     @arg ETIMER_TS_ITR2: Internal Trigger 2
  *     @arg ETIMER_TS_ITR3: Internal Trigger 3
  *     @arg ETIMER_TS_TI1F_ED: TI1 Edge Detector
  *     @arg ETIMER_TS_TI1FP1: Filtered Timer Input 1
  *     @arg ETIMER_TS_TI2FP2: Filtered Timer Input 2
  *     @arg ETIMER_TS_ETRF: External Trigger input
  * @retval None
  */
void ETIMER_SelectInputTrigger(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_InputTriggerSource)
{
    uint16_t tmpsmcr = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_TRIGGER_SELECTION(ETIMER_InputTriggerSource));
    
    /* Get the ETIMERx SMCR register value */
    tmpsmcr = ETIMERx->SMCR;
    
    /* Reset the TS Bits */
    tmpsmcr &= (uint16_t)(~((uint16_t)ETIMER_SMCR_TS));
    
    /* Set the Input Trigger source */
    tmpsmcr |= ETIMER_InputTriggerSource;
    
    /* Write to ETIMERx SMCR */
    ETIMERx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the ETIMERx Encoder Interface.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_EncoderMode: specifies the ETIMERx Encoder Mode.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *     @arg ETIMER_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *     @arg ETIMER_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                on the level of the other input.
  * @param  ETIMER_IC1Polarity: specifies the IC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Falling: IC Falling edge.
  *     @arg ETIMER_ICPolarity_Rising: IC Rising edge.
  * @param  ETIMER_IC2Polarity: specifies the IC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Falling: IC Falling edge.
  *     @arg ETIMER_ICPolarity_Rising: IC Rising edge.
  * @retval None
  */
void ETIMER_EncoderInterfaceConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_EncoderMode,	uint16_t ETIMER_IC1Polarity, uint16_t ETIMER_IC2Polarity)
{
    uint16_t tmpsmcr = 0;
    uint16_t tmpccmr1 = 0;
    uint16_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_ENCODER_MODE(ETIMER_EncoderMode));
    assert_param(IS_ETIMER_IC_POLARITY(ETIMER_IC1Polarity));
    assert_param(IS_ETIMER_IC_POLARITY(ETIMER_IC2Polarity));

    /* Get the ETIMERx SMCR register value */
    tmpsmcr = ETIMERx->SMCR;

    /* Get the ETIMERx CCMR1 register value */
    tmpccmr1 = ETIMERx->CCMR1;

    /* Get the ETIMERx CCER register value */
    tmpccer = ETIMERx->CCER;
  
    /* Set the encoder Mode */
    tmpsmcr &= (uint16_t)(~((uint16_t)ETIMER_SMCR_SMS));
    tmpsmcr |= ETIMER_EncoderMode;

    /* Select the Capture Compare 1 and the Capture Compare 2 as input */
    tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)ETIMER_CCMR1_CC1S)) & (uint16_t)(~((uint16_t)ETIMER_CCMR1_CC2S)));
    tmpccmr1 |= ETIMER_CCMR1_CC1S_0 | ETIMER_CCMR1_CC2S_0;

    /* Set the TI1 and the TI2 Polarities */
    tmpccer &= (uint16_t)(((uint16_t)~((uint16_t)ETIMER_CCER_CC1P)) & ((uint16_t)~((uint16_t)ETIMER_CCER_CC2P)));
    tmpccer |= (uint16_t)(ETIMER_IC1Polarity | (uint16_t)(ETIMER_IC2Polarity << (uint16_t)4));
  
    /* Write to ETIMERx SMCR */
    ETIMERx->SMCR = tmpsmcr;
    /* Write to ETIMERx CCMR1 */
    ETIMERx->CCMR1 = tmpccmr1;
    /* Write to ETIMERx CCER */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Forces the ETIMERx output 1 waveform to active or inactive level.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ForcedAction_Active: Force active level on OC1REF/强制为有效电平（强制OC1REF为高）
  *     @arg ETIMER_ForcedAction_InActive: Force inactive level on OC1REF/强制为无效电平（强制OC1REF为低）
  * @retval None
  */
void ETIMER_ForcedOC1Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_FORCED_ACTION(ETIMER_ForcedAction));
    
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC1M Bits */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC1M);
    
    /* Configure The Forced output Mode */
    tmpccmr1 |= ETIMER_ForcedAction;
    
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the ETIMERx output 2 waveform to active or inactive level.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ForcedAction_Active: Force active level on OC2REF/强制为有效电平（强制OC2REF为高）
  *     @arg ETIMER_ForcedAction_InActive: Force inactive level on OC2REF./强制为无效电平（强制OC2REF为低）
  * @retval None
  */
void ETIMER_ForcedOC2Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_FORCED_ACTION(ETIMER_ForcedAction));
    
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC2M Bits */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC2M);
    
    /* Configure The Forced output Mode */
    tmpccmr1 |= (uint16_t)(ETIMER_ForcedAction << 8);
    
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the ETIMERx output 3 waveform to active or inactive level.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ForcedAction_Active: Force active level on OC3REF/强制为有效电平（强制OC3REF为高）
  *     @arg ETIMER_ForcedAction_InActive: Force inactive level on OC3REF./强制为无效电平（强制OC3REF为低）
  * @retval None
  */
void ETIMER_ForcedOC3Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_FORCED_ACTION(ETIMER_ForcedAction));
    
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC1M Bits */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC3M);
    
    /* Configure The Forced output Mode */
    tmpccmr2 |= ETIMER_ForcedAction;
    
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Forces the ETIMERx output 4 waveform to active or inactive level.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ForcedAction_Active: Force active level on OC4REF/强制为有效电平（强制OC4REF为高）
  *     @arg ETIMER_ForcedAction_InActive: Force inactive level on OC4REF./强制为无效电平（强制OC4REF为低）
  * @retval None
  */
void ETIMER_ForcedOC4Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ForcedAction)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_FORCED_ACTION(ETIMER_ForcedAction));
    
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC2M Bits */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC4M);
    
    /* Configure The Forced output Mode */
    tmpccmr2 |= (uint16_t)(ETIMER_ForcedAction << 8);
    
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables ETIMERx peripheral Preload register on ARR.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the ETIMERx peripheral Preload register
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_ARRPreloadConfig(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set the ARR Preload Bit */
        ETIMERx->CR1 |= ETIMER_CR1_ARPE;  // 自动重装载预装载允许
    }
    else
    {
        /* Reset the ARR Preload Bit */
        ETIMERx->CR1 &= (uint16_t)~((uint16_t)ETIMER_CR1_ARPE);
    }
}

/**
  * @brief  Selects the ETIMERx peripheral Commutation event.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the Commutation event.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_SelectCOM(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set the COM Bit */
        ETIMERx->CR2 |= ETIMER_CR2_CCUS;
    }
    else
    {
        /* Reset the COM Bit */
        ETIMERx->CR2 &= (uint16_t)~((uint16_t)ETIMER_CR2_CCUS);
    }
}

/**
  * @brief  Sets or Resets the ETIMER peripheral Capture Compare Preload Control bit.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the Capture Compare Preload Control bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_CCPreloadControl(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{ 
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set the CCPC Bit */
        ETIMERx->CR2 |= ETIMER_CR2_CCPC;
    }
    else
    {
        /* Reset the CCPC Bit */
        ETIMERx->CR2 &= (uint16_t)~((uint16_t)ETIMER_CR2_CCPC);
    }
}

/**
  * @brief  Enables or disables the ETIMERx peripheral Preload register on CCR1.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPreload: new state of the ETIMERx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPreload_Enable
  *     @arg ETIMER_OCPreload_Disable
  * @retval None
  */
void ETIMER_OC1PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCPRELOAD_STATE(ETIMER_OCPreload));
    
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC1PE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC1PE);
    
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr1 |= ETIMER_OCPreload;
    
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the ETIMERx peripheral Preload register on CCR2.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPreload: new state of the ETIMERx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPreload_Enable
  *     @arg ETIMER_OCPreload_Disable
  * @retval None
  */
void ETIMER_OC2PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCPRELOAD_STATE(ETIMER_OCPreload));
    
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC2PE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC2PE);
    
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr1 |= (uint16_t)(ETIMER_OCPreload << 8);
    
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the ETIMERx peripheral Preload register on CCR3.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPreload: new state of the ETIMERx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPreload_Enable
  *     @arg ETIMER_OCPreload_Disable
  * @retval None
  */
void ETIMER_OC3PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCPRELOAD_STATE(ETIMER_OCPreload));
    
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC3PE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC3PE);
    
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr2 |= ETIMER_OCPreload;
    
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the ETIMERx peripheral Preload register on CCR4.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPreload: new state of the ETIMERx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPreload_Enable
  *     @arg ETIMER_OCPreload_Disable
  * @retval None
  */
void ETIMER_OC4PreloadConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPreload)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCPRELOAD_STATE(ETIMER_OCPreload));
    
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC4PE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC4PE);
    
    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr2 |= (uint16_t)(ETIMER_OCPreload << 8);
    
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the ETIMERx Output Compare 1 Fast feature.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCFast_Enable: ETIMER output compare fast enable
  *     @arg ETIMER_OCFast_Disable: ETIMER output compare fast disable
  * @retval None
  */
void ETIMER_OC1FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCFAST_STATE(ETIMER_OCFast));
    
    /* Get the ETIMERx CCMR1 register value */
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC1FE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC1FE);
    
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr1 |= ETIMER_OCFast;
    
    /* Write to ETIMERx CCMR1 */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the ETIMERx Output Compare 2 Fast feature.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER 
  * @param  ETIMER_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCFast_Enable: ETIMER output compare fast enable
  *     @arg ETIMER_OCFast_Disable: ETIMER output compare fast disable
  * @retval None
  */
void ETIMER_OC2FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCFAST_STATE(ETIMER_OCFast));
    
    /* Get the ETIMERx CCMR1 register value */
    tmpccmr1 = ETIMERx->CCMR1;
    
    /* Reset the OC2FE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC2FE);
    
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr1 |= (uint16_t)(ETIMER_OCFast << 8);
    
    /* Write to ETIMERx CCMR1 */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the ETIMERx Output Compare 3 Fast feature.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCFast_Enable: ETIMER output compare fast enable
  *     @arg ETIMER_OCFast_Disable: ETIMER output compare fast disable
  * @retval None
  */
void ETIMER_OC3FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCFAST_STATE(ETIMER_OCFast));
    
    /* Get the ETIMERx CCMR2 register value */
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC3FE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC3FE);
    
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr2 |= ETIMER_OCFast;
    
    /* Write to ETIMERx CCMR2 */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the ETIMERx Output Compare 4 Fast feature.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCFast_Enable: ETIMER output compare fast enable
  *     @arg ETIMER_OCFast_Disable: ETIMER output compare fast disable
  * @retval None
  */
void ETIMER_OC4FastConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCFast)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCFAST_STATE(ETIMER_OCFast));
    
    /* Get the ETIMERx CCMR2 register value */
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC4FE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC4FE);
    
    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr2 |= (uint16_t)(ETIMER_OCFast << 8);
    
    /* Write to ETIMERx CCMR2 */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF1 signal on an external event
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCClear_Enable: ETIMER Output clear enable
  *     @arg ETIMER_OCClear_Disable: ETIMER Output clear disable
  * @retval None
  */
void ETIMER_ClearOC1Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCCLEAR_STATE(ETIMER_OCClear));

    tmpccmr1 = ETIMERx->CCMR1;

    /* Reset the OC1CE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC1CE);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr1 |= ETIMER_OCClear;
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF2 signal on an external event
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCClear_Enable: ETIMER Output clear enable
  *     @arg ETIMER_OCClear_Disable: ETIMER Output clear disable
  * @retval None
  */
void ETIMER_ClearOC2Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear)
{
    uint16_t tmpccmr1 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCCLEAR_STATE(ETIMER_OCClear));
    
    tmpccmr1 = ETIMERx->CCMR1;
    /* Reset the OC2CE Bit */
    tmpccmr1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_OC2CE);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr1 |= (uint16_t)(ETIMER_OCClear << 8);
    /* Write to ETIMERx CCMR1 register */
    ETIMERx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF3 signal on an external event
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCClear_Enable: ETIMER Output clear enable
  *     @arg ETIMER_OCClear_Disable: ETIMER Output clear disable
  * @retval None
  */
void ETIMER_ClearOC3Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCCLEAR_STATE(ETIMER_OCClear));
    
    tmpccmr2 = ETIMERx->CCMR2;
    /* Reset the OC3CE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC3CE);
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr2 |= ETIMER_OCClear;
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF4 signal on an external event
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCClear_Enable: ETIMER Output clear enable
  *     @arg ETIMER_OCClear_Disable: ETIMER Output clear disable
  * @retval None
  */
void ETIMER_ClearOC4Ref(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCClear)
{
    uint16_t tmpccmr2 = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCCLEAR_STATE(ETIMER_OCClear));
    
    tmpccmr2 = ETIMERx->CCMR2;
    
    /* Reset the OC4CE Bit */
    tmpccmr2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_OC4CE);
    
    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr2 |= (uint16_t)(ETIMER_OCClear << 8);
    
    /* Write to ETIMERx CCMR2 register */
    ETIMERx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the ETIMERx channel 1 polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPolarity: specifies the OC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPolarity_High: Output Compare active high
  *     @arg ETIMER_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC1PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCPolarity));
    
    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC1P Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC1P);
    tmpccer |= ETIMER_OCPolarity;
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx Channel 1N polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCNPolarity: specifies the OC1N Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCNPolarity_High: Output Compare active high
  *     @arg ETIMER_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC1NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCNPolarity));

    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC1NP Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC1NP);
    tmpccer |= ETIMER_OCNPolarity;
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx channel 2 polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPolarity: specifies the OC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPolarity_High: Output Compare active high
  *     @arg ETIMER_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC2PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCPolarity));
    
    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC2P Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC2P);
    tmpccer |= (uint16_t)(ETIMER_OCPolarity << 4);
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx Channel 2N polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCNPolarity: specifies the OC2N Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCNPolarity_High: Output Compare active high
  *     @arg ETIMER_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC2NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCNPolarity));

    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC2NP Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC2NP);
    tmpccer |= (uint16_t)(ETIMER_OCNPolarity << 4);
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx channel 3 polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPolarity: specifies the OC3 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPolarity_High: Output Compare active high
  *     @arg ETIMER_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC3PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCPolarity));
    
    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC3P Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC3P);
    tmpccer |= (uint16_t)(ETIMER_OCPolarity << 8);
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx Channel 3N polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCNPolarity: specifies the OC3N Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCNPolarity_High: Output Compare active high
  *     @arg ETIMER_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC3NPolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCNPolarity)
{
    uint16_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OCN_POLARITY(ETIMER_OCNPolarity));

    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC3NP Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC3NP);
    tmpccer |= (uint16_t)(ETIMER_OCNPolarity << 8);
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configures the ETIMERx channel 4 polarity.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OCPolarity: specifies the OC4 Polarity
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCPolarity_High: Output Compare active high
  *     @arg ETIMER_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void ETIMER_OC4PolarityConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OCPolarity)
{
    uint16_t tmpccer = 0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OC_POLARITY(ETIMER_OCPolarity));
    
    tmpccer = ETIMERx->CCER;
    
    /* Set or Reset the CC4P Bit */
    tmpccer &= (uint16_t)~((uint16_t)ETIMER_CCER_CC4P);
    tmpccer |= (uint16_t)(ETIMER_OCPolarity << 12);
    
    /* Write to ETIMERx CCER register */
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Enables or disables the ETIMER Capture Compare Channel x.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_Channel: specifies the ETIMER Channel
  *   This parameter can be one of the following values:
  *     @arg ETIMER_Channel_1: ETIMER Channel 1
  *     @arg ETIMER_Channel_2: ETIMER Channel 2
  *     @arg ETIMER_Channel_3: ETIMER Channel 3
  *     @arg ETIMER_Channel_4: ETIMER Channel 4
  * @param  ETIMER_CCx: specifies the ETIMER Channel CCxE bit new state.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_CCx_Enable
  *     @arg ETIMER_CCx_Disable
  * @retval None
  */
void ETIMER_CCxCmd(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_CCx)
{
    uint16_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_CHANNEL(ETIMER_Channel));
    assert_param(IS_ETIMER_CCX(ETIMER_CCx));

    tmp = CCER_CCE_Set << ETIMER_Channel;

    /* Reset the CCxE Bit */
    ETIMERx->CCER &= (uint16_t)(~tmp);

    /* Set or reset the CCxE Bit */ 
    ETIMERx->CCER |= (uint16_t)(ETIMER_CCx << ETIMER_Channel);
}

/**
  * @brief  Enables or disables the ETIMERx Capture Compare Channel xN.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_Channel: specifies the ETIMER Channel
  *   This parameter can be one of the following values:
  *     @arg ETIMER_Channel_1: ETIMER Channel 1
  *     @arg ETIMER_Channel_2: ETIMER Channel 2
  *     @arg ETIMER_Channel_3: ETIMER Channel 3
  * @param  ETIMER_CCxN: specifies the ETIMER Channel CCxNE bit new state.
  *   This parameter can be: ETIMER_CCxN_Enable or ETIMER_CCxN_Disable. 
  * @retval None
  */
void ETIMER_CCxNCmd(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_CCxN)
{
    uint16_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_COMPLEMENTARY_CHANNEL(ETIMER_Channel));
    assert_param(IS_ETIMER_CCXN(ETIMER_CCxN));

    tmp = CCER_CCNE_Set << ETIMER_Channel;

    /* Reset the CCxNE Bit */
    ETIMERx->CCER &= (uint16_t)(~tmp);

    /* Set or reset the CCxNE Bit */ 
    ETIMERx->CCER |=  (uint16_t)(ETIMER_CCxN << ETIMER_Channel);
}

/**
  * @brief  Selects the ETIMER Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output
  *         Compare Mode.
  *         User has to enable this channel using ETIMER_CCxCmd and ETIMER_CCxNCmd functions.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_Channel: specifies the ETIMER Channel
  *   This parameter can be one of the following values:
  *     @arg ETIMER_Channel_1: ETIMER Channel 1
  *     @arg ETIMER_Channel_2: ETIMER Channel 2
  *     @arg ETIMER_Channel_3: ETIMER Channel 3
  *     @arg ETIMER_Channel_4: ETIMER Channel 4
  * @param  ETIMER_OCMode: specifies the ETIMER Output Compare Mode.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OCMode_Timing
  *     @arg ETIMER_OCMode_Active
  *     @arg ETIMER_OCMode_Toggle
  *     @arg ETIMER_OCMode_PWM1
  *     @arg ETIMER_OCMode_PWM2
  *     @arg ETIMER_ForcedAction_Active
  *     @arg ETIMER_ForcedAction_InActive
  * @retval None
  */
void ETIMER_SelectOCxM(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_Channel, uint16_t ETIMER_OCMode)
{
    uint32_t tmp = 0;
    uint16_t tmp1 = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_CHANNEL(ETIMER_Channel));
    assert_param(IS_ETIMER_OCM(ETIMER_OCMode));

    tmp = (uint32_t) ETIMERx;
    tmp += CCMR_Offset;

    tmp1 = CCER_CCE_Set << (uint16_t)ETIMER_Channel;

    /* Disable the Channel: Reset the CCxE Bit */
    ETIMERx->CCER &= (uint16_t) ~tmp1;

    if ((ETIMER_Channel == ETIMER_Channel_1) || (ETIMER_Channel == ETIMER_Channel_3))
    {
        tmp += (ETIMER_Channel >> 1);

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)ETIMER_CCMR1_OC1M);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp |= ETIMER_OCMode;
    }
    else
    {
        tmp += (uint16_t)(ETIMER_Channel - (uint16_t)4) >> (uint16_t)1;

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)ETIMER_CCMR1_OC2M);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp |= (uint16_t)(ETIMER_OCMode << 8);
    }
}

/**
  * @brief  Enables or Disables the ETIMERx Update event.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the ETIMERx UDIS bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_UpdateDisableConfig(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set the Update Disable Bit */
        ETIMERx->CR1 |= ETIMER_CR1_UDIS;
    }
    else
    {
        /* Reset the Update Disable Bit */
        ETIMERx->CR1 &= (uint16_t)~((uint16_t)ETIMER_CR1_UDIS);
    }
}

/**
  * @brief  Configures the ETIMERx Update Request Interrupt source.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_UpdateSource: specifies the Update source.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_UpdateSource_Regular: Source of update is the counter overflow/underflow
                                       or the setting of UG bit, or an update generation
                                       through the slave mode controller.
  *     @arg ETIMER_UpdateSource_Global: Source of update is counter overflow/underflow.
  * @retval None
  */
void ETIMER_UpdateRequestConfig(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_UpdateSource)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_UPDATE_SOURCE(ETIMER_UpdateSource));
    
    if (ETIMER_UpdateSource != ETIMER_UpdateSource_Global)
    {
        /* Set the URS Bit */
        ETIMERx->CR1 |= ETIMER_CR1_URS;
    }
    else
    {
        /* Reset the URS Bit */
        ETIMERx->CR1 &= (uint16_t)~((uint16_t)ETIMER_CR1_URS);
    }
}

/**
  * @brief  Enables or disables the ETIMERx's Hall sensor interface.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  NewState: new state of the ETIMERx Hall sensor interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETIMER_SelectHallSensor(ETIMER_TypeDef* ETIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set the TI1S Bit */
        ETIMERx->CR2 |= ETIMER_CR2_TI1S;
    }
    else
    {
        /* Reset the TI1S Bit */
        ETIMERx->CR2 &= (uint16_t)~((uint16_t)ETIMER_CR2_TI1S);
    }
}

/**
  * @brief  Selects the ETIMERx's One Pulse Mode.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_OPMode: specifies the OPM Mode to be used.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_OPMode_Single
  *     @arg ETIMER_OPMode_Repetitive
  * @retval None
  */
void ETIMER_SelectOnePulseMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_OPMode)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_OPM_MODE(ETIMER_OPMode));
    
    /* Reset the OPM Bit */
    ETIMERx->CR1 &= (uint16_t)~((uint16_t)ETIMER_CR1_OPM);
    /* Configure the OPM Mode */
    ETIMERx->CR1 |= ETIMER_OPMode;
}

/**
  * @brief  Selects the ETIMERx Trigger Output Mode.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_TRGOSource: specifies the Trigger Output source.
  *   This paramter can be one of the following values:
  *
  *  - For all ETIMERx
  *     @arg ETIMER_TRGOSource_Reset:  The UG bit in the ETIMER_EGR register is used as the trigger output (TRGO).
  *     @arg ETIMER_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *     @arg ETIMER_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *
  *     @arg ETIMER_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
  *                              is to be set, as soon as a capture or compare match occurs (TRGO).
  *     @arg ETIMER_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *     @arg ETIMER_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).
  *     @arg ETIMER_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output (TRGO).
  *     @arg ETIMER_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output (TRGO).
  *
  * @retval None
  */
void ETIMER_SelectOutputTrigger(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_TRGOSource)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_TRGO_SOURCE(ETIMER_TRGOSource));
    
    /* Reset the MMS Bits */
    ETIMERx->CR2 &= (uint16_t)~((uint16_t)ETIMER_CR2_MMS);
    /* Select the TRGO source */
    ETIMERx->CR2 |= ETIMER_TRGOSource;
}

/**
  * @brief  Selects the ETIMERx Slave Mode.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_SlaveMode: specifies the Timer Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_SlaveMode_Reset: Rising edge of the selected trigger signal (TRGI) re-initializes
  *                               the counter and triggers an update of the registers.
  *     @arg ETIMER_SlaveMode_Gated:     The counter clock is enabled when the trigger signal (TRGI) is high.
  *     @arg ETIMER_SlaveMode_Trigger:   The counter starts at a rising edge of the trigger TRGI.
  *     @arg ETIMER_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void ETIMER_SelectSlaveMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_SlaveMode)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_SLAVE_MODE(ETIMER_SlaveMode));
    
    /* Reset the SMS Bits */
    ETIMERx->SMCR &= (uint16_t)~((uint16_t)ETIMER_SMCR_SMS);
    /* Select the Slave Mode */
    ETIMERx->SMCR |= ETIMER_SlaveMode;
}

/**
  * @brief  Sets or Resets the ETIMERx Master/Slave Mode.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_MasterSlaveMode_Enable: synchronization between the current timer
  *                                      and its slaves (through TRGO).
  *     @arg ETIMER_MasterSlaveMode_Disable: No action
  * @retval None
  */
void ETIMER_SelectMasterSlaveMode(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_MasterSlaveMode)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_MSM_STATE(ETIMER_MasterSlaveMode));
    
    /* Reset the MSM Bit */
    ETIMERx->SMCR &= (uint16_t)~((uint16_t)ETIMER_SMCR_MSM);

    /* Set or Reset the MSM Bit */
    ETIMERx->SMCR |= ETIMER_MasterSlaveMode;
}

/**
  * @brief  Sets the ETIMERx Counter Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void ETIMER_SetCounter(ETIMER_TypeDef* ETIMERx, uint16_t Counter)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Counter Register value */
    ETIMERx->CNT = Counter;
}

/**
  * @brief  Sets the ETIMERx Autoreload Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void ETIMER_SetAutoreload(ETIMER_TypeDef* ETIMERx, uint16_t Autoreload)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Autoreload Register value */
    ETIMERx->ARR = Autoreload;
}

/**
  * @brief  Sets the ETIMERx Capture Compare1A Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare1A: specifies the Capture Compare1A register new value.
  * @retval None
  */
void ETIMER_SetCompare1A(ETIMER_TypeDef* ETIMERx, uint16_t Compare1A)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare1 Register value */
    ETIMERx->CCR1A = Compare1A;
}

/**
  * @brief  Sets the ETIMERx Capture Compare2A Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare2A: specifies the Capture Compare2A register new value.
  * @retval None
  */
void ETIMER_SetCompare2A(ETIMER_TypeDef* ETIMERx, uint16_t Compare2A)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare2 Register value */
    ETIMERx->CCR2A = Compare2A;
}

/**
  * @brief  Sets the ETIMERx Capture Compare3A Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare3A: specifies the Capture Compare3A register new value.
  * @retval None
  */
void ETIMER_SetCompare3A(ETIMER_TypeDef* ETIMERx, uint16_t Compare3A)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare3 Register value */
    ETIMERx->CCR3A = Compare3A;
}

/**
  * @brief  Sets the ETIMERx Capture Compare4A Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare4A: specifies the Capture Compare4A register new value.
  * @retval None
  */
void ETIMER_SetCompare4A(ETIMER_TypeDef* ETIMERx, uint16_t Compare4A)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare4 Register value */
    ETIMERx->CCR4A = Compare4A;
}

/**
  * @brief  Sets the ETIMERx Capture Compare1B Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare1B: specifies the Capture Compare1B register new value.
  * @retval None
  */
void ETIMER_SetCompare1B(ETIMER_TypeDef* ETIMERx, uint16_t Compare1B)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare1 Register value */
    ETIMERx->CCR1A = Compare1B;
}

/**
  * @brief  Sets the ETIMERx Capture Compare2B Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare2B: specifies the Capture Compare2B register new value.
  * @retval None
  */
void ETIMER_SetCompare2B(ETIMER_TypeDef* ETIMERx, uint16_t Compare2B)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare2 Register value */
    ETIMERx->CCR2A = Compare2B;
}

/**
  * @brief  Sets the ETIMERx Capture Compare3B Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare3B: specifies the Capture Compare3B register new value.
  * @retval None
  */
void ETIMER_SetCompare3B(ETIMER_TypeDef* ETIMERx, uint16_t Compare3B)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare3 Register value */
    ETIMERx->CCR3A = Compare3B;
}

/**
  * @brief  Sets the ETIMERx Capture Compare4B Register value
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  Compare4B: specifies the Capture Compare4B register new value.
  * @retval None
  */
void ETIMER_SetCompare4B(ETIMER_TypeDef* ETIMERx, uint16_t Compare4B)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Set the Capture Compare4 Register value */
    ETIMERx->CCR4A = Compare4B;
}

/**
  * @brief  Sets the ETIMERx Input Capture 1 prescaler.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPSC: specifies the Input Capture1 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPSC_DIV1: no prescaler
  *     @arg ETIMER_ICPSC_DIV2: capture is done once every 2 events
  *     @arg ETIMER_ICPSC_DIV4: capture is done once every 4 events
  *     @arg ETIMER_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void ETIMER_SetIC1Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx));
    assert_param(IS_ETIMER_IC_PRESCALER(ETIMER_ICPSC));
    
    /* Reset the IC1PSC Bits */
    ETIMERx->CCMR1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_IC1PSC);
    /* Set the IC1PSC value */
    ETIMERx->CCMR1 |= ETIMER_ICPSC;
}

/**
  * @brief  Sets the ETIMERx Input Capture 2 prescaler.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPSC: specifies the Input Capture2 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPSC_DIV1: no prescaler
  *     @arg ETIMER_ICPSC_DIV2: capture is done once every 2 events
  *     @arg ETIMER_ICPSC_DIV4: capture is done once every 4 events
  *     @arg ETIMER_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void ETIMER_SetIC2Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx));
    assert_param(IS_ETIMER_IC_PRESCALER(ETIMER_ICPSC));
    
    /* Reset the IC2PSC Bits */
    ETIMERx->CCMR1 &= (uint16_t)~((uint16_t)ETIMER_CCMR1_IC2PSC);
    /* Set the IC2PSC value */
    ETIMERx->CCMR1 |= (uint16_t)(ETIMER_ICPSC << 8);
}

/**
  * @brief  Sets the ETIMERx Input Capture 3 prescaler.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPSC: specifies the Input Capture3 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPSC_DIV1: no prescaler
  *     @arg ETIMER_ICPSC_DIV2: capture is done once every 2 events
  *     @arg ETIMER_ICPSC_DIV4: capture is done once every 4 events
  *     @arg ETIMER_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void ETIMER_SetIC3Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx));
    assert_param(IS_ETIMER_IC_PRESCALER(ETIMER_ICPSC));
    
    /* Reset the IC3PSC Bits */
    ETIMERx->CCMR2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_IC3PSC);
    /* Set the IC3PSC value */
    ETIMERx->CCMR2 |= ETIMER_ICPSC;
}

/**
  * @brief  Sets the ETIMERx Input Capture 4 prescaler.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPSC: specifies the Input Capture4 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPSC_DIV1: no prescaler
  *     @arg ETIMER_ICPSC_DIV2: capture is done once every 2 events
  *     @arg ETIMER_ICPSC_DIV4: capture is done once every 4 events
  *     @arg ETIMER_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void ETIMER_SetIC4Prescaler(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPSC)
{  
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx));
    assert_param(IS_ETIMER_IC_PRESCALER(ETIMER_ICPSC));
    
    /* Reset the IC4PSC Bits */
    ETIMERx->CCMR2 &= (uint16_t)~((uint16_t)ETIMER_CCMR2_IC4PSC);
    
    /* Set the IC4PSC value */
    ETIMERx->CCMR2 |= (uint16_t)(ETIMER_ICPSC << 8);
}

/**
  * @brief  Sets the ETIMERx Clock Division value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_CKD: specifies the clock division value.
  *   This parameter can be one of the following value:
  *     @arg ETIMER_CKD_DIV1: TDTS = Tck_tim
  *     @arg ETIMER_CKD_DIV2: TDTS = 2*Tck_tim
  *     @arg ETIMER_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void ETIMER_SetClockDivision(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_CKD)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_CKD_DIV(ETIMER_CKD));
    
    /* Reset the CKD Bits */
    ETIMERx->CR1 &= (uint16_t)~((uint16_t)ETIMER_CR1_CKD);
    
    /* Set the CKD value */
    ETIMERx->CR1 |= ETIMER_CKD;
}

/**
  * @brief  Gets the ETIMERx Input Capture 1A value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Capture Compare 1A Register value.
  */
uint16_t ETIMER_GetCapture1A(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Capture 1 Register value */
    return ETIMERx->CCR1A;
}

/**
  * @brief  Gets the ETIMERx Input Capture 2A value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Capture Compare 2A Register value.
  */
uint16_t ETIMER_GetCapture2A(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Capture 2 Register value */
    return ETIMERx->CCR2A;
}

/**
  * @brief  Gets the ETIMERx Input Capture 3A value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Capture Compare 3A Register value.
  */
uint16_t ETIMER_GetCapture3A(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Capture 3 Register value */
    return ETIMERx->CCR3A;
}

/**
  * @brief  Gets the ETIMERx Input Capture 4A value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Capture Compare 4A Register value.
  */
uint16_t ETIMER_GetCapture4A(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Capture 4 Register value */
    return ETIMERx->CCR4A;
}

/**
  * @brief  Gets the ETIMERx Counter value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Counter Register value.
  */
uint16_t ETIMER_GetCounter(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Counter Register value */
    return ETIMERx->CNT;
}

/**
  * @brief  Gets the ETIMERx Prescaler value.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @retval Prescaler Register value.
  */
uint16_t ETIMER_GetPrescaler(ETIMER_TypeDef* ETIMERx)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Get the Prescaler Register value */
    return ETIMERx->PSC;
}

/**
  * @brief  Checks whether the specified ETIMER flag is set or not.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_FLAG_Update: ETIMER update Flag
  *     @arg ETIMER_FLAG_CC1: ETIMER Capture Compare 1 Flag
  *     @arg ETIMER_FLAG_CC2: ETIMER Capture Compare 2 Flag
  *     @arg ETIMER_FLAG_CC3: ETIMER Capture Compare 3 Flag
  *     @arg ETIMER_FLAG_CC4: ETIMER Capture Compare 4 Flag
  *     @arg ETIMER_FLAG_COM: ETIMER Commutation Flag
  *     @arg ETIMER_FLAG_Trigger: ETIMER Trigger Flag
  *     @arg ETIMER_FLAG_Break: ETIMER Break Flag
  *     @arg ETIMER_FLAG_CC1OF: ETIMER Capture Compare 1 overcapture Flag
  *     @arg ETIMER_FLAG_CC2OF: ETIMER Capture Compare 2 overcapture Flag
  *     @arg ETIMER_FLAG_CC3OF: ETIMER Capture Compare 3 overcapture Flag
  *     @arg ETIMER_FLAG_CC4OF: ETIMER Capture Compare 4 overcapture Flag   
  * @retval The new state of ETIMER_FLAG (SET or RESET).
  */
FlagStatus ETIMER_GetFlagStatus(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_FLAG)
{ 
    FlagStatus bitstatus = RESET;  
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_GET_FLAG(ETIMER_FLAG));

    if ((ETIMERx->SR & ETIMER_FLAG) != (uint16_t)RESET)
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
  * @brief  Clears the ETIMERx's pending flags.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_FLAG: specifies the flag bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ETIMER_FLAG_Update: ETIMER update Flag
  *     @arg ETIMER_FLAG_CC1: ETIMER Capture Compare 1 Flag
  *     @arg ETIMER_FLAG_CC2: ETIMER Capture Compare 2 Flag
  *     @arg ETIMER_FLAG_CC3: ETIMER Capture Compare 3 Flag
  *     @arg ETIMER_FLAG_CC4: ETIMER Capture Compare 4 Flag
  *     @arg ETIMER_FLAG_COM: ETIMER Commutation Flag
  *     @arg ETIMER_FLAG_Trigger: ETIMER Trigger Flag
  *     @arg ETIMER_FLAG_Break: ETIMER Break Flag
  *     @arg ETIMER_FLAG_CC1OF: ETIMER Capture Compare 1 overcapture Flag
  *     @arg ETIMER_FLAG_CC2OF: ETIMER Capture Compare 2 overcapture Flag
  *     @arg ETIMER_FLAG_CC3OF: ETIMER Capture Compare 3 overcapture Flag
  *     @arg ETIMER_FLAG_CC4OF: ETIMER Capture Compare 4 overcapture Flag   
  * @retval None
  */
void ETIMER_ClearFlag(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_FLAG)
{  
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_CLEAR_FLAG(ETIMER_FLAG));

    /* Clear the flags */
    ETIMERx->SR = (uint16_t)(~ETIMER_FLAG);
}

/**
  * @brief  Checks whether the ETIMERx interrupt has occurred or not.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_IT: specifies the ETIMER interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_IT_Update: ETIMER update Interrupt source
  *     @arg ETIMER_IT_CC1: ETIMER Capture Compare 1 Interrupt source
  *     @arg ETIMER_IT_CC2: ETIMER Capture Compare 2 Interrupt source
  *     @arg ETIMER_IT_CC3: ETIMER Capture Compare 3 Interrupt source
  *     @arg ETIMER_IT_CC4: ETIMER Capture Compare 4 Interrupt source
  *     @arg ETIMER_IT_COM: ETIMER Commutation Interrupt source
  *     @arg ETIMER_IT_Trigger: ETIMER Trigger Interrupt source
  *     @arg ETIMER_IT_Break: ETIMER Break Interrupt source 
  * @retval The new state of the ETIMER_IT(SET or RESET).
  */
ITStatus ETIMER_GetITStatus(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT)
{
    ITStatus bitstatus = RESET;  
    uint16_t itstatus = 0x0, itenable = 0x0;
    
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_GET_IT(ETIMER_IT));

    itstatus = ETIMERx->SR & ETIMER_IT;    // 获取中断标志
    itenable = ETIMERx->DIER & ETIMER_IT;  // 获取中断使能状态
    
    if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
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
  * @brief  Clears the ETIMERx's interrupt pending bits.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_IT: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ETIMER_IT_Update: ETIMER update Interrupt source
  *     @arg ETIMER_IT_CC1: ETIMER Capture Compare 1 Interrupt source
  *     @arg ETIMER_IT_CC2: ETIMER Capture Compare 2 Interrupt source
  *     @arg ETIMER_IT_CC3: ETIMER Capture Compare 3 Interrupt source
  *     @arg ETIMER_IT_CC4: ETIMER Capture Compare 4 Interrupt source
  *     @arg ETIMER_IT_COM: ETIMER Commutation Interrupt source
  *     @arg ETIMER_IT_Trigger: ETIMER Trigger Interrupt source
  *     @arg ETIMER_IT_Break: ETIMER Break Interrupt source   
  * @retval None
  */
void ETIMER_ClearITPendingBit(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_IT)
{
    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    assert_param(IS_ETIMER_IT(ETIMER_IT));
    
    /* Clear the IT pending Bit */
    ETIMERx->SR = (uint16_t)(~ETIMER_IT);
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Rising
  *     @arg ETIMER_ICPolarity_Falling
  * @param  ETIMER_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICSelection_DirectTI: ETIMER Input 1 is selected to be connected to TI1.
  *     @arg ETIMER_ICSelection_IndirectTI: ETIMER Input 1 is selected to be connected to TI2.
  *     @arg ETIMER_ICSelection_TRC: ETIMER Input 1 is selected to be connected to TRC.
  * @param  ETIMER_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void ETIMER_TI1_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Disable the Channel 1: Reset the CC1E Bit */
    ETIMERx->CCER &= (uint16_t)~((uint16_t)ETIMER_CCER_CC1E);  // capture disable
    tmpccmr1 = ETIMERx->CCMR1;
    tmpccer  = ETIMERx->CCER;
    /* Select the Input and set the filter */
    tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)ETIMER_CCMR1_CC1S)) & ((uint16_t)~((uint16_t)ETIMER_CCMR1_IC1F)));
    tmpccmr1 |= (uint16_t)(ETIMER_ICSelection << 0);
    tmpccmr1 |= (uint16_t)(ETIMER_ICFilter << 4);
  
    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(ETIMER_CCER_CC1P));   // 上升沿捕获
    tmpccer |= (uint16_t)(ETIMER_ICPolarity | (uint16_t)ETIMER_CCER_CC1E);  // 配置捕获边沿及使能捕获 

    /* Write to ETIMERx CCMR1 and CCER registers */
    ETIMERx->CCMR1 = tmpccmr1;
    ETIMERx->CCER  = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Rising
  *     @arg ETIMER_ICPolarity_Falling
  * @param  ETIMER_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICSelection_DirectTI: ETIMER Input 2 is selected to be connected to TI2.
  *     @arg ETIMER_ICSelection_IndirectTI: ETIMER Input 2 is selected to be connected to TI1.
  *     @arg ETIMER_ICSelection_TRC: ETIMER Input 2 is selected to be connected to TRC.
  * @param  ETIMER_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void ETIMER_TI2_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Disable the Channel 2: Reset the CC2E Bit */
    ETIMERx->CCER &= (uint16_t)~((uint16_t)ETIMER_CCER_CC2E);  // capture disable
    tmpccmr1 = ETIMERx->CCMR1;
    tmpccer  = ETIMERx->CCER;
    tmp = (uint16_t)(ETIMER_ICPolarity << 4);
    /* Select the Input and set the filter */
    tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)ETIMER_CCMR1_CC2S)) & ((uint16_t)~((uint16_t)ETIMER_CCMR1_IC2F)));
    tmpccmr1 |= (uint16_t)(ETIMER_ICSelection << 8);
    tmpccmr1 |= (uint16_t)(ETIMER_ICFilter << 12);

    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(ETIMER_CCER_CC2P));    // 上升沿捕获
    tmpccer |= (uint16_t)(tmp | (uint16_t)ETIMER_CCER_CC2E);   // 配置捕获边沿及使能捕获 
  
    /* Write to ETIMERx CCMR1 and CCER registers */
    ETIMERx->CCMR1 = tmpccmr1;
    ETIMERx->CCER  = tmpccer;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Rising
  *     @arg ETIMER_ICPolarity_Falling
  * @param  ETIMER_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICSelection_DirectTI: ETIMER Input 3 is selected to be connected to TI3.
  *     @arg ETIMER_ICSelection_IndirectTI: ETIMER Input 3 is selected to be connected to TI4.
  *     @arg ETIMER_ICSelection_TRC: ETIMER Input 3 is selected to be connected to TRC.
  * @param  ETIMER_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void ETIMER_TI3_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter)
{
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Disable the Channel 3: Reset the CC3E Bit */
    ETIMERx->CCER &= (uint16_t)~((uint16_t)ETIMER_CCER_CC3E);   // capture disable
    tmpccmr2 = ETIMERx->CCMR2;
    tmpccer  = ETIMERx->CCER;
    tmp = (uint16_t)(ETIMER_ICPolarity << 8);
    /* Select the Input and set the filter */
    tmpccmr2 &= (uint16_t)(((uint16_t)~((uint16_t)ETIMER_CCMR2_CC3S)) & ((uint16_t)~((uint16_t)ETIMER_CCMR2_IC3F)));
    tmpccmr2 |= (uint16_t)(ETIMER_ICSelection << 0);
    tmpccmr2 |= (uint16_t)(ETIMER_ICFilter << 4);
    
    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(ETIMER_CCER_CC3P));    // 上升沿捕获
    tmpccer |= (uint16_t)(tmp | (uint16_t)ETIMER_CCER_CC3E);  // 配置捕获边沿及使能捕获 
  
    /* Write to ETIMERx CCMR2 and CCER registers */
    ETIMERx->CCMR2 = tmpccmr2;
    ETIMERx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  ETIMERx: where x can be 1 to select the ETIMERx peripheral.
  *   This parameter can be one of the following values:
  *     ETIMER
  * @param  ETIMER_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICPolarity_Rising
  *     @arg ETIMER_ICPolarity_Falling
  * @param  ETIMER_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg ETIMER_ICSelection_DirectTI: ETIMER Input 4 is selected to be connected to TI4.
  *     @arg ETIMER_ICSelection_IndirectTI: ETIMER Input 4 is selected to be connected to TI3.
  *     @arg ETIMER_ICSelection_TRC: ETIMER Input 4 is selected to be connected to TRC.
  * @param  ETIMER_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
void ETIMER_TI4_Config(ETIMER_TypeDef* ETIMERx, uint16_t ETIMER_ICPolarity, uint16_t ETIMER_ICSelection, uint16_t ETIMER_ICFilter)
{
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Check the parameters */
    assert_param(IS_ETIMER_ALL_PERIPH(ETIMERx)); 
    
    /* Disable the Channel 4: Reset the CC4E Bit */
    ETIMERx->CCER &= (uint16_t)~((uint16_t)ETIMER_CCER_CC4E);
    tmpccmr2 = ETIMERx->CCMR2;
    tmpccer  = ETIMERx->CCER;
    tmp = (uint16_t)(ETIMER_ICPolarity << 12);
    /* Select the Input and set the filter */
    tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)ETIMER_CCMR2_CC4S) & ((uint16_t)~((uint16_t)ETIMER_CCMR2_IC4F)));
    tmpccmr2 |= (uint16_t)(ETIMER_ICSelection << 8);
    tmpccmr2 |= (uint16_t)(ETIMER_ICFilter << 12);
  
    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(ETIMER_CCER_CC4P));   // 上升沿捕获
    tmpccer |= (uint16_t)(tmp | (uint16_t)ETIMER_CCER_CC4E);  // 配置捕获边沿及使能捕获 

    /* Write to ETIMERx CCMR2 and CCER registers */
    ETIMERx->CCMR2 = tmpccmr2;
    ETIMERx->CCER  = tmpccer;
}


