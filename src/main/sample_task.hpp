#include "task.hpp"
#include "mutex"

class SampleTask: public Task {
	static std::mutex lock;
	static bool seeded;
	Queue& queue;
public:
	SampleTask(Queue&);
	~SampleTask();
	void run();
};
