#include "laasonen.h"

Laasonen::Laasonen(Problem problem) : Implicit(problem) {
	name = "Laasonen";
}

Vector Laasonen::build_r(Vector previous_step) {
	unsigned int size = previous_step.getSize() - 2, j = 0;
	Vector r(size);
	for (unsigned int i = 0; i < size; i++) {
		j = i + 1;
		r[i] = (i == 0 || i == size - 1) ? q * SURFACE_TEMPERATURE + previous_step[j] : previous_step[j];
	}
	return r;
}
