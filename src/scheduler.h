#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

/**
 * \file scheduler.h
 * \brief thread for scheduling and managinf processes.
 *
 */
#include <pthread.h>
#include <unistd.h>


extern pthread_t schedt;

extern struct timespec SCHEDULE_FREQ;
/* root of the chain. NULL if no process. is on queue. */
extern proc_t** ps;
extern size_t psize;

extern unsigned int _t;
extern float _a, _b;


void start_scheduler();
void stop_scheduler();
proc_t* pspop();
void psinsert(proc_t* node);

#endif
