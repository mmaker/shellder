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

const struct dbgf_t  {
    const char* name;
    int (*funct) (int argc, char** argv);
} dbgop[] = {
    {.name="ps", .funct=processes},
    {.name="pd", .funct=pd},
    {.name=NULL, .funct=NULL},
};


