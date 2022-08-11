#pragma once
#include "TypeTask.h"

struct Task {
	int id;
	int priority;
	double size;
};

typedef struct Task Task;

static int id = 0;

/// <summary>
/// Create task with values
/// </summary>
/// <param name="priority"></param>
/// <param name="size"></param>
/// <returns>Pointer to task</returns>
Task* createTask(int priority, double size);


/// <summary>
/// Freeing dynamically allocated memory
/// </summary>
/// <param name="task">- Pointer to task</param>
void freeTask(Task* task);


/// <summary>
/// Print all values of task
/// </summary>
/// <param name="task">- Pointer to task</param>
void printTask(const Task* task);


/// <summary>
/// Create task with random values
/// </summary>
/// <returns>Pointer to task</returns>
Task* createRandomTask();

double getTimeToRunAllTask(Task* task);

double getPortionOfTaskCompletedOnTime(Task* task, double time);


int getId(Task* task);

int getPriority(Task* task);

double getSize(Task* task);

Task* dynamicAllocationTask();