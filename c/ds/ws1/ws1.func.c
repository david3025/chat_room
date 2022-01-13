#include <stdio.h> /*printf*/
#include <limits.h> /*CHAR_BIT*/
#include "bit_array .h"

#define WORD_ZISE 8
#define EIGHT_BYTES (int)(sizeof(bitsarr_t) * CHAR_BIT)


bitsarr_t BitsArrSetAll(bitsarr_t num)
{
	(void)num;
	return 0xFFFFFFFFFFFFFFFF;
}

bitsarr_t BitsArrResetAll(bitsarr_t num)
{
	(void)num;
	return 0x0;
}

bitsarr_t BitsArrSetOn(bitsarr_t num, size_t index)
{
	bitsarr_t mask = (bitsarr_t)1 << index;
	num |= mask;
	
	return num;
}

bitsarr_t BitsArrSetOff(bitsarr_t num, size_t index)
{
	num &= ~((bitsarr_t)1 << (index));
	
	return num;
}

int BitsArrGetVal(bitsarr_t num, size_t index)
{
	return ((num >> index) & (bitsarr_t)1);
}
/*-----------------------------------------------*/
int CountBitsON(int number)
{
	int count = 0;
	size_t i = 0;
	
	for (; i < sizeof(int) * 8; i++)
	{
		count += 1 & (number >> i);
	}
	
	return count;
}

size_t BitsArrCountOn(bitsarr_t num)
{
	size_t count = 0;
	
	while (num != 0)
	{
		num &= (num - 1);
		count++;
	}
	
	return count;
}


size_t BitsArrCountOnLUP(bitsarr_t number)
{
  unsigned char lookup_t[256] = {0}; 
  bitsarr_t i = 0; 
  int count = 0;
 
  for (; i < 256; i++)
  {
    lookup_t[i] = CountBitsON(i);
  }
 
  for (i = 1; i <= sizeof(bitsarr_t) && number; i++)
  {
    count += lookup_t[number & 255];
    number >>= 8;
  }
 
  return count;
}
/*-----------------------------------------------*/

size_t BitsArrCountOff(bitsarr_t number)
{
	size_t count = 0;
	int bits = sizeof(bitsarr_t) * CHAR_BIT;
	
	while(bits)
	{
		count += !((bitsarr_t)1 & number);
		number >>= 1;
		bits--;
	}
	
	return count;
}



/*-----------------------------------------------*/


bitsarr_t BitsArrFlip(bitsarr_t num, size_t index)
{
	num ^= ((bitsarr_t)1 << index);
	
	return num;
}

/*//////////////////////////////  LUT  ///////////////////////////////////*/
unsigned char BitsArrMirrorchar(unsigned char input) 
{
    size_t i = 0;
    unsigned char mirror = 0;
    
    for(; i < CHAR_BIT; ++i) 
    {
        mirror |= input & 1;
        mirror <<= 1;
        input >>= 1;
    }
    
    return mirror;
}

unsigned char InitializeMirrorLUT(const char befor_mirror)
{
	static unsigned char lookup_t[256] = {0}; 
	static int flag = 1;
	unsigned char after_mirror;
	size_t i = 0; 
	
	if (flag)
	{
		for (; i < 256; i++)
		{
			lookup_t[i] = BitsArrMirrorchar(i);
		}
		
		flag = 0;
	}
	
	after_mirror = lookup_t[(size_t)befor_mirror];
	
	return after_mirror;
}

bitsarr_t BitsArrMirrorLUT(bitsarr_t input) 
{
	size_t i = 0; 
  	bitsarr_t mirror = 0X0;
 
    mirror = (bitsarr_t)InitializeMirrorLUT(input & 255) << 8;
     
    for (; i < CHAR_BIT; i++)
    {
      mirror = (bitsarr_t)InitializeMirrorLUT(input & 255);
       input >>= 8;
       mirror <<= 8;
    }
    
   return mirror;
 
}
/*/////////////////////////////////////////////////////////////////////////*/

bitsarr_t BitsArrMirror(bitsarr_t input) 
{
    bitsarr_t mirror = 0;
    size_t i = 0;
   
   	for(; i < EIGHT_BYTES; ++i) 
    {
        mirror |= input & 1;
        mirror <<= 1;
        input >>= 1;
    }
    
    return mirror;
}

/*/////////////////////////////////////////////////////////////////////////*/

bitsarr_t BitsArrMirrorWitoutLoop(bitsarr_t num)
{
	num = (num & 0x00000000FFFFFFFF) << 32 | (num & 0xFFFFFFFF00000000) >> 32;
	num = (num & 0x0000FFFF0000FFFF) << 16 | (num & 0xFFFF0000FFFF0000) >> 16;
	num = (num & 0x00FF00FF00FF00FF) << 8  | (num & 0xFF00FF00FF00FF00) >> 8;
	
	return num;
}

/*-----------------------------------------------*/

bitsarr_t BitsArrRotR(bitsarr_t num, size_t rotations)
{
	size_t rot_without_rest = rotations % EIGHT_BYTES;
	bitsarr_t save_and_bits = num << (EIGHT_BYTES - rot_without_rest);
	
	num >>= rot_without_rest;
	
	return num ^ save_and_bits;
}

bitsarr_t BitsArrRotL(bitsarr_t num, size_t rotations)
{
	size_t rot_without_rest = rotations % EIGHT_BYTES;
	bitsarr_t save_and_bits = num >> (EIGHT_BYTES - rot_without_rest);
	
	num <<= rot_without_rest;
	
	return num ^ save_and_bits;
}

/*----------------------------------------------*/

void BitsArrToString(bitsarr_t num, char *buffer)
{
	size_t bites = EIGHT_BYTES;
	
	while (bites)
	{
		bites--;
		*(buffer++) = (char)('0' + (int)((num >> bites) & 1));
	}
	
	*buffer = '\0';
}
















