#include <stdio.h>
#include "s_list.h"

void TestProgram();
void TestSLDestroy();
void TestAddAndRemove();
void TestAddAndCount();
void TestSLForEachAndFind();


void PrintTest(int result);

int main()
{
	
	TestProgram();
	
	return 0;
}

void TestProgram()
{
	TestSLDestroy();
    TestAddAndCount();
    TestAddAndRemove();
    TestSLForEachAndFind();
}

void TestSLDestroy()
{
	int result = 0;
	slist_t *list  = NULL;
	
	list = SLCreate();
	
	if(list)
	{
		result = 1;
	}
	
	SLDestroy(list);
	PrintTest(result);
}

void TestAddAndCount()
{
	int result = 1;
	int val = 7;
	slist_t *list  = SLCreate();
	sl_iter_t iterator;

	result *= (SLIsEmpty(list));
	
	result *= (SLCount(list) == 0);
	
	iterator = SLAddBefore(SLBegin(list), &val);
	
	result *= (SLCount(list) == 1);

    result *= ((int*)(SLGetValue(iterator)) == &val);  
	
	SLRemove(iterator);
		
	result *= (SLCount(list) == 0); 

	PrintTest(result);
	SLDestroy(list);	

}

void TestAddAndRemove()
{
	int result = 1;
	int a = 1, b = 2, c = 3, d = 4;
	
	slist_t *list  = SLCreate();
	sl_iter_t iterator;
	
	result *= (SLIsEmpty(list));
	
	iterator = SLAddBefore(SLBegin(list), &a);
	result *= (SLBegin(list) == iterator);
	result *= ((int*)(SLGetValue(iterator)) == &a);
	result *= (SLCount(list) == 1);

	iterator = SLAddBefore(SLBegin(list), &b);
	result *= ((int*)(SLGetValue(iterator)) == &b);
	result *= ((int*)(SLGetValue(SLNext(iterator))) == &a);
	result *= (SLCount(list) == 2);

	iterator = SLAddAfter(SLBegin(list), &c);
	result *= (SLBegin(list) == iterator);
	/result *= (SLCount(list) == 3);
	
	iterator = SLAddBefore(SLBegin(list), &d);
	SLSetValue(iterator, &a);
	result *= ((int*)(SLGetValue(iterator)) == &a);	
	
	iterator = SLRemoveAfter(iterator);
	iterator = SLRemove(iterator);
	result *= (SLCount(list) == 2);
	result *= ((int*)(SLGetValue(iterator)) == &c);
	
	iterator = SLRemove(iterator);
	result *= (SLCount(list) == 1);
	result *= ((int*)(SLGetValue(iterator)) == &a);
	
	iterator = SLRemove(iterator);
	result *= (SLIsEmpty(list));
	

	PrintTest(result);
	SLDestroy(list);	
}

int Add(void *a , void *param)
{
	*(int*)param += *(int*)a ;
	
	return 0;
}

int PrintData(void *data , void *param)
{
	int result;
	
	result = printf("%d,", *(int*)data);
	
	(void)param;
	
	return (result == 0);
}

int CompareVal(const void *a, const void *b)
{
	return !(*(int*)a == *(int*)b);
}

void TestSLForEachAndFind()
{
	int result = 1;
	sl_iter_t iter = NULL;
	slist_t *list;
	
	int param = 0;
	int a = 3, b = 1, c = 4, d = 5;
	
	list  = SLCreate();

	SLAddBefore(SLBegin(list), &a);
	SLAddBefore(SLBegin(list), &b);
	SLAddBefore(SLBegin(list), &c);
	SLAddBefore(SLBegin(list), &d);
	
	SLForEach(SLBegin(list), SLEnd(list), Add, &param);
	
	result *= (param == (a + b + c + d));
	
	iter = SLFind(list, (void*)&d, CompareVal);
	result *= (*(int*)SLGetValue(iter) == 5);


	SLDestroy(list);
	PrintTest(result);	
}

void PrintTest(int result)
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
