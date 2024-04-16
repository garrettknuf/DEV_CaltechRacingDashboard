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
	Led_Off(LED_ID_4);
	Led_Off(LED_ID_5);
	Led_Off(LED_ID_DEBUG1);
	Led_Off(LED_ID_DEBUG2);
}

void Led_On(led_id_t led_id) {
	switch (led_id) {
		case LED_ID_1:
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			break;
		case LED_ID_2:
			break;
		case LED_ID_3:
			break;
		case LED_ID_4:
			break;
		case LED_ID_5:
			break;
		case LED_ID_DEBUG1:
			break;
		case LED_ID_DEBUG2:
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
			break;
		case LED_ID_3:
			break;
		case LED_ID_4:
			break;
		case LED_ID_5:
			break;
		case LED_ID_DEBUG1:
			break;
		case LED_ID_DEBUG2:
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
			break;
		case LED_ID_3:
			break;
		case LED_ID_4:
			break;
		case LED_ID_5:
			break;
		case LED_ID_DEBUG1:
			break;
		case LED_ID_DEBUG2:
			break;
		default:
			break;
	}
}
