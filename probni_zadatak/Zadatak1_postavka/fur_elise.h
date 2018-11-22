/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   fur_elise.h                                                             */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Notes for tune "Fur Elise"  by Ludwig van Beethoven                     */
/*                                                                           */
/*   Time and length are specified represented with number of                */
/*   blocks. Use Block Size to determine tempo.                              */
/*                                                                           */
/*   Author  : Dejan Bokan                                                   */
/*                                                                           */
/*****************************************************************************/

#ifndef FUR_ELISE_H_
#define FUR_ELISE_H_

#include "notes.h"
#include "tistdtypes.h"

typedef struct
{
	Int16 duration;
	notes_t note;
	Int32 time;
} tone_t;

extern tone_t furEliseNotes0[];
extern tone_t furEliseNotes1[];
extern tone_t furEliseNotes2[];
extern tone_t furEliseNotes3[];
extern tone_t furEliseNotes4[];

extern const Int32 furEliseLength;


#endif /* FUR_ELISE_H_ */
