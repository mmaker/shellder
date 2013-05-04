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

#include "process.h"
#include "utils.h"

extern int errno;

static const int lenpn = 10;
static const int BUF = 256;

static pid_t popen2(const char* command, int* outfp)
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

        execl("/bin/sh", "sh", "-c", command, NULL);
        EXIT_ERRNO();
    } else {
        close(poutfno[1]);
        if (!outfp) close(poutfno[0]);
        else        *outfp = poutfno[0];
        return pid;
    }
}

proc_t* pnew(const char* cmd) {
    proc_t* p;

    p = malloc(sizeof(proc_t));
    if (!p) EXIT_ENOMEM();

    p->name = strdup(cmd);
    if (!p->name) EXIT_ENOMEM();

    p->pid = popen2(cmd, &p->outfno);
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
    if (kill(p->pid, SIGSTOP) != 0)
        error_at_line(1, errno, __FILE__, __LINE__, NULL);
}

void pcont(proc_t* p)
{
    if (kill(p->pid, SIGCONT) != 0)
        error_at_line(1, errno, __FILE__, __LINE__, NULL);

}


uint8_t palive(const proc_t* p)
{
    return !waitpid(p->pid, NULL, WNOHANG);
}

void plog(const proc_t* p)
{
    /*
    assert (*slogf);
    struct stat sb;
    if (stat(slogf, &sb) < 0) {
        fprintf(stderr, "Error: bad file descriptor: %s\n", slogf);
        exit(errno);
    }
    XXX. check stat file for writable, not directory.
    slogfno = open(slogf, O_DIRECT|O_CREAT|O_WRONLY|O_TRUNC, 0644);
    close(slogfno);
    */
    char* buf = malloc(sizeof(char) * BUF);
    if (!buf) EXIT_ENOMEM();

    while (read(p->outfno, buf, BUF) > 0)
        fprintf(stdout, buf);
    free(buf);
}

