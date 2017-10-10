#ifndef WALL_H  
#define WALL_H

#include "../variants/utils.h"
#include "../grid/matrix.h"

class Wall {
	double delta_x;
	double delta_t;

	unsigned int x_size;
	unsigned int t_size;

	Vector x_values;
	Vector t_values;

	Matrix grid;

	void set_x_values();
	void set_t_values();
	void set_initial_conditions();
	
	public:
	Wall();
	Wall(double dt);
	unsigned int get_xsize();
	unsigned int get_tsize();
	Vector get_xvalues();
	Vector get_tvalues();
	Matrix * get_grid();
};

#endif