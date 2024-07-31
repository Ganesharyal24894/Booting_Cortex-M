#include <stdint.h>

#define RAM_START                  0x20000000U
#define RAM_SIZE                   (8U * 1024U)
#define STACK_START                ((RAM_START) + (RAM_SIZE))

int main(void);

void Reset_Handler(void);
void NMI_Handler(void)                                               __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)                                         __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)                                               __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)                                            __attribute__((weak, alias("Default_Handler")));
void Systick_Handler(void)                                           __attribute__((weak, alias("Default_Handler")));
void WWDG_Handler(void)                                              __attribute__((weak, alias("Default_Handler")));
void RTC_Handler(void)                                               __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void)                                             __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void)                                               __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_Handler(void)                                           __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_Handler(void)                                           __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_Handler(void)                                          __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_Handler(void)                                     __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_Handler(void)                                   __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5Handler(void)   __attribute__((weak, alias("Default_Handler")));
void ADC_Handler(void)                                               __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_Handler(void)                               __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void)                                           __attribute__((weak, alias("Default_Handler")));
void TIM3_TIM4_Handler(void)                                         __attribute__((weak, alias("Default_Handler")));
void TIM6_Handler(void)                                              __attribute__((weak, alias("Default_Handler")));
void TIM7_Handler(void)                                              __attribute__((weak, alias("Default_Handler")));
void TIM14_Handler(void)                                             __attribute__((weak, alias("Default_Handler")));
void TIM15_Handler(void)                                             __attribute__((weak, alias("Default_Handler")));
void TIM16_Handler(void)                                             __attribute__((weak, alias("Default_Handler")));
void TIM17_Handler(void)                                             __attribute__((weak, alias("Default_Handler")));
void I2C1_Handler(void)                                              __attribute__((weak, alias("Default_Handler")));
void I2C2_I2C3_Handler(void)                                         __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void)                                              __attribute__((weak, alias("Default_Handler")));
void SPI2_SPI3_Handler(void)                                         __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void)                                            __attribute__((weak, alias("Default_Handler")));
void USART2_Handler(void)                                            __attribute__((weak, alias("Default_Handler")));
void USART3_USART4_USART5_USART6_Handler(void)                       __attribute__((weak, alias("Default_Handler")));

const uint32_t Vector_Table[] __attribute__((section(".vector_table"))) = {
    (uint32_t)STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&SVC_Handler,
    0,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&Systick_Handler,
    (uint32_t)&WWDG_Handler,
    0,
    (uint32_t)&RTC_Handler,
    (uint32_t)&FLASH_Handler,
    (uint32_t)&RCC_Handler,
    (uint32_t)&EXTI0_1_Handler,
    (uint32_t)&EXTI2_3_Handler,
    (uint32_t)&EXTI4_15_Handler,
    0,
    (uint32_t)&DMA1_Channel1_Handler,
    (uint32_t)&DMA1_Channel2_3_Handler,
    (uint32_t)&DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5Handler,
    (uint32_t)&ADC_Handler,
    (uint32_t)&TIM1_BRK_UP_TRG_COM_Handler,
    (uint32_t)&TIM1_CC_Handler,
    0,
    (uint32_t)&TIM3_TIM4_Handler,
    (uint32_t)&TIM6_Handler,
    (uint32_t)&TIM7_Handler,
    (uint32_t)&TIM14_Handler,
    (uint32_t)&TIM15_Handler,
    (uint32_t)&TIM16_Handler,
    (uint32_t)&TIM17_Handler,
    (uint32_t)&I2C1_Handler,
    (uint32_t)&I2C2_I2C3_Handler,
    (uint32_t)&SPI1_Handler,
    (uint32_t)&SPI2_SPI3_Handler,
    (uint32_t)&USART1_Handler,
    (uint32_t)&USART2_Handler,
    (uint32_t)&USART3_USART4_USART5_USART6_Handler,
    0,
    0
};

__attribute__((naked, noreturn)) void Reset_Handler(void)
{
    extern uint32_t _sdata;
    extern uint32_t _edata;
    extern uint32_t _sload_data;

    /* copy .data section into RAM */
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *Src_addr = (uint8_t *)&_sload_data;
    uint8_t *Dest_addr = (uint8_t *)&_sdata;

    for (uint32_t i = 0; i < data_size; i++)
    {
        *Dest_addr++ = *Src_addr++;
    }

    extern uint32_t _sbss;
    extern uint32_t _ebss;

    data_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    Dest_addr = (uint8_t *)&_sbss;

    /* Zeroing the .bss section */
    for (uint32_t i = 0; i < data_size; i++)
    {
        *Dest_addr++ = 0;
    }

    main();

    while (1)
    {
        // get trapped here you bitch
    }
}

void Default_Handler(void)
{
    while (1)
    {
    }
}
