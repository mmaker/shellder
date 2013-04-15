/**
 * \file process.h
 * \brief Structures and operations over processses.
 *
 * \detail This file holds the base struct proc_t and declares the basics fucntions to
 *         interact with it.
 */


typedef struct {
} proc_t;


/**
 * \brief Executes the given command, forking the process and then substituing
 *        its memory space.
 * \param cmd The command to be executed.
 *
 */
int run(char* cmd);
