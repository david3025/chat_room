/******************************************************************************
* Author        
* Reviewer      
* Description   Priority_Queue
* Group         
* Company       
* ****************************************************************************/

#include <assert.h> /* assert*/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#include "sorted_list.h"
#include "priority_q.h"

struct priority_q
{
    sr_list_t *srlist;
};


pq_t *PQCreate(int (*prioritize)(const void *data1, const void *data2))
{
    pq_t *priority_queue = malloc(sizeof(*priority_queue));

    assert(prioritize);

    if (!priority_queue)
    {
        return NULL;
    }

    priority_queue->srlist = SortedLCreate(prioritize);
    if (!priority_queue->srlist)
    {
        free(priority_queue);
        return NULL;
    }

    return priority_queue;
}


void PQDestroy(pq_t *prior_q)
{
    assert(prior_q);
    assert(prior_q->srlist);

    SortedLDestroy(prior_q->srlist);
    prior_q->srlist = NULL;

    free(prior_q);
    prior_q = NULL;
}


/* Empty && Size */
/******************************************************************/
int PQIsEmpty(const pq_t *prior_q)
{
    assert(prior_q);
    assert(prior_q->srlist);

    return SortedLIsEmpty(prior_q->srlist);
}


size_t PQSize(const pq_t *prior_q)
{
    assert(prior_q);
    assert(prior_q->srlist);

    return SortedLSize(prior_q->srlist);
}


/* Enqueue && Dequeue */
/******************************************************************/
int PQEnqueue(pq_t *prior_q, void *data)
{
    assert(prior_q);
    assert(prior_q->srlist);

    return SortedLIsIterEqual(SortedLInsert(prior_q->srlist, data),
           SortedLEnd(prior_q->srlist));
}


void *PQDequeue(pq_t *prior_q)
{
    assert(prior_q);
    assert(prior_q->srlist);

    return SortedLPopBack(prior_q->srlist);
}


/* Peek && Erase */
/******************************************************************/
void *PQPeek(const pq_t *prior_q)
{
    assert(prior_q);
    assert(prior_q->srlist);

    return SortedLGetData(SortedLPrev(SortedLEnd(prior_q->srlist)));
}


void *PQErase(pq_t *prior_q, const void *data)
{
    sr_iter_t iter;
    void *found_data = NULL;

    assert(prior_q);
    assert(prior_q->srlist);

    iter = SortedLFind(SortedLBegin(prior_q->srlist),
           SortedLEnd(prior_q->srlist), data, prior_q->srlist);

    if (SortedLIsIterEqual(iter, SortedLEnd(prior_q->srlist)))
    {
        return NULL;
    }
    else
    {
        found_data = SortedLGetData(iter);
        SortedLRemove(iter);
        return found_data;
    }
}


/* Erase_If */
/******************************************************************/
void *PQEraseIf(pq_t *prior_q, const void *criteria,
    int (*is_match)(const void *data, const void *criteria))
{
    sr_iter_t iter;
    void *found_data = NULL;

    assert(prior_q);
    assert(prior_q->srlist);

    iter = SortedLFindIf(SortedLBegin(prior_q->srlist),
           SortedLEnd(prior_q->srlist), criteria, is_match);

   if (SortedLIsIterEqual(iter, SortedLEnd(prior_q->srlist)))
   {
       return NULL;
   }
   else
   {
       found_data = SortedLGetData(iter);
       SortedLRemove(iter);
       return found_data;
   }
}


/* Clear */
/******************************************************************/
void PQClear(pq_t *prior_q)
{
    sr_iter_t iter;
    size_t i = 0;
    size_t len = 0;

    assert(prior_q);
    assert(prior_q->srlist);

    len = PQSize(prior_q);
    iter = SortedLBegin(prior_q->srlist);

    for (i = 0; i < len; ++i)
    {
        iter = SortedLRemove(iter);
    }
}




/* space */
