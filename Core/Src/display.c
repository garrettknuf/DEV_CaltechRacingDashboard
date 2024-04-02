/*
 * @file display.c
 * @brief Display interface for ILI9488
 *
 * @author Garrett Knuf
 * @date 3/29/2024
 */

/* User-defined includes */
#include "display.h"

/* Auto-generated includes */
#include "main.h"

void Display_Init(SPI_HandleTypeDef *hspi)
{
	/* Hardware reset display */
	Display_HWReset(hspi);

	/* Software reset */
	Display_TransmitCmd(hspi, DISPLAY_SWRESET);
	HAL_Delay(250);

	/* Exit sleep mode */
	Display_TransmitCmd(hspi, DISPLAY_SLEEPOUT);
	HAL_Delay(100);

	/* 4-line serial interface mode control */
	Display_TransmitCmdParam(hspi, DISPLAY_INTMCTRL, 0x00);

	/* 3-bit RGB interface pixel format */
	Display_TransmitCmdParam(hspi, DISPLAY_INTPXLFMT, 0x01);

	/* Memory access control sets scanning direction of frame memory */
	Display_TransmitCmdParam(hspi, DISPLAY_MEMACTRL, 0x08);

	/* TODO modify positive, negative, and digital gamma settings */

	/* Exit sleep mode */
	Display_TransmitCmd(hspi, DISPLAY_SLEEPOUT);
	HAL_Delay(250);

	/* Turn display on */
	Display_TransmitCmd(hspi, DISPLAY_DISPON);
}

void Display_HWReset(SPI_HandleTypeDef *hspi)
{
	/* Hold RESET pin LOW with delay */
	HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(DISPLAY_RESET_TIME_MS);

	/* Set RESET pin HIGH and wait for system reset to complete */
	HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(DISPLAY_RESET_TIME_MS);
}

void Display_TransmitCmd(SPI_HandleTypeDef *hspi, uint8_t cmd)
{
	/* DC/RS LOW since writing command */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_RESET);

	/* Set CS LOW */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write SPI data */
	HAL_SPI_Transmit(hspi, &cmd, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Set CS HIGH */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_TransmitParam(SPI_HandleTypeDef *hspi, uint8_t param)
{
	/* DC/RS HIGH since writing data */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write SPI data */
	HAL_SPI_Transmit(hspi, &param, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Set CS HIGH */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_TransmitCmdParam(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t param)
{
	/* Send command */
	Display_TransmitCmd(hspi, cmd);

	/* Send parameter */
	Display_TransmitParam(hspi, param);
}

void Display_SetWindow(SPI_HandleTypeDef *hspi, uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	/* Check coordinate are not out of range */
	if ((xs > xe) || (xe > DISPLAY_MAX_X) || (ys > ye) || (ye > DISPLAY_MAX_Y)) {
		/* Error so do nothing */
		return;
	}

	/* Set column range */
	Display_TransmitCmd(hspi, DISPLAY_COLADDRSET);

	/* Set DC/RS LOW since transmitting date */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Hold CS LOW until all parameters have been sent */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write column start and end data */
	uint8_t byte = xs >> 8;	// SC[15:8]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xs & 0xFF;		// SC[7:0]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xe >> 8;			// EC[15:8]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xe & 0xFF;		// EC[7:0]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Last parameter sent so end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

	/* Set page range */
	Display_TransmitCmd(hspi, DISPLAY_PGADDRSET);

	/* Set DC/RS LOW since transmitting date */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Begin multi-parameter transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write page start and end data */
	byte = ys >> 8;		// SP[15:8]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ys & 0xFF;	// SP[7:0]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ye >> 8;		// EP[15:8]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ye & 0xFF;	// EP[7:0]
	HAL_SPI_Transmit(hspi, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Last parameter sent so end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_DrawRect(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
{
	/* Set window of rectangle */
	Display_SetWindow(hspi, x, y, x + w - 1, y + h - 1);

	/* Set up writing to frame buffer */
	Display_TransmitCmd(hspi, DISPLAY_MEMWR);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write the color to every pixel in the frame buffer. Since 3-bit RGB is
	 * used for color there is data for 2 pixels in each byte, hence divide
	 * the number of pixels to write to by 2 */
	for (uint32_t i = 0; i < w * h / 2; i++) {
		HAL_SPI_Transmit(hspi, &color, sizeof(uint8_t), SPI_TIMEOUT_MS);
	}

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_DrawPixel(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y, uint8_t color)
{
	/* Set window to single pixel */
	Display_SetWindow(hspi, x, x, y, y);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(hspi, &color, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_FillScreen(SPI_HandleTypeDef *hspi, uint8_t color)
{
	/* Set entire display as window */
	Display_SetWindow(hspi, 0, 0, DISPLAY_MAX_X, DISPLAY_MAX_Y);

	/* Set up writing to frame buffer */
	Display_TransmitCmd(hspi, DISPLAY_MEMWR);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write the color to every pixel in the frame buffer. Since 3-bit RGB
	 * stores color data for 2 pixels in 1 byte, the total number of data
	 * bytes is the total number of pixels divided by 2 */
	for (uint32_t i = 0; i < DISPLAY_CACHE_MEM / 2; i++) {
		HAL_SPI_Transmit(hspi, &color, sizeof(uint8_t), SPI_TIMEOUT_MS);
	}

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}


void Display_ClearScreen(SPI_HandleTypeDef *hspi, uint16_t color) {
	// TODO
}

void Display_Image(SPI_HandleTypeDef *hspi, uint16_t x, uint16_t y,
					uint16_t w, uint16_t h, uint8_t *pixels) {

	/* Set window to display image */
	Display_SetWindow(hspi, x, y, x+w-1, y+h-1);

	/* Set up writing to frame buffer */
	Display_TransmitCmd(hspi, DISPLAY_MEMWR);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	for (uint32_t i = 0; i < w*h / 2; i++) {
		HAL_SPI_Transmit(hspi, &(pixels[i]), sizeof(uint8_t), SPI_TIMEOUT_MS);
	}

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}
