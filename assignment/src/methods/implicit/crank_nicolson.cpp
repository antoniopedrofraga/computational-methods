#include "crank_nicolson.h"

CrankNicolson::CrankNicolson(Wall wall) : Implicit(wall) {
	double delta_x = wall.get_deltax();
	double delta_t = wall.get_deltat();
	this->c = 0.5 * delta_t * DIFUSIVITY / pow(delta_x, 2);
}

void CrankNicolson::compute_solution() {
	unsigned int t_size = wall.get_tsize();
	unsigned int x_size = wall.get_xsize();

	double delta_t = wall.get_deltat();

	Vector p(x_size), y(x_size - 1), t_values = wall.get_tvalues();
	Matrix * grid = wall.get_grid();

	for (int n = 0; n < t_size; n++) {
		for (int i = 0; i < x_size; i++) {
			if (i == 0) {
				y[i] = c / (1 + 2 * c);
				p[i] = c * (matrix[n + 1][i - 1] + matrix[n][i + 1] - ( -1 / c + 2) * matrix[n][i] + matrix[n][i - 1]) / (1 + 2 * c);
			} else if (i == x_size - 1) {
				p[i] = (c * (matrix[n + 1][i + 1] + matrix[n][i + 1] - ( -1 / c + 2) * matrix[n][i] + matrix[n][i - 1]) + c * p[i - 1]) / ((1 + 2 * c) + c * y[i - 1]);
			} else {
				y[i] = -c / ((1 + 2 * c) + c * y[i - 1]);
				p[i] = (c * (matrix[n][i + 1] - ( -1 / c + 2) * matrix[n][i] + matrix[n][i - 1]) + c * p[i - 1]) / ((1 + 2 * c) + c * y[i - 1]);
			}
		}
		matrix[n + 1][x_size - 1] = p[x_size - 1];
		for (int i = x_size - 1; i > 0; i--) {
			matrix[n + 1][i] = p[i] - y[i] * matrix[n + 1][i + 1];
		}
	}
	
	for (unsigned int i = 1; i < NUMBER_TIME_STEPS; i++) {
		int time = t_values[i] / delta_t;
		(*grid)[i] = matrix[time];
	}
	std::cout << (*grid);
}