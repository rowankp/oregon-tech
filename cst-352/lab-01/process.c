//*********************************************************
// filename: process.c
// purpose:  utility uses postfilter and prefilter to 
//           process the output of a specified command
// author:   Rowan Parker
//*********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include <unistd.h>

#define FD_COUNT 4 // number of file descriptions

//*********************************************************
// function:    validateArgs
// purpose:     check for at least three arguments and
//              issue warnings for potentially problematic 
//              arguments
// arguments:   command line argument count (argc), 
//              command line arguments (argv)
// return:      0 if correct number of args, -1 if not
// safety:      none
//*********************************************************
static int validateArgs(int argc, const char **argv)
{
    // check for at least three arguments
    if (argc < 4)
    {
        fprintf(stderr, "ERROR: at least three arguments required - "
                        "two characters to filter by and "
                        "a command whose output is to be filtered\n");
        return -1;
    }

    // check for single character first argument and issue warning
    if (strlen(argv[1]) > 1)
    {
        fprintf(stderr, "WARNING: too many characters supplied for prefilter."
                        " First character '%c' will be used\n", argv[1][0]);
    }

    // check for single character second argument and issue warning
    if (strlen(argv[2]) > 1)
    {
        fprintf(stderr, "WARNING: too many characters supplied for postfilter."
                        " First character '%c' will be used\n", argv[2][0]);
    }

    return 0;
}

//*********************************************************
// function:    closeAll
// purpose:     loop through and close all file descriptors 
// arguments:   array of file descriptions (int *)
// return:      void
// safety:      none
//*********************************************************
static void closeAll(int *fd)
{
    for (int i = 0; i < FD_COUNT; ++i)
        close(fd[i]);
}

//*********************************************************
// function:    command 
// purpose:     execute a command    
// arguments:   command line argument count (argc), 
//              command line arguments (argv)
// return:      0 if successfully execute, -1 if not
// safety:      none
//*********************************************************
static int command(int argc, char **argv)
{
    int ret = 0;
    char** cmd = (char **)malloc(sizeof(char *) * (argc - 2));
    // exevcp requires null terminated list, add NULL last item
    cmd[argc - 3] = NULL;

    // build command list by removing pre/post filter arguments
    for (int cmd_i = 0, argv_i = 3; argv_i < argc; ++argv_i, ++cmd_i)
        cmd[cmd_i] = argv[argv_i];

    // if command fails, set negative return value
    // no error message, assuming command will print its own errors
    if (execvp(cmd[0], cmd) < 0) ret = -1;

    free(cmd);

    return ret;
}

//*********************************************************
// function:    prefilter
// purpose:     execute the prefilter command
// arguments:   filter character
// return:      0 if successfully execute, -1 if not
// safety:      none
//*********************************************************
static int prefilter(char filter)
{
    int ret = 0;
    char filter_s[] = { filter, '\0'};
    char *cmd[] = {"./prefilter", filter_s, NULL};

    // if prefilter fails, set negative return value
    // no error message, assuming prefilter will print its own errors
    if (execvp(cmd[0], cmd) < 0) ret = -1;

    return ret;
}

//*********************************************************
// function:    postfilter
// purpose:     execute the postfilter command
// arguments:   filter character
// return:      0 if successfully execute, -1 if not
// safety:      none
//*********************************************************
static int postfilter(char filter)
{
    int ret = 0;
    char filter_s[] = { filter, '\0'};
    char *cmd[] = {"./postfilter", filter_s, NULL};

    // if postfilter fails, set negative return value
    // no error message, assuming postfilter will print its own errors
    if (execvp(cmd[0], cmd) < 0) ret = -1;

    return ret;
}

//*********************************************************
int main(int argc, char **argv)
{   
    // if invalid arguments, exit program
    if (validateArgs < 0) exit(EXIT_FAILURE);

    // file descriptors for two pipes
    int fd[FD_COUNT];
    // cmd->prefilter pipe
    pipe(fd);
    // prefilter->postfilter pipe
    pipe(fd + 2);
    
    // fd[0] = read end of cmd->prefilter (read by prefilter)
    // fd[1] = write end of cmd->prefilter (written by cmd)
    // fd[2] = read end of prefilter->postfilter (read by postfilter)
    // fd[3] = write end of prefilter->postfilter (written by prefilter)

    // fork the first child (to execute cmd)
    int pid = fork();
    // check for valid fork
    if (pid < 0)
    {
        fprintf(stderr, "ERROR: unable to fork()\n"); 
        exit(EXIT_FAILURE);
    }
    // check for child
    else if (pid == 0)
    {
        // replace cmd's stdout with write part of cmd->pre
        dup2(fd[1], 1);

        // close all ends of pipes
        closeAll(fd);

        // execute command
        if (command(argc, argv) < 0) exit(EXIT_FAILURE);
    }
    else
    {
        // fork the second child (to execute prefilter)
        pid = fork();
        // check for valid fork
        if (pid < 0)
        {
            fprintf(stderr, "ERROR: unable to fork()\n"); 
            exit(EXIT_FAILURE);
        }
        // check for child
        else if (pid == 0)
        {
            // replace prefilter's stdin with read end of cmd->pre
            dup2(fd[0], 0);

            // replace prefilter's stdout with write end of pre->post
            dup2(fd[3], 1);
            
            // close all ends of pipes
            closeAll(fd);

            // excute prefilter
            if (prefilter(argv[1][0]) < 0) exit(EXIT_FAILURE);
        }
        else
        {
            // fork third child (to execute postfilter)
            pid = fork();
            // check for valid fork
            if (pid < 0)
            {
                fprintf(stderr, "ERROR: unable to fork()\n"); 
                exit(EXIT_FAILURE);
            }
            // check for child
            else if (pid == 0)
            {
                // replace prefilter's stdin with input read of pre->post
                dup2(fd[2], 0);

                // close all ends of pipes
                closeAll(fd);

                // execute postfilter
                if (postfilter(argv[2][0]) < 0) exit(EXIT_FAILURE);
            }
        }
    }
    
    // only parent gets here and needs to wait for children to finish
    // close all pipes
    closeAll(fd);

    // parent wait for children
    wait(NULL);

    return 0;
}