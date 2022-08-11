#include "TypeTask.h"

static Priority** priorities;

Priority* createTypeTask(char* name, double timeToByte, int timeOut);

void initPriorities(int numPriorities) {
	priorities = calloc(numPriorities, sizeof(Priority*));
	assert(priorities);
	assert(numPriorities == 3);
	for (size_t i = 0; i < numPriorities; i++)
		priorities[i] = calloc(1, sizeof(Priority));
	priorities[0] = createTypeTask(READ, TIME_TO_BYTE_PRIORITY1, TIMEOUT_PRIORITY1);
	priorities[1] = createTypeTask(WRITE, TIME_TO_BYTE_PRIORITY2, TIMEOUT_PRIORITY2);
	priorities[2] = createTypeTask(DELETE, TIME_TO_BYTE_PRIORITY3, TIMEOUT_PRIORITY3);
}

char* getName(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority-1]->name;
}

double getTimeToByte(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority - 1]->timeToByte;
}

int getTimeOut(int priority) {
	assert(isValidPriority(priority));
	return priorities[priority - 1]->timeOut;
}

bool isValidPriority(int priority) {
	return NUM_PRIORITIES >= priority && 0 <= priority;
}

Priority* createTypeTask(char* name, double timeToByte, int timeOut) {
	Priority* priority = calloc(1, sizeof(Priority));
	assert(priority);
	priority->name = name;
	priority->timeOut = timeOut;
	priority->timeToByte = timeToByte;
	return priority;
}
