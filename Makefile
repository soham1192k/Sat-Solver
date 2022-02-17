.SILENT:
CPP=g++
FLAGS=-std=c++17
all:solver.cpp input.txt output.txt
	$(CPP) $(FLAGS) solver.cpp
	./a.out
clean:
	rm -rf *.out
