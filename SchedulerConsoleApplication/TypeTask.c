#include "TypeTask.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


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

#pragma region Declarations of functions
TypeTask* getTypeTaskByPriority(int priority);
TypeTask* createTypeTask(int priority, char* name, double timeToByte, int timeOut);

void printTypeTask(const TypeTask* typeTask);

void freeTypeTask(TypeTask* typeTask);

void setPriority(TypeTask* typeTask, int priority);
int getPriority(TypeTask* typeTask);

void setName(TypeTask* typeTask, char* name);
char* getName(TypeTask* typeTask);

void setTimeToByte(TypeTask* ttypeTaskype, double timeToByte);
double getTimeToByte(TypeTask* typeTask);

void setTimeOut(TypeTask* typeTask, int timeOut);
int getTimeOut(TypeTask* typeTask);

bool isValidName(char* name);
bool isValidTimeToByte(double timeToByte);
bool isValidPriority(int priority);
bool isValidTimeOut(int timeOut);

#pragma endregion


/* Based on the priority received, create a TypeTask */
TypeTask* getTypeTaskByPriority(int priority) {
	assert(isValidPriority(priority));
	switch (priority)
	{
		case 1:
			return createTypeTask(1, READ, TIME_TO_BYTE_PRIORITY1, TIMEOUT_PRIORITY1);
		case 2:
			return createTypeTask(2, WRITE, TIME_TO_BYTE_PRIORITY2, TIMEOUT_PRIORITY2);
		case 3:
			return createTypeTask(3, DELETE, TIME_TO_BYTE_PRIORITY3, TIMEOUT_PRIORITY3);
		default:
			printf("Priority %d not exist...", priority);
			return NULL;
	}
}


/* Print all values of TypeTask */
void printTypeTask(const TypeTask* typeTask) {
	printf("typeTask { name: %s, priority:%d, time-to-byte: %f, timeOut: %d }",
		getName(typeTask), getPriority(typeTask), getTimeToByte(typeTask), getTimeOut(typeTask));
}


/* Freeing dynamically allocated memory */
void freeTypeTask(TypeTask* typeTask) {
	assert(typeTask);
	free(typeTask->name);
	free(typeTask);
}


/* Create typeTask with values*/
TypeTask* createTypeTask(int priority, char* name, double timeToByte, int timeOut) {
	TypeTask* type = calloc(1, sizeof(TypeTask));
	assert(type);
	setPriority(type, priority);
	setName(type, name);
	setTimeToByte(type, timeToByte);
	setTimeOut(type, timeOut);
	return type;
}


void setPriority(TypeTask* typeTask, int priority) {
	assert(typeTask);
	assert(isValidPriority(priority));
	//assert(3 < priority || 0 > priority);
	typeTask->priority = priority;
}
int getPriority(TypeTask* typeTask) {
	assert(typeTask);
	return typeTask->priority;
}

void setName(TypeTask* typeTask, char* name) {
	assert(typeTask);
	assert(isValidName(name));
	typeTask->name = name;
}
char* getName(TypeTask* typeTask) {
	assert(typeTask);
	return typeTask->name;
}

void setTimeToByte(TypeTask* typeTask, double timeToByte) {
	assert(typeTask);
	assert(isValidTimeToByte(timeToByte));
	typeTask->timeToByte = timeToByte;
}
double getTimeToByte(TypeTask* typeTask) {
	assert(typeTask);
	return typeTask->timeToByte;
}

void setTimeOut(TypeTask* typeTask, int timeOut) {
	assert(typeTask);
	assert(isValidTimeOut(timeOut));
	typeTask->timeOut = timeOut;
}
int getTimeOut(TypeTask* typeTask) {
	assert(typeTask);
	return typeTask->timeOut;
}


inline bool isValidPriority(int priority) {
	return 3 >= priority && 0 <= priority;
}
inline bool isValidName(char* name) {
	return
		strcmp(name, READ) == 0 ||
		strcmp(name, WRITE) == 0 ||
		strcmp(name, DELETE) == 0;
}
inline bool isValidTimeToByte(double timeToByte) {
	return
		timeToByte == TIME_TO_BYTE_PRIORITY1 ||
		timeToByte == TIME_TO_BYTE_PRIORITY2 ||
		timeToByte == TIME_TO_BYTE_PRIORITY3;
}
inline bool isValidTimeOut(int timeOut) {
	return
		timeOut == TIMEOUT_PRIORITY1 ||
		timeOut == TIMEOUT_PRIORITY2 ||
		timeOut == TIMEOUT_PRIORITY3;
}