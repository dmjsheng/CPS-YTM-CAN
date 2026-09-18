#ifndef __CPS32K21X_H__     
#define __CPS32K21X_H__


#ifdef __cplusplus
 extern "C" {
#endif 
	 
typedef unsigned int vu32;
typedef unsigned short int vu16;
typedef unsigned char vu8;
  
/**
 * @brief In the following line adjust the Internal High Speed oscillator (HIRC) Startup
   Timeout value
  */

#if !defined  (HIRC_STABLE_TIMEOUT)
#define HIRC_STABLE_TIMEOUT     ((uint16_t)0x5000)     /*!< Time out for HIRC STABLE */
#endif /* HIRC_STABLE_TIMEOUT */

/**
 * @brief In the following line adjust the External High Speed oscillator (HXT) Startup 
   Timeout value 
   */
#if !defined  (HXT_STABLE_TIMEOUT)
#define HXT_STABLE_TIMEOUT      ((uint16_t)0x5000)     /*!< Time out for HXT STABLE */
#endif /* HXT_STABLE_TIMEOUT */

/**
 * @brief In the following line adjust the Internal Low Speed oscillator (LIRC) Startup 
   Timeout value 
   */
#if !defined  (LIRC_STABLE_TIMEOUT)
#define LIRC_STABLE_TIMEOUT     ((uint16_t)0x5000)   /*!< Time out for LIRC STABLE */*/
#endif /* LIRC_STABLE_TIMEOUT */


#if !defined  (Fpclk) 
#define Fpclk  ((uint32_t)48000000)    /*!< Value of the Fpclk in Hz */
#endif /* Fpclk */
 

#define __CPS32K21X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version     */
#define __CPS32K21X_STDPERIPH_VERSION_SUB1   (0x05) /*!< [23:16] sub1 version     */
#define __CPS32K21X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __CPS32K21X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __CPS32K21X_STDPERIPH_VERSION        ((__CPS32K21X_STDPERIPH_VERSION_MAIN << 24)\
                                              | (__CPS32K21X_STDPERIPH_VERSION_SUB1 << 16)\
                                              | (__CPS32K21X_STDPERIPH_VERSION_SUB2 << 8)\
                                              | (__CPS32K21X_STDPERIPH_VERSION_RC))
																						 
/**
 * @brief CPS32K21x Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
#define __CM0_REV                (0)   /*!< Core Revision r0p0                             */
#define __MPU_PRESENT            (0)   /*!< CPS32K21x do not provide MPU                  */
#define __NVIC_PRIO_BITS         (2)   /*!< CPS32K21x uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig   (0)   /*!< Set to 1 if different SysTick Config is used   */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
/******************  Cortex-M0 Processor Exceptions Numbers *****************/
    NonMaskableInt_IRQn = -7,     /*!< Non Maskable Interrupt               */
    HardFault_IRQn      = -6,     /*!< Cortex-M0 Hard Fault Interrupt       */
    SVC_IRQn            = -4,     /*!< Cortex-M0 SV Call Interrupt          */
    PendSV_IRQn         = -2,     /*!< Cortex-M0 Pend SV Interrupt          */
    SysTick_IRQn        = -1,     /*!< Cortex-M0 System Tick Interrupt      */

    GPIOA_IRQn          = 0,      /*!< GPIOA Interrupt                      */
    GPIOB_IRQn          = 1,      /*!< GPIOB Interrupt                      */
    GPIOC_IRQn          = 2,      /*!< GPIOC Interrupt                      */
    GPIOD_IRQn          = 3,      /*!< GPIOD Interrupt                      */
    FLASH_IRQn          = 4,	  /*!< FLASH Interrupt                      */
    RESERVED0_IRQn      = 5,      /*!< RESERVED0 Interrupt                  */
    EUART0_RX_IRQn      = 6,      /*!< EUART0 RX Interrupt                  */
    EUART1_RX_IRQn      = 7,      /*!< EUART1 RX Interrupt                  */
    ASPI_TX_IRQn        = 8,      /*!< ASPI TX Interrupt                    */
    CAN0_IRQn           = 9,      /*!< CAN0 Interrupt                       */
    ASPI_RX_IRQn        = 10,     /*!< ASPI RX Interrupt                    */
    SPI1_IRQn           = 11,     /*!< SPI1 Interrupt                       */
    I2C0_IRQn           = 12,     /*!< I2C0 Interrupt                       */
    RESERVED1_IRQn      = 13,     /*!< RESERVED1 Interrupt                  */
    TIM10_IRQn          = 14,     /*!< TIM10 Interrupt                      */
    TIM11_IRQn          = 15,     /*!< TIM11 Interrupt                      */
    LPTIM_IRQn          = 16,     /*!< LPTIM Interrupt                      */
    GPIOE_IRQn          = 17,     /*!< GPIOE Interrupt                      */
    ETIMER_IRQn         = 18,     /*!< ETIMER Interrupt                     */
    TIM2_IRQn           = 19,	  /*!< TIM2 Interrupt                       */
    EUART0_TX_IRQn      = 20,	  /*!< EUART0 TX Interrupt                  */
    EUART1_TX_IRQn      = 21,	  /*!< EUART1 TX Interrupt                  */
    WWDG_IRQn           = 22,     /*!< WWDG Interrupt                       */
    IWDG_IRQn           = 23,     /*!< IWDG Interrupt                       */
    ADC_IRQn            = 24,     /*!< ADC Interrupt                        */
    LVD_IRQn            = 25,     /*!< LVD Interrupt                        */
    VC_IRQn             = 26,     /*!< VC Interrupt                         */
    SRAM_IRQn           = 27,     /*!< SRAM Interrupt                       */
    AWK_IRQn            = 28,     /*!< AWK Interrupt                        */
    RESERVED2_IRQn      = 29,     /*!< RESERVED2 Interrupt                  */
    RESERVED3_IRQn      = 30,     /*!< RESERVED3 Interrupt                  */
    CLKTRIM_IRQn        = 31      /*!< CLKTRIM Interrupt                    */    
}IRQn_Type;


/**
* @brief setting bits macro.
*/
#ifndef SET_BIT32
  #define SET_BIT32(reg, mask)        ((reg) |= (uint32_t)(mask))
#endif

/**
* @brief clearing bits macro.
*/
#ifndef CLEAR_BIT32
  #define CLEAR_BIT32(reg, mask)      ((reg) &= (~((uint32_t)(mask))))
#endif

/**
* @brief read bits macro.
*/
#ifndef READ_BIT32
  #define READ_BIT32(reg, mask)       ((reg) & ((uint32_t)(mask)))
#endif

/**
* @brief write register macro.
*/
#ifndef WRITE_REG32
  #define WRITE_REG32(reg, value)     ((reg) = (uint32_t)(value))
#endif

/**
* @brief clear bits and set with new value
*/
#ifndef MODIFY_REG32
  #define MODIFY_REG32(reg, mask, pos, value)  (WRITE_REG32((reg), (((reg) & (~((uint32_t)mask))) | (((uint32_t)value) << pos))))
#endif

/**
* @brief read 32 bits memory macro.
*/
#ifndef READ_MEM32
  #define READ_MEM32(address)      (*(volatile uint32_t*)(address))
#endif

/**
* @brief write 32 bits memory macro.
*/
#ifndef WRITE_MEM32
  #define WRITE_MEM32(address, value)      ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/**
* @brief clear bits and set with new value for memory.
*/
#ifndef MODIFY_MEM32
  #define MODIFY_MEM32(address, mask, pos, value)   (WRITE_MEM32((address), ((READ_MEM32(address) & (~((uint32_t)mask))) | (((uint32_t)value) << pos))))
#endif


/**
  * @}
  */
#include <stdint.h>
#include "core_cm0plus.h"
#include "system_cps32k21x.h"


/** @addtogroup Exported_types
  * @{
  */  
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Copyright (C) 2022 ChipSine Semiconductor Co., Ltd. All rights reserved   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
typedef enum {FALSE = 0, TRUE = !FALSE} BOOL_Type;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define IS_FUNCTION_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef void (*DeviceCallback_Type)(void *device, uint32_t wpara, uint32_t lpara);

#define SRAM_Typedef    SRAM_TypeDef
#define CAN_Typedef     CAN_TypeDef

/** @addtogroup Peripheral_registers_structures
  * @{
  */  

/**
  * @} RCC_TypeDef / 系统复位与时钟    
  */
typedef struct
{
	__IO uint32_t HCLKDIV;        /*!< 0x00 - AHB时钟分频寄存器  */
	__IO uint32_t PCLKDIV;        /*!< 0x04 - APB时钟分频寄存器  */
	__IO uint32_t HCLKEN;         /*!< 0x08 - AHB周边模块时钟使能寄存器 */
	__IO uint32_t PCLKEN;         /*!< 0x0C - APB周边模块时钟使能寄存器 */
	__IO uint32_t MCOCR;          /*!< 0x10 - 时钟输出控制寄存器 */
	__IO uint32_t RESERVED0;      /*!< 0x14 - Reserve */       
	__IO uint32_t RSTCR;          /*!< 0x18 - 系统复位控制寄存器 */
	__IO uint32_t RSTSR;          /*!< 0x1C - 复位状态寄存器     */  
	__IO uint32_t SYSCLKCR;       /*!< 0x20 - 时钟源设置寄存器   */  
	__IO uint32_t SYSCLKSEL;      /*!< 0x24 - 系统时钟源选择寄存器 */
	__IO uint32_t HIRCCR;         /*!< 0x28 - 内部高速RC振荡器控制寄存器  */
	__IO uint32_t HXTCR;          /*!< 0x2C - 外部高速晶体振荡器控制寄存器 */
	__IO uint32_t LIRCCR;         /*!< 0x30 - 内部低速RC振荡器控制寄存器  */
	__IO uint32_t RESERVED1;      /*!< 0x34 - Reserve */
	__IO uint32_t IRQLATENCY;     /*!< 0x38 - M0 IRQ延时控制  */ 
	__IO uint32_t STICKCR;        /*!< 0x3C - SysTick Timer周期校准寄存器 */
	__IO uint32_t SWDIOCR;        /*!< 0x40 - 管脚特殊功能选择寄存器 */
	__IO uint32_t PERIPRST;       /*!< 0x44 - 周边模块复位控制寄存器 */
    __IO uint32_t RESERVED2;      /*!< 0x48 - Reserve  */
	__IO uint32_t PLLCR;	      /*!< 0x4C - PLL控制寄存器  */
	__IO uint32_t CANCR;          /*!< 0x50 - CAN时钟寄存器  */
	__IO uint32_t RESERVED3;      /*!< 0x54 - Reserve */
	__IO uint32_t RESERVED4;      /*!< 0x58 - Reserve */
	__IO uint32_t RESERVED5;      /*!< 0x5C - Reserve */
	__IO uint32_t UNLOCK;         /*!< 0x60 - 寄存器写保护 */
    __IO uint32_t RESERVED[183];  /*!< 0x64 ~ 0x33C - Reserve */
    __IO uint32_t HXTUNLOCK;      /*!< 0x340 - 外部高速晶体振荡器解锁寄存器 */
} RCC_TypeDef;


/**
  * @}addtogroup SYSCON_TypeDef / 系统配置 
  */
typedef struct
{
	__IO uint32_t CFGR0;           /*!< 0x00 - 系统配置寄存器 0   */
	__IO uint32_t PORTINTCR;       /*!< 0x04 - 端子的中断模式设定 */
	__IO uint32_t PORTCR;          /*!< 0x08 - 管脚控制寄存器  */
    __IO uint32_t RESERVED0;       /*!< 0x0C - Reserved */
	__IO uint32_t ETIMERCR;        /*!< 0x10 - ETIMER 通道输入源选择 */
	__IO uint32_t TIM2CR;          /*!< 0x14 - TIM2 通道输入源选择 */
	__IO uint32_t RESERVED1;       /*!< 0x18 - Reserved  */
	__IO uint32_t RESERVED2;       /*!< 0x1C - Reserved  */
	__IO uint32_t RSTCTRL;         /*!< 0x20 - 外部复位控制寄存器 */
	__IO uint32_t RESERVED3;       /*!< 0x24 - Reserved  */
	__IO uint32_t RESERVED4;       /*!< 0x28 - Reserved  */
	__IO uint32_t RESERVED5;       /*!< 0x2C - Reserved  */
	__IO uint32_t NMICR;           /*!< 0x30 - NMI控制寄存器 */
	__IO uint32_t NMISR;           /*!< 0x34 - NMI状态寄存器 */
	__IO uint32_t RESERVED6;       /*!< 0x38 - Reserved */
	__IO uint32_t RESERVED7;       /*!< 0x3C - Reserved */
	__IO uint32_t RESERVED8;       /*!< 0x40 - Reserved */
	__IO uint32_t RESERVED9;       /*!< 0x44 - Reserved */
    __IO uint32_t RESERVED10;      /*!< 0x48 - Reserved */
	__IO uint32_t RESERVED11;      /*!< 0x4C - Reserved */
	__IO uint32_t UNLOCK;          /*!< 0x50 - 寄存器写保护 */
} SYSCON_TypeDef;


/**
  * @} GPIO_TypeDef / 通用输入输出口
  */
typedef struct
{
	__IO uint32_t DIRCR;        /*!< 0x00 - 输入输出模式寄存器 */
	__IO uint32_t OTYPER;       /*!< 0x04 - 输出类型寄存器 */
	__IO uint32_t ODR;          /*!< 0x08 - 输出数据寄存器 */
	__IO uint32_t IDR;          /*!< 0x0C - 输入数据寄存器 */
	__IO uint32_t INTEN;        /*!< 0x10 - 中断使能寄存器 */
	__IO uint32_t RAWINTSR;     /*!< 0x14 - 中断原始状态寄存器, 只读,不论中断是否使能，都可以读到中断状态 */
	__IO uint32_t MSKINTSR;     /*!< 0x18 - 中断状态寄存器 */
	__IO uint32_t INTCLR;       /*!< 0x1C - 中断清除寄存器 */
	__IO uint32_t INTTYPCR;     /*!< 0x20 - 中断类型寄存器 */
	__IO uint32_t INTPOLCR;     /*!< 0x24 - 中断极性寄存器 */
	__IO uint32_t INTANY;       /*!< 0x28 - 任意边沿触发中断寄存器 */
	__IO uint32_t ODSET;        /*!< 0x2C - 输出置位寄存器 */
	__IO uint32_t ODCLR;        /*!< 0x30 - 输出清除寄存器 */
	__IO uint32_t INDBEN;       /*!< 0x34 - 输入去抖动和同步使能寄存器 */
	__IO uint32_t DBCLKCR;      /*!< 0x38 - 输入去抖动时钟配置寄存器   */
	__IO uint32_t PUPDR;        /*!< 0x3C - 上拉/下拉寄存器  */
	__IO uint32_t SLEWCR;       /*!< 0x40 - 电压转换速率控制 */
	__IO uint32_t DRVCR;        /*!< 0x44 - 驱动强度配置     */
	__IO uint32_t AFR1;         /*!< 0x48 - 复用功能寄存器1  */
    __IO uint32_t AFR2;         /*!< 0x4C - 复用功能寄存器2  */
    __IO uint32_t CS;           /*!< 0x50 - 施密特触发输入选择寄存器 */
} GPIO_TypeDef;


/**
  * @} FLASH_TypeDef / FLASH控制器
  */
typedef struct
{
	__IO uint32_t ACR;          /*!< 0x00 - 闪存访问控制寄存器 */ 
	__IO uint32_t KEYR;         /*!< 0x04 - FPEC键寄存器  */ 	
	__IO uint32_t OPTKEYR;      /*!< 0x08 - 闪存OPTKEY寄存器 */ 	
	__IO uint32_t SR;           /*!< 0x0C - 闪存状态寄存器 */ 	
	__IO uint32_t CR;           /*!< 0x10 - 闪存控制寄存器 */ 		
	__IO uint32_t AR;           /*!< 0x14 - 闪存地址寄存器 */ 	
	__IO uint32_t RESERVED0;    /*!< 0x18 - Reserved  */ 
	__IO uint32_t OBR;          /*!< 0x1C - 选择字节寄存器 */ 
	__IO uint32_t WRPR1;        /*!< 0x20 - 写保护寄存器1  */ 
	__IO uint32_t WRPR2;        /*!< 0x24 - 写保护寄存器2  */ 
    __IO uint32_t RESERVED1;    /*!< 0x28 - Reserved */ 
    __IO uint32_t RESERVED2;    /*!< 0x2C - Reserved */ 
    __IO uint32_t RESERVED3;    /*!< 0x30 - Reserved */ 
    __IO uint32_t RESERVED4;    /*!< 0x34 - 写保护寄存器3 */ 
    __IO uint32_t RESERVED5;    /*!< 0x38 - 写保护寄存器4 */ 
    __IO uint32_t SWDP;         /*!< 0x3C - SWD保护寄存器 */ 
} FLASH_TypeDef;                                                


/**
  * @} SRAM_TypeDef / SRAM控制器
  */
typedef struct
{
    __IO uint32_t ECCEN;      /*!< 0x00 - SRAM ECC错误检测功能使能寄存器 */ 
    __IO uint32_t ECCCR;      /*!< 0x04 - SRAM 控制寄存器 */
} SRAM_TypeDef;


/**
  * @} CRC_TypeDef / CRC循环冗余校验
  */
typedef struct
{
    __IO uint32_t CR;          /*!< 0x00 - 控制寄存器 */ 
    __IO uint32_t DATAIN;      /*!< 0x04 - 数据输入寄存器 */
    __IO uint32_t DATAOUT;     /*!< 0x08 - 数据输出寄存器 */
    __IO uint32_t MAR;         /*!< 0x0C - 监测地址寄存器 */
} CRC_TypeDef;

/** 
* @brief ETIMER_TypeDef / 高级定时器ETIMER
  */
typedef struct
{
    __IO uint32_t CR1;        /*!< 0x00 - 控制寄存器1  */ 
    __IO uint32_t CR2;        /*!< 0x04 - 控制寄存器2  */ 
    __IO uint32_t SMCR;       /*!< 0x08 - 从模式控制寄存器 */ 
    __IO uint32_t DIER;       /*!< 0x0C - 中断使能寄存器 */ 
    __IO uint32_t SR;         /*!< 0x10 - 状态寄存器     */ 
    __IO uint32_t EGR;        /*!< 0x14 - 事件产生寄存器  */ 
    __IO uint32_t CCMR1;      /*!< 0x18 - 捕获/比较模式寄存器1 */ 
    __IO uint32_t CCMR2;      /*!< 0x1C - 捕获/比较模式寄存器2 */ 
    __IO uint32_t CCER;       /*!< 0x20 - 捕获/比较使能寄存器  */ 
    __IO uint32_t CNT;        /*!< 0x24 - 计数器   */ 
    __IO uint32_t PSC;        /*!< 0x28 - 预分频器 */ 
    __IO uint32_t ARR;        /*!< 0x2C - 自动重装载寄存器 */ 
    __IO uint32_t RCR;        /*!< 0x30 - 重复计数寄存器   */ 
    __IO uint32_t CCR1A;      /*!< 0x34 - 捕获/比较寄存器1A */ 
    __IO uint32_t CCR2A;      /*!< 0x38 - 捕获/比较寄存器2A */ 
    __IO uint32_t CCR3A;      /*!< 0x3C - 捕获/比较寄存器3A */ 
    __IO uint32_t CCR4A;      /*!< 0x40 - 捕获/比较寄存器4A */ 
    __IO uint32_t BDTR;       /*!< 0x44 - 刹车和死区寄存器 */ 
    __IO uint32_t RESERVED0;  /*!< 0x48 - Reserved */ 
    __IO uint32_t RESERVED1;  /*!< 0x4C - Reserved */ 
    __IO uint32_t CCR1B;      /*!< 0x50 - 捕获/比较寄存器1B */ 
    __IO uint32_t CCR2B;      /*!< 0x54 - 捕获/比较寄存器2B */ 
    __IO uint32_t CCR3B;      /*!< 0x58 - 捕获/比较寄存器3B */ 
    __IO uint32_t CCR4B;      /*!< 0x5C - 捕获/比较寄存器4B */ 
} ETIMER_TypeDef;	


/** 
* @brief ADVTIM_TypeDef / 高级定时器
  */
typedef struct
{
    __IO uint32_t CR1;        /*!< 0x00 - 控制寄存器1  */ 
    __IO uint32_t CR2;        /*!< 0x04 - 控制寄存器2  */ 
    __IO uint32_t SMCR;       /*!< 0x08 - 从模式控制寄存器 */ 
    __IO uint32_t DIER;       /*!< 0x0C - 中断使能寄存器 */ 
    __IO uint32_t SR;         /*!< 0x10 - 状态寄存器     */ 
    __IO uint32_t EGR;        /*!< 0x14 - 事件产生寄存器  */ 
    __IO uint32_t CCMR1;      /*!< 0x18 - 捕获/比较模式寄存器1 */ 
    __IO uint32_t CCMR2;      /*!< 0x1C - 捕获/比较模式寄存器2 */ 
    __IO uint32_t CCER;       /*!< 0x20 - 捕获/比较使能寄存器  */ 
    __IO uint32_t CNT;        /*!< 0x24 - 计数器   */ 
    __IO uint32_t PSC;        /*!< 0x28 - 预分频器 */ 
    __IO uint32_t ARR;        /*!< 0x2C - 自动重装载寄存器 */ 
    __IO uint32_t RESERVED0;  /*!< 0x30 - Reserved */ 
    __IO uint32_t CCR1;       /*!< 0x34 - 捕获/比较寄存器1 */ 
    __IO uint32_t CCR2;       /*!< 0x38 - 捕获/比较寄存器2 */ 
    __IO uint32_t CCR3;       /*!< 0x3C - 捕获/比较寄存器3 */ 
    __IO uint32_t CCR4;       /*!< 0x40 - 捕获/比较寄存器4 */  
} ADVTIM_TypeDef;  


/**
  * @}TIM_TypeDef / 基础定时器TIM10 & TIM11
  */
typedef struct
{
	__IO uint32_t CR;           /*!< 0x00 - 控制寄存器 */
	__IO uint32_t LOAD;         /*!< 0x04 - 32位立即重载寄存器 */
	__IO uint32_t CNT;          /*!< 0x08 - 读计数器寄存器   */
	__IO uint32_t RAWINTSR;     /*!< 0x0C - 读原始中断寄存器 */
	__IO uint32_t MSKINTSR;     /*!< 0x10 - 读中断寄存器   */
	__IO uint32_t INTCLR;       /*!< 0x14 - 中断清除寄存器 */
	__IO uint32_t BGLOAD;       /*!< 0x18 - 32位周期重载寄存器 */
} TIM_TypeDef;


/**
  * @}addtogroup LPTIM_TypeDef / 低功耗定时器
  */
typedef struct
{
	__IO uint32_t CNTVAL;       /*!< 0x00 - 计数值只读寄存器 */
	__IO uint32_t CR;           /*!< 0x04 - 控制寄存器     */
	__IO uint32_t LOAD;         /*!< 0x08 - 立即重载寄存器 */
	__IO uint32_t INTSR;        /*!< 0x0C - 中断寄存器     */
	__IO uint32_t INTCLR;	    /*!< 0x10 - 中断清除寄存器 */
	__IO uint32_t BGLOAD;       /*!< 0x14 - 周期重载寄存器 */
} LPTIM_TypeDef;


/**
  * @} AWK_TypeDef / 自动唤醒定时器
  */
typedef struct
{
	__IO uint32_t CR;           /*!< 0x00 - 自唤醒定时器控制寄存器 */ 
	__IO uint32_t RLOAD;        /*!< 0x04 - 自唤醒定时器重装载数据寄存器 */ 
	__IO uint32_t SR;           /*!< 0x08 - 自唤醒定时器状态寄存器 */ 
	__IO uint32_t INTCLR;       /*!< 0x0C - 自唤醒中断清除寄存器   */ 
} AWK_TypeDef;


/** 
  * @brief IWDG_TypeDef / 独立看门狗
  */
typedef struct
{
    __IO uint32_t CMDCR;        /*!< 0x00 - 控制命令寄存器 */
    __IO uint32_t CFGR;         /*!< 0x04 - 配置寄存器 */
    __IO uint32_t RLOAD;        /*!< 0x08 - 计数器重装载寄存器 */
    __IO uint32_t CNTVAL;       /*!< 0x0C - 计数器值   */
    __IO uint32_t SR;           /*!< 0x10 - 中断状态寄存器 */
    __IO uint32_t INTCLR;       /*!< 0x14 - 中断清除寄存器 */
    __IO uint32_t UNLOCK;       /*!< 0x18 - 寄存器访问保护 */
} IWDG_TypeDef;


/** 
  * @brief WWDG_TypeDef / 系统窗口看门狗
  */
typedef struct
{
    __IO uint32_t RLOAD;        /*!< 0x00 - 重载计数寄存器 */
    __IO uint32_t CR;           /*!< 0x04 - 控制寄存器     */
    __IO uint32_t INTEN;        /*!< 0x08 - 中断使能寄存器 */
    __IO uint32_t SR;           /*!< 0x0C - 状态寄存器     */
    __IO uint32_t INTCLR;       /*!< 0x10 - 中断清除寄存器 */
    __IO uint32_t CNTVAL;       /*!< 0x14 - 计数器值寄存器 */
} WWDG_TypeDef;


/** 
  * @brief BEEP_TypeDef / 蜂鸣器
  */
typedef struct
{
    __IO uint32_t CSR;        /*!< 0x00 - 蜂鸣器控制寄存器 */
} BEEP_TypeDef;


/** 
  * @brief EUART_TypeDef / 通用异步收发器
  */
typedef struct
{
	__IO uint32_t RESERVED0;  /*!< 0x00 - 保留位 */
	__IO uint32_t RESERVED1;  /*!< 0x04 - 保留位 */
	__IO uint32_t GLOBAL;     /*!< 0x08 - 全局寄存器 */
	__IO uint32_t RESERVED2;  /*!< 0x0C - 保留位 */
	__IO uint32_t BAUD;       /*!< 0x10 - 波特率寄存器 */
	__IO uint32_t STAT;       /*!< 0x14 - 状态寄存器 */
	__IO uint32_t CTRL;       /*!< 0x18 - 控制寄存器 */
	__IO uint32_t DATA;       /*!< 0x1C - 数据寄存器 */
    __IO uint32_t MATCH;      /*!< 0x20 - 地址匹配寄存器 */
    __IO uint32_t MODIR;      /*!< 0x24 - IrDA模式寄存器 */
    __IO uint32_t FIFO;       /*!< 0x28 - FIFO寄存器 */
    __IO uint32_t WATER;      /*!< 0x2C - 水位寄存器 */
} EUART_TypeDef;


/** 
  * @brief I2C_TypeDef / I2C接口  
  */
typedef struct
{
	__IO uint32_t CR;         /*!< 0x00 - 配置寄存器 */ 
    __IO uint32_t DATA;       /*!< 0x04 - 数据寄存器 */ 
    __IO uint32_t ADDR;       /*!< 0x08 - 地址寄存器 */ 
    __IO uint32_t SR;         /*!< 0x0C - 状态寄存器 */ 
    __IO uint32_t TIMRUN;     /*!< 0x10 - 波特率计数器使能寄存器 */ 
    __IO uint32_t BAUDCR;     /*!< 0x14 - 波特率计数器配置寄存器 */ 
} I2C_TypeDef;


/**
  * @} ASPI_TypeDef / 高级串行外设接口ASPI
  */
typedef struct
{
	__IO uint32_t SPDR;           /*!< 0x00 - 数据寄存器  */  
	__IO uint32_t SPDLR;          /*!< 0x04 - 延迟寄存器 */
	__IO uint32_t SPCR;           /*!< 0x08 - 控制寄存器  */
	__IO uint32_t SPPCR;          /*!< 0x0C - 引脚控制寄存器 */
    __IO uint32_t SPBR;           /*!< 0x10 - 波特率控制寄存器 */
    __IO uint32_t SPCMD;          /*!< 0x14 - 命令寄存器  */
    __IO uint32_t RESERVED0;      /*!< 0x18 - Reserved */ 
    __IO uint32_t RESERVED1;      /*!< 0x1C - Reserved */ 
    __IO uint32_t RESERVED2;      /*!< 0x20 - Reserved */ 
    __IO uint32_t RESERVED3;      /*!< 0x24 - Reserved */ 
    __IO uint32_t RESERVED4;      /*!< 0x28 - Reserved */ 
    __IO uint32_t RESERVED5;      /*!< 0x2C - Reserved */ 
    __IO uint32_t RESERVED6;      /*!< 0x30 - Reserved */ 
    __IO uint32_t RESERVED7;      /*!< 0x34 - Reserved */ 
    __IO uint32_t RESERVED8;      /*!< 0x38 - Reserved */ 
    __IO uint32_t RESERVED9;      /*!< 0x3C - Reserved */ 
    __IO uint32_t SPDCR1;         /*!< 0x40 - 数据控制寄存器1 */ 
    __IO uint32_t SPDCR2;         /*!< 0x44 - 数据控制寄存器2 */ 
    __IO uint32_t RESERVED10;     /*!< 0x48 - Reserved */ 
    __IO uint32_t RESERVED11;     /*!< 0x4C - Reserved */ 
    __IO uint32_t SPSR;           /*!< 0x50 - 状态寄存器 */ 
    __IO uint32_t RESERVED12;     /*!< 0x54 - Reserved */ 
    __IO uint32_t SPTFSR;         /*!< 0x58 - 发送FIFO状态寄存器 */
    __IO uint32_t SPRFSR;         /*!< 0x5C - 接收FIFO状态寄存器 */
    __IO uint32_t RESERVED13;     /*!< 0x60 - Reserved */ 
    __IO uint32_t RESERVED14;     /*!< 0x64 - Reserved */ 
    __IO uint32_t SPSCR;          /*!< 0x68 - 状态清除寄存器 */ 
    __IO uint32_t SPFCR;          /*!< 0x6C - FIFO清除寄存器 */ 
} ASPI_TypeDef;


/**
  * @} SPI_TypeDef / 串行外设接口SPI
  */
typedef struct
{
	__IO uint32_t CR;         /*!< 0x00 - 配置寄存器 */  
	__IO uint32_t SSN;        /*!< 0x04 - 片选配置寄存器 */
	__IO uint32_t SR;         /*!< 0x08 - 状态寄存器 */
	__IO uint32_t DATA;       /*!< 0x0C - 数据寄存器 */
} SPI_TypeDef;


/**
  * @} CLKTRIM_TypeDef / 时钟安全及校准
  */
typedef struct
{
	__IO uint32_t CR;           /*!< 0x00 - 配置寄存器 */ 
	__IO uint32_t REFCON;       /*!< 0x04 - 参考计数器初值配置寄存器 */ 
	__IO uint32_t REFCNT;       /*!< 0x08 - 参考计数器值寄存器 */ 
	__IO uint32_t CALCNT;       /*!< 0x0C - 校准计数器值寄存器 */ 
	__IO uint32_t IFR;          /*!< 0x10 - 中断标志位寄存器 */ 
	__IO uint32_t ICLR;         /*!< 0x14 - 中断标志位清除寄存器 */ 
	__IO uint32_t RESERVED0;    /*!< 0x18 - Reserved 0 */ 
    __IO uint32_t HTCR;         /*!< 0x1C - 时钟监测上限阈值比较寄存器 */ 
    __IO uint32_t LTCR;         /*!< 0x20 - 时钟监测下限阈值比较寄存器 */ 
} CLKTRIM_TypeDef;


/**
  * @} ADC_TypeDef / 模拟-数字转换器
  */
typedef struct
{
	__IO uint32_t CR0;              /*!< 0x00 - 配置寄存器 0 */
    __IO uint32_t CR1;              /*!< 0x04 - 配置寄存器 1 */
    __IO uint32_t SQR0;             /*!< 0x08 - 顺序扫描转换通道配置寄存器 0 */
    __IO uint32_t SQR1;             /*!< 0x0C - 顺序扫描转换通道配置寄存器 1 */
    __IO uint32_t RESERVED_0;       /*!< 0x10 - Reserved 0 */
    __IO uint32_t JQR;              /*!< 0x14 - 插队扫描转换通道配置寄存器 */
    __IO uint32_t SQRRESULT0;       /*!< 0x18 - 顺序扫描转换通道 0 转换结果 */
    __IO uint32_t SQRRESULT1;       /*!< 0x1C - 顺序扫描转换通道 1 转换结果 */
    __IO uint32_t SQRRESULT2;       /*!< 0x20 - 顺序扫描转换通道 2 转换结果 */
    __IO uint32_t SQRRESULT3;       /*!< 0x24 - 顺序扫描转换通道 3 转换结果 */
    __IO uint32_t SQRRESULT4;       /*!< 0x28 - 顺序扫描转换通道 4 转换结果 */
    __IO uint32_t SQRRESULT5;       /*!< 0x2C - 顺序扫描转换通道 5 转换结果 */
    __IO uint32_t SQRRESULT6;       /*!< 0x30 - 顺序扫描转换通道 6 转换结果 */
    __IO uint32_t SQRRESULT7;       /*!< 0x34 - 顺序扫描转换通道 7 转换结果 */
    __IO uint32_t SQRRESULT8;       /*!< 0x38 - 顺序扫描转换通道 8 转换结果 */
    __IO uint32_t SQRRESULT9;       /*!< 0x3C - 顺序扫描转换通道 9 转换结果 */
    __IO uint32_t RESERVED_1;       /*!< 0x40 - Reserved 1 */
    __IO uint32_t RESERVED_2;       /*!< 0x44 - Reserved 2 */
    __IO uint32_t RESERVED_3;       /*!< 0x48 - Reserved 3 */
    __IO uint32_t RESERVED_4;       /*!< 0x4C - Reserved 4 */
    __IO uint32_t JQRRESULT0;       /*!< 0x50 - 插队扫描转换通道 0 转换结果 */
    __IO uint32_t JQRRESULT1;       /*!< 0x54 - 插队扫描转换通道 1 转换结果 */
    __IO uint32_t JQRRESULT2;       /*!< 0x58 - 插队扫描转换通道 2 转换结果 */
    __IO uint32_t JQRRESULT3;       /*!< 0x5C - 插队扫描转换通道 3 转换结果 */
    __IO uint32_t RESULT;           /*!< 0x60 - 转换结果寄存器 */
    __IO uint32_t RESERVED5;        /*!< 0x64 - Reserved 5 */
    __IO uint32_t HT;               /*!< 0x68 - 比较上阈值 */
    __IO uint32_t LT;               /*!< 0x6C - 比较下阈值 */
    __IO uint32_t IER;              /*!< 0x70 - 中断使能寄存器  */
    __IO uint32_t IFR;              /*!< 0x74 - 中断标志寄存器 */
    __IO uint32_t ICR;              /*!< 0x78 - 中断清除寄存器 */
    __IO uint32_t EXTTRIGGER0;      /*!< 0x7C - 单次转换或顺序扫描转换外部中断触发源配置寄存器 0 */
    __IO uint32_t EXTTRIGGER1;      /*!< 0x80 - 插队扫描转换外部中断触发源配置寄存器 1 */
    __IO uint32_t SGLSTART;         /*!< 0x84 - 单次转换启动控制寄存器 */
    __IO uint32_t SQRSTART;         /*!< 0x88 - 顺序扫描转换启动控制寄存器 */
    __IO uint32_t JQRSTART;         /*!< 0x8C - 插队扫描转换启动控制寄存器 */
} ADC_TypeDef;


/**
  * @}addtogroup TSN_TypeDef / 温度传感器
  */
typedef struct
{
	__IO uint32_t HIGHTEMP;     /*!< 0x00 - Tj=150℃时，CP高温测试所测得的TSN输出电压值 */ 
	__IO uint32_t LOWTEMP;      /*!< 0x04 - Tj=-40℃时，CP低温测试所测得的TSN输出电压值 */
    __IO uint32_t NORMTEMP;     /*!< 0x08 - Ta=25℃时，FT常温测试所测得的TSN输出电压值   */
}TSN_TypeDef;


/**
  * @}addtogroup LVD_TypeDef / 低电压检测器  
  */
typedef struct
{
	__IO uint32_t CR;       /*!< 0x00 - 控制寄存器 */ 
	__IO uint32_t SR;       /*!< 0x04 - 状态寄存器 */
}LVD_TypeDef;


/**                                                             
  * @} VC_TypeDef / 比较器                                        
  */                                                            
typedef struct                                                  
{                                                               
    __IO uint32_t CSR;         /*!< 0x00 - VC控制和状态寄存器 */ 
    __IO uint32_t CR;          /*!< 0x04 - VC控制寄存器 */ 
    __IO uint32_t OUTCFG;      /*!< 0x08 - VC输出配置寄存器 */  
    __IO uint32_t SR;          /*!< 0x0C - VC状态寄存器 */ 
    __IO uint32_t RESERVED_0;  /*!< 0x10 - Reserved 0 */
    __IO uint32_t RESERVED_1;  /*!< 0x14 - Reserved 1 */
    __IO uint32_t RESERVED_2;  /*!< 0x18 - Reserved 2 */
    __IO uint32_t RESERVED_3;  /*!< 0x1C - Reserved 3 */
    __IO uint32_t RESERVED_4;  /*!< 0x20 - Reserved 4 */
    __IO uint32_t RESERVED_5;  /*!< 0x24 - Reserved 5 */
    __IO uint32_t RESERVED_6;  /*!< 0x28 - Reserved 6 */
    __IO uint32_t RESERVED_7;  /*!< 0x2C - Reserved 7 */
    __IO uint32_t PGACR;       /*!< 0x30 - PGA控制寄存器 */
} VC_TypeDef;


/**
  * @} DEBUG_TypeDef / Debug支持  
  */
typedef struct
{
	__IO uint32_t APBFZ;     /*!< 0x00 - Debug模式控制寄存器 */ 
} DEBUG_TypeDef;



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ****************************    CAN    *************************************/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
  * @brief Controller Area Network
  */

#define CAN_BUFFER_SIZE      (64 / 4)       /*!< CAN Buffer Size   */

/**
  * @brief CAN receive buffer register define structure
  */

typedef struct
{
    __IO uint32_t  ID_ESI;                  /*!< [31]: Error state indicator (ESI)          */
                                            /*!< [28:0]: Identifier (ID)                    */
                                                                                            
    __IO uint32_t  RXCTRL;                  /*!< [15:13]: Kind of error                     */
                                            /*!< [12]: For lookback mode (Tx)               */
                                            /*!< [7]: Identifier extension (IDE)            */
                                            /*!< [6]: Remote transmission request (RTR)     */
                                            /*!< [5]: FD format indicator (FDF)             */
                                            /*!< [4]: Bit rate switch (BRS)                 */
                                            /*!< [3:0]: Data length code (DLC)              */
                                                                                                                                                                                               
    __IO uint32_t  DATA[CAN_BUFFER_SIZE];   /*!< Buffer data                                */
    __IO uint32_t  RTS0;                    /*!< Receive time stamps 0                      */
    __IO uint32_t  RTS1;                    /*!< Receive time stamps 1                      */
} CAN_RxBufferTypedef;

/**
  * @brief CAN transmit buffer register define structure
  */

typedef struct
{
    __IO uint32_t  ID_TTSEN;                /*!< [31]: Transmit time-stamp enable (TISEN)   */
                                            /*!< [28:0]: Identifier (ID)                    */
                                            
    __IO uint32_t  TXCTRL;                  /*!< [7]: Identifier extension (IDE)            */
                                            /*!< [6]: Remote transmission request (RTR)     */
                                            /*!< [5]: FD format indicator (FDF)             */
                                            /*!< [4]: Bit rate switch (BRS)                 */
                                            /*!< [3:0]: Data length code (DLC)              */
                                                                                 
    __IO uint32_t  DATA[CAN_BUFFER_SIZE];   /*!< Buffer data                                */
} CAN_TxBufferTypedef;

typedef struct 
{                                           
  __IO CAN_RxBufferTypedef  RBUF;           /*!< Receive buffer                                               */
  __IO CAN_TxBufferTypedef  TBUF;           /*!< Transmit buffer                                              */
  __I  uint32_t             TTS0;           /*!< Transmission time stamp 0                                    */
  __I  uint32_t             TTS1;           /*!< Transmission time stamp 1                                    */
  __IO uint32_t             CTRL0;          /*!< Config state and transmit/receive control register 0         */
  __IO uint32_t             CTRL1;          /*!< CAN interrupt enable/disable and flag control register 1     */                                                                                                               
  __IO uint32_t             SBITRATE;       /*!< Normat CAN baudrate configuration register                   */
  __IO uint32_t             FBITRATE;       /*!< FAST CAN(CAN_FD) baudrate configuration register             */
  __IO uint32_t             ERRINFO;        /*!< CAN error type and transmit/receive error conunter register  */                                                          
  __IO uint32_t             ACFCTRL;        /*!< Acceptance Filter Control Register                           */
  __IO uint32_t             ACF;            /*!< Acceptance Code Register                                     */
  __IO uint32_t             VERSION;        /*!< Version Information Register 0                               */
} CAN_TypeDef;                              


/*----------------------- APB外设基地址定义 ----------------------*/
#define SYSCON_BASE         (0x40001C00UL)
#define SRAM_BASE           (0x40001C24UL)
#define ETIMER_BASE	        (0x40001000UL)
#define ADVTIM_BASE         (0x40003C00UL)
#define TIM10_BASE	        (0x40001800UL) 
#define TIM11_BASE	        (0x40001900UL) 
#define LPTIM_BASE          (0x40004400UL)
#define AWK_BASE	        (0x40002800UL)
#define	IWDG_BASE		    (0x40002400UL)
#define WWDG_BASE           (0x40002000UL)
#define BEEP_BASE           (0x40004800UL)
#define	EUART0_BASE		    (0x40000000UL)
#define	EUART1_BASE		    (0x40000400UL)
#define	I2C0_BASE		    (0x40000C00UL)
#define ASPI_BASE           (0x40000800UL)
#define SPI1_BASE           (0x40005800UL)
#define CAN0_BASE           (0x40005400UL)
#define CLKTRIM_BASE        (0x40003400UL)
#define ADC_BASE            (0x40002C00UL)
#define TSN_BASE            (0x1FFFF050UL)
#define LVD_BASE            (0x40004000UL)
#define VC_BASE             (0x40004080UL)
#define DEBUG_BASE          (0x40004C00UL)

/*------------------------ AHB外设基地址定义 ----------------------*/
#define RCC_BASE            (0x40020000UL)
#define FLASH_BASE          (0x40020400UL)
#define CRC_BASE            (0x40020800UL)
#define	GPIOA_BASE		    (0x40021000UL)
#define	GPIOB_BASE		    (0x40021400UL)
#define	GPIOC_BASE		    (0x40021800UL)
#define	GPIOD_BASE		    (0x40021C00UL)
#define GPIOE_BASE          (0x40022000UL)

/*------------------------------------------------------------------*/
/*                                                                  */
/*           BASE ADDRESS DEFINE, DEFINE ALL MODE......             */
/*                                                                  */
/*------------------------------------------------------------------*/
#define SYSCON          ((SYSCON_TypeDef *)SYSCON_BASE)   
#define SRAM            ((SRAM_TypeDef *)SRAM_BASE)       
#define ETIMER			((ETIMER_TypeDef *)ETIMER_BASE)   
#define TIM2            ((ADVTIM_TypeDef *)ADVTIM_BASE)   
#define TIM10           ((TIM_TypeDef *)TIM10_BASE) 
#define TIM11           ((TIM_TypeDef *)TIM11_BASE) 
#define LPTIM           ((LPTIM_TypeDef *)LPTIM_BASE) 
#define AWK             ((AWK_TypeDef *)AWK_BASE)
#define IWDG            ((IWDG_TypeDef *)IWDG_BASE)
#define WWDG            ((WWDG_TypeDef *)WWDG_BASE)
#define BEEP            ((BEEP_TypeDef *)BEEP_BASE)
#define EUART0          ((EUART_TypeDef *)EUART0_BASE)
#define EUART1          ((EUART_TypeDef *)EUART1_BASE)
#define I2C0            ((I2C_TypeDef *)I2C0_BASE)
#define ASPI            ((ASPI_TypeDef *)ASPI_BASE)
#define SPI1            ((SPI_TypeDef *)SPI1_BASE)
#define CAN0            ((CAN_TypeDef *)CAN0_BASE) 
#define CAN             ((CAN_TypeDef *)CAN0_BASE) 
#define CLKTRIM         ((CLKTRIM_TypeDef *)CLKTRIM_BASE)
#define ADC             ((ADC_TypeDef *)ADC_BASE)                    
#define TSN             ((TSN_TypeDef *)TSN_BASE)                               
#define LVD             ((LVD_TypeDef *)LVD_BASE) 
#define VC              ((VC_TypeDef *)VC_BASE) 
#define DEBUG           ((DEBUG_TypeDef *)DEBUG_BASE)  

#define RCC             ((RCC_TypeDef *)RCC_BASE) 
#define FLASH           ((FLASH_TypeDef *)FLASH_BASE)  
#define CRC             ((CRC_TypeDef *)CRC_BASE)        
#define GPIOA           ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB           ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC           ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD           ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE           ((GPIO_TypeDef *)GPIOE_BASE)


#ifdef __cplusplus
}
#endif

#endif /* __CPS32K21X_H__ */

