#include "Task.h"
#include "Priority.h"
#include "Scheduler.h"

#include <time.h>


int main() {
	initPriorities(NUM_PRIORITIES);

	Scheduler* scheduler = initScheduler();

	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());
	putTask(scheduler, createRandomTask());


	int time_task;

	printScheduler(scheduler);

	while (1)
	{
		time_task = schedulerTasks(scheduler);
		time_t start = time(NULL);
		printf("\n\n\n");
		while (start+time_task > time(NULL) && !isSchedulerFull(scheduler))
		{
			Task* t = createRandomTask();
			putTask(scheduler, t);
		}
		printf("\n\n\n");
		removingCPU_PuttingScheduler(scheduler);
		printScheduler(scheduler);
		//while (start + time_task > time(NULL));
	}

}