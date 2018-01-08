#include "task.hpp"

Task::Task() {
	callback = nullptr;
}

Task::Task(Callback callback): callback(callback) {}

Task::~Task() {}

void Task::notify() {
	if (callback != nullptr) {
		(*callback)();
	}
}
