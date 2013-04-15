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

char* logf = "shellder.log";


/**
 * \brief Prints out an help for each command line argument, then exit.
 *
 */
static void usage(char* progname)
{
    fprintf(stderr, "%s usage: %s [-l logffile] [-p prompt]\n", progname, progname);
}


int main(int argc, char** argv)
{
    char* progname = argv[0];
    char opt;
    extern char* logf;

    while ((opt = getopt(argc, argv, "l:h:p")) != EOF)
        switch (opt) {
            case 'h':
                usage(progname);
                exit(EXIT_SUCCESS);
            case 'l':
                logf = optarg;
                break;
            case 'p':
                PS1 = optarg;
                break;
            default:
                usage(progname);
                exit(EXIT_FAILURE);
    }
    main_shellder();

    return 0;
}


void main_shellder()
{
    char* line;
    int logfno;
    int buf;

    assert (*logf);
    /*
    struct stat sb;
    if (stat(logf, &sb) < 0) {
        fprintf(stderr, "Error: bad file descriptor: %s\n", logf);
        exit(errno);
    }
    XXX. check stat file for writable, not directory.
    */
    logfno = open(logf, O_DIRECT | O_CREAT | O_WRONLY | O_TRUNC, 0644);
    buf = dup(1);
    dup2(logfno, 1);
    dup2(buf, 1);


    while ((line = readline(PS1)) != 0) {
        if (!*line) continue;

        printf("[%s] on proc %d\n", line, 0);
        /* all happens here */
        add_history(line);
        free(line);
    }
    fprintf(stdout, "\nexit\n");

    fflush(stdout);
    exit(EXIT_SUCCESS);
}


