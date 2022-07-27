#include "Task.h"
#include "TypeTask.h"
#include "Scheduler.h"

int main()
{
	TypeTask* type1 = task_init();
	type1->name = "1";
	type1->priority = 1;
	type1->timeToByte = 1;

	TypeTask* type2 = task_init();
	type2->name = "2";
	type2->priority = 2;
	type2->timeToByte = 2;

	TypeTask* type3 = task_init();
	type3->name = "3";
	type3->priority = 3;
	type3->timeToByte = 3;

	Scheduler* scheduler = scheduler_init();
	
	Task* task1 = task_init();
	task1->size = 1;
	task1->timeOut = 1;
	task1->typeTask = type1;
	enqueue_task(scheduler, task1);

	Task* task2 = task_init();
	task2->size = 2;
	task2->timeOut = 2;
	task2->typeTask = type2;
	enqueue_task(scheduler, task2);

	Task* task3 = task_init();
	task3->size = 3;
	task3->timeOut = 3;
	task3->typeTask = type3;
	enqueue_task(scheduler, task3);

	Task* task11 = task_init();
	task11->size = 11;
	task11->timeOut = 11;
	task11->typeTask = type1;
	enqueue_task(scheduler, task11);

	Task* task22 = task_init();
	task22->size = 22;
	task22->timeOut = 22;
	task22->typeTask = type2;
	enqueue_task(scheduler, task22);

	Task* task33 = task_init();
	task33->size = 3.3;
	task33->timeOut = 33;
	task33->typeTask = type3;
	enqueue_task(scheduler, task33);

	Task* task111 = task_init();
	task111->size = 1.11;
	task111->timeOut = 111;
	task111->typeTask = type1;
	enqueue_task(scheduler, task111);

	Task* task222 = task_init();
	task222->size = 2.22;
	task222->timeOut = 222;
	task222->typeTask = type2;
	enqueue_task(scheduler, task222);

	Task* task333 = task_init();
	task333->size = 3.33;
	task333->timeOut = 333;
	task333->typeTask = type3;
	enqueue_task(scheduler, task333);

	Task* task3333 = task_init();
	task3333->size = 333;
	task3333->timeOut = 3333;
	task3333->typeTask = type3;
	enqueue_task(scheduler, task3333);

	print_scheduler(scheduler);
}