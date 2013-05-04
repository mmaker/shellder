#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>


#include "process.h"
#include "utils.h"
#include "scheduler.h"

pthread_t schedt;
static pthread_attr_t schedta;

proc_t** ps = NULL;
size_t psize = 0;
static int HEAPLEN = 10;

struct timespec SCHEDULE_FREQ = {
    .tv_sec = 1,
    .tv_nsec = 0,
};

#define PRIORITY(p)      1
#define DELAY()          nanosleep(&SCHEDULE_FREQ, NULL);


/*
 * -- HEAP FUNCTIONS
 * Scheduler performes partial sorting of the processes queue using a binary
 * heap, and the function impolemented below, following MIT's Introduction to
 * Algorithms. Wondering why standard c does not provide any macro for that.
 */

#define CLEFT(node)      node << 1
#define CRIGHT(node)     (node << 1) + 1
#define PARENT(node)     node / 2
#define PSMAX            ps[0]
#define PSWAP(fst, snd)  {\
        proc_t* swap = ps[fst];  \
        ps[fst] = ps[snd];       \
        ps[snd] = swap;          \
    }

static void heapify(int i)
{
    int l = CLEFT(i),
        r = CRIGHT(i);
    int largest;

    if (l < psize && ps[l] > ps[i])       largest = l;
    else                                  largest = i;
    if (r < psize && ps[r] > ps[largest]) largest = r;

    if (largest != i) {
        PSWAP(i, largest);
        heapify(largest);
    }
}



proc_t*  pspop()
{
    proc_t* p = PSMAX;

    if (psize < 1) return NULL;

    PSMAX = ps[--psize];
    heapify(0);
    return p;
}

void psinsert(proc_t* node)  {
    size_t i;

    node->priority = PRIORITY(node);
    ps[psize++] = node;

    for (i = psize-1;
         i > 0 && i < psize && ps[i]->priority > ps[PARENT(i)]->priority;
         i=PARENT(i))
        PSWAP(i, PARENT(i));
}



/*
 * -- SCHEDULER MANAGIN' UCNTION
 */

void* _init_sched(void *_)
{
    proc_t* p;

    while (1) {
        if (!(p = pspop())) { DELAY(); continue; }

        fprintf(stdout, "\n[resume %s on pid %d]\n",
                        p->name,
                        p->pid);
        pcont(p);
        DELAY();
        pstop(p);
        plog(p);
        if (!palive(p)) pdel(p);
        else            psinsert(p);
    }
    return NULL;
}


void start_scheduler()
{
    /* set up process queue */
    ps = malloc(sizeof(proc_t*) * HEAPLEN);

    /* set up attributes for thread. */
    pthread_attr_init(&schedta);
    pthread_attr_setdetachstate(&schedta, PTHREAD_CREATE_DETACHED);
    pthread_create(&schedt, &schedta, _init_sched, NULL);
}

void stop_scheduler()
{
    /* clean up thread attributes.
    pthread_exit(NULL);
    */
    ;
}
