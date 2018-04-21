#pragma once

template <typename T>
class unbounded_queue {
	protected:
		struct Node {
			T key;
			struct Node* next;
		};

		Node* HEAD;
		Node* TAIL;
		Node* dummy;

	public:
		// constructor
		unbounded_queue();
		~unbounded_queue();

		void enqueue(T key);
		T dequeue();
};

#include "unbounded_lockfree_queue.tpp"
