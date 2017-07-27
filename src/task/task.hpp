#ifndef __TASK_HPP__
#define __TASK_HPP__

class Task {
public:
	virtual void run() = 0;
	virtual ~Task() {}
};

#endif
