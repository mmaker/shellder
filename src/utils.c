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


char* split(char* s)
{
   /* XXX. please implement me */
   return strtok(s, " \t");
}

