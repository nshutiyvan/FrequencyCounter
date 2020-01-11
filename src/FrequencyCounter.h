/*
 * FrequencyCounter.h
 *
 *  Created on: 9 Jan 2020
 *      Author: vectaa
 */

#ifndef FREQUENCYCOUNTER_H_
#define FREQUENCYCOUNTER_H_
//#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal.h"
#include "GPIO.h"

namespace es4 {

class FrequencyCounter {
private:
		GPIO_TypeDef* port1,*gpio_timer;
		TIM_TypeDef *timer;
		GPIO gpioTimer;
		IRQn_Type irq;

		void setGpio();
		void setTimer();
		void setExti();
public:
	FrequencyCounter();
	virtual ~FrequencyCounter();
	 void setInputCapture(uint16_t polarity);

	void init();
    void start();
    void stop();
    inline int getGateValue() { return timer->CNT; } // Return curret gate time
    inline TIM_TypeDef *getTimer() { return timer; }
    double getFreqValue();
    int getPeriod();
    void setGateValue(uint32_t value) { timer->CNT = value;} // Return curret gate time
};

} /* namespace es4 */

#endif /* FREQUENCYCOUNTER_H_ */
