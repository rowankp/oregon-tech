#include "d_list.h"
#include <stdlib.h>
#include <stdio.h>

// Doubly Linked List implementation

// node structure to hold data
typedef struct Node_S
{
	int data;
	struct Node_S * next;
	struct Node_S * previous;
} Node;

// list structure to hold nodes
typedef struct List_S
{
	int count;
	Node * head;
	Node * tail;
} List;

// Name: Init_List
// Purpose: 
// Create and initialize a list. Return a pointer 
// to list on success. Return NULL on failure.
Linked_List Init_List()
{
	List * new_list = (List *)malloc(sizeof(List));
	
	new_list->count = 0;
	new_list->head = NULL;
	new_list->tail = NULL;
	
	return (Linked_List) new_list;
}

// Name: Delete_List
// Purpose:
// Delete a list and deallocate memory used by the 
// list. Return zero on success.
int Delete_List(Linked_List passed)
{
	// return valuer
	int ret = 0;
	
	// test for valid passed list
	if (passed == NULL)
	{
		ret = 1;
	}
	else
	{
		// recast passed list
		List * list = (List *)passed;
		
		List * travel = NULL;
		
		while(list->head != NULL)
		{
			travel = list->head;
			list->head = list->head->m_next;
			free(travel);
		}

		list->head = NULL;
		list->tail = NULL;
		list->count = 0;
	}
	
	return ret;
}

// Name: Node_Count
// Purpose:
// Return the number of items in the list.
// Return -1 on fail.
int Node_Count(Linked_List list)
{
	// return value
	int ret = 0;
	
	// test for valid list
	if (passed == NULL)
	{
		ret = -1;
	}
	else
	{
		// recast passed list
		List * list = (List *)passed;
		
		// get node ocunt
		ret = list->count;
	}

	return ret;
}

// Name: Insert_At_Beginning
// Purpose: 
// Insert a new node at beginning of the list.
// Return zero on success.
int Insert_At_Beginning(Linked_List passed, int data)
{
	// return value
	int ret = 0;
	
	// test for valid list
	if (passed == NULL)
	{
		ret = 1;
	}
	else
	{
		// recast passed list
		List * list = (List *)passed;
		
		// create new node
		Node * new_node = (Node *)malloc(sizeof(Node));
		
		// copy data into new node
		new_node->data = data;
		
		// new node next points to head
		new_node->next = list->head;
		
		// new_node previous points to NULL
		new_node->previous = NULL;
		
		// test for empty list
		if (list->count != 0)
		{
			// change previous of head to new node
			list->head->previous = new_node;
		}
		
		// set new node to head
		list->head = new_node;

		// increment count
		(list->count)++;
	}
	
	return ret;
}

// Name: Insert_At_End
// Purpose: 
// Insert a new node at end of the list. 
// Return zero on success.
int Insert_At_End(Linked_List passed, int data)
{
	// return value
	int ret = 0;
	
	// test for valid list
	if (passed == NULL)
	{
		ret = 1;
	}
	else
	{
		// create new node
		Node * new_node = (Node *)malloc(sizeof(Node));
	
		// copy data into new node
		new_node->data = data;
	
		// set new node next to null
		new_node->next = NULL;
	
		// test if list is empty
		if (list->count == 0)
		{
			// set new node previous to null
			new_node->previous = NULL;
			// set new node to head
			(list->head = new_node;
		}
		// else if list has one node
		else if (list->count == 1)
		{
			// set new node previous to head
			new_node->previous = list->head;
			// set tail to new node
			list->tail = new_node;
			// set head next to tail
			list->head->next = list->tail;
		}
		else
		{
			// set tail to new node
			list->tail->next = new_node;
			// set new node previous to tail
			new_node->previous = list->tail;
			// set tail to new node
			list->tail = new_node;
		}

		// increment count
		(list->count)++;		
	}

	return ret;
}

// Name: Remove_From_Beginning
// Purpose:
// Delete a node from the beginning of the list.
// Return zero on success.
int Remove_From_Beginning(Linked_List passed)
{
	// return value
	int ret = 0;
	
   	// recast passed list
	List * list = (List *)passed;

	// test for valid list
	if (passed == NULL && list->count == 0)
	{
		ret = 1;
	}
	else
	{	
		// store old  head in node to delete
		Node * to_delete = list->head;

		// assign new head
		list->head = list-head->next;
		
		// update new head previous
		list->head->previous = NULL;
		
		// display data
		printf("Node Data: ", to_delete->data);

		// release old head
		free(to_delete);

		// decrement count
		(list->count)--;
	}

	return ret;
}

// Name: Remove_From_End
// Purpose:
// Delete a node from the end of the list.
// Return zero on success.
int Remove_From_End(Linked_List passed)
{
	// return value
	int ret = 0;
	
   	// recast passed list
	List * list = (List *)passed;

	// test for valid list
	if (passed == NULL && list->count == 0)
	{
		ret = 1;
	}
	else
	{	
		// store old  head in node to delete
		Node * to_delete = list->tail;

		// assign new tail
		list->tail = list-tail->previous;
		
		// update new tail next
		list->tail->next = NULL;

		// display data
		printf("Node Data: ", to_delete->data);

		// release old tail
		free(to_delete);

		// decrement count
		(list->count)--;
	}

	return ret;
}
