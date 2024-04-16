/*
 * @file led.h
 * @brief LED utility
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#ifndef INC_LED_H_
#define INC_LED_H_

typedef enum {
	LED_ID_1,
	LED_ID_2,
	LED_ID_3,
	LED_ID_4,
	LED_ID_5,
	LED_ID_DEBUG1,
	LED_ID_DEBUG2,
	LED_CNT		// total number of LEDs
} led_id_t;

/**
 * @brief Initialize LED controllers
 */
void Led_Init(void);

/**
 * @brief Turn on specified LED
 * @param led_id (led_id_t) - id of led to turn on
 */
void Led_On(led_id_t led_id);

/**
 * @brief Turn off specified LED
 * @param led_id (led_id_t) - id of led to turn off
 */
void Led_Off(led_id_t led_id);

/**
 * @brief Toggle specified LED
 * @param led_id (led_id_t) - id of led to toggle
 */
void Led_Toggle(led_id_t led_id);

#endif /* INC_LED_H_ */
