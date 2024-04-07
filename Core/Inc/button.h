/*
 * @file button.c
 * @brief Button utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#ifndef INC_BUTTON_C_
#define INC_BUTTON_C_

typedef enum {
	BTN_ID_1,
	BTN_CNT	// total number of buttons
} button_id_t;

/**
 * @brief Initialize button controllers
 */
void Button_Init(void);

/**
 * @brief Event handler to debounce buttons
 *
 * 	Should be called every 1 millisecond.
 */
void Button_Debounce(void);


#endif /* INC_BUTTON_C_ */
