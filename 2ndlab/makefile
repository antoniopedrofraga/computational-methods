all: *.cpp
	g++ -std=c++11 *.cpp -o heattransfer
run:
	make
	./heattransfer
saveplot:
	gnuplot -e "set title \""$$scheme" method at t = "$$time"\";set tics scale 0; set border 3; set yrange [-0.2:1]; set ylabel \"f(x)\";set xlabel \"x\"; set datafile separator ','; set key outside; set term png; set output \"./plots/"$$scheme$$time".png\"; plot \"./matrices/"$$scheme$$time".csv\" using 1 with lines title columnheader lw 2 lt rgb \"red\", \"./matrices/"$$scheme$$time".csv\" using 2 with points title columnheader pt 17 ps 1 lw 1"
plot:
	make
	for root in "matrices" "plots"; do \
		if [ ! -d ./$$root/ ]; then \
	  		mkdir -p ./$$root/; \
		fi; \
	done; \

	for scheme in "simpleexplicit"; do \
		for time in 1.2 5.2 10.0; do \
			./heattransfer $$scheme 30 $$time; \
		done; \
	done; \

	for root in "matrices" "plots"; do \
		for scheme in "simpleexplicit"; do \
			for time in 1.2 5.2 10.0; do \
				make scheme=$$scheme time=$$time saveplot; \
			done; \
		done; \
	done;
clean:
	\rm  -r ./matrices 
	\rm  -r ./plots
