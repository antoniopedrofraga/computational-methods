#include "laasonen.h"

Laasonen::Laasonen(Wall wall) : Implicit(wall) {
	name = "Laasonen";
}

Vector Laasonen::build_r(Vector previous_step) {
	unsigned int size = previous_step.getSize() - 2, j = 0;
	Vector r(size);
	for (unsigned int i = 0; i < size; i++) {
		j = i + 1;
		if (i == 0) {
			r[i] = q * previous_step[j - 1] + previous_step[j];
		} else if (i == size - 1) {
			r[i] = q * previous_step[j + 1] + previous_step[j];
		} else {
			r[i] = previous_step[j];
		}
	}
	return r;
}
