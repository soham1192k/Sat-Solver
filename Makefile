.SILENT:
CPP=g++
FLAGS=-std=c++17
all:satsolver.cpp input.txt output.txt
	$(CPP) $(FLAGS) satsolver.cpp
	./a.out
clean:
	rm -rf *.out
