#pragma once

#include "Queue.h"
#include "Task.h"

#define NUM_PRIORITIES 3
#define MAX_TASKS 8
#define MAX_SIZE_OF_TASK 20

struct Scheduler
{
	Queue** queues;
	int num_tasks;

};

typedef struct Scheduler Scheduler;

Scheduler* scheduler_init();

void scheduler_free(Scheduler* scheduler);

void enqueue_task(Scheduler* scheduler, const Task* task);

//Task* dequeue_task(Scheduler* scheduler);

void print_scheduler(const Scheduler* scheduler);

void timer_task(int time);

