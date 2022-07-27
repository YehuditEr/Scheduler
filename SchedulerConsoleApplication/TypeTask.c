#include "TypeTask.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void type_free(TypeTask* type) {
	assert(type);
	free(type->name);
	free(type);
}

TypeTask* type_init() {
	TypeTask* type = calloc(1, sizeof(TypeTask));
	assert(type);
	return type;
}

void type_init_values(TypeTask* type, int priority, char* name, double timeToByte) {
	assert(type);
	type->priority = priority;
	type->name = name;
	type->timeToByte = timeToByte;
}

void print_type(const TypeTask* type) {
	printf("type{ name: %s, priority:%d, time-to-byte: %f }",
		type->name, type->priority, type->timeToByte);
}
