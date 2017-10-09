#ifndef SOLVER_H  
#define SOLVER_H

#include "../variants/utils.h"
#include "../grid/matrix.h"

class Solver {
	double delta_x;
	double delta_t;

	double x_size;
	double t_size;

	Vector x_values;
	Vector t_values;

	Matrix matrix;

	public:

	static const double THICKNESS;
	static const double TIMELIMIT;

	Solver(double dt);
	void setXValues();
	void setTValues();
	void setInitialConditions();
};

#endif