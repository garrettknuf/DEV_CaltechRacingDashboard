/*
 * @file img.c
 * @brief Pixel data for displaying images
 *
 * @author Garrett Knuf
 * @date 4/1/2024
 */


#ifndef INC_IMG_H_
#define INC_IMG_H_

#define CALTECH_RACING_LOGO_IMG_LEN 18923
#define DRIVE_MODE_BACKGROUND_IMG_LEN 76800

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t *data;
	uint32_t data_len;
} image_t;

#endif /* INC_IMG_H_ */
