#ifndef FORWARD_TIME_CENTRAL_SPACE_H  
#define FORWARD_TIME_CENTRAL_SPACE_H

#include "explicit.h"

class FTCS: public Explicit {
public:
	FTCS(Problem problem);
	Vector build_iteration(Vector current_step, Vector previous_step);
};

#endif