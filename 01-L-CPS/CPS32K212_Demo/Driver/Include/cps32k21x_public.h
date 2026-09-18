#ifndef __CPS32K21X_PUBLIC_H__
#define __CPS32K21X_PUBLIC_H__


#include "cps32k21x.h"
#include <stdio.h>
#include <string.h>


#ifndef STRUCT_MEMCLR
#define STRUCT_MEMCLR(x)      cps_ddl_memclr((uint8_t*)(&(x)), (uint32_t)(sizeof(x)))
#endif

#define DEC2BCD(x)            ((((x) / 10) << 4) + ((x) % 10))
#define BCD2DEC(x)            ((((x) >> 4) * 10) + ((x) & 0x0F))

/* -------------------------- Bit Define  -------------------------------------*/
#define BIT0         ((uint32_t)0x00000001)
#define BIT1         ((uint32_t)0x00000002)
#define BIT2         ((uint32_t)0x00000004)
#define BIT3         ((uint32_t)0x00000008)
#define BIT4         ((uint32_t)0x00000010)
#define BIT5         ((uint32_t)0x00000020)
#define BIT6         ((uint32_t)0x00000040)
#define BIT7         ((uint32_t)0x00000080)
#define BIT8         ((uint32_t)0x00000100)
#define BIT9         ((uint32_t)0x00000200)
#define BIT10        ((uint32_t)0x00000400)
#define BIT11        ((uint32_t)0x00000800)
#define BIT12        ((uint32_t)0x00001000)
#define BIT13        ((uint32_t)0x00002000)
#define BIT14        ((uint32_t)0x00004000)
#define BIT15        ((uint32_t)0x00008000)
#define BIT16        ((uint32_t)0x00010000)
#define BIT17        ((uint32_t)0x00020000)
#define BIT18        ((uint32_t)0x00040000)
#define BIT19        ((uint32_t)0x00080000)
#define BIT20        ((uint32_t)0x00100000)
#define BIT21        ((uint32_t)0x00200000)
#define BIT22        ((uint32_t)0x00400000)
#define BIT23        ((uint32_t)0x00800000)
#define BIT24        ((uint32_t)0x01000000)
#define BIT25        ((uint32_t)0x02000000)
#define BIT26        ((uint32_t)0x04000000)
#define BIT27        ((uint32_t)0x08000000)
#define BIT28        ((uint32_t)0x10000000)
#define BIT29        ((uint32_t)0x20000000)
#define BIT30        ((uint32_t)0x40000000)
#define BIT31        ((uint32_t)0x80000000)
/* --------------------------End of  Bit Define  -----------------------------*/


#define USE_FULL_ASSERT    (1u)
#undef  USE_FULL_ASSERT

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
    #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
    /* Exported functions ------------------------------------------------------- */
    void assert_failed(uint8_t* file, uint32_t line);
#else
    #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


/*******************************************************************************
函数声明
*******************************************************************************/
extern void cps_ddl_memclr(void* p_Address, uint32_t memSize);


#endif   /* __CPS32K21X_PUBLIC_H__ */
