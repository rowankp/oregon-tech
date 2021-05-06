//**************************************************
// Linked list implementation

#include <pthread.h>
#include <stdlib.h>
#include "list.h"

// node structure to hold data
typedef struct node_s
{
	int64_t data;
    struct node_s * next;
	struct node_s * previous;
} node_t;

// list structure to hold nodes
typedef struct list_s
{
	pthread_mutex_t list_lock;
	int64_t count;
	node_t * head;
	node_t * tail;
} list_t;

// Create and initialize a list. 
// Return pointer to list. Return NULL on failure.
linked_list_t * Init_List()
{
	list_t * new_list = (list_t *)malloc(sizeof(list_t));

	if (pthread_mutex_init(&new_list->list_lock, NULL) != 0)
		return (linked_list_t *) -1;
	new_list->count = 0;
	new_list->head = NULL;
	new_list->tail = NULL;

    return (linked_list_t) new_list;
}

// Delete a list are free all memory used by the list
// It is erroneous to use the list pointer after caling this routine.
// Return zero on success
int Delete_List(linked_list_t * list)
{
	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return 1;
	}

    pthread_mutex_lock(&l->list_lock);

	if (l->count != 0)
	{
	  	node_t * travel = NULL;
		
		while(l->head != NULL)
		{ 
			travel = l->head;
			l->head = l->head->next;
			free(travel);
		}
	}

	free(l);
	
	pthread_mutex_unlock(&l->list_lock);
	
	return 0;
}

// Returns the number of items in the list
int64_t Count(linked_list_t * list)
{
	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return 1;
	}
 
	return l->count;
}

// Insert an item at the beginning of the list
// Return zero on success
// Params:
//    list: list to add item to
//    data: Data to be added to the list
int Insert_At_Beginning(linked_list_t * list, int64_t data)
{
	// recast list
	list_t * l = (list_t *)list;
	
	// test for valid list
	if (l == NULL)
	{
		return 1;
	}
	else
	{	
		// lock
		pthread_mutex_lock(&l->list_lock);
		
		// create new node
		node_t * new_node = (node_t *)malloc(sizeof(node_t));

 		// copy data into new node
		new_node->data = data;

		// new_node previous points to NULL
		new_node->previous = NULL;

		// new_nide next point to NULL
		new_node->next = NULL;

		// test for empty list
		if (l->head == NULL)
		{
			// head is equal to new node 
			l->head = new_node;
			// tail is equal to new node
			l->tail = new_node;
		}
		else
		{
			// new node next points to head
			new_node->next = l->head;
			
			// change previous of head to new node
			(l->head)->previous = new_node;
			
			// set new node to head
			l->head = new_node;
		}	
		
		// increment count
		(l->count)++;
	
		// unlock
		pthread_mutex_unlock(&l->list_lock);
	}
	
	return 0;
}

// Insert an item at the end of the list
// Return zero on success
// Params:
//    list: list to add item to
//    data: Data to be added to the list
int Insert_At_End(linked_list_t * list, int64_t data)
{
 	// recast list
	list_t * l = (list_t *)list;
	
	// test for valid list
	if (l == NULL)
	{
		return 1;
	}
	else
	{
		// lock
		pthread_mutex_lock(&l->list_lock);
		
		// create new node
		node_t * new_node = (node_t *)malloc(sizeof(node_t));
	
		// copy data into new node
		new_node->data = data;

		// set new node previous to null
		new_node->previous = NULL;
	
		// set new node next to null
		new_node->next = NULL;
	
		// test if list is empty
		if (l->head == NULL)
		{
			// set new node to head
			l->head = new_node;

			// set new node to tail
			l->tail = new_node;
		}
		else
		{
			// set tail to new node
			(l->tail)->next = new_node;
		
			// set new node previous to tail
			new_node->previous = l->tail;
		
			// set tail to new node
			l->tail = new_node;
		}

		// increment count
		(l->count)++;		
		
		// unlock
		pthread_mutex_unlock(&l->list_lock);
	}

	return 0;
}

// Return true (non-zero) if the list is empty
//    list: list to examine
int Empty(linked_list_t * list)
{
	// recast list
	list_t * l = (list_t *)list;

	// test for empty list
	if (l->count == 0)
	{
		return 1;
	}

    return 0;
}

// Remove an item from the beginning of the list 
// Return zero on success
// Params:
//    list: list to remove item from
//    data: pointer to location to store data of removed item
//          if data is NULL, data is not returned
int Remove_From_Beginning(linked_list_t * list, int64_t* data)
{
   	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return 1;
	}
	else
	{	
		// lock
		pthread_mutex_lock(&l->list_lock);

		// if list exists
		if (l->head != NULL)
		{
			// store old  head in node to delete
			node_t * to_delete = l->head;

			// store data of old head
			(*data) = (l->head)->data;

			if (l->head->next != NULL)
			{
				// assign new head
				l->head = (l->head)->next;
		
				// update new head previous
				(l->head)->previous = NULL;
			}

			// release old head
			free(to_delete);

			// decrement count
			(l->count)--;
		}
		
		// unlock
		pthread_mutex_unlock(&l->list_lock);
	}

	return 0;
}

// Remove an item from the end of the list 
// Return zero on success
// Params:
//    list: list to remove item from
//    data: pointer to location to store data of removed item
//          if data is NULL, data is not returned
int Remove_From_End(linked_list_t * list, int64_t* data)
{
   	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return  1;
	}
	else
	{	
		// lock
		pthread_mutex_lock(&l->list_lock);
		
		// test is list exists
		if (l->head != NULL)
		{
			// store old  head in node to delete
			node_t * to_delete = l->tail;

			// assign data
			(*data) = (l->tail)->data;

			if (l->tail->previous != NULL)
			{
				// assign new tail
				l->tail = (l->tail)->previous;
		
				// update new tail next
				(l->tail)->next = NULL;
			}

			// release old tail
			free(to_delete);

			// decrement count
			(l->count)--;
		}

		// unlock
		pthread_mutex_unlock(&l->list_lock);
	}

	return 0;
}

int Traverse(linked_list_t * list, void (*action)(int64_t data))
{
	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return 1;
	}
	else 
	{	
		node_t * travel = l->head;
		
		while(travel != NULL)
		{
			action(travel->data);
			travel = travel->next;   
		}
	}

	return 0;
}

int Insert_In_Order(linked_list_t * list, int64_t value)
{
	// recast list
	list_t * l = (list_t *)list;

	// test for valid list
	if (l == NULL)
	{
		return 1;
	}

	// lock
	pthread_mutex_lock(&l->list_lock);
	
	// create new node
	node_t * new_node = (node_t *)malloc(sizeof(node_t));
	
	// copy data into new node
	new_node->data = value;

	// new_node previous points to NULL
	new_node->previous = NULL;

	// new_nide next point to NULL
	new_node->next = NULL;

	// if list is empty, insert new node at head
	if (l->head == NULL)
	{
		l->head = new_node;
		l->tail = new_node;
	}
	else
	{
		// if one node in the list
		if (l->head == l->tail)
		{
			// if need to be inserted at head
			if (l->head->data > new_node->data)
			{
				l->head->previous = new_node;
				new_node->next = l->head;
				l->head = new_node;
			}
			// if need to be inserted at tail
			else
			{
				new_node->previous = l->head;
				l->head->next = new_node;
				l->tail = new_node;
			}
		}
		else
		{
			node_t * travel = l->head;
			node_t * trail = NULL;

			// find nodes to insert in between
			while (travel != NULL && travel->data < new_node->data)
			{
				trail = travel;
				travel = travel->next;
			}
			
			// if head data is greater than new_node data
			if (trail == NULL)
			{
				l->head->previous = new_node;
				new_node->next = l->head;
				l->head = new_node;
			}
			// if at the end of list, append to tail
			else if (travel == NULL)
			{
				l->tail->next = new_node;
				new_node->previous = l->tail;
				l->tail = new_node;
			}
			// trail points to the smaller node, travel points to large node
			// new node to be inserted between trail and travel
			else
			{
				new_node->previous = trail;
				new_node->next = travel;
				trail->next = new_node;
				travel->previous = new_node;
			}
		}
	}

	// increment count
	(l->count)++;
	
	// unlock
	pthread_mutex_unlock(&l->list_lock);
	
	return 0;
}
