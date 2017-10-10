#include "analytical.h"

Analytical::Analytical(Wall wall)
: Method(wall) {
	this->nr_of_expansions = NUMBER_OF_EXPANSIONS;
}

void Analytical::compute_solution() {
	Matrix * grid = wall.get_grid();
	Vector t_values = wall.get_tvalues();
	Vector x_values = wall.get_xvalues();

	for (unsigned int t = 1; t < NUMBER_TIME_STEPS; t++) {
		for (unsigned int x = 1; x < wall.get_xsize(); x++) {
			double sum = 0.0;
			for (unsigned int m = 1; m <= this->nr_of_expansions; m++) {
				sum = exp(-DIFUSIVITY * pow(m * PI / THICKNESS, 2) * t_values[t]) * (1 - pow(-1, m)) / (m * PI) * sin(m * PI * x_values[x] / THICKNESS);
			}
			(*grid)[t][x] = SURFACE_TEMPERATURE + 2 * (INITIAL_TEMPERATURE - SURFACE_TEMPERATURE) * sum;
		}
	}
}

