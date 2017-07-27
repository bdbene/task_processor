#include "queue.hpp"
#include "testqueue.hpp"
#include "mock-task.hpp"

using ::testing::Return;
using namespace std;

TestQueue::TestQueue() {}

TestQueue::~TestQueue() {}

TEST_F(TestQueue, DefaultTaskCount_Zero) {
	Queue queue;

	EXPECT_EQ(0, queue.get_task_count());
}

TEST_F(TestQueue, AddOneTask_CountOne) {
	Queue queue;
	MockTask task;

	queue.enqueue(&task);

	EXPECT_EQ(1, queue.get_task_count());
}

TEST_F(TestQueue, AddMultiple_CountMultiple) {
	Queue queue;
	MockTask task1;
	MockTask task2;
	MockTask task3;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);

	EXPECT_EQ(3, queue.get_task_count());
}

TEST_F(TestQueue, AddTaskForceResize_CountMultiple) {
	Queue queue(3);
	MockTask task1;
	MockTask task2;
	MockTask task3;
	MockTask task4;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);
	queue.enqueue(&task4);

	EXPECT_EQ(4, queue.get_task_count());
}

TEST_F(TestQueue, RemoveOneTask_Zero) {
	Queue queue;
	MockTask task;

	queue.enqueue(&task);
	queue.dequeue();

	EXPECT_EQ(0, queue.get_task_count());
}

TEST_F(TestQueue, DequeueOneFromSeveral_SeveralRemain) {
	Queue queue;
	MockTask task1;
	MockTask task2;
	MockTask task3;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);
	queue.dequeue();

	EXPECT_EQ(2, queue.get_task_count());
}

TEST_F(TestQueue, DequeueAfterResize_SeveralRemain) {
	Queue queue(3);
	MockTask task1;
	MockTask task2;
	MockTask task3;
	MockTask task4;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);
	queue.enqueue(&task4);
	queue.dequeue();

	EXPECT_EQ(3, queue.get_task_count());
}

TEST_F(TestQueue, DequeueOnlyTask_TaskReturned) {
	Queue queue;
	MockTask task;

	queue.enqueue(&task);

	EXPECT_EQ(&task, queue.dequeue());
}

TEST_F(TestQueue, DequeueSeveralTasks_FifoOrder) {
	Queue queue;
	MockTask task1;
	MockTask task2;
	MockTask task3;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);

	EXPECT_EQ(&task1, queue.dequeue());
	EXPECT_EQ(&task2, queue.dequeue());
	EXPECT_EQ(&task3, queue.dequeue());
}

TEST_F(TestQueue, DequeueFromResizedQueue_FifoOrder) {
	Queue queue(3);
	MockTask task1;
	MockTask task2;
	MockTask task3;
	MockTask task4;

	queue.enqueue(&task1);
	queue.enqueue(&task2);
	queue.enqueue(&task3);
	queue.enqueue(&task4);

	EXPECT_EQ(&task1, queue.dequeue());
	EXPECT_EQ(&task2, queue.dequeue());
	EXPECT_EQ(&task3, queue.dequeue());
	EXPECT_EQ(&task4, queue.dequeue());
}
