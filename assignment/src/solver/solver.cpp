#include "solver.h"

const double Solver::THICKNESS = 1.0;
const double Solver::TIMELIMIT = 0.5;

Solver::Solver(double delta_t) {
	this->delta_x = 0.05;
	this->delta_t = delta_t;
	this->x_size = (int)(THICKNESS / this->delta_x);
	this->t_size = (int)(TIMELIMIT / this->delta_t);
	this->matrix = Matrix(this->x_size + 1, this->t_size + 1);
	setXValues();
	setTValues();
}

void Solver::setXValues() {
	for (unsigned int index = 0; index < this->x_size; index++) {
		this->x_values[index] = this->delta_x * index;
	}
}

void Solver::setTValues() {
	for (unsigned int index = 0; index < this->t_size; index++) {
		this->t_values[index] = this->delta_t * index;
	}
}

void Solver::setInitialConditions() {
	for (unsigned int n = 0; n < this->x_size; n++) {
		this->matrix[0][n] = 100;
	}
	for (unsigned int t = 0; t < this->t_size; t++) {
		this->matrix[t][this->x_size] = this->matrix[t][0] = 300;
	}
}