#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "shell.h"
#include "process.h"
#include "utils.h"


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


void main_shellder(char* slogfile)
{
   size_t n=1;
   int end=0;
   char* cmd = malloc(sizeof(char));

   assert (!logfile);
   logfile = fopen(slogfile, "w");

   while (!end) {
      printf(PS1);
      /*acquire the string */
      getline(&cmd, &n, stdin);

      strip(&cmd, &n);
      split(cmd);


      /* log. XXX. remove flushing? */
      fprintf(logfile, "$ %s", cmd);
      fflush(logfile);


      /* process */
      end = !strcmp(cmd, "exit");
   }

   fclose(logfile);

   exit(0);
}


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
