/*
 * WBBMain.h
 *
 *  Created on: May 20, 2019
 *      Author: Shasta
 */

#ifndef WBBMAIN_H_
#define WBBMAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void InitMotorDriver1TimerHandle(TIM_HandleTypeDef *htim);
void WBBMain(void);

#ifdef __cplusplus
}
#endif

#endif /* WBBMAIN_H_ */
