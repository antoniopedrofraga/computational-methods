#ifndef ANALYTICAL_H  
#define ANALYTICAL_H

#include "method.h"

class Analytical: public Method {
public:
	Analytical(Wall wall);
	void compute_solution();
};

#endif