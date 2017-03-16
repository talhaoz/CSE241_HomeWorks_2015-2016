all: main
	

main: main.cpp
	g++ -c CPUProgram.cpp
	g++ -c CPU.cpp
	g++ -c _mainTester.cpp
	g++ -c Memory.cpp
	g++ -c Computer.cpp

	g++ CPUProgram.o CPU.o Memory.o Computer.o _mainTester.o -o exec


clean:
	rm *.o exec
