#include <cstdlib>
#include <cstring>
#include "queue.hpp"

Queue::Queue(uint32_t count, uint32_t size) {
	thread_count = count;
	max_size = size;
	start_index = 0;
	end_index = 0;
	task_count = 0;

	container = new Taskptr[size];
}

Queue::~Queue() {
	delete[] container;
}

void Queue::enqueue(const Taskptr task) {
	// If the queue is full, double the array.
	if (task_count == max_size) {
		Taskptr* new_container = new Taskptr[max_size * 2];

		memcpy(new_container, container, sizeof(Taskptr) * max_size);
		delete[] container;

		container = new_container;
		max_size *= 2;
	}

	container[end_index] = task;
	end_index = (end_index + 1) % max_size;
	++task_count;
}

Task* Queue::get_next_task() {
	Task* ret = container[start_index];
	start_index = (start_index + 1) % max_size;
	--task_count;

	return ret;
}

uint32_t Queue::get_task_count() {
	return task_count;
}
