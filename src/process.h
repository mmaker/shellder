/**
 * \file process.h
 * \brief Structures and operations over processses.
 *
 * \detail This file holds the base struct proc_t and declares the basics fucntions to
 *         interact with it.
 */


typedef struct proc_t {
    struct proc_t* next;     /* pointer to the next process in chain */
    struct proc_t* prev;     /* pointer to the previous process in chain */

    int pid;                 /* pid associated with the child. 0 if unknown. */
    char* name;              /* a human-readable string identifying the process. */
    FILE* out;               /* file descriptor for the stdout of the child process. */
} proc_t;


/* root of the chain. NULL if no process. is on queue. */
extern proc_t* ps;
/* reference to the next element of the last process in queue. */
extern proc_t** lst;


/*
 * \brief add a new process to the chain of active processes.
 * \param cmd the command to be executed.
 * \return a new proc_t structure generated from `cmd`.
 */
proc_t* add_proc(char* cmd);

/*
 *  \brief remove a process from the chain of active processes.
 *  \detail only the first occurrence of `pattern` will be removed,
 *          any other match is ignored.
 *  \param pattern pattern.
 *  \return 0 if the chain is empty, its root otherwise.
 */
proc_t* del_procc(char* pattern);

/*
 *  \brief remove a process from the chain of active processes.
 *  \param p the process to be removed.
 *  \return 0 if the chain is empty, its root otherwise.
 */
proc_t* del_procp(proc_t* p);


/*
 * \brief Executes the given command, forking the process and then substituing
 *        its memory space.
 * \param cmd The command to be executed.
 * \return to be defined. XXX.
 *
 */
int run(char* cmd);
