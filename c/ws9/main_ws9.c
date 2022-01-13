#include <stdio.h>
#include <string.h>
#include "ws9.h"

void TestMemmove();
void TestMemcpy();
void TestMemset();
void Test(int result);

/*--------------------------------------------*/

int main () 
{
	TestMemmove();
	TestMemset();
	TestMemcpy();
 
 
	return(0);
}

/*--------------------------------------------*/

void TestMemmove()
{
	int result = 1;
	char test[] = "I am doing a test for the memmove function ";
	
	result += strcmp((char*)Memmove(&test[5], test, 2),(char*)memmove(&test[5], test, 2));
	result += strcmp((char*)Memmove(&test[5], test, 2),(char*)memmove(&test[5], test, 2));
	result += strcmp((char*)Memmove(&test[2], test, 5),(char*)memmove(&test[2], test, 5));
	result += strcmp((char*)Memmove(&test[2], test, 11),(char*)memmove(&test[2], test, 11));
	
	printf("TestMemmove-\t");
	Test(result == 1);
}

/*--------------------------------------------*/

void TestMemcpy()
{
	int result = 1;
	
	char src[50] = "1234567812345678123456781234567812345678";
	char dest_memcopy[50] = "345678123456781234567812345678123456781234567812";	
	char dest_my_memcopy[50] = "345678123456781234567812345678123456781234567812";	

	result += strcmp((char*)Memcpy(&dest_my_memcopy[2], src, 2),(char*)memcpy(&dest_memcopy[2], src, 2));
	result += strcmp((char*)Memcpy(&dest_my_memcopy[2], src, 9),(char*)memcpy(&dest_memcopy[2], src, 9));
	result += strcmp((char*)Memcpy(&dest_my_memcopy[0], src, 2),(char*)memcpy(&dest_memcopy[0], src, 2));
	result += strcmp((char*)Memcpy(&dest_my_memcopy[0], src, 10),(char*)memcpy(&dest_memcopy[0], src, 10));
	result += strcmp((char*)Memcpy(&dest_my_memcopy[0], src, 8),(char*)memcpy(&dest_memcopy[0], src, 8));
	result += strcmp((char*)Memcpy(&dest_my_memcopy[0], src, 16),(char*)memcpy(&dest_memcopy[0], src, 16));

	printf("TestMemcpy-\t");
	Test(result == 1);
}

/*--------------------------------------------*/

void TestMemset()
{
	int result = 1;
	
	char memory[50] = "123456781234567812345678123456781234567812345678";
	char Memory[50] = "123456781234567812345678123456781234567812345678";	
	
	result += strcmp((char*)Memset(&Memory[0], '1', 9),(char*)memset(&memory[0], '1', 9));
	result += strcmp((char*)Memset(&Memory[0], '#', 2),(char*)memset(&memory[0], '#', 2));
	result += strcmp((char*)Memset(&Memory[0], '%', 7),(char*)memset(&memory[0], '%', 7));
	result += strcmp((char*)Memset(&Memory[3], '#', 2),(char*)memset(&memory[3], '#', 2));
	result += strcmp((char*)Memset(&Memory[3], '^', 4),(char*)memset(&memory[3], '^', 4));
	result += strcmp((char*)Memset(&Memory[3], 'e', 6),(char*)memset(&memory[3], 'e', 6));
	result += strcmp((char*)Memset(&Memory[0], 'A', 15),(char*)memset(&memory[0], 'A', 15));
	
	printf("TestMemset-\t");	
	Test(result == 1);
}

/*--------------------------------------------*/

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

