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

#include "stm32l031xx.h"

#include "stm32l0xx_ll_adc.h"
//#include "stm32l0xx_ll_comp.h"


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

#define BUZZER_OPORA 550 // 1.0V - 0.2V
#define BUZZER_OPORA_MIN ((uint16_t) (BUZZER_OPORA*0.995))
#define BUZZER_OPORA_MAX ((uint16_t) (BUZZER_OPORA*1.005))

#define AB_LOW ((uint16_t) (BUZZER_OPORA*0.90))
#define AB_ROLLBACK ((uint16_t) (BUZZER_OPORA*1.1))
#define AB_MAX ((uint16_t) (BUZZER_OPORA*1.29))
#define AB_COLDRUN ((uint16_t) (BUZZER_OPORA*1.05))
#define AB_COLDRUN_FROM_MAX ((uint16_t) (AB_MAX*0.95))

#define TEMP_MAX 2580 // celsium
#define TEMP_COLRSTART 2200
#define TEMP_ROLLBACK 2100

extern volatile uint16_t Global_Power;

extern volatile uint64_t Global_Power_Sumator;
extern volatile uint32_t Global_Power_Ind;

extern volatile uint16_t Global_AB;
extern volatile uint16_t Global_16V;
extern volatile uint16_t Global_TEMP;
extern volatile uint16_t Global_CURR;

extern volatile uint8_t Blocked_by_AB;

extern volatile uint8_t Blocked_by_Perek;

extern volatile uint8_t Blocked_by_PVD;

extern volatile uint8_t Blocked_by_TEMP;

extern volatile uint8_t Blocked_by_Klapan;
extern volatile uint8_t Blocked_by_150;

extern volatile uint8_t Blocked_by_Klapan_CNT;

extern volatile uint8_t INV_STATE;

extern volatile uint8_t KLAPAN_SIGN;

//extern volatile uint8_t ADC_FLAG_TEMP;
//extern volatile uint8_t ADC_FLAG_AB;
//extern volatile uint8_t ADC_FLAG_16V;
//extern volatile uint8_t ADC_FLAG_CUR;

#define KLAPAN_CNT 4

#define ADC_POLKA105_DELAY 2
#define POLKA_LEVEL (uint16_t) (560)
#define POLKA_200 ((uint16_t)  (POLKA_LEVEL*2.0))
#define POLKA_150 ((uint16_t)  (POLKA_LEVEL*1.5))
#define POLKA_95 ((uint16_t)  (POLKA_LEVEL*0.95))
#define POLKA_105 ((uint16_t)  (POLKA_LEVEL*1.05))
#define POLKA_25 ((uint16_t)  (POLKA_LEVEL*0.25))
#define POLKA_50 ((uint16_t)  (POLKA_LEVEL*0.5))
#define POLKA_75 ((uint16_t)  (POLKA_LEVEL*0.75))
#define POLKA_15 ((uint16_t)  (POLKA_LEVEL*0.15))


#define LPWR_MIN  1100
#define LPWR_MAX  2100
extern volatile uint8_t Blocked_by_LPWR;

#define BUZZER_MAX_LENGTH 10 //sec
#define AB_MAX_LENGTH 10 //sec
#define COOLER_MAX_LENGTH 10 //sec
#define TEMP_DELAY_LENGTH 10 //sec
#define TEMP_ROLLBACK_DELAY_LENGTH 10 //sec
#define LPWR_DELAY_LENGTH 2 //sec
#define RESTART_MAX_LENGTH 10 //sec

void ShutDown_with_Power_Off(void);
void ShutDown_with_Power_On(void);
void Enable_INV(void);

#define  COOLER_PRESCALER	(uint32_t)(0)  /* PRESCALER Value  */
#define  COOLER_PERIOD_VALUE       (uint32_t)(31999)  /* Period Value  */
#define  PULSE100_VALUE       (uint32_t)(COOLER_PERIOD_VALUE)        /* 100% */
#define  PULSE70_VALUE       (uint32_t)(COOLER_PERIOD_VALUE*70/100)        /* 70% */
#define  PULSE40_VALUE       (uint32_t)(COOLER_PERIOD_VALUE*40/100) /* 40%  */
#define  PULSE20_VALUE       (uint32_t)(COOLER_PERIOD_VALUE*20/100)        /* 20% */

uint8_t CheckStamp(uint32_t time_stamp, uint8_t time_base);

/* ==============   BOARD GLOBAL VAR END      ============== */


#endif /* SRC_SH_CORE_SH_H_ */
