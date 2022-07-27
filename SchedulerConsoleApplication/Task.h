#pragma once
#include "TypeTask.h"

struct Task {
	TypeTask* typeTask;
	double size;
	double timeOut;
	//clock_t  Clock;
};

typedef struct Task Task;

Task* task_init();

void print_task(const Task* task);

