/*
 * @file led.c
 * @brief LED utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#include "led.h"

void Led_Init(void) {

}

void Led_On(led_id_t led_id) {
	switch (led_id) {
		case LED_ID_1:
			// TODO turn led on
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
			// TODO turn led off
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
			// TODO toggle LED
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
