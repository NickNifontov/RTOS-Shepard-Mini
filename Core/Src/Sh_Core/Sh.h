/*
 * Sh.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Nick Nifontov
 */

#ifndef SRC_SH_CORE_SH_H_
#define SRC_SH_CORE_SH_H_

#include "stm32l0xx_hal.h"
#include "cmsis_os.h"
#include "math.h"

#include "adc.h"
#include "comp.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "gpio.h"
#include "sys.h"


#include "Sh_Cfg.h"
#include "Sh_LED.h"

void Enable_SH_DEBUG(void);


/* ==============   BOARD GLOBAL VAR BEGIN    ============== */

/* Definitions of data related to this example */
/* Definition of ADCx conversions data table size */
#define ADC_CONVERTED_DATA_BUFFER_SIZE   ((uint32_t)  4)   /* Size of array aADCxConvertedData[] */

#define ADC_OVERSAMPLING 16

/* Variable containing ADC conversions data */
extern volatile uint16_t   aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE];

#define BUZZER_OPORA 1620 // 1.0V
#define BUZZER_OPORA_MIN ((uint16_t) (BUZZER_OPORA*0.995))
#define BUZZER_OPORA_MAX ((uint16_t) (BUZZER_OPORA*1.005))

#define AB_LOW ((uint16_t) (BUZZER_OPORA*0.90))
#define AB_ROLLBACK ((uint16_t) (BUZZER_OPORA*1.1))
#define AB_MAX ((uint16_t) (BUZZER_OPORA*1.29))
#define AB_COLDRUN ((uint16_t) (BUZZER_OPORA*1.05))
#define AB_COLDRUN_FROM_MAX ((uint16_t) (AB_MAX*0.95))

#define TEMP_MAX 1800 // celsium
#define TEMP_COLRSTART 1340
#define TEMP_ROLLBACK 1290

extern volatile uint16_t Global_AB;
extern volatile uint16_t Global_16V;
extern volatile uint16_t Global_TEMP;

extern volatile uint8_t Blocked_by_AB;

extern volatile uint8_t Blocked_by_Perek;

extern volatile uint8_t Blocked_by_PVD;

extern volatile uint8_t Blocked_by_TEMP;


#define LPWR_MIN  1100
#define LPWR_MAX  2100
extern volatile uint8_t Blocked_by_LPWR;

#define BUZZER_MAX_LENGTH 10 //sec
#define AB_MAX_LENGTH 10 //sec
#define TEMP_DELAY_LENGTH 10 //sec
#define LPWR_DELAY_LENGTH 1 //sec

void ShutDown_with_Power_Off(void);
void ShutDown_with_Power_On(void);
void Enable_INV(void);

uint8_t CheckStamp(uint32_t time_stamp, uint8_t time_base);

/* ==============   BOARD GLOBAL VAR END      ============== */


#endif /* SRC_SH_CORE_SH_H_ */
