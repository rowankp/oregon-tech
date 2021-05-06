//*********************************************************
// filename: mymalloc.c
// purpose:  implementation of a Buddy System memory 
//           allocator 
// author:   Rowan Parker
//*********************************************************
#include "mymalloc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define MEM_SIZE 4096       // per lab specification
#define MIN_BLOCK_SIZE 16   // per lab specification
#define ORDERS 8            // log_2(MAX) - log_2(MIN/2) = 
                            // log_2(4096) - log_2(8) = 9

typedef struct block_s
{
    void *address;
    int order;
} block_t;

typedef struct free_list_s
{
   block_t *blocks;
   int num_used;
   int max_possible;
   int empty; // empty = 0, not empty = 1
} free_list_t;

free_list_t list[ORDERS + 1];
void *memory; 

//*********************************************************
// function:    compute_order
// purpose:     computes the order of a block based on
//              size
// arguments:   size of block (int)
// return:      order of block (int)
// safety:      none
//*********************************************************
static int compute_order(int size)
{
    int curr_size = MIN_BLOCK_SIZE;
    int order = 0;
   
    while (curr_size < size)
    {
        curr_size <<= 1;
        ++order;
    }

    return order;
}

//*********************************************************
// function:    split
// purpose:     
// arguments:   
// return:      0 on successful split, 1 on failure
// safety:      none
//*********************************************************
static int split(int order)
{
    printf("Enter split(%d)\n", order);

    if (list[order].empty == 0)
        split(order + 1);

    //list[order]

    printf("End split(%d)\n", order);
    return 1;
}

//*********************************************************
// function:    my_mem_init
// purpose:     initialize the memory allocator. This 
//              function must be called before any other 
//              memory allocator function
// arguments:   none
// return:      void. If this function fails, it will print 
//              an error message and terminate the process
// safety:      none
//*********************************************************
void my_mem_init()
{
    // create free lists
    // Order | Block Size | Max Num Blocks
    //   0   |    16      |    256
    //   1   |    32      |    128 
    //   2   |    64      |    64
    //   3   |    128     |    32
    //   4   |    256     |    16
    //   5   |    512     |    8
    //   6   |    1024    |    4
    //   7   |    2048    |    2
    //   8   |    4096    |    1
    for (int i = 0; i <= ORDERS; ++i)
    {
        // calculate max number of blocks
        list[i].max_possible = 1 << (ORDERS - i);
        // allocate list of blocks
        //list[i].blocks = malloc(sizeof(block_t) * list[i].max_possible);

        // test for error
        if (list[i].blocks == NULL)
        {
            fprintf(stderr, "ERROR: unable to initialize memory allocator.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            list[i].num_used = 0;  
            list[i].empty = 0;
        }
    }

    // allocate area of memory to manage
    memory = malloc(MEM_SIZE);
    // check for error
    if (memory == NULL)
    {
        fprintf(stderr, "ERROR: unable to initialize memory allocator.\n");
        exit(EXIT_FAILURE);
    }
}
 
//*********************************************************
// function:    my_malloc
// purpose:     request a block for 'size' bytes
// arguments:   size of block (int)
// return:      pointer to block on success, NULL on 
//              failure
// safety:      none
//*********************************************************
void *my_malloc(int size)
{
    // check for invalid size
    if (size <= 0)
        return NULL;
    
    int order = compute_order(size);
    
    if (list[order].empty == 0)
        split(order + 1);

    return NULL;
}

//*********************************************************
// function:    my_free
// purpose:     free a previously allocated block. If an 
//              error is detected, print an error message 
//              and then terminate the process
// arguments:   pointer to block (void *)
// return:      void. terminates process on failure
// safety:      none
//*********************************************************
void my_free(void *ptr)
{

}

//*********************************************************
// function:    my_validate
// purpose:     scan the meta data for corruption. Will 
//              print information if any corruption is 
//              detected. If no corruption is found, does 
//              nothing
// arguments:   none
// return:      void
// safety:      none
//*********************************************************
void my_validate()
{

}

//*********************************************************
// function:    my_print_mem
// purpose:     prints information about the state of the 
//              memory - including all free and busy blocks
// arguments:   none
// return:      void
// safety:      none
//*********************************************************
void my_print_mem()
{

}

int main()
{
    printf("%d", *(int *)memory);
    return 0;
}