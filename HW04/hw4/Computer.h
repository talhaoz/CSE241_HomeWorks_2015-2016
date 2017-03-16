//Computer.h  header file

//if there is any library included before, dont include it again

#ifndef COMPUTER_H

#define COMPUTER_H

//includes all libraries here that we need
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

using namespace std;


class Computer
{
public:
	//computer constructor take the class objects and the option
	Computer(const CPU &myfirstCPU,const CPUProgram &myfirstProg,const Memory &myfirstMem,int option);
	Computer(int option); // this constructor just take the option

	void setCPU(const CPU &myfirstCPU); // this gonna set the CPU object
	void setCPUProgram(const CPUProgram &myfirstProg);	// this gonna set the CPUprogram object
	void setMemory(const Memory &myfirstMem);	// this gonna set the memory object
	
	CPU getCPU() { return myCPU; } // it returns the Cpu object when required
	CPUProgram getCPUProgram() { return myProg; }	// it returns the Cpuprogram object when required
	Memory getMemory() { return myMemory; }	// it returns the memory object when required
	
	bool execute();	// this func for execute the program (details in Computer.cpp file)

private:
	// making the class objects that we needed
	CPU myCPU;
	CPUProgram myProg;
	Memory myMemory;
	int opt; // its going to keep the entered option

};


#endif

/*############################################################################*/
/* 						       END OF Computer.h                              */
/*############################################################################*/