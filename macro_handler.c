#include <stdio.h>
#include <string.h>
#include "macro_handler.h"

char macro_name[50][64];
char macro_value[50][512];
int macro_count = 0;

void define_macro(char name[], char value[])
{
    if (macro_count < 50)
    {
        strcpy(macro_name[macro_count], name);
        strcpy(macro_value[macro_count], value);
        macro_count++;
    }
}

void replace_macros(char line[])
{
    char result[2048];
    int i = 0, j = 0, k;

    while (line[i] != '\0')
    {
        /* Keep quoted strings unchanged */
        if (line[i] == '"' || line[i] == '\'')
        {
            char quote = line[i];
            result[j++] = line[i++];

            while (line[i] != '\0')
            {
                result[j++] = line[i];

                if (line[i] == '\\' && line[i + 1] != '\0')
                {
                    i++;
                    result[j++] = line[i++];
                    continue;
                }

                if (line[i++] == quote)
                    break;
            }
        }
        else
        {
            int found = 0;

            for (k = 0; k < macro_count; k++)
            {
                int len = strlen(macro_name[k]);

                if (strncmp(&line[i], macro_name[k], len) == 0)
                {
                    strcpy(&result[j], macro_value[k]);
                    j += strlen(macro_value[k]);
                    i += len;
                    found = 1;
                    break;
                }
            }

            if (!found)
                result[j++] = line[i++];
        }
    }

    result[j] = '\0';
    strcpy(line, result);
}
