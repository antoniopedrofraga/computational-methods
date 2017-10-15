#ifndef RICHARDSON_H  
#define RICHARDSON_H

#include "explicit.h"

class Richardson: public Explicit {
public:
	Richardson(Wall wall);
	void compute_solution();
};

#endif