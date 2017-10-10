#include "wall.h"

const double Wall::THICKNESS = 1.0;
const double Wall::TIMELIMIT = 0.5;

Wall::Wall() {}

Wall::Wall(double delta_t) {
	this->delta_x = 0.05;
	this->delta_t = delta_t;
	this->x_size = (int)(THICKNESS / this->delta_x);
	this->t_size = (int)(TIMELIMIT / this->delta_t);
	this->grid = Matrix(NUMBER_TIME_STEPS, this->x_size + 1);
	set_x_values();
	set_t_values();
}

void Wall::set_x_values() {
	for (unsigned int index = 0; index < this->x_size; index++) {
		this->x_values[index] = this->delta_x * index;
	}
}

void Wall::set_t_values() {
	this->t_values = Vector(NUMBER_TIME_STEPS);
	for (unsigned int time; time < NUMBER_TIME_STEPS; time++) {
		this->t_values[time] = time * 0.1;
	}
}

void Wall::set_initial_conditions() {
	for (unsigned int index = 1; index < this->x_size; index++) {
		this->grid[0][index] = INITIAL_TEMPERATURE;
	}
	for (unsigned int time = 0; time < NUMBER_TIME_STEPS; time++) {
		this->grid[time][0] = this->grid[time][x_size] = SURFACE_TEMPERATURE;
	}
}