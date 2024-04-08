/*
 * @file pot.h
 * @brief Potentiometer utility
 *
 * @author Garrett Knuf
 * @date 4/8/2024
 */

#ifndef INC_POT_H_
#define INC_POT_H_

typedef enum {
	POT_ID_1,
	POT_ID_2,
	POT_CNT
} pot_id_t;

/**
 * @brief Initialize potentiometer controllers
 */
void Pot_Init(void);

/**
 * @brief Samples next pot. Should be called every 20ms.
 */
void Pot_Sample(void);


#endif /* INC_POT_H_ */
