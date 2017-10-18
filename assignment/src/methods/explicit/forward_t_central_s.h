#ifndef FORWARD_TIME_CENTRAL_SPACE_H  
#define FORWARD_TIME_CENTRAL_SPACE_H

#include "explicit.h"

class FTCS: public Explicit {
public:
	FTCS(Wall wall);
	Vector build_iteration(Vector current_step, Vector previous_step);
};

#endif