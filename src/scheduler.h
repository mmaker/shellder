/**
 * \file scheduler.h
 * \brief thread for scheduling and managinf processes.
 *
 */
#include <pthread.h>

extern pthread_t schedt;

void start_scheduler();
void stop_scheduler();
