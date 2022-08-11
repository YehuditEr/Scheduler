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

#define NUM_PRIORITIES 3
#pragma endregion

#pragma region Includes

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#pragma endregion

/// <summary>
/// name - read/write/delete
/// timeToByte - 0.1/0.2/0.3
/// timeOut - 170/440/740
/// </summary>
struct Priority {
	char* name;
	double timeToByte;
	int timeOut;
}; 

typedef struct Priority Priority;

/// <summary>
/// init array of priorities with constant values
/// </summary>
/// <param name="numPriorities">- num priorties in this scheduler</param>
void initPriorities(int numPriorities);

char* getName(int priority);

double getTimeToByte(int priority);

int getTimeOut(int priority);

bool isValidPriority(int priority);