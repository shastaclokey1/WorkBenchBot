/*
 * WBBMain.cpp
 *
 *  Created on: May 20, 2019
 *      Author: Shasta
 */

#include "WBBMain.h"
#include "main.h"
#include <stdbool.h>

bool runMotorDriverStateMachine = false;
static TIM_HandleTypeDef *MotorDriver1TimerHandle;

void EnableMotorDriver(void);
void SetMotorDriverForward(void);
void SetMotorDriverBackward(void);
void PulseMotorDriver(void);
void StartMotorDriverTimer(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void InitMotorDriver1TimerHandle(TIM_HandleTypeDef *htim)
{
	MotorDriver1TimerHandle = htim;
}

void WBBMain(void)
{
	EnableMotorDriver();
	SetMotorDriverForward();
	StartMotorDriverTimer();

	while (true)
	{
		if (runMotorDriverStateMachine)
		{
			PulseMotorDriver();
			runMotorDriverStateMachine = false;
		}
	}
}

void EnableMotorDriver(void)
{
	HAL_GPIO_WritePin(MotorDriver1Enable_GPIO_Port, MotorDriver1Enable_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void SetMotorDriverForward(void)
{
	HAL_GPIO_WritePin(MotorDriver1Direction_GPIO_Port, MotorDriver1Direction_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}

void SetMotorDriverBackward(void)
{
	HAL_GPIO_WritePin(MotorDriver1Direction_GPIO_Port, MotorDriver1Direction_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void PulseMotorDriver(void)
{
	HAL_GPIO_WritePin(MotorDriver1Pulse_GPIO_Port, MotorDriver1Pulse_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(MotorDriver1Pulse_GPIO_Port, MotorDriver1Pulse_Pin, GPIO_PIN_RESET);
}

void StartMotorDriverTimer(void)
{
	HAL_TIM_Base_Start_IT(MotorDriver1TimerHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (MotorDriver1TimerHandle->Instance == htim->Instance)
	{
		runMotorDriverStateMachine = true;
	}
}
