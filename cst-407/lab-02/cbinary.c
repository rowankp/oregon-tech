//******************************************************
// Interface for a binary tree for storing integers.
//
// Includes nolock version and one-lock version
// 
//
// Author: Phil Howard

#include <stdlib.h>
#include <pthread.h>

#include "cbinary.h"

typedef struct i_element_s
{
    int value;
    struct i_element_s *left;
    struct i_element_s *right;
    struct i_element_s *parent;
} i_element_t;

typedef struct i_tree_s
{
    i_element_t *root;
    int lock_type;
    pthread_rwlock_t rw_lock;
} i_tree_t;

// Create and initialize a binary tree
tree_t Tree_Init(int lock_type)
{
    i_tree_t *tree = (i_tree_t *)malloc(sizeof(i_tree_t));
    tree->root = NULL;
    tree->lock_type = lock_type;

    // Do other initialization based on the lock type

    return tree;
}

// Insert an integer into a binary tree
void Node_Insert(i_element_t *node, i_element_t *element)
{
    i_element_t *curr, *prev;

    curr = node;
    prev = curr;

    while (curr != NULL)
    {
        prev = curr;
        if (curr->value > element->value)
            curr = curr->left;
        else
            curr = curr->right;
    }

    element->parent = prev;
    if (prev->value > element->value)
        prev->left = element;
    else
        prev->right = element;
}

// Insert an integer into a binary tree
void Tree_Insert(tree_t t, int value)
{
    i_tree_t *tree = (i_tree_t*)t;
    i_element_t *element = (i_element_t *)malloc(sizeof(i_element_t));

    element->value = value;
    element->left = NULL;
    element->right = NULL;
    element->parent = NULL;

    if (tree->root == NULL)
    {
        tree->root = element;
    }
    else
    {
        Node_Insert(tree->root, element);
    }
}

// Delete an integer from a binary tree
// If the integer is not found, no operation is performed on the tree
// If multiple nodes contain the specified value, only one of them will be 
//    deleted
void Tree_Delete(tree_t t, int value)
{
    i_tree_t *tree = (i_tree_t*)t;
    i_element_t *curr;

    // can only delete from a non-empty tree
    if (tree->root != NULL)
    {
        curr = tree->root;

        while (curr != NULL && curr->value != value)
        {
            if (curr->value > value)
                curr = curr->left;
            else
                curr = curr->right;
        }
        
        if (curr != NULL)
        {
            // Deleting the root node. 
            // We have to special case because curr->parent doesn't exist
            if (curr == tree->root)
            {
                if (curr->left != NULL)
                {
                    i_element_t *right_branch = curr->right;

                    tree->root = curr->left;
                    curr->left->parent = tree->root;

                    if (right_branch != NULL) 
                    {
                        Node_Insert(tree->root, right_branch);
                    }
                }
                else
                {
                    tree->root = curr->right;
                }
                if (tree->root != NULL) tree->root->parent = NULL;
                free(curr);
            }
            else
            {
                // Process: cut out the right branch
                // shift the left branch up to the parent
                // reinsert the right branch
                i_element_t *right_branch = curr->right;

                // are we the left or right child
                if (curr->parent->left == curr)
                {
                    curr->parent->left = curr->left;
                    if (curr->left != NULL)
                    {
                        curr->left->parent = curr->parent;
                    }
                    if (right_branch != NULL) 
                    {
                        Node_Insert(curr->parent, right_branch);
                    }
                }
                else
                {
                    // must be right child
                    curr->parent->right = curr->left;
                    if (curr->left != NULL)
                    {
                        curr->left->parent = curr->parent;
                    }
                    if (right_branch != NULL) 
                    {
                        Node_Insert(curr->parent, right_branch);
                    }
                }
                free(curr);
            }
        }
    }
}

// Find a value in the tree.
// If the value is found, the element is returned.
// If the value is not found, the function returns NULL
// Any locks that are required to access the lement will still be held when
// the element is returned. 
element_t Tree_Lookup(tree_t t, int value)
{
    i_tree_t *tree = (i_tree_t*)t;
    i_element_t *curr;

    if (tree->root == NULL) return NULL;

    curr = tree->root;
    while (curr != NULL && curr->value != value)
    {
        if (curr->value > value)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return curr;
}

// Traverse the tree calling the specified function on each node
static void Node_Traverse(i_element_t *node, void (*func)(element_t element))
{
    if (node == NULL) return;

    Node_Traverse(node->left, func);
    func(node);
    Node_Traverse(node->right, func);
}

// Destroy a subtree and free all memory
static void Node_Destroy(i_element_t *node)
{
    if (node == NULL) return;
    Node_Destroy(node->left);
    Node_Destroy(node->right);
    free(node);
}

// Destroy a tree and free all memory
void Tree_Destroy(tree_t t)
{
    i_tree_t *tree = (i_tree_t*)t;

    Node_Destroy(tree->root);

    free(tree);
}

// Traverse the tree calling the specified function on each node
void Tree_Traverse(tree_t t, void (*func)(element_t element))
{
    i_tree_t *tree = (i_tree_t*)t;

    Node_Traverse(tree->root, func);
}

// Retrieve the value from an element
int Element_Value(element_t element)
{
    i_element_t *elem = (i_element_t *)element;
    return elem->value;
}

// release any locks held by an element
void Element_Release(element_t element)
{
    //i_element_t *elem = (i_element_t *)element;
}


