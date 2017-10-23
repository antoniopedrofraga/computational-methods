#ifndef ANALYTICAL_H  
#define ANALYTICAL_H

#include "method.h"

class Analytical: public Method {
	unsigned int nr_of_expansions;
public:
	Analytical(Problem problem);
	void compute_solution();
};

#endif