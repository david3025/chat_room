#include <stdio.h>/*printf*/
#include "bit_array .h"
#include <limits.h>/*CHAR_BIT*/

#define EIGHT_BYTES sizeof(bitsarr_t) * CHAR_BIT

void Test(int result);
void TestBitsArrSetAll();
void TestBitsArrResetAll();
void TestBitsArrSetOn();
void TestBitsArrSetOff();
void TestBitsArrGetVal();
void TestBitsArrCountOn();
void TestBitsArrCountOff();
void TestBitsArrFlip();
int TestBitsArrMirror(bitsarr_t input);
int TestBitsArrMirrorWitoutLoop(bitsarr_t input);
void SuperTestBitsArrMirror();
void SuperTestBitsArrMirrorWitoutLoop();
void TestBitsArrRotLandR();
int TestBitsArrMirrorLUT(bitsarr_t input);
void SuperTestBitsArrMirrorLUT();

int main()
{
	SuperTestBitsArrMirrorLUT();
	return 0;
}


void Test(int result)
{
	if(result)
	{
		printf("Success\n");		
	}
	else
	{
		printf("Fails\n");				
	}
}

void TestBitsArrSetAll()
{
	bitsarr_t num = 11;
	Test(BitsArrSetAll(num) == 0xFFFFFFFFFFFFFFFF);
	Test(BitsArrSetAll(0xFFFFFFFFFFFFFFFF) == 0xFFFFFFFFFFFFFFFF);
}

void TestBitsArrResetAll()
{
	bitsarr_t num = 11;
	Test(BitsArrResetAll(num) == 0x0);
}

void TestBitsArrSetOn()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrSetOn(num, 2) == 15);
	test *= (BitsArrSetOn(num, 3) == 11);
	test *= (BitsArrSetOn(0x18403C000, 3) == 0x18403C008);
	
	Test(test);
}

void TestBitsArrSetOff()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrSetOff(num, 3) == 3);
	test *= (BitsArrSetOff(num, 2) ==11);
	
	Test(test);
}

void TestBitsArrGetVal()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrGetVal(num, 0));
	test *= (!BitsArrGetVal(num, 2));
	test *= (BitsArrGetVal(0x18403C008, 3));
	test *= (!BitsArrGetVal(0x18403C008, 2));
	
	Test(test);


}

void TestBitsArrCountOn()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrCountOn(num) == 3);
	test *= (BitsArrCountOn(0) == 0);
	test *= (BitsArrCountOn(0xFFFFFFFFFFFFFFFF) == 64);
	test *= (BitsArrCountOn(0x18403C008) == 8);
		
	Test(test);
}

void TestBitsArrCountOff()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrCountOff(num) == 61);
	test *= (BitsArrCountOff(0) == 64);
	test *= (BitsArrCountOff((bitsarr_t)-1) == 0);
	test *= (BitsArrCountOn(0x10871FC0) == 17);	
	Test(test);
}

void TestBitsArrFlip()
{
	int test = 1;
	bitsarr_t num = 11;
	
	test *= (BitsArrFlip(num, 2) == 15);
	test *= (BitsArrFlip(num, 3) == 3);
	test *= (BitsArrFlip(0,0) == 1);
	test *= (BitsArrFlip(1,0) == 0);
	test *= (BitsArrFlip(1,0) == 0);
	
	Test(test);
}
/*--------------------------------------------------*/

int TestBitsArrMirror(bitsarr_t input)
{
	bitsarr_t returnval = BitsArrMirror(input);
	size_t i = 0;
	int compare = 1;
	
	for(; i < sizeof(bitsarr_t) * 8; ++i) 
    {
        bitsarr_t input_bit1 = (input >> i) & 1;
        bitsarr_t returnval_bit = (returnval >> (7 - i)) & 1;
        
        compare ^= !(input_bit1 ^ returnval_bit);
	 }
    
    return compare;
}

void SuperTestBitsArrMirror()
{
	Test(TestBitsArrMirror(0));
	Test(TestBitsArrMirror(255));
	Test(TestBitsArrMirror(128));
}

int TestBitsArrMirrorWitoutLoop(bitsarr_t input)
{
	bitsarr_t returnval = BitsArrMirrorWitoutLoop(input);
	size_t i = 0;
	int compare = 1;
	
	for(; i < sizeof(bitsarr_t) * 8; ++i) 
    {
        bitsarr_t input_bit1 = (input >> i) & 1;
        bitsarr_t returnval_bit = (returnval >> (7 - i)) & 1;
        
        compare ^= !(input_bit1 ^ returnval_bit);
	 }
    
    return compare;
}

void SuperTestBitsArrMirrorWitoutLoop()
{
	Test(TestBitsArrMirrorWitoutLoop(0));
	Test(TestBitsArrMirrorWitoutLoop(255));
	Test(TestBitsArrMirrorWitoutLoop(128));
}
/*--------------------------------------------------*/

void TestBitsArrRotLandR()
{
	int test = 1;
	bitsarr_t num = 124131;
	
	test *= (BitsArrRotL(num, 84) != BitsArrRotR(num, 84));
	test *= (BitsArrRotR(BitsArrRotL(num, 23), 23) == num);
	test *= (BitsArrRotL(0, 84) == BitsArrRotR(0, 84));
	
	Test(test);
}

/*-------------------- LUT ---------------------------*/

int TestBitsArrMirrorLUT(bitsarr_t input)
{
	bitsarr_t returnval = BitsArrMirrorLUT(input);
	size_t i = 0, j = EIGHT_BYTES -1;
	int compare = 1;
	
	input = BitsArrMirrorLUT(returnval);
	
	for(; i < EIGHT_BYTES; ++i, j--) 
    {
        compare *= !(((input << i) & 1) ^ ((returnval >> j) & 1)); 
        
    }
    
    return compare;
}


void SuperTestBitsArrMirrorLUT()
{
	Test(TestBitsArrMirrorLUT(0x0));
	Test(TestBitsArrMirrorLUT(0xF4));
	Test(TestBitsArrMirrorLUT(0x18403C000));
	Test(TestBitsArrMirrorLUT(0xFFFFFFFFFFFFFFFF));
	Test(TestBitsArrMirrorLUT(0xFFF4F03FC008));
}

/*---------------------------------------------------*/


