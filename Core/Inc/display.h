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
#define DISPLAY_SIZE_X		480						// number of columns
#define DISPLAY_SIZE_Y		320						// number of rows
#define DISPLAY_MAX_X		DISPLAY_SIZE_X - 1		// maximum column number
#define DISPLAY_MAX_Y		DISPLAY_SIZE_Y - 1		// maximum row number
#define DISPLAY_CACHE_MEM	(DISPLAY_SIZE_X * DISPLAY_SIZE_Y)	// total number of pixels

/**
 * @brief Initialize display
 */
void Display_Init(void);

/**
 * @brief Hardware reset on display
 */
void Display_HWReset(void);

/**
 * @brief Transmit command to display
 * @param cmd (uint8_t) - cmd to send to display
 */
void Display_TransmitCmd(uint8_t cmd);

/**
 * @brief Transmit single parameter to display
 * @param param (uint8_t) - data to set as parameter
 */
void Display_TransmitParam(uint8_t param);

/**
 * @brief Transmit command followed by single parameter to display
 * @param cmd (uint8_t) - command to send
 * @param param (uint8_t) - parameter to send
 */
void Display_TransmitCmdParam(uint8_t cmd, uint8_t param);

/**
 * @brief Set window of display
 * @param xs (uint16_t) - starting x-column (0 <= xs <= xe)
 * @param ys (uint16_t) - starting y-page (0 <= ys <= ye)
 * @param xe (uint16_t) - ending x-column (xs <= xe <= DISPLAY_MAX_X)
 * @param ye (uint16_t) - ending y-page (ys <= ye <= DISPLAY_MAX_Y)
 */
void Display_SetWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);

/**
 * @brief Send color data to display
 * @param npixels (uint32_t) - number of pixels to update
 * @param color (uint8_t) - color of pixels
 */
void Display_SendColor(uint32_t npixels, uint8_t color);

/**
 * @brief Send data to the display
 * @param data_len (uint32_t) - length of data to send
 * @param data (uint8_t *) - pointer to data to send
 */
void Display_SendData(uint32_t data_len, uint8_t *data);

#endif /* INC_DISPLAY_H_ */
