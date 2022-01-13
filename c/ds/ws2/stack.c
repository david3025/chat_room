#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc,free*/

#include "stack.h"

struct stack
{
	void **base_ptr;
	size_t top_index;
	size_t capacity;
};


/*---------------------------------*/

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	 
	stack->base_ptr = (void **)malloc(capacity * sizeof(void*));
	stack->top_index = 0;
	stack->capacity = capacity; 
	 
	return stack;
}
/*---------------------------------*/
void StackDestroy(stack_t *stack)
{
	free(stack->base_ptr);
	stack->base_ptr = NULL;
	
	free(stack);
	stack = NULL;
}
/*---------------------------------*/
void *StackPop(stack_t *stack)
{
	if (StackIsEmpty(stack))
    {
        printf("underflow! program terminated\n");
        exit(EXIT_FAILURE);
    }

	stack->top_index--;
	
	return stack->base_ptr[stack->top_index]; 	
}

/*---------------------------------*/

int IsFull(stack_t *stack) 
{

	int is_full = StackSize(stack) == StackCapacity(stack);
    
    return is_full;     
}
 
void StackPush(stack_t *stack, void *object)
{
	if (IsFull(stack))
    {
        printf("Overflow! program terminated\n");
        exit(EXIT_FAILURE);
    }
    
	stack->base_ptr[stack->top_index] = object; 
	stack->top_index++;
}

/*---------------------------------*/
int StackIsEmpty(const stack_t *stack)
{
	int result = 1;
	
	if (StackSize(stack) > 0)
	{
		result = 0;
	}
	
	return result;
}
/*---------------------------------*/
void *StackPeek(const stack_t *stack)
{
	int top = stack->top_index;
	top--;
	
	return (stack->base_ptr)[top];
}
/*---------------------------------*/
size_t StackSize(const stack_t *stack)
{
	return stack->top_index;
}
/*---------------------------------*/
size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}
/*---------------------------------*/












