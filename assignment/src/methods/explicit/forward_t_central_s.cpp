#include "forward_t_central_s.h"

FTCS::FTCS(Problem problem)
: Explicit(problem) {
	name = "Forward time Central space";
}

Vector FTCS::build_iteration(Vector current_step, Vector previous_step) {
	unsigned int size = previous_step.getSize();
	Vector result(size);
	result[0] = result[size - 1] = SURFACE_TEMPERATURE;
	for (unsigned int i = 1; i < size - 1; i++) {
		result[i] = previous_step[i] + q / 2.0 * (previous_step[i + 1] - 2.0 * previous_step[i] + previous_step[i - 1]);
	}
	return result;
}