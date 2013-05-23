#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <error.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <syslog.h>
#include <pthread.h>

#include "process.h"
#include "utils.h"

/* please remove this shit. */
#define MAX_WORDS 8

extern int errno;

static const int lenpn = 10;
static const int BUF = 256;

FILE* shell_out;

static pid_t popen2(char* command, char** args, int* outfp)
{
    int poutfno[2];
    pid_t pid;

    if (pipe2(poutfno, O_NONBLOCK))
        EXIT_ERRNO();

    pid = fork();
    if (pid < 0) {
        EXIT_ERRNO();
    } else if (pid == 0) {
        //close(poutfno[0]);
        dup2(poutfno[1], STDOUT_FILENO);

        execvp(command, args);
        EXIT_ERRNO();
    } else {
        close(poutfno[1]);
        if (!outfp) close(poutfno[0]);
        else        *outfp = poutfno[0];
        return pid;
    }

    return 0;
}

proc_t* pnew(char* cmd) {
    proc_t* p;

    p = malloc(sizeof(proc_t));
    if (!p) EXIT_ENOMEM();

    p->name = strdup(cmd);
    if (!p->name) EXIT_ENOMEM();

    char** words = calloc(MAX_WORDS, sizeof(char*));
    size_t count=0;
    split(p->name, &words, &count);
    p->pid = popen2(words[0], words, &p->outfno);
    return p;
}

void pdel(proc_t* p)
{
    /* wait for the process to terminate; avoid zombie processes. */
    waitpid(p->pid, NULL, 0);
    free(p->name);
    free(p);
}

void pstop(proc_t* p)
{
    // syslog(LOG_NOTICE, "'%s' STOP %d ", p->name, time(NULL));
    if (kill(p->pid, SIGSTOP) != 0)
        error_at_line(1, errno, __FILE__, __LINE__, NULL);
}

void pcont(proc_t* p)
{
    // syslog(LOG_NOTICE, "'%s' CONT %d", p->name, time(NULL));
    if (kill(p->pid, SIGCONT) != 0)
        error_at_line(1, errno, __FILE__, __LINE__, NULL);

}


uint8_t palive(const proc_t* p)
{
    return !waitpid(p->pid, NULL, WNOHANG);
}

void plog(const proc_t* p)
{
    char* buf = malloc(sizeof(char) * BUF);
    if (!buf) EXIT_ENOMEM();

    while (read(p->outfno, buf, BUF) > 0)
        fprintf(shell_out, buf);
    fflush(shell_out);
    free(buf);
}

