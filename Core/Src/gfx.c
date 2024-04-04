/*
 * @file gfx.c
 * @brief Graphics functions
 *
 * @author Garrett Knuf
 * @date 4/3/2024
 */

#include "display.h"
#include "gfx.h"

/* External reference to display SPI handle */
extern SPI_HandleTypeDef hspi2;

/* Masks for interpreting patterns for 7-segment display pattern */
#define SEG_A_MASK 0b1000000
#define SEG_B_MASK 0b0100000
#define SEG_C_MASK 0b0010000
#define SEG_D_MASK 0b0001000
#define SEG_E_MASK 0b0000100
#define SEG_F_MASK 0b0000010
#define SEG_G_MASK 0b0000001

/* Current background color (needed to "delete" graphics) */
static uint8_t background_color = COLOR_BLACK;

/**
 * @brief Patterns of segments to display when drawing digits
 *
 * 7-bits where 1 represents segment on and 0 represents segment off
 * Stored in a,b,c,d,e,f,g order similar to a 7-segment display
 */
static uint8_t digit_patterns[10] = {
	0b1111110, // 0
	0b0110000, // 1
	0b1101101, // 2
	0b1111001, // 3
	0b0110011, // 4
	0b1011011, // 5
	0b1011111, // 6
	0b1110000, // 7
	0b1111111, // 8
	0b1110011  // 9
};

void Gfx_Init(void) {
	Gfx_SetBackground(COLOR_BLACK);
}

void Gfx_SetBackground(uint8_t color) {
	background_color = color;
	Gfx_DrawRect(0, 0, DISPLAY_SIZE_X, DISPLAY_SIZE_Y, color);
}

void Gfx_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
	/* Set window of rectangle */
	Display_SetWindow(x, y, x + w - 1, y + h - 1);

	/* Send pixel data */
	Display_SendColor(w * h, color);
}

void Gfx_DrawDigit(uint16_t x, uint16_t y, uint8_t digit, uint8_t font_height, uint8_t color) {

	/* Digits 0-9 will map directly to display that digit, -1 will delete the digit */
	if (digit != (uint8_t)(-1) && (digit < 0 || digit > 9)) {
		// Do nothing if digit is not a valid value
		return;
	}

	/* thickness of each segment */
	uint8_t thickness = font_height / 10;

	/* length of each segment */
	uint8_t seg_len = (font_height - (thickness * 2)) / 2;

	/* for small fonts make the segments slightly thicker */
	if (font_height < 40) {
		thickness += 2;
	}

	/* Get abcdefg pattern for digit (or zero if digit == -1)*/
	uint8_t pattern = (digit == (uint8_t)(-1)) ? 0 : digit_patterns[digit];

	/* Active segments are set to color */
	/* Inactive segments are set to background color */
	uint8_t new_color;

	// a
	new_color = ((pattern & SEG_A_MASK) ? color : background_color);
	Gfx_DrawRect(x+thickness, y, seg_len, thickness, new_color);

	// b
	new_color = ((pattern & SEG_B_MASK) ? color : background_color);
	Gfx_DrawRect(x+seg_len+thickness, y+thickness, thickness, seg_len, new_color);

	// c
	new_color = ((pattern & SEG_C_MASK) ? color : background_color);
	Gfx_DrawRect(x+seg_len+thickness, y+(2*thickness)+seg_len, thickness, seg_len, new_color);

	// d
	new_color = ((pattern & SEG_D_MASK) ? color : background_color);
	Gfx_DrawRect(x+thickness, y+(2*thickness)+(2*seg_len), seg_len, thickness, new_color);

	// e
	new_color = ((pattern & SEG_E_MASK) ? color : background_color);
	Gfx_DrawRect(x, y+(2*thickness)+seg_len, thickness, seg_len, new_color);

	// f
	new_color = ((pattern & SEG_F_MASK) ? color : background_color);
	Gfx_DrawRect(x, y+thickness, thickness, seg_len, new_color);

	// g
	new_color = ((pattern & SEG_G_MASK) ? color : background_color);
	Gfx_DrawRect(x+thickness, y+thickness+seg_len, seg_len, thickness, new_color);
}

void Gfx_DrawImage(image_t *img) {
	/* Set window to display image */
	Display_SetWindow(img->x, img->y, img->x + img->w -1, img->y + img->h - 1);

	/* Send image data */
	Display_SendData(img->data_len, img->data);
}

void Gfx_DeleteImage(image_t *img) {
	/* Set window of image */
	Display_SetWindow(img->x, img->y, img->x + img->w -1, img->y + img->h - 1);

	/* Draw background color to delete image */
	Gfx_DrawRect(img->x, img->y, img->w, img->h, background_color);

}
