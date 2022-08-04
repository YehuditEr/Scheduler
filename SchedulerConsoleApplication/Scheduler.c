#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "Scheduler.h"
#include "Queue.h"

Scheduler* scheduler_init() {
	Scheduler* scheduler = calloc(1, sizeof(Scheduler));
	assert(scheduler);
	scheduler->queues = calloc(NUM_PRIORITIES, sizeof(Queue*));
	scheduler->scheduling = calloc(1, sizeof(struct Scheduling*));
	assert(scheduler->scheduling);
	scheduler->scheduling->current_queue = 1;
	scheduler->scheduling->sum_current_queue = 0;
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
	//printf("\n----enqueue_task:\n");
	//print_task(task);
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

Task* task_to_push = NULL;

double dequeue_task(Scheduler* scheduler, int num_queue, double max_time_in_queue) {

	assert(max_time_in_queue <= 10);

	Task* task = queue_dequeue(scheduler->queues[num_queue]);
	if (task == NULL)
		printf("\n\tNOT SCHEDULING TASK....\n");
	else
		printf("Task scheduler: %d", task->Id);
	/*printf("\n----dequeue_task\n");
	print_task(task);*/

	if (task == NULL)
		return 0;
	double time_task = task->size * task->typeTask->timeToByte;
	if (time_task <= max_time_in_queue) {
		scheduler->num_tasks--;
		return time_task;
		
	}
	else {
		task->size -= (max_time_in_queue / task->typeTask->timeToByte);
		task_to_push = task;
		//queue_enqueue(scheduler->queues[num_queue], task);
		return max_time_in_queue;
	}

}

void pushTaskToPush(Scheduler* scheduler) {
	if (task_to_push != NULL)
		queue_enqueue(scheduler->queues[task_to_push->typeTask->priority - 1], task_to_push);
	task_to_push = NULL;
}

void print_scheduler(const Scheduler* scheduler) {
	assert(scheduler);
	printf("\n********Scheduler********\n");
	for (size_t i = 0; i < NUM_PRIORITIES; i++) {
		printf("\nQueue %d: \n", (int)i);
		print_queue(scheduler->queues[i],print_task);
	}
}

double schedulerTasks(Scheduler* scheduler) {

	/*printf("\n----schedulerTasks\n");
	print_scheduler(scheduler);*/

	if (queue_is_empty(scheduler->queues[scheduler->scheduling->current_queue - 1])) {
		scheduler->scheduling->current_queue = (scheduler->scheduling->current_queue % 3) + 1;
		if (queue_is_empty(scheduler->queues[scheduler->scheduling->current_queue - 1])) {
			scheduler->scheduling->current_queue = (scheduler->scheduling->current_queue % 3) + 1;
			if (queue_is_empty(scheduler->queues[scheduler->scheduling->current_queue - 1])) {
				scheduler->scheduling->current_queue = (scheduler->scheduling->current_queue % 3) + 1;
				return;
			}

		}
	}
	printf("\n\tuse queue: %d\n", scheduler->scheduling->current_queue);

	if (scheduler->scheduling->sum_current_queue >= time_to_queue[scheduler->scheduling->current_queue - 1]) {
		scheduler->scheduling->sum_current_queue = 0;
		scheduler->scheduling->current_queue = (scheduler->scheduling->current_queue % 3) + 1;
	}

	int remaining_time_to_queue = time_to_queue[scheduler->scheduling->current_queue - 1] - scheduler->scheduling->sum_current_queue;
	int time_to_task = 0;
	if (remaining_time_to_queue > 10)
		time_to_task = dequeue_task(scheduler, scheduler->scheduling->current_queue - 1, 10);
	else
		time_to_task = dequeue_task(scheduler, scheduler->scheduling->current_queue - 1, remaining_time_to_queue);

	scheduler->scheduling->sum_current_queue += time_to_task;

	return time_to_task;
}

bool isFull(Scheduler* scheduer) {
	return scheduer->num_tasks == MAX_TASKS;
}

void creator_activation(double time_task,  Scheduler* scheduler) {
	time_t start = time(NULL);

	while (start + time_task > time(NULL) && !isFull(scheduler))
	{
		double milisecond = (rand() % 10)+1;
		Sleep(milisecond);
		Task* t = create_random_task();
		printf("\t%d,", t->Id);
		enqueue_task(scheduler, t);
	}
}