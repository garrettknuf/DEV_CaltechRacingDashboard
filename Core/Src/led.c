/*
 * @file led.c
 * @brief LED utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#include "led.h"
#include "main.h"

void Led_Init(void) {
	Led_Off(LED_ID_1);
	Led_Off(LED_ID_2);
	Led_Off(LED_ID_3);
}

void Led_On(led_id_t led_id) {
	switch (led_id) {
		case LED_ID_1:
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			break;
		case LED_ID_2:
			// TODO turn led on
			break;
		case LED_ID_3:
			// TODO turn led on
			break;
		default:
			break;
	}
}

void Led_Off(led_id_t led_id) {
	switch (led_id) {
		case LED_ID_1:
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			break;
		case LED_ID_2:
			// TODO turn led off
			break;
		case LED_ID_3:
			// TODO turn led off
			break;
		default:
			break;
	}
}

void Led_Toggle(led_id_t led_id) {
	switch (led_id) {
		case LED_ID_1:
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			break;
		case LED_ID_2:
			// TODO toggle LED
			break;
		case LED_ID_3:
			// TODO toggle LED
			break;
		default:
			break;
	}
}
