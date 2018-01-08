#include "concrete_task.hpp"

ConcreteTask::ConcreteTask(): Task() {}

ConcreteTask::ConcreteTask(Callback callback): Task(callback) {}

ConcreteTask::~ConcreteTask() {}

void ConcreteTask::run() {}
