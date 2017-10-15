#ifndef DUFORT_FRANKEL_H  
#define DUFORT_FRANKEL_H

#include "explicit.h"

class DufortFrankel: public Explicit {
public:
	DufortFrankel(Wall wall);
	void compute_solution();
};

#endif