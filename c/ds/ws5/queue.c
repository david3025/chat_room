#include <stdio.h>/*peintf*/
#include <stdlib.h>/*malloc,free*/
#include <assert.h>/*assert*/

#include "s_list.h"
#include "queue.h"

#define LIST queue->q_list
#define HEAD SLBegin(LIST)
#define END SLEnd(LIST)

struct queue
{
    slist_t *q_list;
};

queue_t *QCreate()
{
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	slist_t *list;
	
	if (!queue)
	{
		
		return NULL;
	}
	
	list = SLCreate();
	
	if (!list)
	{
		free(queue);
		queue = NULL;
		
		return NULL;
	}
	
	queue->q_list = list;
	
	return queue;
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(queue);
	
	return SLIterIsEqual(SLAddBefore(END, data), END);
}

void *QDequeue(queue_t *queue)
{
	void *result = QPeek(queue);
	
	assert(!QIsEmpty(queue));
	
	SLRemove(HEAD);
	
	return result;
}

size_t QGetSize(const queue_t *queue)
{
	assert(queue);
	
	return SLCount(LIST);
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return SLIterIsEqual(HEAD, END);
}


void QDestroy(queue_t *queue)
{
	assert(queue);
	
	SLDestroy(LIST);
	
	free(queue);
	queue = NULL;
}

void *QPeek(const queue_t *queue)
{
	assert(queue);
	
	return SLGetValue(HEAD);
}

void QAppend(queue_t *base, queue_t *append)
{
	assert(base && append);
	
	SLAppend(base->q_list, append->q_list);
}
/*---------------------------------------*/


void PrintAllQueue(queue_t *queue)
{
	sl_iter_t iter = SLBegin(LIST);
	
	while (NULL != SLNext(iter))
	{
		printf("%d,", *(int*)SLGetValue(iter));
		iter = SLNext(iter);
	}
}
