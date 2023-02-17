#include <Delay_F407G.h>
#include <RCC_Config.h>
#include <stm32f4xx.h>

void TIM6_Config(void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the Prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/

	RCC->APB1ENR |= (1<<4); // enable clock for TIM6
	/*
	TIM6->CR1 = 0; // Reset all
	TIM6->CR1 |= (0<<1); // UDIS=0; UEV ENABLED. The update event will generate.
	TIM6->CR1 |= (0<<7); // ARPE=0; ARR Auto Reload Disabled
	*/

	TIM6->PSC = 168-1; // Prescalar value (168 MHz)/168 = 1MHz ~ 1 us delay
	TIM6->ARR = 0xffff-1; // ARR value

	TIM6->CR1 |= (1<<0); // Enable timer counter
	while (!(TIM6->SR & (1<<0)));  // UIF: Update interrupt flag.. This bit is set by hardware when the registers are updated
	// Delay_ms(10);
}

void Delay_us(uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. Reset the counter
	2. Wait for the counter to reach the entered value. As each count will take 1 us,
	   the total waiting time will be the required us delay
	************************************************/
	TIM6->CNT = 0;
	while(TIM6->CNT < us);
}

void Delay_ms(uint16_t ms)
{
	for(uint16_t i=0; i<ms; i++)
		Delay_us(1000); // delay of 1 ms
}

void Delay_For(int delay)
{
	for(; delay>0; delay--)
		for(int i=0; i<=3195; i++);
}

void Delay_While(int delay)
{
	while(delay--);
}
