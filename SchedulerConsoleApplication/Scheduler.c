#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "Scheduler.h"
#include "Queue.h"

Scheduler* scheduler_init() {
	Scheduler* scheduler = calloc(1, sizeof(Scheduler));
	assert(scheduler);
	scheduler->queues = calloc(NUM_PRIORITIES, sizeof(Queue*));
	assert(scheduler->queues);
	scheduler->num_tasks = 0;
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		scheduler->queues[i] = queue_init();
	return scheduler;
}

void scheduler_free(Scheduler* scheduler) {
	assert(scheduler);
	for (size_t i = 0; i < NUM_PRIORITIES; i++)
		queue_free(scheduler->queues[i]);
}

void enqueue_task(Scheduler* scheduler, const Task* task) {
	assert(scheduler);
	assert(task);
	//assert(scheduler->num_tasks < MAX_TASKS);
	if (scheduler->num_tasks >= MAX_TASKS) {
		printf("\nThe scheduler full!!\n");
		return;
	}

	if (task->size * task->typeTask->timeToByte > MAX_SIZE_OF_TASK) {
		printf("This is too big a task!!!");
		return;
	}

	Queue* queue_of_priority = scheduler->queues[task->typeTask->priority-1];
	queue_enqueue(queue_of_priority, task);
	scheduler->num_tasks++;
}

void print_scheduler(const Scheduler* scheduler) {
	assert(scheduler);
	printf("\n********Scheduler********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(scheduler->queues[i],print_task);
	}
}

void timer_task(int time) {
	clock_t msec = clock();
	while (clock() - msec < time);
}

void dequeue_task(Scheduler* scheduler, int num_queue) {
	Task* task = queue_dequeue(scheduler->queues[num_queue]);
	double time_task = task->size * task->typeTask->timeToByte;
	if (time_task <= 10)
		timer_task(time_task);
	else {
		timer_task(10);
		task->size -= (10 / task->typeTask->timeToByte);
		queue_enqueue(scheduler->queues[num_queue], task);
	}
}
