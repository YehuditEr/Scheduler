#include "Task.h"
#include "TypeTask.h"
#include "Scheduler.h"

#include <time.h>


int main() {

	//TypeTask* type = getTypeTaskByPriority(1);
	//printf("priority: %d\n", getPriority(type));
	//printf("name: %s\n", getName(type));
	//printf("time to byte: %f\n", getTimeToByte(type));

	//Task* task1 = createTask(1, 2);
	//printTask(task1);
	//Task* task2 = createTask(2, 2);
	//printTask(task2);
	//Task* task3 = createTask(3, 2);
	//printTask(task3);
	//Task* task4 = createRandomTask();
	//printTask(task4);
	//Task* task5 = createTask(4, 2);
	//printTask(task5);

	Scheduler* scheduler = initScheduler();

	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());


	int time_task;

	printf("\n\tBedore scheduler use queue %d\n", scheduler->scheduling->currentQueue);
	printScheduler(scheduler);

	while (1)
	{
		time_task = schedulerTasks(scheduler);
		time_t start = time(NULL);
		printf("\n\n\n");
		tasksCreatorActivation(scheduler, time_task);
		printf("\n\n\n");
		removingCPU_PuttingScheduler(scheduler);
		printScheduler(scheduler);
		//while (start + time_task > time(NULL));
	}

}