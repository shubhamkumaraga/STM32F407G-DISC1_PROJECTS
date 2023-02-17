#include <stm32f4xx.h>
#include <RCC_Config.h>
#include <Delay_F407G.h>

void GPIO_Config(void)
{
	// ENABLE GIPOA CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// SET PD13 (BUILT IN LED) AS OUTPUT MODE
	GPIOD->MODER |= (1<<26);
	GPIOD->MODER &= ~(1<<27);

	// SET PA0 (USER BUTTON) AS INPUT MODE
	GPIOA->MODER &= ~((1<<0) | (1<<1));

	// SET OUTPUT PUSH-PULL
	GPIOD->OTYPER &= ~(1<<13);
	GPIOA->OTYPER &= ~(1<<0);

	// SET OUTPUT SPEED AS HIGH
	GPIOD->OSPEEDR |= (2<<26);
	GPIOA->OSPEEDR |= (2<<0);
}

int main(void)
{
	SysClockConfig();
	GPIO_Config();

	while(1)
	{
		if(GPIOA->IDR & (1<<0))
		{
			GPIOD->ODR |= (1<<13);
		}
		else
		{
			GPIOD->ODR &= ~(1<<13);
		}
	}
}
