#ifndef IMPLICIT_H  
#define IMPLICIT_H

#include "../method.h"

class Implicit: public Method {
private:
	void set_initial_conditions(unsigned int x_size, unsigned int t_size);
protected:
	Matrix matrix;
	double c;
public:
	Implicit(Wall wall);
	virtual void compute_solution() = 0;
};

#endif