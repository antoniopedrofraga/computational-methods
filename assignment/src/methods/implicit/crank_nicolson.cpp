#include "crank_nicolson.h"

CrankNicolson::CrankNicolson(Problem problem) : Implicit(problem) {
	name = "Crank-Nicholson";
	q *= 0.5;
}

Vector CrankNicolson::build_r(Vector previous_step) {
	unsigned int size = previous_step.getSize() - 2, j = 0;
	Vector r(size);
	for (unsigned int i = 0; i < size; i++) {
		j = i + 1;
		r[i] = (i == 0 || i == size - 1) ? previous_step[j] + q * (SURFACE_TEMPERATURE + previous_step[j - 1] - 2.0 * previous_step[j] + previous_step[j + 1])
		: previous_step[j] + q * (previous_step[j - 1] - 2.0 * previous_step[j] + previous_step[j + 1]);
	}
	return r;
}
