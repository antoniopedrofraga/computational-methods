#ifndef METHOD_H  
#define METHOD_H

#include "../wall.h"

class Method {
protected:
	Wall wall;
public:
	Method();
	Method(Wall wall);
};

#endif