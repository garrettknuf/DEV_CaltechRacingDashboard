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
 * Stored in ABCDEFG order similar to a 7-segment display
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
	Gfx_DrawFilledRect(0, 0, DISPLAY_SIZE_X, DISPLAY_SIZE_Y, color);
}

void Gfx_DrawFilledRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
	if (x + w > DISPLAY_SIZE_X || y + h > DISPLAY_SIZE_Y) {
		/* Do nothing if arguments are invalid */
		return;
	}

	/* Set window of rectangle */
	Display_SetWindow(x, y, x + w - 1, y + h - 1);

	/* Send pixel data */
	Display_SendColor(w * h, color);
}

void Gfx_DrawUnfilledRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color, uint8_t thickness) {
	Gfx_DrawFilledRect(x, y, w, thickness, color);
	Gfx_DrawFilledRect(x, y, thickness, h, color);
	Gfx_DrawFilledRect(x + w - thickness, y, thickness, h, color);
	Gfx_DrawFilledRect(x, y + h - thickness, w, thickness, color);
}

void Gfx_DrawNumber(uint16_t x, uint16_t y, uint8_t number, uint8_t font_height, uint8_t color) {
	Gfx_Draw7SegDigit(x, y, number % 10, font_height, color);
	Gfx_Draw7SegDigit(x + (font_height * 3 / 2), y, number / 10, font_height, color);
}

void Gfx_DrawImage(image_t *img, uint16_t x, uint16_t y) {
	/* Set window to display image */
	Display_SetWindow(x, y, x + img->w -1, y + img->h - 1);

	/* Send image data */
	Display_SendData(img->data_len, img->data);
}


void Gfx_Draw7SegDigit(uint16_t x, uint16_t y, int8_t digit, uint8_t font_height, uint8_t color) {
	/* Digits 0-9 will map directly to display that digit, -1 will delete the digit */
	if (digit != -1 && (digit < 0 || digit > 9)) {
		// Do nothing if digit is not a valid value
		return;
	}

	/* Thickness of each segment */
	uint8_t thickness = font_height / 10;

	/* Length of each segment */
	uint8_t seg_len = (font_height - (thickness * 2)) / 2;

	/* For small fonts make the segments slightly thicker */
	if (font_height < 40) {
		thickness += 2;
	}

	/* Get ABCDEFG pattern for digit (or zero if digit == -1)*/
	uint8_t pattern = (digit == -1) ? 0 : digit_patterns[digit];

	/* Active segments are set to color */
	/* Inactive segments are set to background color */
	uint8_t new_color;

	// Segment A
	new_color = ((pattern & SEG_A_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x+thickness, y, seg_len, thickness, new_color);

	// Segment B
	new_color = ((pattern & SEG_B_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x+seg_len+thickness, y+thickness, thickness, seg_len, new_color);

	// Segment C
	new_color = ((pattern & SEG_C_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x+seg_len+thickness, y+(2*thickness)+seg_len, thickness, seg_len, new_color);

	// Segment D
	new_color = ((pattern & SEG_D_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x+thickness, y+(2*thickness)+(2*seg_len), seg_len, thickness, new_color);

	// Segment E
	new_color = ((pattern & SEG_E_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x, y+(2*thickness)+seg_len, thickness, seg_len, new_color);

	// Segment F
	new_color = ((pattern & SEG_F_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x, y+thickness, thickness, seg_len, new_color);

	// Segment G
	new_color = ((pattern & SEG_G_MASK) ? color : background_color);
	Gfx_DrawFilledRect(x+thickness, y+thickness+seg_len, seg_len, thickness, new_color);
}
