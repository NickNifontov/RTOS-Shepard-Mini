/*
 * Sh_Cfg.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Nick Nifontov
 */

#ifndef SRC_SH_CORE_SH_CFG_H_
#define SRC_SH_CORE_SH_CFG_H_

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
#define SD_Pin GPIO_PIN_14
#define SD_GPIO_Port GPIOC
#define SD_EXTI_IRQn EXTI4_15_IRQn
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOC
#define CURRENT_Pin GPIO_PIN_0
#define CURRENT_GPIO_Port GPIOA
#define AB_Pin GPIO_PIN_1
#define AB_GPIO_Port GPIOA
#define TEMP_ADC_Pin GPIO_PIN_2
#define TEMP_ADC_GPIO_Port GPIOA
#define KLAPAN_COMP_Pin GPIO_PIN_3
#define KLAPAN_COMP_GPIO_Port GPIOA
#define VCC16V_Pin GPIO_PIN_4
#define VCC16V_GPIO_Port GPIOA
#define Cooler_Pin GPIO_PIN_5
#define Cooler_GPIO_Port GPIOA
#define BLOCK_PORT_1_Pin GPIO_PIN_6
#define BLOCK_PORT_1_GPIO_Port GPIOA
#define BLOCK_PORT_2_Pin GPIO_PIN_7
#define BLOCK_PORT_2_GPIO_Port GPIOA
#define BLOCK_POWER_Pin GPIO_PIN_1
#define BLOCK_POWER_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_9
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_10
#define LED_2_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */


#endif /* SRC_SH_CORE_SH_CFG_H_ */
