//*********************************************************
// filename: postfilter.c
// purpose:  utility that read lines of text from stdin 
//           and, for each line, print to stdout all 
//           characters before a specified character
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
//              all characters before and a specified 
//              filter character
// arguments:   character to filter for (filter)
// return:      void
// safety:      none
//*********************************************************
static void postfilter(char filter)
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

        fprintf(stderr, "%d post %c: %s\n", id, filter, buffer);

        line = strrchr(buffer, filter);
        if (line != NULL)
        {
            int length = strlen(buffer) - strlen(line);
            line = (char *)calloc(length + 1, sizeof(char));
            line = strncpy(line, buffer, length);

            if (strlen(line) > 0)
                fprintf(stdout, "%s\n", line);

            fprintf(stderr, "%d remaining: %s\n", id, line);

            free(line);
        }
        else 
        {
            if (strlen(buffer) > 0)
                fprintf(stdout, "%s\n", buffer);

            fprintf(stderr, "%d remaining: %s\n", id, buffer);
        }
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

    postfilter(argv[1][0]);
    
    return 0;
}