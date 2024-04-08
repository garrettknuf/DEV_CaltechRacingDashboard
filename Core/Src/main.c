/**
 * @file main.c
 * @brief Main file for ILI94868 Display Driver Demo
 *
 * @author Garrett Knuf
 * @date 3/29/2024
 */

/* Auto-generated includes */
#include "main.h"
#include "stm32f4xx_it.h"

/* User-defined includes */
#include "button.h"
#include "display.h"
#include "demo.h"
#include "encoder.h"
#include "init.h"
#include "led.h"
#include "gfx.h"
#include "img.h"
#include "pot.h"
#include "timer.h"
#include "ui.h"

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
	MX_TIM2_Init();
	MX_TIM3_Init();

	/* Turn off all LEDs */
	Led_Init();

	/* Reset button controllers */
	Button_Init();

	/* Initialize rotary encoder controllers */
	Encoder_Init();

	/* Initialize potentiometer controllers */
	Pot_Init();

	/* Initialize display */
	Display_Init();

	/* Initialize graphics unit */
	Gfx_Init();

	/* Initialize UI */
	UI_Init();

	/* Start interrupts from timer */
	Timer_EnableInterrupts();

	/* Infinite main loop */
	while (1)
	{

	}

}
