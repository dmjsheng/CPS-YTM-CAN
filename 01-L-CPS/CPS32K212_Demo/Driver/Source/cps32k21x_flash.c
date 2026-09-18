/*Includes -------------------------------------------------------------------*/
#include "cps32k21x_flash.h"


/** 
  * @brief  Erase the specified sector of flash memory
  * @param  FLASHx: Selects the FLASHx peripheral
  *   This parameter can be one of the following values: 
  *       FLASH
  * @param  sectorAddr: the sector of flash memory
  * @retval The result of the operation
  *   This parameter can be one of the following values: 
  *     @arg RESET (Success)
  *     @arg SET   (Fail)
  */
FlagStatus FLASH_Sector_Erase(FLASH_TypeDef* FLASHx, uint32_t sectorAddr)
{ 
    FlagStatus status = RESET;   
    
    while ((FLASHx->CR & FLASH_CR_LOCK) == FLASH_CR_LOCK)  // 判断FLASH_CR.LOCK是否被硬件清0
    {
        /* 执行FPEC解锁序列 */
        FLASHx->KEYR = FLASH_KEY1;    // 写入解锁序列，KEY1 = 0x45670123
        FLASHx->KEYR = FLASH_KEY2;    // 写入解锁序列，KEY2 = 0xCDEF89AB
    }
    
    while (FLASHx->SR & FLASH_SR_BSY) {;}  // wait for flash operation done, busy=0
        
    FLASHx->CR |= FLASH_CR_PER;   // 开始Sector擦除,即FLASH_CR.PER=1
    FLASHx->AR  = sectorAddr;     // 选择要擦除的扇区地址
    FLASHx->CR |= FLASH_CR_STRT;  // 开始操作
    while (FLASHx->SR & FLASH_SR_BSY) {;}  // wait for flash operation done, busy=0
        
    if ((FLASHx->SR & FLASH_SR_EOP) == FLASH_SR_EOP)   // 判断EOP标志是否为1
    {
        FLASHx->SR |= FLASH_SR_EOP;   // Write 1 to clear FLASG_SR.EOP
    }
    else   // EOP标志不为1时，表示扇区擦除失败
    {
        status = SET;  // 擦除失败标志置位
    }
    
    FLASHx->CR &= ~FLASH_CR_PER;  // FLASH_CR.PER=0
    
    return status;
}

/** 
  * @brief  向FLASH指定地址单元写入32位宽的数据
  * @param  FLASHx: Selects the FLASHx peripheral
  *   This parameter can be one of the following values: 
  *       FLASH
  * @param  flashAddr: FLASH地址，必须按Word对齐
  * @param  writeData: 待写入的32位数据（只支持按字编程）
  * @retval The result of the operation
  *   This parameter can be one of the following values: 
  *     @arg RESET (Success)
  *     @arg SET   (Fail)
  */
FlagStatus FLASH_Word_Program(FLASH_TypeDef* FLASHx, uint32_t flashAddr, uint32_t writeData)
{
    FlagStatus status = RESET;
    
    /* 判断word操作的目标地址是否按word对齐（地址最低两位为0）*/
    if ((flashAddr & ((uint32_t)0x03)) != 0)    
    {
        status = SET;
        return status;   // 编程失败
    }
    
    if (writeData != 0xFFFFFFFFUL)   // 写入数据为0xFFFFFFFF时不写入，无意义
    {
        while ((FLASHx->CR & FLASH_CR_LOCK) == FLASH_CR_LOCK)    // 判断FLASH_CR.LOCK是否被硬件清0
        {
            /* 执行FPEC解锁序列 */
            FLASHx->KEYR = FLASH_KEY1;   // 写入解锁序列，KEY1 = 0x45670123
            FLASHx->KEYR = FLASH_KEY2;   // 写入解锁序列，KEY2 = 0xCDEF89AB
        }
        
        while (FLASHx->SR & FLASH_SR_BSY) {;}  // wait for flash operation done, busy=0
        
        FLASHx->CR |= FLASH_CR_PG;    // FLASH_CR.PG=1, 编程使能
        *(uint32_t *)flashAddr = writeData;	  // 写入32位宽数据
        while (FLASHx->SR & FLASH_SR_BSY) {;}	// wait for flash operation done, busy=0
        if ((FLASHx->SR & FLASH_SR_EOP) == FLASH_SR_EOP)   // 判断EOP标志是否为1
        {
            FLASHx->SR |= FLASH_SR_EOP;   // Write 1 to clear FLASG_SR.EOP
        }
        else  // EOP标志不为1时，表示编程失败
        {
            status = SET;   // 编程失败
        } 
        
        FLASHx->CR &= ~FLASH_CR_PG;   // FLASH_CR.PG=0, 编程禁止  
    }
    
    return status;
}

/** 
  * @brief  FLASH选项字节空间擦除
  * @param  FLASHx: Selects the FLASHx peripheral
  *   This parameter can be one of the following values: 
  *       FLASH
  * @param  sectorAddr: FLASH选项字节扇区地址
  * @retval The result of the operation
  *   This parameter can be one of the following values: 
  *     @arg RESET (Success)
  *     @arg SET   (Fail)
  */
FlagStatus FLASH_OPT_Erase(FLASH_TypeDef* FLASHx, uint32_t sectorAddr)
{
    FlagStatus status = RESET;
    
    /*--------------------- 选项字节区地址范围判断 ---------------------------*/
    if ((sectorAddr < OPTION_BYTE_START_ADDR) || (sectorAddr > OPTION_BYTE_END_ADDR))
    {
        status = SET;   // 选项字节区擦除失败
        return status;  
    }
    
    while ((FLASHx->CR & FLASH_CR_LOCK) == FLASH_CR_LOCK)    // 判断FLASH_CR.LOCK是否被硬件清0
    {
        /* 执行FPEC解锁序列 */
        FLASHx->KEYR = FLASH_KEY1;    // 写入解锁序列，KEY1 = 0x45670123
        FLASHx->KEYR = FLASH_KEY2;    // 写入解锁序列，KEY2 = 0xCDEF89AB
    }
        
    while (FLASHx->SR & FLASH_SR_BSY);	// wait for flash operation done, busy=0
        
    while ((FLASHx->CR & FLASH_CR_OPTWRE) != FLASH_CR_OPTWRE)   // wait for FLASH_CR.OPTWRE=1,等待充许擦写选项字节标志
    {
        /* 执行键序列，使FLASH_CR.OPTWRE=1 */
        FLASHx->OPTKEYR = FLASH_KEY1;
        FLASHx->OPTKEYR = FLASH_KEY2;
    }
        
    FLASHx->CR |= FLASH_CR_OPTER;     // FLASH_CR.OPTER=1, 擦除选项字节
    FLASHx->AR = sectorAddr;          // 设置要擦除的选项字节扇区起始地址
    FLASHx->CR |= FLASH_CR_STRT;      // 开始操作
    while (FLASHx->SR & FLASH_SR_BSY);	// wait for flash operation done, busy=0
    if ((FLASHx->SR & FLASH_SR_EOP) == FLASH_SR_EOP)   // 判断EOP标志是否为1
    {
        FLASHx->SR |= FLASH_SR_EOP;       // Write 1 to clear FLASG_SR.EOP
    }
    else  // EOP标志不为1时，表示选项字节区擦除失败
    {
        status = SET;   // 擦除失败
    }
    
    FLASHx->CR &= ~FLASH_CR_OPTER;    // FLASH_CR.OPTER=0
    FLASHx->CR &= ~FLASH_CR_OPTWRE;   // FLASH_CR.OPTWRE=0, 禁止擦写选项字节
    
    return status;
 }

/** 
  * @brief  选项字节地址单元写入一个字的数据
  * @param  FLASHx: Selects the FLASHx peripheral
  *   This parameter can be one of the following values: 
  *       FLASH
  * @param  flashAddr: 选项字节扇区地址，地址按字对齐
  * @param  writeData: 待写入的32位数据（只支持按字编程）
  * @retval The result of the operation
  *   This parameter can be one of the following values: 
  *     @arg RESET (Success)
  *     @arg SET   (Fail)
  */
FlagStatus FLASH_OPT_Program(FLASH_TypeDef* FLASHx,uint32_t flashAddr, uint32_t writeData)
{
    FlagStatus status = RESET;
    
    /*--------------------- 选项字节区地址范围判断 ---------------------------*/
    if ((flashAddr < OPTION_BYTE_START_ADDR) || (flashAddr > OPTION_BYTE_END_ADDR))
    {
        status = SET;   // 选项字节区编程失败
        return status;  
    }
    
    /* 判断word操作的目标地址是否按word对齐（地址最低两位为0）*/
    if ((flashAddr & 0x03UL) != 0)   
    {
        status = SET;   // 选项字节区编程失败
        return status;  
    }
    
    if (writeData != 0xFFFFFFFFUL)  // 写入数据不为0xFFFFFFFF时才写入，写入0xFFFFFFFF无意义
    {
        while ((FLASHx->CR & FLASH_CR_LOCK) == FLASH_CR_LOCK)    // 判断FLASH_CR.LOCK是否被硬件清0
        {
            /* 执行FPEC解锁序列 */
            FLASHx->KEYR = FLASH_KEY1;    // 写入解锁序列，KEY1 = 0x45670123
            FLASHx->KEYR = FLASH_KEY2;    // 写入解锁序列，KEY2 = 0xCDEF89AB
        }
            
        while (FLASHx->SR & FLASH_SR_BSY);	// wait for flash operation done, busy=0
            
        while ((FLASHx->CR & FLASH_CR_OPTWRE) != FLASH_CR_OPTWRE)   // wait for FLASH_CR.OPTWRE=1,等待充许擦写选项字节标志
        {
            /* 执行键序列，使FLASH_CR.OPTWRE=1 */
            FLASHx->OPTKEYR = FLASH_KEY1;
            FLASHx->OPTKEYR = FLASH_KEY2;
        }
            
        FLASHx->CR |= FLASH_CR_OPTPG;      // FLASH_CR.OPTPG=1, 编程选项字节
        *(uint32_t *)flashAddr = writeData;	  // 写入32位宽数据
        while (FLASHx->SR & FLASH_SR_BSY);	  // wait for flash operation done, busy=0
        if ((FLASHx->SR & FLASH_SR_EOP) == FLASH_SR_EOP)   // 判断EOP标志是否为1
        {
            FLASHx->SR |= FLASH_SR_EOP;       // Write 1 to clear FLASG_SR.EOP
        }
        else  // EOP标志不为1时，表示选项字节区编程失败
        { 
            status = SET;   // 选项字节区编程失败
        }
        
        FLASHx->CR &= ~FLASH_CR_OPTPG;     // FLASH_CR.OPTPG=0
        FLASHx->CR &= ~FLASH_CR_OPTWRE;    // FLASH_CR.OPTWRE=0, 禁止擦写选项字节
    }
    
    return status;
}

/** 
  * @brief  从FLASH指定地址读取一个字节（8位）数据
  * @param  flashAddr: Flash地址空间
  * @retval 8位宽数据
  */
uint8_t FLASH_Read_Byte_Data(uint32_t flashAddr)
{
    return (*((volatile uint8_t *)flashAddr));
}

/** 
  * @brief  从FLASH指定地址读取一个半字（16位）数据
  * @param  flashAddr: Flash地址空间
  * @retval 16位宽数据
  */
uint16_t FLASH_Read_HalfWord_Data(uint32_t flashAddr)
{
    return (*((volatile uint16_t *)flashAddr));
}

/** 
  * @brief  从FLASH指定地址读取一个字（32位）数据
  * @param  flashAddr: Flash地址空间
  * @retval 32位宽数据
  */
uint32_t FLASH_Read_Word_Data(uint32_t flashAddr)
{
    return (*((volatile uint32_t *)flashAddr));
}

