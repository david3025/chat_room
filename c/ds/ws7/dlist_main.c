#include <stdio.h>
#include "dlist.h"

void PrintTest(int result);
void TestAll();

void TestInsertAndRemove();
void TestBase();
void TestCreateDestroy();
void PrintBlist(dlist_t *dlist);
void TestForEach();
void TestDLFind();
void TestDLMultiFind();

int main()
{
	TestAll();

	
	return 0;
}
void TestAll()
{
	TestCreateDestroy();
	TestForEach();
	TestInsertAndRemove();
	TestBase();
	TestDLFind();
	TestDLMultiFind();
}




int Isequal(const void *a, const void *b)
{
	 return (*(int*)a == *(int*)b);
}


void TestDLMultiFind()
{
	int result = 1;
	int i = 0, find = 3;
	int arr[] = {3,2,3,4,3,3,5,6,7,3};
	dlist_t *dlist = DLCreate();
	dlist_t *dest = DLCreate();
	
	for (; i < 10; i++)
	{
		DLPushBack(dlist, arr + i);
	}
	
	DLMultiFind(DLBegin(dlist), DLEnd(dlist)
	            , dest, &find, Isequal);
	result *= DLSize(dest) == 5;
	
	DLMultiFind(DLNext(DLBegin(dlist)),
	            DLEnd(dlist), dest, &find, Isequal);
	            
	result *= DLSize(dest) == 9;
	
	PrintTest(result);
	DLDestroy(dlist);
	DLDestroy(dest);
}

void TestCreateDestroy()
{
	int arr[] = {1,2,3,4,5,6,7}, i = 0;
	dlist_t *dlist = DLCreate();
	
	for (; i < 7; i++)
	{
		DLPushBack(dlist, arr + i);
	}
	
	DLDestroy(dlist);
}
void TestInsertAndRemove()
{
	int result = 1;
	int arr[] = {1,2,3};
	dlist_t *dlist = DLCreate();
	
	DLInsert(DLBegin(dlist), arr);
	DLInsert(DLEnd(dlist), arr + 1);
	DLInsert(DLEnd(dlist), arr + 2);
	
	result *= DLSize(dlist) == 3;
	
	DLRemove(DLBegin(dlist));
	DLRemove(DLBegin(dlist));
	DLRemove(DLBegin(dlist));
	
	result *= DLIsEmpty(dlist);
	
	PrintTest(result);
	DLDestroy(dlist);
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

/*-----------------------------*/
void TestBase()
{
	int result = 1;
	int arr[] = {1,2,3,4,5,6,7};
	dlist_t *dlist = DLCreate();
	
	result *= DLSize(dlist) == 0;
	DLPushFront(dlist, arr);
	result *= *(int*)DLGetData(DLBegin(dlist)) == 1;
	result *= DLIsIterEqual(DLBegin(dlist), DLPrev(DLEnd(dlist)));
	DLPushBack(dlist, &arr[1]);
	result *= (*(int*)DLGetData(DLPrev(DLEnd(dlist))) == 2);
	result *= DLSize(dlist) == 2;
	result *= *(int*)DLGetData(DLPushFront(dlist, arr + 4)) == 5;
	DLSetData(DLNext(DLBegin(dlist)), arr + 5);
	result *= *(int*)DLGetData(DLNext(DLBegin(dlist))) == 6;

	PrintTest(result);
	DLDestroy(dlist);
}
/*-----------------------------*/
int Add(void *a , void *param)
{
	*(int*)param += *(int*)a ;
	
	return 0;
}

void TestForEach()
{
	int i = 0, param = 0;
	int arr[] = {1,2,3,4,5,6,7};
	dlist_t *dlist = DLCreate();
	
	for (; i < 7; i++)
	{
		DLPushBack(dlist, arr + i);
	}
	
	DLForEach(DLBegin(dlist), DLEnd(dlist), Add, &param);
	
	PrintTest(param == 28);
	DLDestroy(dlist);	
}
/*-----------------------------*/
int IsMatch(const void *a, const void *b)
{
	 return (*(int*)a > *(int*)b);
}

void TestDLFind()
{
	int result = 1;
	int i = 0, test1 = 7, test2 = 10;
	
	int arr[] = {2,3,1,8,7,5};
	dl_iter_t iter1, iter2;
	dlist_t *dlist = DLCreate();
	
	for (; i < 6; i++)
	{
		DLPushBack(dlist, arr + i);
	}
	
	iter1 = DLFind(DLBegin(dlist), DLEnd(dlist), (void*)&test1, IsMatch);
	iter2 = DLFind(DLBegin(dlist), DLEnd(dlist), (void*)&test2, IsMatch);
	
	result *= (*(int*)DLGetData(iter1) == 8);
	result *= (DLIsIterEqual(iter2, DLEnd(dlist)));
	PrintTest(result);
	DLDestroy(dlist);
}

/*-----------------------------*/

void PrintBlist(dlist_t *dlist)
{
	dl_iter_t iter = DLBegin(dlist);
	
	while (!DLIsIterEqual(DLNext(iter), DLEnd(dlist)))
	{
		printf("%d,",*(int*)DLGetData(iter));
		
		iter = DLNext(iter);
	}
	
	printf("%d\n",*(int*)DLGetData(iter));

}












