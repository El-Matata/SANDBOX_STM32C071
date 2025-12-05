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
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	  HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    osDelay(500);
  }
  /* USER CODE END ComTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

