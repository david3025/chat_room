#include <stdio.h>
#include "queue.h"
#include "s_list.h"

void PrintAllQueue(queue_t *queue);
void PrintTest(int result);
void GeneralTest();
void TestQAppend();
int main()
{	
	
	/*GeneralTest();*/
	TestQAppend();

	return 0;
}

void GeneralTest()
{
	queue_t *queue;
	int arr[] = {3,4,7};
	int result = 1;
	
	queue = QCreate();
	result *= QIsEmpty(queue);
	
	QEnqueue(queue, (void*)arr);
	result *= QPeek(queue) == arr;
	
	QEnqueue(queue, (void*)(arr + 1));
	result *= QPeek(queue) == arr;
	result *= !QIsEmpty(queue);
	
	QEnqueue(queue, (void*)(arr + 2));	
	result *= QGetSize(queue) == 3;
	
	result *= QDequeue(queue) == arr;
	result *= QGetSize(queue) == 2;	
	
	QDequeue(queue);
	result *= QPeek(queue) == arr + 2;
	result *= QGetSize(queue) == 1;	
	
	result *= QDequeue(queue) == arr + 2;
	result *= QGetSize(queue) == 0;		
	
	QDestroy(queue);
	
	PrintTest(result);
}
void TestQAppend()
{
	int result = 1;
	queue_t *base, *append;
	int arr[] = {1,2,3,4,5};
	
	base = QCreate();
	QEnqueue(base, (void*)arr);
	QEnqueue(base, (void*)(arr + 1));
	QEnqueue(base, (void*)(arr + 2));
	result *= QGetSize(base) == 3;
	
	append = QCreate();
	QEnqueue(append, (void*)(arr + 3));
	QEnqueue(append, (void*)(arr + 4));
	result *= QGetSize(append) == 2;
	
	QAppend(base, append);
	
	result *= QGetSize(base) == 5;
	result *= QGetSize(append) == 0;
	
	QAppend(append, base);
	
	result *= QGetSize(base) == 0;
	result *= QGetSize(append) == 5;
	
	
	QDestroy(base);
	QDestroy(append);
	
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




