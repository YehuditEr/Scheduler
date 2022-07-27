#pragma once

#include "Queue.h"
#include "Task.h"

struct Scheduler
{
	Queue** queues;
	int num_tasks;
};

typedef struct Scheduler Scheduler;

Scheduler* scheduler_init();

void enqueue_task(Scheduler* scheduler, const Task* task);

void print_scheduler(const Scheduler* scheduler);

