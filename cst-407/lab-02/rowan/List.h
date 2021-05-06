//***********************************************
// Linked List Abstract Base Class
// Rowan Parker
// Winter 2021

#pragma once
#include "Node.h"

class List
{
	public:
		List(int nodes = 0)
		{ }

		virtual ~List()
		{ }

		virtual void prepend(int value) = 0;
		virtual void append(int value) = 0;
		virtual void remove(int value) = 0;
		virtual void insertOrdered(int value) = 0;
		virtual Node* lookup(int value) = 0;
		virtual int elementValue(const Node *node) = 0;
		virtual void elementRelease(Node *node) = 0;
		virtual void traverse(void(*action)(int value)) = 0;

	protected:
		Node* _head = nullptr;

		void purge()
		{
			Node* trail = _head;

			while (_head != nullptr)
			{
				_head = _head->_next;
				delete trail;
				trail = _head;
			}

			_head = nullptr;
		}
};