#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void action(int data);

//******************************************
int main()
{
    linked_list_t list;
    int ii;
    int value;

    printf("Checking stack behavior\n");
    list = Init_List();
    if (list == NULL)
    {
        printf("Unable to initialize list\n");
        return 1;
    }

    for (ii=0; ii<10; ii++)
    {
        if (Insert_At_Beginning(list, ii) != 0)
        {
            printf("Error inserting %d\n", ii);
        }
    }

    if (Count(list) != 10) 
    {
        printf("Count is not correct after inserts: %d\n", Count(list));
    }

    for (ii=9; ii>=0; ii--)
    {
        if (Remove_From_Beginning(list, &value) != 0)
        {
            printf("Failed to remove item\n");
        }
        if (ii != value)
        {
            printf("Error removing %d %d\n", ii, value);
        }
    }

    if (!Empty(list)) 
    {
        printf("List is not empty after removes\n");
    }

    Delete_List(list);

    printf("Stack tests complete\n");

	// begin traverse test
	printf("Checking traverse behavior\n");
	
	// create loop variable
	int i;

	// create list variable
	linked_list_t t_list;

	// initialize list
    t_list = Init_List();

	// check for valid initialization
    if (t_list == NULL)
    {
        printf("Unable to initialize list\n");
        return 1;
    }

	// insert values 0 to 9
	for (i = 9; i >= 0; i--)
   {
        if (Insert_At_Beginning(t_list, i) != 0)
        {
            printf("Error inserting %d\n", i);
        }
    }

	// traverse list
	if (Traverse(t_list, action) != 0)
	{
		printf("Error traversing list\n");
	}
	
	// deallocate list
	Delete_List(t_list);

	// print success message
	printf("Traverse test complete.\n");

	// test Insert in Order
	printf("Checking insert in order behavior\n");

	// create loop variable
	int r;

	// crate new list
	linked_list_t r_list;

	// initialize list
    r_list = Init_List();

	// check for valid initialization
    if (r_list == NULL)
    {
        printf("Unable to initialize list\n");
        return 1;
    }
	
	// insert 20 random values
	for (r = 0; r < 20; r++)
	{
		value = rand() % 1000;
		if (Insert_In_Order(r_list, value) != 0)
		{
			printf("Error inserting %d", value);
		}
	}

	// traverse list
	if (Traverse(r_list, action) != 0)
	{
		printf("Error traversing list\n");
	}
	
	// deallocate list
	Delete_List(r_list);

	// print success message
	printf("Insert in order  test complete.\n");

    return 0;
}

void action(int data)
{
	printf("%d\n", data);
}
