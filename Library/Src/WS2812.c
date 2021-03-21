/*
 * WS2812.c
 *
 *  Created on: 21 mar. 2021
 *      Author: Mikel
 */


//#include "stm32L4xx_hal.h"
#include "WS2812.h"
#include "stdio.h"
#include <math.h>
#include "string.h"

//Handle variable
static TIM_HandleTypeDef wsTimmer;

//Led array pin congifguration
static GPIO_TypeDef	*wsPort;
static uint16_t wsPin;

//Led Format
struct led{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}LED;

//Leds manipulation
uint8_t ledsCount;


void WS2812_init(TIM_HandleTypeDef htim, GPIO_TypeDef *GPIO_Port, uint16_t wsDataPin, uint8_t ledsCount){

	//Copy TIM handle variable
	memcpy(&wsTimmer, &htim, sizeof(htim));
	wsPort = GPIO_Port;
	wsPin = wsDataPin;

}


void printManyLeds(uint8_t redD,uint8_t greenD,uint8_t blueD, uint8_t count){
	uint8_t i = 0;
	for(i=0;i<count;i++){
		printLed(redD, greenD, blueD);
	}
}
void printLed(uint8_t redD,uint8_t greenD,uint8_t blueD){
	sendByte(greenD);
	sendByte(redD);
	sendByte(blueD);
}
//Private purpose libraries;
void sendByte(uint8_t data){//Mirar el orden de transmision de datos 7 6 5 4 3 2 1 o 1 2 3 4 5 6 7
	uint8_t bit = 0x80;//0b10000000
	for(uint8_t i = 0; i< sizeof(uint8_t);i++){//Recorrer todo el byte
		if(data&bit)
			pulseOne();
		else
			pulseZero();
		bit=bit>>1;
	}

}

void pulseZero(){
	HAL_GPIO_WritePin(wsPort, wsPin, GPIO_PIN_SET);
	delay(WS2812_PulseZeroH);
	HAL_GPIO_WritePin(wsPort, wsPin, GPIO_PIN_RESET);
	delay(WS2812_PulseZeroL);
}
void pulseOne(){
	HAL_GPIO_WritePin(wsPort, wsPin, GPIO_PIN_SET);
	delay(WS2812_PulseOneH);
	HAL_GPIO_WritePin(wsPort, wsPin, GPIO_PIN_RESET);
	delay(WS2812_PulseOneL);
}

void delay(uint16_t delay){ //Configure to have 1us timer
	__HAL_TIM_SET_COUNTER(&wsTimmer,0);
	while(__HAL_TIM_GET_COUNTER(&wsTimmer)< delay); //Maximum 65535 (uint16_t)
}
