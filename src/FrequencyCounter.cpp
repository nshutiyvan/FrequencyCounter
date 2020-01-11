/*
 * FrequencyCounter.cpp
 *
 *  Created on: 9 Jan 2020
 *      Author: vectaa
 */

#include "FrequencyCounter.h"

namespace es4 {


FrequencyCounter *freqPtr;
volatile uint32_t period;
volatile uint32_t capture_1;
volatile uint32_t capture_2;
volatile uint32_t new_capture;
volatile uint32_t previous_capture;
double frequency;

FrequencyCounter::FrequencyCounter() {
	// TODO Auto-generated constructor stub
}

FrequencyCounter::~FrequencyCounter() {
	// TODO Auto-generated destructor stub
}

void FrequencyCounter::init() {

	setGpio();
	setExti();
	setTimer();
}

void FrequencyCounter::setGpio() {
	// settings for button 1
	port1 = GPIOC;
	port1->MODER = (port1->MODER & ~GPIO_MODER_MODER13)
			| (0b00 << GPIO_MODER_MODER13_Pos);       // set pin PA0 to input.

	port1->PUPDR = (port1->PUPDR & ~GPIO_PUPDR_PUPDR13)
			| (0b01 << GPIO_PUPDR_PUPDR13_Pos); // set pin PA0 pull-up/pull-down to pull-up

	// settings for button 2
}

void FrequencyCounter::setTimer() {

	// Enable timer 2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	uint8_t timer2_af = ((uint8_t) 0x01);
	uint8_t pin_source = ((uint8_t) 0x00);
	const uint32_t counter_mode 	= 0x00000000U;
	const uint32_t clock_division 	= 0x00000000U;
	uint32_t tim_polarity = 0x00000000U;

	gpioTimer.setGpioClock(ENABLE, RCC_AHBENR_GPIOAEN);
	gpioTimer.init(GPIOA, GPIO_PIN_0, ALTERNATE_FUNCTION, GPIO_NOPULL,
			GPIO_SPEED_FREQ_HIGH, PUSH_PULL);
	gpioTimer.setAlternateFunction(timer2_af, pin_source);

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	uint32_t periphClockFreq = 0;
	//
	//	// Get clock configuration
	//	// Note: PclkFreq contains here the Latency (not used after)
	HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &periphClockFreq);

	timer->PSC = 47999; //prescalerFreq;//48000;//47999;															   // Set prescaler so timer clock will be 1 MHz.
	timer->ARR = 1000 - 1;	// timer auto reload value (20000 ticks per second)
	timer->CR1 |= counter_mode;
	timer->CR1 |= clock_division;	//	timer->CR1  |= 0x00000000U;
	timer->EGR = TIM_EGR_UG;
	uint32_t tmpSMCR = 0U;
	/* Reset the SMS, TS, ECE, ETPS and ETRF bits */
	tmpSMCR = timer->SMCR;
	tmpSMCR &= ~(TIM_SMCR_SMS | TIM_SMCR_TS);
	tmpSMCR &= ~(TIM_SMCR_ETF | TIM_SMCR_ETPS | TIM_SMCR_ECE | TIM_SMCR_ETP);
	timer->SMCR = tmpSMCR;
	/* Disable slave mode to clock the prescaler directly with the internal clock */
	timer->SMCR &= ~TIM_SMCR_SMS;

	/* Reset the MMS Bits */
	timer->CR2 &= ~TIM_CR2_MMS;
	/* Select the TRGO source */
	timer->CR2 |= TIM_TRGO_RESET;

	/* Reset the MSM Bit */
	timer->SMCR &= ~TIM_SMCR_MSM;
	/* Set or Reset the MSM Bit */
	timer->SMCR |= TIM_MASTERSLAVEMODE_DISABLE;

	/* TI1 Configuration */
	setInputCapture (tim_polarity);

	NVIC_EnableIRQ(irq);// Enable interrupt vector TIM1_CC_IRQn so interrupt handler TIM1_CC_IRQHandler() will be called.

}

void FrequencyCounter::setExti() {
	//it is on place 4
	SYSCFG->EXTICR[0] = (SYSCFG->EXTICR[0] & ~SYSCFG_EXTICR1_EXTI0_PC)
			| (0b0010 << SYSCFG_EXTICR1_EXTI0_Pos); // pin PC0 to interrupt  EXTI0

	EXTI->FTSR = EXTI_FTSR_TR0;
	EXTI->IMR = EXTI_IMR_MR0;
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void FrequencyCounter::setInputCapture(uint16_t polarity) {

	uint16_t prescaler = 0;
	uint16_t filter = 0xf;

	timer->CCER &= (uint16_t) ~TIM_CCER_CC1E;

	/* Select the Input and set the filter */
	timer->CCMR1 &= ((uint16_t) ~TIM_CCMR1_CC1S) & ((uint16_t) ~TIM_CCMR1_IC1F);
	timer->CCMR1 |= (uint16_t) (TIM_CCMR1_CC1S_0 | (uint16_t) (filter << (uint16_t) 4));

	/* Select the Polarity and set the CC1E Bit */
	timer->CCER &= (uint16_t) ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	timer->CCER |= (uint16_t) (polarity | (uint16_t) TIM_CCER_CC1E);

	/* Set the Input Capture Prescaler value */
	/* Reset the IC1PSC Bits */
	timer->CCMR1 &= (uint16_t) ~TIM_CCMR1_IC1PSC;

	/* Set the IC1PSC value */
	timer->CCMR1 |= prescaler;
}

void FrequencyCounter::start() {
	/* Enable the TIM Update interrupt */
	timer->DIER |= TIM_DIER_CC1IE | TIM_DIER_UIE; // Capture/Compare 1 interrupt enable.

	/* Enable the Peripheral */
	timer->CR1 |= TIM_CR1_CEN;
}

void FrequencyCounter::stop() {
	/* Enable the TIM Update interrupt */
	timer->DIER &= ~TIM_DIER_CC1IE & ~TIM_DIER_UIE; // Capture/Compare 1 interrupt enable.

	/* Enable the Peripheral */
	timer->CR1 &= ~TIM_CR1_CEN;
}

double FrequencyCounter::getFreqValue() {
	/* convert period from milliseconds to seconds */
	double time = period / 1000.0;
	/* calculate frequency in hertz */
	frequency = 1 / time;

	return frequency;
}

int FrequencyCounter::getPeriod() {
	return (int) period;
}


extern "C" {

int getTimerStatusIT(uint16_t interruptFlag) {

	TIM_TypeDef *timer = freqPtr->getTimer();
	if (((timer->SR & interruptFlag) != (uint16_t) RESET)
			&& ((timer->DIER & interruptFlag) != (uint16_t) RESET)) {
		return SET;
	}
	return RESET;
}

void TIM2_IRQHandler(void) {
	TIM_TypeDef *timer = freqPtr->getTimer();

	/* check the interrupt event */
	if ((timer->SR & (TIM_FLAG_CC1)) == TIM_FLAG_CC1) {
		/* Check the interrupt source */
		if ((timer->DIER & (TIM_IT_CC1)) == (TIM_IT_CC1)) {
			/* Clear all pending bits */
			timer->SR = ~TIM_DIER_CC1IE; // clear pending bit
			timer->SR = ~TIM_DIER_UIE;
			timer->SR = ~TIM_IT_CC1;

			/* Input capture event */
			if ((timer->CCMR1 & TIM_CCMR1_CC1S) != 0x00U) {
				/* copy captured value saved in the CCR1 register */
				new_capture = timer->CCR1;

				period = new_capture - previous_capture;
				previous_capture = new_capture;

			} else {
				printf("Error: not an input capture event\n\r");
			}
		}
	}
}

} /* extern "C"  */

} /* namespace es4 */
