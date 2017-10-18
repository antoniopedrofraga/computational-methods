#ifndef RICHARDSON_H  
#define RICHARDSON_H

#include "explicit.h"

class Richardson: public Explicit {
protected:
	Vector build_iteration(Vector current_step, Vector previous_step);
public:
	Richardson(Wall wall);
};

#endif