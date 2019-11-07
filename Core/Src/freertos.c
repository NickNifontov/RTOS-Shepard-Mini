/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "Sh.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Loop_TaskHandle;
osThreadId LED_TaskHandle;
osThreadId Buzzer_TaskHandle;
osThreadId Cooler_TaskHandle;
osThreadId AB_TaskHandle;
osThreadId TEMP_TaskHandle;
osThreadId LowPWR_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartLoop_Task(void const * argument);
void StartLED_Task(void const * argument);
void StartBuzzer_Task(void const * argument);
void StartCooler_Task(void const * argument);
void StartAB_Task(void const * argument);
void StartTEMP_Task(void const * argument);
void StartLowPWR_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Loop_Task */
  osThreadDef(Loop_Task, StartLoop_Task, osPriorityNormal, 0, 128);
  Loop_TaskHandle = osThreadCreate(osThread(Loop_Task), NULL);

  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, StartLED_Task, osPriorityBelowNormal, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of Buzzer_Task */
  osThreadDef(Buzzer_Task, StartBuzzer_Task, osPriorityBelowNormal, 0, 128);
  Buzzer_TaskHandle = osThreadCreate(osThread(Buzzer_Task), NULL);

  /* definition and creation of Cooler_Task */
  osThreadDef(Cooler_Task, StartCooler_Task, osPriorityBelowNormal, 0, 128);
  Cooler_TaskHandle = osThreadCreate(osThread(Cooler_Task), NULL);

  /* definition and creation of AB_Task */
  osThreadDef(AB_Task, StartAB_Task, osPriorityBelowNormal, 0, 128);
  AB_TaskHandle = osThreadCreate(osThread(AB_Task), NULL);

  /* definition and creation of TEMP_Task */
  osThreadDef(TEMP_Task, StartTEMP_Task, osPriorityBelowNormal, 0, 128);
  TEMP_TaskHandle = osThreadCreate(osThread(TEMP_Task), NULL);

  /* definition and creation of LowPWR_Task */
  osThreadDef(LowPWR_Task, StartLowPWR_Task, osPriorityBelowNormal, 0, 128);
  LowPWR_TaskHandle = osThreadCreate(osThread(LowPWR_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartLoop_Task */
/**
  * @brief  Function implementing the Loop_Task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartLoop_Task */
void StartLoop_Task(void const * argument)
{
  /* USER CODE BEGIN StartLoop_Task */
  /* Infinite loop */

  ShutDown_with_Power_Off();

  /* ###  - Start conversion in DMA mode ################################# */
  HAL_ADC_Start_DMA(&hadc,(uint32_t *)aADCxConvertedData,ADC_CONVERTED_DATA_BUFFER_SIZE);

  HAL_GPIO_EXTI_Callback(SD_Pin);

  for(;;)
  {
	if ((Blocked_by_AB==0) && (Blocked_by_Perek==0) && (Blocked_by_PVD==0) && (Blocked_by_TEMP==0)) {
		Enable_INV();
	} else {
		ShutDown_with_Power_Off();
	}
	IWDG_Reset();
    osDelay(1);
  }
  /* USER CODE END StartLoop_Task */
}

/* USER CODE BEGIN Header_StartLED_Task */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED_Task */

extern volatile uint8_t Blocked_by_AB;

extern volatile uint8_t Blocked_by_Perek;

extern volatile uint8_t Blocked_by_PVD;


void StartLED_Task(void const * argument)
{
  /* USER CODE BEGIN StartLED_Task */
  /* Infinite loop */
  for(;;)
  {
	if ((Blocked_by_AB==1) || (Blocked_by_LPWR==1) || (Blocked_by_PVD==1) || (Blocked_by_TEMP==1)) {
		LED_Blink(LED_1_GPIO_Port,LED_1_Pin,10);
		osDelay(100);
	} else {
			if (Blocked_by_Perek==1) {
				LED_Blink(LED_1_GPIO_Port,LED_1_Pin,10);
			} else {
				LED_Blink_X(LED_1_GPIO_Port,LED_1_Pin,3,10);
			}
			osDelay(1000);
	}
  }
  /* USER CODE END StartLED_Task */
}

/* USER CODE BEGIN Header_StartBuzzer_Task */
/**
* @brief Function implementing the Buzzer_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBuzzer_Task */
void StartBuzzer_Task(void const * argument)
{
  /* USER CODE BEGIN StartBuzzer_Task */
  /* Infinite loop */

  uint32_t buzzer_stamp=xTaskGetTickCount();

  while ((Global_AB<AB_COLDRUN) && (Blocked_by_Perek==0))  {
	  if (xTaskGetTickCount()-buzzer_stamp<=BUZZER_MAX_LENGTH*1000) {
		  LED_Blink(BUZZER_GPIO_Port,BUZZER_Pin,1);
	  }
	  osDelay(3000);
  }

  LED_Blink(BUZZER_GPIO_Port,BUZZER_Pin,100);

  buzzer_stamp=0;

  for(;;)
  {
			if (  ((Blocked_by_Perek==0) && ((Global_AB>=AB_LOW) && ((Global_AB<=BUZZER_OPORA_MAX) || (Global_AB>=AB_MAX)) ) )
					|| ((Blocked_by_Perek==1) &&  (Global_AB>=AB_MAX) )
					|| (Blocked_by_TEMP==1) ) {
				if (buzzer_stamp==0) {
					buzzer_stamp=xTaskGetTickCount();
				}
				if (xTaskGetTickCount()-buzzer_stamp<=BUZZER_MAX_LENGTH*1000) {
					LED_Blink_X(BUZZER_GPIO_Port,BUZZER_Pin,3,300);
				}
				osDelay(2500);
			}
			if ((buzzer_stamp!=0) && (Global_AB>=AB_COLDRUN) &&  (Global_AB<AB_COLDRUN_FROM_MAX)) {
				LED_Blink_X(BUZZER_GPIO_Port,BUZZER_Pin,6,100);
				buzzer_stamp=0;
			}

    osDelay(1);

  }
  /* USER CODE END StartBuzzer_Task */
}

/* USER CODE BEGIN Header_StartCooler_Task */
/**
* @brief Function implementing the Cooler_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCooler_Task */
void StartCooler_Task(void const * argument)
{
  /* USER CODE BEGIN StartCooler_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartCooler_Task */
}

/* USER CODE BEGIN Header_StartAB_Task */
/**
* @brief Function implementing the AB_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAB_Task */
void StartAB_Task(void const * argument)
{
  /* USER CODE BEGIN StartAB_Task */
  /* Infinite loop */
	while ((Global_AB<AB_COLDRUN) && (Blocked_by_Perek==0)) {
		  Blocked_by_AB=1;
		  osDelay(3000);
	  }

  uint32_t ab_stamp=0;

  if (Global_AB>AB_LOW) {
	  Blocked_by_AB=0;
  } else {
	  Blocked_by_AB=1;
  }

  for(;;)
  {
	if ( (Blocked_by_AB==0) && ((Global_AB<=AB_LOW)  || (Global_AB>=AB_MAX) ) ) {
		Blocked_by_AB=1;
		LED_Blink_X(BUZZER_GPIO_Port,BUZZER_Pin,4,100);
		osDelay(3000);
	}
	if ( (Blocked_by_AB==1) && (Global_AB>=AB_ROLLBACK) &&   (Global_AB<=AB_COLDRUN_FROM_MAX) ) {
		if (ab_stamp==0) {
			ab_stamp=xTaskGetTickCount();
		}
		if ((xTaskGetTickCount()-ab_stamp>AB_MAX_LENGTH*1000) || (Blocked_by_Perek==1)) {
			 Blocked_by_AB=0;
			 ab_stamp=0;
			 LED_Blink_X(BUZZER_GPIO_Port,BUZZER_Pin,4,100);
		}
	} else {
		ab_stamp=0;
	}

    osDelay(1);
  }
  /* USER CODE END StartAB_Task */
}

/* USER CODE BEGIN Header_StartTEMP_Task */
/**
* @brief Function implementing the TEMP_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTEMP_Task */
void StartTEMP_Task(void const * argument)
{
  /* USER CODE BEGIN StartTEMP_Task */
  /* Infinite loop */
	while (Global_TEMP>=TEMP_COLRSTART) {
		  Blocked_by_TEMP=1;
		  osDelay(3000);
	  }
	Blocked_by_TEMP=0;
	uint32_t temp_stamp=0;
  for(;;)
  {
	    if (Global_TEMP<TEMP_MAX) {
		  if ((Blocked_by_TEMP==1) && (Global_TEMP<=TEMP_ROLLBACK)) {
			  if (temp_stamp==0) {
				  temp_stamp=xTaskGetTickCount();
			  }
			  if (xTaskGetTickCount()-temp_stamp>TEMP_DELAY_LENGTH*1000) {
						 Blocked_by_TEMP=0;
						 temp_stamp=0;
			  }
		  } else {
			  Blocked_by_TEMP=0;
		  }
	    } else {
	  	  Blocked_by_TEMP=1;
	    }
	    osDelay(1000);
  }
  /* USER CODE END StartTEMP_Task */
}

/* USER CODE BEGIN Header_StartLowPWR_Task */
/**
* @brief Function implementing the LowPWR_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLowPWR_Task */
void StartLowPWR_Task(void const * argument)
{
  /* USER CODE BEGIN StartLowPWR_Task */
  /* Infinite loop */

   uint32_t lpwr_stamp=0;

	while (((Global_16V<LPWR_MIN) || (Global_16V>LPWR_MAX)) && (Blocked_by_Perek==0) ) {
		  Blocked_by_LPWR=1;
		  osDelay(3000);
	}

	Blocked_by_LPWR=0;

  for(;;)
  {
	   if (Blocked_by_Perek==1) {
		   Blocked_by_LPWR=0;
		   lpwr_stamp=0;
	   } else {
		   if ((Global_16V<LPWR_MIN) || (Global_16V>LPWR_MAX))  {
			   if ((lpwr_stamp==0) && (Blocked_by_LPWR==0)) {
			   	lpwr_stamp=xTaskGetTickCount();
			   }
			   if (CheckStamp(lpwr_stamp,LPWR_DELAY_LENGTH)==1) {
				   Blocked_by_LPWR=1;
				   lpwr_stamp=0;
			   }
		   } else {
			   if ((lpwr_stamp==0) && (Blocked_by_LPWR==1)) {
				   lpwr_stamp=xTaskGetTickCount();
			   }
			   if (CheckStamp(lpwr_stamp,LPWR_DELAY_LENGTH)==1) {
				    Blocked_by_LPWR=0;
			   		lpwr_stamp=0;
			   }
		   }
	  }
    osDelay(1);
  }
  /* USER CODE END StartLowPWR_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
