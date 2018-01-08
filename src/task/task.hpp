#ifndef __TASK_HPP__
#define __TASK_HPP__

class Task {
public:
	typedef void (*Callback)();
private:
	Callback callback;
public:
	Task();
	Task(Callback);
	virtual ~Task();

	virtual void run() = 0;
	void notify();
};

#endif
