#include <stdio.h>
#include "ws8.h"


int TestMax2(int a, int b, int expected);
int TestMax3(int a, int b, int c, int expected);
void SuperTestMax2();
void SuperTestMax3();
void Test(int result);

int main()
{
	
	object objs [SUM_OF_OBJECT];
	SuperTestMax2();
	SuperTestMax3();
	CreateIntobject(&objs[0],12);
	CreateFloatObject(&objs[1],12.3);
	CreateStringobject(&objs[2],"hello");
	PrintAllobjects(objs);
	AddToAllobjects(objs, 10);
	PrintAllobjects(objs);
	FreeAllobjects(objs);

	return 0;
}

/*-------------------------------------*/

int TestMax2(int a, int b, int expected)
{
	int result = 1;
	
	if (MAX2(a, b) != expected)
	{
		result = 0;
	}
	
	return result;
}

void SuperTestMax2()
{
	int result = 1;
	
	result *= TestMax2(6, 0, 6);
	result *= TestMax2(423, 6, 423);
	result *= TestMax2(0, 0, 0);
	
	Test(result);
}

int TestMax3(int a, int b, int c, int expected)
{
	int result = 1;
	
	if (MAX3(a, b, c) != expected)
	{
		result = 0;
	}
	
	return result;
}

void SuperTestMax3()
{
	int result = 1;
	
	result *= TestMax3(6, 0, 6, 6);
	result *= TestMax3(324, 6, 15, 324);
	result *= TestMax3(0, 0, 0, 0);
	
	Test(result);
}

/*--------------------------------------*/

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
