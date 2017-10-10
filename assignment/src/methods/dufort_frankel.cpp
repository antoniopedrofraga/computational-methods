#include "dufort_frankel.h"

DufortFrankel::DufortFrankel(Wall wall)
: Method(wall) {}

void DufortFrankel::compute_solution() {
	Matrix * grid = wall.get_grid();
	Vector t_values = wall.get_tvalues();

	unsigned int x_size = wall.get_xsize();
	unsigned int t_size = wall.get_tsize();

	double delta_t = wall.get_deltat();
	double delta_x = wall.get_deltax();

	double c = (2 * delta_t * DIFUSIVITY) / pow(delta_x, 2);
	unsigned int tvalues_size = t_values.getSize();

	Vector current_iteration(x_size + 1), temp_a(x_size + 1), temp_b(x_size + 1);

	temp_a = (*grid)[0];
	current_iteration[0] = current_iteration[x_size] = temp_b[0] = temp_b[x_size] = SURFACE_TEMPERATURE;

	for (unsigned int index = 1; index < x_size; index++) {
		current_iteration[index] = temp_a[index] - DIFUSIVITY * delta_t * (temp_a[index] - temp_a[index - 1]) / delta_x;
	}
	for (unsigned int time = 2; time < t_size + 1; time++) {
		for (unsigned int index = 1; index < x_size; index++) {
			temp_b[index] = (temp_a[index] + c * (current_iteration[index + 1] - temp_a[index] + current_iteration[index - 1])) / (1 + c);
		}
		temp_a = current_iteration;
		current_iteration = temp_b;

		for (unsigned int t = 1; t < tvalues_size; t++) {
			double time_value = double(time) * delta_t;
			if(t_values[t] == time_value) {
				grid->set_row(t, current_iteration);
			}
		}
	}
	std::cout << (*grid);
}