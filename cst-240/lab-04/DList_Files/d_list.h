#pragma once

//**********************************************
// Doubly  Linked List Definition
//
// This header file defines types and functions 
// for a doubled linked list.
//**********************************************

// opaque type for lists
typedef void * Linked_List;
// node structure to hold data
typedef struct Node;
// list structure to hold nodes
typedef struct List;

// Name: Init_List
// Purpose: 
// Create and initialize a list. Return a pointer 
// to list on success. Return NULL on failure.
Linked_List Init_List();

// Name: Delete_List
// Purpose:
// Delete a list and deallocate memory used by the 
// list. Return zero on success.
int Delete_List(Linked_List passed);

// Name: Node_Count
// Purpose:
// Return the number of items in the list.
int Node_Count(Linked_List passed);

// Name: Insert_At_Beginning
// Purpose: 
// Insert a new node at beginning of the list.
// Return zero on success.
int Insert_At_Beginning(Linked_List passed, int data);

// Name: Insert_At_End
// Purpose: 
// Insert a new node at end of the list. 
// Return zero on success.
int Insert_At_End(Linked_List passed, int data);

// Name: Remove_From_Beginning
// Purpose:
// Delete a node from the beginning of the list.
// Return zero on success.
int Remove_From_Beginning(Linked_List passed);

// Name: Remove_From_End
// Purpose:
// Delete a node from the end of the list.
// Return zero on success.
int Remove_From_End(Linked_List passed); 
