/*
 * @file can.h
 * @brief CAN utility
 *
 * @author Garrett Knuf
 * @date 4/15/2024
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

/**
 * @brief Initialize CAN interface.
 */
void Can_Init(void);

/**
 * @brief Event handler for CAN data events.
 * @param data (void *) - pointer to data relevant to CAN event
 */
void Can_EventHandler(void *data);

#endif /* INC_CAN_H_ */
