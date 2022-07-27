#include "Task.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Task* task_init() {
	Task* task = calloc(1, sizeof(Task));
	assert(task);
	task->typeTask = type_init();
}


void print_task(const Task* task) {
	printf("\nTask: { ");
	print_type(task->typeTask);
	printf(", size: %f, time-out: %f }\n", task->size, task->timeOut);
}
