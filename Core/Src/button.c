/*
 * @file button.h
 * @brief Button utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "button.h"
#include "main.h"
#include "gfx.h"
#include "led.h"

#define DEBOUNCE_TIME 20

typedef struct {
	button_id_t id;					// button ID
	uint8_t counter;				// debounce counter
	GPIO_TypeDef *port;				// GPIO port of button
	uint32_t pin;					// pin of button on the GPIO port
} button_t;

/* Statically allocate button controllers */
static button_t btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8;

/* List of button handles (order must match button_id_t enum) */
static button_t *button_list[BTN_CNT] = {&btn1};

void Button_Init(void) {
	btn1 = (button_t) {.id = BTN_ID_1, .counter = 0, .port = B1_GPIO_Port, .pin = B1_Pin};
	btn2 = (button_t) {.id = BTN_ID_2, .counter = 0, .port = 0, .pin = 0};
	btn3 = (button_t) {.id = BTN_ID_3, .counter = 0, .port = 0, .pin = 0};
	btn4 = (button_t) {.id = BTN_ID_4, .counter = 0, .port = 0, .pin = 0};
	btn5 = (button_t) {.id = BTN_ID_5, .counter = 0, .port = 0, .pin = 0};
	btn6 = (button_t) {.id = BTN_ID_6, .counter = 0, .port = 0, .pin = 0};
	btn7 = (button_t) {.id = BTN_ID_DEBUG1, .counter = 0, .port = 0, .pin = 0};
	btn8 = (button_t) {.id = BTN_ID_DEBUG2, .counter = 0, .port = 0, .pin = 0};
}

/**
 * @brief Callback function when button pressed
 * @param id (button_id_t) - id of button pressed
 */
static void Button_PressedHandler(button_id_t id) {
	switch (id) {
		case BTN_ID_1:
			Led_Toggle(LED_ID_1);
			break;
		case BTN_ID_2:
			break;
		case BTN_ID_3:
			break;
		case BTN_ID_4:
			break;
		case BTN_ID_5:
			break;
		case BTN_ID_6:
			break;
		case BTN_ID_DEBUG1:
			break;
		case BTN_ID_DEBUG2:
			break;
		default:
			break;
	}
}

/**
 * @brief Callback function when button released
 * @param id (button_id_t) - id of button released
 */
static void Button_ReleasedHandler(button_id_t id) {
	switch (id) {
		case BTN_ID_1:
			break;
		case BTN_ID_2:
			break;
		case BTN_ID_3:
			break;
		case BTN_ID_4:
			break;
		case BTN_ID_5:
			break;
		case BTN_ID_6:
			break;
		case BTN_ID_DEBUG1:
			break;
		case BTN_ID_DEBUG2:
			break;
		default:
			break;
	}
}

void Button_Debounce(void) {
	for (uint8_t i = 0; i < BTN_CNT; i++) {
		// get next button to debounce
		button_t *btn = button_list[i];

		// Read current state of button
		bool pressed = !HAL_GPIO_ReadPin(btn->port, btn->pin);

		if (!pressed) {
			// if button released then call callback function if it exists
			if (btn->counter == DEBOUNCE_TIME + 1) {
				Button_PressedHandler(btn->id);
			}

			// button not pressed so reset counter
			btn->counter = 0;
		} else {
			// do not allow counter to overflow
			if (btn->counter <= DEBOUNCE_TIME) {
				btn->counter++;
				// if counter reaches debounce time then register press
				if (btn->counter == DEBOUNCE_TIME) {
					Button_ReleasedHandler(btn->id);
				}
			}
		}
	}
}
