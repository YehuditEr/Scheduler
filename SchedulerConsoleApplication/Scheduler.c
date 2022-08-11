#include "Scheduler.h"
#include "Queue.h"

#pragma region Declarations of functions
Scheduler* initScheduler();
Scheduling* initScheduling();
void freeScheduler(Scheduler* scheduler);
void freeScheduling(Scheduling* scheduling);
void putTask(Scheduler* scheduler, const Task* task);
double removeTaskAndChangeSize(Scheduler* scheduler, int numQueue, double maxTime);
void increaseNumTask(Scheduler* scheduler);
void decreaseNumTask(Scheduler* scheduler);
void increaseTimeInCurrentQueue(Scheduler* scheduler, double additionalTime);
void decreaseSizeTask(Task* task, double decreaseSize);
bool isValidQuantumTask(double time);
bool isValidNumQueue(int numQueue);
bool isValidSizeTask(Scheduler* scheduler, Task* task);
bool isRemainingTimeToCurrentQueue(Scheduler* scheduler);
bool isEmptyScheduler(Scheduler* scheduler);
bool isSchedulerFull(Scheduler* scheduer);
double getQuantumToQueue(int queue);
double getTimeInCurrentQueue(Scheduler* scheduler);
Queue* getQueueOfPriority(Scheduler* scheduler, int priority);
Task* getTaskInCPU(Scheduler* scheduler);
void setTaskInCPU(Scheduler* scheduler, Task* task);
void setCurrentQueue(Scheduler* scheduler, int numQueue);
int getCurrentQueue(Scheduler* scheduler);
int getNumTasksInScheduler(Scheduler* scheduler);
int getCurrentQueueNotEmpty(Scheduler* scheduler);
void setTimeInCurrentQueue(Scheduler* scheduler, double time);

double remainingTimeToCurrentQueue(Scheduler* scheduler);
void nextCurrentQueue(Scheduler* scheduler);
void printSpace();
#pragma endregion

/* Dynamic initialization and allocation for the scheduler */
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

/* Dynamic initialization and allocation for the scheduling */
Scheduling* initScheduling() {
	Scheduling* scheduling = calloc(1, sizeof(Scheduling));
	assert(scheduling);
	scheduling->taskInCPU = dynamicAllocationTask();
	assert(scheduling->taskInCPU);
	scheduling->taskInCPU = NULL;
	scheduling->currentQueue = 0;
	scheduling->timeInCurrentQueue = 0;
	return scheduling;
}

/* Freeing dynamically allocated memory of Scheduler */
void freeScheduler(Scheduler* scheduler) {
	assert(scheduler);
	freeScheduling(scheduler->scheduling);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		queue_free(scheduler->queues[i]);
}

/* Freeing dynamically allocated memory of Scheduling */
void freeScheduling(Scheduling* scheduling) {
	assert(scheduling);
	freeTask(scheduling->taskInCPU);
	free(scheduling);
}

/* Scheduler the task to run in CPU */
double schedulerTasks(Scheduler* scheduler) {
	printSpace();
	printf("----------schedulerTasks----------");
	if (isEmptyScheduler(scheduler)) {
		printf("\n\tScheduler empty");
		return -1;
	}

	int numQueue = getCurrentQueueNotEmpty(scheduler);
	assert(isValidNumQueue(numQueue));
	/* If the timing for the current queue is timed out */
	if (!isRemainingTimeToCurrentQueue(scheduler)) {
		setTimeInCurrentQueue(scheduler, 0);
		nextCurrentQueue(scheduler);
		numQueue = getCurrentQueueNotEmpty(scheduler);
		assert(isValidNumQueue(numQueue));
	}
	printf("\n\tUse queue %d", numQueue);

	/* 
		Running the task for the shortest time: 
			* QUANTUM_TASK
			* remaining time to current queue
	*/
	double remainingTime = remainingTimeToCurrentQueue(scheduler);
	double quantumToTask;
	if (QUANTUM_TASK < remainingTime)
		quantumToTask = QUANTUM_TASK;
	else
		quantumToTask = remainingTime;

	quantumToTask = removeTaskAndChangeSize(scheduler, getCurrentQueue(scheduler), quantumToTask);

	increaseTimeInCurrentQueue(scheduler, quantumToTask);

	printf("\n\tTask run in cpu to %f", quantumToTask);

	return quantumToTask;
}

/* Adding a new task to the schedule */
void putTask(Scheduler* scheduler, const Task* task) {
	assert(scheduler);
	assert(task);

	if (isSchedulerFull(scheduler)) {
		printf("\n\tScheduler is full");
		return;
	}

	if (!isValidSizeTask(scheduler, task)) {
		printf("\n\tSize of task not valid");
		printTask(task);
		return;
	}

	Queue* queue = getQueueOfPriority(scheduler, getPriority(task));
	assert(queue);
	queue_enqueue(queue, task);
	increaseNumTask(scheduler);
}

/* Removing a task from the queue and resizing the task */
double removeTaskAndChangeSize(Scheduler* scheduler, int numQueue, double maxTime) {
	assert(isValidQuantumTask(maxTime));

	Task* task = queue_dequeue(getQueueOfPriority(scheduler, numQueue + 1));

	if (task == NULL)
	{
		printf("\n\tNot exist task to remove in queue %d", numQueue);
		return 0;
	}
	else
		printf("\n\tRemove task %d from queueu %d", getId(task), numQueue);


	double timeTask = getTimeToRunAllTask(task);
	printf("\n\tTime to run all task %f", timeTask);
	/* Completed the task */
	if (timeTask <= maxTime)
	{
		printf("\n\tCompleted task %d", getId(task));
		decreaseNumTask(scheduler);
		setTaskInCPU(scheduler, NULL);
		return timeTask;
	}

	else
	{
		double prtitionComplete = getPortionOfTaskCompletedOnTime(task, maxTime);
		printf("\n\tPartition from task that completed %f", prtitionComplete);
		decreaseSizeTask(task, prtitionComplete);
		setTaskInCPU(scheduler, task);
		return maxTime;
	}
}

/* Print all task in scheduer */
void printScheduler(const Scheduler* scheduler) {
	assert(scheduler);
	printf("\n********Scheduler********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(scheduler->queues[i], printTask);
	}
}

/* Removing the task from the CPU and inserting it into the Scheduler */
void removingCPU_PuttingScheduler(Scheduler* scheduler) {
	if (getTaskInCPU(scheduler) != NULL)
	{
		int priority = getPriority(getTaskInCPU(scheduler));
		Queue* queue = getQueueOfPriority(scheduler, priority);
		queue_enqueue(queue, getTaskInCPU(scheduler));
	}
	setTaskInCPU(scheduler, NULL);
}


void increaseNumTask(Scheduler* scheduler) {
	scheduler->numTasks++;
}

void decreaseNumTask(Scheduler* scheduler) {
	scheduler->numTasks--;
}

void increaseTimeInCurrentQueue(Scheduler* scheduler, double additionalTime) {
	scheduler->scheduling->timeInCurrentQueue += additionalTime;
}

void decreaseSizeTask(Task* task, double decreaseSize) {
	task->size -= decreaseSize;
}

bool isValidQuantumTask(double time) {
	return  QUANTUM_TASK >= time;
}

bool isValidNumQueue(int numQueue) {
	return numQueue >= 0 && numQueue < NUM_PRIORITIES;
}

bool isValidSizeTask(Scheduler* scheduler, Task* task) {
	return  MAX_SIZE_OF_TASK > getSize(task) * getTimeToByte(getPriority(task));
}

bool isRemainingTimeToCurrentQueue(Scheduler* scheduler) {
	return remainingTimeToCurrentQueue(scheduler) > 0;
}

bool isEmptyScheduler(Scheduler* scheduler) {
	return  0 >= getNumTasksInScheduler(scheduler);
}

bool isSchedulerFull(Scheduler* scheduler) {
	return MAX_TASKS <= scheduler->numTasks;
}


double getQuantumToQueue(int numQueue) {

	switch (numQueue)
	{
		case 0:
			return QUANTUM_QUEUE1;
		case 1:
			return QUANTUM_QUEUE2;
		case 2:
			return QUANTUM_QUEUE3;
		default:
			exit(-1);
	}
}

double getTimeInCurrentQueue(Scheduler* scheduler) {
	return scheduler->scheduling->timeInCurrentQueue;
}

void setTimeInCurrentQueue(Scheduler* scheduler, double time) {
	scheduler->scheduling->timeInCurrentQueue = time;
}

int getCurrentQueue(Scheduler* scheduler) {
	return scheduler->scheduling->currentQueue;
}

int getCurrentQueueNotEmpty(Scheduler* scheduler) {
	if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler) + 1)))
	{
		nextCurrentQueue(scheduler);
		if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler) + 1)))
		{
			nextCurrentQueue(scheduler);
			if (isEmptyQueue(getQueueOfPriority(scheduler, getCurrentQueue(scheduler) + 1)))
			{
				nextCurrentQueue(scheduler);
				return -1;
			}

		}
	}
	return getCurrentQueue(scheduler);
}

void setCurrentQueue(Scheduler* scheduler, int numQueue) {
	assert(isValidNumQueue(numQueue));
	scheduler->scheduling->currentQueue = numQueue;

}

Queue* getQueueOfPriority(Scheduler* scheduler, int prioity) {
	return scheduler->queues[prioity - 1];
}

Task* getTaskInCPU(Scheduler* scheduler) {
	//if (scheduler->scheduling->taskInCPU == NULL)
	//	printf("\tgetTaskInCPU is NULL!!");
	//else
	//	printf("\tgetTaskInCPU: id=%d", getId(scheduler->scheduling->taskInCPU));
	return scheduler->scheduling->taskInCPU;
}

void setTaskInCPU(Scheduler* scheduler, Task* task) {
	//if (getTaskInCPU(scheduler) == NULL)
	//	printf("\tsetTaskInCPU is NULL");
	//else
	//	printf("\tsetTaskInCPU: old-id=%d", scheduler->scheduling->taskInCPU->id);
	scheduler->scheduling->taskInCPU = task;
	//if (getTaskInCPU(scheduler) == NULL)
	//	printf("\tsetTaskInCPU new task is NULL");
	//else
	//	printf("\tsetTaskInCPU: new-task-id=%d", scheduler->scheduling->taskInCPU->id);
}

int getNumTasksInScheduler(Scheduler* scheduler) {
	return scheduler->numTasks;
}


double remainingTimeToCurrentQueue(Scheduler* scheduler) {
	int currentQueue = getCurrentQueue(scheduler);
	double maxTimeInQueue = getQuantumToQueue(currentQueue);
	double timeInCurrentQueueu = getTimeInCurrentQueue(scheduler);
	return maxTimeInQueue - timeInCurrentQueueu;
}

void nextCurrentQueue(Scheduler* scheduler) {
	setCurrentQueue(scheduler, (getCurrentQueue(scheduler) + 1) % 3);
	setTimeInCurrentQueue(scheduler, 0);
}

void printSpace() {
	printf("\n\n\n");
}