#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "queue.hpp"
#include "sample_task.hpp"
using namespace std;

bool SampleTask::seeded = false;

mutex SampleTask::lock;

SampleTask::SampleTask(Queue& queue): queue(queue) {
	if (!seeded) {
		srand(getpid());
		seeded = true;
	}
}

SampleTask::~SampleTask() {}

void SampleTask::run() {
	uint32_t seconds = (rand() % 5) + 2;

	{
		unique_lock<mutex> lk(lock);
		cout << "Working for " << seconds << endl;
	}
	this_thread::sleep_for(chrono::seconds(seconds));
	{
		unique_lock<mutex> lk(lock);
		cout << "Done working for " << seconds << endl;
	}
}
