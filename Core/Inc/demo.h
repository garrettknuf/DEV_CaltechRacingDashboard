/*
 * @file demo.h
 * @brief Demo functions for display
 *
 * @author Garrett Knuf
 * @date 4/1/2024
 */

#ifndef INC_DEMO_H_
#define INC_DEMO_H_

/**
 * @brief Display red, green, and blue background with delay between each
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 */
void demo_display_fill(SPI_HandleTypeDef *hspi);

/**
 * @brief Display six (6) rectangle on the screen of different colors
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 */
void demo_display_rect(SPI_HandleTypeDef *hspi);

#endif /* INC_DEMO_H_ */
