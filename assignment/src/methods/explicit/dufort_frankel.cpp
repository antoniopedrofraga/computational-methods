#include "dufort_frankel.h"

DufortFrankel::DufortFrankel(Problem problem)
: Explicit(problem) {
	name = "DuFort-Frankel";
}

Vector DufortFrankel::build_iteration(Vector current_step, Vector previous_step) {
	unsigned int size = previous_step.getSize();
	Vector result(size);
	result[0] = result[size - 1] = SURFACE_TEMPERATURE;
	for (unsigned int i = 1; i < size - 1; i++) {
			result[i] = ((1.0 - q) * previous_step[i] + q * (current_step[i + 1] + current_step[i - 1])) / (1.0 + q);
	}
	return result;
}