#include <bsp-interface/di/interrupt.h>
#include <Exti.h>

bsp::IExtiManager &DI_ExtiManager()
{
    return hal::Exti::Instance();
}
