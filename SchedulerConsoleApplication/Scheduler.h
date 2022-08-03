#pragma once

#include "Queue.h"
#include "Task.h"
#include "DefinationsOfSize.h"

#include <stdbool.h>

struct Scheduling {
	int current_queue;
	int sum_current_queue;
};

struct Scheduler
{
	Queue** queues;
	int num_tasks;
	struct Scheduling* scheduling;
};

static int time_to_queue[NUM_PRIORITIES] = { TIME_QUEUE1 ,TIME_QUEUE2, TIME_QUEUE3 };

typedef struct Scheduler Scheduler;

Scheduler* scheduler_init();

void scheduler_free(Scheduler* scheduler);

void enqueue_task(Scheduler* scheduler, const Task* task);

void print_scheduler(const Scheduler* scheduler);

double schedulerTasks(Scheduler* scheduler);

bool isFull(Scheduler* scheduer);

void pushTaskToPush(Scheduler* scheduler);
