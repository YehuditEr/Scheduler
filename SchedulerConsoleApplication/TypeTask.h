#pragma once

struct TypeTask {
	int priority;
	char* name;
	double timeToByte;
};

typedef struct TypeTask TypeTask;

TypeTask* type_init();

void type_free(TypeTask* type);

void type_init_values(TypeTask* type, int priority, char* name, double timeToByte);

void print_type(const TypeTask* type);