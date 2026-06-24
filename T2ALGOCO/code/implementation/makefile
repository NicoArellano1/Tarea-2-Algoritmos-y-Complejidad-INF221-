all: compile tests run plots

compile:
	g++ general.cpp algorithms/brute-force.cpp algorithms/greedy1.cpp algorithms/greedy2.cpp algorithms/dynamic-programming.cpp -o general

tests:
	cd scripts && python3 testcases_generator.py

run:
	./general

plots:
	cd scripts && python3 plot_generator.py

clean:
	rm -f general
	rm -f data/measurements/*
	rm -f data/outputs/*
	rm -f data/plots/*
	rm -rf data/testcases/