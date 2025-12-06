/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for HeartbeatTask */
osThreadId_t HeartbeatTaskHandle;
const osThreadAttr_t HeartbeatTask_attributes = {
  .name = "HeartbeatTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for ComTask */
osThreadId_t ComTaskHandle;
const osThreadAttr_t ComTask_attributes = {
  .name = "ComTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for DisplayTask */
osThreadId_t DisplayTaskHandle;
const osThreadAttr_t DisplayTask_attributes = {
  .name = "DisplayTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1024 * 4
};
/* Definitions for LoggerTask */
osThreadId_t LoggerTaskHandle;
const osThreadAttr_t LoggerTask_attributes = {
  .name = "LoggerTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 512 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of HeartbeatTask */
  HeartbeatTaskHandle = osThreadNew(StartHeartbeatTask, NULL, &HeartbeatTask_attributes);

  /* creation of ComTask */
  ComTaskHandle = osThreadNew(StartComTask, NULL, &ComTask_attributes);

  /* creation of DisplayTask */
  DisplayTaskHandle = osThreadNew(StartDisplayTask, NULL, &DisplayTask_attributes);

  /* creation of LoggerTask */
  LoggerTaskHandle = osThreadNew(StartLoggerTask, NULL, &LoggerTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_StartHeartbeatTask */
/**
* @brief Function implementing the HeartbeatTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartHeartbeatTask */
void StartHeartbeatTask(void *argument)
{
  /* USER CODE BEGIN HeartbeatTask */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
    osDelay(500);
  }
  /* USER CODE END HeartbeatTask */
}

/* USER CODE BEGIN Header_StartComTask */
/**
* @brief Function implementing the ComTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartComTask */
void StartComTask(void *argument)
{
  /* USER CODE BEGIN ComTask */
  /* Infinite loop */
	char message[50]={"Hello World!\r\n"};
	  HAL_UART_Transmit(&huart1, message, strlen(message), HAL_MAX_DELAY);
  for(;;)
  {

    osDelay(100);
  }
  /* USER CODE END ComTask */
}

/* USER CODE BEGIN Header_StartDisplayTask */
/**
* @brief Function implementing the DisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDisplayTask */
void StartDisplayTask(void *argument)
{
  /* USER CODE BEGIN DisplayTask */
  /* Infinite loop */
  display_Init();
  display_Wombat();

  osDelay(100);

	// Initialise the VL53L0X
	statInfo_t_VL53L0X distanceStr;
	initVL53L0X(1, &hi2c1);

	// Configure the sensor for high accuracy and speed in 20 cm.
	setSignalRateLimit(200);
	setVcselPulsePeriod(VcselPeriodPreRange, 10);
	setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	setMeasurementTimingBudget(300 * 1000UL);

	uint16_t distance;

  for(;;)
  {
	  // uint16_t distance is the distance in millimeters.
	  		// statInfo_t_VL53L0X distanceStr is the statistics read from the sensor.
	  		distance = readRangeSingleMillimeters(&distanceStr);

	  		display_distance(distance);
    osDelay(1);
  }
  /* USER CODE END DisplayTask */
}

/* USER CODE BEGIN Header_StartLoggerTask */
/**
* @brief Function implementing the LoggerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLoggerTask */
void StartLoggerTask(void *argument)
{
  /* USER CODE BEGIN LoggerTask */
  /* Infinite loop */
/*
	uint8_t write_page_buffer[EEPROM_PAGE_SIZE]={0};
	uint8_t read_page_buffer[EEPROM_PAGE_SIZE]={0};

	for (int i = 0; i < EEPROM_PAGE_SIZE; i++) {
	        write_page_buffer[i] = (uint8_t)i; // 0, 1, 2, ... 127
	}
	EEPROM_Page_Write(PAGE_0_ADDRESS, write_page_buffer);

	EEPROM_Page_Read(PAGE_0_ADDRESS, read_page_buffer);

	EEPROM_Chip_Erase();

	EEPROM_Page_Read(PAGE_0_ADDRESS, read_page_buffer);
*/
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LoggerTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

