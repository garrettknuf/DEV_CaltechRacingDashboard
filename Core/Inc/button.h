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
	BTN_ID_2,
	BTN_ID_3,
	BTN_ID_4,
	BTN_ID_5,
	BTN_ID_6,
	BTN_ID_DEBUG1,
	BTN_ID_DEBUG2,
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
