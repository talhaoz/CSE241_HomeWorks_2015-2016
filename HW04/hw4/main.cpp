/*----------------------------------------------------------------------------*/
/* */
/* HW03_131044003_Talha_Oz */
/* */
/*                              main.cpp                                      */
/* ---------------------------------------------------------------------------*/
/* Created on 27/10/2016 by Talha_OZ */ 
/*____________________________________________________________________________*/




/*############################################################################*/
/*                                 Includes                                   */
/*############################################################################*/


#include <iostream>
#include <string>

#include "CPUProgram.h"
#include "CPU.h"
#include "Memory.h"
#include "Computer.h"



//main func
int main(int argc, char const *argv[])
{
	int opt;
	 


	//if there is any argument missing ,give out an error
	if(argc > 3 || argc < 3)
	{
		cerr << "Unexpected Compile Type!" << endl;
		return 0;
	}

	//check the what opt entered
	if(argv[2][0]-'0'>=0 && argv[2][0]-'0'<=2)
		opt=argv[2][0]-'0';
	else
	{
		cerr << "Unexpected Compile Option!" << endl;
		return 0;
	}

	//call cpuProgram constructor for read from file
	CPUProgram  myProg(argv[1]);
	//call myCpu constructor for initialize
	CPU myCPU(opt);

	Memory myMemory(opt);

	//calling Computer class constructor for assign the objects and option
	Computer myComputer(myCPU,myProg,myMemory,opt);

	//execute the instructions
	if(!myComputer.execute())
		return 0;

	return 0;
}

/*############################################################################*/
/* 						       END OF main.cpp                                */
/*############################################################################*/