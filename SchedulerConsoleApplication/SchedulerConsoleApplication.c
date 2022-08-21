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
	while (1)
	{
		if (isLeftTimeToRunTaskInCpu()) {
			changeSizeOfTaskInCPU();
			if(!isSchedulerQueuesFull()){
				t = createRandomTask();
				pushTask(t);
			}
			else {
				printf("");
			}
		}
		else {
			saveOrDelteTaskInCPU();
			nextTask();
		}
	}
}