#include "can_demo_logic.h"

void CanDemoButton_Init(can_demo_button_t *button, bool released_level)
{
    if (button == 0)
    {
        return;
    }

    button->stable_level = released_level;
    button->last_sample_level = released_level;
    button->stable_sample_count = CAN_DEMO_BUTTON_DEBOUNCE_SAMPLES;
}

bool CanDemoButton_Update(can_demo_button_t *button, bool sampled_level)
{
    bool pressed_event = false;

    if (button == 0)
    {
        return false;
    }

    if (sampled_level == button->last_sample_level)
    {
        if (button->stable_sample_count < CAN_DEMO_BUTTON_DEBOUNCE_SAMPLES)
        {
            button->stable_sample_count++;
        }
    }
    else
    {
        button->last_sample_level = sampled_level;
        button->stable_sample_count = 1U;
    }

    if ((button->stable_sample_count >= CAN_DEMO_BUTTON_DEBOUNCE_SAMPLES) &&
        (button->stable_level != sampled_level))
    {
        pressed_event = button->stable_level && !sampled_level;
        button->stable_level = sampled_level;
    }

    return pressed_event;
}
