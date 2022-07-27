#include "TypeTask.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

TypeTask* type_init() {
	TypeTask* type = calloc(1, sizeof(TypeTask));
	assert(type);
	return type;
}

void print_type(const TypeTask* type) {
	printf("type{ name: %s, priority:%d, time-to-byte: %f }",
		type->name, type->priority, type->timeToByte);
}
