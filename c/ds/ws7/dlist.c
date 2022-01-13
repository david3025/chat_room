#include <stdlib.h>/*malloc free*/
#include <assert.h>/*assert*/

#include "dlist.h"

#define NODE_P(iter) (iter).internal

typedef struct dl_node dl_node_t; 

struct dl_node
{
    dl_node_t *prev;
    dl_node_t *next;
    void *data;
}; 

struct dlist
{
    dl_node_t head;
    dl_node_t tail;
};



/*-------------------------------*/

dlist_t *DLCreate(void)
{
	dlist_t *dlist = (dlist_t*)malloc(sizeof(dlist_t));
	
	dlist->head.next = &dlist->tail;
	dlist->tail.prev = &dlist->head;
	
	dlist->head.prev = NULL;
	dlist->tail.next = NULL;
	
	dlist->head.data = NULL;
	dlist->tail.data = NULL;
	
	return dlist;
}

void DLDestroy(dlist_t *dlist)
{
    dl_iter_t iter = DLBegin(dlist);
    
    assert(dlist);

    while (!DLIsIterEqual(iter, DLEnd(dlist)))
    {
        iter = DLRemove(iter);
    }
    
    free(dlist);
}
/*--------------------------------------------*/

dl_iter_t DLBegin(const dlist_t *dlist)
{
	dl_iter_t iter;
	
	assert(dlist);
	iter.internal = dlist->head.next;
	
	return iter;
}

dl_iter_t DLEnd(const dlist_t *dlist)
{
	dl_iter_t iter;
	
	assert(dlist);
	iter.internal = (dlist->tail.prev)->next;
	
	return iter;
}

dl_iter_t DLNext(dl_iter_t dl_iter)
{
	dl_iter_t iter;
	
	dl_node_t *next_node = dl_iter.internal->next;
	assert(dl_iter.internal);
	
	iter.internal = next_node;

	return iter;
}

dl_iter_t DLPrev(dl_iter_t dl_iter)
{
	dl_iter_t iter;
	
	dl_node_t *next_node = dl_iter.internal->prev;
	assert(dl_iter.internal);
	
	iter.internal = next_node;

	return iter;
}

/*--------------------------------------------*/
int DLIsEmpty(const dlist_t *dlist)
{
	return DLIsIterEqual(DLBegin(dlist), DLEnd(dlist));
}

int DLIsIterEqual(dl_iter_t dl_i1, dl_iter_t dl_i2)
{
    assert(NODE_P(dl_i1) && NODE_P(dl_i2));
    return NODE_P(dl_i1) == NODE_P(dl_i2);
}

size_t DLSize(const dlist_t *dlist)
{
	size_t count = 0;
	dl_iter_t iter = DLBegin(dlist);
	
	assert(dlist);
	
	while (!DLIsIterEqual(iter, DLEnd(dlist)))
	{
		iter = DLNext(iter);
		count++;
	}
	
	return count;
}

void *DLGetData(dl_iter_t dl_iter)
{
	assert(dl_iter.internal);
	
	return dl_iter.internal->data;
}

void DLSetData(dl_iter_t dl_iter, void *data)
{
	dl_iter.internal->data = data;
}

/*----------------------------------------------------------*/
static dl_iter_t GetEnd(dl_iter_t iter)
{
    while (NULL != iter.internal->next)
    {
        iter = DLNext(iter);
    }
    return iter;
}

dl_iter_t CreatIter(void *data)
{
	dl_iter_t iter;
	dl_node_t *node = (dl_node_t*)malloc(sizeof(dl_node_t));
	node->data = data;
	
	iter.internal = node;
	iter.internal->next = NULL;
	iter.internal->prev = NULL;
	
	
	return iter;
}


void Conect2Iters(dl_iter_t it1, dl_iter_t it2)
{
	it1.internal->next = it2.internal;
	it2.internal->prev = it1.internal;
}
void ConectIterToTail(dl_iter_t last, dlist_t *dlist)
{
	last.internal->next = &dlist->tail;
	dlist->tail.prev = last.internal;
}
void ConectHeadToIter(dlist_t *dlist, dl_iter_t first)
{
	first.internal->prev = &dlist->head;
	dlist->head.next = first.internal;
}
/*----------------------------------------------------------*/
dl_iter_t DLPushFront(dlist_t *dlist, void *data)
{
	dl_iter_t first_iter = DLBegin(dlist);
	dl_iter_t new_iter = CreatIter(data);
	
	ConectHeadToIter(dlist, new_iter);
	Conect2Iters(new_iter, first_iter);
	
	return new_iter;
}

dl_iter_t DLPushBack(dlist_t *dlist, void *data)
{
	dl_iter_t last_iter = DLPrev(DLEnd(dlist));
	dl_iter_t new_iter = CreatIter(data);
	
	if (!NODE_P(new_iter))
	{
		return DLEnd(dlist); 
	}
	
	ConectIterToTail(new_iter, dlist);
	Conect2Iters(last_iter, new_iter);
	
	return new_iter;
}

void *DLPopFront(dlist_t *dlist)
{
	void *data = DLGetData(DLBegin(dlist));
	
	dl_iter_t remove = DLBegin(dlist);
	dl_iter_t secend_iter = DLNext(remove);
	
	ConectHeadToIter(dlist, secend_iter);
	
	free(remove.internal);
	remove.internal = NULL;
	
	return data;
}

void *DLPopBack(dlist_t *dlist)
{
	void *data = DLGetData(DLPrev(DLEnd(dlist)));
	
	dl_iter_t remove = DLPrev(DLEnd(dlist));
	dl_iter_t last_iter = DLPrev(remove);
	
	ConectIterToTail(last_iter, dlist);
		
	free(remove.internal);
	remove.internal = NULL;
	
	return data;
}

dl_iter_t DLInsert(dl_iter_t dl_iter, void *data)
{
	dl_iter_t new_iter = CreatIter(data);
	dl_iter_t prev_iter = DLPrev(dl_iter);
	
	if (!NODE_P(new_iter))
    {
        return GetEnd(dl_iter);
    }
    
	Conect2Iters(prev_iter, new_iter);
	Conect2Iters(new_iter, dl_iter);	
	
	return new_iter;
}



dl_iter_t DLRemove(dl_iter_t dl_iter)
{
	dl_iter_t remove = dl_iter;
	dl_iter_t next_iter = DLNext(dl_iter);
	
	Conect2Iters(DLPrev(dl_iter), next_iter);
	
	free(remove.internal);
	remove.internal = NULL;
	
	return next_iter;
}
/*----------------------------*/

int DLForEach(dl_iter_t from, dl_iter_t to,
int (*action)(void *data, void *param), void *param)
{
	dl_iter_t iter = from;
	int result = 0;
	
	assert(from.internal || to.internal);
	
	for (; !DLIsIterEqual(iter, to) && !result; iter = DLNext(iter))
	{
		result = action(DLGetData(iter), param);
	}
	
	return result;
}

dl_iter_t DLFind(dl_iter_t from, dl_iter_t to, const void *data, int (*is_match)(const void *, const void*))
{
	dl_iter_t iter = from;
	
	for (; !DLIsIterEqual(iter, to) ; iter = DLNext(iter))
	{
		if (is_match(DLGetData(iter), data))
		{
			break;
		}
	}

	return iter;
}	

int DLMultiFind(dl_iter_t from, dl_iter_t to, dlist_t *dest,
                const void *data, int (*is_match)(const void *, const void *))
{
    dl_iter_t iter = from;

    for (; !DLIsIterEqual(iter, to); iter = DLNext(iter))
    {
        if (is_match(DLGetData(iter), data))
        { 
            if (DLIsIterEqual(DLPushBack(dest, DLGetData(iter)), DLEnd(dest)))
            {
                return 1;
            }
        }
    }

    return 0;
}

/*------------------------------------------------*/


void DLSplice(dl_iter_t dest, dl_iter_t src_from, dl_iter_t src_to)
{
	dl_iter_t dest_prev = DLPrev(dest);
    dl_iter_t src_to_prev = DLPrev(src_to);
    dl_iter_t src_from_prev = DLPrev(src_from);
    
    Conect2Iters(dest_prev, src_from);
    Conect2Iters(src_to_prev, dest);
    Conect2Iters(src_from_prev, src_to);
}





































