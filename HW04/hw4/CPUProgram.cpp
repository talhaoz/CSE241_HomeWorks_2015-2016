//includes for CPUProgram.cpp

#include <iostream>
#include <string>
#include <fstream>

//include CPUProgram.h which keeps the class information
#include "CPUProgram.h"

using namespace std;

//constructor gonna call readfile func
CPUProgram::CPUProgram(const char *fileName)
{
	ReadFile(fileName);
}

CPUProgram::CPUProgram()
{
	int i;   //mean nothing
	i=0;
}

//readfile func gonna read the lines from file one by one
void CPUProgram::ReadFile(const char *fileName)
{
	int i=1;
	fstream inputStream;

	//open file
	inputStream.open(fileName);

	//get the lines into string array
	while(getline(inputStream,lines[i]))
		++i;

	sizeOfLines=i-1; //i miles 1 because we started the index from 1

	//close file
	inputStream.close();
}

/*############################################################################*/
/* 						       END OF CPUProgram.cpp                          */
/*############################################################################*/