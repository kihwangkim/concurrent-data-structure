#pragma once

#include <queue>
#include <mutex>

template <typename T>
class giantlock_queue {
	protected:
		std::queue<T> q;
		std::mutex mtx;

	public:
		// constructor
		giantlock_queue();
		~giantlock_queue();

		void enqueue(T key);
		T dequeue();
};

#include "giantlock_queue.tpp"
