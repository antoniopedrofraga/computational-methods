#include "dufort_frankel.h"

DufortFrankel::DufortFrankel(Wall wall)
: Explicit(wall) {}

void DufortFrankel::compute_solution() {
	Matrix * grid = wall.get_grid();
	Vector t_values = wall.get_tvalues();

	unsigned int x_size = wall.get_xsize();
	unsigned int t_size = wall.get_tsize();

	double delta_t = wall.get_deltat();
	double delta_x = wall.get_deltax();

	double c = (2 * delta_t * DIFUSIVITY) / pow(delta_x, 2);
	unsigned int tvalues_size = t_values.getSize();

	this->temp_a = (*grid)[0];
	this->current_iteration[0] = this->current_iteration[x_size] = this->temp_b[0] = this->temp_b[x_size] = SURFACE_TEMPERATURE;

	for (unsigned int index = 1; index < x_size; index++) {
		this->current_iteration[index] = this->temp_a[index] - DIFUSIVITY * delta_t * (this->temp_a[index] - this->temp_a[index - 1]) / delta_x;
	}
	for (unsigned int time = 2; time < t_size + 1; time++) {
		for (unsigned int index = 1; index < x_size; index++) {
			this->temp_b[index] = (this->temp_a[index] + c * (this->current_iteration[index + 1] - this->temp_a[index] + this->current_iteration[index - 1])) / (1 + c);
		}
		this->temp_a = this->current_iteration;
		this->current_iteration = this->temp_b;

		for (unsigned int t = 1; t < tvalues_size; t++) {
			double time_value = double(time) * delta_t;
			if(t_values[t] == time_value) {
				grid->set_row(t, this->current_iteration);
			}
		}
	}
	std::cout << (*grid);
}