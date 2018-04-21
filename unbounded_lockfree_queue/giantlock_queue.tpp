
#include <thread>

#include "giantlock_queue.hpp"


template <typename T>
giantlock_queue<T>::giantlock_queue()
{
}

template <typename T>
giantlock_queue<T>::~giantlock_queue()
{
}



template <typename T>
void giantlock_queue<T>::enqueue(T key)
{
	std::lock_guard<std::mutex> lock(mtx);
	q.emplace(key);
}

template <typename T>
T giantlock_queue<T>::dequeue()
{

	std::lock_guard<std::mutex> lock(mtx);
	T ret_key;

	while (q.empty()) {
		std::this_thread::yield();
	}
	ret_key = q.front();
	q.pop();

	return ret_key;
}





