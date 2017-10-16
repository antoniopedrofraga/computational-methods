#ifndef METHOD_H  
#define METHOD_H

#include "../variants/wall.h"

class Method {
protected:
	Wall wall;
	std::string name;
public:
	Method();
	~Method();
	Method(Wall wall);
	std::string get_name();
	Matrix get_grid();
	virtual void compute_solution() = 0;
};

#endif