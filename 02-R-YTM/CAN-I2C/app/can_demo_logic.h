#ifndef CAN_DEMO_LOGIC_H
#define CAN_DEMO_LOGIC_H

#include <stdbool.h>
#include <stdint.h>

#define CAN_DEMO_BUTTON_DEBOUNCE_SAMPLES (4U)

typedef struct
{
    bool stable_level;
    bool last_sample_level;
    uint8_t stable_sample_count;
} can_demo_button_t;

void CanDemoButton_Init(can_demo_button_t *button, bool released_level);
bool CanDemoButton_Update(can_demo_button_t *button, bool sampled_level);

#endif /* CAN_DEMO_LOGIC_H */
