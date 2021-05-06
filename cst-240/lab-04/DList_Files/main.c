#include "d_list.h"
#include <stdio.h>
#include <stdlib.h>

// Test code for Doubly Linked List

int main()
{
	List list = Init_List();
	int count = -1;
	int ret = -1;

	// test for empty count
	count = Node_Count(list);
	printf("-- Testing Count Return for Empty List --");
	printf("Expected Count: 0");
	printf("Actual Count: ", count);
	if (count == 0)
	{
		printf("Test Passed!");
	}
	else
	{
		printf("Test Failed.");
	}

	// test for add to beginning
	Insert_At_Beginning(list, 5);
	count = Node_Count(list);
	printf("-- Testing Add To Beginning --");
	printf("Expected Node Count: 1");
	printf("Actual Node Count: ", list->count);
	if (count == 1)
	{
		printf("Test Passed!");
	}
	else
	{
		printf("Test Failed.");
	}

	// test for delete from beginning
	printf("-- Testing Add To Beginning --");
	printf("Expected Display: 5");
	Remove_From_Beginning(list);
	count = Node_Count(list);
	printf("Expected Node Count: 0");
	printf("Actual Node Count: ", list->count);
	if (count == 1)
	{
		printf("Test Passed!");
	}
	else
	{
		printf("Test Failed.");
	}
  
	return 0;
}
