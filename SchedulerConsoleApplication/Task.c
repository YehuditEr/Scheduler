#include "Task.h"
#include "DefinationsOfSize.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#pragma region Declarations of functions
void setId(Task* task, int id);
void setPriority(Task* task, int priority);
void setSize(Task* task, double size);
double getRandomSizeByPriority(int priority);
int getRandomPriority();
#pragma endregion


/* Create task with values */
Task* createTask(int priority, double size) {
	Task* task = calloc(1, sizeof(Task));
	assert(task);
	setId(task, id++);
	setPriority(task, priority);
	setSize(task, size);
	return task;
}


/* Create task with random values */
Task* createRandomTask() {
	int priority = getRandomPriority();
	double size = getRandomSizeByPriority(priority);
	return createTask(priority, size);
}


/* Freeing dynamically allocated memory */
void freeTask(Task* task) {
	assert(task);
	free(task);
}

Task* dynamicAllocationTask() {
	Task* task = calloc(1, sizeof(Task));
	return task;
}


/* Print all values of task */
void printTask(const Task* task) {
	assert(task);
	printf("\nTask: { ");
	printf("id: %d, priority: %d, size : %f }\n", getId(task), getPriority(task), getSize(task));
}

int getPriority(Task* task) {
	assert(task);
	return task->priority;
}
void setPriority(Task* task, int priority) {
	assert(task);
	assert(isValidPriority(priority));
	task->priority = priority;
}


int getId(Task* task) {
	assert(task);
	return task->id;
}
void setId(Task* task, int id) {
	assert(task);
	task->id = id;
}


double getSize(Task* task) {
	assert(task);
	return task->size;
}
void setSize(Task* task, double size) {
	assert(task);
	task->size = size;
}

double getRandomSizeByPriority(int priority) {
	assert(isValidPriority(priority));
	switch (priority)
	{
		case 1:
			return (rand() % 200) + 1;
		case 2:
			return (rand() % 100) + 1;
		case 3:
			return (rand() % 66) + 1;
		default:
			printf("priority %d not exist...", priority);
			exit(-1);
	}
}
int getRandomPriority() {
	return (rand() % NUM_PRIORITIES) + 1;
}

double getTimeToRunAllTask(Task* task) {
	assert(task);
	return task->size * getTimeToByte(getPriority(task));
}

double getPortionOfTaskCompletedOnTime(Task* task, double time) {
	assert(task);
	return time / getTimeToByte(getPriority(task));
}