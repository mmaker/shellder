#ifndef __DBG_H__
#define __DBG_H__
/**
 * \file dbg.h
 * \brief Debug operations on the shell.
 *
 * \detail This file implements all available debug options to be used at
 *         run-time.
 */

/**
 *
 * \brief easter egg
 * \return always 42
 *
 * \detail function "pd" (Print Deus) tests out funny stuff with unicode data.
 *
 */
int pd(int argc, char** argv);

/**
 * \brief debug the chain of processes.
 * \return always 0
 *
 * \detail function "ps" (Processes Status) prints out the chain of processes in
 *        queue.
 *
 */
int processes(int argc, char** argv);

/**
 * \brief chage scheduler constraints.
 * \return 0 in case of success, 1 otherwise
 *
 * \detail function "set" permits to tune scheduler constraints at run time.
 */
int set(int argc, char** argv);


/**
 * \brief list available commands
 *
 * \detail function "help" (DeBuG HELP) prints out the available commands to be
 *          used for monitoring the shell.
 */
int dbghelp(int argc, char** argv);


/**
 * \struct dbgf_t
 * \brief debug functions.
 *
 * \detail object to keep track of available debug functions.
 */
struct dbgf_t  {
    /** invocation name */
    const char* name;
    /** pointer to the procedure to be executed*/
    int (*funct) (int argc, char** argv);
    /** brief description, used for %help */
    const char* desc;
};

extern const struct dbgf_t dbgop[];

#endif
