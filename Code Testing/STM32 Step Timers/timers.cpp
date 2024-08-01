// timers.cpp

#include "timers.h"

void initTim4Ch1()
{
	// 1-Enable GPIOB and peropheral clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	// 2-Set GPIO as AF and set AF to TIM4
	GPIOB->MODER &= ~(0b11 << 12); // Clear bits 12 and 13
	GPIOB->MODER |= (0b10 << 12); // Set PB6 to AF (10)
	GPIOB->AFR[0] &= ~(0b1111 << 24); // Clear bits 24-27
	GPIOB->AFR[0] |= (0b0010 << 24); // Set bits 24-27 to 0b0010 (TIM4)
	
	// 3-Set timer as output capture
	TIM4->CCMR1 &= ~(0b11 << 0); // Set CC1S to 00 (OC mode)
	TIM4->CCMR1 &= ~(0b111 << 4); // Clear OC1M bits
	TIM4->CCMR1 |= (0b011 << 4); // Set OC1M to toggle mode (011)	
	
	TIM4->CNT = 0; // Reset counter
	TIM4->CCER |= (1 << 0); // Enable capture/compare output for channel 1 (CC1E)
}

void setTim4Frequency(uint16_t psc, uint16_t arr)
{
	TIM4->CR1 &= ~(1 << 0); // Stop timer
	TIM4->CNT = 0; // Clear timer

	TIM4->PSC = psc-1;
	TIM4->ARR = arr-1;  
	TIM4->CCR1 = arr/2 - 1;
}

void startTim4Ch1()
{
	TIM4->CNT = 0;
	TIM4->CR1 |= (1 << 0);
}

void stopTim4Ch1()
{
	TIM4->CR1 &= ~(1 << 0);
	TIM4->CNT = 0;
}



