# include <stdio.h> /* printf */
# include "sorted_list.h"


void TestSortedLCreateAndDestroy(void);
void TestSortedLInsertAndRemove(void);
void TestSortedLPopBackAndFront(void);
void TestSortedLFindIf(void);
void TestSortedLFind(void);
void TestSortedLForEach(void);
void TestSortedLMerge(void);
void TestSortedLEmpty(void);


void TestArraySortedLInsert(sr_list_t*, int*, size_t);
void TestArraySortedLRemove(sr_list_t*, int*, size_t);
void TestSomeSortedLPeek(sr_iter_t, int);
void PrintList(sr_list_t*, int*, size_t);


int CompareTo(const void*, const void*);
int IsMatch(const void*, const void*);
int PrintData(void*, void*);
int PrintAster(void*, void*);


void PrintResultsInt (int, int);
void PrintResultsLong (char*, size_t, size_t);


int main()
{
	TestSortedLCreateAndDestroy();
	TestSortedLInsertAndRemove();
	TestSortedLPopBackAndFront();
	TestSortedLFindIf();
	TestSortedLFind();
	TestSortedLForEach();
	TestSortedLMerge();
	TestSortedLEmpty();
	
	printf("\n");
	return 0;
}



void TestArraySortedLInsert(sr_list_t *srlist, int *arr, size_t size)
{
	size_t i = 0;
	
	for (; i < size; i++)
	{
		SortedLInsert(srlist, (void*)(long)arr[i]);
	}
}


void TestArraySortedLRemove(sr_list_t *srlist, int *arr, size_t size)
{
	size_t i = 0;
	sr_iter_t iter = SortedLBegin(srlist);
	
	for (; i < size; i++)
	{
		TestSomeSortedLPeek(iter, arr[i]);
		iter = SortedLRemove(iter);
	}
}


void TestSomeSortedLPeek(sr_iter_t iter, int expect)
{
	int result = (int)(long)SortedLGetData(iter);
	PrintResultsInt(result, expect);
}


void PrintList(sr_list_t *srlist, int *expect, size_t size)
{
	size_t i = 0;
	
	for (; i < size; i++)
	{
		int result = (int)(long)SortedLPopFront(srlist);
		PrintResultsInt(result, expect[i]);
	}
}





void TestSortedLCreateAndDestroy()
{
	sr_list_t *srlist = NULL;
	
	printf("\nTest - Sorted_List Create & Destroy ...");
	
	srlist = SortedLCreate(CompareTo);
	SortedLDestroy(srlist);
	srlist = NULL;
	
	printf (" Passed!\n");
}


void TestSortedLInsertAndRemove()
{
	sr_list_t *srlist = NULL;
	sr_iter_t iter;
	int values[] = {2,4,3,1};
	int results[] = {1,2,3,4};
	
	printf("\nTest - Sorted_List Insert & Remove\n");
	
	srlist = SortedLCreate(CompareTo);
	
	TestArraySortedLInsert(srlist, values, 4);
	
	PrintResultsLong("size", SortedLSize(srlist), 4);
	PrintResultsLong("is_empty", SortedLIsEmpty(srlist), 0);
	
	TestArraySortedLRemove(srlist, results, 4);
	
	PrintResultsLong("size", SortedLSize(srlist), 0);
	PrintResultsLong("is_empty", SortedLIsEmpty(srlist), 1);
	
	iter = SortedLInsert(srlist, (void*)(long)5);
	TestSomeSortedLPeek(SortedLPrev(iter), 5);
	
	SortedLDestroy(srlist);
	srlist = NULL;
}


void TestSortedLPopBackAndFront()
{
	sr_list_t *srlist = NULL;
	void *val[8] = {0};
	int results[] = {8,7,1,2,6,3};
	size_t i = 0;
	
	printf("\nTest - Sorted_List Pop - Back & Front\n");
	
	srlist = SortedLCreate(CompareTo);
	
	SortedLInsert(srlist, (void*)(long)8);
	SortedLInsert(srlist, (void*)(long)2);
	SortedLInsert(srlist, (void*)(long)1);
	SortedLInsert(srlist, (void*)(long)7);
	SortedLInsert(srlist, (void*)(long)6);
	SortedLInsert(srlist, (void*)(long)3);
	
	PrintResultsLong("size", SortedLSize(srlist), 6);
	
	val[0] = SortedLPopBack(srlist);
	val[1] = SortedLPopBack(srlist);
	val[2] = SortedLPopFront(srlist);
	val[3] = SortedLPopFront(srlist);
	
	SortedLInsert(srlist, (void*)(long)4);
	SortedLInsert(srlist, (void*)(long)5);
	
	val[4] = SortedLPopBack(srlist);
	val[5] = SortedLPopFront(srlist);
	
	for (i = 0; i < 6; i++)
	{
		PrintResultsInt((int)(long)val[i], results[i]);
	}
	
	PrintResultsLong("size", SortedLSize(srlist), 2);
	
	SortedLDestroy(srlist);
	srlist = NULL;
}


void TestSortedLFindIf()
{
	sr_list_t *srlist = NULL;
	sr_iter_t iter;
	int values[] = {0,2,4,6,8,1,3,5,7,9};
	
	printf("\nTest - Sorted_List Find If\n");
	srlist = SortedLCreate(CompareTo);
	
	/* Insert */
	TestArraySortedLInsert(srlist, values, 10);
	
	/* FindIf */
	iter = SortedLFindIf(
		SortedLBegin(srlist), SortedLEnd(srlist),
		(void*)(long)5, IsMatch);
	TestSomeSortedLPeek(iter, 5);
	
	iter = SortedLFindIf(
		SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)2, IsMatch);
	TestSomeSortedLPeek(iter, 2);
	
	iter = SortedLFindIf(
	SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)8, IsMatch);
	TestSomeSortedLPeek(iter, 8);
	
	iter = SortedLFindIf(
	SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)7, IsMatch);
	TestSomeSortedLPeek(iter, 7);
	
	SortedLDestroy(srlist);
	srlist = NULL;
}


void TestSortedLFind()
{
	sr_list_t *srlist = NULL;
	sr_iter_t iter;
	int values[] = {0,2,4,6,8,1,3,7,9};
	
	printf("\nTest - Sorted_List Find\n");
	srlist = SortedLCreate(CompareTo);
	
	/* Insert */
	TestArraySortedLInsert(srlist, values, 9);
	
	/* Find */
	iter = SortedLFind(
		SortedLBegin(srlist), SortedLEnd(srlist),
		(void*)(long)5, srlist);
	TestSomeSortedLPeek(iter, 6);
	
	iter = SortedLFind(
		SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)2, srlist);
	TestSomeSortedLPeek(iter, 2);
	
	iter = SortedLFind(
	SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)8, srlist);
	TestSomeSortedLPeek(iter, 8);
	
	iter = SortedLFind(
	SortedLNext(SortedLNext(SortedLBegin(srlist))),
		SortedLPrev(SortedLPrev(SortedLEnd(srlist))),
		(void*)(long)7, srlist);
	TestSomeSortedLPeek(iter, 7);
	
	SortedLDestroy(srlist);
	srlist = NULL;
}


void TestSortedLForEach()
{
	sr_list_t *srlist = NULL;
	sr_iter_t iters[10] = {0};
	sr_iter_t iter;
	int values[] = {0,2,4,6,8,1,3,5,7,9};
	size_t i = 0;
	int error = 0;
	
	printf("\nTest - Sorted_List For Each\n");
	srlist = SortedLCreate(CompareTo);
	
	/* Insert */
	TestArraySortedLInsert(srlist, values, 10);
	
	iter = SortedLBegin(srlist);
	for (i = 0; i < 10; i++)
	{
		iters[i] = iter;
		iter = SortedLNext(iter);
	}
	
	/* For-each : print values from 4 (inc) to 8 (exc) */
	error = SortedLForEach(iters[4], iters[8], PrintData,
											(size_t*)2);
	PrintResultsLong("\nerror_value", error, 0);
	
	for (i = 4; i < 8; i++)
	{
		TestSomeSortedLPeek(iters[i], i);
	}
	
	error = SortedLForEach(iters[4], iters[8], PrintAster, (void*)3);
	PrintResultsLong("\nerror_value", error, 1);
	
	SortedLDestroy(srlist);
	srlist = NULL;
}


void TestSortedLMerge()
{
	sr_list_t *base = NULL, *append = NULL;
	int values1[] = {1,3,9,7,5};
	int values2[] = {2,4,0,8,6};
	int vals_base_expect[] = {0,1,2,3,4,5,6,7,8,9};
	
	printf("\nTest - Sorted_List Merge\n");
	
	base = SortedLCreate(CompareTo);
	append = SortedLCreate(CompareTo);
	
	/* insert */
	TestArraySortedLInsert(base, values1, 5);
	TestArraySortedLInsert(append, values2, 5);
	
	PrintResultsLong("base size", SortedLSize(base), 5);
	PrintResultsLong("append size", SortedLSize(append), 5);
	
	/* merge */
	SortedLMerge(base, append);
	
	PrintResultsLong("base size", SortedLSize(base), 10);
	PrintResultsLong("append size", SortedLSize(append), 0);
	
	PrintList(base, vals_base_expect, SortedLSize(base));
	
	SortedLDestroy(append);
	append = NULL;
	
	SortedLDestroy(base);
	base = NULL;
}


void TestSortedLEmpty()
{
	
}




int CompareTo(const void *e1, const void *e2)
{
	if ((size_t)e1 > (size_t)e2)
	{
		return 1;
	}
	else if ((size_t)e1 < (size_t)e2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


int IsMatch(const void *e1, const void *e2)
{
	return (e1 == e2);
}


int PrintData(void *data, void *param)
{
	(void)param;
	printf(" %d ", (int)(long)data);
	return 0;
}


int PrintAster(void *data, void *param)
{
	int error = 0;
	size_t i = 0;
	(void)data;
	
	for (; i < (size_t)param; i++)
	{
		printf("*");
		if (2 == i)
		{
			error = 1; /* return error */
			break;
		}
	}
	
	return error;
}






void PrintResultsInt (int res, int expect)
{
	if (res == expect)
	{
		printf("\033[1;32m"); /* green - equals */
	}
	else
	{
		printf("\033[1;31m"); /* red - different */
	}
	printf ("result: %d , expect: %d\n", res, expect);
	
	printf("\033[0m"); /* reset color */
}


void PrintResultsLong (char *title, size_t res, size_t expect)
{
	if (res == expect)
	{
		printf("\033[1;32m"); /* green - equals */
	}
	else
	{
		printf("\033[1;31m"); /* red - different */
	}
	printf ("%s: %ld , expect: %ld\n", title, res, expect);
	
	printf("\033[0m"); /* reset color */
}









