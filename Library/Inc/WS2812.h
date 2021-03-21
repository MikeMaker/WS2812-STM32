/*
 * WS2812.h
 *
 *  Created on: 21 mar. 2021
 *      Author: Mikel
 */

#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#define WS2812_PulseZeroH	400//400n
#define WS2812_PulseZeroL	800//800n

#define WS2812_PulseOneH	700//700n
#define WS2812_PulseOneL	600//600n
#define WS2812_PulseReset	60000//>50u


void WS2812_init(TIM_HandleTypeDef htim, GPIO_TypeDef *GPIO_Port, uint16_t wsDataPin, uint8_t ledsCount);
void printLed(uint8_t redD,uint8_t greenD,uint8_t blueD);
//Private purpose libraries;
void sendByte(uint8_t data);
void pulseZero();
void pulseOne();
void delay(uint16_t delay);

#endif /* INC_WS2812_H_ */
