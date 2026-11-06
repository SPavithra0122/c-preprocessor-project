#include <stdio.h>
#include "file_inclusion.h"

void process_include(char filename[], FILE *output)
{
    FILE *input;
    char ch;

    input = fopen(filename, "r");

    if (input == NULL)
    {
        printf("File not found: %s\n", filename);
        return;
    }

    while ((ch = fgetc(input)) != EOF)
    {
        fputc(ch, output);
    }

    fclose(input);
}

