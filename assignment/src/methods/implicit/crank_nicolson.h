#ifndef CRANK_NICOLSON_H  
#define CRANK_NICOLSON_H

#include "implicit.h"

class CrankNicolson: public Implicit {
public:
	CrankNicolson(Wall wall);
	void compute_solution();
};

#endif