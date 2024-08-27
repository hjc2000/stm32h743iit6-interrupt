#pragma once
#include <base/Initializer.h>
#include <bsp-interface/di/interrupt.h>
#include <Exti.h>
#include <hal.h>

namespace hal
{
    class InterruptSwitch final :
        public bsp::IInterruptSwitch
    {
    private:
        InterruptSwitch() = default;

    public:
        static InterruptSwitch &Instance()
        {
            static InterruptSwitch o;
            return o;
        }

        void DisableInterrupt(uint32_t irq) noexcept override
        {
            HAL_NVIC_DisableIRQ(static_cast<IRQn_Type>(irq));
        }

        void EnableInterrupt(uint32_t irq) noexcept override
        {
            HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq));
        }

        /// @brief 使能指定 irq 的中断。
        /// @param irq 中断号。
        /// @param priority 优先级。
        virtual void EnableInterrupt(uint32_t irq, uint32_t priority) noexcept
        {
            // 中断优先级可能需要先禁用中断后才能改。不知道，反正做了没错。
            DisableInterrupt(irq);
            HAL_NVIC_SetPriority(static_cast<IRQn_Type>(irq), priority, 0);
            HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq));
        }

        /// @brief 禁止全局中断
        virtual void DisableGlobalInterrupt() noexcept
        {
            __disable_irq();
        }

        /// @brief 启用全局中断
        virtual void EnableGlobalInterrupt() noexcept
        {
            __enable_irq();
        }
    };
} // namespace hal
