//***********************************************
// Fine Grain Locking Linked List
// Rowan Parker
// Winter 2021

#pragma once
#include "List.h"

class FineGrainList : public List
{
	public:
		//***********************************************
		FineGrainList(int size = 0) : List()
		{ 
			for (int ii = 0; ii < size; ++ii)
				insertOrdered(ii);
		}

		//***********************************************
		~FineGrainList()
		{
			purge();
		}

		//***********************************************
		void prepend(int value)
		{
			Node* new_node = new Node(value);
			new_node->_mutex.lock();

			if (_head == nullptr)
				_head = new_node;
			else
			{
				_head->_mutex.lock();
				new_node->_next = _head;
				_head = new_node;
				_head->_next->_mutex.unlock();
			}

			_head->_mutex.unlock();
		}

		//***********************************************
		void append(int value)
		{
			Node* new_node = new Node(value);
			new_node->_mutex.lock();

			if (_head == nullptr)
				_head = new_node;
			else
			{
				Node* travel = _head;
				while (travel->_mutex.try_lock() == false);
				
				while (travel->_next != nullptr)
				{
					travel->_mutex.unlock();
					travel = travel->_next;
					travel->_mutex.lock();
				}

				travel->_next = new_node;
				travel->_mutex.unlock();
			}

			new_node->_mutex.unlock();
		}

		//***********************************************
		void remove(int value)
		{
			if (_head != nullptr)
			{
				Node* travel = _head;
				Node* trail = travel;

				while (travel->_mutex.try_lock() == false);

				while (travel != nullptr && travel->_data != value)
				{
					trail->_mutex.unlock();
					trail = travel;
					travel = travel->_next;
					trail->_mutex.lock();
				}

				if (travel != nullptr)
				{
					if (travel == _head)
						_head = travel->_next;
					else
						trail->_next = travel->_next;

					travel->_mutex.unlock();
					delete travel;
				}

				trail->_mutex.unlock();
			}
		}

		//***********************************************
		void insertOrdered(int value)
		{
			Node* new_node = new Node(value);
	
			if (_head == nullptr)
			{
				_head = new_node;
			}
			else if (new_node->_data <= _head->_data)
			{
				while (_head->_mutex.try_lock() == false);
				new_node->_next = _head;
				_head = new_node;
				_head->_next->_mutex.unlock();
			}
			else
			{
				Node* travel = _head;
				Node* trail = travel;

				while (travel->_mutex.try_lock() == false);

				while (travel != nullptr && travel->_data <= value)
				{
					trail->_mutex.unlock();
					trail = travel;
					travel = travel->_next;
					trail->_mutex.lock();
				}

				trail->_next = new_node;
				new_node->_next = travel;
				trail->_mutex.unlock();
			}
		}

		//***********************************************
		Node* lookup(int value)
		{
			Node* travel = _head;
			Node* trail = travel;

			while(travel->_mutex.try_lock_shared() == false);

			while (travel != nullptr && travel->_data != value)
			{
				trail->_mutex.unlock_shared();
				trail = travel;
				travel = travel->_next;
				trail->_mutex.lock_shared();
			}

			if (trail != nullptr)
				trail->_mutex.unlock_shared();

			return travel;
		}

		//***********************************************
		int elementValue(const Node* node)
		{
			if (node != nullptr)
				return node->_data;
			else
				return -1;
		}

		//***********************************************
		void elementRelease(Node* node)
		{ 
			if (node != nullptr)
				node->_mutex.unlock_shared();
		}

		//***********************************************
		void traverse(void(*action)(int value))
		{
			Node* travel = _head;
			Node* trail = travel;

			while(travel->_mutex.try_lock_shared() == false);

			while (travel != nullptr)
			{
				action(travel->_data);

				trail->_mutex.unlock_shared();
				trail = travel;
				travel = travel->_next;
				trail->_mutex.lock_shared();
			}

			if (trail != nullptr)
				trail->_mutex.unlock_shared();
		}
};