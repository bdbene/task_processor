#include <cstdlib>
#include "queue.hpp"
#include "task.hpp"
#include "worker.hpp"
using namespace std;

static inline uint32_t increment_index(uint32_t index, const uint32_t size) {
	return (index + 1) % size;
}

Queue::Queue(uint32_t size, uint32_t count) {
	thread_count = count;
	max_size = size;
	start_index = 0;
	end_index = 0;
	task_count = 0;

	container = new Taskptr[max_size];
	worker_pool = new Workerptr[thread_count];

	// Create the workers
	for (int i = 0; i < thread_count; ++i) {
		worker_pool[i] = new Worker(*this);
	}

	// Get the workers running
	for (int i = 0; i < thread_count; ++i) {
		worker_pool[i]->start();
	}



}

Queue::~Queue() {
	delete[] container;

	for (int i = thread_count - 1; i >= 0; --i) {
		delete worker_pool[i];
	}

	delete worker_pool;
}

void Queue::enqueue(const Taskptr task) {
	unique_lock<mutex> lk(lock);

	// If the queue is full, double the array.
	if (task_count == max_size) {
		Taskptr* new_container = new Taskptr[max_size * 2];

		// Rearrange the queue so that the first task is at index zero.
		uint32_t cur_index = 0;
		uint32_t moved_task = 0;
		while (moved_task <= task_count) {
			new_container[cur_index] = container[start_index];
			start_index = increment_index(start_index, max_size);
			++cur_index;
			++moved_task;
		}
		start_index = 0;
		end_index = task_count;

		delete[] container;
		container = new_container;
		max_size *= 2;
	}

	container[end_index] = task;
	end_index = increment_index(end_index, max_size);
	++task_count;
	worker_cv.notify_one();
}

Task* Queue::dequeue() {
	unique_lock<mutex> lk(lock);

	while (task_count == 0) {
		// Wait on cv until work is available
		worker_cv.wait(lk);
	}

	Task* ret = container[start_index];
	start_index = increment_index(start_index, max_size);
	--task_count;

	return ret;
}

uint32_t Queue::get_task_count() {
	// Not automic, but good enough for now.
	return task_count;
}
