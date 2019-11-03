/*
 * Sh_LED.c
 *
 *  Created on: Oct 26, 2019
 *      Author: Nick Nifontov
 */

#include "Sh.h"

void LED_Blink(GPIO_TypeDef* sh_port, uint16_t sh_pin,uint16_t sh_delay) {
	HAL_GPIO_WritePin(sh_port, sh_pin, GPIO_PIN_SET); // STAT
	osDelay(sh_delay);
	HAL_GPIO_WritePin(sh_port, sh_pin, GPIO_PIN_RESET); // STAT
}

void LED_Blink_X(GPIO_TypeDef* sh_port, uint16_t sh_pin,uint8_t sh_cnt,uint16_t sh_delay) {
	for (uint16_t i=0;i<sh_cnt;i++) {
		LED_Blink(sh_port,sh_pin,sh_delay);
		osDelay(100);
	}
}
