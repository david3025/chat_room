#include <stdio.h>
#include "sorted_list.h"

int Add(void *a , void *param);
int Compare(const void *a, const void *b);
int CompareDlData(sr_list_t *l1, sr_list_t *l2);
void PrintSrList(sr_list_t *srlist);
void PrintTest(int result);


void TestSortedLMerge();
void TestInsertRemoveFind();
void TestPopBackAndFront();
void TestForEach();
void TestSortedLFindIf();
void TestAll();

int main()
{	
	
	TestAll();
	
	return 0;
}
/*------------------------------------*/

void TestAll()
{
	
	
	TestInsertRemoveFind();
	TestSortedLMerge();
	TestSortedLFindIf();
	TestForEach();
	TestPopBackAndFront();
}
/*------------------------------------*/
int is_match(const void *a, const void *b)
{
	return (*(int*)a > *(int*)b); 
}

void TestSortedLFindIf()
{
	int i = 0, param1 = 3, param2 = 8;
	int arr[] = {6,4,2,3,7,5,1};
	sr_list_t *list = SortedLCreate(Compare);	
	sr_iter_t find_if;
	
	for (; i < 7; i++)
	{
		SortedLInsert(list, arr + i);
	}

	find_if =SortedLFindIf(SortedLBegin(list), 
	         SortedLEnd(list), &param1, is_match);
	
	PrintTest(*(int*)SortedLGetData(find_if) == 4);
	
	
	find_if =SortedLFindIf(SortedLBegin(list), 
	         SortedLEnd(list), &param2, is_match);
	         
	PrintTest(SortedLIsIterEqual(find_if, SortedLEnd(list)));
	
	SortedLDestroy(list);		
}
/*------------------------------------*/

int Add(void *a, void *param)
{
	*(int*)param += *(int*)a ;
	
	return 0;
}

void TestForEach()
{
	int i = 0, param = 0;
	int arr[] = {1,2,3,4,5,6,7};
	sr_list_t *list = SortedLCreate(Compare);	
	
	for (; i < 7; i++)
	{
		SortedLInsert(list, arr + i);
	}
	
	SortedLForEach(SortedLBegin(list), SortedLEnd(list), Add, &param);
		
	PrintTest(param == 28);
	SortedLDestroy(list);		
}


/*------------------------------------*/


void TestPopBackAndFront()
{
	int result = 1, x[] = {6,4,1,7,2}, i;
	sr_list_t *list = SortedLCreate(Compare);	
	void *data;
	
	result *= SortedLIsEmpty(list);
	
	for (i = 0; i < 5; i++)
	{
		SortedLInsert(list, x + i);
	}
	result *= SortedLSize(list) == 5;

	data = SortedLGetData(SortedLBegin(list));
	
	result *= *(int*)SortedLPopFront(list) == *(int*)data;
	
	data = SortedLGetData(SortedLPrev(SortedLEnd(list)));
	
	result *= *(int*)SortedLPopBack(list) == *(int*)data;
	
	result *= SortedLSize(list) == 3;
	
	PrintTest(result);
	SortedLDestroy(list);	
}

/*------------------------------------*/

int ListIsSort(sr_list_t *list)
{
	sr_iter_t iter = SortedLBegin(list);
	
	while (!SortedLIsIterEqual(iter, 
	        SortedLPrev(SortedLEnd(list))))
	{
		if ( *(int*)SortedLGetData(iter) >
		                 *(int*)SortedLGetData(SortedLNext(iter)))
		{
			return 0;
		}
		                 
		iter = SortedLNext(iter);
	}
	
	return 1;
}
void TestInsertRemoveFind()
{
	int i = 0, result = 1;
	int x[] = {4,1,6,7,2};
	sr_list_t *list = SortedLCreate(Compare);	

	
	result *= SortedLIsEmpty(list);
	
	for (i = 0; i < 5; i++)
	{
		SortedLInsert(list, x + i);
	}
	
	result *= ListIsSort(list);
	
	result *= SortedLSize(list) == 5;
	
	                     
	
	PrintTest(result);
	SortedLDestroy(list);
}

/*------------------------------------*/

void TestSortedLMerge()
{
	int x[] = {6,4,1,7,2}, i = 0;
	int y[] = {5,3,8};
	int test[] = {1,2,3,4,5,6,7,8};
	
	sr_list_t *list = SortedLCreate(Compare);
	sr_list_t *list1 = SortedLCreate(Compare);
	
	sr_list_t *expected = SortedLCreate(Compare);
	
	for (; i < 5; i++)
	{
		SortedLInsert(list, x + i);
	}
	
	i = 0;
	
	for (; i < 3; i++)
	{
		SortedLInsert(list1, y + i);
	}

	i = 0;	
	
	for (; i < 8; i++)
	{
		SortedLInsert(expected, test + i);
	}
	
	SortedLMerge(list, list1);
	
	PrintTest(CompareDlData(expected, list));
	
	SortedLDestroy(list);
	SortedLDestroy(list1);
	SortedLDestroy(expected);
}


void test()
{
	int x[] = {4,3,1,6,8,4,3,2,5}, i = 0, data = 5;
	
	sr_list_t *list = SortedLCreate(Compare);
	printf("%d\n",SortedLIsIterEqual(SortedLBegin(list), SortedLEnd(list)));
	
	for (; i < 9; i++)
	{
		SortedLInsert(list, x + i);
	}
	
	SortedLRemove(SortedLFind(SortedLBegin(list),SortedLEnd(list), &data, list));
	
	 printf("\n%d\n",*(int*)SortedLPopBack(list));
	 SortedLPopFront(list);
	                      
	
	printf("%lu\n",SortedLSize(list));

	SortedLDestroy(list);

}


int Compare(const void *e1, const void *e2)
{
	if (*(int*)e1 > *(int*)e2)
	{
		return 1;
	}
	else if (*(int*)e1 < *(int*)e2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
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
