#pragma once
#include <iostream>
#include <mutex>
#include <shared_mutex>

using std::cout;
using std::shared_mutex;

class Node
{
	friend class List;
	friend class SimpleList;
	friend class SingleLockList;
	friend class ReadWriteLockList;
	friend class FineGrainList;

	public:
		Node(int data) : _data(data), _next(nullptr)
		{ }

		~Node()
		{ }

		void display()
		{
			cout << _data << " ";
		}

	protected:
		int _data;
		Node* _next;
		shared_mutex _mutex;
};