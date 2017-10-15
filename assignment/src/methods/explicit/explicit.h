#ifndef EXPLICIT_H  
#define EXPLICIT_H

#include "../method.h"

class Explicit: public Method {
protected:
	Vector current_iteration, temp_a, temp_b;
public:
	Explicit(Wall wall);
	virtual void compute_solution() = 0;
};

#endif