#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "shell.h"


static const char* PS1 = ">>> ";
static FILE* logfile;

void strip(char**, size_t*);


int main(int argc, char** argv)
{
    char* exe = argv[0];
    char* log = "/tmp/shellder.log";
    size_t i;

    for (i=1; i!=argc; i++) {
        if (!strcmp(argv[i], "--help"))
            print_help(exe, 0);
        else if (!strcmp(argv[i], "-l") && i+1 < argc)
            log = argv[++i];
        else if (argv[i])
            print_help(exe, 1);
    }
    main_shellder(log);
    return 0;
}


/**
 * Removes trailing and leading whitespaces from a string.
 */
void strip(char **s, size_t* n)
{
    char *tmp;

    /* leading whitespaces */
    for (; isspace(**s); (*n)--)
        (*s)++;
    /* trailing whitespaces */
    for (tmp = *s + *n-1; isspace(*tmp); (*n)--)
        tmp--;

   (*s)[*n++] = '\0';
}



/**
 * Main loop for the shell.
 */
void main_shellder(char* slogfile)
{
   size_t n=1;
   int end=0;
   char* cmd = malloc(sizeof(char));
   logfile = fopen(slogfile, "w");

   while (!end) {
      printf(PS1);
      /*acquire the string */
      getline(&cmd, &n, stdin);
      strip(&cmd, &n);

      /* log. XXX. remove flushing? */
      fprintf(logfile, "$ %s", cmd);
      fflush(logfile);


      /* process */
      end = !strcmp(cmd, "exit");
   }

   fclose(logfile);

   exit(0);
}


/**
 * Prints out an help for each command line argument, then exit.
 */
void print_help(char* exe, int returncode)
{
    switch (returncode) {
        case 0 :
            printf("hey this is %s\n", exe);
            break;
        case 1:
            fprintf(stderr, "hey this is %s. Check for error\n", exe);
            break;
    }
    exit(returncode);
}
