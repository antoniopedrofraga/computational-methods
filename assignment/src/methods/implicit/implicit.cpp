#include "implicit.h"

Implicit::Implicit(Wall wall) : Method(wall) {
	double delta_t = wall.get_deltat(), delta_x = wall.get_deltax();
	q = delta_t * DIFUSIVITY / pow(delta_x, 2);
}

void Implicit::compute_solution() {
	Vector previous_step, current_step, r, t_values = wall.get_tvalues();
	unsigned int t_size = wall.get_tsize();
	double delta_t = wall.get_deltat(), time;

	for (unsigned int i = 1; i <= t_size; i++) {
		if (i == 1) { previous_step = wall.get_first_row(); }
		r = build_r(previous_step);
		current_step = thomas_algorithm(r, -q, (1.0 + 2.0 * q), -q);
		current_step.push_front_back(SURFACE_TEMPERATURE);
		previous_step = current_step;
		time = delta_t * (double)i;
		wall.set_time_step(current_step, time);
	}
}

Vector Implicit::thomas_algorithm(Vector r, double a, double b, double c) {
	unsigned int size = r.getSize();
	Vector p(size), y(size - 1), x(size);
	for (unsigned int i = 0; i < size; i++) {
		if (i == 0) {
			y[i] = c / b;
			p[i] = r[i] / b;
		} else if (i == size - 1) {
			p[i] = (r[i] - a * p[i - 1]) / (b - a * y[i - 1]);
		} else {
			y[i] = c / (b - a * y[i - 1]);
			p[i] = (r[i] - a * p[i - 1]) / (b - a * y[i - 1]);
		}
	}
	x[size - 1] = p[size - 1];
	for (int i = size - 2; i >= 0; i--) {
		x[i] = p[i] - y[i] * x[i + 1];
	}
	return x;
}
