/*
 * @file speaker.h
 * @brief Speaker utility
 *
 * @author Garrett Knuf
 * @date 4/15/2024
 */

#ifndef INC_SPEAKER_H_
#define INC_SPEAKER_H_

typedef enum {
	NOTE_OFF,
	NOTE_A3,
	NOTE_A3_SHARP,
	NOTE_B3,
	NOTE_C3,
	NOTE_C3_SHARP,
	NOTE_D3,
	NOTE_D3_SHARP,
	NOTE_E3,
	NOTE_F3,
	NOTE_F3_SHARP,
	NOTE_G3,
	NOTE_G3_SHARP,
	NOTE_A4,
	NOTE_A4_SHARP,
	NOTE_B4,
	NOTE_C4,
	NOTE_C4_SHARP,
	NOTE_D4,
	NOTE_D4_SHARP,
	NOTE_E4,
	NOTE_F4,
	NOTE_F4_SHARP,
	NOTE_G4,
	NOTE_G4_SHARP,
} note_t;

/**
 * @brief Initialize speaker interface.
 */
void Speaker_Init(void);

/**
 * @brief Set tone (frequency of speaker)
 * @param note (note_t) - note to play
 */
void Speaker_SetTone(note_t note);

#endif /* INC_SPEAKER_H_ */
