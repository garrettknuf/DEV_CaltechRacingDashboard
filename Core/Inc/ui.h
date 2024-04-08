/*
 * ui.h
 *
 *  Created on: Apr 7, 2024
 *      Author: garrett
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include <stdint.h>

/**
 * @brief Initialize user interface
 */
void UI_Init(void);

/**
 * @brief Reset lap time
 *
 * @param time_elapsed (uint32_t) - total time elapsed (seconds)
 */
void UI_Reset_Laptime(uint32_t time_elapsed);

/**
 * @brief Update lap time on display
 *
 * @param time_elapsed (uint32_t) - total time elapsed (seconds)
 */
void UI_Update_Laptime(uint32_t time_elapsed);

/**
 * @brief Update RPM on display
 *
 * @param rpm (uint16_t) - wheel speed in revolutions per minute
 */
void UI_Update_RPM(uint16_t rpm);

/**
 * @brief Update battery percentage on display
 *
 * @param battery_pct(uint8_t) - battery percentage [0, 99]
 */
void UI_Update_BatteryPct(uint8_t battery_pct);

/**
 * @brief Update wheel temperatures on display
 *
 * @param front_left (uint8_t) - front left wheel temp
 * @param front_right (uint8_t) - front right wheel temp
 * @param back_left (uint8_t) - back left wheel temp
 * @param back_left (uint8_t) - back right wheel temp
 */
void UI_Update_WheelTemps(uint8_t front_left, uint8_t front_right,
						  uint8_t back_left, uint8_t back_right);

/**
 * @brief Update tachometer on display
 *
 * @param speed (uint8_t) - vehicle speed in miles per hour
 */
void UI_Update_Speedometer(uint8_t speed);

/**
 * @brief Update cooling temperature on display in degrees fahrenheit
 */
void UI_Update_CoolingTemp(uint8_t temp);

#endif /* INC_UI_H_ */
