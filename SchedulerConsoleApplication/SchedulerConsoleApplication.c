#include "Task.h"
#include "TypeTask.h"
#include "Scheduler.h"

int main()
{
	Scheduler* scheduler2 = scheduler_init();
	for (size_t i = 0; i < 10; i++)
	{
		enqueue_task(scheduler2, create_random_task());
	}

	print_scheduler(scheduler2);
	free(scheduler2);


}