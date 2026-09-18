#ifndef CAN_DRV_H
#define CAN_DRV_H

#include "cps32k21x_can.h"
#include "cps32k21x_gpio.h"
#include "cps32k21x_rcc.h"
#include "baselib_types.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t id;
    uint8_t  dlc;
    uint8_t  data[8];
} can_frame_t;

void Init_CAN(void);
bool CAN_Send_Msg(uint32_t id, const uint8_t *data, uint8_t dlc);
bool CAN_Get_Rx_Msg(can_frame_t *msg);

#endif /* CAN_DRV_H */
