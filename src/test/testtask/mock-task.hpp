#ifndef __MOCK_TASK_HPP__
#define __MOCK_TASK_HPP__

// TODO: fix this.
#include "../../task/task.hpp"

class MockTask: public Task {
public:
	MOCK_METHOD0(run, void());
};

#endif
