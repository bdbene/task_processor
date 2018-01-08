#include <cstdlib>
#include "queue.hpp"
#include "task.hpp"
#include "worker.hpp"
using namespace std;

static inline uint32_t increment_index(uint32_t index, const uint32_t size) {
	return (index + 1) % size;
}

Queue::Queue(uint32_t size, uint32_t count): max_worker_count(count) {
	worker_count = count;
	worker_resting = count;
	shut_down = false;
	max_size = size;
	start_index = 0;
	end_index = 0;
	task_count = 0;

	container = new Taskptr[max_size];
	worker_pool = new Workerptr[worker_count];

	// Create the workers
	for (int i = 0; i < worker_count; ++i) {
		worker_pool[i] = new Worker(*this);
	}

	// Get the workers running
	for (int i = 0; i < worker_count; ++i) {
		worker_pool[i]->start();
	}
}

Queue::~Queue() {
	{
		unique_lock<mutex> lk(lock);
		delete[] container;
		container = nullptr;

		shut_down = true;

		// Wait until all workers have finished their currently assigned tasks.
		while(worker_count > worker_resting) {
			cleanup_cv.wait(lk);
		}
	}

	for (int i = worker_count - 1; i >= 0; --i) {
		// Worker dtor notfies pool if it has already stopped worker,
		// preventing double deletes.
		delete worker_pool[i];
	}

	delete[] worker_pool;
}

void Queue::enqueue(const Taskptr task) {
	unique_lock<mutex> lk(lock);

	if (shut_down) {
		return;
	}

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

	if (shut_down) {
		--worker_count;
		cleanup_cv.notify_one();
		return nullptr;
	}

	// Notify the queue that this worker is sleeping in case of shutdown.
	bool notified_sleeping = false;
	while (task_count == 0) {
		// Wait on cv until work is available
		if (!notified_sleeping) {
			++worker_resting;
			notified_sleeping = true;
		}
		cleanup_cv.notify_one();
		worker_cv.wait(lk);
	}
	--worker_resting;

	Task* ret = container[start_index];
	start_index = increment_index(start_index, max_size);
	--task_count;

	return ret;
}

uint32_t Queue::get_task_count() {
	// Not atomic, but good enough for now.
	return task_count;
}

void Queue::notify_stopped(Worker* worker) {
	// Traverse the pool
	for (int i = 0; i < max_worker_count; i++) {
		// Remove the worker from the pool if it matches.
		if (worker_pool[i] == worker) {
			--worker_count;

			// Remove the reference to the worker. No recovery.
			worker_pool[i] = nullptr;
			break;
		}
	}

	// For now, don't bother spawning another worker.
}
