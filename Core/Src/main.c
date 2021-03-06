/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_CAN_Init();
  MX_DAC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */
	DAC_Start();
	Encoder_Start();
	Pwm_Start();
	CAN_Start();
	ADC_Start();
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	int counter = 0;
//	RGB_Set(1000, 0, 0);
//	HAL_Delay(1000);
//	RGB_Set(0, 1000, 0);
//	HAL_Delay(1000);
//	RGB_Set(0, 0, 1000);
//	HAL_Delay(1000);
//	RGB_Set(100, 0, 0);
//	HAL_Delay(1000);
//	RGB_Set(0, 100, 0);
//	HAL_Delay(1000);
//	RGB_Set(0, 0, 100);
//	HAL_Delay(1000);
	HAL_GPIO_WritePin(SLEEPn_GPIO_Port, SLEEPn_Pin, 1);
	HAL_GPIO_WritePin(CAN_STBY_GPIO_Port, CAN_STBY_Pin, 0);

	while (1) {
		int16_t cur = (RxData[ID * 2 - 2] << 8) + (RxData[ID * 2 - 1] << 0);
		double current = (double) cur;
		double current2 = 1023.0 - current / 0x7fff * 1023.0;
		if (current > 0.0)
			Pwm_Set(current2, 1023);
		else if (current < 0.0) {
			Pwm_Set(1023, -current2);
			current = -current;
		} else
			Pwm_Set(1023, 1023);
		DAC_set_voltage(2.5 * current / 0x7fff);
		int32_t enc_val = Encoder_Read();

		TxData[0] = (enc_val >> 24) & 0xff; //position32bit
		TxData[1] = (enc_val >> 16) & 0xff;
		TxData[2] = (enc_val >> 8) & 0xff;
		TxData[3] = (enc_val >> 0) & 0xff;

		TxData[4] = (ADCBuffer1[1] >> 8) & 0xff;//voltage
		TxData[5] = (ADCBuffer1[1] >> 0) & 0xff;

		TxData[6] = (ADCBuffer2[0] >> 8) & 0xff;//current
		TxData[7] = (ADCBuffer2[0] >> 0) & 0xff;

		ADCBuffer1;
		ADCBuffer2;
//		uint16_t voltage = ADCValue[0];
//		uint16_t aiout = ADCValue[1];
//		TxData[4] = (ADCValue[1] >> 8) & 0xff; //current
//		TxData[5] = (ADCValue[1] >> 0) & 0xff;
//
//		TxData[6] = (ADCValue[0] >> 8) & 0xff; //voltage
//		TxData[7] = (ADCValue[0] >> 0) & 0xff;
//		TxData[0]=0xAA;
//		TxData[1]=0xAB;
//		TxData[2]=0xA9;
//		TxData[3]=0xAA;
//		TxData[4]=0xAA;
//		TxData[5]=0xAB;
//		TxData[6]=0xAB;
//		TxData[7]=0xA9;

		CAN_Send();
//		RGB_Set(abs(enc_val), counter, 500);
		RGB_Set(RxData[0], RxData[1], RxData[2]);

		HAL_Delay(1);
		counter++;
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
