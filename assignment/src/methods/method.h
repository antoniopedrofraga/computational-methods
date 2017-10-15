#ifndef METHOD_H  
#define METHOD_H

#include "../variants/wall.h"

class Method {
protected:
	Wall wall;
public:
	Method();
	~Method();
	Method(Wall wall);
	virtual void compute_solution() = 0;
};

#endif