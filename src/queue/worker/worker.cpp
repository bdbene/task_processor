#include "worker.hpp"
#include "queue.hpp"
#include "task.hpp"
using namespace std;

Worker::Worker(Queue &queue): queue(queue) {}

Worker::~Worker() {
	if (worker_thread.joinable()) {
		worker_thread.detach();
	}
}

void Worker::start() {
	worker_thread = thread(&Worker::run, this);
	worker_thread.detach();
}

void Worker::run() {
	Task *task = queue.dequeue();
	task->run();
}
