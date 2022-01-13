#include <stdio.h>/*printf*/
#include <string.h>/*strcmp*/
#include <assert.h>/*assert*/
#include "ws10.h"


#define TEST_ENDIAN(x) (*(char*)&(x)==1)?printf("little endian"):printf("Big endian")

void TestItoa();
void TestAtoi();
void TestSelectedElements();

void TestItoaBase10();
void TestAtoiBase10();
void Test(int result);

int main()
{
	TestSelectedElements();
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

void TestAtoiBase10()
{
	int result = 1;
	
	result *= (AtoiBase10("7605") == 7605);
	result *= (AtoiBase10("-1023") == -1023);
	result *= (AtoiBase10("1") == 1);
	result *= (AtoiBase10("0") ==  0);
	result *= (AtoiBase10("043E2") ==  0);
	result *= (AtoiBase10("0 53") ==  0);
	
	printf("TestAtoiBase10 >>\t");
	Test(result == 1);
}

void TestItoaBase10()
{
	int result = 1;
	result += strcmp(ItoaBase10(437), "437");
	result += strcmp(ItoaBase10(-123), "-123");
	result += strcmp(ItoaBase10(1), "1");
	result += strcmp(ItoaBase10(0), "0");
	
	printf("TestItoaBase10 >>\t");
	Test(result == 1);
}

void TestItoa()
{
	int result = 1;
	char test[100];
	
	result *= !strcmp(Itoa(437, test, 10), "437");
	result *= !strcmp(Itoa(123456789, test, 10), "123456789");
	result *= !strcmp(Itoa(15, test, 9), "16");	
	result *= !strcmp(Itoa(-111111111, test, 10), "-111111111");
	result *= !strcmp(Itoa(51, test, 32), "1j");	
	result *= !strcmp(Itoa(0, test, 10), "0");
	result *= !strcmp(Itoa(5, test, 2), "101");	

	printf("TestAtoiBase10 >>\t");
	Test(result == 1);
}
void TestAtoi()
{
	int result = 1;
	
	result *= (Atoi("7605") == 7605);
	result *= (Atoi("-1023") == -1023);
	result *= (Atoi("1") == 1);
	result *= (Atoi("0") ==  0);
	result *= (Atoi("043E2") ==  0);
	result *= (Atoi("0 53") ==  0);
	result *= (Atoi(" -123") == -123);
	result *= (Atoi(" -1 23") == 0);
	
	printf("TestAtoiBase10 >>\t");
	Test(result == 1);
}

void TestSelectedElements()
{
	char ar1[] = "aaaaaaa";
	char ar2[] = "aaaaaaa";
	char ar3[] = "1cl23oko";
	
	char ar11[] = "1234";
    char ar12[] = "45678";
	char ar13[] = "abAB123";
	
	char ar21[] = "";
    char ar22[] = "";
	char ar23[] = "";
	
	char ar31[] = "126123";
    char ar32[] = "24567";
	char ar33[] = "93ju4d";
	
	printf("expected to get: aaaaaaa \t");
	SelectedElements(ar1, 7, ar2, 7, ar3, 8);
	printf("expected to get: 4 : \t");
	SelectedElements(ar11, 4, ar12, 5, ar13, 7);
	printf("expected to get: -nothing- \t");	
	SelectedElements(ar21, 0, ar22, 0, ar23, 0);
	printf("expected to get: 262:     \t");	
	SelectedElements(ar31, 6, ar32, 5, ar33, 6);
	
	
}
