#include <stdio.h>
#include "priority_q.h"

int priorit(void *a, void *b)
{
	if (*(int*)a > *(int*)b)
	{
		return 1;
	}
	else if (*(int*)a == *(int*)b)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int main()
{

	pq_t *priority_q = PQCreate(priorit);
	return 0;
}
