#ifndef EXPLICIT_H  
#define EXPLICIT_H

#include "../method.h"

class Explicit: public Method {
private:
	Vector first_iteration(Vector v);
protected:
	double q;
	virtual Vector build_iteration(Vector current_step, Vector previous_step) = 0;
public:
	Explicit(Wall wall);
	void compute_solution();
};

#endif