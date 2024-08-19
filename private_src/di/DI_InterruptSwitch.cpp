#include <InterruptSwitch.h>

bsp::IInterruptSwitch &DI_InterruptSwitch()
{
	return hal::InterruptSwitch::Instance();
}
