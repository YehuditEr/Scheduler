#include "TypeTask.h"


//use spaces please!
//this file shall be moved to test proj

#pragma region Declarations of functions
/// <summary>
///Create TypeTask with all values, called only from the function getTypeTaskByPriority
/// </summary>
/// <param name="priority">priority of TypeTask</param>
/// <param name="name">goal of TypeTask</param>
/// <param name="timeToByte">time to byte of TypeTask</param>
/// <param name="timeOut">time out TypeTask</param>
/// <returns>pointer of TypeTask</returns>
TypeTask* createTypeTask(int priority, char* name, double timeToByte, int timeOut);
/// <summary>
/// Set priority of TypeTask
/// </summary>
/// <param name="typeTask">pointer of TypeTask you want to insert a value into</param>
/// <param name="priority">priority of this TypeTask</param>
void setPriority(TypeTask* typeTask, int priority);
/// <summary>
/// Set name of TypeTask
/// </summary>
/// <param name="typeTask">pointer of TypeTask you want to insert a value into</param>
/// <param name="name">goal of this TypeTask</param>
void setName(TypeTask* typeTask, char* name);
/// <summary>
/// Set time to byte of TypeTask
/// </summary>
/// <param name="typeTask">pointer of TypeTask you want to insert a value into</param>
/// <param name="timeToByte">TimeToByte of this TypeTask</param>
void setTimeToByte(TypeTask* ttypeTaskype, double timeToByte);
/// <summary>
/// Set time out of TypeTask
/// </summary>
/// <param name="typeTask">pointer of TypeTask you want to insert a value into</param>
/// <param name="timeOut">TimeOut of this TypeTask</param>
void setTimeOut(TypeTask* typeTask, int timeOut);
/// <summary>
/// Retrieving the time out of a TypeTask
/// </summary>
/// <param name="typeTask">- Pointer to TypeTask</param>
/// <returns>Time Out of TypeTask</returns>
int getTimeOut(TypeTask* typeTask);
/// <summary>
/// Checking whether the received value is valid
/// </summary>
/// <param name="name">string of goal of TypeTask</param>
/// <returns>true or false</returns>
bool isValidName(char* name);
/// <summary>
/// Checking whether the received value is valid
/// </summary>
/// <param name="timeToByte">timeToByte of TypeTask</param>
/// <returns>true or false</returns>
bool isValidTimeToByte(double timeToByte);
/// <summary>
/// Checking whether the received value is valid
/// </summary>
/// <param name="priority">priority of TypeTask</param>
/// <returns>true or false</returns>
bool isValidPriority(int priority);
/// <summary>
/// Checking whether the received value is valid
/// </summary>
/// <param name="timeOut">timeOut of TypeTask</param>
/// <returns>true or false</returns>
bool isValidTimeOut(int timeOut);

#pragma endregion

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

void printTypeTask(const TypeTask* typeTask) {
	printf("typeTask { name: %s, priority:%d, time-to-byte: %f, timeOut: %d }",
		getName(typeTask), getPriority(typeTask), getTimeToByte(typeTask), getTimeOut(typeTask));
}

void freeTypeTask(TypeTask* typeTask) {
	assert(typeTask);
	free(typeTask->name);
	free(typeTask);
}

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