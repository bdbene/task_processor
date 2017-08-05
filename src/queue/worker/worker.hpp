#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <thread>

class Queue;

class Worker {
private:
	Queue& queue;
	std::thread worker_thread;

public:
	Worker(Queue&);
	~Worker();

	void run();
	void start();
};

#endif
