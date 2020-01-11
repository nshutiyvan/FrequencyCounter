/*
 * GPIO.h
 *
 *  Created on: 9 Jan 2020
 *      Author: vectaa
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f3xx_hal.h"
#include "stddef.h"

#define PUSH_PULL 0x00
#define OPEN_DRAIN 0x01
#define INPUT     ((uint32_t)0x00000000U)   /*!< Input Floating Mode                   */
#define OUTPUT       ((uint32_t)0x00000001U)   /*!< Output Push Pull Mode                 */
#define ALTERNATE_FUNCTION  ((uint32_t)0x00000002U)   /*!< Alternate Function Push Pull Mode     */
#define ANALOG      ((uint32_t)0x00000003U)   /*!< Alternate Function Open Drain Mode    */

namespace es4 {

class GPIO {
private:
	GPIO_TypeDef *port;
	uint16_t pin;
public:
	GPIO();
	void init(GPIO_TypeDef *port, uint16_t gpioPin,  uint32_t gpioMode, uint32_t gpioPull,  uint32_t gpioSpeed, uint8_t gpioOtype);
	void setGpioClock(FunctionalState state, uint32_t peripherial);
	void setAlternateFunction(uint8_t alternateFunction, uint8_t pinSource);
	void write(int level);
	int read();
	inline GPIO_TypeDef *getPort() { return port; }

	virtual ~GPIO();


};

} /* namespace es4 */

#endif /* GPIO_H_ */
