.SILENT:
CPP=g++
FLAGS=-std=c++17
all:satsolver.cpp input.txt output.txt compute.cpp
	$(CPP) $(FLAGS) satsolver.cpp -o satsolver.out 
	./satsolver.out
	$(CPP) $(FLAGS) compute.cpp -o compute.out
	./compute.out
clean:
	rm -rf *.out 
