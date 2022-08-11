#pragma once

#include "Queue.h"
#include "Task.h"
#include "DefinationsOfSize.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

/// <summary>
/// Saves the timing state between queues:
///   currentQueue - The queue number from which to schedule.
///   timeInCurrentQueue - The time this queue is scheduled.
///   taskInCPU - The task that is in the CPU.
/// </summary>
struct Scheduling {
	int currentQueue;
	double timeInCurrentQueue;
	Task* taskInCPU;
};

typedef struct Scheduling Scheduling;

/// <summary>
/// Saving all task to scheduler:
///    queues - An array of queues, a queue for each priority
///    numTasks - Number of task that exist in all queues together
///    scheduling - Managing the scheduler between queues as explained above
/// </summary>
struct Scheduler
{
	Queue** queues;
	int numTasks;
	struct Scheduling* scheduling;
};

typedef struct Scheduler Scheduler;

/// <summary>
/// Dynamic initialization and allocation for the Scheduler
/// </summary>
/// <returns>Pointer to Scheduler</returns>
Scheduler* initScheduler();

/// <summary>
/// Freeing dynamically allocated memory of Scheduler
/// </summary>
/// <param name="scheduler">- Pointer to scheduler</param>
void freeScheduler(Scheduler* scheduler);

/// <summary>
/// Scheduler the task to run in CPU
/// </summary>
/// <param name="scheduler">-Pointer to scheduler</param>
/// <returns>Time the task is in the CPU</returns>
double schedulerTasks(Scheduler* scheduler);

/// <summary>
/// Print all task in scheduer
/// </summary>
/// <param name="scheduler">-Pointer to scheduer</param>
void printScheduler(const Scheduler* scheduler);

/// <summary>
/// Removing the task from the CPU and inserting it into the Scheduler
/// </summary>
/// <param name="scheduler">Pointer to scheduler</param>
void removingCPU_PuttingScheduler(Scheduler* scheduler);

/// <summary>
/// Check if scheduler full
/// </summary>
/// <param name="scheduler">Pointer to scheduler</param>
bool isSchedulerFull(Scheduler* scheduer);

/// <summary>
/// Enter new task to scheduler
/// </summary>
/// <param name="scheduler">Pointer to scheduler</param>
/// <param name="task">Pointer to task</param>
void putTask(Scheduler* scheduler, const Task* task);