#pragma once
#pragma region Defines
#define READ "read"
#define WRITE "write"
#define DELETE "delete"

#define TIME_TO_BYTE_PRIORITY1 0.1
#define TIME_TO_BYTE_PRIORITY2 0.2
#define TIME_TO_BYTE_PRIORITY3 0.3

#define TIMEOUT_PRIORITY1 170
#define TIMEOUT_PRIORITY2 440
#define TIMEOUT_PRIORITY3 740
#pragma endregion
#pragma region Includes

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#pragma endregion


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
/// <summary>
/// Retrieving the priority of a TypeTask
/// </summary>
/// <param name="typeTask">- Pointer to TypeTask</param>
/// <returns>Priority of TypeTask</returns>
int getPriority(TypeTask* typeTask);
/// <summary>
/// Retrieving the purpuse of a TypeTask
/// </summary>
/// <param name="typeTask">- Pointer to TypeTask</param>
/// <returns>The purpose of the TypeTask</returns>
char* getName(TypeTask* typeTask);
/// <summary>
/// Retrieving the time to byte of a TypeTask
/// </summary>
/// <param name="typeTask">- Pointer to TypeTask</param>
/// <returns>Time to byte of TypeTask</returns>
double getTimeToByte(TypeTask* typeTask);