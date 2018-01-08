#ifndef __CONCRETE_TASK_HPP__
#define __CONCRETE_TASK_HPP__

#include "../../task/task.hpp"

class ConcreteTask: public Task {
public:
	ConcreteTask();
	ConcreteTask(Callback);
	~ConcreteTask();

	virtual void run();
};

#endif
