#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include <pthread.h>
#include <unistd.h>

/**
 * \file scheduler.h
 * \brief thread for scheduling and managinf processes.
 *
 */

/** root of the chain. NULL if no process is present on the queue. */
extern proc_t** ps;
extern size_t psize;
extern pthread_mutex_t qmutex;

extern unsigned long int _t;
extern long double _a, _b;


/**
 * \brief start the sheduler.
 *
 * \detail create a new thread for the scheduler, launching its main loop.
 */
void start_scheduler(void);

/**
 * \brief shut down the scheduler.
 *
 * \detail right now, does. nothing.
 */
void stop_scheduler(void);

/**
 * \brief remove a process from the queue.
 * \return process with maximum priority
 *
 * \detail Pops out the process with highest priority.
 */
proc_t* pspop();

/**
 * \brief insert a new process into the queue.
 *
 * \detail insert a new process, swapping parents until the tree is sorted.
 */
void psinsert(proc_t* node);

#endif
