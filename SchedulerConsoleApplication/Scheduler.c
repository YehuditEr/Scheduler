#include "Scheduler.h"


#pragma region Defination

void initMetaData();
void initTaskMetaData();

void freeMetaData();
void freeTaskMetaData();

Queue** getQueues();
Queue* getQueueByPriority(int priority);
void setQueues(Queue* queues);
int getNumTasks(); 
void setNumTasks(int numTasks);
SchedulerMetaData* getSchedulerMetaData();
void setSchedulerMetaData(SchedulerMetaData* schedulerMetaData);

int getCurrentQueue();
void setCurrentQueue(int currentQueue);
time_t getStartTimeInCurrentQueue();
void setStartTimeInCurrentQueue(time_t startTimeInCurrentQueue);
TaskInCpuMetaData* getTaskInCPUMetaData();
void setTaskInCPUMetaData(TaskInCpuMetaData* taskInCPUMetaData);

Task* getTaskInCPU();
void setTaskInCPU(Task* taskInCPU);
time_t getStartTimeOfTaskInCPU();
void setStartTimeOfTaskInCPU(time_t startTimeOfTaskInCPU);
double getTimeToRunInCPU();
void setTimeToRunInCPU(double timeToRunInCPU);
void setTaskInCpuMetaData(Task* taskInCPU, time_t startTimeOfTaskInCPU, double timeToRunInCPU);

int getQuantumToQueue(int numQueue);
double quantityRemainingForCurrentQueue();
void nextQueue();
int findQueueNotEmpty();

void decreaseNumTask();
void increaseNumTask();

bool isLeftTimeToRunTaskInCpu();
//bool isLeftTimeToCurrentQueue();

#pragma endregion



static SchedulerDataStructure* DataStructure;


#pragma region InitDataStructure
/* Dynamic initialization and allocation for the DataStructure */
void initDataStructure() {
	DataStructure = calloc(1, sizeof(SchedulerDataStructure));
	assert(DataStructure);
	DataStructure->queues = calloc(NUM_PRIORITIES, sizeof(Queue*));
	assert(DataStructure->queues);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		DataStructure->queues[i] = queue_init();
	DataStructure->numTasks = 0;
	initMetaData();
	assert(DataStructure->metaData);
	return DataStructure;
}

/* Dynamic initialization and allocation for SchedulerMetaData */
void initMetaData() {
	assert(DataStructure);
	DataStructure->metaData = calloc(1, sizeof(SchedulerMetaData));
	assert(DataStructure->metaData);
	DataStructure->metaData->currentQueue = 0;
	initTaskMetaData();
	assert(DataStructure->metaData->taskInCPUMetaData);
	DataStructure->metaData->startTimeInCurrentQueue = time(NULL);
	assert(DataStructure->metaData->startTimeInCurrentQueue);
}

/* Dynamic initialization and allocation for TaskMetaData */
void initTaskMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	DataStructure->metaData->taskInCPUMetaData = calloc(1, sizeof(TaskInCpuMetaData*));
	assert(DataStructure->metaData->taskInCPUMetaData);
	DataStructure->metaData->taskInCPUMetaData->startTimeOfTaskInCPU = 0;
	DataStructure->metaData->taskInCPUMetaData->lastUpdateTime = 0;
	DataStructure->metaData->taskInCPUMetaData->timeToRunInCPU = 0;
}
#pragma endregion

#pragma region FreeDataStructure
/* Freeing dynamically allocated memory of SchedulerDataStructure */
void freeDataStructure() {
	assert(DataStructure);
	assert(DataStructure->queues);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		queue_free(DataStructure->queues[i]);
	freeMetaData();
	free(DataStructure);
}

/* Freeing dynamically allocated memory of SchedulerMetaData */
void freeMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	free(DataStructure->metaData->startTimeInCurrentQueue);
	freeTaskMetaData();
	free(DataStructure->metaData);
}

/* Freeing dynamically allocated memory of TaskMetaData */
void freeTaskMetaData() {
	assert(DataStructure);
	assert(DataStructure->metaData);
	assert(DataStructure->metaData->taskInCPUMetaData);
	free(DataStructure->metaData->taskInCPUMetaData->startTimeOfTaskInCPU);
	free(DataStructure->metaData->taskInCPUMetaData->lastUpdateTime);
	freeTask(DataStructure->metaData->taskInCPUMetaData->taskInCPU);
	free(DataStructure->metaData);
}

#pragma endregion

#pragma region Getters & Setters of SchedulerDataSructure

/* return queues of DataStructure */
Queue** getQueues() {
	Queue** queues = DataStructure->queues;
	return DataStructure->queues;
}

/* return queue of priority from DataStructure */
Queue* getQueueByPriority(int priority) {
	return getQueues()[priority - 1];
}

/* return num tasks that exist in DataStructure */
int getNumTasks() {
	int numTasks = DataStructure->numTasks;
	return DataStructure->numTasks;
}

/* return scheduler metaData of DataStructure*/
SchedulerMetaData* getSchedulerMetaData() {
	return DataStructure->metaData;
}

void setQueues(Queue* queues) {
	DataStructure->queues = queues;
}

void setNumTasks(int numTasks) {
	DataStructure->numTasks = numTasks;
}

void setSchedulerMetaData(SchedulerMetaData* schedulerMetaData) {
	DataStructure->metaData = schedulerMetaData;
}
#pragma endregion

#pragma region Getters & Setters of SchedulerMetaData
int getCurrentQueue() {
	return getSchedulerMetaData()->currentQueue;
}

time_t getStartTimeInCurrentQueue() {
	return getSchedulerMetaData()->startTimeInCurrentQueue;
}

TaskInCpuMetaData* getTaskInCPUMetaData() {
	return getSchedulerMetaData()->taskInCPUMetaData;
}

void setCurrentQueue(int currentQueue) {
	getSchedulerMetaData()->currentQueue = currentQueue;
}

void setStartTimeInCurrentQueue(time_t startTimeInCurrentQueue) {
	getSchedulerMetaData()->startTimeInCurrentQueue = startTimeInCurrentQueue;
}

void setTaskInCPUMetaData(TaskInCpuMetaData* taskInCPUMetaData) {
	getSchedulerMetaData()->taskInCPUMetaData = taskInCPUMetaData;
}
#pragma endregion

#pragma region Getters & Setters of TaskInCpuMetaData
Task* getTaskInCPU() {
	return getTaskInCPUMetaData()->taskInCPU;
}

time_t getStartTimeOfTaskInCPU() {
	return getTaskInCPUMetaData()->startTimeOfTaskInCPU;
}

time_t getLastUpdateSize() {
	return getTaskInCPUMetaData()->lastUpdateTime;
}

double getTimeToRunInCPU() {
	double timeToRunInCPU = getTaskInCPUMetaData()->timeToRunInCPU;
	return getTaskInCPUMetaData()->timeToRunInCPU;
}

void setTaskInCPU(Task* taskInCPU) {
	getTaskInCPUMetaData()->taskInCPU = taskInCPU;
}

void setStartTimeOfTaskInCPU(time_t startTimeOfTaskInCPU) {
	getTaskInCPUMetaData()->startTimeOfTaskInCPU = startTimeOfTaskInCPU;
}

void setLastUpdateSize(time_t lastUpdateTime) {
	getTaskInCPUMetaData()->lastUpdateTime = lastUpdateTime;
}

void setTimeToRunInCPU(double timeToRunInCPU) {
	getTaskInCPUMetaData()->timeToRunInCPU = timeToRunInCPU;
}

void setTaskInCpuMetaData(Task* taskInCPU, time_t startTimeOfTaskInCPU,time_t lastUpdateTime, double timeToRunInCPU) {
	setTaskInCPU(taskInCPU);
	setStartTimeOfTaskInCPU(startTimeOfTaskInCPU);
	setLastUpdateSize(lastUpdateTime);
	setTimeToRunInCPU(timeToRunInCPU);
}
#pragma endregion

#pragma region Queues functions

/* return quantum of queue */
int getQuantumToQueue(int numQueue) {
	assert(isValidNumQueue(numQueue));
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

/* Finding a queue that is not empty by going through all the queues until finding a queue with tasks. 
   If all the queues are empty - 1- is returned. */
int findQueueNotEmpty() {
	int i = 1;
	while (i <= NUM_PRIORITIES && isQueueEmpty(getQueueByPriority(getCurrentQueue() + 1)))
	{
		nextQueue();
		i++;
	}
	int currentQueue = getCurrentQueue();
	if (isQueueEmpty(getQueueByPriority(currentQueue + 1)))
		return -1;
	return currentQueue;
}

/* set current queue to be next queue */
void nextQueue() {
	setCurrentQueue((getCurrentQueue() + 1) % 3);
	setStartTimeInCurrentQueue(time(NULL));
}

/* Quantity remaining for the current queue */
double quantityRemainingForCurrentQueue() {
	int currentQueue = getCurrentQueue();
	double maxTimeInQueue = getQuantumToQueue(currentQueue);
	double timeInCurrentQueueu = time(NULL) - getStartTimeInCurrentQueue();
	return maxTimeInQueue - timeInCurrentQueueu;
}

#pragma endregion

#pragma region Task In CPU
/* check if the task have time left to run on the cpu */
bool isLeftTimeToRunTaskInCpu() {
	time_t start = getStartTimeOfTaskInCPU();
	double timeToRun = getTimeToRunInCPU();
	time_t now = time(NULL);
	return time(NULL) - start <= timeToRun;
}
#pragma endregion

#pragma region Scheduer
void increaseNumTask() {
	DataStructure->numTasks++;
}

void decreaseNumTask() {
	DataStructure->numTasks--;
}

/* Print all task in scheduer */
void printDataStructure(){
	assert(DataStructure);
	printf("\n********SchedulerDataStructure********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(DataStructure->queues[i], printTask);
	}
}

#pragma endregion

#pragma region Validation
bool isValidQuantumTask(double time) {
	return  QUANTUM_TASK >= time;
}

bool isValidNumQueue(int numQueue) {
	return 0 <= numQueue && NUM_PRIORITIES > numQueue;
}

bool isValidSizeTask(Task* task) {
	return  MAX_SIZE_OF_TASK > getSize(task) * getTimeToByte(getPriority(task));
}

bool isRemainingTimeToCurrentQueue() {
	return quantityRemainingForCurrentQueue() > 0;
}

bool isEmptyScheduler() {
	return  0 >= getNumTasks();
}

bool isSchedulerQueuesFull() {
	return MAX_TASKS <= getNumTasks();
}
#pragma endregion


/* Scheduling a new task to run on the processor */
void nextTask() {
	assert(DataStructure);
	/* Checking that the task in the processor ran the time allotted to it */
	if (!isLeftTimeToRunTaskInCpu()) {

		/* Finding a queue in which tasks exist. 
		   If there are tasks in the current queue, 
		   the current queue will be returned */
		int currentQueue = findQueueNotEmpty();

		/* Checking whether there is a queue that has tasks */
		if (-1 != currentQueue) {

			/* Finding the time to remove tasks from the current queue */
			double remaimigTimeToQueue = quantityRemainingForCurrentQueue();

			/* Checking whether there is no time left - you need to move to the next queue */
			if (0 >= remaimigTimeToQueue) {
				nextQueue();
				currentQueue = findQueueNotEmpty();
			}

			/* Removing a task from the queue and updating the TaskInCpuMetaData*/
			Task* task = queue_dequeue(getQueueByPriority(currentQueue + 1));
			decreaseNumTask();
			double timeToRunTask = calculateRunTimeOfTask(task);
			double timeToRunInCpu = MIN(remaimigTimeToQueue, timeToRunTask);
			timeToRunInCpu = MIN(QUANTUM_TASK, timeToRunInCpu);
			setTaskInCpuMetaData(task, time(NULL), time(NULL), timeToRunInCpu);
			
			printf("\nnextTask: Task scheduling from queue %d:", currentQueue);
			printTask(task);
			printf("\n-------------\n\n");
		}
		else
			printf("\nnextTask: All queues is empty, num tasks in data structure is %d", getNumTasks());
	}
	else
	{
		printf("\nnextTask: Exist task in cpu");
	}
}

/* Adding a new task to the schedule */
void pushTask(const Task* task) {
	assert(DataStructure);
	assert(task);

	if (isSchedulerQueuesFull()) {
		printf("\n\tScheduler is full");
		return;
	}

	if (!isValidSizeTask(task)) {
		printf("\n\tSize of task not valid");
		printTask(task);
		return;
	}

	Queue* queue = getQueueByPriority(getPriority(task));
	assert(queue);
	queue_enqueue(queue, task);
	printf("\nPut task: ");
	printTask(task);
	printf("\n-------------\n\n\n");
	increaseNumTask();
}

void changeSizeOfTaskInCPU() {
	printf("\nchangeSizeOfTaskInCPU:taskId: %d, sizeTask=%f, ",getId(getTaskInCPU()), getSize(getTaskInCPU()));
	time_t start = getLastUpdateSize();
	double timeTaskRun = time(NULL) - start;
	printf("taskRunInCPU=%f, ", timeTaskRun);
	double prtitionComplete = getPortionOfTaskCompletedOnTime(getTaskInCPU(), timeTaskRun);
	printf("\t=>PartitionCompleted=%f\n", prtitionComplete);
	decreaseSizeTask(getTaskInCPU(), prtitionComplete);
	setLastUpdateSize(time(NULL));
}

void saveOrDelteTaskInCPU() {
	double sizeTask = getSize(getTaskInCPU());
	printf("\n\t\t\tsaveOrDelteTaskInCPU: sizeTask = %f", sizeTask);
	if (sizeTask > 0) {
		pushTask(getTaskInCPU());
	}
}