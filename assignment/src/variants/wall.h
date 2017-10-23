#ifndef WALL_H  
#define WALL_H

#include "../variants/utils.h"
#include "../grid/matrix.h"

class Wall {
private:
	double delta_x;
	double delta_t;

	unsigned int x_size;
	unsigned int t_size;

	Vector x_values;
	Vector t_values;

	Matrix grid;

	void set_x_values();
	void set_t_values();
	
public:
	Wall();
	Wall(double dt, double dx);
	unsigned int get_xsize();
	unsigned int get_tsize();
	double get_deltax();
	double get_deltat();
	Vector get_xvalues();
	Vector get_tvalues();
	Vector get_first_row();
	Matrix *get_grid();
	void set_time_step(Vector step, double time);
	void set_initial_conditions();
};

#endif