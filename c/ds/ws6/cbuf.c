/*
    Team: All.
    c_buffer

    date:    9/9/2021
    version: 01
*/
#include <stdio.h>/*printf*/

#include <stdlib.h> /*malloc,free*/
#include <assert.h>/*assert*/

#include "cbuf.h"


struct cb {
    size_t head;
    size_t size;
    size_t capacity;
    char buf[1]; 
};

cbuff_t *CBCreate(size_t capacity)
{
	cbuff_t *cbuff = (cbuff_t*)malloc(sizeof(cbuff_t) 
	                 + sizeof(char) * capacity);
	
	if (!cbuff)
	{
		return NULL;
	}
	
	cbuff->head = 0;
	cbuff->size = 0;
	cbuff->capacity = capacity;
	
	return cbuff;
}


void CBDestroy(cbuff_t *cbuff)
{
	assert(cbuff);
	
	free(cbuff);
	cbuff = NULL;
	
}

size_t CBFreeSpace(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return (cbuff->capacity - cbuff->size);
}

size_t CBBufsiz(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return cbuff->capacity;
}

int CBIsEmpty(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return cbuff->size == 0;
}

ssize_t CBWrite(cbuff_t *cbuff, const void *buf, size_t count)
{
	size_t writen = 0;
	char *buf_byte = (char*)buf;
	
	assert(cbuff && buf);
	
	while (CBFreeSpace(cbuff) && (writen < count))
	{
		size_t index = (cbuff->head + cbuff->size++) 
		               % CBBufsiz(cbuff);
		
		cbuff->buf[index] = buf_byte[writen++];
	}
	
	return writen;
}

ssize_t CBRead(cbuff_t *cbuff, void *buf, size_t count)
{
	size_t read = 0;
	char *buf_byte = (char*)buf;
	
	while (!CBIsEmpty(cbuff) && (read < count) )
	{
		buf_byte[read++] = cbuff->buf[(cbuff->head) 
		                % CBBufsiz(cbuff)];
		cbuff->size--;
	}
	
	return read;
}

/*------------------------------------------------------*/

char CBRemove(cbuff_t *cbuff) 
{
    char data;

    assert(cbuff);

    data = cbuff->buf[cbuff->head];
   	
    cbuff->head = (cbuff->head + 1) % cbuff->capacity;
    (cbuff->size)--;
    
    return data;
}

void CBPrint(cbuff_t *cbuff)
{
	size_t max = cbuff->capacity, i = 0;
	
	while (i < max)
	{
		printf("%c", cbuff->buf[(cbuff->head + i++) % max]);
	}
	
	printf("\n");
}








