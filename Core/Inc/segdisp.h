/*
 * @file segdisp.h
 * @brief Segmented Display utility
 *
 * @author Garrett Knuf
 * @date 4/15/2024
 */

#ifndef INC_SEGDISP_H_
#define INC_SEGDISP_H_

/**
 * @brief Initialize segmented display.
 */
void SegDisp_Init(void);

/**
 * @brief Set number on segmented display to specified value.
 * @param value (uint16_t) - value to set display to
 */
void SegDisplay_SetNumber(uint16_t num);

#endif /* INC_SEGDISP_H_ */
