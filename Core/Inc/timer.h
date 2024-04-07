/*
 * @file timer.h
 * @brief Event handlers for timer interrupts
 *
 * @author Garrett Knuf
 * @date 4/7/2024
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

/**
 * @brief Enable interrupts for timers.
 */
void Timer_EnableInterrupts(void);

/**
 * @brief Event handler for timer interrupts
 * @param htim (TIM_HandleTypeDef *) - handle of timer that generated interrupt
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */
