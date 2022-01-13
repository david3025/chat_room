/*-------------------------------c file --------------------------------#include */
#include <assert.h>     /* assert */
#include <sys/types.h>  /* pid_t, getpid */
#include "priority_q.h"
#include "scheduler.h"

struct scheduler
{
    pq_t *pq;
    task_t *running;
};

typedef struct
{
    int (*action)(void *param);
    void *param;
    int (*kill)(void *kill_param);
    void *kill_param;
    size_t interval;
    time_t run_time; 
    uuid_t uid;
} task_t;

~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~

#ifndef __OL110SCHEDULER_H__
#define __OL110SCHEDULER_H__

#include <stddef.h> /* size_t */
#include <time.h>   /* time_t */
#include "uid.h"    /* uuid_t */

typedef struct scheduler schedule_t;

/* O(1) */
/* creates an empty scheduler */
/* with a built-in prioritize function */
/* returns a pointer to it */
/* returns NULL on failure */
schedule_t *SchedCreate(void);

/* O(n) */
/* removes all tasks and frees all allocations */
void SchedDestroy(schedule_t *sched);

/* O(n) */
/* returns the amount of tasks scheduled */
size_t SchedSize(const schedule_t *sched);

/* O(1) */
/* returns 0 if there are tasks scheduled */
/* returns another number otherwise */
int SchedIsEmpty(const schedule_t *sched);

/* O(n) */
/* receives parameters for a task */
/* generates and inserts task appropriately */
/* returns a uid identifier for the task */
/* on failure, returns BAD_UID */
uuid_t SchedAddTask(schedule_t *sched, time_t run_time, size_t interval_in_sec, int (*action)(void *param), void *param, int (*kill)(void *kill_param), void *kill_param); 

/* O(n) */
/* finds a task associated with given uid */
/* removes selected task from schedule */
/* returns 0 if found and another number otherwise */
int SchedRemoveTask(schedule_t *sched, uuid_t uid);

/* O(n) */
/* removes all tasks */
void SchedClear(schedule_t *sched);

/* O(n) */
/* runs the scheduler */
/* if first task is of negative time, offsets all tasks by difference */
/* returns task exit status */
int SchedRun(schedule_t *sched);

/* O(1) */
/* terminates running task */
void SchedStop(schedule_t *sched);

#endif /* __OL110SCHEDULER_H__ */
