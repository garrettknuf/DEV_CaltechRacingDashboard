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

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t *data;
	uint32_t data_len;
} image_t;

/**
 * @brief Initialize graphics unit
 */
void Gfx_Init(void);

void Gfx_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);

/**
 * @brief Set the background color
 * @param color (uint8_t) - background color
 */
void Gfx_SetBackground(uint8_t color);

/**
 * @brief Draw a digit (7-segment display pattern) at a specified position
 * 			with a specified height and color
 * @param x (uint16_t) - top-left x coordinate of digit
 * @param y (uint16_t) - top-left y coordinate of digit
 * @param digit (uint8_t) - value of digit to draw (0 <= digit <= 9) or digit = -1
 * 							to delete it
 * @param font_height (uint8_t) - height of digit
 * @param color (uint8_t) - color of digit
 */
void Gfx_DrawDigit(uint16_t x, uint16_t y, uint8_t digit, uint8_t font_height, uint8_t color);

/**
 * @brief Draw an image on the display with its specified properties
 * @param img (image_t) - image properties
 */
void Gfx_DrawImage(image_t *img);

/**
 * @brief Delete an image from the display (replace with background color)
 * @param img (image_t) - image properties
 */
void Gfx_DeleteImage(image_t *img);

#endif /* INC_GFX_H_ */
