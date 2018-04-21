
#include <thread>

#include "unbounded_lockfree_queue.hpp"


template <typename T>
unbounded_queue<T>::unbounded_queue()
{
	dummy = new Node;
	dummy->next = NULL;
	HEAD = dummy;
	TAIL = dummy;
}

template <typename T>
unbounded_queue<T>::~unbounded_queue()
{
	while (true) {
		if (HEAD->next == NULL){
			break;
		}
		dequeue();
	}
	delete HEAD;
}



template <typename T>
void unbounded_queue<T>::enqueue(T key)
{
	Node* node = new Node;
	node->key = key;
	node->next = NULL;

	while (true) {
		Node* last = TAIL;
		Node* next = last->next;
		if (last == TAIL) {
			if (next == NULL) {
				if (__sync_bool_compare_and_swap(&last->next, next, node)) {
					__sync_bool_compare_and_swap(&TAIL, last, node);
					return;
				}
			}
			else {
				__sync_bool_compare_and_swap(&TAIL, last, next);
			}
		}
	}

	return;
}

// CAUTION!!
// In this version, only one thread can be dequeuing without datarace.
// multi producer, one consumer
template <typename T>
T unbounded_queue<T>::dequeue()
{
	T ret_key;

	while (true) {
		if (HEAD->next != NULL) {
			break;
		}
		std::this_thread::yield();
	}

	Node* temp = HEAD;

	HEAD = HEAD->next;
	ret_key = HEAD->key;

	delete temp;

	return ret_key;
}





