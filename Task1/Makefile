all: matrix.cpp
	g++ -O0 -fopenmp -std=c++11 matrix.cpp -o matrix

test: matrix-test.cpp
	g++ -O0 -fopenmp -std=c++11 matrix-test.cpp -o matrix-test
intel: matrix-test.cpp
	icc -O2 -qopenmp -qopt-report=3 -qopt-report-phase=vec matrix-test.cpp -o matrix-test

clean:
	rm matrix matrix-test
