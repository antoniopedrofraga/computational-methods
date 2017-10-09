all: *.cpp
	g++ -std=c++11 -Lmydirlib -lliblapacke -lliblapack -lllibblas -lgfortran *.cpp -o heattransfer
run:
	make
	./heattransfer
saveplot:
	gnuplot -e "set title \""$$scheme" method at t = "$$time" and r = "$$r"\";set tics scale 0; set border 3; set yrange [-0.2:1]; set ylabel \"f(x)\";set xlabel \"x\"; set datafile separator ','; set key outside; set term png; set output \"./plots/"$$scheme"t="$$time"r="$$r".png\"; plot \"./matrices/"$$scheme"t="$$time"r="$$r".csv\" using 1 with lines title columnheader lw 2 lt rgb \"red\", \"./matrices/"$$scheme"t="$$time"r="$$r".csv\" using 2 with points title columnheader pt 17 ps 1 lw 1"
plot:
	make
	for root in "matrices" "plots"; do \
		if [ ! -d ./$$root/ ]; then \
	  		mkdir -p ./$$root/; \
		fi; \
	done; \

	for scheme in "simpleexplicit" "thomas" "lupartialpivoting"; do \
		for time in 1.20 5.20 10.00; do \
			for r in 0.40 0.51 0.60; do \
				./heattransfer $$scheme 30 $$time $$r 0.02; \
			done; \
		done; \
	done; \

	for root in "matrices" "plots"; do \
		for scheme in "simpleexplicit" "thomas" "lupartialpivoting"; do \
			for time in 1.20 5.20 10.00; do \
				for r in 0.40 0.51 0.60; do \
					make scheme=$$scheme time=$$time r=$$r saveplot; \
				done; \
			done; \
		done; \
	done;
testlu:
	make
	./heattransfer lupartialpivoting 30 10.00 0.40 0.02;
clean:
	\rm  -r ./matrices 
	\rm  -r ./plots
