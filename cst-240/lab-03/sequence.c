//*****************************************************
// A function that generates the next time in a sequence
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
// Date:   2016/02/20
//

#include <stdint.h>
#include <unistd.h>

#include "sequence.h"

// static variable to remember the last sequence number
static int64_t g_sequence = 0;

//*************************************
// Generate the next sequence number
//
// NOTE: YOU ARE NOT ALLOWED TO MODIFY THE FOLLOWING CODE
//       This code was specifically crafted to test your 
//       threading implementation
//
static int64_t get_next()
{
    int64_t current;

    current = g_sequence;

    //usleep(1);

    current++;
    g_sequence = current;

    return current;
}

// returns the next number in a sequence
int64_t Next_In_Sequence()
{
    int64_t next;

    next = get_next();

    return next;
}
