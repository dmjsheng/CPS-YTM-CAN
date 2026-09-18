#ifndef BASELIB_TYPES_H
#define BASELIB_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#define USER_UNUSED                 __attribute__((unused))
#define USER_SECTION(x)             __attribute__((section(x)))
#define USER_USED                   __attribute__((used))
#define USER_ALIGN(n)               __attribute__((aligned(n)))
#define USER_WEAK                   __attribute__((weak))
#define USER_INLINE                 static __inline

enum FLAG_STATUS
{
    E_NOT_OK = 1,
    E_OK     = 0
};

#endif /* BASELIB_TYPES_H */
