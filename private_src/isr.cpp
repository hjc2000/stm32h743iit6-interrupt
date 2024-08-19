#include <bsp-interface/di.h>
#include <stm32h743iit6-interrupt/Interrupt.h>

static void SafeRun(std::function<void()> &func)
{
    try
    {
        func();
    }
    catch (...)
    {
    }
}

extern "C"
{
    void USART1_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::USART1_IRQn));
        SafeRun(func);
    }

    void TIM3_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::TIM3_IRQn));
        SafeRun(func);
    }

    void WWDG1_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::WWDG_IRQn));
        SafeRun(func);
    }

    void EXTI0_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI0_IRQn));
        SafeRun(func);
    }

    void EXTI1_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI1_IRQn));
        SafeRun(func);
    }

    void EXTI2_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI2_IRQn));
        SafeRun(func);
    }

    void EXTI3_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI3_IRQn));
        SafeRun(func);
    }

    void EXTI4_IRQHandler()
    {
        std::function<void()> &func = DI_IsrManager().GetIsr(static_cast<uint32_t>(IRQn_Type::EXTI4_IRQn));
        SafeRun(func);
    }
}
