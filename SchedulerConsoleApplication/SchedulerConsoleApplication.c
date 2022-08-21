#include <time.h>

#include "Scheduler.h"

void init() {
	initDataStructure();
	initPriorities();
}

int main() {
	init();
	Task* t = createRandomTask();
	putTask(t);
	nextTask();
	while (1)
	{
		if (isLeftTimeToTaskInCpu()) {
			changeSizeOfTaskInCPU();
			if(!isSchedulerFull()){
				t = createRandomTask();
				putTask(t);
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