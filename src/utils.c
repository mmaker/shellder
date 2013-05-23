#include <string.h>
#include <ctype.h>

#include "utils.h"

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


size_t split(char* s, char*** argvp, size_t* argcp)
{
    char** argv = *argvp;
    size_t argc;

    argv[0] = strtok(s, " ");
    for (argc=1; argc!=8; argc++)
        if (!(argv[argc] = strtok(NULL, " "))) break;

    return *argcp = argc;
}

