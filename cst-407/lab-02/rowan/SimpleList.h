//***********************************************
// Non-Thread Safe Linked List
// Rowan Parker
// Winter 2021

#pragma once
#include "List.h"

class SimpleList : public List
{
	public:
		//***********************************************
		SimpleList(int size = 0) : List()
		{ 
			for (int ii = 0; ii < size; ++ii)
				insertOrdered(ii);
		}

		//***********************************************
		~SimpleList()
		{
			purge();
		}

		//***********************************************
		void prepend(int value)
		{
			Node* new_node = new Node(value);
			new_node->_next = _head;
			_head = new_node;
		}

		//***********************************************
		void append(int value)
		{
			Node* new_node = new Node(value);

			if (_head == nullptr)
				_head = new_node;
			else
			{
				Node* travel = _head;

				while (travel->_next != nullptr)
					travel = travel->_next;

				travel->_next = new_node;
			}
		}

		//***********************************************
		void remove(int value)
		{
			Node* travel = _head;
			Node* trail = travel;

			while (travel != nullptr && travel->_data != value) 
			{
				trail = travel;
				travel = travel->_next;
			}

			if (travel != nullptr)
			{
				if (travel == _head)
					_head = travel->_next;
				else
					trail->_next = travel->_next;

				delete travel;
			}
		}

		//***********************************************
		void insertOrdered(int value)
		{
			Node* new_node = new Node(value);

			if ((_head == nullptr) || (new_node->_data <= _head->_data))
			{
				new_node->_next = _head;
				_head = new_node;
			}
			else
			{
				Node* travel = _head;
				Node* trail = nullptr;

				while ((travel != nullptr) && (travel->_data <= new_node->_data))
				{
					trail = travel;
					travel = travel->_next;
				}

				trail->_next = new_node;
				new_node->_next = travel;
			}
		}

		//***********************************************
		Node* lookup(int value)
		{ 
			Node *travel = _head;

			while ((travel != nullptr) && (travel->_data != value))
				travel = travel->_next;

			return travel;
		}
		
		//***********************************************
		int elementValue(const Node* node)
		{ 
			return node->_data;
		}
		
		//***********************************************
		void elementRelease(Node *node) 
		{ }
		
		//***********************************************
		void traverse(void(*action)(int value))
		{ 
			Node* travel = _head;

			while (travel != nullptr)
			{
				action(travel->_data);
				travel = travel->_next;
			}
		}
};