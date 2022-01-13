#ifndef __DVECTOR_H__
#define __DVECTOR_H__

#include <stddef.h> /* size_t */

/* OL110 version: 1 */


typedef struct vector vector_t;

vector_t *DVectorCreate(size_t capacity);
void DVectorDestroy(vector_t *vector);

void DVectorSet(vector_t *vector, size_t index, void *element);
void *DVectorGet(const vector_t *vector, size_t index);
int DVectorPushBack(vector_t *vector, void *element);  
size_t DVectorGetSize(const vector_t *vector);
size_t DVectorGetCapacity(const vector_t *vector);
void *DVectorPopBack(vector_t *vector); 


int DVectorReserve(vector_t *vector, size_t new_capacity); 
int DVectorShrinkToFit(vector_t *vector); 

int IsEmpty(const vector_t *vector);
int IsFull(vector_t *vector) ;
#endif /* __DVECTOR_H__ */


