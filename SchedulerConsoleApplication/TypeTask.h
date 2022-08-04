#pragma once

#include <stdbool.h>

struct TypeTask {
	int priority;
	char* name;
	double timeToByte;
	int timeOut;
};


typedef struct TypeTask TypeTask;

/// <summary>
/// Based on the priority received, create a TypeTask
/// </summary>
/// <param name="priority">- valid: 1,2,3</param>
/// <returns>Pointer to TypeTask with values</returns>
TypeTask* getTypeTaskByPriority(int priority);

/// <summary>
/// Print all values of TypeTask
/// </summary>
/// <param name="typeTask">- Pointer to typeTask task</param>
void printTypeTask(const TypeTask* typeTask);

/// <summary>
/// Freeing dynamically allocated memory
/// </summary>
/// <param name="typeTask">- Pointer to TypeTask</param>
void freeTypeTask(TypeTask* typeTask);


int getPriority(TypeTask* typeTask);

char* getName(TypeTask* typeTask);

double getTimeToByte(TypeTask* typeTask);