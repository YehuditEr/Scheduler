#pragma once
#include "TypeTask.h"

struct Task {
	int Id;
	TypeTask* typeTask;
	double size;
	double timeOut;
	//clock_t  Clock;
};

typedef struct Task Task;

Task* task_init();

void task_free(Task* task);

void print_task(const Task* task);

Task* create_random_task();
