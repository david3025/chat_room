/*tuvia & 15 and ron */

#include <stdio.h>/*printf*/
#include <math.h>/*pow*/
#include <stdint.h>/*uint32_t*/

long Pow2(unsigned int x, unsigned int y);
int IfPowOf2(unsigned int n);
int IfPowOf2Loop(unsigned int n);
int AddOne(int x);
int CountBistInUnsignedInt(unsigned int n);
int ONlyHave3Bits(unsigned int array[], int size);
unsigned char Mirror8(unsigned char input);
int AreBits2and6ON(unsigned char input);
int Bits2or6(unsigned char input);
unsigned char Swap2Bit(unsigned char n);
void SwapBitwise(int *x, int *y);

/*--------------*/
void PrintBin(unsigned n);
void Test(int result);
void PrintFloat(float number);
/*--------------*/


void TestPow2(unsigned int x, unsigned int y, unsigned int expected);
void TestIfPowOf2(unsigned int n, int expected);
void TestIfPowOf2Loop(unsigned int n);
void TestAddOne(int x, int expected);
void TestONlyHave3Bits(unsigned int array[], int size,int expected);
void TestMirror8(unsigned char input);
void TestAreBits2and6ON(unsigned char input, int expected);
void TestBits2or6(unsigned char input, int expected);
void TestSwap2Bit(unsigned char n, unsigned char expected);
unsigned int DividedBy16(unsigned int number);
void TestSwapBitwise(int x, int y);
int CountBits( int n);
void TestCountBits(int n, int expected);
int CountBitsFloat(float number);
int countSetBits(unsigned int n);

int TestMirror8new(unsigned char input);
void SuperTestMirror8new();

void SuperTestIfPowOf2();
void SuperTestIfPowOf2Loop();
void SuperTestAddOne();
void SuperTestONlyHave3Bits();
void SuperTestMirror8();
void SuperTestBits2or6();
void SuperTestAreBits2and6ON();
void SuperTestSwap2Bit();
void SuperTestDividedBy16();

void SuperTestPow2();
void SuperTestCountBits();



int main()
{	
	PrintFloat(31);
	return 0;
}
/*---------------------------------------------*/
int countSetBits(unsigned int number)
{
  unsigned char lookup_t[256] = {0}; 
  unsigned int i; 
  int count = 0;
 
  for (i = 0; i < 256; i++)
  {
    lookup_t[i] = CountBits(i);
  }
 
  for (i = 1; i <= sizeof(int) && number; i++)
  {
    count += lookup_t[number & 255];
    number >>= 8;
  }
 
  return count;
}

void TestcountSetBits(unsigned int number, int expected)
{
	Test(countSetBits(number) == expected);
} 

void SuperTestcountSetBits()
{
	printf("<< Test CountBits >>\n");
	TestCountBits(4134321,13);
	TestCountBits(2232,5);
	TestCountBits(1,1);
	TestCountBits(0,0);
	TestCountBits(45621378,8);
}

/*---------------------------------------------*/
int CountBitsFloat(float number)
{
	return CountBits((int)number);
}
/*----------*/
int CountBits(int number)
{
	int count = 0;
	size_t i = 0;
	
	for (; i < sizeof(int) * 8; i++)
	{
		count += 1 & (number >> i);
	}
	
	return count;
}

void TestCountBits(int number, int expected)
{
	Test(CountBits(number) == expected);
} 

void SuperTestCountBits()
{
	printf("<< Test CountBits >>\n");
	TestCountBits(270,4);
	TestCountBits(300,4);
	TestCountBits(1,1);
	TestCountBits(0,0);
	TestCountBits(-1,32);
	TestCountBits(45678,9);
	TestCountBits(-45678,23);
}
/*----------------------------------------------*/
long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

void TestPow2(unsigned int x, unsigned int y, unsigned int expected)
{
	
	Test(expected == Pow2(x, y));
}

void SuperTestPow2()
{
	printf("<< Test Pow2 >>\n");
	TestPow2(2,16,131072);
	TestPow2(0,1,0);
	TestPow2(1,0,1);

}
/*----------------------------------------------*/
int IfPowOf2(unsigned int input)
{
	int power = 0;
	
	if (0 != input && 0 == (input & (input-1) ))
	{
		power = 1;
	}
	
	return power;
}

void TestIfPowOf2(unsigned int input, int expected)
{
		Test(IfPowOf2(input) == expected);
}

void SuperTestIfPowOf2()
{
	size_t i = 0;
	unsigned int result_for_all_exp = 1;

	for (; i < sizeof(int)*8; i++)
	{
		result_for_all_exp *= IfPowOf2((unsigned int)Pow2(1,i));
	}

	printf("<< Test If N Is Pow Of 2 >>\n");	
	
	TestIfPowOf2(result_for_all_exp,1);
	TestIfPowOf2(143325,0);
	TestIfPowOf2(-1,0);
	TestIfPowOf2(0,0);
}

/*-----------*/

int IfPowOf2Loop(unsigned int n)
{
	size_t i = 1;
	unsigned int result = 0;
	
	for (; i < sizeof(unsigned int) * 8; i++)
	{
		if (n == ((unsigned int)1 << i))
		{
			result = 1;
			break;
		}
	}
	
	return result;
}

void TestIfPowOf2Loop(unsigned int input)
{
	Test(IfPowOf2Loop(input) == IfPowOf2(input));
}

void SuperTestIfPowOf2Loop()
{
	printf("<< Test If N Is Pow Of 2 with loop >>\n");		
	TestIfPowOf2Loop(4114);
	TestIfPowOf2Loop(-1);
	TestIfPowOf2Loop(16);
	TestIfPowOf2Loop(1024);
	TestIfPowOf2Loop(-3411);
}
/*----------------------------------------------*/
int AddOne(int input)
{
    int base = 1;
  
    while ( input & base )
    {
        input = input ^ base;
        base = base << 1;
    }

	 return input ^ base;
}

void TestAddOne(int input, int expected)
{
	Test(expected == AddOne(input));
}

void SuperTestAddOne()
{
	TestAddOne(0,1);
	TestAddOne(-1,0);	
	TestAddOne(42949672,42949673);
	TestAddOne(1,2);
	TestAddOne(-20,-19);	
}

/*----------------------------------------------*/
int ONlyHave3Bits(unsigned int array[], int size)
{
	int i = 0;
	int sum_of_elements_with_3_bits  = 0;
	
	for(; i < size; i++)
	{
		if(3 == CountBistInUnsignedInt(array[i]))
		{
			printf("%d,", array[i]);
			
			sum_of_elements_with_3_bits++;
		}
		
	}
	return sum_of_elements_with_3_bits;
}

void TestONlyHave3Bits(unsigned int array[], int size, int expected)
{
	
	Test(ONlyHave3Bits(array, size) == expected);
}

void SuperTestONlyHave3Bits()
{
	unsigned int array[] = {11,0,6,14,64};
	TestONlyHave3Bits(array, 5, 2);
}
/*--------------------------------------------------------------*/
unsigned char Mirror8(unsigned char input) {
    
    unsigned char mirror = 0;
    size_t i = 0;
    
    for(; i < sizeof(unsigned char) * 8; ++i) 
    {
        char bit = input & 1;
        
        mirror <<= 1;
        mirror += bit;   
        input >>= 1;
    }
    
    return mirror;
}

int TestMirror8new(unsigned char input)
{
	unsigned char returnval = Mirror8(input);
	int i = 0;
	int compare = 1;
	
	for(; i < (char)sizeof(unsigned char) * 8; ++i) 
    {
        unsigned char input_bit1 = (input >> i) & 1;
        unsigned char returnval_bit = (returnval >> (7 - i)) & 1;
        
        compare ^= !(input_bit1 ^ returnval_bit);
	 }
    
    return compare;
}

void SuperTestMirror8new()
{
	Test(TestMirror8new(0));
	Test(TestMirror8new(255));
	Test(TestMirror8new(128));
}

/*-------------------------------------------------------------*/
int AreBits2and6ON(unsigned char input)
{
	int mask2 =(input >> 1) & 1;
	int mask6 =(input >> 5) & 1;
	
	return (mask2 & mask6);	
}

void TestAreBits2and6ON(unsigned char input,  int expected)
{
	Test(AreBits2and6ON(input) == expected);
}

void SuperTestAreBits2and6ON()
{
	TestAreBits2and6ON(0, 0);
	TestAreBits2and6ON(34, 1);
	TestAreBits2and6ON(29, 0);	
}
/*-----------------*/
int Bits2ord6(unsigned char input)
{
	int mask2 =(input >>1)&1;
	int mask6 =(input >>5)&1;
	
	return (mask2 | mask6);
}

void TestBits2or6(unsigned char input, int expected)
{
	Test(Bits2ord6(input) == expected);
}

void SuperTestBits2or6()
{
	TestBits2or6(0, 0);
	TestBits2or6(32, 1);
	TestBits2or6(29, 0);	
}

/*-------------------------------------------------------*/

unsigned char Swap2Bit(unsigned char input)
{
    unsigned char bit_3 = (input >> 3) & 1;
    unsigned char bit_5 = (input >> 5) & 1;
    unsigned char swich = bit_3 ^ bit_5;

    input  = input ^ (swich << 3);
    input  = input ^ (swich << 5);

    return input;

}

void TestSwap2Bit(unsigned char number, unsigned char expected)
{
	Test(Swap2Bit(number) == expected);
}

void SuperTestSwap2Bit()
{
	TestSwap2Bit(15, 39);
	TestSwap2Bit(8, 32);
	TestSwap2Bit(16, 16);
}
/*---------------*/
void SwapBitwise(int *x, int *y)
{
	if (x != y)
	{
		*x = *x ^ *y;
		*y = *x ^ *y;
		*x = *x ^ *y;
	}
}

void TestSwapBitwise(int x, int y)
{
	
	int old_x = x, old_y = y;
	
	SwapBitwise(&x, &y);
	
	 Test((x == old_y) && (y == old_x));
	
}


/*----------------------------------------------*/

unsigned int DividedBy16(unsigned int number)
{
	return number & (-1 ^ 15);
}

void TestDividedBy16(unsigned int number, unsigned char expected)
{
	Test(DividedBy16(number) == expected);
}

void SuperTestDividedBy16()
{
	TestDividedBy16(15,0);
	TestDividedBy16(16,16);
	TestDividedBy16(68,64);
}
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/

void PrintFloat(float number)
{
	unsigned int i = 1 << 31;
	
	int j = 0;
	
	for(; j < 32; j++)
	{
	    if((int)number & i)
	    {
	    	printf("1");
	    }
	    else
	    {
	    	printf("0");
	    }
	  	
	  	i = i >> 1;
	}
	
	printf("\n");
}

void PrintBin(unsigned n)
{
     int i;
    
    for (i = 1 << 31; i > 0; i = i / 2)
    {
        if(n & i)
        {
        	printf("1");
        }
        else
        {
        	printf("0");
        }
    }
    printf("\n");
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

/*----------------------------------------------*/

int CountBistInUnsignedInt(unsigned int n)
{
	int countbits = 0;
	int m = 1;
	unsigned int i = 0;
	
	for (; i < sizeof(unsigned int) * 8; i++)
	{
		countbits += (n >> i) & m ;
	}
	
	return countbits;
}
















