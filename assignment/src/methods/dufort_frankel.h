#ifndef DUFORT_FRANKEL_H  
#define DUFORT_FRANKEL_H

#include "method.h"

class DufortFrankel: public Method {
public:
	DufortFrankel(Wall wall);
	void compute_solution();
};

#endif