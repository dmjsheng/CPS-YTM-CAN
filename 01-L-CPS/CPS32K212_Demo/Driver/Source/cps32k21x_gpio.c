/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_gpio.h"
#include "cps32k21x_rcc.h"


/** 
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
    if (GPIOx == GPIOA)
    {
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOA_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOA_RST, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOB_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOB_RST, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOC_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOC_RST, DISABLE);
    }  
    else if (GPIOx == GPIOD)
    {
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOD_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOD_RST, DISABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOE_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOE_RST, DISABLE);
    }
}

/** 
  * @brief  Deinitializes the Alternate Functions registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_AFIODeInit(void)
{
	GPIOA->AFR1 = (uint32_t)0xFFFFFFFF;
	GPIOA->AFR2 = (uint32_t)0xFFFFFFFF;
	GPIOB->AFR1 = (uint32_t)0xFFFFFFFF;
	GPIOB->AFR2 = (uint32_t)0xFFFFFFFF;
	GPIOC->AFR1 = (uint32_t)0xFFFFFFFF;
	GPIOC->AFR2 = (uint32_t)0xFFFFFFFF;
	GPIOD->AFR1 = (uint32_t)0xFFFFFFFF;
	GPIOD->AFR2 = (uint32_t)0xFFFFFFFF;
	GPIOE->AFR1 = (uint32_t)0xFFFFFFFF;
	GPIOE->AFR2 = (uint32_t)0xFFFFFFFF;
}

/** 
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t pinpos = 0;
	uint32_t pos = 0;
	uint32_t currentpin = 0;
    uint32_t AFR_temp = 0;
    
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
	assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
	assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));
	assert_param(IS_GPIO_DRIVE(GPIO_InitStruct->GPIO_Drive));
	assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

	/* ------------------------- Configure the port pins ---------------- */
	/*-- GPIO Mode Configuration --*/
	for (pinpos = 0x00; pinpos < 16u; pinpos++)
	{
		pos = ((uint32_t)0x01) << pinpos;
		/* Get the port pins position */
		currentpin = (uint32_t)(GPIO_InitStruct->GPIO_Pin) & pos;

		if (currentpin == pos)
		{
			if (pinpos < 8u)  
			{
				pos = pinpos << 2u;
                AFR_temp = ((uint32_t)(GPIOx->AFR1 >> pos) & 0x0FUL);
                if (0x0FUL == AFR_temp)
                {
                    GPIOx->AFR1 &= ~(uint32_t)(GPIO_MODE << pos); 
                }
			}
			else
			{
				pos = (pinpos - 8u) << 2u;
                AFR_temp = ((uint32_t)(GPIOx->AFR2 >> pos) & 0x0FUL);
                if (0x0FUL == AFR_temp)
                {
                    GPIOx->AFR2 &= ~(uint32_t)(GPIO_MODE << pos);
                }
			}
			 
			if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
			{
				/* set gpio direction to output */
				GPIOx->DIRCR |= (uint32_t)(GPIO_PIN_MODE_OUT << pinpos);   // output mode
				
				/* Output mode configuration, pull-push or OD*/
				GPIOx->OTYPER &= ~(uint32_t)(GPIO_OTYPER_OD << pinpos);  // default pull-push output model
				GPIOx->OTYPER |=  (uint32_t)(GPIO_InitStruct->GPIO_OType << pinpos);
			}
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
            {
                /* set gpio direction to input */
				GPIOx->DIRCR &= ~(uint32_t)(GPIO_PIN_MODE_OUT << pinpos);   // default input mode
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_ANA)
            {
            	if (pinpos < 8u)
            	{
            		pos = pinpos << 2u;
            		GPIOx->AFR1 |= (uint32_t)(GPIO_MODE << pos);
            	}
            	else
            	{
            		pos = (pinpos - 8u) << 2u;
            		GPIOx->AFR2 |= (uint32_t)(GPIO_MODE << pos);  
            	}
            }
            
			/* Pull-up Pull down resistor configuration */
			pos = pinpos << 1u;
			GPIOx->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD << pos);  // 乘2，两位一起移
			GPIOx->PUPDR |=  (uint32_t)(GPIO_InitStruct->GPIO_PuPd << pos);

			GPIOx->SLEWCR &= ~(uint32_t)(GPIO_SLEWCR_MASK << pinpos);   // 端口高压摆率
			GPIOx->SLEWCR |=  (uint32_t)(GPIO_InitStruct->GPIO_Speed << pinpos); 

			GPIOx->DRVCR &= ~(uint32_t)(GPIO_DRVCR_MASK << pinpos);    // 高驱动强度
			GPIOx->DRVCR |=  (uint32_t)(GPIO_InitStruct->GPIO_Drive << pinpos); 
        }
    }
}

/** 
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /*Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin   = GPIO_Pin_None;        /*<! No pin selected, 0 */
    GPIO_InitStruct->GPIO_Mode  = GPIO_Mode_ANA;      	/*<! 端口默认模拟功能, default : 0x02 */
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_High;   	/*<! 端口电压转换速度，默认高速, 0 */
	GPIO_InitStruct->GPIO_Drive = GPIO_Drive_High;      /*<! 端口驱动强度，默认高驱动强度, 0 */
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;     	/*<! 输出类型：推挽输出(复位后默认值),0 */
    GPIO_InitStruct->GPIO_PuPd  = GPIO_PuPd_NOPULL;  	/*<! 上拉下拉情况，默认禁止上下拉, 0*/
}

/** 
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0;
    
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return (bitstatus);
}

/** 
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->IDR);
}

/** 
  * @brief  Enable the specified GPIO port Debounce of SYNC_EN.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  NewState: new state of the GPIOX_INDBEN.SYNC_EN.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBSyncCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
  /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		GPIOx->INDBEN |=  GPIO_DIDB_SYNC_EN;
	}
	else
	{
		GPIOx->INDBEN &= ~GPIO_DIDB_SYNC_EN;
	}
}

/** 
  * @brief  Set the specified GPIOx peripheral pins Debounce function.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  DB_Pin: 端子Pxn(n=0~15)消抖使能配置位
  *   This parameter can be any combination of the following values:
       @arg GPIO_DIDB_PIN0_EN     
       @arg GPIO_DIDB_PIN1_EN     
       @arg GPIO_DIDB_PIN2_EN     
       @arg GPIO_DIDB_PIN3_EN     
       @arg GPIO_DIDB_PIN4_EN     
       @arg GPIO_DIDB_PIN5_EN     
       @arg GPIO_DIDB_PIN6_EN    
       @arg GPIO_DIDB_PIN7_EN
       @arg GPIO_DIDB_PIN8_EN  
       @arg GPIO_DIDB_PIN9_EN  
       @arg GPIO_DIDB_PIN10_EN  
       @arg GPIO_DIDB_PIN11_EN  
       @arg GPIO_DIDB_PIN12_EN  
       @arg GPIO_DIDB_PIN13_EN  
       @arg GPIO_DIDB_PIN14_EN  
       @arg GPIO_DIDB_PIN15_EN  
       
  * @param  NewState: new state of DB function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBPinSyncCmd(GPIO_TypeDef* GPIOx, uint32_t DB_Pin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_DIDB_PINxEN(DB_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		GPIOx->INDBEN |=  DB_Pin;
	}
	else
	{
		GPIOx->INDBEN &= ~DB_Pin;
	}
}

/** 
  * @brief  Enable or disable the specified GPIO port Debounce Clock.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  NewState: new state of Debounce CLock enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void GPIO_DBClkCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		GPIOx->DBCLKCR |=  GPIO_DBCLK_EN;
	}
	else
	{
		GPIOx->DBCLKCR &= ~GPIO_DBCLK_EN;
	}
}

/** 
  * @brief  Set the specified GPIO port Debounce Clock
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  DBClk: DB Clock of cycle .
  *   This parameter can be the following values:
  		@arg GPIO_DBCLK_1CYCLE           
  		@arg GPIO_DBCLK_2CYCLE           
  		@arg GPIO_DBCLK_4CYCLE           
  		@arg GPIO_DBCLK_8CYCLE            
  		@arg GPIO_DBCLK_16CYCLE           
  		@arg GPIO_DBCLK_32CYCLE          
  		@arg GPIO_DBCLK_64CYCLE           
  		@arg GPIO_DBCLK_128CYCLE          
  		@arg GPIO_DBCLK_256CYCLE          
  		@arg GPIO_DBCLK_512CYCLE          
  		@arg GPIO_DBCLK_1024CYCLE         
  		@arg GPIO_DBCLK_2048CYCLE         
  		@arg GPIO_DBCLK_4096CYCLE         
  		@arg GPIO_DBCLK_8192CYCLE         
  		@arg GPIO_DBCLK_16384CYCLE        
		@arg GPIO_DBCLK_32768CYCLE        
  		
  * @retval None.
  */
void GPIO_SetDBClk(GPIO_TypeDef* GPIOx, uint32_t DBClk)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_DBCLK_CYCLE(DBClk));
    
    /* Set the specified GPIO port DB Clock */
    GPIOx->DBCLKCR &= ~GPIO_DBCLK_CYCLEMASK;
    GPIOx->DBCLKCR |=  DBClk;
}

/** 
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if (((GPIOx->ODR) & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/** 
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->ODR);
}

/** 
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written to high.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODSET |= (uint32_t)GPIO_Pin;
}

/** 
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODCLR |= (uint32_t)GPIO_Pin;
}

/** 
  * @brief  Sets or clears the selected data port bits.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enum values:
  * @arg    Bit_RESET: to clear the port pin
  * @arg    Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal != Bit_RESET)
    {
        GPIOx->ODSET |= (uint32_t)GPIO_Pin;
    }
    else
    {
        GPIOx->ODCLR |= (uint32_t)GPIO_Pin;
    }
}

/** 
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR = PortVal;
}

/** 
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral 
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).               
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /*Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->ODR ^= (uint32_t)GPIO_Pin;   
}

/** 
  * @brief  Enables or disables pull-up or pull-down
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral 
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).   
  * @param  GPIO_PUPD: set the GPIO peripheral port pin Pull-up or Pull-down
  *         This parameter can be the following values:
  			@arg GPIO_PuPd_NOPULL 
  			@arg GPIO_PuPd_UP     
  			@arg GPIO_PuPd_DOWN   
  * @retval None
  */
void GPIO_PinPuPdCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t GPIO_PUPD)
{
	uint32_t pinpos = 0;
	uint32_t pos = 0;
	uint32_t currentpin = 0;
	
	/*Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_PUPD(GPIO_PUPD));
	
	/*set the GPIO peripheral port pin Pu or Pd*/
	for (pinpos = 0; pinpos < 0x10; pinpos++)
	{
		pos = ((uint32_t)0x01) << pinpos;
		
		/* Get the port pins position */
		currentpin = (uint32_t)GPIO_Pin & pos;
		
		if (currentpin == pos)
		{
			pos = pinpos << 1u;
			GPIOx->PUPDR &= ~(uint32_t)(GPIO_PUPDR_PUPD << pos); 
			GPIOx->PUPDR |=  (uint32_t)(GPIO_PUPD << pos); 
		}
	}   
}

/** 
  * @brief  Enables or disables port Drive/端口驱动强度使能或禁止
  * @param  GPIOx: where x can be (A..E) to select the GPIO peripheral 
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).   
  * @param  NewState: new state of Port Drive enable.
  *         This parameter can be: ENABLE or DISABLE.
  			ENABLE  : 高驱动强度(复位默认)
  			DISABLE : 低驱动强度
  * @retval None
  */
void GPIO_PortDriveCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, FunctionalState NewState)
{
	uint32_t pinpos = 0;
	uint32_t pos = 0;
	uint32_t currentpin = 0;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* set the GPIO peripheral port pin Pu or Pd */
	for (pinpos = 0; pinpos < 0x10; pinpos++)
	{
		pos = ((uint32_t)0x01) << pinpos;
		
		/* Get the port pins position */
		currentpin = (uint32_t)GPIO_Pin & pos;
		
		if (currentpin == pos)
		{
			if (NewState != DISABLE)
			{
			    GPIOx->DRVCR &= ~(uint32_t)(0x01UL << pinpos);  // 高驱动强度
			} 
			else   // DISABLE
			{
				GPIOx->DRVCR |=  (uint32_t)(0x01UL << pinpos);  // 低驱动强度
			}
		}
	}
}

/** 
  * @brief   Changes the mapping of the specified pin.
  * @param   GPIOx: where x can be (A..E) to select the GPIO peripheral                    
  * @param   GPIO_PinSource: specifies the pin for the Alternate function.
  *          This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @param   GPIO_AF: selects the pin to used as Alternate function.
  *          This parameter can be can be (0..0x0F):
  * @retval  None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint8_t GPIO_PinSource, uint8_t GPIO_AF)
{
    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AF(GPIO_AF));

  	if (GPIO_PinSource < 0x08u)
  	{
        GPIOx->AFR1 &= ~(uint32_t)(((uint32_t)0xF) << ((GPIO_PinSource & 0x0Fu) << 2u));
        GPIOx->AFR1 |=  (uint32_t)(((uint32_t)GPIO_AF) << ((GPIO_PinSource & 0x0Fu) << 2u));
  	}
    else
    {
    	GPIO_PinSource &= 0x0F;
        GPIO_PinSource -= 0x08;
        GPIOx->AFR2 &= ~(uint32_t)(((uint32_t)0xF) << ((GPIO_PinSource & 0x0Fu) << 2u));
        GPIOx->AFR2 |=  (uint32_t)(((uint32_t)GPIO_AF) << ((GPIO_PinSource & 0x0Fu) << 2u));
    }
}

/** 
  * @brief  读取中断原始状态寄存器，不论是否使能相应管脚中断
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *     This parameter can be  GPIOx where x can be (A..E).
  * @retval 返回GPIOx各管脚中断状态
  */
uint16_t GPIO_EXIT_ReadRawIntSR(GPIO_TypeDef* GPIOx)
{
	return (uint16_t)(GPIOx->RAWINTSR);
}

/** 
  * @brief  获取GPIO管脚中断原始状态，不论中断是否使能，都可以读到中断状态
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *     This parameter can be  GPIOx where x can be (A..E).
   * @param  GPIO_Pin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval 返回GPIOx各管脚中断状态
  */
BitAction GPIO_EXIT_Get_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	BitAction status = Bit_RESET;

	if ((GPIOx->RAWINTSR & ((uint32_t)GPIO_Pin)) != 0)
	{
		status = Bit_SET;
	}

	return (status);
}

/** 
  * @brief  获取GPIO管脚中断标志位, 只有使能中断才能读到中断状态
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *     This parameter can be  GPIOx where x can be (A..E).
   * @param  GPIO_Pin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval 返回GPIOx各管脚中断状态
  */
BitAction GPIO_EXIT_Get_IT_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	BitAction status = Bit_RESET;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    
	if ((GPIOx->MSKINTSR & ((uint32_t)GPIO_Pin)) != 0)
	{
		status = Bit_SET;
	}

	return (status);
}

/** 
  * @brief  清除GPIO端口中断标志位
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *     This parameter can be  GPIOx where x can be (A..E).
   * @param  GPIO_Pin:  specifies the port bit to read.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval 返回GPIOx各管脚中断状态
  */
void GPIO_EXIT_Clear_IT_Flag(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    
	GPIOx->INTCLR |= (uint32_t)GPIO_Pin;
}

/** 
  * @brief  Fills each EXIT_InitStruct member with its default value.
  * @param  EXIT_InitStruct : pointer to a EXIT_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_EXIT_StructInit(EXIT_InitTypeDef* EXIT_InitStruct)
{
    /*Reset GPIO init structure parameters values */
    EXIT_InitStruct->EXIT_Pin_En      = EXIT_Pin_Disable;        /*<! GPIO中断禁止 */
	EXIT_InitStruct->EXIT_IT_Type     = EXIT_IT_Type_Edge;       /*<! 边沿触发中断方式 */
	EXIT_InitStruct->EXIT_IT_Polarity = EXIT_IT_Pol_LowFalling;  /*<! 低电平或下降沿触发中断 */
	EXIT_InitStruct->EXIT_Flag_Clr    = EXIT_Flag_Keep;          /*<! 中断标志保持 */
	EXIT_InitStruct->EXIT_AnyEdge     = EXIT_AnyEdge_Disable;    /*<! 双边沿触发中断禁止 */
}

/** 
  * @brief  Config the GPIO pin used as EXTI Line.
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *     This parameter can be  GPIOx where x can be (A..E).
  * @param  GPIO_Pin: specifies the port bit to read.
  *     This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @param  EXIT_InitStructure: pointer to a EXIT_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_EXTILineConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, EXIT_InitTypeDef* EXIT_InitStructure)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

	/*!< 中断类型，电平触发，边沿触发 */
	if (EXIT_IT_Type_Level == EXIT_InitStructure->EXIT_IT_Type)   
	{
		GPIOx->INTTYPCR |=  (uint32_t)GPIO_Pin;  // 电平触发中断
	}
	else
	{
		GPIOx->INTTYPCR &= ~(uint32_t)GPIO_Pin;  // 边沿触发中断
	}

	/*!<中断极性，高电平或上升沿触发，低电平或下降沿触发方式 */
	if (EXIT_IT_Pol_HighRising == EXIT_InitStructure->EXIT_IT_Polarity) 
	{
		GPIOx->INTPOLCR |=  (uint32_t)GPIO_Pin;  // 高电平或上升沿触发中断
	}
	else
	{
		GPIOx->INTPOLCR &= ~(uint32_t)GPIO_Pin;  // 低电平或下降沿触发中断 
	}

	/*!<端口任意边沿触发中断 */
	if (EXIT_AnyEdge_Enable == EXIT_InitStructure->EXIT_AnyEdge) 
	{
		GPIOx->INTANY |=  (uint32_t)GPIO_Pin;  // 上升沿、下降沿都触发中断
	}
	else
	{
		GPIOx->INTANY &= ~(uint32_t)GPIO_Pin;  // 中断触发沿由中断极性位决定
	}
	
	/*!<中断标志位清除 */
	if (EXIT_Flag_Clear == EXIT_InitStructure->EXIT_Flag_Clr)  
	{
		GPIOx->INTCLR |=  (uint32_t)GPIO_Pin;  // 清除对应的中断标志位
	}
	else
	{
		GPIOx->INTCLR &= ~(uint32_t)GPIO_Pin;  // 保留中断标志位
	}
	
	/*!<中断使能设置 */
	if (EXIT_Pin_Enable == EXIT_InitStructure->EXIT_Pin_En)
	{
		GPIOx->INTEN |=  (uint32_t)GPIO_Pin;
	}
	else
	{
		GPIOx->INTEN &= ~(uint32_t)GPIO_Pin;
	}
}


