#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "process.h"
#include "utils.h"
#include "dbg.h"
#include "locale.h"
#include "scheduler.h"

char* PS1 = ">>> ";
char* slogf = "shellder.log";


/**
 * \brief Prints out an help for each command line argument, then exit.
 *
 */
static void usage()
{
    fprintf(stderr, "%s usage: %s [-l slogfile] [-p prompt]\n",
            program_invocation_short_name, program_invocation_name);
}

/**
 * \brief process a debug command.
 *
 */
void process_dbg(char *line) {
    struct dbgf_t const * it;

    for (it = dbgop; it->name; it++)
        if (!strcmp(line, it->name)) {
             (*(it->funct))(0, NULL);
             return;
        }
    fprintf(stderr, "shellder: command not found.\n");
}

/**
 * \brief executes a command.
 */
void process_cmd(char *line) {
    proc_t* p = pnew(line);
    pstop(p);
    psinsert(p);
    printf("[%s on proc %d]\n", p->name, p->pid);
}

int main(int argc, char** argv)
{
    char opt;
    extern char* slogf;
    setlocale(LC_ALL, "");

    while ((opt = getopt(argc, argv, "l:h:p")) != EOF)
        switch (opt) {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'l':
                slogf = optarg;
                break;
            case 'p':
                PS1 = optarg;
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
    }
    main_shellder();

    return 0;
}


void main_shellder()
{
    char* line = NULL;
    start_scheduler();

    while ((line = readline(PS1)) != 0) {
        /* possible leak when pressing return. XXX */
        if (!*line)                 continue;
        else if (line[0] == '%')    process_dbg(line+1);
        else                        process_cmd(line);

        add_history(line);
        free(line);
    }
    fprintf(stdout, "exit\n");

    stop_scheduler();
    /* streams are flushed automagically here:
     * https://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html
     */
    exit(EXIT_SUCCESS);
}
