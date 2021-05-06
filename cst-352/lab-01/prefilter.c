//*********************************************************
// filename: prefilter.c
// purpose:  utility that read lines of text from stdin 
//           and, for each line, print to stdout all 
//           characters including and following a specified 
//           character
// author:   Rowan Parker
//*********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LENGTH 512 // buffer length

//*********************************************************
// function:    prefilter
// purpose:     read lines from stdin and print to stdout
//              all characters including and following a 
//              specified filter character
// arguments:   character to filter with (filter)
// return:      void
// safety:      none
//*********************************************************
static void prefilter(char filter)
{
    char buffer[BUFFER_LENGTH];
    char *line = NULL;
    int id = getpid();

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        for (int i = strlen(buffer); i >= 0; --i)
        {
            line = &buffer[i];
            if (*line == 10 || *line == 13) *line = '\0';
        }

        fprintf(stderr, "%d pre %c: %s\n", id, filter, buffer);

        line = strchr(buffer, filter);

        if (line != NULL && strlen(line) > 0)
        {
            fprintf(stdout, "%s\n", line);
            fprintf(stderr, "%d rest: %s\n", id, line);
        }
        else
            fprintf(stderr, "%d rest:\n", id);
    }
}

//*********************************************************
int main(int argc, char **argv)
{
    // check for at least one command line argument
    if (argc < 2)
    {
        fprintf(stderr, "ERROR: character to filter by required\n");
        return 1;
    }
    // check for too many command line arguments 
    else if (argc > 2)
    {
        fprintf(stderr, "ERROR: too many arguments supplied\n");
        return 1;
    }

    // check for single character argument and issue warning
    if (strlen(argv[1]) > 1)
    {
        fprintf(stderr, "WARNING: more than one character supplied. First "
                        "character '%c' will be used for filtering\n", 
                        argv[1][0]);
    }

    prefilter(argv[1][0]);

    return 0;
}