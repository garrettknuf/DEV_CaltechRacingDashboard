/**
 * @file main.c
 * @brief Main file for ILI94868 Display Driver Demo
 *
 * @author Garrett Knuf
 * @date 3/29/2024
 */

/* Auto-generated includes */
#include "main.h"

/* User-defined includes */
#include "display.h"
#include "demo.h"
#include "init.h"
#include "img.h"

extern SPI_HandleTypeDef hspi2;

int main(void)
{
	/* Reset of all peripherals, initializes the flash interface and the systick */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_SPI2_Init();

	/* Initialize display */
	Display_Init(&hspi2);

	/* Display Caltech Racing Logo with black background */
	Display_FillScreen(&hspi2, COLOR_BLACK);
	Display_Image(&hspi2, 120, 20, 87, 435, caltech_racing_logo_img);

	/* Infinite main loop */
	while (1)
	{
		// demo_display_fill(&hspi2);
		// demo_display_rect(&hspi2);
		// HAL_Delay(2000);
	}

}
