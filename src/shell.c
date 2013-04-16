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


extern int errno;
extern char* optarg;
extern char* PS1;
extern char* program_invocation_name;
extern char* program_invocation_short_name;

char* logf = "shellder.log";


/**
 * \brief Prints out an help for each command line argument, then exit.
 *
 */
static void usage()
{
    fprintf(stderr, "%s usage: %s [-l logffile] [-p prompt]\n",
            program_invocation_short_name, program_invocation_name);
}


int main(int argc, char** argv)
{
    char opt;
    extern char* logf;

    while ((opt = getopt(argc, argv, "l:h:p")) != EOF)
        switch (opt) {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'l':
                logf = optarg;
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
    char* line;
    int logfno;

    assert (*logf);
    /*
    struct stat sb;
    if (stat(logf, &sb) < 0) {
        fprintf(stderr, "Error: bad file descriptor: %s\n", logf);
        exit(errno);
    }
    XXX. check stat file for writable, not directory.
    */
    logfno = open(logf, O_DIRECT|O_CREAT|O_WRONLY|O_TRUNC, 0644);

    while ((line = readline(PS1)) != 0) {
        if (!*line) continue;

        printf("[%s] on proc %d\n", line, 0);
        run(line);
        add_history(line);
        free(line);
    }
    fprintf(stdout, "\nexit\n");

    fflush(stdout);
    close(logfno);
    exit(EXIT_SUCCESS);
}


