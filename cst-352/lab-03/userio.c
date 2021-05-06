//*********************************************************
// filename:    userio.c
// purpose:     user mode library of IO intended for the
//              stackl environment
// author:      Rowan Parker
//*********************************************************
#pragma once

#include "userio.h"
#include <inp_def.h>
#include <machine_def.h>
#include <string.h>

//*********************************************************
// function:    syscall
// purpose:     validate arguments and call systrap
// arguments:   opcode, parameter for instruction
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int syscall(int opcode, void *param)
{
    // check for null ptr
    if (param == NULL ) return ERROR;

    // check for valid op code
    if (opcode != INP_PRINTS_CALL && opcode != INP_GETI_CALL && 
        opcode != INP_GETL_CALL && opcode != HALT) return ERROR;

    // trap
    asm("TRAP");

    // check for failure in systrap
    if (opcode == ERROR) return ERROR;

    return 0;
}

//*********************************************************
// function:    prints
// purpose:     prints the string to stdout
// arguments:   string (char *)
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int prints(char *string)
{
    int opcode;
    opcode = INP_PRINTS_CALL;       

    // check for null
    if (string == NULL) return ERROR;

    // check for syscall failure
    if (syscall(opcode, string) == ERROR) return ERROR;

    // return operation status
    return 0;
}

//*********************************************************
// function:    printi
// purpose:     prints the interger value to stdout
//              assumes conversion will never exceed a
//              256 buffer size
// arguments:   value (int)
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int printi(int value)
{
    int opcode;
    char string[BUFFER_SIZE];   
    opcode = INP_PRINTS_CALL;  
    itostr(value, string);
    
    // check for syscall failure
    if (syscall(opcode, string) == ERROR) return ERROR;

    // return operation status
    return 0;
}

//*********************************************************
// function:    geti
// purpose:     read an interger value from stdin
// arguments:   none
// return:      value from stdin
// safety:      none
//*********************************************************
int geti()
{
    int opcode;
    int value;       
    opcode = INP_GETI_CALL;       

    // check for syscall and operation failure
    syscall(opcode, &value);

    // return value
    return value;
}

//*********************************************************
// function:    gets
// purpose:     read a line of text from stdin,
//              has similar behavior to C language 
//              fgets(buffer, 256, stdin) function,
//              assumed maximum buffer size of 256
// arguments:   buffer (char *)
// return:      0 on success, 1 on failure
// safety:      none
//*********************************************************
int gets(char *buffer)
{
    int opcode;
    opcode = INP_GETL_CALL; 

    // check for valid buffer
    if (buffer == 0) return ERROR;
    // ensure no junk in buffer
    memset(buffer, 0, BUFFER_SIZE);

    // check for syscall failure
    if (syscall(opcode, buffer) == ERROR) return ERROR;

    // return operation status
    return 0;
}

//*********************************************************
// function:    halt
// purpose:     stop CPU and terminate stackl interpreter
// arguments:   none
// return:      if this method returns at all, an error
//              has occurred 
// safety:      none
//*********************************************************
int halt()
{
    int opcode;    
    opcode = HALT;
    
    // opcode doesn't need a parameter, but we need to pass
    // an address to syscall, so we are just going to pass
    // it opcode's address as a dummy address
    syscall(opcode, &opcode);

    // if this method returns at all, an error has occurred
    return ERROR;
}