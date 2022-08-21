#pragma once

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Task.h"
#include "Queue.h"
#include "Definitions.h"

/// <summary>
/// Data about the task on the processor
///		taskInCPU - A task that runs on the CPU.
///		startTimeOfTaskInCPU - Time when the task started in the CPU.
///		lastUpdateSize - to update size of task
///		timeToRunInCPU - Quntum of the task to be run on the CPU
/// </summary>
struct TaskInCpuMetaData
{
	Task* taskInCPU;
	time_t startTimeOfTaskInCPU;
	time_t lastUpdateSize;
	double timeToRunInCPU;
};

typedef struct TaskInCpuMetaData TaskInCpuMetaData;


/// <summary>
/// Saves the timing state between queues:
///   currentQueue - The queue number from which to schedule.
///   startTimeInCurrentQueue - Start time for this queue.
/// </summary>
struct SchedulerMetaData {
	int currentQueue;
	time_t startTimeInCurrentQueue;
	TaskInCpuMetaData* taskInCPUMetaData;
};

typedef struct SchedulerMetaData SchedulerMetaData;


/// <summary>
/// Saving all task to scheduler:
///    queues - An array of queues, a queue for each priority
///    numTasks - Number of task that exist in all queues together
///    mtaData - Managing the scheduler between queues as explained above
/// </summary>
struct SchedulerDataStructure
{
	Queue** queues;
	int numTasks;
	struct SchedulerMetaData* metaData;
};

typedef struct SchedulerDataStructure SchedulerDataStructure;



/// <summary>
/// Dynamic initialization and allocation for the DataStructure
/// </summary>
/// <returns>Pointer to SchedulerDataStructure</returns>
void initDataStructure();

/// <summary>
/// Freeing dynamically allocated memory of SchedulerDataStructure
/// </summary>
void freeDataStructure();

bool isSchedulerFull();

/// <summary>
/// find next task to run in CPU
/// </summary>
/// <returns>Time the task is in the CPU</returns>
void nextTask();

void changeSizeOfTaskInCPU();
void saveOrDelteTaskInCPU();


/// <summary>
/// Print all task in DataStructure
/// </summary>
void printDataStructure();


/// <summary>
/// Removing the task from the CPU and inserting it into the SchedulerDataStructure
/// </summary>
void TerminationTaskRunInCpu();


/// <summary>
/// Check if DataStructure full
/// </summary>
bool isDataStructutreFull();


/// <summary>
/// Insert new task to DataStructure
/// </summary>
/// <param name="task">Pointer to task</param>
void putTask(const Task* task);
bool isLeftTimeToTaskInCpu();