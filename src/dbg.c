#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "process.h"
#include "scheduler.h"
#include "dbg.h"

const struct dbgf_t dbgop[] = {
    {.name="ps",    .funct=processes,    .desc="list current processes"},
    {.name="pd",    .funct=pd,           .desc=""},
    {.name="set",   .funct=set,          .desc="tune constraints"},
    {.name="help",  .funct=dbghelp,      .desc="print help"},
    {.name=NULL,    .funct=NULL,         .desc=NULL},
};


int pd(int argc, char** argv)
{
    printf("%ls", L"Pater Noster qui es in cælis:\n"
            "sanctificétur nomen tuum;\n"
            "advéniat regnum tuum;\n"
            "fiat volúntas tua,\n"
            "sicut in cælo, et in terra.\n"
            "Panem nostrum cotidianum\n"
            "da nobis hódie;\n"
            "et dimítte nobis débita nostra,\n"
            "sicut et nos\n"
            "dimíttimus debitóribus nostris;\n"
            "et ne nos indúcas in tentatiónem;\n"
            "sed líbera nos a malo.\n"
            "men.\n");
    return 42;
}

int set(int argc, char** argv)
{
    if (argc == 1) {
        printf("A=%Lf; B=%Lf; t=%lu\n", _a, _b, _t);
        return 0;
    } else if (argc != 3) return 1;

    if (!strcmp(argv[1], "a"))
        _a = atof(argv[2]);
    else if (!strcmp(argv[1], "b"))
        _b = atof(argv[2]);
    else if (!strcmp(argv[1], "t"))
        _t = atoi(argv[2]);
    else
       return 1;

    return 0;
}

int processes(int argc, char** argv)
{
    size_t i;

    if (!psize) {
        printf("No processes in queue.\n");
        return 1;
    }

    printf("Found %u processes in queue: ",
           (unsigned int) psize);

    for (i = 0; i != psize; i++)
        printf("'%s', ", ps[i]->name);
    printf("\b\b    \n");
    return 0;
}

int dbghelp(int argc, char** argv)
{
    size_t i;

    for(i=0; dbgop[i].name; i++)
        printf("%%%s\t%s;\n", dbgop[i].name, dbgop[i].desc);
    printf("\n");

    return 0;
}



