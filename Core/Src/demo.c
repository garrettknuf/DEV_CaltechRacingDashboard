/*
 * @file demo.c
 * @brief Demo functions for display
 *
 * @author Garrett Knuf
 * @date 4/1/2024
 */

#include "display.h"
#include "demo.h"


void demo_display_fill(SPI_HandleTypeDef *hspi) {
	/* Fill screen with various colors and wait between each one */
	Display_FillScreen(hspi, COLOR_RED);
	HAL_Delay(1000);
	Display_FillScreen(hspi, COLOR_GREEN);
	HAL_Delay(1000);
	Display_FillScreen(hspi, COLOR_BLUE);
	HAL_Delay(1000);
	Display_FillScreen(hspi, COLOR_BLACK);
	HAL_Delay(1000);
}

void demo_display_rect(SPI_HandleTypeDef *hspi) {
	/* Draw various rectangles of different and positions with delay */
	Display_DrawRect(hspi, 20, 100, 50, 50, COLOR_RED);
	HAL_Delay(200);
	Display_DrawRect(hspi, 130, 100, 50, 50, COLOR_GREEN);
	HAL_Delay(200);
	Display_DrawRect(hspi, 240, 100, 50, 50, COLOR_BLUE);
	HAL_Delay(200);
	Display_DrawRect(hspi, 20, 200, 50, 50, COLOR_YELLOW);
	HAL_Delay(200);
	Display_DrawRect(hspi, 130, 200, 50, 50, COLOR_PINK);
	HAL_Delay(200);
	Display_DrawRect(hspi, 240, 200, 50, 50, COLOR_CYAN);
	HAL_Delay(200);
}
