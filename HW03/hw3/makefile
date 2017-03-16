all: main
	

main: main.cpp
	g++ -c CPUProgram.cpp
	g++ -c CPU.cpp
	g++ -c main.cpp

	g++ CPUProgram.o CPU.o main.o -o exec


clean:
	rm *.o exe
