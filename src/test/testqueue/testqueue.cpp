#include "queue.hpp"
#include "testqueue.hpp"

using ::testing::Return;
using namespace std;

TestQueue::TestQueue() {}

TestQueue::~TestQueue() {}

TEST_F(TestQueue, DefaultTaskCount_Zero) {
	Queue queue;

	EXPECT_EQ(0, queue.get_task_count());
}
