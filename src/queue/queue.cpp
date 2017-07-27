#include <cstdlib>
#include "queue.hpp"
#include "task.hpp"

static inline uint32_t increment_index(uint32_t index, const uint32_t size) {
	return (index + 1) % size;
}

Queue::Queue(uint32_t size, uint32_t count) {
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
}

Task* Queue::dequeue() {
	Task* ret = container[start_index];
	start_index = increment_index(start_index, max_size);
	--task_count;

	return ret;
}

uint32_t Queue::get_task_count() {
	return task_count;
}
