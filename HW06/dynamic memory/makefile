all: main
	

main: main.cpp
	g++ -c CPUProgramDyn.cpp -std=c++11
	g++ -c _mainTester.cpp -std=c++11

	g++ CPUProgramDyn.o _mainTester.o -o exe


clean:
	rm *.o exe
