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
#include "button.h"
#include "display.h"
#include "demo.h"
#include "init.h"
#include "led.h"
#include "gfx.h"
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

	/* Turn off all LEDs */
	Led_Init();

	/* Reset button controllers */
	Button_Init();

	/* Initialize display */
	Display_Init();

	/* Initialize graphics unit */
	Gfx_Init();

	/* Get reference to Caltech Racing Logo image*/
	extern uint8_t caltech_racing_logo_img[];

	image_t team_logo_img = {
			.x = 20,
			.y = 120,
			.w = 435,
			.h = 87,
			.data = caltech_racing_logo_img,
			.data_len = CALTECH_RACING_LOGO_IMG_LEN
	};

	/* Infinite main loop */
	while (1)
	{
		/* Show team logo */
		Gfx_DrawImage(&team_logo_img);
		HAL_Delay(2000);
		Gfx_DeleteImage(&team_logo_img);

		/* Count from 0 -9 */
		for (uint8_t count = 0; count < 10; count++) {
			Gfx_DrawDigit( 10, 40, count,  20, COLOR_RED);
			Gfx_DrawDigit( 40, 40, count,  35, COLOR_PINK);
			Gfx_DrawDigit( 80, 40, count,  50, COLOR_YELLOW);
			Gfx_DrawDigit(140, 40, count,  80, COLOR_GREEN);
			Gfx_DrawDigit(220, 40, count, 120, COLOR_CYAN);
			Gfx_DrawDigit(320, 40, count, 200, COLOR_BLUE);
			HAL_Delay(800);
		}

		/* Delete digits */
		Gfx_DrawDigit( 10, 40, -1,  20, COLOR_RED);
		Gfx_DrawDigit( 40, 40, -1,  35, COLOR_PINK);
		Gfx_DrawDigit( 80, 40, -1,  50, COLOR_YELLOW);
		Gfx_DrawDigit(140, 40, -1,  80, COLOR_GREEN);
		Gfx_DrawDigit(220, 40, -1, 120, COLOR_CYAN);
		Gfx_DrawDigit(320, 40, -1, 200, COLOR_BLUE);
	}

}
