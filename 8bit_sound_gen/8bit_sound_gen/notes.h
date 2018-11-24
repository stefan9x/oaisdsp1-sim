/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   notes.c                                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*    TO DO                                                                  */
/*                                                                           */
/*   Author  : Dejan Bokan                                                   */
/*                                                                           */
/*****************************************************************************/
#ifndef NOTES_H_
#define NOTES_H_

typedef enum
{
	A1 = 0,
	B1,
	C2,
	CSHARP2,
	D2,
	DSHARP2,
	E2,
	F2,
	FSHARP2,
	G2,
	GSHARP2,
	A2,
	ASHARP2,
	B2,
	C3,
	CSHARP3,
	D3,
	DSHARP3,
	E3,
	F3,
	FSHARP3,
	G3,
	GSHARP3,
	A3,
	ASHARP3,
	B3,
	C4,
	CSHARP4,
	D4,
	DSHARP4,
	E4,
	F4,
	FSHARP4,
	G4,
	GSHARP4,
	A4,
	ASHARP4,
	B4,
	C5,
	CSHARP5,
	D5,
	DSHARP5,
	E5,
	F5,
	FSHARP5,
	G5,
	GSHARP5,
	A5,
	ASHARP5,
	B5,
	C6,
	CSHARP6,
	D6,
	DSHARP6,
	E6,
	F6,
	FSHARP6,
	G6,
	GSHARP6,
	A6,
	ASHARP6,
	B6,
	C7,
	CSHARP7,
	D7,
	DSHARP7,
	E7,
	F7,
	FSHARP7,
	G7,
	GSHARP7,
	A7,
	ASHARP7,
	B7
} notes_t;

float note_to_freq(notes_t note);
const char* note_to_string(notes_t note);

#endif /* NOTES_H_ */
