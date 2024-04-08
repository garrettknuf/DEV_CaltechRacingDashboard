/*
 * @file encoder.h
 * @brief Encoder utility
 *
 * @author Garrett Knuf
 * @date 4/8/2024
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

typedef enum {
	ENC_ID_1,
	ENC_CNT
} encoder_id_t;

/**
 * @brief Initialize encoder controllers
 */
void Encoder_Init(void);

/**
 * @brief Event handler to debounce encoder values
 */
void Encoder_Debounce(void);

#endif /* INC_ENCODER_H_ */
