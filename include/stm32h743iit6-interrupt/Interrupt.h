#pragma once
#include <hal.h>

namespace hal
{
    /// @brief 静态类。提供中断相关的操作。
    class Interrupt final
    {
    private:
        Interrupt() = delete;
        Interrupt(Interrupt const &o) = delete;
        Interrupt(Interrupt const &&o) = delete;
        Interrupt &operator=(Interrupt const &value) = delete;

    public:
        /// @brief 抢占优先级组。
        enum class PreemptionPriorityGroup
        {
            /// @brief 0 位抢占优先级，4 位响应优先级。
            Group0 = NVIC_PRIORITYGROUP_0,

            /// @brief 1 位抢占优先级，3 位响应优先级。
            Group1 = NVIC_PRIORITYGROUP_1,

            /// @brief 2 位抢占优先级，2 位响应优先级。
            Group2 = NVIC_PRIORITYGROUP_2,

            /// @brief 3 位抢占优先级，1 位响应优先级。
            Group3 = NVIC_PRIORITYGROUP_3,

            /// @brief 4 位抢占优先级，0 位响应优先级。
            Group4 = NVIC_PRIORITYGROUP_4,
        };

        /// @brief 设置抢占优先级组。
        /// @param group
        static void SetPriorityGroup(PreemptionPriorityGroup group);

        /// @brief 设置中断优先级。
        /// @param irq_n 中断号的枚举
        ///
        /// @param preempt_priority 中断抢占优先级。范围 [0,15] ，数值越小优先级越高。
        /// @note 根据优先级分组，抢占优先级最多可以有 4 位，但此时就没有响应优先级的位置了。
        /// 所以 [0,15] 是理论可以设置的范围，实际有效的范围还得看设置的优先级分组。
        ///
        /// @param sub_priority 中断响应优先级。范围 [0,15] ，数值越小优先级越高。
        /// @note 根据优先级分组，响应优先级最多可以有 4 位，但此时就没有抢占优先级的位置了。
        /// 所以 [0,15] 是理论可以设置的范围，实际有效的范围还得看设置的优先级分组。
        static void SetPriority(IRQn_Type irq_n, uint32_t preempt_priority, uint32_t sub_priority)
        {
            HAL_NVIC_SetPriority(irq_n, preempt_priority, sub_priority);
        }
    };
} // namespace hal
