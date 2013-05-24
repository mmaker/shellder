#ifndef __DBG_H__
#define __DBG_H__
/**
 * \brief function "pd" (Print Deus) tests out funny stuff with unicode data.
 * \return always 42
 *
 */
int pd(int argc, char** argv);

/**
 * \brief fucntion "ps" (Processes Status) prints out the chain of processes in
 *        queue.
 *
 */
int processes(int argc, char** argv);

int set(int argc, char** argv);

int dbghelp(int argc, char** argv);

struct dbgf_t  {
    const char* name;
    int (*funct) (int argc, char** argv);
    const char* desc;
};

extern const struct dbgf_t dbgop[];

#endif
