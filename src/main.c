#include <stdint.h>

/*

 This is for configuring simple LED blinking on PORTB-3(PB3)

 */

#define RCC_BASE 0x40021000
#define IOPENR_OFFSET 0x34

#define GPIOB_BASE 0x50000400
#define GPIOA_BASE 0x50000000
#define MODER_OFFSET 0x00
#define ODR_OFFSET 0x14

uint32_t delay = 100000;

__attribute__((naked, noreturn)) int main(void)
{

	*((uint32_t *)(RCC_BASE + IOPENR_OFFSET)) |= (1U << 1) | (1U << 0); // enabling port A & B

	*((uint32_t *)(GPIOB_BASE + MODER_OFFSET)) |= (1U << 6);  // setting it as Output PB3
	*((uint32_t *)(GPIOB_BASE + MODER_OFFSET)) &= ~(1U << 7); // setting it as Output PB3

	*((uint32_t *)(GPIOA_BASE + MODER_OFFSET)) |= (1U << 6);  // setting it as Output PA3
	*((uint32_t *)(GPIOA_BASE + MODER_OFFSET)) &= ~(1U << 7); // setting it as Output PA3
	while (1)
	{
		*((uint32_t *)(GPIOB_BASE + ODR_OFFSET)) ^= (1U << 3); // toggling Output
		*((uint32_t *)(GPIOA_BASE + ODR_OFFSET)) ^= (1U << 3); // toggling Output
		for (uint32_t k = 0; k < delay; k++)
		{
			asm("nop");
		}
		// if (delay >= 1000000)
		// {
		// 	delay = 100000;
		// }
		// else
		// {
		// 	delay += 100000;
		// }
	}
}
