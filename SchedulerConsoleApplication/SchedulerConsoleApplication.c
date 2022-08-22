#include <time.h>

#include "Scheduler.h"

void init() {
	initDataStructure();
	initPriorities();
}

int main() {
	init();
	Task* t = createRandomTask();
	pushTask(t);
	nextTask();
	clock_t start = clock();
	while (1)
	{
		if (isLeftTimeToRunTaskInCpu()) {
			if(!isSchedulerQueuesFull()){
				t = createRandomTask();
				pushTask(t);
			}
		}
		else {
			saveOrDelteTaskInCPU();
			clock_t end = clock();
			printf("\n**********task run in cpu: %f", ((double)end - (double)start) / CLOCKS_PER_SEC);
			nextTask();
			start = clock();
		}
		printf("\n-------------------------------------------------------\n");
		changeSizeOfTaskInCPU();
	}
}