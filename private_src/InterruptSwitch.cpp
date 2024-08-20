#include "InterruptSwitch.h"
#include <base/Initializer.h>

static base::Initializer _init{
    []()
    {
        HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
        hal::InterruptSwitch::Instance();
    }};
