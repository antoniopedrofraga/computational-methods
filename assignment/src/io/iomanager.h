#ifndef IO_MANAGER_H  
#define IO_MANAGER_H

#include "../libs/gnuplot-iostream.h"
#include "../methods/method.h"

class IOManager {
private:
	const std::string pathname = "../plots";

	bool create_plots_dir();
	void plot(Method * analytical, Method * method);
	std::string double_to_string(double value);
public:
	IOManager();
	void export_plots(Method * analytical, std::vector<Method*> methods);
};

#endif