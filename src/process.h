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

/**
 * \struct proc_t
 * \brief process informations.
 *
 * \detail A `proc_t` object holds all necessary informations to deal with a forked
 *         process.
 */
typedef struct proc_t {
    /** pid associated with the child. 0 if unknown. */
    pid_t pid;
    /** the priority of the current process. */
    long double priority;
    /** a human-readable string identifying the process. */
    char* name;
    /** file descriptor for the stdout of the child process. */
    int outfno;
} proc_t;


/**
 * \brief add a new process to the chain of active processes.
 * \param cmd the command to be executed.
 * \return a new proc_t structure generated from `cmd`.
 *
 * \detail this call inserts a new process into the queue. Note that calling
 *         `pnew()` is not thread-safe, and behavior is not defined for
 *         processes with equal priority.
 */
proc_t* pnew(char* cmd);

/**
 *  \brief remove a process from the chain of active processes.
 *  \param p the process to be removed from the queue.
 *  \return 0 if the chain is empty, its root otherwise.
 *
 *  \detail only the first occurrence of `pattern` will be removed,
 *          any other match is ignored.
 */
void pdel(proc_t* p);


/**
 * \brief stops a process
 * \param p the process to be stopped.
 *
 * \detail wrapper around the `kill -SIGSTOP`, which checks for errors.
 */
void pstop(proc_t* p);

/**
 * \brief unblock a stopped process.
 * \param p the process to be continued.
 *
 * \detail wrapper around the `kill -SIGCONT`, which checks for errors.
 */
void pcont(proc_t* p);

/**
 * \brief logs data from a process'stdout.
 *
 * \detail iterates though the file descriptor of `p`, and store its stdout on
 *         the log file prompted from the user.
 */
void plog(const proc_t *p);


/**
 * \brief checks if a process is still running.
 * \param p the process to be checked.
 * \return true if the process `p` is still processing, false otherwise.
 */
uint8_t palive(const proc_t *p);

#endif
