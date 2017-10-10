#include "analytical.h"

Analytical::Analytical(Wall wall)
: Method(wall) {
	this->nr_of_expansions = NUMBER_OF_EXPANSIONS;
}

void Analytical::compute_solution() {
	Matrix * grid = wall.get_grid();
	Vector t_values = wall.get_tvalues();
	Vector x_values = wall.get_xvalues();
	unsigned int x_size = wall.get_xsize();

	for (unsigned int t = 0; t < NUMBER_TIME_STEPS; t++) {
		for (unsigned int x = 0; x <= x_size; x++) {
			double sum = 0.0;
			for (unsigned int m = 1; m <= this->nr_of_expansions; m++) {
				double m_double = (double)m;
				sum += exp(-DIFUSIVITY * pow(m_double * PI / THICKNESS, 2) * t_values[t]) * (1 - pow(-1, m_double)) / (m_double * PI) * sin(m_double * PI * x_values[x] / THICKNESS);
			}
			(*grid)[t][x] = SURFACE_TEMPERATURE + 2.0 * (INITIAL_TEMPERATURE - SURFACE_TEMPERATURE) * sum;
		}
	}
	std::cout << (*grid);
}

