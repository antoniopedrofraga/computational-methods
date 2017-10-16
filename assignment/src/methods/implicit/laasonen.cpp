#include "laasonen.h"

Laasonen::Laasonen(Wall wall) : Implicit(wall) {
	name = "Laasonen";
	double delta_x = wall.get_deltax();
	double delta_t = wall.get_deltat();
	this->c = delta_t * DIFUSIVITY / pow(delta_x, 2);
}

void Laasonen::compute_solution() {
	unsigned int t_size = wall.get_tsize();
	unsigned int x_size = wall.get_xsize();

	double delta_t = wall.get_deltat();

	Vector t_values = wall.get_tvalues();
	Matrix * grid = wall.get_grid();

	for (int n = 1; n <= t_size; n++) {
		Vector p(x_size), y(x_size - 1);
		for (int i = 1; i < x_size; i++) {
			if (i == 1) {
				y[i] = -c / (1.0 + 2.0 * c);
				p[i] = (matrix[n][i + 1] + c * matrix[n][i]) / (1.0 + 2.0 * c);
			} else if (i == x_size - 1) {
				p[i] = (matrix[n][i + 1] + c * matrix[n][i] - (-c) * p[i - 1]) / ((1.0 + 2.0 * c) - (-c) * y[i - 1]);
			} else {
				y[i] = -c / ((1.0 + 2.0 * c) - (-c) * y[i - 1]);
				p[i] = (matrix[n][i] - (-c) * p[i - 1]) / ((1.0 + 2.0 * c) - (-c) * y[i - 1]);
			}
		}
		matrix[n + 1][x_size - 1] = p[x_size - 1];
		for (int i = x_size - 2; i > 0; i--) {
			matrix[n + 1][i] = p[i] - y[i] * matrix[n + 1][i + 1];
		}
	}

	for (unsigned int i = 1; i < NUMBER_TIME_STEPS; i++) {
		int time = t_values[i] / delta_t;
		(*grid)[i] = matrix[time];
	}
}