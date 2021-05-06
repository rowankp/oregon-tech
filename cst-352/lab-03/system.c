//*********************************************************
// filename:    system.c
// purpose:     contains "below the line" code, like
//              startup and systrap routines
// author:      Rowan Parker
//*********************************************************
#pragma startup startup__
#pragma systrap systrap__
#pragma feature inp

#include "constants.h"
#include <inp_def.h>  
#include <machine_def.h>
#include <string.h>

//*********************************************************
// function:    trap_func
// purpose:     systrap helper function
// arguments:   opcode, parameter for instruction
// return:      0 on success, -1 on failure
// safety:      none
//*********************************************************
int trap_func(int opcode, void *param)
{
    int bp;
    int lp;

    // check for null ptr
    if (param == NULL ) return ERROR;

    // check for valid op code
    if (opcode != INP_PRINTS_CALL && opcode != INP_GETI_CALL && 
        opcode != INP_GETL_CALL && opcode != HALT) return ERROR;

    // adjust
    bp = asm2("PUSHREG", BP_REG);
    lp = asm2("PUSHREG", LP_REG);
    param += bp;
    
    // check for halt
    if (opcode == HALT) asm ("HALT");

    // create io_blk_t for INP
    io_blk_t io_blk;
    io_blk.op = opcode;
    io_blk.param1 = param;

    // if not halt, perform I/O action
    asm("INP", &io_blk);

    // poll op field until done and BUFFER_SIZE is not exceeded
    while ((io_blk.op & INP_OP_DONE) == 0) 
    { }

    // check for error
    if ((io_blk.op & INP_OP_ERROR) != 0) return ERROR;

    return 0;
}

//*********************************************************
// function:    systrap__
// purpose:     function that gets called when the TRAP 
//              instruction executes
// arguments:   opcode, parameter for instruction
// return:      -1 on failure, reflected by opcode
// safety:      none
//*********************************************************
int systrap__(int opcode, void *param)
{
    // check for error
    if (trap_func(opcode, param) != 0) opcode = ERROR;
    asm("RTI");
}

//*********************************************************
// function:    startup__
// purpose:     startup routine, provided by Phil Howard
// arguments:   none
// return:      0 on success, non-zero on failure
// safety:      none
//*********************************************************
int startup__()
{
    io_blk_t io_blk;
    int bp;
    int high_mem;
    int *stack_size;

    // Set the BP leaving enough room for our stack
    bp = asm2("PUSHREG", SP_REG);
    // size of stack
    bp += 64;                       
    asm2("POPREG", BP_REG, bp);

    // Load user.slb into memory
    io_blk.op = INP_EXEC_CALL;
    // program to run
    io_blk.param1 = "user.slb";     
    io_blk.param2 = 0;
    asm("INP", &io_blk);
    // wait for EXEC to finish
    while (io_blk.op >= 0)          
    {    }

    // Set the LP leaving room for stack
    // EXEC places requested stack size here
    stack_size = io_blk.param2;     
    high_mem = io_blk.param2 + *stack_size;
    asm2("POPREG", LP_REG, high_mem);

    // Set SP and FP
    // NOTE: FP must be set only AFTER all variable references
    // NOTE: SP must be set LAST (otherwise you're using the user's stack)
    high_mem = io_blk.param2 + 4 - bp;
    asm("DUP", high_mem);
    asm2("POPREG", FP_REG);
    asm2("POPREG", SP_REG);

    // Execute user.slb
    asm2("JMPUSER", 8);
    asm("HALT");
}