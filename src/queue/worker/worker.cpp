#include "worker.hpp"
#include "queue.hpp"
#include "task.hpp"
using namespace std;

Worker::Worker(Queue &queue): queue(queue) {}

Worker::~Worker() {
	if (worker_thread.joinable()) {
		worker_thread.detach();
	}

	// Inform the queue that this is shutting down.
	queue.notify_stopped(this);
}

void Worker::start() {
	worker_thread = thread(&Worker::run, this);
	worker_thread.detach();
}

void Worker::run() {

	// The queue won't give work if it's shutting down.
	while (Task *task = queue.dequeue()) {
		task->run();
		task->notify();
	}
}
