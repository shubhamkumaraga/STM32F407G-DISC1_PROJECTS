#include <stm32f4xx.h>

void GPIO_Config(void)
{
	// ENABLE GIPOA CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	// SET PD13 (BUILT IN LED) AS OUTPUT MODE
	GPIOD->MODER |= (1<<26);
	GPIOD->MODER &= ~(1<<27);
	// SET OUTPUT PUSH-PULL
	GPIOD->OTYPER &= ~(1<<13);
	// SET OUTPUT SPEED AS HIGH
	GPIOD->OSPEEDR |= (2<<26);
}

void Delay(int delay)
{
	for(; delay>0; delay--)
		for(int i=0; i<=3195; i++);
}

int main(void)
{
	GPIO_Config();

	while(1)
	{
		GPIOD->ODR |= (1<<13);
		Delay(100);
		GPIOD->ODR &= ~(1<<13);
		Delay(100);
	}
}
