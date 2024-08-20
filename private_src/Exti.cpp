#include "Exti.h"
#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <stdexcept>

static base::Initializer _initializer{
    []()
    {
        hal::Exti::Instance();
    }};

hal::Exti::Exti()
{
    DI_IsrManager().AddIsr(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn),
                           []()
                           {
                               HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
                           });

    DI_IsrManager().AddIsr(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn),
                           []()
                           {
                               HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
                           });

    DI_IsrManager().AddIsr(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn),
                           []()
                           {
                               HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
                           });

    DI_IsrManager().AddIsr(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn),
                           []()
                           {
                               HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
                           });

    DI_IsrManager().AddIsr(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn),
                           []()
                           {
                               HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
                           });
}

void hal::Exti::Register(int line_id, std::function<void()> callback)
{
    switch (line_id)
    {
    case 0:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn));
            _on_exti0_interrupt = callback;
            DI_InterruptSwitch().EnableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn), 4);
            break;
        }
    case 1:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn));
            _on_exti1_interrupt = callback;
            DI_InterruptSwitch().EnableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn), 4);
            break;
        }
    case 2:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn));
            _on_exti2_interrupt = callback;
            DI_InterruptSwitch().EnableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn), 4);
            break;
        }
    case 3:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn));
            _on_exti3_interrupt = callback;
            DI_InterruptSwitch().EnableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn), 4);
            break;
        }
    case 4:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn));
            _on_exti4_interrupt = callback;
            DI_InterruptSwitch().EnableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn), 4);
            break;
        }
    default:
        {
            throw std::invalid_argument{"pin 超出范围。"};
        }
    }
}

void hal::Exti::Unregister(int line_id)
{
    switch (line_id)
    {
    case 0:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn));
            _on_exti0_interrupt = nullptr;
            break;
        }
    case 1:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn));
            _on_exti1_interrupt = nullptr;
            break;
        }
    case 2:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn));
            _on_exti2_interrupt = nullptr;
            break;
        }
    case 3:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn));
            _on_exti3_interrupt = nullptr;
            break;
        }
    case 4:
        {
            DI_InterruptSwitch().DisableInterrupt(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn));
            _on_exti4_interrupt = nullptr;
            break;
        }
    default:
        {
            throw std::invalid_argument{"pin 超出范围。"};
        }
    }
}

extern "C"
{
    /// @brief 重写 HAL 库中的 weak 版本
    /// @param pin
    void HAL_GPIO_EXTI_Callback(uint16_t pin)
    {
        switch (pin)
        {
        case GPIO_PIN_0:
            {
                if (hal::Exti::Instance()._on_exti0_interrupt)
                {
                    hal::Exti::Instance()._on_exti0_interrupt();
                }

                break;
            }
        case GPIO_PIN_1:
            {
                if (hal::Exti::Instance()._on_exti1_interrupt)
                {
                    hal::Exti::Instance()._on_exti1_interrupt();
                }

                break;
            }
        case GPIO_PIN_2:
            {
                if (hal::Exti::Instance()._on_exti2_interrupt)
                {
                    hal::Exti::Instance()._on_exti2_interrupt();
                }

                break;
            }
        case GPIO_PIN_3:
            {
                if (hal::Exti::Instance()._on_exti3_interrupt)
                {
                    hal::Exti::Instance()._on_exti3_interrupt();
                }

                break;
            }
        case GPIO_PIN_4:
            {
                if (hal::Exti::Instance()._on_exti4_interrupt)
                {
                    hal::Exti::Instance()._on_exti4_interrupt();
                }

                break;
            }
        default:
            {
                break;
            }
        }
    }
} // extern "C"
