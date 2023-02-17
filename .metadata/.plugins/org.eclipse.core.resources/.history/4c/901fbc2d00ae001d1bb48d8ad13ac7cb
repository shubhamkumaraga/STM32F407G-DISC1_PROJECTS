#include <Delay_F407G.h>
#include <RCC_Config.h>
#include <stm32f4xx.h>

void SysClockConfig(void)
{
	/* STEPS FOLLOWED
	1. Enable HSE and wait for the HSE to become ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY related settings
	4. Configure the PRESCALERS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to set
	*/

	#define PLL_M 8
	#define PLL_N 336
	#define PLL_P 0 // PLLP = 2
	#define PLL_Q 7 // PLLQ = 7

	// Step 1
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	// Delay_ms(10);

	// Step 2
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;

	// Step 3
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	// Step 4
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // AHB PRESCALER = 1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // APB1 PRESCALER = 4
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // APB2 PRESCALER = 2

	// Step 5
	RCC->PLLCFGR |= (PLL_M<<0) | (PLL_N<<6) | (PLL_P<<16) | (PLL_Q<<24) | RCC_PLLCFGR_PLLSRC_HSE;

	// Step 6
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	// Delay_ms(10);

	// Step 7
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	// Delay_ms(10);
}
