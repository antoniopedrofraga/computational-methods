#ifndef CRANK_NICOLSON_H  
#define CRANK_NICOLSON_H

#include "implicit.h"

class CrankNicolson: public Implicit {
protected:
	Vector build_r(Vector previous_step);
public:
	CrankNicolson(Problem problem);
};

#endif