/* Includes ------------------------------------------------------------------*/
#include  "cps32k21x_crc.h"


/** 
  * @brief  Deinitializes the CRC peripheral registers to their default reset values.
  * @param  None 
  * @retval None
  */
void CRC_DeInit(void)
{
    /* Enable CRC reset state */
    RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_CRC_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release CRC from reset state */
    RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_CRC_RST, DISABLE);   
}

/**
  * @brief  Fills each CRC_InitTypeDef member with its default value.
  * @param  CRC_InitStruct : pointer to a CRC_InitTypeDef structure which will be initialized.
  * @retval None
  */
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct)
{
    CRC_InitStruct->MSBLSB_Sel    = MSBLSB_SELECT_LSB;           /*<! LSB优先生成CRC */
    CRC_InitStruct->CRC_Poly_Sel  = CRC_POLY_SEL_None;           /*<! CRC多项式选择：未执行任何计算 */
    CRC_InitStruct->Monitor_En    = CRC_MONITOR_DISABLE;         /*<! CRC监测禁止 */
    CRC_InitStruct->Monitor_RW    = CRC_MONITOR_READ;            /*<! CRC监测方式读操作 */
    CRC_InitStruct->MonitorSource = CRC_MONITOR_SOURCE_PERIPH;   /*<! CRC监测源选择成外设 */
}

/**
  * @brief  Initializes the CRCx peripheral according to the specified parameters
  *         in the CRC_InitTypeDef.
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  CRC_InitStruct: pointer to a CRC_InitTypeDef structure that contains 
  *         the configuration information for the specified CRCx peripheral.
  * @retval None
  */
void CRC_Init(CRC_TypeDef* CRCx, CRC_InitTypeDef* CRC_InitStruct)
{
    uint32_t tmpcr = 0;

    tmpcr = CRCx->CR;   // read CRC_CR register

    /* config CRC_CR.LMS */
    (MSBLSB_SELECT_LSB == CRC_InitStruct->MSBLSB_Sel) ? (tmpcr &= ~MSBLSB_SELECT_MSB) : (tmpcr |= MSBLSB_SELECT_MSB);

    /* config CRC_CR.GPS */
    tmpcr &= ~CRC_POLY_SEL_Mask;
    tmpcr |=  CRC_InitStruct->CRC_Poly_Sel;

    /* config CRC_CR.CRCMEN */
    (CRC_MONITOR_DISABLE == CRC_InitStruct->Monitor_En) ? (tmpcr &= ~CRC_MONITOR_ENABLE) : (tmpcr |= CRC_MONITOR_ENABLE);

    /* config CRC_CR.CRCMWR */
    (CRC_MONITOR_READ == CRC_InitStruct->Monitor_RW) ? (tmpcr &= ~CRC_MONITOR_WRITE) : (tmpcr |= CRC_MONITOR_WRITE);

    /* config CRC_CR.MONSEL */
    (CRC_MONITOR_SOURCE_PERIPH == CRC_InitStruct->MonitorSource) ? (tmpcr &= ~CRC_MONITOR_SOURCE_ROM) : (tmpcr |= CRC_MONITOR_SOURCE_ROM);

     CRCx->CR = tmpcr;   // write CRC_CR register 
}

/** 
  * @brief  Clear the CRC DATAOUT register.
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @retval None
  */
void CRC_DATAOUT_Clear(CRC_TypeDef* CRCx)
{
	/* Clear the CRC DATAOUT register */
	CRCx->CR |= BIT31;
}

/** 
  * @brief  基于多项式（CRC-8： X8+X2+X+1）计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 8位宽的CRC计算结果
  */
uint8_t CRC_Poly_CRC8_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen)
{
	uint16_t i = 0;
    uint8_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }
    
    crc_result = (uint8_t)(CRCx->DATAOUT >> 24);   // 读取计算的CRC值
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-8： X8+X2+X+1）校验输入数据及CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer: 指向要计算CRC值的数据输入源
  * @param  DataLen: 数据长度, 以字节为单位
  * @param  crc_for_check: 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC8_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint8_t crc_for_check)
{
    uint16_t i = 0;
    ErrorStatus check_status = SUCCESS;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }
    
    CRCx->DATAIN = (uint32_t)(((uint32_t)crc_for_check) << 24);  // 待校验的CRC值写入
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status);
}

/** 
  * @brief  基于多项式（CRC-16： X16+X15+X2+1）计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 16位宽的CRC计算结果
  */
uint16_t CRC_Poly_CRC16_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen)
{
    uint16_t i = 0;
    uint16_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT

    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }
    
    crc_result = (uint16_t)(CRCx->DATAOUT >> 16);  // 读取计算的CRC值
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-16： X16+X15+X2+1）校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源
  * @param  DataLen : 数据长度, 以字节为单位
  * @param  crc_for_check : 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC16_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint16_t crc_for_check)
{
    ErrorStatus check_status = SUCCESS;
    uint16_t i = 0;
    uint32_t tmpcr = 0;

    tmpcr = CRCx->CR;  // Read CRC_CR register
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }

    if (tmpcr & ((uint32_t)(0x01UL << 30)))  // MSB优先生成CRC
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(((crc_for_check >> 8) & 0x00FF))) << 24);
        CRCx->DATAIN = (uint32_t)(((uint32_t)(crc_for_check & 0x00FF)) << 24);
    }
    else  // LSB优先生成CRC
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(crc_for_check & 0x00FF)) << 24);
        CRCx->DATAIN = (uint32_t)(((uint32_t)(((crc_for_check >> 8) & 0x00FF))) << 24);
    }
    
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status); 
}

/** 
  * @brief  基于多项式（CRC-CCITT： X16+X12+X5+1）计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 16位宽的CRC计算结果
  */
uint16_t CRC_Poly_CRC16_CCIT_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen)
{
    uint16_t i = 0;
    uint16_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }
    
    crc_result = (uint16_t)(CRCx->DATAOUT >> 16);   // 读取计算的CRC值
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-CCITT： X16+X12+X5+1）校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源
  * @param  DataLen : 数据长度, 以字节为单位
  * @param  crc_for_check : 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误 
  */
ErrorStatus CRC_Poly_CRC16_CCIT_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint16_t crc_for_check)
{
    uint8_t sel_msb_lsb = 0;
    ErrorStatus check_status = SUCCESS;
    uint16_t i = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT

    ((CRCx->CR & BIT30) != 0) ? (sel_msb_lsb = 0x01u) : (sel_msb_lsb = 0);
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(*(pBuffer + i))) << 24);
    }
    
    if (0x01u == sel_msb_lsb)  // MSB优先生成CRC
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(((crc_for_check >> 8) & 0x00FF))) << 24);
        CRCx->DATAIN = (uint32_t)(((uint32_t)(crc_for_check & 0x00FF)) << 24);
    }
    else  // LSB优先生成CRC
    {
        CRCx->DATAIN = (uint32_t)(((uint32_t)(crc_for_check & 0x00FF)) << 24);
        CRCx->DATAIN = (uint32_t)(((uint32_t)(((crc_for_check >> 8) & 0x00FF))) << 24);
    }

    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status); 
}

/** 
  * @brief  基于多项式（CRC-32： X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1）
            计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为8bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 32位宽的CRC计算结果
  */
uint32_t CRC_Poly_CRC32_Calculate_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen)
{
    uint8_t mod = 0;
    uint16_t tmp32_count = 0;
    uint16_t i = 0;
    uint32_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    tmp32_count = (uint16_t)(DataLen >> 2);
    mod = DataLen % 4;
    
    for (i=0; i<tmp32_count; i++)
    {
        CRCx->DATAIN = (uint32_t)(((*(pBuffer + (i << 2) + 3)) << 24) | ((*(pBuffer + (i << 2) + 2)) << 16) | ((*(pBuffer + (i << 2) + 1)) << 8) | (*(pBuffer + (i << 2)))); 
    }

    switch (mod)
    {
        case 1: CRCx->DATAIN = (uint32_t)(*(pBuffer + (tmp32_count << 2) + 0));
                break;
        case 2: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        case 3: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 2)) << 16) | ((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        default : break;
    }
    
    crc_result = CRCx->DATAOUT;  // 得到计算的CRC结果
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-32： X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1）
            校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为8bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @param  crc_for_check : 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC32_Check_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check)
{
    uint8_t mod = 0;
    ErrorStatus check_status = SUCCESS;
    uint16_t tmp32_count = 0;
    uint16_t i = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    tmp32_count = (uint16_t)(DataLen >> 2);
    mod = DataLen % 4;
    
    for (i=0; i<tmp32_count; i++)
    {
        CRCx->DATAIN = (uint32_t)(((*(pBuffer + (i << 2) + 3)) << 24) | ((*(pBuffer + (i << 2) + 2)) << 16) | ((*(pBuffer + (i << 2) + 1)) << 8) | (*(pBuffer + (i << 2)))); 
    }

    switch (mod)
    {
        case 1: CRCx->DATAIN = (uint32_t)(*(pBuffer + (tmp32_count << 2) + 0));
                break;
        case 2: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        case 3: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 2)) << 16) | ((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        default : break;
    }
    
    CRCx->DATAIN = crc_for_check;  // 写入待校验的32位CRC值
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status);
}

/** 
  * @brief  基于多项式（CRC-32：X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1）
            计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer ：指向要计算CRC值的数据输入源, 输入数据位宽为32bit
  * @param  DataLen ：数据长度, 以字节为单位
  * @retval 32位CRC计算结果 
  */
uint32_t CRC_Poly_CRC32_Calculate_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen)
{
    uint16_t i = 0;
    uint32_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = *(pBuffer + i);
    }
    
    crc_result = CRCx->DATAOUT;  // 得到计算的CRC值
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-32：X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1）
            校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer ：指向要计算CRC值的数据输入源, 输入数据位宽为32bit
  * @param  DataLen ：数据长度, 以字节为单位
  * @param  crc_for_check ：待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC32_Check_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check)
{
    ErrorStatus check_status = SUCCESS;
    uint16_t i = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = *(pBuffer + i);
    }
    
    CRCx->DATAIN = crc_for_check;   // 写入待校验的CRC值
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status);
}

/** 
  * @brief  基于多项式（CRC-32C：X32+X28+X27+X26+X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1）
            计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为8bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 32位宽的CRC计算结果
  */
uint32_t CRC_Poly_CRC32C_Calculate_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen)
{
    uint8_t mod = 0;
    uint16_t i = 0;
    uint16_t tmp32_count = 0;
    uint32_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT

    tmp32_count = (uint16_t)(DataLen >> 2);
    mod = DataLen % 4;
    
    for (i=0; i<tmp32_count; i++)
    {
        CRCx->DATAIN = (uint32_t)(((*(pBuffer + (i << 2) + 3)) << 24) | ((*(pBuffer + (i << 2) + 2)) << 16) | ((*(pBuffer + (i << 2) + 1)) << 8) | (*(pBuffer + (i << 2)))); 
    }

    switch (mod)
    {
        case 1: CRCx->DATAIN = (uint32_t)(*(pBuffer + (tmp32_count << 2) + 0));
                break;
        case 2: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        case 3: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 2)) << 16) | ((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        default : break;
    }
    
    crc_result = CRCx->DATAOUT;   // 得到计算的32位CRC值
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-32C：X32+X28+X27+X26+X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1）
            校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为8bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @param  crc_for_check : 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC32C_Check_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check)
{
    uint8_t mod = 0;
    ErrorStatus check_status = SUCCESS;
    uint16_t tmp32_count = 0;
    uint16_t i = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    tmp32_count = (uint16_t)(DataLen >> 2);
    mod = DataLen % 4;
    
    for (i=0; i<tmp32_count; i++)
    {
        CRCx->DATAIN = (uint32_t)(((*(pBuffer + (i << 2) + 3)) << 24) | ((*(pBuffer + (i << 2) + 2)) << 16) | ((*(pBuffer + (i << 2) + 1)) << 8) | (*(pBuffer + (i << 2)))); 
    }

    switch (mod)
    {
        case 1: CRCx->DATAIN = (uint32_t)(*(pBuffer + (tmp32_count << 2) + 0));
                break;
        case 2: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        case 3: CRCx->DATAIN = (uint32_t)(((*(pBuffer + (tmp32_count << 2) + 2)) << 16) | ((*(pBuffer + (tmp32_count << 2) + 1)) << 8) | (*(pBuffer + (tmp32_count << 2) + 0))); 
                break;
        default : break;
    }
    
    CRCx->DATAIN = crc_for_check;  // 待校验CRC值写入
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status); 
}

/** 
  * @brief  基于多项式（CRC-32C：X32+X28+X27+X26+X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1）
            计算输入数据的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为32bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @retval 32位宽的CRC计算结果
  */
uint32_t CRC_Poly_CRC32C_Calculate_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen)
{
    uint16_t i = 0;
    uint32_t crc_result = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = *(pBuffer + i);
    }
    
    crc_result = CRCx->DATAOUT;   // 得到CRC计算结果
    
    return (crc_result);
}

/** 
  * @brief  基于多项式（CRC-32C：X32+X28+X27+X26+X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1）
            校验数据及对应的CRC值
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  pBuffer : 指向要计算CRC值的数据输入源, 输入数据位宽为32bit
  * @param  DataLen : 数据长度, 以字节为单位
  * @param  crc_for_check : 待校验的CRC值
  * @retval CRC校验结果，SUCESS表示校验正确, ERROR表示校验错误
  */
ErrorStatus CRC_Poly_CRC32C_Check_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check)
{
    ErrorStatus check_status = SUCCESS;
    uint16_t i = 0;
    
    CRC_DATAOUT_Clear(CRCx);  // 清除DATAOUT
    
    for (i=0; i<DataLen; i++)
    {
        CRCx->DATAIN = *(pBuffer + i);
    }
    
    CRCx->DATAIN = crc_for_check;   // 待校验CRC写入
    (0 == CRCx->DATAOUT) ? (check_status = SUCCESS) : (check_status = ERROR);
    
    return (check_status); 
}

/** 
  * @brief  配置CRC多项式
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  Select_Poly: specifies the CRC Polynomial.
  * 	This parameter can be one of the following value:
  *     	@arg CRC_POLY_SEL_None
  *     	@arg CRC_POLY_SEL_CRC8
  *     	@arg CRC_POLY_SEL_CRC16
  *     	@arg CRC_POLY_SEL_CRC_CCITT
  *     	@arg CRC_POLY_SEL_CRC32
  *     	@arg CRC_POLY_SEL_CRC32C
  * @retval None
  */
void CRC_Poly_Switch_Config(CRC_TypeDef* CRCx, uint32_t Select_Poly)
{
    uint32_t tmpcr = 0;

    tmpcr  =  CRCx->CR;    // Read CRC_CR register
    tmpcr &= ~CRC_POLY_SEL_Mask;
    tmpcr |=  Select_Poly;  
    CRCx->CR = tmpcr;
} 

/**
  * @brief  Enables or disables the CRC monitor function.
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  NewState: new state of the CRC monitor function.
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_Monitor_Cmd(CRC_TypeDef* CRCx, FunctionalState NewState)
{
    if (NewState != DISABLE)
	{
		/* Enable the CRC monitor function */
		CRCx->CR |=  CRC_MONITOR_ENABLE;
	}
	else
	{
		/* Disable the CRC monitor function*/
		CRCx->CR &= ~CRC_MONITOR_ENABLE;
	}
}

/** 
  * @brief  CRC监测读写操作方式配置
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  RWSel: 指定CRC监测读取/写入操作方式
  * 	This parameter can be one of the following value:
  *     	@arg CRC_MONITOR_READ
  *     	@arg CRC_MONITOR_WRITE
  * @retval None
  */
void CRC_Monitor_RW_Config(CRC_TypeDef* CRCx, uint32_t RWSel)
{
    if (RWSel == CRC_MONITOR_READ)
    {
        CRCx->CR &= ~CRC_MONITOR_WRITE;  // 监测选择读取操作
    }
    else
    {
        CRCx->CR |=  CRC_MONITOR_WRITE;  // 监测选择写入操作
    }
}

/** 
  * @brief  CRC监测源选择配置
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  MonitorSrc: 指定CRC监测源
  * 	This parameter can be one of the following value:
  *     	@arg CRC_MONITOR_SOURCE_PERIPH
  *     	@arg CRC_MONITOR_SOURCE_ROM
  * @retval None
  */
void CRC_Monitor_Source_Config(CRC_TypeDef* CRCx, uint32_t MonitorSrc)
{
    if (CRC_MONITOR_SOURCE_PERIPH == MonitorSrc)
    {
        CRCx->CR &= ~CRC_MONITOR_SOURCE_ROM;   // 监测源选择外设
    }
    else
    {
        CRCx->CR |=  CRC_MONITOR_SOURCE_ROM;   // 监测源选择ROM
    }
}

/** 
  * @brief  加载要监测的外设地址
  * @param  CRCx: Select the CRC peripheral 
  * 	This parameter can be one of the following values: CRC
  * @param  periphAddr: 外设地址
  * @retval None
  */
void CRC_MonitorAddress_Load(CRC_TypeDef* CRCx, uint32_t periphAddr)
{
    uint32_t address = periphAddr & 0x0000FFFFUL;
    
    address = (uint32_t)(address << 16);
    CRCx->MAR = address;
}


