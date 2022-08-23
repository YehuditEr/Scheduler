//#include <time.h>
//
//#include "Scheduler.h"
//
//#define MAX_PUSH_TASK 100
//
//void tst_random();
//
//
//void init() {
//	initDataStructure();
//	initPriorities();
//}
//
//int main() {
//	init();
//	tst_random();
//}
//
//
//
////void dif() {
////	Task* t = createRandomTask();
////	pushTask(t);
////	nextTask();
////	clock_t start = clock();
////	while (1)
////	{
////		if (isLeftTimeToRunTaskInCpu()) {
////			if (!isSchedulerQueuesFull()) {
////				t = createRandomTask();
////				pushTask(t);
////			}
////		}
////		else {
////			saveOrDelteTaskInCPU();
////			clock_t end = clock();
////			printf("\n**********task run in cpu: %f", ((double)end - (double)start) / CLOCKS_PER_SEC);
////			nextTask();
////			start = clock();
////		}
////		printf("\n-------------------------------------------------------\n");
////		changeSizeOfTaskInCPU();
////	}
////}
//
//
////#pragma region Tests
////
////#pragma region Data Structure To check test
////
////struct TaskRunMetaData
////{
////	clock_t entryTime;
////	clock_t leaveTime;
////	int numTimesInCpu;
////	double totalRunningTimeInCpu;
////	Task* orginalTask;
////	Task* updateTask;
////};
////
////typedef struct TaskRunMetaData TaskRunMetaData;
////
////
////struct TestDataStructure
////{
////	int numTasksPush;
////	TaskRunMetaData* tasksRunMetaData[MAX_PUSH_TASK];
////};
////
////typedef struct TestDataStructure TestDataStructure;
////
////
////TestDataStructure* testDataStructure;
////
////void initTestDataStructure() {
////	testDataStructure = calloc(1, sizeof(TestDataStructure*));
////	testDataStructure->numTasksPush = 0;
////	initTaskRunMetaData();
////}
////
////void initTaskRunMetaData() {
////	for (size_t i = 0; i < MAX_PUSH_TASK; i++) {
////		testDataStructure->tasksRunMetaData[i] = calloc(1, sizeof(TaskRunMetaData*));
////		assert(testDataStructure->tasksRunMetaData[i]);
////		testDataStructure->tasksRunMetaData[i]->numTimesInCpu = 0;
////		testDataStructure->tasksRunMetaData[i]->totalRunningTimeInCpu = 0;
////		testDataStructure->tasksRunMetaData[i]->orginalTask = dynamicAllocationTask();
////		testDataStructure->tasksRunMetaData[i]->updateTask = dynamicAllocationTask();
////	}
////}
////
////void initTaskValues(Task* t) {
////	//assert(tasksRunMetaData[getId(t)]);
////	//tasksRunMetaData[getId(t)]->orginalTask = copyTask(t);
////	//tasksRunMetaData[getId(t)]->updateTask = t;
////	//tasksRunMetaData[getId(t)]->entryTime = clock();
////	//tasksRunMetaData[getId(t)]->numTimesInCpu = 0;
////}
////
////void updateTaskValues(Task* t, clock_t start) {
////	int id = getId(getTaskInCPU());
////	//assert(tasksRunMetaData[id]);
////	//tasksRunMetaData[id]->numTimesInCpu++;
////	//tasksRunMetaData[id]->totalRunningTimeInCpu += (((double)clock() - (double)start) / CLOCKS_PER_SEC);
////	//tasksRunMetaData[id]->leaveTime = clock();
////}
////
////void addRandomTask() {
////	Task* t = createRandomTask();
////	pushTask(t);
////	initTaskValues(t);
////}
////
////#pragma region Timer
////clock_t start;
////
////void stratTimer() {
////	start = clock();
////}
////
////#pragma endregion
////
////
////#pragma endregion
////
////void tst_random() {
////
////	initTaskRunMetaData();
////
////	addRandomTask();
////
////	nextTask();
////
////	stratTimer();
////
////	int i = 0;
////
////	while ((i < MAX_PUSH_TASK || getNumTasks() > 0 || i == 0) && getTaskInCPU() != NULL)
////	{
////		if (isLeftTimeToRunTaskInCpu()) {
////			if (!isSchedulerQueuesFull() && MAX_PUSH_TASK - 1 > i) {
////				int push = rand() % 2 + 1;
////				if (push == 1) {
////					addRandomTask();
////					i++;
////				}
////			}
////		}
////		else {
////			changeSizeOfTaskInCPU();
////			saveOrDelteTaskInCPU();
////			/*updateTaskValues(t, start);*/
////			nextTask();
////			start = clock();
////		}
////		printf("\n-------------------------------------------------------\n");
////	}
////
////	for (size_t i = 0; i < MAX_PUSH_TASK; i++)
////	{
////		/*assert(tasksRunMetaData[i]);
////		printTask(tasksRunMetaData[getId(t)]->orginalTask);
////		printTask(tasksRunMetaData[getId(t)]->updateTask);
////		printf("\nTask %d was in cpu %d times during %f", (int)i, tasksRunMetaData[i]->numTimesInCpu, tasksRunMetaData[i]->totalRunningTimeInCpu);
////		printf("\ncheck timeOut: entryTime=%d, leaveTime=%d, timeOut-of-task=%d, current-timeOut=%d\n\n",
////			tasksRunMetaData[i]->entryTime, tasksRunMetaData[i]->leaveTime, getTimeOut(getPriority(tasksRunMetaData[getId(t)]->orginalTask), (tasksRunMetaData[i]->leaveTime - tasksRunMetaData[i]->entryTime) / CLOCKS_PER_SEC));*/
////	}
////	printDataStructure();
////}
////
////
////#pragma endregion
//
