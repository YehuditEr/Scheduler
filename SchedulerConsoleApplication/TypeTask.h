#pragma once

struct TypeTask {
	int priority;
	char* name;
	double timeToByte;
};

typedef struct TypeTask TypeTask;

TypeTask* type_init();

void print_type(const TypeTask* type);