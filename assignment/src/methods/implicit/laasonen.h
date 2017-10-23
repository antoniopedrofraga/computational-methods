#ifndef LAASONEN_H  
#define LAASONEN_H

#include "implicit.h"

class Laasonen: public Implicit {
protected:
	Vector build_r(Vector previous_step);
public:
	Laasonen(Problem problem);
};

#endif