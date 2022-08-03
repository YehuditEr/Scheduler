#include "Task.h"
#include "TypeTask.h"
#include "Scheduler.h"

#include <time.h>


int main() {

	Scheduler* scheduler = scheduler_init();

	enqueue_task(scheduler, create_random_task());
	enqueue_task(scheduler, create_random_task());
	enqueue_task(scheduler, create_random_task());
	enqueue_task(scheduler, create_random_task());
	enqueue_task(scheduler, create_random_task());


	int time_task;

	printf("\n\tBedore scheduler use queue %d\n", scheduler->scheduling->current_queue);
	print_scheduler(scheduler);

	while (1)
	{
		time_task = schedulerTasks(scheduler);
		time_t start = time(NULL);
		printf("\n\n\n");
		while (start+time_task > time(NULL) && !isFull(scheduler))
		{
			Task* t = create_random_task();
			printf("\t%d,", t->Id);
			enqueue_task(scheduler, t);
		}
		printf("\n\n\n");
		pushTaskToPush(scheduler);
		print_scheduler(scheduler);
		//while (start + time_task > time(NULL));
	}

}