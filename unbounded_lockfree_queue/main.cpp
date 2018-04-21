

#include <iostream>
#include <thread>

#ifdef GL
#include "giantlock_queue.hpp"
#else
#include "unbounded_lockfree_queue.hpp"
#endif

#define PRODUCER_THREAD 12
#define ENQUE_PER_PRODUCER 10000000

#define CONSUMER_THREAD 1
#define DEQUE_PER_CONSUMER (ENQUE_PER_PRODUCER*PRODUCER_THREAD/CONSUMER_THREAD)


#ifdef GL
giantlock_queue<uint64_t> q;
#else
unbounded_queue<uint64_t> q;
#endif

bool validation[PRODUCER_THREAD*ENQUE_PER_PRODUCER];

void producer(int base) {
	for (int i = 0; i < ENQUE_PER_PRODUCER; i++) {
		q.enqueue(base + i);
	}
	return;
}

void consumer(void) {
	for (int i = 0; i < DEQUE_PER_CONSUMER; i++) {
		int v = q.dequeue();
		validation[v] = true;
	}
	return;
}


int main() {

	for (int i = 0; i < PRODUCER_THREAD*ENQUE_PER_PRODUCER; i++) {
		validation[i] = false;
	}

	std::thread producer_threads[PRODUCER_THREAD];
	std::thread consumer_threads[CONSUMER_THREAD];

	for (int i = 0; i < PRODUCER_THREAD; i++) {
		producer_threads[i] = std::thread(producer, i * ENQUE_PER_PRODUCER);
	}

	for (int i = 0; i < CONSUMER_THREAD; i++) {
		consumer_threads[i] = std::thread(consumer);
	}

	for (int i = 0; i < PRODUCER_THREAD; i++) {
		producer_threads[i].join();
	}

	for (int i = 0; i < CONSUMER_THREAD; i++) {
		consumer_threads[i].join();
	}

	for (int i = 0; i < PRODUCER_THREAD*ENQUE_PER_PRODUCER; i++) {
		if (validation[i] == false) {
			std::cout << "INCORRECT" << std::endl;
			break;
		}
	}

	std::cout << "CORRECT" << std::endl;

	return 0;
}


