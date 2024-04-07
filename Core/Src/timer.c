/*
 * @file timer.c
 * @brief Event handlers for timer interrupts
 *
 * @author Garrett Knuf
 * @date 4/7/2024
 */

#include "button.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim3;

void Timer_EnableInterrupts(void) {
	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim3) {
		// Should be called every 1ms
		Button_Debounce();
	}
}
