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
#include <syslog.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "process.h"
#include "utils.h"
#include "dbg.h"
#include "locale.h"
#include "scheduler.h"

char* PS1 = ">>> ";
int log_options = LOG_CONS | LOG_NOWAIT;

char* shell_out_fname = "/tmp/shellder.log";


/**
 * \brief Prints out an help for each command line argument, then exit.
 *
 */
static void usage()
{
    static const char* help =  "%s usage: %s "
                               "[-l logfile ] "
                               "[-p prompt] "
                               "[-A a] "
                               "[-B b] "
                               "[-T microseconds] "
                               "\n";
    fprintf(stderr, help,
            program_invocation_short_name,
            program_invocation_name);
}

/**
 * \brief process a debug command.
 *
 */
void process_dbg(char *line) {
    struct dbgf_t const * it;
    int ret;

    char** argv = (char**) calloc(8, sizeof(char*));
    size_t argc;

    split(line, &argv, &argc);

    for (it = dbgop; it->name; it++)
        if (!strcmp(line, it->name)) {
             ret = (*(it->funct))(argc, argv);
             if (ret) fprintf(stderr, "!%d\n", ret);
             goto quit;
        }
    fprintf(stderr, "shellder: command not found.\n");
quit:
    free(argv);
    return;
}

/**
 * \brief executes a command.
 */
void process_cmd(char *line) {
    proc_t* p = pnew(line);
    pstop(p);
    psinsert(p);
//     printf("[%s on proc %d]\n", p->name, p->pid);
}

int main(int argc, char** argv)
{
    char opt;
    setlocale(LC_ALL, "");

    while ((opt = getopt(argc, argv, "l:h:p:A:B:T:")) != EOF)
        switch (opt) {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'l':
                 shell_out_fname = optarg;
                break;
            case 'p':
                PS1 = optarg;
                break;
            case 'A':
                _a = atof(optarg);
                break;
            case 'B':
                _b = atof(optarg);
                break;
            case 'T':
                _t = atoi(optarg);
                break;
            case '?':
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
    openlog(program_invocation_short_name, log_options, LOG_USER);
    shell_out = fopen(shell_out_fname, "w");

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
    /* optional */
    closelog();
    /* streams are flushed automagically here:
     * https://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html
     */
    exit(EXIT_SUCCESS);
}
