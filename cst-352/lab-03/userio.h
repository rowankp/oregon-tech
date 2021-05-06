//*********************************************************
// filename:    userio.h
// purpose:     user mode library of IO intended for the
//              stackl environment
// author:      Rowan Parker
//*********************************************************
#pragma once
#include "constants.h"

//*********************************************************
// function:    prints
// purpose:     prints the string to stdout
// arguments:   string (char *)
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int prints(char *string);

//*********************************************************
// function:    printi
// purpose:     prints the interger value to stdout
// arguments:   value (int)
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int printi(int value);

//*********************************************************
// function:    geti
// purpose:     read an interger value from stdin
// arguments:   none
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int geti();

//*********************************************************
// function:    gets
// purpose:     read a line of text from stdin,
//              has similar behavior to C language 
//              fgets(buffer, 256, stdin) function,
//              assumed maximum buffer size of 256
// arguments:   buffer (char *)
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int gets(char *buffer);

//*********************************************************
// function:    halt
// purpose:     stop CPU and terminate stackl interpreter
// arguments:   none
// return:      if this method returns at all, an error
//              has occurred 
// safety:      none
//*********************************************************
int halt();
