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

/* External reference to display SPI handle */
extern SPI_HandleTypeDef hspi2;

void Display_Init(void)
{
	/* Hardware reset display */
	Display_HWReset();

	/* Software reset */
	Display_TransmitCmd(DISPLAY_SWRESET);
	HAL_Delay(250);

	/* Exit sleep mode */
	Display_TransmitCmd(DISPLAY_SLEEPOUT);
	HAL_Delay(100);

	/* 4-line serial interface mode control */
	Display_TransmitCmdParam(DISPLAY_INTMCTRL, 0x00);

	/* 3-bit RGB interface pixel format */
	Display_TransmitCmdParam(DISPLAY_INTPXLFMT, 0x01);

	/* Memory access control sets scanning direction of frame memory */
	// was 0x08
	Display_TransmitCmdParam(DISPLAY_MEMACTRL, 0x08);

	/* TODO modify positive, negative, and digital gamma settings */

	/* Exit sleep mode */
	Display_TransmitCmd(DISPLAY_SLEEPOUT);
	HAL_Delay(250);

	/* Turn display on */
	Display_TransmitCmd(DISPLAY_DISPON);
}

void Display_HWReset(void)
{
	/* Hold RESET pin LOW with delay */
	HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(DISPLAY_RESET_TIME_MS);

	/* Set RESET pin HIGH and wait for system reset to complete */
	HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(DISPLAY_RESET_TIME_MS);
}

void Display_TransmitCmd(uint8_t cmd)
{
	/* DC/RS LOW since writing command */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_RESET);

	/* Set CS LOW */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write SPI data */
	HAL_SPI_Transmit(&hspi2, &cmd, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Set CS HIGH */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_TransmitParam(uint8_t param)
{
	/* DC/RS HIGH since writing data */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write SPI data */
	HAL_SPI_Transmit(&hspi2, &param, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Set CS HIGH */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_TransmitCmdParam(uint8_t cmd, uint8_t param)
{
	/* Send command */
	Display_TransmitCmd(cmd);

	/* Send parameter */
	Display_TransmitParam(param);
}

void Display_SetWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	/* Check coordinate are not out of range */
	if ((xs > xe) || (xe > DISPLAY_MAX_X) || (ys > ye) || (ye > DISPLAY_MAX_Y)) {
		/* Error so do nothing */
		return;
	}

	/* Set column range */
	Display_TransmitCmd(DISPLAY_COLADDRSET);

	/* Set DC/RS LOW since transmitting date */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Hold CS LOW until all parameters have been sent */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write column start and end data */
	uint8_t byte = ys >> 8;	// SC[15:8]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ys & 0xFF;		// SC[7:0]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ye >> 8;			// EC[15:8]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = ye & 0xFF;		// EC[7:0]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Last parameter sent so end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

	/* Set page range */
	Display_TransmitCmd(DISPLAY_PGADDRSET);

	/* Set DC/RS LOW since transmitting date */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Begin multi-parameter transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* Write page start and end data */
	byte = xs >> 8;		// SP[15:8]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xs & 0xFF;	// SP[7:0]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xe >> 8;		// EP[15:8]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);
	byte = xe & 0xFF;	// EP[7:0]
	HAL_SPI_Transmit(&hspi2, &byte, sizeof(uint8_t), SPI_TIMEOUT_MS);

	/* Last parameter sent so end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}


void Display_SendColor(uint32_t npixels, uint8_t color) {
	/* Set up writing to frame buffer */
	Display_TransmitCmd(DISPLAY_MEMWR);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	/* If odd number of pixels pad a data byte to fill byte */
	if (npixels % 2 != 0) {
		npixels++;
	}

	/* 2 pixel data stored per byte, so divide npixels by 2 */
	for (uint32_t i = 0; i < npixels / 2; i++) {
		HAL_SPI_Transmit(&hspi2, &color, sizeof(uint8_t), SPI_TIMEOUT_MS);
	}

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

void Display_SendData(uint32_t data_len, uint8_t *data) {

	/* Set up writing to frame buffer */
	Display_TransmitCmd(DISPLAY_MEMWR);

	/* Set up sending data to display */
	HAL_GPIO_WritePin(SPI_DCRS_GPIO_Port, SPI_DCRS_Pin, GPIO_PIN_SET);

	/* Set CS LOW to begin transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	for (uint32_t i = 0; i < data_len; i++) {
		HAL_SPI_Transmit(&hspi2, &(data[i]), sizeof(uint8_t), SPI_TIMEOUT_MS);
	}

	/* Set CS HIGH to end transaction */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}
