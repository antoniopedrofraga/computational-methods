#ifndef IMPLICIT_H  
#define IMPLICIT_H

#include "../method.h"

class Implicit: public Method {
private:
	Vector thomas_algorithm(Vector r, double a, double b, double c);
protected:
	double q;
	virtual Vector build_r(Vector previous_step) = 0;
public:
	Implicit(Problem problem);
	void compute_solution();
};

#endif