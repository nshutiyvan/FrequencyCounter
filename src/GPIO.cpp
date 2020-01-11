/*
 * GPIO.cpp
 *
 *  Created on: 9 Jan 2020
 *      Author: vectaa
 */

#include "GPIO.h"
#include "stm32f3xx_hal_rcc.h"

namespace es4 {

#define NUM_GPIOs (16U)

GPIO::GPIO() {
	// TODO Auto-generated constructor stub

}

GPIO::~GPIO() {
	// TODO Auto-generated destructor stub
}

void GPIO::init(GPIO_TypeDef *port, uint16_t pin,  uint32_t gpioMode, uint32_t gpioPull,  uint32_t gpioSpeed, uint8_t gpioOtype){

	/* save configured port */
	this->port = port;
	this->pin = pin;

	/* The pin index in the mode register */
	uint32_t pinIndex = 0x00U;

	/* Save the content of the GPIO registers into temp variables */
	uint32_t MODER 		= this->port->MODER,
			 OSPEEDR 	= this->port->OSPEEDR,
			 OTYPER 	= this->port->OTYPER,
			 PUPDR 		= this->port->PUPDR;

	/* ------------------------- Configure the GPIO port pins ---------------- */
	while (pinIndex < NUM_GPIOs) {

		if ((1 << pinIndex) & pin) {

			MODER &= ~(GPIO_MODER_MODER0 << (pinIndex * 2));
			MODER |= (((uint32_t) gpioMode) << (pinIndex * 2));

			/* Configure only if selected mode is output or alternate function*/
			if ((gpioMode == OUTPUT) || (gpioMode == ALTERNATE_FUNCTION)) {

				/* Speed mode configuration */
				OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinIndex * 2));
				OSPEEDR |= ((uint32_t) (gpioSpeed) << (pinIndex * 2));

				/* Output mode configuration*/
				OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t) pinIndex));
				OTYPER |= (uint16_t) (((uint16_t) gpioOtype) << ((uint16_t) pinIndex));
			}

			/* Pull-up Pull down resistor configuration*/
			PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t) pinIndex * 2));
			PUPDR |= (((uint32_t) gpioPull) << (pinIndex * 2));
		}
		pinIndex++;
	}

	this->port->MODER 	= MODER;
	this->port->OSPEEDR = OSPEEDR;
	this->port->OTYPER 	= OTYPER;
	this->port->PUPDR 	= PUPDR;

}

void GPIO::setGpioClock(FunctionalState state, uint32_t peripherial){
	if (state == ENABLE) {
		RCC->AHBENR |= peripherial;
	} else {
		RCC->AHBENR &= ~peripherial;
	}
}

void GPIO::write(int level){
	port->BSRR = (level != 0) ? pin : (uint32_t)pin << 16U;
}

int GPIO::read(){
	  return ((port->IDR & pin) != (uint32_t)GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}


void GPIO::setAlternateFunction(uint8_t af, uint8_t pin_source) {
	/* each in has a 4-bit mux valuem so 4x16=64bitsm spread over two 32bit AFR words */
	const uint32_t maskOft 		= (((uint32_t) pin_source & (uint32_t) 0x07) * 4);
	const uint32_t AF_clearMask = ~((uint32_t) 0xF << maskOft);
	const uint32_t AF_setMask 	= ((uint32_t) af << maskOft);

	port->AFR[pin_source >> 0x03] &= AF_clearMask;
	port->AFR[pin_source >> 0x03] |= AF_setMask;
}

} /* namespace es4 */
