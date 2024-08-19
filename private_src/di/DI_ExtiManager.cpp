#include <Exti.h>
#include <bsp-interface/di.h>

bsp::IExtiManager &DI_ExtiManager()
{
	return hal::Exti::Instance();
}
