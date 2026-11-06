#include "comment_removal.h"

void remove_comments(char text[])
{
    int i = 0, j = 0;
    int single = 0, multi = 0;

    while (text[i] != '\0')
    {
        if (single == 1)
        {
            if (text[i] == '\n')
            {
                single = 0;
                text[j++] = '\n';
            }
        }
        else if (multi == 1)
        {
            if (text[i] == '*' && text[i + 1] == '/')
            {
                multi = 0;
                i++;
            }
            else if (text[i] == '\n')
            {
                text[j++] = '\n';
            }
        }
        else if (text[i] == '/' && text[i + 1] == '/')
        {
            single = 1;
            i++;
        }
        else if (text[i] == '/' && text[i + 1] == '*')
        {
            multi = 1;
            i++;
        }
        else
        {
            text[j++] = text[i];
        }

        i++;
    }

    text[j] = '\0';
}
