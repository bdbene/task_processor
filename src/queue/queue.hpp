#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <cstdint>
#include <condition_variable>
#include <mutex>

class Task;
class Worker;

class Queue {
private:
	static const uint32_t default_size = 20;
	static const uint32_t default_threads = 4;

	typedef Task* Taskptr;
	typedef Worker* Workerptr;

	uint32_t thread_count;

	Taskptr* container;		// Points to all memory allocated for the queue
	Workerptr* worker_pool; // All worker threads
	void* raw_worker_mem;	// For allocating space without default ctor
	uint32_t max_size;		// Max number of tasks that can be queued.
	uint32_t start_index;	// First queued task
	uint32_t end_index;		// Last queued task
	uint32_t task_count;	// Number of queued tasks

	// To make the queue thread safe
	std::mutex lock;
	std::condition_variable worker_cv;		// For waiting workers.

	Queue(const Queue&);
	Queue operator=(const Queue&);

public:
	Queue(uint32_t size = default_size, uint32_t count = default_threads);
	~Queue();

	Taskptr dequeue();
	void enqueue(const Taskptr);

	uint32_t get_task_count();
};

#endif
