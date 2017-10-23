#ifndef DUFORT_FRANKEL_H  
#define DUFORT_FRANKEL_H

#include "explicit.h"

class DufortFrankel: public Explicit {
protected:
	Vector build_iteration(Vector current_step, Vector previous_step);
public:
	DufortFrankel(Problem problem);
};

#endif