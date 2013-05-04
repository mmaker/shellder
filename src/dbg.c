#include <stdio.h>
#include <wchar.h>

#include "process.h"
#include "scheduler.h"

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

int processes(int argc, char** argv)
{
    size_t i;

    for (i = 0; i != psize; i++)
        printf("%s, ", ps[i]->name);
    printf("\b\n");
    return 0;
}
