#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "Scheduler.h"
#include "Queue.h"

//some of the declaration shall be public and in H file.
#pragma region Declarations of functions
Scheduler* initScheduler();
double getQuantumToQueue(int queue);
Scheduling* initScheduling();
void freeScheduler(Scheduler* scheduler);
void freeScheduling(Scheduling* scheduling);
void putTask(Scheduler* scheduler, const Task* task);
bool isFull(Scheduler* scheduler);
bool isValidSize(Scheduler* scheduler, Task* task);
Queue* getQueueOfPriority(Scheduler* scheduler, int priority);
double getTimeToRunAllTask(Task* task);
void increasNumTasks(Scheduler* scheduler);
void decreasNumTasks(Scheduler* scheduler);
void decreaseSizeTask(Task* task, int decreaseSize);
double getPortionOfTaskCompletedOnTime(Task* task, double time);
Task* getTaskInCPU(Scheduler* scheduler);
void setTaskInCPU(Scheduler* scheduler, Task* task);
void isValidNumQueue(int numQueue);
void nextCurrentQueue(Scheduler* scheduler);
void setCurrentQueue(Scheduler* scheduler, int numQueue);
double getTimeInCurrentQueue(Scheduler* scheduler);
int getCurrentQueue(Scheduler* scheduler);
int getNumTasksInScheduler(Scheduler* scheduler);
int getCurrentQueueNotEmpty(Scheduler* scheduler);
void setTimeInCurrentQueue(Scheduler* scheduler, double time);
void increaseTimeInCurrentQueue(Scheduler* scheduler, double additionalTime);
bool isRemainingTimeToCurrentQueue(Scheduler* scheduler);
double remainingTimeToCurrentQueue(Scheduler* scheduler);
bool isEmptyScheduler(Scheduler* scheduler);
bool isEmptyScheduler(Scheduler* scheduler);
#pragma endregion

//add func description
Scheduler* initScheduler() {
	Scheduler* scheduler = calloc(1, sizeof(Scheduler));
	assert(scheduler);
	scheduler->queues = calloc(NUM_PRIORITIES, sizeof(Queue*));
	assert(scheduler->queues);
	scheduler->scheduling = initScheduling();
	scheduler->numTasks = 0;
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		scheduler->queues[i] = queue_init();
	return scheduler;
}

//add func description
Scheduling* initScheduling() {
	Scheduling* scheduling = calloc(1, sizeof(Scheduling));
	assert(scheduling);
	scheduling->taskInCPU = calloc(1, sizeof(Task));
	assert(scheduling->taskInCPU);
	scheduling->taskInCPU = NULL;
	scheduling->currentQueue = 0;
	scheduling->timeInCurrentQueue = 0;
}


void freeScheduler(Scheduler* scheduler) {
	assert(scheduler);
	freeScheduling(scheduler->scheduling);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		queue_free(scheduler->queues[i]);
}

//rename
void freeScheduling(Scheduling* scheduling) {
	assert(scheduling);
	freeTask(scheduling->taskInCPU);
	free(scheduling);
}

//rename:push task
//add func description
void putTask(Scheduler* scheduler, const Task* task) {
	assert(scheduler);
	assert(task);
	if (isFull(scheduler)) {//what is full? rename func
		printf("\nThe scheduler full!!\n");
		return;
	}

	if (!isValidSize(scheduler, task)) {
		printf("This is too big a task!!!");
		return;
	}

	Queue* queue = getQueueOfPriority(scheduler, getPriority(getTypeTask(task)));
	printf("\n\tput task id:%d, timeOut: %d", task->id, task->typeTask->timeOut);
	queue_enqueue(queue, task);
	scheduler->numTasks++;// why are you conuting twice? in here and in queue
}

//add func description
double removeTaskAndChangeSize(Scheduler* scheduler, int numQueue, double maxTime) {

	assert(maxTime <= QUANTUM_TASK);

	Task* task = queue_dequeue(getQueueOfPriority(scheduler, numQueue + 1));

	if (task == NULL) {
		printf("\n\tNO TASK TO REMOVE FROM QUEUE %d....\n", numQueue);
		return 0;
	}
	else
		printf("\nTask removed: %d", task->id);

	double timeTask = getTimeToRunAllTask(task);

	/* Completed the task */
	if (timeTask <= maxTime)
	{
		decreasNumTasks(scheduler);
		setTaskInCPU(scheduler, NULL);
		return timeTask;
	}

	else
	{
		decreaseSizeTask(task, getPortionOfTaskCompletedOnTime(task, maxTime));
		setTaskInCPU(scheduler, task);
		return maxTime;
	}
//add print: insert to CPU
}

//rename: no ing in func name
void removingCPU_PuttingScheduler(Scheduler* scheduler) {
	if (getTaskInCPU(scheduler) != NULL) 
	{
		int priority = getPriority(getTypeTask(getTaskInCPU(scheduler)));
		Queue* queue = getQueueOfPriority(scheduler, priority);
		queue_enqueue(queue, getTaskInCPU(scheduler));
	}
	setTaskInCPU(scheduler, NULL);
}

void printScheduler(const Scheduler* scheduler) {
	assert(scheduler);
	printf("\n********Scheduler********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(scheduler->queues[i], printTask);
	}
}

//add func description
double schedulerTasks(Scheduler* scheduler) {
	if (isEmptyScheduler(scheduler)) {
		printf("Scheduler is empty");
		return -1;
	}

	int numQueue = getCurrentQueueNotEmpty(scheduler); //rename:get current task count in queue
	assert(numQueue != -1);

	printf("\n\tuse queue: %d\n", numQueue);

	if (!isRemainingTimeToCurrentQueue(scheduler)) {
		setTimeInCurrentQueue(scheduler, 0);
		nextCurrentQueue(scheduler);
		numQueue = getCurrentQueueNotEmpty(scheduler);
		assert(numQueue != -1);
	}

	int remainingTime = remainingTimeToCurrentQueue(scheduler);
	int quantumToTask;
	if (QUANTUM_TASK < remainingTime)
		quantumToTask = QUANTUM_TASK;
	else
		quantumToTask = remainingTime;

	quantumToTask = removeTaskAndChangeSize(scheduler, getCurrentQueue(scheduler), quantumToTask);

	increaseTimeInCurrentQueue(scheduler, quantumToTask);

	return quantumToTask;
}

bool isRemainingTimeToCurrentQueue(Scheduler* scheduler) {
	/*int currentQueue = getCurrentQueue(scheduler);
	double maxTimeInQueue = getQuantumToQueue(scheduler);
	return getTimeInCurrentQueue(scheduler) < maxTimeInQueue;*/
	return (remainingTimeToCurrentQueue(scheduler) > 0);
}

double getQuantumToQueue(int numQueue) {
	switch (numQueue)
	{
		case 0:
			return QUANTUM_QUEUE1;
			break;
		case 1:
			return QUANTUM_QUEUE2;
			break;
		case 2:
			return QUANTUM_QUEUE3;
			break;
		default:
			printf("Current queue not valid");
			exit(-1);
	}
}

double remainingTimeToCurrentQueue(Scheduler* scheduler) {
	int currentQueue = getCurrentQueue(scheduler);
	double maxTimeInQueue = getQuantumToQueue(currentQueue);
	return maxTimeInQueue - getTimeInCurrentQueue(scheduler);
}

double getTimeInCurrentQueue(Scheduler* scheduler) {
	return scheduler->scheduling->timeInCurrentQueue;
}

void setTimeInCurrentQueue(Scheduler* scheduler, double time) {
	scheduler->scheduling->timeInCurrentQueue = time;
}

void increaseTimeInCurrentQueue(Scheduler* scheduler, double additionalTime) {
	scheduler->scheduling->timeInCurrentQueue += additionalTime;
}


bool isEmptyScheduler(Scheduler* scheduler) {
	return  0 >= getNumTasksInScheduler(scheduler);
}

int getNumTasksInScheduler(Scheduler* scheduler) {
	return scheduler->numTasks;
}

int getCurrentQueue(Scheduler* scheduler) {
	return scheduler->scheduling->currentQueue;
}

int getCurrentQueueNotEmpty(Scheduler* scheduler) {
	if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler)+1)))
	{
		nextCurrentQueue(scheduler);
		if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler)+1)))
		{
			nextCurrentQueue(scheduler);
			if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler)+1)))
			{
				nextCurrentQueue(scheduler);
				return -1;
			}

		}
	}
	return getCurrentQueue(scheduler);
}

void setCurrentQueue(Scheduler* scheduler, int numQueue) {
	isValidNumQueue(numQueue);
	scheduler->scheduling->currentQueue = numQueue;
}

void nextCurrentQueue(Scheduler* scheduler) {
	setCurrentQueue(scheduler, (getCurrentQueue(scheduler) + 1) % 3);
}


void isValidNumQueue(int numQueue) {
	return numQueue >= 0 && numQueue < NUM_PRIORITIES;
}


bool isFull(Scheduler* scheduler) {
	return MAX_TASKS <= scheduler->numTasks;
}

bool isValidSize(Scheduler* scheduler, Task* task) {
	return  MAX_SIZE_OF_TASK > task->size* task->typeTask->timeToByte;
}

Queue* getQueueOfPriority(Scheduler* scheduler, int prioity) {
	return scheduler->queues[prioity-1];
}

double getTimeToRunAllTask(Task* task) {
	assert(task);
	return task->size * task->typeTask->timeToByte;
}

void increasNumTasks(Scheduler* scheduler) {
	scheduler->numTasks++;
}

void decreasNumTasks(Scheduler* scheduler) {
	scheduler->numTasks--;
}

void decreaseSizeTask(Task* task, int decreaseSize) {
	task->size -= decreaseSize;
}

double getPortionOfTaskCompletedOnTime(Task* task, double time) {
	return time / task->typeTask->timeToByte;
}

Task* getTaskInCPU(Scheduler* scheduler) {
	return scheduler->scheduling->taskInCPU;
}

void setTaskInCPU(Scheduler* scheduler, Task* task) {
	scheduler->scheduling->taskInCPU = task;
}
