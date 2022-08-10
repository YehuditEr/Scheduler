#pragma once

#include "Queue.h"
#include "Task.h"
#include "DefinationsOfSize.h"

#include <stdbool.h>

/// <summary>
/// Saves the timing state between queues
/// </summary>
struct Scheduling {
	int currentQueue;
	int timeInCurrentQueue;
	Task* taskInCPU;
};

typedef struct Scheduling Scheduling;

struct Scheduler
{
	Queue** queues;
	int numTasks;
	struct Scheduling* scheduling;
};

typedef struct Scheduler Scheduler;

static int time_to_queue[NUM_PRIORITIES] = { QUANTUM_QUEUE1 ,QUANTUM_QUEUE2, QUANTUM_QUEUE3 };

Scheduler* initScheduler();

void freeScheduler(Scheduler* scheduler);

void putTask(Scheduler* scheduler, const Task* task);

void printScheduler(const Scheduler* scheduler);

double schedulerTasks(Scheduler* scheduler);

bool isFull(Scheduler* scheduer);

void removingCPU_PuttingScheduler(Scheduler* scheduler);

inline void tasksCreatorActivation( Scheduler* scheduler,double time_task);