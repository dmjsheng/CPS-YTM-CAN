/* Includes ------------------------------------------------------------------*/
#include "cps32k21x_spi.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the SPIx peripheral registers to their default
  *         reset values .
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef* SPIx)
{
    /* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
    if (SPIx == SPI1)
	{
	    /* Enable SPI1 reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SPI1_RST, ENABLE);
    	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    	
    	/* Release SPI1 from reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SPI1_RST, DISABLE);
	}
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *     contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
	uint32_t tmpreg = 0;
	
	/* Check the SPI parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx)); 
	assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
	assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
	assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));

    /*------------------------- SPIx CR1 Configuration ------------------------*/

	tmpreg |= (uint32_t)((SPI_InitStruct->SPI_Mode) |\
	                      (SPI_InitStruct->SPI_CPOL) |\
	                      (SPI_InitStruct->SPI_CPHA) |\
	                      (SPI_InitStruct->SPI_BaudRatePrescaler));
	/* Write to SPIx CR */
	SPIx->CR = tmpreg;
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct : pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;  // 从机模式
	SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;    // 时钟极性低电平
	SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;  // 相位极性第一边沿采集
	SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // DIV2
}

/**
  * @brief  Enables or disables the specified SPIx peripheral.
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  NewState: new state of the SPIx peripheral. 
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	
	if (NewState != DISABLE)
	{
		/* Enable the selected SPIx peripheral */
		SPIx->CR |= SPI_SPEN_ENABLE;
	}
	else
	{
		/* Disable the selected SPIx peripheral */
		SPIx->CR &= ~SPI_SPEN_ENABLE;
	}
}

/**
  * @brief  SPIx主机模式发送并接收数据
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  TxData: 主机发送的数据
  * @retval 主机接收到的来自从机的数据
  */
uint8_t SPI_Master_TransmitReceive(SPI_TypeDef* SPIx, uint8_t TxData)
{
    /* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
    
	SPIx->DATA = TxData;
    while ((SPIx->SR & SPI_FLAG_SPIF) != SPI_FLAG_SPIF) {;}
        
    return SPIx->DATA;
}

/**
  * @brief  SPIx从机模式发送数据
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  TxData: 从机发送的数据
  * @retval None
  */
void SPI_Slave_SendData(SPI_TypeDef* SPIx, uint8_t TxData)
{
    /* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
    while ((SPIx->SR & SPI_FLAG_SPIF) != SPI_FLAG_SPIF) {;}
    SPIx->DATA = TxData;
}

/**
  * @brief  SPIx从机模式接收数据.
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval 返回从机接收到的数据
  */
uint8_t SPI_Slave_ReceiveData(SPI_TypeDef* SPIx)
{
    /* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx)); 

    while ((SPIx->SR & SPI_FLAG_SPIF) != SPI_FLAG_SPIF) {;}

    return SPIx->DATA;
}

/**
  * @brief  Enables or disables the SSN output for the selected SPIx.
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  NewState: new state of the SPIx SSN output. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_SSNOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	/* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE)
	{
		/* Enable the selected SPI SS output */
		SPIx->SSN &= SPI_SSN_Low;
	}
	else
	{
		/* Disable the selected SPI SS output */
		SPIx->SSN |= SPI_SSN_High;
	}
}

/**
  * @brief  Checks whether the specified SPIx flag is set or not.
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  SPI_FLAG: specifies the SPI flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SPI_FLAG_SPIF: End of transmission interrupt flag
  *     @arg SPI_FLAG_WCOL: Write Conflict Interruption flag
  *     @arg SPI_FLAG_SSERR: Slave SSN error flag
  *     @arg SPI_FLAG_MDF:  Slave mode error flag
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
	FlagStatus bitstatus = RESET;
	
	/* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	assert_param(IS_SPI_FLAG(SPI_FLAG));
	
	/* Check the status of the specified SPI flag */
	if ((SPIx->SR & SPI_FLAG) != (uint16_t)RESET)
	{
		/* SPI_FLAG is set */
		bitstatus = SET;
	}
	else
	{
		/* SPI_FLAG is reset */
		bitstatus = RESET;
	}
	/* Return the SPI_FLAG status */
	return  bitstatus;
}


