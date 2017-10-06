all: *.cpp
	g++ -std=c++11 *.cpp -o waveequation
saveplot:
	gnuplot -e "set tics scale 0; set border 3; set yrange [-0.2:1.2]; set ylabel \"f(i)\";set xlabel \"i\"; set datafile separator ','; set key outside; set term png; set output \"./plots/"$$cases"/"$$size"/"$$scheme".png\"; plot for [col=1:3] \"./matrices/"$$cases"/"$$size"/"$$scheme".csv\" using col with lines title columnheader lw 2;"
plot:
	make
	for root in "matrices" "plots"; do \
		for cases in "1stcase" "2ndcase"; do \
			for size in 100 200 400; do \
				if [ ! -d ./$$root/$$cases/$$size ]; then \
			  		mkdir -p ./$$root/$$cases/$$size; \
				fi; \
			done; \
		done; \
	done; 
	./waveequation
	for cases in "1stcase" "2ndcase"; do \
		for scheme in "analitical" "upwind" "centraldifference" "lax" "leapfrog"; do \
			for size in 100 200 400; do \
				make cases=$$cases scheme=$$scheme size=$$size saveplot; \
			done; \
		done; \
	done; 
clean:
	\rm  -r ./matrices
