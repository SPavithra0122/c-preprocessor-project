#include <stdio.h>
#include "macro_handler.h"

int main()
{
    process_macros("macro_sample.c", "macro_sample.i");

    printf("Macro substitution completed!\n");

    return 0;
}
