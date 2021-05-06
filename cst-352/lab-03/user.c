//*********************************************************
// filename:    user.c
// purpose:     test code for userio library
// author:      Rowan Parker
//*********************************************************
#include "userio.h"

int main()
{
    int val;
    int check;
    char buffer[BUFFER_SIZE];
    
    // test gets and prints
    check = prints("--- GETS & PRINTS TEST ---\n");
    if (check == 0) check = prints("enter string: ");
    if (check == 0) check = gets(buffer);
    if (check == 0) check = prints("string read: ");
    if (check == 0) check = prints(buffer);

    // test geti and printi
    if (check == 0) check = prints("\n--- GETI & PRINTI TEST ---\n");
    if (check == 0) check = prints("enter value: ");
    val = geti();
    check = prints("value read: ");
    if (check == 0) check = printi(val);
    if (check == 0) check = prints("\n");
    if (check == 0) check = prints("\n");

    // test halt
    if (check == 0) check = prints("--- HALT TEST ---\n");
    halt();
    prints("this line should not print\n");
    
    return 0;
}