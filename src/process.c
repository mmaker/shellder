#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "process.h"

proc_t* ps = NULL;
proc_t** lst = &ps;
static const int lenpn = 10;

proc_t* add_proc(char* cmd) {

    proc_t *p;
    char* name = malloc(sizeof(char) * lenpn );

    p = malloc(sizeof(proc_t));
    p->next = NULL;
    p->prev = *lst;
    p->name = name;
    p->out = popen(cmd, "r");

    if (!ps) ps = p;
    lst = &(p->next);

    strncpy(p->name, cmd, lenpn);
    p->name[lenpn-1] = '\0';

    return p;
}

proc_t* del_procc(char* name) {
    /* XXX. please implement me. */
    return NULL;
}

proc_t* del_procp(proc_t* p) {
   if (p->next)
       p->next->prev = p->prev;
   if (p->prev)
       p->prev->next = p->next;

   if (p == ps)
       ps = p->next;
   if (p == *lst)
       lst = &p->prev;

   free(p->name);
   free(p);
   return ps;
}


int run(char* cmd)
{
    proc_t* p;
    char* buf = malloc(sizeof(char) * 1024);

    p = add_proc(cmd);
    while (fread(buf, sizeof(char), 1024, p->out))
        fprintf(stdout, buf);

    wait(NULL);
    del_procp(p);
    free(buf);
    return 0;
}



