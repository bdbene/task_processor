#include <cstdlib>
#include <iostream>
#include "queue.hpp"
#include "task.hpp"
using namespace std;

int main(int argc, char** argv) {
	int thread_count = 4;
	int task_count = 100;

	switch (argc) {
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

	cout << thread_count << endl;
	cout << task_count << endl;

	int queue_size = task_count / 2 + 1;

	Queue* processor = new Queue(thread_count, queue_size);
	delete processor;
}
