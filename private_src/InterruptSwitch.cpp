#include "InterruptSwitch.h"

hal::InterruptSwitch &hal::InterruptSwitch::Instance()
{
    class Getter : public base::SingletonGetter<InterruptSwitch>
    {
    public:
        std::unique_ptr<InterruptSwitch> Create() override
        {
            return std::unique_ptr<InterruptSwitch>{new InterruptSwitch{}};
        }

        void Lock() override
        {
            __disable_irq();
        }

        void Unlock() override
        {
            __enable_irq();
        }
    };

    Getter g;
    return g.Instance();
}
