#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"

pthread_t schedt;
static pthread_attr_t schedta;


void* _init_sched(void *_)
{
    printf("whoa, this is a thread, br0. ");
    return NULL;
}


void start_scheduler()
{
    /* set up attributes for thread. */
    pthread_attr_init(&schedta);
    pthread_attr_setdetachstate(&schedta, PTHREAD_CREATE_DETACHED);
    pthread_create(&schedt, &schedta, _init_sched, NULL);
}

void stop_scheduler()
{
    /* clean up thread attributes. */
    pthread_exit(NULL);
}
