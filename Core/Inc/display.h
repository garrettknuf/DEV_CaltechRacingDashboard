/*
 * @file display.h
 * @brief Display interface for ILI9486
 *
 * @author Garrett Knuf
 * @date 3/29/2024
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

/* Standard C includes */
#include <stdint.h>

/* Auto-generated includes */
#include "main.h"

/* SPI timeout duration to prevent hanging (ms) */
#define SPI_TIMEOUT_MS 100

/* Time to hold reset pin LOW during hardware reset (ms) */
#define DISPLAY_RESET_TIME_MS 10

/* Display commands (more available in ILI9488 datasheet) */
#define DISPLAY_NOP			0x00	// No operation
#define DISPLAY_SWRESET		0x01	// Software reset
#define DISPLAY_SLEEPIN		0x10	// Sleep in
#define DISPLAY_SLEEPOUT	0x11	// Sleep out
#define DISPLAY_PMON		0x12	// Partial mode on
#define DISPLAY_NMON		0x13	// Normal mode on
#define DISPLAY_INVOFF		0x20	// Display inversion off
#define DISPLAY_INVON		0x21	// Display inversion on
#define DISPLAY_PIXOFF		0x22	// All pixels off
#define DISPLAY_PIXON		0x23	// All pixels on
#define DISPLAY_DISPOFF		0x28	// Display off
#define DISPLAY_DISPON		0x29	// Display on
#define DISPLAY_COLADDRSET	0x2A	// Column address set
#define DISPLAY_PGADDRSET	0x2B	// Page address set
#define DISPLAY_MEMWR		0x2C	// Memory write
#define DISPLAY_MEMRD		0x2D	// Memory read
#define DISPLAY_MEMACTRL	0x36 	// Memory access control
#define DISPLAY_IDLEOFF		0x38	// Idle mode off
#define DISPLAY_IDLEON		0x39	// Idle mode on
#define DISPLAY_INTPXLFMT	0x3A	// Interface pixel format
#define DISPLAY_BRTWR		0x51	// Write display brightness value
#define DISPLAY_CTRLWR		0x53	// Write CTRL display value
#define DISPLAY_INTMCTRL	0xB0	// Interface mode control
#define DISPLAY_FRCNM		0xB1	// Frame rate control (in normal mode)
#define DISPLAY_FRCIM		0xB2	// Frame rate control (in idle mode)
#define DISPLAY_FRCPM		0xB3	// Frame rate control (in partial mode)
#define DISPLAY_PWRCTRL1	0xC0	// Power control 1
#define DISPLAY_PWRCTRL2	0xC1	// Power control 2
#define	DISPLAY_PWRCTRL3	0xC2	// Power control 3 (for normal mode)
#define DISPLAY_PWRCTRL4	0xC3	// Power control 4 (for idle mode)
#define DISPLAY_PWRCTRL5	0xC4	// Power control 5 (for partial mode)
#define DISPLAY_VCOMCTRL	0xC5	// VCOM Control

/* Display pixel colors (3-bit RGB) (X, X, R1, G1, B1, R2,G2,B2)*/
#define COLOR_BLACK		0x00
#define COLOR_WHITE		0x3F
#define COLOR_RED		0x24
#define COLOR_GREEN		0x12
#define COLOR_BLUE		0x09
#define COLOR_YELLOW	0x36
#define COLOR_PINK		0x2D
#define COLOR_CYAN		0x1A

/* Display dimensions */
#define DISPLAY_SIZE_X		320						// number of columns
#define DISPLAY_SIZE_Y		480						// number of rows
#define DISPLAY_MAX_X		DISPLAY_SIZE_X - 1		// maximum column number
#define DISPLAY_MAX_Y		DISPLAY_SIZE_Y - 1		// maximum row number
#define DISPLAY_CACHE_MEM	(DISPLAY_SIZE_X * DISPLAY_SIZE_Y)	// total number of pixels

/**
 * @brief Initialize display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 */
void Display_Init(SPI_HandleTypeDef *hspi);

/**
 * @brief Hardware reset on display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 */
void Display_HWReset(SPI_HandleTypeDef *hspi);

/**
 * @brief Transmit command to display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param cmd (uint8_t) - cmd to send to display
 */
void Display_TransmitCmd(SPI_HandleTypeDef *hspi, uint8_t cmd);

/**
 * @brief Transmit single parameter to display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param param (uint8_t) - data to set as parameter
 */
void Display_TransmitParam(SPI_HandleTypeDef *hspi, uint8_t param);

/**
 * @brief Transmit command followed by single parameter to display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param cmd (uint8_t) - command to send
 * @param param (uint8_t) - parameter to send
 */
void Display_TransmitCmdParam(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t param);

/**
 * @brief Set window of display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param xs (uint16_t) - starting x-column (0 <= xs <= xe)
 * @param ys (uint16_t) - starting y-page (0 <= ys <= ye)
 * @param xe (uint16_t) - ending x-column (xs <= xe <= DISPLAY_MAX_X)
 * @param ye (uint16_t) - ending y-page (ys <= ye <= DISPLAY_MAX_Y)
 */
void Display_SetWindow(SPI_HandleTypeDef *hspi, uint16_t xs, uint16_t ys,
						uint16_t xe, uint16_t ye);

/**
 * @brief Draw rectangle on display
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param x (uint16_t) - top-left corner x-position
 * @param y (uint16_t) - top-left corner y-position
 * @param w (uint16_t) - width of rectangle
 * @param h (uint16_t) - height of rectangle
 */
void Display_DrawRect(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y,
						uint16_t w, uint16_t h, uint8_t color);

/**
 * @brief Draw pixel of specified color at coordinate (x,y)
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param x (uint16_t) - x-coordinate of pixel to change (0 <= x <= DISPLAY_MAX_X)
 * @param y (uint16_t) - y-coordinate of pixel to change (0 <= y <= DISPLAY_MAX_Y)
 * @param color (uint8_t) - new color of pixel
 */
void Display_DrawPixel(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y, uint8_t color);

/**
 * @brief Fill entire screen with one color
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param color (uint8_t) - color to fill display
 */
void Display_FillScreen(SPI_HandleTypeDef *hspi, uint8_t color);

/**
 * @brief Clear display and set it to a specified color
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param color (uint16_t) - new color for display
 */
void Display_ClearScreen(SPI_HandleTypeDef *hspi, uint16_t color);

/**
 * @brief Display an image at specified coordinates with specified size
 * @param hspi (SPI_HandleTypeDef *) - pointer to SPI handle
 * @param x (uint16_t) - x-coordinate of image top-left corner
 * @param y (uint16_t) - y-coordinate of image top-left corner
 * @param w (uint8_t) - image width
 * @param h (uint8_t) - image height
 * @param pixels (uint8_t *) - pointer to array containing pixel data
 *
 * Pixel data should be auto-generated with DisplayImageUtil.py script.
 */
void Display_Image(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y,
					uint16_t w, uint16_t h, uint8_t *pixels);

#endif /* INC_DISPLAY_H_ */
