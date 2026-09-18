#include "cps32k21x_aspi.h"
#include "cps32k21x_rcc.h"


/**
  * @brief  Deinitializes the ASPIx peripheral registers to their default
  *         reset values .
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @retval None
  */
void ASPI_DeInit(ASPI_TypeDef* ASPIx)
{
    /* Check the parameters */
	assert_param(IS_SPI_ALL_PERIPH(SPIx));
	
    if (ASPIx == ASPI)
	{
	    /* Enable SPI1 reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ASPI_RST, ENABLE);
    	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    	
    	/* Release SPI1 from reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ASPI_RST, DISABLE);
	}
}

/**
  * @brief  Fills each ASPI_InitStruct member with its default value.
  * @param  SPI_InitStruct : pointer to a ASPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void ASPI_StructInit(ASPI_InitTypeDef* ASPI_InitStruct)
{
	ASPI_InitStruct->ASPI_Mode = ASPI_Mode_Slave;  // 从机模式
	ASPI_InitStruct->ASPI_CPOL = ASPI_CPOL_Low;    // 时钟极性低电平
	ASPI_InitStruct->ASPI_CPHA = ASPI_CPHA_1Edge;  // 相位极性第一边沿采集
	ASPI_InitStruct->ASPI_BaudRatePrescaler = 0;   // DIV2
}

/**
  * @brief  Initializes the ASPIx peripheral according to the specified 
  *         parameters in the ASPI_InitStruct.
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  ASPI_InitStruct: pointer to a ASPI_InitTypeDef structure that
  *     contains the configuration information for the specified ASPI peripheral.
  * @retval None
  */
void ASPI_Init(ASPI_TypeDef * ASPIx, ASPI_InitTypeDef *ASPI_InitStruct)
{
   	uint32_t tmpreg = 0;
	
	/* Check the SPI parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx)); 
	assert_param(IS_ASPI_MODE(ASPI_InitStruct->ASPI_Mode));
	assert_param(IS_ASPI_CPOL(ASPI_InitStruct->ASPI_CPOL));
	assert_param(IS_ASPI_CPHA(ASPI_InitStruct->ASPI_CPHA));
	assert_param(IS_ASPI_BAUDRATE_PRESCALER(ASPI_InitStruct->ASPI_BaudRatePrescaler));

    /*------------------------- ASPIx MSTR Configuration ------------------------*/
    tmpreg = (ASPIx->SPCR) & (~ASPI_Mode_Master);
//    tmpreg |= ((uint32_t)ASPI_InitStruct->ASPI_Mode << 30);
    tmpreg |= ((uint32_t)ASPI_InitStruct->ASPI_Mode << 0);
    ASPIx->SPCR = tmpreg;
    
    /*------------------------- ASPIx CPOL Configuration ------------------------*/
    tmpreg = (ASPIx->SPCMD) & (~ASPI_CPOL_High);
//    tmpreg |= (uint32_t)(ASPI_InitStruct->ASPI_CPOL << 1) ;
    tmpreg |= (uint32_t)(ASPI_InitStruct->ASPI_CPOL << 0) ;
    ASPIx->SPCMD |= tmpreg;
    
    /*------------------------- ASPIx CPHA Configuration ------------------------*/
    tmpreg = (ASPIx->SPCMD) & (~ASPI_CPHA_2Edge);
    tmpreg |= (uint32_t)(ASPI_InitStruct->ASPI_CPHA);
    ASPIx->SPCMD |= tmpreg;
    
    /*------------------------- ASPIx CPHA Configuration ------------------------*/
    ASPIx->SPBR = ((uint32_t)ASPI_InitStruct->ASPI_BaudRatePrescaler << 8);
}

/**
  * @brief  ASPI功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
     ASPIx->SPCR &= ~ASPI_SPE_MASK;
    
     if (NewState == ENABLE)
     {
        ASPIx->SPCR |= (uint32_t)(1 << 0);
     } 
     else 
     {
        ASPIx->SPCR &= ~(uint32_t)(1 << 0);
     }         
}


/**
  * @brief  ASPI模式选择,四线模式，三线模式
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  mode: Select the ASPIx peripheral workmode
  * 	This parameter can be one of the following values: ASPI_SPMS_4LINE, ASPI_SPMS_3LINE.
  * @retval 主机接收到的来自从机的数据
  */
void ASPI_SPMS_Select(ASPI_TypeDef * ASPIx, ASPI_SPMS_t mode)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));

    ASPIx->SPCR &= ~ASPI_SPMS_MASK;
    
    if (mode == ASPI_SPMS_4LINE)  /* 4 lines spi */
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 24);
    }
    else if (mode == ASPI_SPMS_3LINE) /* 3 lines spi */
    {
        ASPIx->SPCR |=  (uint32_t)(1 << 24);  
    }
    else
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 24);
    }
}

/**
  * @brief  ASPIx 选择输出引脚是CMOS输出还是开漏输出
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  mode: 选择输出脚的模式
  * @retval None
  */
void ASPI_SPOM_Select(ASPI_TypeDef * ASPIx, ASPI_SPOM_t mode)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    ASPIx->SPPCR &= ~ASPI_SPOM_MASK;
    
    if (mode == ASPI_SPOM_CMOS)
    {
        ASPIx->SPPCR &= ~ASPI_SPOM_MASK;
    }
    else
    {
        ASPIx->SPPCR |= (uint32_t)(mode << 18);    
    }
   
}

/**
  * @brief  SPIx 回环模式2选择设置，
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: ASPI_SPLP2_NORMAL,ASPI_SPLP2_LOOPBACK
  * @param  TxData: 主机发送的数据
  * @retval 主机接收到的来自从机的数据
  */
void ASPI_SPLP2_Select(ASPI_TypeDef * ASPIx, ASPI_SPLP2_t mode)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));

    ASPIx->SPPCR  &= ~ASPI_SPLP2_MASK;

    if (mode == ASPI_SPLP2_NORMAL)
    {
        ASPIx->SPPCR &= ~ASPI_SPLP2_MASK;
    }
    else
    {
        ASPIx->SPPCR |= (uint32_t)(mode << 17);    
    }
}

/**
  * @brief  SPIx 回环模式1选择
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: ASPI_SPLP1_NORMAL,ASPI_SPLP1_LOOPBACK
  * @param  TxData: 主机发送的数据
  * @retval 主机接收到的来自从机的数据
  */
void ASPI_SPLP1_Select(ASPI_TypeDef * ASPIx, ASPI_SPLP1_t mode)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));

    ASPIx->SPPCR &= ~ASPI_SPLP1_MASK;

    if (mode == ASPI_SPLP1_NORMAL)
    {
        ASPIx->SPPCR &= ~ASPI_SPLP1_MASK;
    }
    else
    {
        ASPIx->SPPCR |= (uint32_t)(mode << 16);    
    }
}

/**
  * @brief  ASPI选择读接收缓冲区 Or 发送缓冲区
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  mode ：ASPI_SPDR_RECEIVE：接收缓冲区  
  *                ASPI_SPDR_SEND：发送缓冲区
  * @retval None
  */
void ASPI_SPRDTD_Select(ASPI_TypeDef* ASPIx, ASPI_SPDR_t mode)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    ASPIx->SPDCR1 &= ~ASPI_SPDCR1_MASK;   // SPDR读取接收缓冲区

    if (mode == ASPI_SPDR_RECEIVE)  // 0
    {
       ASPIx->SPDCR1 &= ~ASPI_SPDCR1_MASK;
    }
    else
    {
       ASPIx->SPDCR1 |= (uint32_t)(0x01UL << 3);    
    }
}

/**
  * @brief  ASPIx 设置发送FIFO的阈值
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  Depth：发送FIFO阈值(0 ~ 3)
  * @retval 无
  */
void ASPI_FIFO_TTRG_Set(ASPI_TypeDef * ASPIx, uint32_t Depth)
{
    assert_param(IS_ASPI_ALL_PERIPH(SPIx));   
    assert_param(IS_ASPI_TTRG(Depth));    
    
    if (Depth > 3)
    {
        Depth = 3;
    }
    ASPIx->SPDCR2 &= ~ASPI_TTRG_MASK;
    ASPIx->SPDCR2 |=  (uint32_t)(Depth << 8);    
}

/**
  * @brief  ASPIx 设置接收FIFO的阈值
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  Depth： 接收FIFO阈值
  * @retval 无
  */
void ASPI_FIFO_RTRG_Set(ASPI_TypeDef * ASPIx,uint32_t Depth)
{
    assert_param(IS_ASPI_ALL_PERIPH(SPIx));   
    assert_param(IS_ASPI_RTRG(Depth));    

    ASPIx->SPDCR1 &= ~ASPI_RTRG_MASK;
    ASPIx->SPDCR1 |=  (uint32_t)(Depth << 0);    
}

/**
  * @brief  发送缓冲区空中断使能/禁止
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPTIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
   /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    ASPIx->SPCR &= ~ASPI_SPTIE_MASK;

    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1 << 20);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 20);
    }         
}

/**
  * @brief  SPIIE功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPIIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    ASPIx->SPCR &= ~ASPI_SPIIE_MASK;
    
    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1 << 18);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 18);
    }         
}

/**
  * @brief  SPRIE功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPRIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    ASPIx->SPCR &= ~ASPI_SPRIE_MASK;
    
    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1<<17);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1<<17);
    }         
}

/**
  * @brief  SPEIE功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPEIE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    ASPIx->SPCR &= ~ASPI_SPEIE_MASK;
    
    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1 << 16);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 16);
    }         
}

/**
  * @brief  MODFEN功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_MODFEN_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    ASPIx->SPCR &= ~ASPI_MODFEN_MASK;

    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1<<14);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1<<14);
    }         
}

/**
  * @brief  BFDS功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_BFDS_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    ASPIx->SPCR &= ~ASPI_BFDS_MASK;
    
    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1 << 13);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 13);
    }         
}

/**
  * @brief  SCKASE功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SCKASE_Cmd(ASPI_TypeDef * ASPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    ASPIx->SPCR &= ~ASPI_SCKAES_MASK;
    
    if (NewState == ENABLE)
    {
        ASPIx->SPCR |= (uint32_t)(1 << 12);
    } 
    else 
    {
        ASPIx->SPCR &= ~(uint32_t)(1 << 12);
    }         
}

/**
  * @brief  SLNDEN功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SLNDEN_Cmd(ASPI_TypeDef* ASPIx, FunctionalState NewState,uint16_t SSL_Delay_Cycle)
{
    /* Check the parameters */
    assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ASPI_SSL_DELAY(SSL_Delay_Cycle));

    if (NewState != DISABLE)
    {
        /* Enable the selected SPIx peripheral */
        ASPIx->SPCMD |= ASPI_SLNDEN_ENABLE;
        ASPIx->SPDLR &= ~(ASPI_SSL_DELAY_MASK); 
        ASPIx->SPDLR |= (SSL_Delay_Cycle<<8);   
    }
    else
    {
        /* Disable the selected SPIx peripheral */
        ASPIx->SPCMD &= ~ASPI_SLNDEN_ENABLE;
    }
}

/**
  * @brief  SPNDL功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SPNDL_Cmd(ASPI_TypeDef* ASPIx, FunctionalState NewState,uint16_t SPN_Delay_Cycle)
{
	/* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ASPI_SSL_DELAY(SPN_Delay_Cycle));
    
	if (NewState != DISABLE)
	{
		/* Enable the selected SPIx peripheral */
		ASPIx->SPCMD |=  ASPI_SPNDL_ENABLE;
        ASPIx->SPDLR &= ~(ASPI_SPN_DELAY_MASK); 
        ASPIx->SPDLR |=  (SPN_Delay_Cycle << 16);   
	}
	else
	{
		/* Disable the selected SPIx peripheral */
		ASPIx->SPCMD &= ~ASPI_SPNDL_ENABLE;
	}
}

/**
  * @brief  SCKDL功能使能
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @param  NewState: ENABLE/DISABLE
  * @retval  无
  */
void ASPI_SCKDL_Cmd(ASPI_TypeDef* ASPIx, FunctionalState NewState,uint16_t SCK_Delay_Cycle)
{
	/* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ASPI_SSL_DELAY(SCK_Delay_Cycle));
    
	if ((NewState != DISABLE))
	{
		/* Enable the selected SPIx peripheral */
		ASPIx->SPCMD |=  ASPI_SCKDEN_ENABLE;
        ASPIx->SPDLR &= ~(ASPI_SCK_DELAY_MASK); 
        ASPIx->SPDLR |=  (SCK_Delay_Cycle);   
	}
	else
	{
		/* Disable the selected SPIx peripheral */
		ASPIx->SPCMD &= ~ASPI_SCKDEN_ENABLE;
	}
}

/**
  * @brief  SPIx主机模式发送并接收数据
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  TxData: 主机发送的数据
  * @retval 主机接收到的来自从机的数据
  */
uint8_t ASPI_Master_TransmitReceive(ASPI_TypeDef* ASPIx, uint8_t TxData)
{
    /*Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(SPIx));  
    
    while (((ASPIx->SPSR) & ASPI_SPTEF_FLAG) == 0){};

	ASPIx->SPDR = TxData;

    while (((ASPIx->SPSR) & ASPI_SPRF_FLAG) == 0);  
    
    return  ASPIx->SPDR;   
}


/**
  * @brief  ASPIx主机模式发送数据
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  TxData: 主机发送的数据
  * @retval  无
  */

void ASPI_MasterSend(ASPI_TypeDef * ASPIx, uint32_t TxData)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));

    while (((ASPIx->SPSR) & ASPI_SPTEF_FLAG) == 0);   // must add this
    ASPIx->SPDR = TxData;
}


/**
  * @brief  ASPIx主机模式接收数据
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval 主机接收到的来自从机的数据
  */
uint32_t ASPI_MasterReceive(ASPI_TypeDef * ASPIx)
{
    uint32_t recvData;
    
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    while (((ASPIx->SPSR) & ASPI_SPTEF_FLAG) == 0); // must add this
     
    ASPIx->SPDR = 0xff;
    
    while (((ASPIx->SPSR) & (ASPI_SPRF_FLAG)) == 0); 
    
    if (ASPIx->SPSR == 0)
    {
        /* Do nothing, just for read SPSR reg and avoid compile warning */
    }
    
    ASPIx->SPDCR1 &= ~(ASPI_SPRDTD_READ_SEND_BUFFER);  // choose rxdata_buf
    recvData = ASPIx->SPDR;// READ DATA
    ASPIx->SPSCR = 0xfd800000;
    
    return recvData;
}


/**
  * @brief  ASPIx从机模式发送数据
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI.
  * @param  TxData: 从机发送的数据
  * @retval  无
  */
void ASPI_SlaveSend(ASPI_TypeDef * ASPIx, uint32_t txData)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
  
    while (((ASPIx->SPSR) & ASPI_SPTEF_FLAG) == 0); // must add this
    ASPIx->SPDR = txData;
}

/**
  * @brief  ASPIx  FIFO 复位
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: ASPI1.
  * @retval 无
  */
void ASPI_ResetFIFO(ASPI_TypeDef * ASPIx)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    ASPIx->SPFCR = (uint32_t)0x1;  
}

/**
  * @brief  ASPIx从机模式接收数据
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval 从机接收到的来自主机的数据
  */
uint32_t ASPI_SlaveReceive(ASPI_TypeDef * ASPIx)
{
    uint32_t recvData;
    
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));

    while (((ASPIx->SPSR) & ASPI_SPRF_FLAG) == 0); 
    
    if (ASPIx->SPSR  == 0)
    {
        /* Do nothing, just for read SPSR reg and avoid compile warning */
    }
    
    ASPIx->SPDCR1 &= ~(ASPI_SPRDTD_READ_SEND_BUFFER);  // choose rxdata_buf
    recvData = ASPIx->SPDR;
    ASPIx->SPSCR = 0xfd800000;
    
    return recvData;
}

/**
  * @brief  ASPIx清楚中断标准位
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @param  FLAG: 中断标志位
  * @retval 无
  */
void  ASPI_ClearFlag(ASPI_TypeDef * ASPIx,ASPI_INTTERUPT_FLAG_t Flag)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    switch (Flag)
    {
        case ASPI_OVRFC_FLAG:  /*clear 0VRFC FLAG*/
             ASPIx->SPSCR |= (uint32_t)(1<<24);
        break;
        
        case ASPI_MODFC_FLAG:   /*clear MODFC FLAG*/
             ASPIx->SPSCR |= (uint32_t)(1<<26);
        break;
        
        case ASPI_UDRFC_FLAG:   /*clear UDRFC FLAG*/
             ASPIx->SPSCR |= (uint32_t)(1<<28);
        break;
        
        case ASPI_SPIEFC_FLAG:   /*clear SPIEFC FLAG*/
             ASPIx->SPSCR |= (uint32_t)(1<<29);
        break;
        
        case ASPI_SPRFC_FLAG:  /*clear SPRFC FLAG*/
             ASPIx->SPSCR |= (uint32_t)(0x01UL << 31);
        break;
        
        default: break;
    }
}

/**
  * @brief  ASPIx 读取ASPI发送FIFO的状态寄存器的值
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval ASPI接收FIFO状态寄存器的值
  */
uint32_t ASPI_GetSPTFSRFlag(ASPI_TypeDef * ASPIx)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    return ASPIx->SPTFSR;
}

/**
  * @brief  ASPIx 读取ASPI接收FIFO的状态寄存器的值
  * @param  ASPIx: Select the ASPIx peripheral 
  * 	This parameter can be one of the following values: APSI.
  * @retval ASPI接收FIFO状态寄存器的值
  */
uint32_t ASPI_GetSPRFSRFlag(ASPI_TypeDef * ASPIx)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    return ASPIx->SPRFSR;
}

/**
  * @brief  ASPIx读取状态寄存器的值
  * @param  SPIx: Select the SPIx peripheral 
  * 	This parameter can be one of the following values: SPI0, SPI1.
  * @retval 状态寄存器的值
  */
uint32_t ASPI_GetSPSRFlag(ASPI_TypeDef * ASPIx)
{
    /* Check the parameters */
	assert_param(IS_ASPI_ALL_PERIPH(ASPIx));
    
    return ASPIx->SPSR;
}         

