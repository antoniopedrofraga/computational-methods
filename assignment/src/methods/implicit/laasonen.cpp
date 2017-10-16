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

	Vector p(x_size - 1), y(x_size - 2), t_values = wall.get_tvalues();
	Matrix * grid = wall.get_grid();

	for (int n = 0; n < t_size; n++) {
		for (int i = 1; i < x_size; i++) {
			int j = i - 1;
			if (i == 1) {
				y[j] = -c / (1 + 2 * c);
				p[j] = (matrix[n][i] + c * matrix[n][i - 1]) / (1 + 2 * c);
			} else if (i == x_size - 1) {
				p[j] = (matrix[n][i + 1] + c * matrix[n][i] + c * p[j - 1]) / ((1 + 2 * c) + c * y[j - 1]);
			} else {
				y[j] = -c / ((1 + 2 * c) + c * y[j - 1]);
				p[j] = (matrix[n][i] + c * p[j - 1]) / ((1 + 2 * c) + c * y[j - 1]);
			}
		}
		matrix[n + 1][x_size - 1] = p[x_size - 2];
		for (int i = x_size - 2; i > 0; i--) {
			int j = i - 1;
			matrix[n + 1][i] = p[j] - y[j] * matrix[n + 1][i + 1];
		}
	}

	for (unsigned int i = 1; i < NUMBER_TIME_STEPS; i++) {
		int time = t_values[i] / delta_t;
		(*grid)[i] = matrix[time];
	}
}