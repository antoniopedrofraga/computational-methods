#include "wall.h"

Wall::Wall() {}

Wall::Wall(double dt, double dx) {
	if (dx <= 0) throw std::out_of_range("space step can't be negative.");
	if (dt <= 0) throw std::out_of_range("time step can't be negative.");

	delta_x = dx;
	delta_t = dt;

	x_size = (int)(THICKNESS / delta_x);
	t_size = (int)(TIMELIMIT / delta_t);
	grid = Matrix(NUMBER_TIME_STEPS, x_size + 1);
	set_x_values();
	set_t_values();
	set_initial_conditions();
}

void Wall::set_x_values() {
	x_values = Vector(x_size + 1);
	for (unsigned int index = 0; index <= x_size; index++) {
		x_values[index] = delta_x * index;
	}
}

void Wall::set_t_values() {
	t_values = Vector(NUMBER_TIME_STEPS);
	for (unsigned int time = 0; time < NUMBER_TIME_STEPS; time++) {
		t_values[time] = double(time) / 10.0;
	}
}

void Wall::set_initial_conditions() {
	for (unsigned int index = 1; index < x_size; index++) {
		grid[0][index] = INITIAL_TEMPERATURE;
	}
	for (unsigned int time = 0; time < NUMBER_TIME_STEPS; time++) {
		grid[time][0] = grid[time][x_size] = SURFACE_TEMPERATURE;
	}
}

void Wall::set_time_step(Vector step, double time) {
	int position = t_values.find(time);
	if (position != -1) {
		grid.set_row(position, step);
	}
}

Vector Wall::get_first_row() {
	return grid[0];
}

unsigned int Wall::get_xsize() {
	return x_size;
}

unsigned int Wall::get_tsize() {
	return t_size;
}

double Wall::get_deltax() {
	return delta_x;
}

double Wall::get_deltat() {
	return delta_t;
}

Vector Wall::get_xvalues() {
	return x_values;
}

Vector Wall::get_tvalues() {
	return t_values;
}

Matrix *Wall::get_grid() {
	return &grid;
}
