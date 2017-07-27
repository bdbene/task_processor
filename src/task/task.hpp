#ifndef __TASK_HPP__
#define __TASK_HPP__

class Task {
	bool requeue_request;

public:
	virtual void run() = 0;
	bool is_requeue_requested();
};

#endif
