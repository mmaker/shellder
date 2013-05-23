#ifndef __PROCESS_H__
#define __PROCESS_H__
/**
 * \file process.h
 * \brief Structures and operations over processses.
 *
 * \detail This file holds the base struct proc_t and declares the basics fucntions to
 *         interact with it.
 */
#include <stdint.h>
#include <sys/types.h>


extern FILE* shell_out;


typedef struct proc_t {
    pid_t pid;                 /* pid associated with the child. 0 if unknown. */
    long double priority;          /* the priority of the current process. */
    char* name;              /* a human-readable string identifying the process. */
    int outfno;             /* file descriptor for the stdout of the child process. */
} proc_t;


/*
 * \brief add a new process to the chain of active processes.
 * \param cmd the command to be executed.
 * \return a new proc_t structure generated from `cmd`.
 */
proc_t* pnew(char* cmd);

/*
 *  \brief remove a process from the chain of active processes.
 *  \detail only the first occurrence of `pattern` will be removed,
 *          any other match is ignored.
 *  \param pattern pattern.
 *  \return 0 if the chain is empty, its root otherwise.
 */
void pdel(proc_t* p);

void pstop(proc_t* p);
void pcont(proc_t* p);
void plog(const proc_t *);
uint8_t palive(const proc_t *);


/*
 * \brief Executes the given command, forking the process and then substituing
 *        its memory space.
 * \param cmd The command to be executed.
 * \return to be defined. XXX.
 *
 */
int run(char* cmd);

#endif
