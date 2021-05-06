//***********************************************
// Read/Write Locking Linked List
// Rowan Parker
// Winter 2021

#pragma once
#include "List.h"
#include <mutex>
#include <shared_mutex>
using std::shared_mutex;

class ReadWriteLockList : public List
{
	public:
		//***********************************************
		ReadWriteLockList(int size = 0) : List()
		{ 
			for (int ii = 0; ii < size; ++ii)
				insertOrdered(ii);
		}

		//***********************************************
		~ReadWriteLockList()
		{
			purge();
		}

		//***********************************************
		void prepend(int value)
		{
			// acquire exclusive lock
			while (_mutex.try_lock() == false);

			Node* new_node = new Node(value);
			new_node->_next = _head;
			_head = new_node;

			// unlock exclusise lock
			_mutex.unlock();
		}

		//***********************************************
		void append(int value)
		{
			// acquire exclusive lock
			while (_mutex.try_lock() == false);

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

			// unlock exclusise lock
			_mutex.unlock();
		}

		//***********************************************
		void remove(int value)
		{
			// acquire exclusive lock
			while (_mutex.try_lock() == false);

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

			// unlock exclusise lock
			_mutex.unlock();
		}

		//***********************************************
		void insertOrdered(int value)
		{
			// acquire exclusive lock
			while (_mutex.try_lock() == false);

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

			// unlock exclusise lock
			_mutex.unlock();
		}

		//***********************************************
		Node* lookup(int value)
		{
			// acquire shared lock
			while (_mutex.try_lock_shared() == false);

			Node* travel = _head;

			while ((travel != nullptr) && (travel->_data != value))
				travel = travel->_next;

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
			// unlock shared lock
			_mutex.unlock_shared();
		}

		//***********************************************
		void traverse(void(*action)(int value))
		{
			// acquire shared lock
			while (_mutex.try_lock_shared() == false);

			Node* travel = _head;

			while (travel != nullptr)
			{
				action(travel->_data);
				travel = travel->_next;
			}

			// unlock shared lock
			_mutex.unlock_shared();
		}

	protected:
		shared_mutex _mutex;
};