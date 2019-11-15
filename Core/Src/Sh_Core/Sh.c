/*
 * Sh.c
 *
 *  Created on: Oct 26, 2019
 *      Author: Nick Nifontov
 */


#include "Sh.h"

void Enable_SH_DEBUG(void) {
	__HAL_RCC_DBGMCU_CLK_ENABLE();
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_WWDG_STOP;
    DBGMCU->APB2FZ = 0xFFFFFFFF;
    DBGMCU->APB1FZ = 0xFFFFFFFF;
    DBGMCU->CR |=DBGMCU_CR_DBG_STOP;
    __HAL_DBGMCU_FREEZE_IWDG();
}

/* ==============   BOARD GLOBAL VAR BEGIN    ============== */
volatile uint16_t   aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE];

volatile uint16_t Global_Power=0;

volatile uint64_t Global_Power_Sumator=0;
volatile uint32_t Global_Power_Ind=0;

volatile uint16_t Global_AB=0;
volatile uint16_t Global_16V=0;
volatile uint16_t Global_TEMP=0;
volatile uint16_t Global_CURR=0;

volatile uint8_t Blocked_by_AB=1;

volatile uint8_t Blocked_by_Perek=1;

volatile uint8_t Blocked_by_PVD=1;

volatile uint8_t Blocked_by_LPWR=1;

volatile uint8_t Blocked_by_TEMP=1;

volatile uint8_t Blocked_by_Klapan=0;

volatile uint8_t Blocked_by_Klapan_CNT=0;

volatile uint8_t Blocked_by_150=0;

volatile uint8_t INV_STATE=0; // 0-off

volatile uint8_t KLAPAN_SIGN=0;

//volatile uint8_t ADC_FLAG_TEMP=0;
//volatile uint8_t ADC_FLAG_AB=0;
//volatile uint8_t ADC_FLAG_16V=0;
//volatile uint8_t ADC_FLAG_CUR=0;


/* ==============   ADC BEGIN    ============== */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc1)
{
	ShutDown_with_Power_Off();
	Blocked_by_150=1;
}

/*void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
	ShutDown_with_Power_Off();
    Blocked_by_Klapan=1;
}*/


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)
{
	Global_TEMP=aADCxConvertedData[2]/ADC_OVERSAMPLING;
	Global_16V=aADCxConvertedData[3]/ADC_OVERSAMPLING;
	//ADC_FLAG_TEMP=1;
	//ADC_FLAG_16V=1;
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc1)
{
	Global_AB=aADCxConvertedData[1]/ADC_OVERSAMPLING;
	Global_CURR=aADCxConvertedData[0]/ADC_OVERSAMPLING;
	//ADC_FLAG_AB=1;
	//ADC_FLAG_CUR=1;

	if (Global_CURR>=POLKA_15) {
		Global_Power_Sumator=Global_Power_Sumator+Global_CURR*Global_CURR;
		Global_Power_Ind++;
	}

	if (Global_CURR>POLKA_150) {

				Blocked_by_Klapan_CNT++;

				if (Blocked_by_Klapan_CNT>=KLAPAN_CNT) {
					ShutDown_with_Power_Off();
					Blocked_by_150=1;
				} else {
					GPIOA->BRR  = GPIO_BRR_BR_6;
					GPIOA->BSRR  = GPIO_BSRR_BS_7;
					GPIOB->BRR  = GPIO_BRR_BR_1;

					uint16_t microsec_pause=Blocked_by_Klapan_CNT*250;

					//10 000 microsec
					for (uint16_t i=0; i<microsec_pause; ++i) {
								// 1 microsec
								for (int j = 0; j < 32; ++j) {
									__asm__ __volatile__("nop\n\t":::"memory");
								}
					}

					GPIOA->BSRR  = GPIO_BSRR_BS_6;
					GPIOA->BRR  = GPIO_BRR_BR_7;

					GPIOB->BSRR  = GPIO_BSRR_BS_1;
				}

		//ShutDown_with_Power_Off();
		//Blocked_by_150=1;
	}
	/*if (Blocked_by_150==0) {
			if (Global_CURR>POLKA_105)  {
				ADC_FLAG_CUR_BLOCKED++;
			} else {
				ADC_FLAG_CUR_OK++;
			}
	} else {
		ADC_FLAG_CUR_BLOCKED=1;
		ADC_FLAG_CUR_OK=0;
	}*/
}
/* ==============   ADC END      ============== */

void HAL_PWR_PVDCallback(void)
{
	if __HAL_PWR_GET_FLAG(PWR_FLAG_PVDO) {
		Blocked_by_PVD=1;
	} else {
		Blocked_by_PVD=0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//if(GPIO_Pin== SD_Pin) {
		if (HAL_GPIO_ReadPin(SD_GPIO_Port,SD_Pin)==GPIO_PIN_RESET) {
			Blocked_by_Perek=1;
		} else {
			Blocked_by_Perek=0;
		}
	//}
}


void __attribute__((optimize("O0"))) ShutDown_with_Power_Off(void) {
	GPIOA->BRR  = GPIO_BRR_BR_6;
	GPIOA->BSRR  = GPIO_BSRR_BS_7;
	GPIOB->BRR  = GPIO_BRR_BR_1;

	/*HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_1_Pin, GPIO_PIN_RESET); // SET BLOCK 8V FLAG and block all PWMs
	HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BLOCK_POWER_GPIO_Port, BLOCK_POWER_Pin, GPIO_PIN_RESET);   // POWER OFF
	*/
}

void __attribute__((optimize("O0"))) ShutDown_with_Power_On(void) {
	/*HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_1_Pin, GPIO_PIN_RESET); // SET BLOCK 8V FLAG and block all PWMs
	HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BLOCK_POWER_GPIO_Port, BLOCK_POWER_Pin, GPIO_PIN_SET);   // POWER ON
	*/

	GPIOA->BRR  = GPIO_BRR_BR_6;
	GPIOA->BSRR  = GPIO_BSRR_BS_7;
	GPIOB->BSRR  = GPIO_BSRR_BS_1;
}

void __attribute__((optimize("O0"))) Enable_INV(void) {

	GPIOA->BRR  = GPIO_BRR_BR_6;
	GPIOA->BSRR  = GPIO_BSRR_BS_7;
	GPIOB->BSRR  = GPIO_BSRR_BS_1;
	GPIOA->BSRR  = GPIO_BSRR_BS_6;
	GPIOA->BRR  = GPIO_BRR_BR_7;


	/*HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_1_Pin, GPIO_PIN_RESET); // SET BLOCK 8V FLAG and block all PWMs
	HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BLOCK_POWER_GPIO_Port, BLOCK_POWER_Pin, GPIO_PIN_SET); // POWER ON
	HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_1_Pin, GPIO_PIN_SET); //  UNBLOCK 8V FLAG and UNBLOCK all PWMs
	HAL_GPIO_WritePin(GPIOA, BLOCK_PORT_2_Pin, GPIO_PIN_RESET);*/
}

uint8_t CheckStamp(uint32_t time_stamp, uint8_t time_base) {
	if (xTaskGetTickCount()-time_stamp>time_base*1000) {
		return 1;
	} else {
		return 0;
	}
}
