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

	const uint32_t max_worker_count;
	uint32_t worker_count;
	uint32_t worker_resting;
	bool shut_down;			// Whether queue is shutting down

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
	std::condition_variable cleanup_cv;		// For waiting for all workers to finish their current task.

	Queue(const Queue&);
	Queue operator=(const Queue&);

public:
	Queue(uint32_t size = default_size, uint32_t count = default_threads);
	~Queue();

	Taskptr dequeue();
	void enqueue(const Taskptr);

	void notify_stopped(Worker*);

	uint32_t get_task_count();
};

#endif
