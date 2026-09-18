#include "cps32k21x_euart.h"
#include "cps32k21x_rcc.h"


/** 
  * @brief  Deinitializes the EUARTx peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EUART_DeInit(EUART_TypeDef* EUARTx)
{
    if (EUARTx == EUART0)
    {
        /* Enable EUART0 reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_EUART0_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

        /* Release EUART0 from reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_EUART0_RST, DISABLE);
    }
    else if (EUARTx == EUART1)
    {
        /* Enable EUART1 reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_EUART1_RST, ENABLE);
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

        /* Release EUART1 from reset state */
        RCC_PeriphResetCmd(RCC, RCC_APBPeriph_EUART1_RST, DISABLE);
    }
}

/** 
  * @brief  IEUARTx peripheral software reset, reset all digital logic and registers except IEUARTx_GLOBAL
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   	This parameter can be one of the following values:
  *   		EUART0, EUART1 
  * @retval None
  */
void EUART_Soft_Reset(EUART_TypeDef* EUARTx)
{
    EUARTx->GLOBAL |=  EUART_GLOBAL_RST_Mask;   /* RST=1: Module is reset */
	EUARTx->GLOBAL &= ~EUART_GLOBAL_RST_Mask;   /* RST=0: Module is not reset */
}

/**
  * @brief  Fills each EUART_InitStruct member with its default value.
  * @param  EUART_InitStruct : pointer to a EUART_InitTypeDef structure which will be initialized.
  * @retval None
  */
void EUART_StructInit(EUART_InitTypeDef* EUART_InitStruct)
{
    EUART_InitStruct->SysclkFreq = SYSCLK_FREQ_48Mz;     /*<! 系统时钟频率（unit : Hz） */
    EUART_InitStruct->BaudRate   = 9600U;                /*<! 通信波特率9600 */
    EUART_InitStruct->WordLength = WordLength_8bit;      /*<! 数据位长度8位 */
    EUART_InitStruct->StopBits   = StopBits_1bit;        /*<! 停止位1位 */
    EUART_InitStruct->ParitySel  = Parity_None;          /*<! 奇偶校验位无 */
    EUART_InitStruct->WorkMode   = WorkMode_Rx;          /*<! 工作模式为接收 */
    EUART_InitStruct->IDLE_Type  = IDLE_TYPE_AfterStop;  /*<! 空闲字符计数在停止位之后开始 */
}

/**
  * @brief  Initializes the EUARTx peripheral according to the specified
  *         parameters in the EUART_InitStruct.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   	This parameter can be one of the following values:
  *   		EUART0, EUART1
  * @param  EUART_InitStruct: pointer to a EUART_InitTypeDef structure
  *         that contains the configuration information for the specified EUARTx peripheral.   
  * @retval None
  */
void EUART_Init(EUART_TypeDef* EUARTx, EUART_InitTypeDef* EUART_InitStruct)
{
    uint8_t osr_tmp = 0;
	float baudrate = 0;
	uint32_t tmpbaud = 0;
    uint32_t tmpctrl = 0;

    tmpbaud = EUARTx->BAUD;   // 读取EUARTx_BAUD寄存器内容
    tmpctrl = EUARTx->CTRL;   // 读取EUARTx_CTRL寄存器内容

    /* 1. configures the EUART communication baud rate  */
    tmpbaud &= ~EUART_BAUD_OSR_Mask;    
    tmpbaud |=  EUART_BAUD_OSR(0x0F);     /* Take "OR" with default 0x0F since writing 0 will result 0x0F */
    osr_tmp  =  (uint8_t)((tmpbaud >> 24) & 0x1FUL);   // Get EUART_BAUD.OSR value
    baudrate =  (1.0 * EUART_InitStruct->SysclkFreq) / ((osr_tmp + 1) * EUART_InitStruct->BaudRate);
    tmpbaud &= ~EUART_BAUD_SBR_Mask;      /* Clear SBR field */
    tmpbaud |=  EUART_BAUD_SBR(SHE_4_5_RU(baudrate)); 

    /* 2. configures the EUART communication data bits  */
    switch (EUART_InitStruct->WordLength)
    {
        case WordLength_7bit:
            tmpctrl |=  EUART_CTRL_M7_Mask;   // 接收发送7位数据帧
            tmpbaud &= ~EUART_BAUD_M10_Mask;  // 接收或发送7到9位数据帧
            break;
            
        case WordLength_8bit:
            tmpctrl &= ~EUART_CTRL_M_Mask;    // 接收和发送8位数据帧
            tmpctrl &= ~EUART_CTRL_M7_Mask;   // 接收和发送8位到10位的数据帧
            tmpbaud &= ~EUART_BAUD_M10_Mask;  // 接收或发送7到9位数据帧
            break;
            
        case WordLength_9bit:
            tmpctrl |=  EUART_CTRL_M_Mask;    // 接收和发送9位数据帧
            tmpctrl &= ~EUART_CTRL_M7_Mask;   // 接收和发送8位到10位的数据帧
            tmpbaud &= ~EUART_BAUD_M10_Mask;  // 接收或发送7到9位数据帧
            break;
            
        case WordLength_10bit:
            tmpbaud |=  EUART_BAUD_M10_Mask;  // 接收或发送 10 位数据帧
            tmpctrl &= ~EUART_CTRL_M7_Mask;   // 接收和发送8位到10位的数据帧
            break;
            
        default :
            tmpctrl &= ~EUART_CTRL_M_Mask;    // 接收和发送8位数据帧
            tmpctrl &= ~EUART_CTRL_M7_Mask;   // 接收和发送8位到10位的数据帧
            tmpbaud &= ~EUART_BAUD_M10_Mask;  // 接收或发送7到9位数据帧
            break;
    }

    /* 3. configures the EUART communication stop bits  */
    switch (EUART_InitStruct->StopBits)
    {
        case StopBits_1bit:
            tmpbaud &= ~EUART_BAUD_SBNS_Mask;     /* SBNS=0: 停止位1位 */
            break;

        case StopBits_2bit:
            tmpbaud |=  EUART_BAUD_SBNS_Mask;     /* SBNS=1: 停止位2位 */
            break;

        default : 
            tmpbaud &= ~EUART_BAUD_SBNS_Mask;     /* SBNS=0: 停止位1位 */
            break;
    }

    /* 4. configures the EUART parity  */
    switch (EUART_InitStruct->ParitySel)
    {
        case Parity_None:   
            tmpctrl &= ~EUART_CTRL_PE_Mask;  // 禁止奇偶校验
            break;
            
        case Parity_Odd:
            tmpctrl |=  EUART_CTRL_PE_Mask;  // 使能奇偶校验
            tmpctrl &= ~EUART_CTRL_PT_Mask;  // 奇校验
            break;
            
        case Parity_Even:
            tmpctrl |=  EUART_CTRL_PE_Mask;  // 使能奇偶校验
            tmpctrl |=  EUART_CTRL_PT_Mask;  // 偶校验
            break;
            
        default : 
            tmpctrl &= ~EUART_CTRL_PE_Mask;  // 禁止奇偶校验
            break;
    }

    /* 5. configures the EUART work mode  */
    if (WorkMode_Rx == EUART_InitStruct->WorkMode)   // Rx enable
    {
        tmpctrl |=  EUART_CTRL_RE_Mask;   // Rx Enable
        tmpctrl &= ~EUART_CTRL_TE_Mask;   // Tx Disable
    }
    else if (WorkMode_Tx == EUART_InitStruct->WorkMode)  // Tx enable
    {
        tmpctrl |=  EUART_CTRL_TE_Mask;   // Tx Enable
        tmpctrl &= ~EUART_CTRL_RE_Mask;   // Rx Disable
    }
    else if (WorkMode_TxRx == EUART_InitStruct->WorkMode)
    {
        tmpctrl |=  EUART_CTRL_RE_Mask;   // Rx Enable
        tmpctrl |=  EUART_CTRL_TE_Mask;   // Tx Enable
    }
    else  // Others
    {
        tmpctrl &= ~EUART_CTRL_RE_Mask;   // Rx Disable
        tmpctrl &= ~EUART_CTRL_TE_Mask;   // Tx Disable
    }
    
    /* 6. configures the type of IDLE level */
    if (IDLE_TYPE_AfterStop == EUART_InitStruct->IDLE_Type)
    {
        tmpctrl |=  EUART_CTRL_ILT_Mask;  // 空闲字符计数在停止位之后开始
    }
    else
    {
        tmpctrl &= ~EUART_CTRL_ILT_Mask;  // 空闲字符计数在起始位之后开始
    }

    EUARTx->BAUD = tmpbaud;
    EUARTx->CTRL = tmpctrl;
}

/** 
  * @brief  Enables or disables the specified EUARTx peripheral Transmit function.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  NewState: new state of the EUARTx Transmit function.
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EUART_Tx_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState)
{
    if (NewState != DISABLE)
	{
		/* Enable the EUARTx transmit function */
		EUARTx->CTRL |=  EUART_CTRL_TE_Mask;
	}
	else
	{
		/* Disable the EUARTx transmit function */
		EUARTx->CTRL &= ~EUART_CTRL_TE_Mask;
	}
}

/** 
  * @brief  Enables or disables the specified EUARTx peripheral receive function.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  NewState: new state of the EUARTx receive function.
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EUART_Rx_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState)
{
    if (NewState != DISABLE)
	{
		/* Enable the EUARTx transmit function */
		EUARTx->CTRL |=  EUART_CTRL_RE_Mask;
	}
	else
	{
		/* Disable the EUARTx transmit function */
		EUARTx->CTRL &= ~EUART_CTRL_RE_Mask;
	}
}

/** 
  * @brief  Enables or disables LIN break field dectect function.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  NewState: new state of the EUARTx receive function.
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EUART_LIN_BreakDetect_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState)
{
    if (NewState != DISABLE)
	{
		/* Enable LIN Break Field Dectect function  */
		EUARTx->STAT |=  EUART_STAT_LBKDE_Mask;
	}
	else
	{
		/* Disable LIN Break Field Dectect function */
		EUARTx->STAT &= ~EUART_STAT_LBKDE_Mask;
	}
}

/** 
  * @brief  选择LIN间隔字符长度
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  CharLen: 选择LIN间隔字符长度
  * 	This parameter can be one of the following values:
  *		@arg LIN_BRK_Char_9to13
  *		@arg LIN_BRK_Char_12to15
  * @retval None
  */
void EUART_BRK13_CharLenght_Config(EUART_TypeDef* EUARTx, uint32_t CharLen)
{
    EUART_Tx_Cmd(EUARTx, DISABLE);   // 禁止发送器，只有发送器禁止时方可设置字符长度
    
    if (LIN_BRK_Char_12to15 == CharLen)
    {
        EUARTx->STAT |= EUART_STAT_BRK13_Mask;   /*!< 间隔字符的长度为 12 到 15 位 */
    }
    else
    {
        EUARTx->STAT &= ~EUART_STAT_BRK13_Mask;  /*!< 间隔字符的长度为 9 到 13 位 */
    }
}

/** 
  * @brief  EUART空闲电平类型配置
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  ILT_Sel: 选择空闲电平类型
  * 	This parameter can be one of the following values:
  *		@arg IDLE_TYPE_AfterStop
  *		@arg IDLE_TYPE_AfterStart
  * @retval None
  */
void EUART_IDLE_Type_Config(EUART_TypeDef* EUARTx, uint32_t ILT_Sel)
{
    if (IDLE_TYPE_AfterStop == ILT_Sel)
    {
        EUARTx->CTRL |=  EUART_CTRL_ILT_Mask;  // 空闲字符计数在停止位之后开始
    }
    else
    {
        EUARTx->CTRL &= ~EUART_CTRL_ILT_Mask;  // 空闲字符计数在开始位之后开始
    }
}

/** 
  * @brief  设置空闲字符数
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  idle_char: 设定的空闲字符数
  * 	This parameter can be one of the following values:
  *		@arg EUART_IDLECFG_1bit
  *		@arg EUART_IDLECFG_2bit
  *		@arg EUART_IDLECFG_4bit
  *		@arg EUART_IDLECFG_8bit
  *		@arg EUART_IDLECFG_16bit
  *		@arg EUART_IDLECFG_32bit
  *		@arg EUART_IDLECFG_64bit
  *		@arg EUART_IDLECFG_128bit
  * @retval None
  */
void EUART_IDLE_Char_Config(EUART_TypeDef* EUARTx, uint32_t idle_char)
{
    EUARTx->CTRL &= ~EUART_CTRL_IDLECFG_Mask;
    EUARTx->CTRL |=  idle_char;
}

/** 
  * @brief  Transmits single data through the EUARTx peripheral.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  SendData: the data to transmit.
  * @retval None
  */
void EUART_Transmit_Data(EUART_TypeDef* EUARTx, uint8_t SendData)
{
    /* Wait for EUARTx Send data register is empty? */
	while (0 == (EUARTx->STAT & EUART_STAT_TDRE_Mask)) {;}   

	/* Transmit Data */
    EUARTx->DATA = SendData;
}

/** 
  * @brief  Transmits the string through the EUARTx peripheral.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @param  strData: the string to transmit.
  * @retval None
  */
void EUART_Transmit_String(EUART_TypeDef* EUARTx, uint8_t *strData)
{
    while (*strData != '\0')
    {
        EUART_Transmit_Data(EUARTx, *strData);
        strData++;
    }
}

/** 
  * @brief  Returns the recent received data by the EUARTx peripheral.
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @retval The received data.
  */
uint8_t EUART_Receive_Data(EUART_TypeDef* EUARTx)
{
    /* Wait for EUARTx Received data register is empty? */
    //while (0 == (EUARTx->STAT & EUART_STAT_RDRF_Mask)) {;}  

    /* Receive Data */
    return (uint8_t)(EUARTx->DATA);
}

/**
  * @brief  Returns the recent received RB8 by the EUARTx peripheral. 
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @retval None
  */
uint8_t EUART_Recevie_RB8(EUART_TypeDef* EUARTx)
{
    return (uint8_t)(EUARTx->CTRL >> EUART_CTRL_R8T9_Pos);
}

/**
  * @brief  Returns the recent received RB9 by the EUARTx peripheral. 
  * @param  EUARTx: Select the EUARTx peripheral. 
  *   This parameter can be one of the following values:
  *   EUART0, EUART1
  * @retval None
  */
uint8_t EUART_Recevie_RB9(EUART_TypeDef* EUARTx)
{
    return (uint8_t)((EUARTx->CTRL >> EUART_CTRL_R9T8_Pos) & 0x01UL);
}

/** 
  * @brief  Checks whether the specified EUART_STAT register bit is set or not.
  * @param  EUARTx: Select the EUARTx peripheral.
  *   This parameter can be one of the following values: EUART0, EUART1
  * @param  EUART_Flag: EUART Flag Status
  *   This parameter can be one of the following values:
  *     @arg EUART_STAT_FLAG_LBKDIF
  *     @arg EUART_STAT_FLAG_RXEDGIF
  *     @arg EUART_STAT_FLAG_RAF
  *     @arg EUART_STAT_FLAG_TDRE
  *     @arg EUART_STAT_FLAG_TC
  *     @arg EUART_STAT_FLAG_RDRF
  *     @arg EUART_STAT_FLAG_IDLE
  *     @arg EUART_STAT_FLAG_OR
  *     @arg EUART_STAT_FLAG_NF
  *     @arg EUART_STAT_FLAG_FE
  *     @arg EUART_STAT_FLAG_PF
  *     @arg EUART_STAT_FLAG_MA1F
  *     @arg EUART_STAT_FLAG_MA2F
  * @retval The new state of EUART_Flag (SET or RESET).
  */
FlagStatus EUART_STAT_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag)
{ 
    FlagStatus bitstatus = RESET;  

    if ((EUARTx->STAT & EUART_Flag) != (uint16_t)RESET)
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
  * @brief  Checks whether the specified EUART_DATA register bit is set or not.
  * @param  EUARTx: Select the EUARTx peripheral.
  *   This parameter can be one of the following values: EUART0, EUART1
  * @param  EUART_Flag: EUART Flag Status
  *   This parameter can be one of the following values:
  *     @arg EUART_DATA_FLAG_NOISY
  *     @arg EUART_DATA_FLAG_PARITYE
  *     @arg EUART_DATA_FLAG_RXEMPT
  *     @arg EUART_DATA_FLAG_IDLINE
  * @retval The new state of EUART_Flag (SET or RESET).
  */
FlagStatus EUART_DATA_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag)
{ 
    FlagStatus bitstatus = RESET;  

    if ((EUARTx->DATA & EUART_Flag) != (uint16_t)RESET)
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
  * @brief  Checks whether the specified EUART_FIFO register bit is set or not.
  * @param  EUARTx: Select the EUARTx peripheral.
  *   This parameter can be one of the following values: EUART0, EUART1
  * @param  EUART_Flag: EUART Flag Status
  *   This parameter can be one of the following values:
  *     @arg EUART_FIFO_FLAG_TXEMPT
  *     @arg EUART_FIFO_FLAG_RXEMPT
  *     @arg EUART_FIFO_FLAG_TXOF
  *     @arg EUART_FIFO_FLAG_RXUF
  * @retval The new state of EUART_Flag (SET or RESET).
  */
FlagStatus EUART_FIFO_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag)
{ 
    FlagStatus bitstatus = RESET;  

    if ((EUARTx->FIFO & EUART_Flag) != (uint16_t)RESET)
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
  * @brief EUARTx STAT状态寄存器特定标志位清零
  * @param  EUARTx: selects the EUARTx peripheral
  * 	This parameter can be one of the following values: EUART0, EUART1.
  * @param  EUART_Flag: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg EUART_STAT_FLAG_LBKDIF
  *     @arg EUART_STAT_FLAG_RXEDGIF
  *     @arg EUART_STAT_FLAG_IDLE
  *     @arg EUART_STAT_FLAG_OR
  *     @arg EUART_STAT_FLAG_NF
  *     @arg EUART_STAT_FLAG_FE
  *     @arg EUART_STAT_FLAG_PF
  *     @arg EUART_STAT_FLAG_MA1F
  *     @arg EUART_STAT_FLAG_MA2F
  * @retval None
  */
void EUART_STAT_ClearFlag(EUART_TypeDef* EUARTx, uint32_t EUART_Flag)
{
    EUARTx->STAT = EUART_Flag;  // 不能按位或，否则清除一位标志同时会清除其他标志？
}

/** 
  * @brief EUARTx FIFO寄存器特定标志位清零
  * @param  EUARTx: selects the EUARTx peripheral
  * 	This parameter can be one of the following values: EUART0, EUART1.
  * @param  EUART_Flag: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg EUART_FIFO_FLAG_TXOF
  *     @arg EUART_FIFO_FLAG_RXUF
  * @retval None
  */
void EUART_FIFO_ClearFlag(EUART_TypeDef* EUARTx, uint32_t EUART_Flag)
{
    EUARTx->FIFO |= EUART_Flag;;
}

/** 
  * @brief  Enables or disables the specified EUARTx interrupts.
  * @param  EUARTx: selects the EUARTx peripheral
  * 	This parameter can be one of the following values: EUART0, EUART1.
  * @param  EUART_IT: specifies the EUARTx interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg EUART_IT_LBKDIE
  *     @arg EUART_IT_RXEDGIE
  *     @arg EUART_IT_ORIE
  *     @arg EUART_IT_NEIE
  *     @arg EUART_IT_FEIE
  *     @arg EUART_IT_PEIE
  *     @arg EUART_IT_TIE
  *     @arg EUART_IT_TCIE
  *     @arg EUART_IT_RIE
  *     @arg EUART_IT_ILIE
  *     @arg EUART_IT_MA1IE
  *     @arg EUART_IT_MA2IE
  *     @arg EUART_IT_TXOFE
  *     @arg EUART_IT_RXUFE
  * @param  NewState: new state of the ETIMERx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EUART_ITConfig(EUART_TypeDef* EUARTx, uint32_t EUART_IT, FunctionalState NewState)
{ 
    uint8_t  temp = 0;
    uint32_t baud_lbkdie = 0;
    uint32_t baud_rxedgie = 0;
    uint32_t fifo_txofe = 0;
    uint32_t fifo_rxufe = 0;

    /* 分析EUART_IT_LBKDIE和EUART_IT_RXEDGIE中断使能情况 */
    temp = (uint8_t)EUART_IT;
    switch (temp)
    {
        case EUART_IT_LBKDIE: 
            baud_lbkdie = 0x01UL << EUART_BAUD_LBKDIE_Pos;
            break;
            
        case EUART_IT_RXEDGIE: 
            baud_rxedgie = 0x01UL << EUART_BAUD_RXEDGIE_Pos;
            break;
            
        case EUART_IT_LBKDIE | EUART_IT_RXEDGIE:
            baud_lbkdie = 0x01UL << EUART_BAUD_LBKDIE_Pos;
            baud_rxedgie = 0x01UL << EUART_BAUD_RXEDGIE_Pos;
            break;

        default : break;
    }

    EUART_IT &= 0xFFFFFFF0UL;  // EUART_IT.bit3~bit0 must be cleared
    
    /* 分析EUART_IT_TXOFE和EUART_IT_RXUFE中断使能情况 */
    if (!((EUART_IT == EUART_IT_TXOFE) || \
         (EUART_IT == EUART_IT_RXUFE) || \
         (EUART_IT == (EUART_IT_TXOFE | EUART_IT_RXUFE))))
    {
        fifo_txofe = (uint32_t)(EUART_IT & EUART_FIFO_TXOFE_Mask);
        fifo_rxufe = (uint32_t)(EUART_IT & EUART_FIFO_RXUFE_Mask);
    }
    else
    {
        fifo_txofe = EUART_IT;
        fifo_rxufe = EUART_IT;
    }

    /* Enable or disable Interrupt sources */
    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        EUARTx->CTRL |= EUART_IT;
        EUARTx->BAUD |= baud_lbkdie;
        EUARTx->BAUD |= baud_rxedgie;
        EUARTx->FIFO |= fifo_txofe;
        EUARTx->FIFO |= fifo_rxufe;
        
    }
    else
    {
        /* Disable the Interrupt sources */
        EUARTx->CTRL &= (uint32_t)(~EUART_IT);
        EUARTx->BAUD &= (uint32_t)(~baud_lbkdie);
        EUARTx->BAUD &= (uint32_t)(~baud_rxedgie);
        EUARTx->FIFO &= (uint32_t)(~fifo_txofe);
        EUARTx->FIFO &= (uint32_t)(~fifo_rxufe);
    }
}

