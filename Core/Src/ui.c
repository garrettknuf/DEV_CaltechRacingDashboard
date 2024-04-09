/*
 * @file ui.c
 * @brief User Interface
 *
 * @author Garrett Knuf
 * @date 4/7/2024
 */

#include "gfx.h"
#include "img.h"

static uint32_t lap_time_start = 0;

#define BATTERY_ICON_WIDTH 76
#define BATTERY_ICON_HEIGHT 35
#define BATTERY_THRESHOLD_PCT_YELLOW 60
#define BATTERY_THRESHOLD_PCT_RED	 30

#define WHEEL_TEMP_THRESHOLD 80

/* Get reference to background image */
extern uint8_t drive_mode_background_img[];
image_t background_img = {
	.w = 480,
	.h = 320,
	.data = drive_mode_background_img,
	.data_len = DRIVE_MODE_BACKGROUND_IMG_LEN
};

void UI_Init(void) {
	Gfx_SetBackground(COLOR_BLACK);
	Gfx_DrawImage(&background_img, 0, 0);
}

void UI_Reset_Laptime(uint32_t time_elapsed) {
	lap_time_start = time_elapsed;
}

void UI_Update_Laptime(uint32_t time_elapsed) {
	uint8_t minutes = (time_elapsed - lap_time_start) / 60;
	uint8_t seconds = (time_elapsed - lap_time_start) % 60;

	Gfx_Draw7SegDigit(325, 260, minutes / 10, 40, COLOR_PINK);
	Gfx_Draw7SegDigit(355, 260, minutes % 10, 40, COLOR_PINK);
	Gfx_Draw7SegDigit(405, 260, seconds / 10, 40, COLOR_PINK);
	Gfx_Draw7SegDigit(435, 260, seconds % 10, 40, COLOR_PINK);
	Gfx_DrawFilledRect(390, 270, 5, 5, COLOR_PINK);
	Gfx_DrawFilledRect(390, 290, 5, 5, COLOR_PINK);
}

void UI_Update_BatteryPct(uint8_t battery_pct) {
	uint8_t color;
	if (battery_pct > BATTERY_THRESHOLD_PCT_YELLOW) {
		color = COLOR_GREEN;
	} else if (battery_pct > BATTERY_THRESHOLD_PCT_RED) {
		color = COLOR_YELLOW;
	} else {
		color = COLOR_RED;
	}

	uint8_t width = battery_pct * BATTERY_ICON_WIDTH / 100;
	Gfx_DrawFilledRect(295, 15, width, BATTERY_ICON_HEIGHT, color);
	Gfx_DrawFilledRect(295+width, 15, BATTERY_ICON_WIDTH - width, BATTERY_ICON_HEIGHT, COLOR_BLACK);

	/* Battery */
	Gfx_Draw7SegDigit(390, 20, battery_pct / 10, 25, COLOR_GREEN);
	Gfx_Draw7SegDigit(410, 20, battery_pct % 10, 25, COLOR_GREEN);
}

void UI_Update_RPM(uint16_t rpm) {
	Gfx_Draw7SegDigit(195, 260, rpm / 1000, 40, COLOR_GREEN);
	Gfx_Draw7SegDigit(220, 260, (rpm / 100) % 10, 40, COLOR_GREEN);
	Gfx_Draw7SegDigit(245, 260, (rpm % 100) / 10, 40, COLOR_GREEN);
	Gfx_Draw7SegDigit(270, 260, rpm % 10, 40, COLOR_GREEN);
}

void UI_Update_WheelTemps(uint8_t front_left, uint8_t front_right,
		  	  	  	  	  uint8_t back_left, uint8_t back_right) {
	Gfx_Draw7SegDigit(5, 230, front_left / 10, 25, COLOR_CYAN);
	Gfx_Draw7SegDigit(30, 230, front_left % 10, 25, COLOR_CYAN);

	Gfx_Draw7SegDigit(87, 230, front_right / 10, 25, COLOR_CYAN);
	Gfx_Draw7SegDigit(112, 230, front_right % 10, 25, COLOR_CYAN);

	Gfx_Draw7SegDigit(5, 280, back_left / 10, 25, COLOR_CYAN);
	Gfx_Draw7SegDigit(30, 280, back_left % 10, 25, COLOR_CYAN);

	Gfx_Draw7SegDigit(87, 280, back_right / 10, 25, COLOR_CYAN);
	Gfx_Draw7SegDigit(112, 280, back_right % 10, 25, COLOR_CYAN);
}

void UI_Update_Speedometer(uint8_t speed) {
	Gfx_Draw7SegDigit(150, 70, speed / 10, 120, COLOR_YELLOW);
	Gfx_Draw7SegDigit(240, 70, speed % 10, 120, COLOR_YELLOW);
}

void UI_Update_CoolingTemp(uint8_t temp) {
	Gfx_Draw7SegDigit(60, 15, temp / 10, 25, COLOR_CYAN);
	Gfx_Draw7SegDigit(81, 15, temp % 10, 25, COLOR_CYAN);
}

