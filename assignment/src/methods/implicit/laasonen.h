#ifndef LAASONEN_H  
#define LAASONEN_H

#include "implicit.h"

class Laasonen: public Implicit {
public:
	Laasonen(Wall wall);
	void compute_solution();
};

#endif