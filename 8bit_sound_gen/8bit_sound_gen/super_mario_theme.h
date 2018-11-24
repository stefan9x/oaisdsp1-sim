/*
 * super_mario_theme.h
 *
 *  Created on: 14 Nov 2018
 *      Author: dbokan
 */

#ifndef SUPER_MARIO_THEME_H_
#define SUPER_MARIO_THEME_H_

#include "notes.h"

typedef struct
{
	int duration;
	notes_t note;
	int time;
} tone_t;

extern const int superMarioThemeLength;

extern tone_t superMarioTriangle[291];
extern tone_t superMarioWhiteNoise[377];
extern tone_t superMarioSquare30[300];
extern tone_t superMarioSquare50[311];


#endif /* SUPER_MARIO_THEME_H_ */
