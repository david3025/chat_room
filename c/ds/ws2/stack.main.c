#include <stdio.h>
#include <stdlib.h>/*free*/
#include "stack.h"

void TestLipoStruct();
void TestPopAndPush();
void TestStackPeek();

void TestStackCreate(size_t capacity);
void TestStackPop(size_t capacity);
void TestStackCapacity(size_t capacity);
void TestStackSize(size_t capacity);
void TestStackIsEmpty(size_t capacity);

void Test(int result);

int main()
{
	TestLipoStruct();
	TestPopAndPush();
	TestStackPeek();
	
	TestStackCreate(51241);
	TestStackPop(5341);
	TestStackCapacity(5123);
	TestStackSize(53123);
	TestStackIsEmpty(512);
	
	
	return 0;
}

void TestStackCreate(size_t capacity)
{
	int res = 0;
	
	stack_t *stack = StackCreate(capacity);
	
	if (stack)
	{
		res = 1;
	}
	
	free(stack);
	stack = NULL;
	
	Test(res);
}

void TestStackPop(size_t capacity)
{
	int res = 1;
	void *ptr = &res;
	
	stack_t *stack  = StackCreate(capacity);
	StackPush(stack, ptr);
	
	res *= (StackPop(stack) == ptr);
	
	Test(res);
	StackDestroy(stack);
}

void TestStackCapacity(size_t capacity)
{
	int res = 1;
	stack_t *stack = StackCreate(capacity);
	
	res *= (StackCapacity(stack) == capacity);
	
	Test(res);
	StackDestroy(stack);
}
	
void TestStackSize(size_t capacity)
{
	int res = 1;
	float test = 3;
	char *str = "test";
	stack_t *stack = StackCreate(capacity);
	
	res *= (StackSize(stack) == 0);
	StackPush(stack, &res);
	res *= (StackSize(stack) == 1);
	StackPush(stack, &test);
	res *= (StackSize(stack) == 2);	
	StackPush(stack, str);
	res *= (StackSize(stack) == 3);
	StackPop(stack);
	res *= (StackSize(stack) == 2);
	
	Test(res);
	StackDestroy(stack);
}

void TestStackIsEmpty(size_t capacity)
{
	int res = 1;
	stack_t *stack = StackCreate(capacity);
	
	res *= (StackIsEmpty(stack) == 1);
	StackPush(stack, &res);
	res *= (StackIsEmpty(stack) == 0);
	
	Test(res);
	StackDestroy(stack);
}

void TestPopAndPush()
{
	int res = 1;
	stack_t *stack = StackCreate(4);
	
	res *= (StackSize(stack) == 0);	
	StackPush(stack, &res);
	StackPush(stack, &res);
	res *= (StackSize(stack) == 2);	
	StackPush(stack, &res);
	StackPush(stack, &res);
	res *= (StackSize(stack) == 4);
	StackPop(stack);
	StackPop(stack);
	res *= (StackSize(stack) == 2);	
	StackPop(stack);
	StackPop(stack);
	res *= (StackSize(stack) == 0);	
	
	Test(res);
	StackDestroy(stack);
}

void TestLipoStruct()
{
	int res = 1;
	stack_t *stack = StackCreate(3);
	
	int a = 2;
	char *b = "hello";
	float c = 3.43;
	
	StackPush(stack, &a);
	StackPush(stack, b);
	StackPush(stack, &c);
	
	res *= (StackPop(stack) == &c);
	res *= (StackPop(stack) == b);
	res *= (StackPop(stack) == &a);
	
	Test(res);
	StackDestroy(stack);
}

void TestStackPeek()
{
	int res = 1;
	stack_t *stack = StackCreate(3);
	
	int a = 2;
	char *b = "hello";
	float c = 3.43;
	
	StackPush(stack, &a);
	res *= (*(int*)StackPeek(stack) == 2);
	
	StackPush(stack, b);
	res *= (*(char*)StackPeek(stack) == 'h');
	
	StackPush(stack, &c);
	res *= (StackPeek(stack) == &c);   /********/
	
	StackPop(stack);
	res *= (StackPeek(stack) == b);
	
	Test(res);
	StackDestroy(stack);
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



