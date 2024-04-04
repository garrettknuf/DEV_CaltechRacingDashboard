/*
 * @file button.h
 * @brief Button utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#include <stddef.h>
#include <stdint.h>
#include "button.h"

#define DEBOUNCE_TIME 20

typedef struct {
	button_id_t id;			// button ID
	uint8_t counter;		// debounce counter
	Button_Callback fxn;	// function to be called when button pressed
	// TODO add port and pin info
} button_t;

static button_t btn1, btn2, btn3;

static button_t *button_list[BTN_CNT] = {&btn1, &btn2, &btn3};

void Button_Init(void) {
	btn1 = (button_t){.id = BTN_ID_1, .counter = 0, .fxn = NULL};
	btn2 = (button_t){.id = BTN_ID_2, .counter = 0, .fxn = NULL};
	btn3 = (button_t){.id = BTN_ID_3, .counter = 0, .fxn = NULL};
}

void Button_Debounce(void) {
	for (uint8_t i = 0; i < BTN_CNT; i++) {
		// get next button to debounce
		button_t *btn = button_list[i];

		// TODO read button
		bool pressed = false;

		if (!pressed) {
			// button not pressed so reset counter
			btn->counter = 0;
		} else {
			// do not allow counter to overflow
			if (btn->counter <= DEBOUNCE_TIME) {
				btn->counter++;
				// if counter reaches debounce time then register press
				if (btn->counter == DEBOUNCE_TIME) {
					// only call function if callback function exists
					if (btn->fxn != NULL) {
						btn->fxn(btn->id);
					}
				}
			}
		}
	}
}
