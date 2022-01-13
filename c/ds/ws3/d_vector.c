#include <stdlib.h>/*malloc,free*/
#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/


#include "d_vector.h"


struct vector
{
	void **base_ptr;
	size_t size;
	size_t capacity;
};



vector_t *DVectorCreate(size_t capacity)
{
	void **array = NULL;
	
	vector_t *vector = (vector_t*)malloc(sizeof(vector_t));
	array = (void **)malloc(capacity * sizeof(void*));
	
	if (!vector | !array)
    {
        free(vector);
        free(array);
        
        return NULL;
    }
    
	vector->base_ptr = array;
	vector->size = 0;
	vector->capacity = capacity; 
	 
	return vector;
}

void DVectorDestroy(vector_t *vector)
{
	assert(vector);
	
	free(vector->base_ptr);
	vector->base_ptr = NULL;
	
	free(vector);
	vector = NULL;
}

void DVectorSet(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	assert(index < vector->capacity);
	
	vector->base_ptr[index] = element;
	
}

void *DVectorGet(const vector_t *vector, size_t index)
{
	assert(vector);
	assert(index < vector->capacity);
	
	return vector->base_ptr[index];
}

int DVectorPushBack(vector_t *vector, void *element)
{
	int result;
	
	assert(vector);
	
	if (IsFull(vector))
	{
        void **array = NULL;
        
        array = realloc(vector->base_ptr, sizeof(void *) * vector->capacity * 2);
        
        if (!array)
        {
        	free(array);
        	
        	return 1;
        }
        
        vector->capacity *= 2;
        vector->base_ptr = array;
    }
    
   	vector->base_ptr[vector->size++] = element;
   	
   	result = (vector->base_ptr[vector->size] == element);
   	
   	return result;
}

size_t DVectorGetSize(const vector_t *vector)
{
	assert(vector);
	
	return vector->size;
}
size_t DVectorGetCapacity(const vector_t *vector)
{
	assert(vector);
	
	return vector->capacity;
}



void *DVectorPopBack(vector_t *vector)
{
	assert(vector);
    
    return vector->base_ptr[--vector->size]; 	
}

int DVectorReserve(vector_t *vector, size_t new_capacity)
{

	void *new_alloc = realloc(vector->base_ptr, sizeof(void *) * new_capacity);
	
	assert(vector);
	
	if (new_capacity < vector->size)
    {
        vector->size = new_capacity;
    }
    
	vector->capacity = new_capacity;
	vector->base_ptr = new_alloc;
	
	
	return (new_alloc != NULL);
}

int DVectorShrinkToFit(vector_t *vector)
{
	assert(vector);
	
	return DVectorReserve(vector, vector->size);
}















/*----------------------------*/

int IsEmpty(const vector_t *vector)
{
	int result = 1;
	
	if (DVectorGetSize(vector) > 0)
	{
		result = 0;
	}
	
	return result;
}

int IsFull(vector_t *vector) 
{

	int isnt_full = DVectorGetSize(vector) == DVectorGetCapacity(vector);
    
    return isnt_full;     
}









