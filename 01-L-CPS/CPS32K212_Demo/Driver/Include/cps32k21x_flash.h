/*Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_FLASH_H__
#define __CPS32K21X_FLASH_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


#define  CHIP_SECTOR_SIZE           (512UL)          // FLASH扇区大小定义
#define  OPTION_BYTE_START_ADDR     (0x1FFFF800UL)   // FLASH选项字节区起始地址定义
#define  OPTION_BYTE_END_ADDR       (0x1FFFF9FFUL)   // FLASH选项字节区结束地址定义
                            
#define  FLASH_KEY1            (0x45670123UL)
#define  FLASH_KEY2            (0xCDEF89ABUL)

/*--------------- Flash Control Register definitions  -------------------*/
#define  FLASH_CR_PG           (0x1UL)
#define  FLASH_CR_PER          (0x2UL)
#define  FLASH_CR_MER          (0x4UL)
#define  FLASH_CR_OPTPG        (0x10UL)
#define  FLASH_CR_OPTER        (0x20UL)
#define  FLASH_CR_STRT         (0x40UL)
#define  FLASH_CR_LOCK         (0x80UL)
#define  FLASH_CR_SYSLOCK      (0x100UL)
#define  FLASH_CR_OPTWRE       (0x200UL)

/*--------------- Flash Status Register definitions  -------------------*/
#define  FLASH_SR_BSY          (0x1UL)     // Busy标志
#define  FLASH_SR_PGERR        (0x4UL)     // 编程错误标志
#define  FLASH_SR_WRPRTERR     (0x10UL)    // 写保护错误标志
#define  FLASH_SR_EOP          (0x20UL)    // EOP,操作结束标志
         
#define  FLASH_SR_ERR          (FLASH_SR_PGERR | FLASH_SR_WRPRTERR)


/* Exported functions --------------------------------------------------------*/
FlagStatus FLASH_Sector_Erase(FLASH_TypeDef* FLASHx, uint32_t sectorAddr);
FlagStatus FLASH_Word_Program(FLASH_TypeDef* FLASHx, uint32_t flashAddr, uint32_t writeData);
FlagStatus FLASH_OPT_Erase(FLASH_TypeDef* FLASHx, uint32_t sectorAddr);
FlagStatus FLASH_OPT_Program(FLASH_TypeDef* FLASHx,uint32_t flashAddr, uint32_t writeData);
uint8_t FLASH_Read_Byte_Data(uint32_t flashAddr);
uint16_t FLASH_Read_HalfWord_Data(uint32_t flashAddr);
uint32_t FLASH_Read_Word_Data(uint32_t flashAddr);



#ifdef __cplusplus
}
#endif


#endif   /* __CPS32K21X_FLASH_H__ */

