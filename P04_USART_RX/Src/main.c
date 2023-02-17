#include <stm32f4xx.h>

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART2_BAUDRATE 115200

void USART_Config(void);
static uint16_t compute_uart2_bd(uint32_t PeriphCLK,uint32_t Baudrate);
char USART_Read(void);

int main(void)
{
	USART_Config();

	while(1)
	{
		char c;
		c = USART_Read();
		if(c == 'A')
			GPIOD->ODR |= (1<<13);
		else if(c == 'B')
			GPIOD->ODR &= ~(1<<13);
	}
}

void USART_Config(void)
{
	// ENABLE GPIOA CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN;

	// SET PD13 (BUILT IN LED) AS OUTPUT PIN
	GPIOD->MODER |= (1<<26);
	GPIOD->MODER &= ~(1<<27);

	// PA2 - USART2_TX, PA3 - USART2_RX (AF7)
	// SET PINS AS ALTERNATE FUNCTION MODE
	// GPIOA->MODER &= ~(1<<4);
	// GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= ~(1<<6);
	GPIOA->MODER |= (1<<7);

	// SET THE ALTERNATE FUNCTION LOW REGISTER
	// GPIOA->AFR[0] |= (7<<8);
	// GPIOA->AFR[0] &= ~(1<<11);
	GPIOA->AFR[0] |= (7<<12);
	GPIOA->AFR[0] &= ~(1<<15);

	// ENABLE USART2 CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// SET BRR, RE, UE
	USART2->BRR = compute_uart2_bd(APB1_CLK,UART2_BAUDRATE);
	USART2->CR1 = 0x00;
	USART2->CR1 |= (1<<2); // Enable USART2 Receiver
	// USART2->CR1 |= (1<<3); // Enable USART2 Transmitter
	USART2->CR1 |= (1<<13); // Enable USART2
}

static uint16_t compute_uart2_bd(uint32_t PeriphCLK,uint32_t Baudrate)
{
	return ((PeriphCLK+(Baudrate/2U))/Baudrate);
}

char USART_Read(void)
{
    // while(!(USART2->SR & (1<<5))); // Wait for data to be received
    return USART2->DR;
}