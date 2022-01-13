#include <stdio.h>
#include <stdlib.h>/*malloc,free*/
#include <assert.h>/*assert*/
#include "s_list.h"

#define NODE_TO_ITER(node) (sl_iter_t)(node)
#define ITER_TO_NODE(iter) (sl_node_t*)(iter)



typedef struct sl_node
{
    void *data;
    struct sl_node *next;
    
} sl_node_t;


struct slist 
{
    sl_node_t *head;
    sl_node_t *end;
};

/*----------------------------------------------------*/

static sl_iter_t SLCreateNode(void *data)
{
	sl_node_t *node = (sl_node_t*)malloc(sizeof(sl_node_t));
	node-> next = NULL;
	node-> data = data;
	
	return node;
}

static sl_iter_t GetEndByIter(const sl_iter_t current)
{
    sl_iter_t i = current;
    
    while (i->next)
    {
        i = i->next;
    }

    return i;
}

static void SwapData(sl_iter_t iter)
{
	sl_node_t *node1 = ITER_TO_NODE(iter);
	sl_node_t *node2 = ITER_TO_NODE(SLNext(iter));
	void *temp_val = node1->data;
	
	node1->data = node2->data;
	node2->data = temp_val;
}

/*-----------------------------------------------------*/
size_t SLCount(const slist_t *list)
{
	size_t counter = 0;
	sl_iter_t iter = SLBegin(list);
	sl_iter_t end = SLEnd(list);
	
	assert(list);  
	
	while(!SLIterIsEqual(iter, end))
	{

		iter = SLNext(iter);
		
		counter++;
	}
	
	return counter;
}


int SLIsEmpty(const slist_t *list)
{
	int result = 0;
	
	assert(list);  
	
	if (SLBegin(list) == SLEnd(list))
	{
		result = 1;
	}
	
	return result;
}

/*-----------------------------------------------------*/

slist_t *SLCreate()
{
	slist_t *list = (slist_t*)malloc(sizeof(slist_t));
	
	list->end = (sl_node_t*)malloc(sizeof(sl_node_t));
	
	list->head = list->end;
	
	list->end->next = NULL;
	list->end->data = list;
	
	return list;
}

void SLDestroy(slist_t *list)
{
	sl_node_t *node = SLBegin(list);
	sl_node_t *end = SLEnd(list);
	sl_node_t *next;
	
	assert(list);  
	
	while(node != end)
	{
		next = SLNext(node);
		free(node);
		node = next;
	}
	
	free(node);
	node = NULL;
	
	free(list);
	list = NULL;
}
/*-----------------------------------------------------*/
int SLIterIsEqual(const sl_iter_t iter1, const sl_iter_t iter2)
{
    return (iter1 == iter2);
}

void *SLGetValue(const sl_iter_t iter)
{
	return iter->data;
}
void SLSetValue(sl_iter_t iter, void *data)
{
	iter->data = data;
}
/*-----------------------------------------------------*/
sl_iter_t SLEnd(const slist_t *list)
{
    return list->end;
}

sl_iter_t SLBegin(const slist_t *list)
{
    return list->head;
}

sl_iter_t SLNext(const sl_iter_t iter)
{
    return iter->next;
}

/*-----------------------------------------------------*/

sl_iter_t SLAddAfter(sl_iter_t iter, void *data)
{
	 sl_node_t *node = SLCreateNode(data);
	 
	 assert(iter);
	 
	 if (!node)
     {
        return GetEndByIter(iter);
     }
     
	 node->next = iter->next;
	 iter->next = node;
	  
	 return iter;
}

sl_iter_t SLAddBefore(sl_iter_t iter, void *data)
{
	sl_node_t *node = SLCreateNode(data);
	
	assert(iter);
	
	if (!node)
    {
        return GetEndByIter(iter);
    }
	 
	if(NULL == iter->next)
	{
		slist_t *list = (slist_t *)iter->data;
		
		list->end = node;
		iter->data = data;
		iter->next = node;
		node->data = list;
	 	
	 	return iter;
	}

	node->next = iter->next;
	iter->next = node;
	SwapData(iter);
	
	return iter;
}

/*-----------------------------------------------------*/
sl_iter_t SLRemoveAfter(sl_iter_t iter)
{	
	sl_node_t *temp_node = iter->next;
	
	assert(iter);
	
	iter->next = temp_node->next;
	
	free(temp_node);
	
	return iter;
}

sl_iter_t SLRemove(sl_iter_t iter)
{
	assert(iter);
	
	if (NULL == iter->next->next)
	{
		slist_t *list;
		
		iter->data = iter->next->data;
		list = (slist_t *)iter->data;
		
		list->end = iter;
		
		free(iter->next);
		iter->next = NULL;
		
		return iter;
	}
	
	iter->data = iter->next->data;
	
	return SLRemoveAfter(iter);
}

/*-----------------------------------------------------*/



int SLForEach(sl_iter_t start, sl_iter_t end, int (*Action)(void * data, void *param), void *param)
{
	sl_iter_t iter = start;
	int result = 0;
	
	assert(start || end);
	
	for (; !SLIterIsEqual(iter, end) && !result; iter = SLNext(iter))
	{
		result = Action(SLGetValue(iter), param);
	}
	
	return result;
}
/*---------------------------------------------------*/

sl_iter_t SLFind(const slist_t *list, const void * data, int (*CompareTo)(const void *, const void *))
{
	sl_iter_t end = SLEnd(list);
	sl_iter_t iter = SLBegin(list);
	
	sl_iter_t result_iter = NULL;
	int is_different = 1;
	
	assert(list);
	
	for (;!SLIterIsEqual(iter, end) && is_different; iter = SLNext(iter))
	{
		is_different = CompareTo(SLGetValue(iter), data);
		
		if (!is_different)
		{
			result_iter = iter;
		}
	}

	return result_iter;
}
/*---------------------------------------------------*/

void SLAppend(slist_t *base,  slist_t *append)
{
	assert(base || append);
	
	SLSetValue(SLEnd(base), SLGetValue(SLBegin(append)));
	SLEnd(base)->next = SLNext(SLBegin(append));
	
	SLSetValue(SLEnd(append),base);
	base->end = SLEnd(append);
	
	SLBegin(append)->next = NULL;
	SLSetValue(SLBegin(append), append);
	append->end = SLBegin(append);
	
}


