/*
 * @file timer.c
 * @brief Event handlers for timer interrupts
 *
 * @author Garrett Knuf
 * @date 4/7/2024
 */

#include "button.h"
#include "encoder.h"
#include "led.h"
#include "gfx.h"
#include "pot.h"
#include "ui.h"
#include "stm32f4xx_hal.h"

/* External references to handle to interact with timer peripherals */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/* Stop watch variables (seconds) */
static uint32_t time_elapsed = 0;
static uint16_t current_ms = 0;

void Timer_EnableInterrupts(void) {
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim3) {
		// Should be called every 1ms
		Button_Debounce();
		Encoder_Debounce();

		// Read different ADC every 50 ms
		if (current_ms % 50 == 0) {
			Pot_Sample();
		}
		current_ms++;
	} else if (htim == &htim2) {
		// Should be called every 1s
		UI_Update_Laptime(time_elapsed);
		UI_Update_BatteryPct(78);
		UI_Update_RPM(2173);
		UI_Update_Speedometer(69);

		// Update these values every 10 seconds
		if (time_elapsed % 10 == 0) {
			UI_Update_WheelTemps(71,73,68,72);
			UI_Update_CoolingTemp(23);
		}

		// Add one more second to time elapsed
		time_elapsed++;
		current_ms = 0;
	}
}
