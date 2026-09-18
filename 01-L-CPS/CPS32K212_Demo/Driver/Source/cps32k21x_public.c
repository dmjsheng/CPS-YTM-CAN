#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include <stdio.h>
#include <string.h>


/*******************************************************************************
函数名称： cps_ddl_memclr
实现功能： Memory clear function for STRUCT_MEMCLR(x)宏
输入参数： p_Address  --> 指向内存单元地址
返回参数： memSize    --> 内存空间大小，以字节为单位
*******************************************************************************/
void cps_ddl_memclr(void* p_Address, uint32_t memSize)
{
    uint8_t* p_Addr = (uint8_t*)p_Address;
    
    if (NULL == p_Addr)   // NULL在#include <string.h>中有定义
    {
        return;
    }
    
    while (memSize--)
    {
        *p_Addr++ = 0;
    }
}
