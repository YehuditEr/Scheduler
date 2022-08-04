#include "Task.h"
#include "DefinationsOfSize.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#pragma region Declarations of functions
Task* createTask(int priority, double size);
void freeTask(Task* task);
void printTask(const Task* task);
Task* createRandomTask();
int getId(Task* task);
void setId(Task* task, int id);
TypeTask* getTypeTask(Task* task);
void setTypeTask(Task* task, TypeTask* typeTask);
double getSize(Task* task);
void setSize(Task* task, double size);
double getRandomSizeByPriority(int priority);
int getRandomPriority();
#pragma endregion


/* Create task with values */
Task* createTask(int priority, double size) {
	Task* task = calloc(1, sizeof(Task));
	assert(task);
	setId(task, id++);
	setTypeTask(task, getTypeTaskByPriority(priority));
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
	freeTypeTask(getTypeTask(task));
	free(task);
}


/* Print all values of task */
void printTask(const Task* task) {
	assert(task);
	printf("\nTask: { ");
	printTypeTask(getTypeTask(task));
	printf(", id: %d, size: %f }\n", getId(task), getSize(task));
}


int getId(Task* task) {
	assert(task);
	return task->id;
}
void setId(Task* task, int id) {
	assert(task);
	task->id = id;
}

TypeTask* getTypeTask(Task* task) {
	assert(task);
	return task->typeTask;
}
void setTypeTask(Task* task, TypeTask* typeTask) {
	assert(task);
	assert(typeTask);
	task->typeTask = typeTask;
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