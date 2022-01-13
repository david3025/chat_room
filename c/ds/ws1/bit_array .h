#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h>

/*
	OL 109
	24/8/2021
	
	version: 2
*/

typedef unsigned long bitsarr_t;

bitsarr_t BitsArrSetAll(bitsarr_t);
bitsarr_t BitsArrResetAll(bitsarr_t);
bitsarr_t BitsArrSetOn(bitsarr_t, size_t index);
bitsarr_t BitsArrSetOff(bitsarr_t, size_t index);
int BitsArrGetVal(bitsarr_t, size_t index);
size_t BitsArrCountOn(bitsarr_t num);
size_t BitsArrCountOnLUP(bitsarr_t number);
size_t BitsArrCountOff(bitsarr_t num);
bitsarr_t BitsArrFlip(bitsarr_t num, size_t index);
bitsarr_t BitsArrMirror(bitsarr_t);
bitsarr_t BitsArrMirrorWitoutLoop(bitsarr_t input);
void BitsArrToString(bitsarr_t, char *buffer);
bitsarr_t BitsArrRotR(bitsarr_t, size_t rotations);
bitsarr_t BitsArrRotL(bitsarr_t, size_t rotations);
void BitsArrToString(bitsarr_t num, char *buffer);
bitsarr_t BitsArrMirrorLUT(bitsarr_t input);



bitsarr_t BitsArrSetBit(bitsarr_t, size_t index, int value);


#endif /* __BIT_ARRAY_H__ */




