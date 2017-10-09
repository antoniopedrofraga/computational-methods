#ifndef WALL_H  
#define WALL_H

#include "../variants/utils.h"
#include "../grid/matrix.h"

class Wall {
	double delta_x;
	double delta_t;

	double x_size;
	double t_size;

	Vector x_values;
	Vector t_values;

	Matrix grid;

	void set_x_values();
	void set_t_values();
	void set_initial_conditions();
	public:
	static const double THICKNESS;
	static const double TIMELIMIT;

	Wall();
	Wall(double dt);
};

#endif