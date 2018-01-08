#include "task.hpp"
#include "testtask.hpp"
#include "concrete_task.hpp"

using ::testing::Return;

TestTask::TestTask() {}

TestTask::~TestTask() {}

bool status = false;
void func() {
	status = true;
}

TEST_F(TestTask, NoCallback_NoopNotify) {
	ConcreteTask task;

	task.notify();

	EXPECT_TRUE(true);
}

TEST_F(TestTask, GivenCallbackFunction_NotifyCallsIt) {
	status = false;
	ConcreteTask task(func);

	task.notify();

	EXPECT_TRUE(status);
}

TEST_F(TestTask, Run_ExecutionReturns) {
	ConcreteTask task;

	task.run();

	EXPECT_TRUE(true);
}
