/*
 * Sh_LED.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Nick Nifontov
 */

#ifndef SRC_SH_CORE_SH_LED_H_
#define SRC_SH_CORE_SH_LED_H_


void LED_Blink(GPIO_TypeDef* sh_port, uint16_t sh_pin,uint16_t sh_delay);
void LED_Blink_X(GPIO_TypeDef* sh_port, uint16_t sh_pin,uint8_t sh_cnt,uint16_t sh_delay);

#endif /* SRC_SH_CORE_SH_LED_H_ */
