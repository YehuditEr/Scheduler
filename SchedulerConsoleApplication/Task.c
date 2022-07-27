#include "Task.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define NUM_PRIORITIES 3

Task* task_init() {
	Task* task = calloc(1, sizeof(Task));
	assert(task);
	task->typeTask = type_init();
}

void task_free(Task* task) {
	assert(task);
	type_free(task->typeTask);
	free(task);
}


void print_task(const Task* task) {
	printf("\nTask: { ");
	print_type(task->typeTask);
	printf(", size: %f, time-out: %f }\n", task->size, task->timeOut);
}

Task* create_random_task() {
	TypeTask** typeTaskArr = calloc(3, sizeof(TypeTask));
	assert(typeTaskArr);
	for (int i = 0; i < NUM_PRIORITIES; i++)
	{
		typeTaskArr[i] = type_init();
	}
	type_init_values(typeTaskArr[0], 1,"read", 0.1);
	type_init_values(typeTaskArr[1], 2, "delete", 0.2);
	type_init_values(typeTaskArr[2],  3, "write", 0.3);
	Task* task = task_init();
	int type = (rand() % 3) + 1;
	task->typeTask = typeTaskArr[type - 1];
	if (type == 1) {
		task->size = (rand() % 200) + 1;
		task->timeOut = 170;
	}
	else {
		if (type == 2) {
			task->size = (rand() % 100) + 1;
			task->timeOut = 440;
		}
		else {
			task->size = (rand() % 66) + 1;
			task->timeOut = 740;
		}
	}
	return task;
}