/**
 ******************************************************************************
 * File Name          : CAN.c
 * Description        : This file provides code for the configuration
 *                      of the CAN instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void) {

	hcan.Instance = CAN;
	hcan.Init.Prescaler = 9;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = DISABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK) {
		Error_Handler();
	}
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = RXID << 5;
	sFilterConfig.FilterIdLow = RXID << 5;
	sFilterConfig.FilterMaskIdHigh = RXID << 5;
	sFilterConfig.FilterMaskIdLow = RXID << 5;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK) {
		Error_Handler();
	}
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (canHandle->Instance == CAN) {
		/* USER CODE BEGIN CAN_MspInit 0 */

		/* USER CODE END CAN_MspInit 0 */
		/* CAN clock enable */
		__HAL_RCC_CAN1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**CAN GPIO Configuration
		 PA11     ------> CAN_RX
		 PA12     ------> CAN_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* CAN interrupt Init */
		HAL_NVIC_SetPriority(CAN_TX_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN_TX_IRQn);
		HAL_NVIC_SetPriority(CAN_RX0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN_RX0_IRQn);
		HAL_NVIC_SetPriority(CAN_RX1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN_RX1_IRQn);
		/* USER CODE BEGIN CAN_MspInit 1 */

		/* USER CODE END CAN_MspInit 1 */
	}
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle) {

	if (canHandle->Instance == CAN) {
		/* USER CODE BEGIN CAN_MspDeInit 0 */

		/* USER CODE END CAN_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CAN1_CLK_DISABLE();

		/**CAN GPIO Configuration
		 PA11     ------> CAN_RX
		 PA12     ------> CAN_TX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

		/* CAN interrupt Deinit */
		HAL_NVIC_DisableIRQ(CAN_TX_IRQn);
		HAL_NVIC_DisableIRQ(CAN_RX0_IRQn);
		HAL_NVIC_DisableIRQ(CAN_RX1_IRQn);
		/* USER CODE BEGIN CAN_MspDeInit 1 */

		/* USER CODE END CAN_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
void CAN_Start(void) {
	HAL_CAN_Start(&hcan);
	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING)
			!= HAL_OK) {
		Error_Handler();
	}
}
void HAL_CAN_RXFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
		Error_Handler();
	}
}
void CAN_Send(void) {
	TxHeader.StdId = TXID;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 3;
	TxHeader.TransmitGlobalTime = DISABLE;
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		Error_Handler();
	}
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
