#include <stdio.h> /*printf*/
#include <stdlib.h>/*free*/
#include "d_vector.h"

void PrintTest(int result);

void TestDVectorCreate(size_t capacity);
void TestDVectorGetSizeAndCapacity(size_t capacity);
void TestPushBackAlloc();
void TestDVectorReserve();
void TestDVectorShrinkToFit();

/*vector vector_t;*/

int main()
{
	
	TestDVectorCreate(4);
	TestDVectorGetSizeAndCapacity(4);
	TestPushBackAlloc();
	TestDVectorReserve();
	TestDVectorShrinkToFit();	
	return 0;
}

void TestDVectorCreate(size_t capacity)
{
	int result = 0;
	vector_t *vector = NULL;
	
	vector = DVectorCreate(capacity);
	
	if (vector)
	{
		result = 1;
	}
	
	DVectorDestroy(vector);
	
	PrintTest(result);
}

void TestDVectorSetAndGet(size_t capacity)
{
	int result = 0;
	int change = 1;
	vector_t *vector = DVectorCreate(capacity);
	DVectorPushBack(vector, &result);
	DVectorSet(vector, 0, &change);
	
	if (DVectorGet(vector, 0) == &change)
	{
		result = 1;
	}
	
	DVectorDestroy(vector);
	
	PrintTest(result);
}

void TestDVectorGetSizeAndCapacity(size_t capacity)
{
	int result = 1;
	vector_t *vector = DVectorCreate(capacity);
	
	result *= DVectorGetCapacity(vector) == capacity;
	result *= DVectorGetSize(vector) == 0;
	
	DVectorPushBack(vector, &result);
	DVectorPushBack(vector, &result);	
	
	result *= DVectorGetSize(vector) == 2;
	
	DVectorDestroy(vector);
	
	PrintTest(result);
}

void TestPushBackAlloc()
{
	int result = 1;
	vector_t *vector = DVectorCreate(2);
	
	DVectorPushBack(vector, &result);
	DVectorPushBack(vector, &result);
	DVectorPushBack(vector, &result);
	
	result *= DVectorGetSize(vector) == 3;
	result *= DVectorGetCapacity(vector) == 4;
	
	DVectorPopBack(vector);
	DVectorPopBack(vector);
	DVectorPopBack(vector);
	
	result *= DVectorGetSize(vector) == 0;
	
	
	DVectorDestroy(vector);
	
	PrintTest(result);
}

void TestDVectorReserve()
{
	int result = 1;
	int first = 8;
	float second = 1.2;
	
	vector_t *vector = DVectorCreate(2);
	
	DVectorPushBack(vector, &first);
	DVectorPushBack(vector, &second);
	
	PrintTest(DVectorReserve(vector, 3));
	
	DVectorReserve(vector, 1);
	
	result *= (DVectorGetCapacity(vector) == 1);
	result *= (DVectorGetSize(vector) == 1);
	
	DVectorDestroy(vector);
	
	PrintTest(result);
}


void TestDVectorShrinkToFit()
{
	int result = 1;
	vector_t *vector = DVectorCreate(2);
	
	DVectorPushBack(vector, &result);
	
	result *= DVectorGetCapacity(vector) == 2;
	
	DVectorReserve(vector, 5);
	
	result *= DVectorGetCapacity(vector) == 5;
	
	DVectorShrinkToFit(vector);
	
	result *= DVectorGetCapacity(vector) == 1;
	
	DVectorDestroy(vector);
	
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

