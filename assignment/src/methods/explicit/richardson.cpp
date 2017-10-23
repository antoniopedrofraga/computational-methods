#include "richardson.h"

Richardson::Richardson(Problem problem)
: Explicit(problem) {
	name = "Richardson";
}

Vector Richardson::build_iteration(Vector current_step, Vector previous_step) {
	unsigned int size = previous_step.getSize();
	Vector result(size);
	result[0] = result[size - 1] = SURFACE_TEMPERATURE;
	for (unsigned int i = 1; i < size - 1; i++) {
			result[i] = previous_step[i] + q * (current_step[i + 1] - 2.0 * current_step[i] + current_step[i - 1]);
	}
	return result;
}