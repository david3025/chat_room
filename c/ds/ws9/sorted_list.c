#include <stdio.h> /*printf*/
#include <stdlib.h>/*malloc free*/
#include <assert.h>
#include "dlist.h"
#include "sorted_list.h"



struct dl_node * GetNode(sr_iter_t iter)
{
	return iter.dl_iter.internal;
}

struct sorted_list
{
    dlist_t *dlist;
    int (*compare)(const void *d1, const void *d2);
};

static sr_iter_t ChangeToSRIter(dl_iter_t dl_iter)
{
    sr_iter_t sr_iter;

    sr_iter.dl_iter = dl_iter;

    return sr_iter;
}
/*----------------------------------------------------------*/

sr_list_t *SortedLCreate(int (*compare)(const void *d1, const void *d2))
{
	sr_list_t *list = (sr_list_t *)malloc(sizeof(*list));
	
	if (!list)
	{
		return NULL;
	}
	
	list->dlist = DLCreate();
	
	if (!list->dlist)
	{
		free(list);
		list = NULL;
		
		return NULL;
	}
	
	list->compare = compare;
	
	return list;
}

void SortedLDestroy(sr_list_t *srlist)
{
	assert(srlist);
	
	DLDestroy(srlist->dlist);
	srlist->dlist = NULL;
	
	free(srlist);
	srlist = NULL; 
}


/*----------------------------------------------------------*/

int PrinttData(void *data, void *param) 
{
	printf("%d ", *(int*)data);
	(void)param;
	
	return 0;
}  

void PrintSrList(sr_list_t *srlist)
{
	void *param = 0;
	assert(srlist);
	
	SortedLForEach(SortedLBegin(srlist),
	     SortedLEnd(srlist), PrinttData, param);
	printf("\n");
}

sr_iter_t SortedLBegin(const sr_list_t *srlist)
{
	assert(srlist);
	
	return ChangeToSRIter(DLBegin(srlist->dlist));;
}

sr_iter_t SortedLEnd(const sr_list_t *srlist)
{
	assert(srlist);

	return ChangeToSRIter(DLEnd(srlist->dlist));
}

sr_iter_t SortedLNext(sr_iter_t iter)
{
	assert(GetNode(iter));
	
	return ChangeToSRIter(DLNext(iter.dl_iter));
}

sr_iter_t SortedLPrev(sr_iter_t iter)
{
	assert(GetNode(iter));
	
	return ChangeToSRIter(DLPrev(iter.dl_iter));
}
/*----------------------------------------------------------*/

int SortedLIsIterEqual(sr_iter_t i1, sr_iter_t i2)
{
	assert(GetNode(i1));
	assert(GetNode(i2));		
	
	return DLIsIterEqual(i1.dl_iter, i2.dl_iter);
}

size_t SortedLSize(const sr_list_t *srlist)
{
	assert(srlist);
	
	return DLSize(srlist->dlist);
}

int SortedLIsEmpty(const sr_list_t *srlist)
{
	assert(srlist);
	
	return DLIsEmpty(srlist->dlist);
}


void *SortedLGetData(sr_iter_t iter)
{
	assert(GetNode(iter));
	
	return DLGetData(iter.dl_iter);
}

/*--------------------------------------------------------*/

sr_iter_t SortedLFind(sr_iter_t from, sr_iter_t to, 
    const void *data, sr_list_t *srlist)
{	
	sr_iter_t iter;
	
	assert(GetNode(from));
	assert(GetNode(to));
	
	iter = from;
	
	while(!(SortedLIsIterEqual(iter, to)))
	{
		if((!srlist->compare(SortedLGetData(iter), data)))
		{
			break;
		}
		
		iter = SortedLNext(iter);
	}
	
	return iter;
}

  
sr_iter_t SortedLInsert(sr_list_t *srlist, void *data)
{
	sr_iter_t iter_run;
	sr_iter_t iter_end;
	
	assert(srlist);
	
	iter_run = SortedLBegin(srlist);
	iter_end = SortedLEnd(srlist);
	
	while (!(SortedLIsIterEqual(iter_run, iter_end)))
	{
		if (0 > (srlist->compare(data, SortedLGetData(iter_run))))
		{
			break;
		}
		
		iter_run = SortedLNext(iter_run);
	}
	
	iter_run = ChangeToSRIter(DLInsert(iter_run.dl_iter, data));
	
	if(!(GetNode(iter_run)))
	{
		return iter_end;
	}
	
	return iter_run;
}

sr_iter_t SortedLRemove(sr_iter_t iter)
{
	assert(GetNode(iter));
	
	return ChangeToSRIter(DLRemove(iter.dl_iter));
}


void *SortedLPopBack(sr_list_t *srlist)
{
	assert(srlist);
	
	return DLPopBack(srlist->dlist);
}

void *SortedLPopFront(sr_list_t *srlist)
{
	assert(srlist);
	
	return DLPopFront(srlist->dlist);
}

/*----------------------------------------------------------*/


void SortedLMerge(sr_list_t *dest, sr_list_t *src)
{
	sr_iter_t iter_src = SortedLBegin(src);
		
	
	while (!SortedLIsIterEqual(iter_src, SortedLEnd(src)))
	{
		
		SortedLInsert(dest, SortedLGetData(iter_src));
		
		iter_src = SortedLRemove(iter_src);
	}
	
}

int CompareDlData(sr_list_t *l1, sr_list_t *l2)
{
	sr_iter_t iter_l1 = SortedLBegin(l1);
	sr_iter_t iter_l2 = SortedLBegin(l2);
	int is_compare = 1;	
	
	while (!SortedLIsIterEqual(iter_l1, SortedLEnd(l1)) && is_compare)
	{
		is_compare = *(int*)SortedLGetData(iter_l1) == *(int*)SortedLGetData(iter_l2);
		
		iter_l1 = SortedLNext(iter_l1);
		iter_l2 = SortedLNext(iter_l2);
	}
	
	return is_compare;
}

/*----------------------------------------------------------*/


int SortedLForEach(sr_iter_t from, sr_iter_t to,
    int (*action)(void *data, void *param), void *param)
{
	
	assert(GetNode(from));
	assert(GetNode(to));
	
	return DLForEach(from.dl_iter, to.dl_iter, action, param);
}

/*----------------------------------------------------------*/
sr_iter_t SortedLFindIf(sr_iter_t from, sr_iter_t to, 
    const void *data, int (*is_match)(const void *, const void *))
{
	assert(GetNode(from));
	assert(GetNode(to));
	
	return ChangeToSRIter(DLFind(from.dl_iter, to.dl_iter, data, is_match));
}













