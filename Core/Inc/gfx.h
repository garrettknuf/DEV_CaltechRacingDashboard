/*
 * @file gfx.h
 * @brief Graphics functions
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#ifndef INC_GFX_H_
#define INC_GFX_H_

#include <stdint.h>
#include "img.h"

/* Display pixel colors (3-bit RGB) (X, X, R1, G1, B1, R2,G2,B2)*/
#define COLOR_BLACK		0x00
#define COLOR_WHITE		0x3F
#define COLOR_RED		0x24
#define COLOR_GREEN		0x12
#define COLOR_BLUE		0x09
#define COLOR_YELLOW	0x36
#define COLOR_PINK		0x2D
#define COLOR_CYAN		0x1A

/**
 * @brief Initialize graphics unit
 */
void Gfx_Init(void);

/**
 * @brief Draw filled rectangle on display
 * @param x (uint16_t) - x-coordinate (top-left corner)
 * @param y (uint16_t) - y-coordinate (top-left corner)
 * @param w (uint16_t) - width of rectangle
 * @param h (uint16_t) - height of rectangle
 * @param color (uint8_t) - color to fill rectangle
 */
void Gfx_DrawFilledRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);

/**
 * @brief Draw unfilled rectangle on display
 * @param x (uint16_t) - x-coordinate (top-left corner)
 * @param y (uint16_t) - y-coordinate (top-left corner)
 * @param w (uint16_t) - width of rectangle
 * @param h (uint16_t) - height of rectangle
 * @param color (uint8_t) - color to fill rectangle
 * @param thickness (uint8_t) - stroke thickness
 */
void Gfx_DrawUnfilledRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color, uint8_t thickness);


/**
 * @brief Set the background color
 * @param color (uint8_t) - background color
 */
void Gfx_SetBackground(uint8_t color);

/**
 * @brief Draw an image on the display with its specified properties
 * @param img (image_t) - image properties
 * @param x (uint16_t) - x-coordinate of image
 * @param y (uint16_t) - y-coordinate of image
 */
void Gfx_DrawImage(image_t *img, uint16_t x, uint16_t y);

/**
 * @brief Draw a digit (7-segment display pattern) at a specified position
 * 			with a specified height and color
 * @param x (uint16_t) - top-left x coordinate of digit
 * @param y (uint16_t) - top-left y coordinate of digit
 * @param digit (int8_t) - value of digit to draw (0 <= digit <= 9) or digit = -1
 * 							to delete it
 * @param font_height (uint8_t) - height of digit
 * @param color (uint8_t) - color of digit
 */
void Gfx_Draw7SegDigit(uint16_t x, uint16_t y, int8_t digit, uint8_t font_height, uint8_t color);

#endif /* INC_GFX_H_ */
