#include "implicit.h"

Implicit::Implicit(Wall wall) : Method(wall) {
	unsigned int x_size = wall.get_xsize() + 1;
	unsigned int t_size = wall.get_tsize() + 1;

	this->matrix = Matrix(t_size, x_size);
	set_initial_conditions(x_size - 1, t_size - 1);
}

void Implicit::set_initial_conditions(unsigned int x_size, unsigned int t_size) {
	for (unsigned int space = 1; space < x_size; space++) {
		this->matrix[0][space] = INITIAL_TEMPERATURE;
	}
	for (unsigned int time = 0; time <= t_size; time++) {
		this->matrix[time][0] = this->matrix[time][x_size] = SURFACE_TEMPERATURE;
	}
}