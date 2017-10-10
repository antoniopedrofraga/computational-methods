#ifndef RICHARDSON_H  
#define RICHARDSON_H

#include "method.h"

class Richardson: public Method {
public:
	Richardson(Wall wall);
	void compute_solution();
};

#endif