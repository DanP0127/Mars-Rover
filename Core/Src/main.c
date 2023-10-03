/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
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

/* USER CODE BEGIN PV */
volatile uint16_t channel_SBUS[18];
float max_RC_Value = 1811.0, min_RC_Value = 60.0, throttle_perct = 0.0, tot_TIM = 65535;
int32_t CH1_DC = 0, CH2_DC = 0, CH3_DC = 0, CH4_DC = 0;


volatile uint16_t failsafe_status; //Failsafe status transmitted if signal lost
volatile uint8_t buffer_SBUS[25]; //SBUS send a 25 byte packet
volatile uint16_t channels_SBUS[18]; //SBUS has 16 channels; Channels are 11 bits each
volatile uint16_t counter;

volatile uint16_t counter;
volatile uint32_t pulseWidth;
volatile float distance;
volatile float distances;

TaskHandle_t led_handler;
TaskHandle_t motor_handler;
TaskHandle_t auto_handler;

SemaphoreHandle_t bin_sem;

QueueHandle_t queue_motor;
QueueHandle_t queue_autonomous;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void led_blink(void *parameters);
void sbus_recieve(void *parameters);
void motor_task(void *parameters);
void autonomy_mode(void *parameters);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  queue_motor = xQueueCreate(18, sizeof(uint16_t[18]));
  queue_autonomous = xQueueCreate(1, sizeof(float));

  bin_sem = xSemaphoreCreateBinary();

  if(bin_sem != NULL)
  {
	  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	  xTaskCreate(led_blink, "Led Blink", 256, NULL, 1, &led_handler);
	  xTaskCreate(motor_task, "MotorTask", 256, NULL, 2, &motor_handler);
	  xTaskCreate(autonomy_mode, "Autonomy Mode", 256, NULL, 2, &auto_handler);
	  HAL_UART_Receive_IT(&huart1, buffer_SBUS, 25);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	  vTaskStartScheduler();
  }




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	BaseType_t xHigherPriorityTaskWoken_V2;
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
		if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)) == 1){

			__HAL_TIM_SET_COUNTER(&htim3, 0);

		}else{
			pulseWidth = __HAL_TIM_GET_COUNTER(&htim3);
			distance = ((float)pulseWidth * 0.0343) / 2.0;

			xQueueSendFromISR(queue_autonomous,&distance,&xHigherPriorityTaskWoken_V2);
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken_V2);
		}
	}
}

void motor_task(void *parameters)
{
	BaseType_t xStatus;
	while(1)
	{
		xStatus = xQueueReceive( queue_motor, channel_SBUS, portMAX_DELAY );
		/*****************************
		 * THROTTLE CONTROL
		 ****************************/
	if (xStatus == pdPASS) {
		if(channel_SBUS[0]){
			throttle_perct = 1 - ((max_RC_Value - ((float)channel_SBUS[0] - 60)) / max_RC_Value);

			if(channel_SBUS[1] >= 872 && channel_SBUS[1] <= 1072){ // 990 is middle condition, 172 low, 1808 high

				/*****************************
				* FORWARD
				****************************/
				if(channel_SBUS[2] >= 576 && channel_SBUS[2] <= 1292){
					// Back Left Forward
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);

					// Back Right Forward
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);

					// Front Left Forward
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);

					// Front Right Forward
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

				TIM2->CCR1 = CH1_DC;
				TIM2->CCR2 = CH2_DC;
				TIM2->CCR3 = CH3_DC;
				TIM2->CCR4 = CH4_DC;
				CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;

				/*****************************
				* BACKWARDS
				****************************/
				} else if(channel_SBUS[2] >= 172 && channel_SBUS[2] <= 376){
					// Back Left Backward
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);

					// Back Right Backward
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);

					// Front Left Backward
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);

					// Front Right Backward
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

					TIM2->CCR1 = CH1_DC;
					TIM2->CCR2 = CH2_DC;
					TIM2->CCR3 = CH3_DC;
					TIM2->CCR4 = CH4_DC;
					CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;
				} else{
					TIM2->CCR1 = CH1_DC;
					TIM2->CCR2 = CH2_DC;
					TIM2->CCR3 = CH3_DC;
					TIM2->CCR4 = CH4_DC;
					CH1_DC = CH2_DC = CH3_DC = CH4_DC = 0;
				}
			/*****************************
			* TURN LEFT
			****************************/
			} else if(channel_SBUS[1] < 872){
				// Back Left Backward
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);

				// Back Right Forward
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);

				// Front Left Backward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);

				// Front Right Forward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

				TIM2->CCR1 = CH1_DC;
				TIM2->CCR2 = CH2_DC;
				TIM2->CCR3 = CH3_DC;
				TIM2->CCR4 = CH4_DC;
				CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;

			/*****************************
			* TURN RIGHT
			****************************/
			} else if(channel_SBUS[1] > 1072){
				// Back Left Forward
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);

				// Back Right Backward
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);

				// Front Left Forward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);

				// Front Right Backward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

				TIM2->CCR1 = CH1_DC;
				TIM2->CCR2 = CH2_DC;
				TIM2->CCR3 = CH3_DC;
				TIM2->CCR4 = CH4_DC;
				CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;
				}
			}
		}
	}
}

void autonomy_mode(void *parameters)
{
	vTaskDelay(pdMS_TO_TICKS(500));
	BaseType_t xHigherPriorityTaskWoken_V2;

	while(1)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 1);
		vTaskDelay(1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);

		xQueueReceiveFromISR(queue_autonomous, &distances, &xHigherPriorityTaskWoken_V2);

		if(distances < 10)
		{
			/*****************************
			* BACKWARDS
			****************************/
			for(int i = 0; i < 100000; i++)
			{
				// Back Left Backward
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);

				// Back Right Backward
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);

				// Front Left Backward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);

				// Front Right Backward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

				TIM2->CCR1 = CH1_DC;
				TIM2->CCR2 = CH2_DC;
				TIM2->CCR3 = CH3_DC;
				TIM2->CCR4 = CH4_DC;
				CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;
			}

			/*****************************
			* Left
			****************************/
			for(int i = 0; i < 100000; i++)
			{
				// Back Left Backward
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);

				// Back Right Forward
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);

				// Front Left Backward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);

				// Front Right Forward
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

				TIM2->CCR1 = CH1_DC;
				TIM2->CCR2 = CH2_DC;
				TIM2->CCR3 = CH3_DC;
				TIM2->CCR4 = CH4_DC;
				CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;
			}

		}else {
			/*****************************
			* FORWARD
			****************************/
			// Back Left Forward
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);

			// Back Right Forward
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);

			// Front Left Forward
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);

			// Front Right Forward
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

			TIM2->CCR1 = CH1_DC;
			TIM2->CCR2 = CH2_DC;
			TIM2->CCR3 = CH3_DC;
			TIM2->CCR4 = CH4_DC;
			CH1_DC = CH2_DC = CH3_DC = CH4_DC = throttle_perct * tot_TIM;

		}

		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void led_blink(void *parameters)
{
	while(1)
	{
		xSemaphoreTake( bin_sem, portMAX_DELAY );
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		if(buffer_SBUS[0] == 0x0F) //The first start byte should be 0x0F. Check if that's the case.
		{
			//Define the channels:
			/*
			 * Process:
			 * Each channel should hold 11 bits of data
			 * First buffer goes left as LSB, second buffer fills the remainder to 11 bit shifting right
			 * The next channel shift to get the remaining bits not used and ORs with next buffer item. Continue trying to get 11 bits per channel
			 * Of course, mask the 16 bit channels to just keep the 11 bits.
			 */
			channels_SBUS[0] = (buffer_SBUS[1] >> 0 | (buffer_SBUS[2] << 8)) & 0x07FF;//Extract 11 bits for channel 0.
			//EX: buffer[2](shifted):1111111100000000 buffer[1]:0000000011111111
			channels_SBUS[1] = (buffer_SBUS[2] >> 3 | (buffer_SBUS[3] << 5)) & 0x07FF;
			//EX: buffer[2] needs to combine the five bits left over with bits from next byte
			channels_SBUS[2] = (buffer_SBUS[3] >> 6 | (buffer_SBUS[4] << 2) | buffer_SBUS[5] << 10) & 0x07FF;
			//EX: buffer[3] needs two more bits, buffer[4] must be shifted to account for buffer 3, buffer[5] must be added in to make 11 bits
			channels_SBUS[3] = (buffer_SBUS[5] >> 1 | (buffer_SBUS[6] << 7)) & 0x07FF;
			channels_SBUS[4] = (buffer_SBUS[6] >> 4 | (buffer_SBUS[7] << 4)) & 0x07FF;
			channels_SBUS[5] = (buffer_SBUS[7] >> 7 | (buffer_SBUS[8] << 1) | buffer_SBUS[9] << 9) & 0x07FF;
			channels_SBUS[6] = (buffer_SBUS[9] >> 2 | (buffer_SBUS[10] << 6)) & 0x07FF;
			channels_SBUS[7] = (buffer_SBUS[10] >> 5 | (buffer_SBUS[11] << 3)) & 0x07FF;
			channels_SBUS[8] = (buffer_SBUS[12] << 0 | (buffer_SBUS[13] << 8)) & 0x07FF;
			channels_SBUS[9] = (buffer_SBUS[13] >> 3 | (buffer_SBUS[14] << 5)) & 0x07FF;
			channels_SBUS[10] = (buffer_SBUS[14] >> 6 | (buffer_SBUS[15] << 2) | buffer_SBUS[16] << 10) & 0x07FF;
			channels_SBUS[11] = (buffer_SBUS[16] >> 1 | (buffer_SBUS[17] << 7)) & 0x07FF;
			channels_SBUS[12] = (buffer_SBUS[17] >> 4 | (buffer_SBUS[18] << 4)) & 0x07FF;
			channels_SBUS[13] = (buffer_SBUS[18] >> 7 | (buffer_SBUS[19] << 1) | buffer_SBUS[20] << 9) & 0x07FF;
			channels_SBUS[14] = (buffer_SBUS[20] >> 2 | (buffer_SBUS[21] << 6)) & 0x07FF;
			channels_SBUS[15] = (buffer_SBUS[21] >> 5 | (buffer_SBUS[22] << 3)) & 0x07FF;

			if (buffer_SBUS[23] & (1 << 0))
			{
				channels_SBUS[16] = 1; //If byte 23(digital channel) is 1, then 17th channel is 1
			}else{
				channels_SBUS[16] = 0;
			}

			if (buffer_SBUS[23] & (1 << 1)) //Digital Channel 18.
			{
				channels_SBUS[17] = 1;
			}else {
				channels_SBUS[17] = 0;
			}

			//Failsafe for lost signal
			if (buffer_SBUS[23] & (1 << 2)) {
				failsafe_status = 0;
			}
			if (channels_SBUS[4] == 1811)
			{
				vTaskResume(auto_handler);
			} else
			{
				vTaskSuspend(auto_handler);
				xQueueSend(queue_motor, channels_SBUS, portMAX_DELAY);
			}

		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BaseType_t xHigherPriorityTaskWoken;
	if (huart->Instance == USART1) {
	    HAL_UART_Receive_IT(&huart1, buffer_SBUS, 25);

	    xHigherPriorityTaskWoken = pdFALSE;
	    xSemaphoreGiveFromISR(bin_sem,&xHigherPriorityTaskWoken );
	    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

	}
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
