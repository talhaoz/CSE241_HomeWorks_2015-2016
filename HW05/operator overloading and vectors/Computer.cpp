//includes for Computer.cpp
#include <iostream>

//we ve already include the memory, cpu  and cpuprogram libraries in computer.h
#include "Computer.h"


using namespace std; 

// computer constructor gonna initialize the option value and set the classes
Computer::Computer(const CPU &myfirstCPU,const CPUProgram &myfirstProg,const Memory &myfirstMem,int option)
{	
	opt=option;
	setCPU(myfirstCPU);
	setCPUProgram(myfirstProg);
	setMemory(myfirstMem);
	
}

// this gonna just set the option into private option in computer class
Computer::Computer(int option)
{
	opt=option;
}

//this is for setting the Cpu class
void Computer::setCPU(const CPU &myfirstCPU)
{
	myCPU=myfirstCPU;


}

//this is for setting the Cpuprogram class
void Computer::setCPUProgram(const CPUProgram &myfirstProg)
{
	myProg=myfirstProg;

} 
//this is for setting the Memory class
void Computer::setMemory(const Memory &myfirstMem)
{
	myMemory=myfirstMem;

}

// this func gonna get the lines and call for Cpu to run the instruction
bool Computer::execute()
{	
	bool res;
	//loop for execute all instructions untill program halted
	while(!myCPU.halted())
	{
		//string for get everyline from big string array
		string instruction=myProg.getLine(myCPU.getPC());

		//then execute the line according to instruction
		res=myCPU.execute(instruction,myMemory);

		//if execute func return false , there is some kind of error,so exit program
		if(!res)
			return false;

	}

	return true;
}

/*############################################################################*/
/* 						       END OF Computer.cpp                            */
/*############################################################################*/