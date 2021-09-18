CPP=g++
FLAGS=-O2
all: hello

hello: main.o function.o
	$(CPP) $(FLAGS) main.o function.o -o hello

main.o: main.cpp
	$(CPP) $(FLAGS) -c main.cpp

function.o: function.cpp
	$(CPP) $(FLAGS) -c function.cpp

clean:
	rm *.o hello
