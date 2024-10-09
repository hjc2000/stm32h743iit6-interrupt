#pragma once
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <Exti.h>
#include <hal.h>

namespace hal
{
    /// @brief 中断开关
    class InterruptSwitch final :
        public bsp::IInterruptSwitch
    {
    private:
        InterruptSwitch() = default;

    public:
        static InterruptSwitch &Instance();

        /// @brief 禁用指定中断号的中断
        /// @param irq
        void DisableInterrupt(uint32_t irq) noexcept override
        {
            HAL_NVIC_DisableIRQ(static_cast<IRQn_Type>(irq));
        }

        /// @brief 使能指定中断号的中断。不设置优先级，使用默认优先级。
        /// @param irq
        void EnableInterrupt(uint32_t irq) noexcept override
        {
            /* 硬件中断控制器中每一个中断都天生自带一个默认的优先级，并且这种优先级一般是由中断号的大小
             * 自然而然地就决定了。所以这里只要使能中断就行了，使用硬件中断控制器自带的优先级。
             */
            HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq));
        }

        /// @brief 使能指定中断号的中断，并且设置优先级。
        /// @param irq 中断号。
        /// @param priority 优先级。
        void EnableInterrupt(uint32_t irq, uint32_t priority) noexcept override
        {
            // 中断优先级可能需要先禁用中断后才能改。不知道，反正做了没错。
            DisableInterrupt(irq);
            HAL_NVIC_SetPriority(static_cast<IRQn_Type>(irq), priority, 0);
            HAL_NVIC_EnableIRQ(static_cast<IRQn_Type>(irq));
        }

        /// @brief 禁用全局中断
        void DisableGlobalInterrupt() noexcept override
        {
            __disable_irq();
        }

        /// @brief 启用全局中断
        void EnableGlobalInterrupt() noexcept override
        {
            __enable_irq();
        }
    };
} // namespace hal
