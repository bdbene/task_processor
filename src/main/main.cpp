#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "queue.hpp"
#include "sample_task.hpp"
using namespace std;

int main(int argc, char** argv) {
	int thread_count = 4;
	int task_count = 100;
	int seconds = 20;
	SampleTask** tasks = nullptr;

	switch (argc) {
		case 4:
			seconds = atoi(argv[3]);
		case 3:
			task_count = atoi(argv[2]);
		case 2:
			thread_count = atoi(argv[1]);
		case 1:
			break;
		default:
			cerr << "ERROR: Incorrect number of arguments. (" << argc - 1 << ")" << endl;
			return -1;
	}

	int queue_size = task_count / 2 + 1;

	Queue processor(queue_size, thread_count);
	tasks = new SampleTask*[task_count];
	for (int i = 0; i < task_count; i++) {
		tasks[i] = new SampleTask(processor);
		processor.enqueue(tasks[i]);
	}

	this_thread::sleep_for(chrono::seconds(20));

	for (int i = task_count - 1; i >= 0; --i) {
		delete tasks[i];
	}

	delete[] tasks;
}
