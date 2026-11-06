#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#include "comment_removal.h"
#include "file_inclusion.h"
#include "macro_handler.h"

int main(int argc, char *argv[])
{
    FILE *fp, *out;
    char text[10000];
    char output[100];
    char line[1000];
    char filename[100];
    char name[64];
    char value[512];

    if (argc != 2)
    {
        printf("Usage: ./mypreprocessor inputfile.c\n");
        return 1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    fread(text, 1, sizeof(text) - 1, fp);
    text[sizeof(text) - 1] = '\0';
    fclose(fp);

    remove_comments(text);

    strcpy(output, argv[1]);

    char *dot = strrchr(output, '.');

    if (dot != NULL)
        *dot = '\0';

    strcat(output, ".i");

    out = fopen(output, "w");

    if (out == NULL)
    {
        printf("Cannot create output file\n");
        return 1;
    }

    fp = fopen("temp.c", "w");

    if (fp == NULL)
    {
        printf("Cannot create temporary file\n");
        fclose(out);
        return 1;
    }

    fputs(text, fp);
    fclose(fp);

    fp = fopen("temp.c", "r");

    if (fp == NULL)
    {
        printf("Cannot read temporary file\n");
        fclose(out);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (sscanf(line, " #define %63s %511s", name, value) == 2)
        {
            define_macro(name, value);
            continue;
        }

        if (sscanf(line, " #include \"%99[^\"]\"", filename) == 1)
        {
            process_include(filename, out);
        }
        else
        {
            replace_macros(line);
            fputs(line, out);
        }
    }

    fclose(fp);
    fclose(out);

    remove("temp.c");

    printf("Preprocessing completed successfully!\n");
    printf("Output file: %s\n", output);

    return 0;
}
